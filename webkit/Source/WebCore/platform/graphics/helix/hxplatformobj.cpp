/* ***** BEGIN LICENSE BLOCK *****
 *
 * Portions Copyright (c) 1995-2004 RealNetworks, Inc. All Rights Reserved.
 *
 * The contents of this file, and the files included with this file,
 * are subject to the current version of the RealNetworks Public
 * Source License (the "RPSL") available at
 * http://www.helixcommunity.org/content/rpsl unless you have licensed
 * the file under the current version of the RealNetworks Community
 * Source License (the "RCSL") available at
 * http://www.helixcommunity.org/content/rcsl, in which case the RCSL
 * will apply. You may also obtain the license terms directly from
 * RealNetworks.  You may not use this file except in compliance with
 * the RPSL or, if you have a valid RCSL with RealNetworks applicable
 * to this file, the RCSL.  Please see the applicable RPSL or RCSL for
 * the rights, obligations and limitations governing use of the
 * contents of the file.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License Version 2 or later (the
 * "GPL") in which case the provisions of the GPL are applicable
 * instead of those above. If you wish to allow use of your version of
 * this file only under the terms of the GPL, and not to allow others
 * to use your version of this file under the terms of either the RPSL
 * or RCSL, indicate your decision by deleting the provisions above
 * and replace them with the notice and other provisions required by
 * the GPL. If you do not delete the provisions above, a recipient may
 * use your version of this file under the terms of any one of the
 * RPSL, the RCSL or the GPL.
 *
 * This file is part of the Helix DNA Technology. RealNetworks is the
 * developer of the Original Code and owns the copyrights in the
 * portions it created.
 *
 * This file, and the files included with this file, is distributed
 * and made available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS
 * ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET
 * ENJOYMENT OR NON-INFRINGEMENT.
 *
 * Technology Compatibility Kit Test Suite(s) Location:
 *    http://www.helixcommunity.org/content/tck
 *
 * Contributor(s):
 *
 * ***** END LICENSE BLOCK ***** */
#include "config.h"

#if ENABLE(VIDEO) && USE(GSTREAMER)
#include "hxcom.h"
#include "hxtypes.h"
#include "dllacces.h"
#include "dllpath.h"
#include "ihxmedpltfm.h"
#include "hxstring.h"
#include "hxthread.h"
#include "thrdutil.h"
#include "hxcbobj.h"
#include "hxplatformobj.h"
#include <stdio.h>

#define DEFAULT_LIB_PATH		"/home/collins/webkitTlc/helixlibs"
#define MAX_PATH			256
#define CLEANUP_CALLBACK_THRESHOLD	30000

namespace WebCore{

// static variables
HXMediaPlatformObj*	HXMediaPlatformObj::zm_pMediaPlatformObj = NULL;
GMutex			HXMediaPlatformObj::zm_Lock;
INT32			HXMediaPlatformObj::zm_lRefCount = 0;
HXBOOL		    HXMediaPlatformObj::m_DeletePrefFile = FALSE;

HXMediaPlatformObj::HXMediaPlatformObj()
    : m_fpHXMediaPlatformOpen(NULL)
    , m_fpHXCreateMediaPlatform(NULL)
    , m_fpHXMediaPlatformClose(NULL)
    , m_pDLLAccess(NULL)
    , m_pMediaPlatform(NULL)
    , m_pMediaPlatformKicker(NULL)
    , m_pScheduler(NULL)
    , m_pScheduler2(NULL)
    , m_pEngineThread(NULL)
    , m_pEvent(NULL)
    , m_bTerminatePending(FALSE)
    , m_pFinalReleaseCallback(NULL)
    , m_pSchedulerWakeupCallback(NULL)
    , m_LastError(HXR_OK)
{
    HXThread::MakeThread(m_pEngineThread);
    g_mutex_init(&zm_Lock);
    HXEvent::MakeEvent(m_pEvent, NULL, FALSE);
}

HXMediaPlatformObj::~HXMediaPlatformObj()
{
    zm_pMediaPlatformObj = NULL;
    HX_DELETE(m_pEvent);
    HX_DELETE(m_pEngineThread);
    if (m_DeletePrefFile)
    {
        //LOGI("The preference file deleted");
        m_DeletePrefFile = FALSE;
    }
    //LOGI("Helix Media platform finial release: done.");
    g_mutex_lock(&zm_Lock);
    g_mutex_clear(&zm_Lock);
}

// static methods
HX_RESULT HXMediaPlatformObj::CreateMediaPlatform(REF(IHXMediaPlatform*) pMediaPlatform)
{
    g_mutex_lock(&zm_Lock);

    HX_RESULT retVal = HXR_OK;
    
    // create singleton HXMediaPlatformObj
    if (!zm_pMediaPlatformObj)
    {
	zm_pMediaPlatformObj = new HXMediaPlatformObj();
	if (!zm_pMediaPlatformObj)
	{
	    retVal = HXR_FAIL;
	}
    }

    // get IHXMediaPlatform
    if (SUCCEEDED(retVal))
    {
	retVal = zm_pMediaPlatformObj->_CreateMediaPlatform(pMediaPlatform);
	if (FAILED(retVal))
	{
	    //LOGE("Can not load helix media platform.");
		printf("HelixOverWebkit [%s] [%s] [%d] Can not load helix media platform.\n", __FILE__, __FUNCTION__, __LINE__);
	}
	else
	{
	    zm_lRefCount++;
	}
    }
    
    g_mutex_unlock(&zm_Lock);

    return retVal;
}

void HXMediaPlatformObj::ReleaseMediaPlatform()
{
    g_mutex_lock(&zm_Lock);
    zm_lRefCount--;
    if (zm_lRefCount > 0)
    {
        g_mutex_unlock(&zm_Lock);
	return;
    }
    
    zm_pMediaPlatformObj->ScheduleShutdown();
    g_mutex_unlock(&zm_Lock);
    return;
}

void HXMediaPlatformObj::ResetMediaPlatformNoDelay()
{
    zm_lRefCount--;
    if (zm_lRefCount > 0)
    {
        return;
    }
    m_DeletePrefFile = TRUE;
    zm_pMediaPlatformObj->HandleFinalReleaseCallback();
}

void HXMediaPlatformObj::ScheduleShutdown()
{
    // schedule finial release
    if (m_pScheduler &&
	m_pFinalReleaseCallback && 
	!m_pFinalReleaseCallback->IsCallbackPending())
    {
	//LOGI("schedule media platform finial release");
	m_pFinalReleaseCallback->ScheduleRelative(m_pScheduler, CLEANUP_CALLBACK_THRESHOLD);
    }
}

HX_RESULT HXMediaPlatformObj::_CreateMediaPlatform(REF(IHXMediaPlatform*) pMediaPlatform)
{
    HX_RESULT retVal = HXR_OK;
    
    // cancel finial release callback
    if (m_pScheduler &&
	m_pFinalReleaseCallback && 
	m_pFinalReleaseCallback->IsCallbackPending())
    {
	printf("HelixOverWebkit [%s] [%s] [%d] media platform finial release canceled.\n", __FILE__, __FUNCTION__, __LINE__);
	m_pFinalReleaseCallback->Cancel(m_pScheduler);
    }

    if (!m_pMediaPlatform)
    {
	retVal = StartEngineThread();
    }
    
    if (retVal == HXR_OK)
    {
	HX_ADDREF(m_pMediaPlatform);
	pMediaPlatform = m_pMediaPlatform;
    }
    else
    {
	pMediaPlatform = NULL;
    }
    
    return retVal;
}

void HXMediaPlatformObj::FinalReleaseCallbackFunc(void* pParam)
{
    if (pParam)
    {
        HXMediaPlatformObj* pObj = (HXMediaPlatformObj*) pParam;
        pObj->HandleFinalReleaseCallback();
    }
}

void HXMediaPlatformObj::HandleFinalReleaseCallback(void)
{
    g_mutex_lock(&zm_Lock);
    if (zm_lRefCount == 0)
    {
	// go ahead with release
	m_bTerminatePending = TRUE;
        if (m_pScheduler &&
            m_pSchedulerWakeupCallback &&
            !m_pSchedulerWakeupCallback->IsCallbackPending())
        {
            m_pSchedulerWakeupCallback->ScheduleRelative(m_pScheduler, 5);
        }
    }
    else
    {
	// cancel release
	g_mutex_unlock(&zm_Lock);
	return;
    }
}

HX_RESULT HXMediaPlatformObj::StartEngineThread()
{
    if (!m_pEngineThread || !m_pEvent)
    {
	return HXR_FAIL;
    }
    
    m_pEngineThread->CreateThread(StaticThreadFunc, (void*)this, FALSE);
    m_pEngineThread->SetThreadName("Helix engine thread");
    m_pEvent->Wait();

    return m_LastError;
}

void* HXMediaPlatformObj::StaticThreadFunc(void* pData)
{
    HXMediaPlatformObj* pThis = (HXMediaPlatformObj*)pData;
    return pThis->EngineDriverThreadProc();
}

void* HXMediaPlatformObj::EngineDriverThreadProc()
{
    UINT32 ulMyThreadID = 0;
    UINT32 ulSleepTime = 0;

    ulMyThreadID = HXGetCurrentThreadID();
    m_LastError = SetupMediaPlatform();

    if (SUCCEEDED(m_LastError))
    {
        //LOGV("Helix Media platform created, thread_id = %u.", ulMyThreadID);
		printf("HelixOverWebkit [%s] [%s] [%d] Helix Media platform created, thread_id = %u.\n", __FILE__, __FUNCTION__, __LINE__, ulMyThreadID);
    }
    else
    {
        CleanupMediaPlatform();
        //LOGE("Create Helix Media platform failed.");
		printf("HelixOverWebkit [%s] [%s] [%d]\n Create Helix Media platform failed.", __FILE__, __FUNCTION__, __LINE__);
        return (void*)NULL;
    }

    m_pEvent->SignalEvent();

    m_pMediaPlatformKicker->StartOnDemandKick(ulMyThreadID);
    while(!m_bTerminatePending)
    {
        m_pMediaPlatformKicker->Kick2(ulMyThreadID, &ulSleepTime);
        if (ulSleepTime != 0)
        {
            m_pMediaPlatformKicker->Wait2(ulMyThreadID, ulSleepTime);
        }
    }

    CleanupMediaPlatform();
    delete this;

	printf("HelixOverWebkit [%s] [%s] [%d]\n", __FILE__, __FUNCTION__, __LINE__);
    return (void*)NULL;
}

HX_RESULT HXMediaPlatformObj::SetupMediaPlatform()
{
    HX_RESULT retVal = HXR_OK;

    // Get lib path from user env
    const char* pszHelixLibs	= getenv("HELIX_LIBS");
    const char* pszHelixPlugins	= getenv("HELIX_PLUGINS");
    const char* pszHelixCommon	= getenv("HELIX_COMMON");
    const char* pszHelixCodecs	= getenv("HELIX_CODECS");
    const char* pszHelixEncSDK	= getenv("HELIX_ENCSDK");

    // Fallback to default android helix lib location
    if (!pszHelixLibs)
    {
	pszHelixLibs = DEFAULT_LIB_PATH;
    }

    // Set the DLL Access paths for any DLLAccess-enabled plugins which are loaded
    GetDLLAccessPath()->SetPath(DLLTYPE_PLUGIN, pszHelixPlugins ? pszHelixPlugins : pszHelixLibs);
    GetDLLAccessPath()->SetPath(DLLTYPE_COMMON, pszHelixCommon ? pszHelixCommon : pszHelixLibs);
    GetDLLAccessPath()->SetPath(DLLTYPE_CODEC, pszHelixCodecs ? pszHelixCodecs : pszHelixLibs);
    GetDLLAccessPath()->SetPath(DLLTYPE_ENCSDK, pszHelixEncSDK ? pszHelixEncSDK : pszHelixLibs);

    // Set the full path for the media platform plugin
    CHXString strMediaPlatformLib = pszHelixLibs;
    UINT32 ulBufLen = MAX_PATH;
    char szMediaPlatformName[ulBufLen];
    DLLAccess::CreateName("hxmedpltfm", "hxmedpltfm", szMediaPlatformName, ulBufLen);
    strMediaPlatformLib = strMediaPlatformLib + '/' + szMediaPlatformName;

    // Allocate a DLLAccess object
    m_pDLLAccess = new DLLAccess();
    if (!m_pDLLAccess)
    {
        //LOGE("Could not allocate a DLLAccess object.");
	retVal = HXR_FAIL;
    }

    // Try to load the media platform plugin.
    if (SUCCEEDED(retVal))
    {
	if (m_pDLLAccess->open((const char*)strMediaPlatformLib) != DLLAccess::DLL_OK)
	{
	    //LOGE("Could not open %s (the media platform shared library)", pszHelixLibs);
	    retVal = HXR_FAIL;
	}
    }

    // Get the media platform entrypoints
    if (SUCCEEDED(retVal))
    {
	m_fpHXMediaPlatformOpen   = (FPHXMEDIAPLATFORMOPEN)   m_pDLLAccess->getSymbol("HXMediaPlatformOpen");
	m_fpHXCreateMediaPlatform = (FPHXCREATEMEDIAPLATFORM) m_pDLLAccess->getSymbol("HXCreateMediaPlatform");
	m_fpHXMediaPlatformClose  = (FPHXMEDIAPLATFORMCLOSE)  m_pDLLAccess->getSymbol("HXMediaPlatformClose");
	if (m_fpHXMediaPlatformOpen   == NULL ||
	    m_fpHXCreateMediaPlatform == NULL ||
	    m_fpHXMediaPlatformClose  == NULL)
	{
	    //LOGE("Could not get media platform entrypoints.");
	    retVal = HXR_FAIL;
	}
    }

    // Open media platform
    if (SUCCEEDED(retVal))
    {
	retVal = m_fpHXMediaPlatformOpen();
	if (FAILED(retVal))
	{
	    //LOGE("HXMediaPlatformOpen failed.");
	}
    }

    // Create a media platform object
    if (SUCCEEDED(retVal))
    {
	retVal = m_fpHXCreateMediaPlatform(&m_pMediaPlatform);
	if (FAILED(retVal))
	{
	    //LOGE("HXCreateMediaPlatform failed.");
	}
    }

    // Must add plugin path for creating engine to work
    if (SUCCEEDED(retVal))
    {
	//LOGD("m_pMediaPlatform->AddPluginPath() path=%s.", pszHelixLibs);
        retVal = m_pMediaPlatform->AddPluginPath("HelixMediaPlayer", pszHelixLibs);
        if (FAILED(retVal))
        {
            //LOGE("m_pMediaPlatform->AddPluginPath() failed.");
        }
    }

    // Init the media platform
    if (SUCCEEDED(retVal))
    {
	retVal = m_pMediaPlatform->Init(NULL);
	if (FAILED(retVal))
	{
	    //LOGE("IHXMediaPlatform::Init() failed.");
	}
    }

    // Get media platform kicker
    if (SUCCEEDED(retVal))
    {
        retVal = m_pMediaPlatform->QueryInterface(IID_IHXMediaPlatformKicker2, (void**) &m_pMediaPlatformKicker);
        if (FAILED(retVal))
        {
            //LOGE("QueryInterface for IHXMediaPlatformKicker failed.");
        }
    }

    // Obtain platform scheduler's scheduler2 API
    if (SUCCEEDED(retVal))
    {
	retVal = m_pMediaPlatform->QueryInterface(IID_IHXScheduler2, (void**) &m_pScheduler2);
        if (FAILED(retVal))
        {
            //LOGE("QueryInterface for IID_IHXScheduler2 failed.");
        }
    }

    // Obtain platform scheduler's scheduler API
    if (SUCCEEDED(retVal))
    {
	retVal = m_pMediaPlatform->QueryInterface(IID_IHXScheduler, (void**) &m_pScheduler);
        if (FAILED(retVal))
        {
            //LOGE("QueryInterface for IID_IHXScheduler failed.");
        }
    }

    // Create release callback
    if (SUCCEEDED(retVal))
    {
	m_pFinalReleaseCallback = new CHXGenericCallback((void*) this, FinalReleaseCallbackFunc);
	if (m_pFinalReleaseCallback)
	{
	    m_pFinalReleaseCallback->AddRef();
	}
	else
	{
	    //LOGE("Create release callback failed.");
	    retVal = HXR_FAIL;
	}

        m_pSchedulerWakeupCallback = new CHXGenericCallback((void*)this, SchedulerWakeupCallbackFunc);
	if (m_pSchedulerWakeupCallback)
	{
	    m_pSchedulerWakeupCallback->AddRef();
	}
	else
	{
	    //LOGE("Create wakeup callback failed.");
	    retVal = HXR_FAIL;
	}
    }

    if (FAILED(retVal))
    {
        CleanupMediaPlatform();
    }

    return retVal;
}

void HXMediaPlatformObj::CleanupMediaPlatform()
{
    HX_RELEASE(m_pFinalReleaseCallback);
    HX_RELEASE(m_pSchedulerWakeupCallback);
    HX_RELEASE(m_pScheduler);
    HX_RELEASE(m_pScheduler2);
    HX_RELEASE(m_pMediaPlatformKicker);

    if (m_pMediaPlatform)
    {
        m_pMediaPlatform->Close();
        HX_RELEASE(m_pMediaPlatform);
    }

    if (m_fpHXMediaPlatformClose)
    {
        m_fpHXMediaPlatformClose();
	m_fpHXMediaPlatformClose = NULL;
    }

    if (m_pDLLAccess)
    {
        m_pDLLAccess->close();
        HX_DELETE(m_pDLLAccess);
    }
}

}/*namespace WebCore*/

#endif

