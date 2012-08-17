/*
 * PlayerDriver.h
 *
 *  Created on: Jul 31, 2012
 *      Author: collins
 */

#ifndef PLAYERDRIVER_H_
#define PLAYERDRIVER_H_

#if ENABLE(VIDEO) && USE(GSTREAMER)

#include <wtf/SinglyLinkedList.h>
#include <wtf/PassOwnPtr.h>
#include <wtf/Threading.h>

#include "config.h"
#include "hxtypes.h"
#include "ihxmedpltfm.h"
#include "hxcom.h"
#include "hxcomm.h"
#include "hxcore.h"
#include "hxclsnk.h"
#include "hxerror.h"
#include "hxprefs.h"
#include "hxstrutl.h"
#include "dllpath.h"
#include "dllacces.h"
#include <hxcbobj.h>
#include <hxthread.h>

#include "clientcontext.h"

namespace WebCore {

class MediaPlayerPrivateHelix;
typedef int status_t;
#define UNKNOWN_ERROR -1
#define NO_ERROR 0
#define OK 0

#define FINISH_RESTART_TO_PREFETCH 1
//#define MEDIA_PLAYER_IDLE 2

typedef void (*media_completion_f)(status_t status, void *cookie);
// Commands that MediaPlayer sends to the HelixPlayer
class PlayerCommand
{
public:
    enum player_command_type
    {
        PLAYER_QUIT                     = 1,
        PLAYER_SET_DATA_SOURCE          ,
        PLAYER_INIT                     ,
        PLAYER_PREPARE                  ,
        PLAYER_START                    ,
        PLAYER_STOP                     ,
        PLAYER_PAUSE                    ,
        PLAYER_RESET                    ,
        PLAYER_SET_LOOP                 ,
        PLAYER_SEEK                     ,
        PLAYER_GET_POSITION             ,
        PLAYER_GET_DURATION             ,
        PLAYER_GET_STATUS               ,
        PLAYER_GET_TRACK_INFO_SIZE      ,
        PLAYER_GET_ALLTRACK_INFO        ,
        PLAYER_GET_CURTRACK_ID          ,
        PLAYER_SET_CURTRACK_ID          ,
        PLAYER_SET_VELOCITY             ,
        PLAYER_GET_VELOCITY             ,
    };

    virtual             ~PlayerCommand() {}
    int                 command() { return mCommand; }
    media_completion_f  callback() { return mCallback; }
    void*               cookie() { return mCookie; }
    bool                hasCompletionHook() { return mCallback == 0; }
    void                complete(status_t status) { mCallback(status, mCookie); }
    void set(media_completion_f cbf, void* cookie) { mCallback = cbf; mCookie = cookie; }
    void setNext(PlayerCommand* next) {mNext = next;}
    PlayerCommand* next() {return mNext;}
protected:
                        PlayerCommand(player_command_type command, media_completion_f cbf, void* cookie) :
                            mCommand(command), mCallback(cbf), mCookie(cookie), mNext(NULL) {}
private:
                        PlayerCommand();
    int                 mCommand;
    media_completion_f  mCallback;
    void*               mCookie;
    PlayerCommand*		mNext;
};

class PlayerQuit : public PlayerCommand
{
public:
                        PlayerQuit(media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_QUIT, cbf, cookie) {}
private:
                        PlayerQuit();
};

class PlayerInit : public PlayerCommand
{
public:
                        PlayerInit(media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_INIT, cbf, cookie) {}
private:
                        PlayerInit();
};

class PlayerPrepare: public PlayerCommand
{
public:
                        PlayerPrepare(media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_PREPARE, cbf, cookie) {}
private:
                        PlayerPrepare();
};

class PlayerStart: public PlayerCommand
{
public:
                        PlayerStart(media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_START, cbf, cookie) {}
private:
                        PlayerStart();
};

class PlayerStop: public PlayerCommand
{
public:
                        PlayerStop(media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_STOP, cbf, cookie) {}
private:
                        PlayerStop();
};

class PlayerPause: public PlayerCommand
{
public:
                        PlayerPause(media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_PAUSE, cbf, cookie) {}
private:
                        PlayerPause();
};

class PlayerReset: public PlayerCommand
{
public:
                        PlayerReset(media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_RESET, cbf, cookie) {}
private:
                        PlayerReset();
};

class PlayerSetDataSource : public PlayerCommand
{
public:
                        PlayerSetDataSource(const char* url, media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_SET_DATA_SOURCE, cbf, cookie), mUrl(0) {
                                if (url) mUrl = strdup(url); }
                        ~PlayerSetDataSource() { if (mUrl) free(mUrl); }
    const char*         url() const { return mUrl; }
private:
                        PlayerSetDataSource();
    char*               mUrl;
};

class PlayerSetLoop: public PlayerCommand
{
public:
                        PlayerSetLoop(int loop, media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_SET_LOOP, cbf, cookie), mLoop(loop) {}
                        int loop() { return mLoop; }
private:
                        PlayerSetLoop();
    int                 mLoop;
};

class PlayerSeek : public PlayerCommand
{
public:
                        PlayerSeek(int msec, media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_SEEK, cbf, cookie), mMsec(msec) {}
    int                 msec() { return mMsec; }
private:
                        PlayerSeek();
    int                 mMsec;
};

class PlayerGetPosition: public PlayerCommand
{
public:
                        PlayerGetPosition(int* msec, media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_GET_POSITION, cbf, cookie), mMsec(msec) {}
                        void set(int msecs) { if (mMsec) *mMsec = msecs; }
private:
                        PlayerGetPosition();
    int*                mMsec;
};

class PlayerGetDuration: public PlayerCommand
{
public:
                        PlayerGetDuration(int* msec, media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_GET_DURATION, cbf, cookie), mMsec(msec) {}
                        void set(int msecs) { if (mMsec) *mMsec = msecs; }
private:
                        PlayerGetDuration();
    int*                mMsec;
};

class PlayerGetStatus: public PlayerCommand
{
public:
                        PlayerGetStatus(int *status, media_completion_f cbf, void* cookie) :
                            PlayerCommand(PLAYER_GET_STATUS, cbf, cookie), mStatus(status) {}
                        void set(int status) { *mStatus = status; }
private:
                        PlayerGetStatus();
    int*                mStatus;
};

class PlayerDriver
{
public:
    PlayerDriver( MediaPlayerPrivateHelix* pPlayer);
    ~PlayerDriver();

    PlayerCommand*              dequeueCommand();
    status_t                    enqueueCommand(PlayerCommand* command);
    void                        SetConfig(const char* pPropName, UINT16 bValue);
    void			setErrorPending(bool b);
    bool			getErrorPending();

    HX_RESULT                   SetupPlaybackEngine();
#ifdef HELIX_FEATURE_SIMPLE_CORE
    HX_RESULT                   SelectClientEngine(bool bRealTime, const char* url, int fd = -1);
#endif
    void                        WritePreference(const char* pName, const char* pValue);
    // Handlers for the various commands we can accept.
    void                        commandCompleted(PlayerCommand* ec);
    status_t                    handleSetDataSource(PlayerSetDataSource* ec);
    status_t                    handlePrepare(PlayerPrepare* ec);
    status_t                    handleStart(PlayerStart* ec);
    status_t                    handleStop(PlayerStop* ec);
    status_t                    handlePause(PlayerPause* ec);
    status_t                    handleSeek(PlayerSeek* ec);
    status_t                    handleReset(PlayerReset* ec);

    status_t                    handleQuit(PlayerQuit* ec);
    status_t                    handleGetPosition(PlayerGetPosition* ec);
    bool                        IsTrackLooping();
    status_t                    initCheck() { return m_Init; }
    void                        setLooping( int isLooping );
    HX_RESULT                   createThread( IHXThread** ppThread);
    bool                        initMsgSender();
    void                        closeMsgSender();
    static void *               notifyCaller(void * pParam);
    bool                        IsSeekDelayed(){return m_bSeekDelayed;}
    int                         getDelaySeekPos(){return m_nSeekDelayedPosition;}
    bool                        m_bIsPlayingWhenSuspend;
    UINT32                      m_PositionWhenSuspend;
    bool                        m_bEnableSendEvent;
    IHXThread*                  m_pMsgSender;
    bool                        IsLive() {return m_pHXPlayer->IsLive();}
    bool                        IsRTSPLive()
    {
        if ( IsLive() )
        {
            const char RTSP_PREFIX[] = "rtsp://";
            if ( 0 == strncmp(RTSP_PREFIX, m_pDataSourcePath, sizeof(RTSP_PREFIX)-1) )
            {
                return true;
            }
        }
        return false;
    }
    bool                        m_bRestart;
    bool                        m_bUnseekable;

private:

    void                        commandCompleted(PlayerCommand* ec, status_t status);

    // Callback for synchronous commands.
    static void                 syncCompletion(status_t s, void *cookie);

    MediaPlayerPrivateHelix*    m_pMediaPlayer;
    status_t                    m_SyncStatus;
    bool                        m_bIsLooping;
    bool                        m_bDoLoop;
    bool                        m_bDataReadyReceived;
    bool                        m_bEndOfData;
    int                         m_nRecentSeek;
    bool                        m_bSeekComp;
    bool                        m_bSeekPending;
    bool                        m_bErrorPending;
    char*                       m_pDataSourcePath;
    status_t                    m_Init;
    int                         m_VideoWidth;
    int                         m_VideoHeight;
    bool                        m_bSeekDelayed;
    int                         m_nSeekDelayedPosition;
    // Command queue and its lock.
    SinglyLinkedList<PlayerCommand>        m_CommandQueue;
    Mutex                       m_QueueLock;

    IHXPlayer*                  m_pHXPlayer;
    IHXClientEngine*		m_pClientEngine;
    WebkitClientContext*       m_pWebkitContext;

    IHXClientState*             m_pClientState;

    IUnknown*                   m_pContext;
    IHXMediaPlatform*           m_pMediaPlatform;
    IHXScheduler*               m_pScheduler;
    IHXPreferences*             m_pPreferences;
    // helix thread
    HXEvent*                    m_pEvent;

    HX_RESULT                   m_LastError;

    // CHXAudioDevice*             m_pAudioDevice;

    // Callback function to process MediaPlayer comand on engine thread
    CHXGenericCallback*		m_pCommandsProcessCallback;
    static void			CommandsProcessCallbackFunc(void* pParam);
    void			HandleCommandsProcessCallback(void);
    PlayerCommand*              DoProcessQueue(status_t& returnStatus);

    void                        ResetPlaybackEngine();
    void                        CleanupPlaybackEngine();
};

}
#endif
#endif /* PLAYERDRIVER_H_ */

