/*
 * PlayerDriver.cpp

 *
 *  Created on: Jul 31, 2012
 *      Author: collins
 */

#include "config.h"

#if ENABLE(VIDEO) && USE(GSTREAMER)
#include "PlayerDriver.h"
#include "hxplatformobj.h"
//#include <iostream>
#include <stdio.h>

//using namespace std;

ENABLE_DLLACCESS_PATHS(g_SPlayAccessPath);


namespace WebCore{

PlayerDriver::PlayerDriver(MediaPlayerPrivateHelix* pPlayer) :
    m_Init(-1),
    m_pMediaPlayer(pPlayer),
    m_bIsLooping(false),
    m_bDoLoop(false),
    m_bDataReadyReceived(false),
    m_bEndOfData(false),
    m_nRecentSeek(0),
    m_bSeekComp(true),
    m_bSeekPending(false),
    m_bErrorPending(false),
    m_bSeekDelayed(false),
    m_nSeekDelayedPosition(0),
    m_bUnseekable(false),
    m_pDataSourcePath(NULL),
    m_pHXPlayer(NULL),
    // m_pAudioEqualizer(NULL),
    m_pClientEngine(NULL),
    m_pWebkitContext(NULL),
    m_pClientState(NULL),
    m_pContext(NULL),
    m_pMediaPlatform(NULL),
    m_pScheduler(NULL),
    m_pEvent(NULL),
    // m_pReg(NULL),
    m_LastError(HXR_OK),
    // m_pAudioDevice(NULL),
    m_bRestart(false),
    m_pCommandsProcessCallback(NULL)
    , m_bIsPlayingWhenSuspend(true)
    , m_PositionWhenSuspend(-1)
    , m_bEnableSendEvent(false)
    , m_pMsgSender(NULL)
{
	printf("PlayerDriver constructor\n");
    HXEvent::MakeEvent(m_pEvent, NULL, FALSE);
}

PlayerDriver::~PlayerDriver()
{
    HX_DELETE(m_pEvent);
    // HX_RELEASE(m_pReg);
}

PlayerCommand* PlayerDriver::dequeueCommand()
{
	printf("HelixOverWebkit [%s] [%s] [%d]\n", __FILE__, __FUNCTION__, __LINE__);
    PlayerCommand* ec = NULL;

    m_QueueLock.lock();
    if (!m_CommandQueue.isEmpty())
    {
        //ec = *(--m_CommandQueue.end());
        //m_CommandQueue.erase(--m_CommandQueue.end());
    	ec = m_CommandQueue.pop();

    }
    m_QueueLock.unlock();

    return ec;
}

status_t PlayerDriver::enqueueCommand(PlayerCommand* ec)
{
	printf("HelixOverWebkit [%s] [%s] [%d]\n", __FILE__, __FUNCTION__, __LINE__);
    if (FAILED(m_LastError))
    {
        return m_LastError;
    }

    if (getErrorPending())
    {
        setErrorPending(false);
    }

    bool syncMode = false;

    // If the user didn't specify a completion callback, we
    // are running in synchronous mode.
    if (ec->hasCompletionHook())
    {
        ec->set(PlayerDriver::syncCompletion, this);
        syncMode = true;
    }

    // save command, since ec will be deleted by the standard completion function
    int command = ec->command();

    // Add the command to the queue.
    m_QueueLock.lock();
    //m_CommandQueue.push_front(ec);
    m_CommandQueue.push(ec);

    // Schedule for process
    CHXGenericCallback* pCallback = new CHXGenericCallback((void*) this, CommandsProcessCallbackFunc);
    HX_ADDREF(pCallback);
    if (pCallback && ! pCallback->IsCallbackPending())
	{
    	pCallback->ScheduleRelative(m_pScheduler, 0);
    }
    HX_RELEASE(pCallback);
    m_QueueLock.unlock();

    // If we are in synchronous mode, wait for completion.
    if (syncMode)
    {
        static const char * player_command_type_string[] = {
            "PLAYER_QUIT"                     ,
            "PLAYER_SET_DATA_SOURCE"          ,
            "PLAYER_INIT"                     ,
            "PLAYER_PREPARE"                  ,
            "PLAYER_START"                    ,
            "PLAYER_STOP"                     ,
            "PLAYER_PAUSE"                    ,
            "PLAYER_RESET"                    ,
            "PLAYER_SET_LOOP"                 ,
            "PLAYER_SEEK"                     ,
            "PLAYER_GET_POSITION"             ,
            "PLAYER_GET_DURATION"             ,
            "PLAYER_GET_STATUS"               ,
            "PLAYER_GET_TRACK_INFO_SIZE"      ,
            "PLAYER_GET_ALLTRACK_INFO"        ,
            "PLAYER_GET_CURTRACK_ID"          ,
            "PLAYER_SET_CURTRACK_ID"          ,
            "PLAYER_SET_VELOCITY"             ,
            "PLAYER_GET_VELOCITY"
        };

        //cout << "waiting for handle command %s ..." << player_command_type_string[command - 1]) << endl;
		printf("HelixOverWebkit [%s] [%s] [%d] waiting for handle command\n", __FILE__, __FUNCTION__, __LINE__, player_command_type_string[command - 1]);
        m_pEvent->Wait();
        //cout << "handle command %s OK." << player_command_type_string[command - 1]) << endl;
		printf("HelixOverWebkit [%s] [%s] [%d] handle command %s OK.\n", __FILE__, __FUNCTION__, __LINE__, player_command_type_string[command - 1]);
        if (command == PlayerCommand::PLAYER_QUIT)
        {
            return 0;
        }

        return m_SyncStatus;
    }

    return OK;
}

inline void PlayerDriver::setErrorPending(bool b)
{
    m_bErrorPending = b;
}

inline bool PlayerDriver::getErrorPending()
{
    return m_bErrorPending;
}

void PlayerDriver::syncCompletion(status_t s, void *cookie)
{
	printf("HelixOverWebkit [%s] [%s] [%d]\n", __FILE__, __FUNCTION__, __LINE__);
    PlayerDriver *ed = static_cast<PlayerDriver*>(cookie);
    ed->m_SyncStatus = s;
    ed->m_pEvent->SignalEvent();
}

void PlayerDriver::CommandsProcessCallbackFunc(void* pParam)
{
    if (pParam)
    {
        PlayerDriver* pObj = (PlayerDriver*) pParam;
        pObj->HandleCommandsProcessCallback();
    }
}

void PlayerDriver::HandleCommandsProcessCallback(void)
{
    status_t returnStatus = UNKNOWN_ERROR;
    PlayerCommand* ec = DoProcessQueue(returnStatus);

    // Schedule for next command if any
    if (!m_CommandQueue.isEmpty())
    {
        m_pCommandsProcessCallback->ScheduleRelative(m_pScheduler, 0);
    }

    if (ec)
    {
        // signal for completion
        commandCompleted(ec, returnStatus);
    }
}

PlayerCommand* PlayerDriver::DoProcessQueue(status_t& ret)
{
    PlayerCommand* ec = dequeueCommand();
	printf("HelixOverWebkit [%s] [%s] [%d] ec %p, ec->command() %d\n", __FILE__, __FUNCTION__, __LINE__, ec, (ec == NULL)?-1: ec->command());
    if (ec)
    {
        switch(ec->command())
        {
        case PlayerCommand::PLAYER_SET_DATA_SOURCE:
            ret = handleSetDataSource(static_cast<PlayerSetDataSource*>(ec));
            break;

        case PlayerCommand::PLAYER_PREPARE:
            ret = handlePrepare(static_cast<PlayerPrepare*>(ec));
            break;

        case PlayerCommand::PLAYER_START:
            ret = handleStart(static_cast<PlayerStart*>(ec));
            break;

        case PlayerCommand::PLAYER_STOP:
            ret = handleStop(static_cast<PlayerStop*>(ec));
            break;

        case PlayerCommand::PLAYER_PAUSE:
            ret = handlePause(static_cast<PlayerPause*>(ec));
            break;

        case PlayerCommand::PLAYER_SEEK:
            ret = handleSeek(static_cast<PlayerSeek*>(ec));
            break;

        case PlayerCommand::PLAYER_GET_POSITION:
            ret = handleGetPosition(static_cast<PlayerGetPosition*>(ec));
            break;

        case PlayerCommand::PLAYER_RESET:
            ret = handleReset(static_cast<PlayerReset*>(ec));
            break;

        case PlayerCommand::PLAYER_QUIT:
            ret = handleQuit(static_cast<PlayerQuit*>(ec));
            break;

        default:
            //cout << "Unexpected command %d" <<  ec->command();
            break;
        }
    }
    return ec;
}

void PlayerDriver::commandCompleted(PlayerCommand* ec, status_t status)
{
    if(status != OK)
    {
        //cout << "Command failed: %d", ec->command() << endl;
        // FIXME: Ignore seek failure because it might not work when streaming
        if (m_bSeekPending)
        {
            //cout << "Ignoring failed seek" << endl;
            ec->complete(NO_ERROR);
            m_bSeekPending = false;
        }
        else
        {
            ec->complete(status);
        }
    }
    else
    {
        ec->complete(OK);
    }
    delete ec;
}

status_t PlayerDriver::handleSetDataSource(PlayerSetDataSource* ec)
{
    const char* url = ec->url();
    if(m_pDataSourcePath)
    {
        free(m_pDataSourcePath);
        m_pDataSourcePath = NULL;
    }
    m_pDataSourcePath = strdup(url);

	SetConfig("FinishMode", /*FINISH_PAUSE*/FINISH_RESTART_TO_PREFETCH);

    return OK;
}

status_t PlayerDriver::handlePrepare(PlayerPrepare* ec)
{
    //std::cout << "PlayerDriver::handlePrepare...");
    return m_pHXPlayer->OpenURL(m_pDataSourcePath);
}

status_t PlayerDriver::handleStart(PlayerStart* ec)
{
    // for video, set thread priority so we don't hog CPU
	/*
    if (m_spSurfaceTexture.get())
    {
        int ret = setpriority(PRIO_PROCESS, 0, ANDROID_PRIORITY_DISPLAY);
    }
    // for audio, set thread priority so audio isn't choppy
    else
    {
        int ret = setpriority(PRIO_PROCESS, 0, ANDROID_PRIORITY_AUDIO);
    }
	*/

    m_bSeekComp = true;
    m_pHXPlayer->Begin();
    //cout << "begin to play" << endl;

    return OK;
}

status_t PlayerDriver::handleSeek(PlayerSeek* ec)
{
    int eState = 0;
    if(m_pClientState)
    {
        eState = m_pClientState->GetState();
    }
    // If we received the seek instruction before prepared,
    // we should delay this seeking operation to ensure seeking successfully.
    if (eState < HX_CLIENT_STATE_OPENED)
    {
        m_bSeekDelayed = true;
        m_nSeekDelayedPosition = ec->msec();
        //TODO: should notify seek complete
        //m_pMediaPlayer->sendEvent(android::MEDIA_SEEK_COMPLETE);
        m_bEndOfData = false;
        return OK;
    }
    // Cache the most recent seek request
    m_nRecentSeek = ec->msec();
    //cout << "handleSeek(%d)" <<  m_nRecentSeek << endl;
    // TODO
    //m_pWebkitContext->m_bSeekCompleteNeedSend = true;
#ifdef HELIX_FEATURE_BEST_EFFORT_SEEK
    m_pHXPlayer->Seek(m_nRecentSeek,FALSE);
#else
    m_pHXPlayer->Seek(m_nRecentSeek);
#endif
    m_bEndOfData = false;
    return OK;
}

status_t PlayerDriver::handleGetPosition(PlayerGetPosition* ec)
{
    ULONG32 t = m_pHXPlayer? m_pHXPlayer->GetCurrentPlayTime(): 0;
    ec->set(t);
    return OK;
}

status_t PlayerDriver::handleStop(PlayerStop* ec)
{
    // setting the looping boolean to false. MediaPlayer app takes care of setting the loop again before the start.
    m_bIsLooping = false;
    m_bDoLoop = false;

    m_pHXPlayer->Stop();
    return OK;
}

status_t PlayerDriver::handlePause(PlayerPause* ec)
{
    if ( IsRTSPLive() )
    {
        //cout << "We are playing with rtsp live streaming, stop!" << endl;
        return handleStop(NULL);
    }

    // pause and return OK - we ignore errors in case it's a network stream
    m_pHXPlayer->Pause();
    return OK;
}

status_t PlayerDriver::handleReset(PlayerReset* ec)
{
    //cout << "handleReset" << endl;

    // setting the looping boolean to false. MediaPlayer app takes care of setting the loop again before the start.
    m_bIsLooping = false;
    m_bDoLoop = false;
    m_bEndOfData = false;

    ResetPlaybackEngine();

    return OK;
}

status_t PlayerDriver::handleQuit(PlayerQuit* ec)
{
    //cout << "handleQuit" << endl;
    if(m_pDataSourcePath)
    {
        free(m_pDataSourcePath);
        m_pDataSourcePath = NULL;
    }

    CleanupPlaybackEngine();

    return OK;
}

void PlayerDriver::setLooping( int isLooping )
{
    m_bIsLooping = isLooping;
    if (m_bIsLooping)
    {
        SetConfig("FinishMode", FINISH_RESTART_TO_PREFETCH);
        SetConfig("LoopingInCurrentTrack", TRUE);
    }
}

#ifdef HELIX_FEATURE_SIMPLE_CORE
HX_RESULT PlayerDriver::SelectClientEngine(bool bRealTime, const char* url, int fd)
{
    const char* pszURL = NULL;
    char pszName1[MAX_PATH];
    char pszName2[MAX_PATH];
    if (fd != -1)
    {
        // Query full path first
        snprintf(pszName1, MAX_PATH-1, "/proc/%d/fd/%d", getpid(), fd);
        INT32 lLen = readlink(pszName1, pszName2, MAX_PATH-1);
        pszName2[lLen] = '\0';
        snprintf(pszName1, MAX_PATH-1, "file://%s", pszName2);
        pszURL = pszName1;
    }
    else
    {
        pszURL = url;
    }

    m_bRealTimeMode    = bRealTime;
    m_bIsUseSimpleCore = false;
    if(0 == strnicmp("file://",pszURL,7)
       || 0 == strnicmp("http://",pszURL,7)
       || 0 == strnicmp("https://",pszURL,8))
    {
        // Local file
        const char *pszExt = strrchr(pszURL, '.');
        if ( !pszExt ||
             !strnicmp(pszExt, ".mp3", 4) ||
             !strnicmp(pszExt, ".apk", 4) ||
             !strnicmp(pszExt, ".wma", 4) ||
             !strnicmp(pszExt, ".wav", 4) ||
             !strnicmp(pszExt, ".ra", 3) ||
             !strnicmp(pszExt, ".au", 3) ||
             !strnicmp(pszExt, ".ape", 4) ||
             !strnicmp(pszExt, ".ogg", 4) ||
             !strnicmp(pszExt, ".flac", 5) ||
             !strnicmp(pszExt, ".aiff", 5) ||
             !strnicmp(pszExt, ".m4a", 4) ||
             !strnicmp(pszExt, ".aac", 4) ||
             !strnicmp(pszExt, ".mp2", 4) ||
             !strnicmp(pszExt, ".amr", 4) ||
             !strnicmp(pszExt, ".mka", 4) )
        {
            //std::cout << "Used Simple core for audio playback<%s>________\n",pszURL);
            m_bIsUseSimpleCore = true;
        }
    }
}
#endif

HX_RESULT PlayerDriver::SetupPlaybackEngine()
{
	printf("HelixOverWebkit [%s] [%s] [%d]\n", __FILE__, __FUNCTION__, __LINE__);
    HX_RESULT retVal = HXR_OK;

    // get IHXMediaPlatform
    if (!m_pMediaPlatform)
    {
        retVal = HXMediaPlatformObj::CreateMediaPlatform(m_pMediaPlatform);
        if (FAILED(retVal))
        {
            //cout << "Can not load helix media platform." << endl;
			printf("HelixOverWebkit [%s] [%s] [%d] Can not load helix media platform\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }

    // Get IUnknown* context from the media platform
    if (SUCCEEDED(retVal) && !m_pContext)
    {
        retVal = m_pMediaPlatform->QueryInterface(IID_IUnknown, (void**) &m_pContext);
        if (FAILED(retVal))
        {
            //cout << "QueryInterface for IUnknown failed.";
			printf("HelixOverWebkit [%s] [%s] [%d] QueryInterface for IUnknown failed\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }

    // Get CCF for creating engine
    IHXCommonClassFactory* pCCF = NULL;
    if (SUCCEEDED(retVal))
    {
        retVal = m_pMediaPlatform->QueryInterface(IID_IHXCommonClassFactory, (void**)&pCCF);
        if (FAILED(retVal))
        {
            //cout << "QueryInterface for IHXCommonClassFactory failed.";
			printf("HelixOverWebkit [%s] [%s] [%d] QueryInterface for IHXCommonClassFactory failed\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }

    // Create client engine
    if (SUCCEEDED(retVal))
    {
        {
            retVal = pCCF->CreateInstance(CLSID_IHXClientEngine, (void**)&m_pClientEngine);
        }
	if (FAILED(retVal))
        {
            //cout << "Can not create IHXClientEngine via m_pMediaPlatform." << endl;
			printf("HelixOverWebkit [%s] [%s] [%d] Can not create IHXClientEngine via m_pMediaPlatform.\n", __FILE__, __FUNCTION__, __LINE__);
            HXMediaPlatformObj::ResetMediaPlatformNoDelay();
        }
        HX_RELEASE(pCCF);
    }

    if (SUCCEEDED(retVal))
    {
        m_pClientEngine->QueryInterface(IID_IHXPreferences, (void**)&m_pPreferences);
    }

     // Create player
    if (SUCCEEDED(retVal))
    {
        retVal = m_pClientEngine->CreatePlayer(m_pHXPlayer);
        if (FAILED(retVal))
        {
            //cout << "Cannot create player";
			printf("HelixOverWebkit [%s] [%s] [%d] Cannot create player\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }

    // Create client context
    // TODO: context and errorsink
    if (SUCCEEDED(retVal))
    {
        m_pWebkitContext = new WebkitClientContext();
        if (m_pWebkitContext)
        {
            HX_ADDREF(m_pWebkitContext);
            m_pWebkitContext->Init(m_pHXPlayer, m_pMediaPlayer);
        }
        else
        {
			printf("HelixOverWebkit [%s] [%s] [%d] Cannot create client context\n", __FILE__, __FUNCTION__, __LINE__);
            retVal = HXR_FAIL;
        }
    }

    // Make client context available to the player
    if (SUCCEEDED(retVal))
    {
        IUnknown* pUnk = NULL;
        m_pWebkitContext->QueryInterface(IID_IUnknown, (void**)&pUnk);
        if (pUnk)
        			{
            m_pHXPlayer->SetClientContext(pUnk);
            HX_RELEASE(pUnk);
        			}
        else
        			{
        			printf("HelixOverWebkit [%s] [%s] [%d] Cannot create client context\n", __FILE__, __FUNCTION__, __LINE__);
            retVal = HXR_FAIL;
        			}
    }

    // Set error sink
	/*
    if (SUCCEEDED(retVal))
    {
        IHXErrorSinkControl* pErrorSinkControl = NULL;
        IHXErrorSink* pErrorSink = NULL;
        m_pHXPlayer->QueryInterface(IID_IHXErrorSinkControl, (void**) &pErrorSinkControl);
        m_pWebkitContext->QueryInterface(IID_IHXErrorSink, (void**) &pErrorSink);
        if (pErrorSinkControl && pErrorSink)
        {
            pErrorSinkControl->AddErrorSink(pErrorSink, HXLOG_EMERG, HXLOG_INFO);
        }
        else
        {
            //cout << "Cannot set error sink";
            retVal = HXR_FAIL;
        }

        HX_RELEASE(pErrorSinkControl);
        HX_RELEASE(pErrorSink);
    }
	*/

    // Obtain player client state interface
    if (SUCCEEDED(retVal))
    {
        retVal = m_pHXPlayer->QueryInterface(IID_IHXClientState, (void**)&m_pClientState);
        if (FAILED(retVal))
        {
            //cout << "can not get IHXClientState";
			printf("HelixOverWebkit [%s] [%s] [%d] can not get IHXClientState\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }
	printf("HelixOverWebkit [%s] [%s] [%d]\n", __FILE__, __FUNCTION__, __LINE__);

    // Get scheduler
    if (SUCCEEDED(retVal) && !m_pScheduler)
    {
        retVal = m_pMediaPlatform->QueryInterface(IID_IHXScheduler, (void**)&m_pScheduler);
        if (FAILED(retVal))
        {
            //cout << "QueryInterface for IID_IHXScheduler failed.";
			printf("HelixOverWebkit [%s] [%s] [%d] QueryInterface for IID_IHXScheduler failed.\n", __FILE__, __FUNCTION__, __LINE__);
        }
    }

    if (SUCCEEDED(retVal) && !m_pCommandsProcessCallback)
    {
        m_pCommandsProcessCallback = new CHXGenericCallback((void*) this, CommandsProcessCallbackFunc);
        if (m_pCommandsProcessCallback)
        {
            m_pCommandsProcessCallback->AddRef();
        }
        else
        {
            //cout << "Create CHXGenericCallback failed.";
			printf("HelixOverWebkit [%s] [%s] [%d] Create CHXGenericCallback failed.\n", __FILE__, __FUNCTION__, __LINE__);
            retVal = HXR_FAIL;
        }
    }

	printf("HelixOverWebkit [%s] [%s] [%d]\n", __FILE__, __FUNCTION__, __LINE__);
    if (FAILED(retVal))
    {
        CleanupPlaybackEngine();
        m_LastError = retVal;
    }
    else
    {
        m_Init = 0;
    }
	printf("HelixOverWebkit [%s] [%s] [%d]\n setupplaybackengine ends retVal %x\n", __FILE__, __FUNCTION__, __LINE__, retVal);
    if (retVal != HXR_OK)
    	return false;
}

void PlayerDriver::ResetPlaybackEngine()
{
    if (m_pHXPlayer)
    {
        m_pHXPlayer->Stop();
    }

    HX_RELEASE(m_pPreferences);
    HX_RELEASE(m_pClientState);
    if(m_pWebkitContext)
    {
        m_pWebkitContext->Close();
        HX_RELEASE(m_pWebkitContext);
    }
	/*
    if (m_pAudioDevice)
    {
        if (m_pHXPlayer)
        {
            IHXAudioDeviceManager* pAudioDeviceManager = NULL;
            m_pHXPlayer->QueryInterface(IID_IHXAudioDeviceManager, (void**)&pAudioDeviceManager);
            if (pAudioDeviceManager)
            {
                pAudioDeviceManager->Remove(m_pAudioDevice);
                HX_RELEASE(pAudioDeviceManager);
            }
        }
        HX_RELEASE(m_pAudioDevice);
    }
    */
#if defined(HELIX_FEATURE_AUDIO_EQUALIZER)
    HX_RELEASE(m_pAudioEqualizer);
#endif
#ifdef HELIX_FEATURE_MULTITRACK_SELECTION
    HX_RELEASE(m_pMultiTrackSelector);
#endif
    if (m_pHXPlayer)
    {
        m_pClientEngine->ClosePlayer(m_pHXPlayer);
        HX_RELEASE(m_pHXPlayer);
    }

    if (m_pClientEngine)
    {
        IHXClientEngine2* pEngine2 = NULL;
        if (HXR_OK == m_pClientEngine->QueryInterface(IID_IHXClientEngine2, (void**)&pEngine2))
        {
            pEngine2->Close();
        }
        HX_RELEASE(pEngine2);
        HX_RELEASE(m_pClientEngine);
    }

    m_Init = -1;
}

void PlayerDriver::CleanupPlaybackEngine()
{
    ResetPlaybackEngine();

    if (m_pCommandsProcessCallback && m_pScheduler)
    {
        m_pCommandsProcessCallback->Cancel(m_pScheduler);
    }
    HX_RELEASE(m_pScheduler);
    HX_RELEASE(m_pCommandsProcessCallback);
    HX_RELEASE(m_pContext);
    if (m_pMediaPlatform)
    {
        HX_RELEASE(m_pMediaPlatform);
        HXMediaPlatformObj::ReleaseMediaPlatform();
    }
}

void PlayerDriver::WritePreference(const char* pName, const char* pValue)
{
    IHXBuffer* pBuffer = NULL;

    /*
    if (m_pPreferences)
    {
        if (HXR_OK == CreateAndSetBufferCCF(pBuffer, (UCHAR*)pValue,
                                     strlen(pValue) + 1, m_pContext))
        {
            m_pPreferences->WritePref(pName, pBuffer);
        }
    }
    */
    HX_RELEASE(pBuffer);
}

void PlayerDriver::SetConfig(const char* pPropName, UINT16 bValue)
{
    IHXCommonClassFactory* pCCF = NULL;
    m_pContext->QueryInterface(IID_IHXCommonClassFactory, (void**)&pCCF);
    if (pCCF)
    {
	IHXValues* pValues = NULL;
	pCCF->CreateInstance(CLSID_IHXValues, (void**)&pValues);
	if (pValues)
	{
	    pValues->SetPropertyULONG32(pPropName, bValue);
	    if (m_pClientState)
	    {
		m_pClientState->SetConfig(pValues);
	    }
	    HX_RELEASE(pValues);
	}
	HX_RELEASE(pCCF);
    }
}

bool PlayerDriver::IsTrackLooping()
{
    return m_bIsLooping;
}

HX_RESULT PlayerDriver::createThread(IHXThread** ppThread)
{
    HX_RESULT retVal = HXR_FAIL;
    IHXCommonClassFactory* pCCF = NULL;

    if ( m_pContext && ppThread )
        m_pContext->QueryInterface(IID_IHXCommonClassFactory, (void**)&pCCF);

    if (pCCF)
    {
        pCCF->CreateInstance(CLSID_IHXThread, (void**)ppThread);
        if ( *ppThread )
        {
            retVal= HXR_OK;
        }
        HX_RELEASE(pCCF);
    }
    return retVal;
}

}

#endif

