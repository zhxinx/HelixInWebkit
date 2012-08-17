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

#ifndef _HX_PLATFORM_OBJECT_
#define _HX_PLATFORM_OBJECT_

#if ENABLE(VIDEO) && USE(GSTREAMER)

//#include <wtf/Threading.h>
#include <glib.h>

#include "config.h"
#include <hxthread.h>
#include <hxcbobj.h>

namespace WebCore{

class HXMediaPlatformObj
{
public:
    HXMediaPlatformObj();
    ~HXMediaPlatformObj();

    static HX_RESULT		CreateMediaPlatform(REF(IHXMediaPlatform*) pMediaPlatform);
    static void			ReleaseMediaPlatform();
    static void			ResetMediaPlatformNoDelay();
    static HXMediaPlatformObj*	zm_pMediaPlatformObj;
    static INT32		zm_lRefCount;
    static GMutex		zm_Lock;
    static HXBOOL			m_DeletePrefFile;

    void			ScheduleShutdown();
private:
    HX_RESULT			_CreateMediaPlatform(REF(IHXMediaPlatform*) pMediaPlatform);

    // entrypoints
    FPHXMEDIAPLATFORMOPEN	m_fpHXMediaPlatformOpen;
    FPHXCREATEMEDIAPLATFORM	m_fpHXCreateMediaPlatform;
    FPHXMEDIAPLATFORMCLOSE	m_fpHXMediaPlatformClose;
    DLLAccess*                  m_pDLLAccess;

    // media platform
    IHXMediaPlatform*		m_pMediaPlatform;
    IHXMediaPlatformKicker2*    m_pMediaPlatformKicker;
    IHXScheduler2*              m_pScheduler2;
    IHXScheduler*               m_pScheduler;

    // helix thread and event
    HXThread*                   m_pEngineThread;
    HXEvent*                    m_pEvent;

    HXBOOL			m_bTerminatePending;
    HX_RESULT			m_LastError;

    HX_RESULT			SetupMediaPlatform();
    void			CleanupMediaPlatform();

    // thread functions
    static void*                StaticThreadFunc(void* pData);
    void*                       EngineDriverThreadProc();
    HX_RESULT			StartEngineThread();

    CHXGenericCallback*		m_pFinalReleaseCallback;
    CHXGenericCallback*		m_pSchedulerWakeupCallback;
    static void			FinalReleaseCallbackFunc(void* pParam);
    static void			SchedulerWakeupCallbackFunc(void* pParam) {};
    void			HandleFinalReleaseCallback(void);
};

}
#endif
#endif // _HX_PLATFORM_OBJECT_
