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

#ifndef _WEBKIT_ADVISE_SINK_
#define _WEBKIT_ADVISE_SINK_

#if ENABLE(VIDEO) && USE(GSTREAMER)
#include "hxwintyp.h"
#include "hxwin.h"
#include "clientcontext.h"

struct IHXClientAdviseSink;
struct IHXGroupSink;
struct IUnknown;
struct IHXRegistry;
struct IHXScheduler;
struct IHXCallback;
struct IHXPlayer;
struct IHXGroup;

namespace WebCore {

enum mediaPlayerState
{
        MEDIA_PLAYER_STATE_ERROR,
        MEDIA_PLAYER_IDLE,
        MEDIA_PLAYER_INITIALIZED,
        MEDIA_PLAYER_PREPARING,
        MEDIA_PLAYER_PREPARED,
        MEDIA_PLAYER_STARTED,
        MEDIA_PLAYER_PAUSED,
        MEDIA_PLAYER_STOPPED,
        MEDIA_PLAYER_PLAYBACK_COMPLETE
} ;

class WebkitClientAdviseSink : public IHXClientAdviseSink,
                                public IHXClientStateAdviseSink,
                                public IHXGroupSink
{
  public:

    WebkitClientAdviseSink(IUnknown* pUnknown, WebkitClientContext* pContext);

    /*
     *  IUnknown methods
     */
    STDMETHOD(QueryInterface)           (THIS_ REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG32,AddRef)          (THIS);
    STDMETHOD_(ULONG32,Release)         (THIS);

    /*
     *  IHXClientAdviseSink methods
     */
    STDMETHOD(OnPosLength)              (THIS_ UINT32 ulPosition, UINT32 ulLength);
    STDMETHOD(OnPresentationOpened)     (THIS);
    STDMETHOD(OnPresentationClosed)     (THIS);
    STDMETHOD(OnStatisticsChanged)      (THIS);
    STDMETHOD(OnPreSeek)                (THIS_ ULONG32 ulOldTime, ULONG32 ulNewTime);
    STDMETHOD(OnPostSeek)               (THIS_ ULONG32 ulOldTime, ULONG32 ulNewTime);
    STDMETHOD(OnStop)                   (THIS);
    STDMETHOD(OnPause)                  (THIS_ ULONG32 ulTime);
    STDMETHOD(OnBegin)                  (THIS_ ULONG32 ulTime);
    STDMETHOD(OnBuffering)              (THIS_ ULONG32 ulFlags, UINT16 unPercentComplete);
    STDMETHOD(OnContacting)             (THIS_ const char* pHostName);

    /*
     *  IHXClientStateAdviseSink methods
     */
    STDMETHOD(OnStateChange)            (THIS_ UINT16 uOldState, UINT16 uNewState);

    /*
     *  IHXGroupSink methods
     */
    STDMETHOD(GroupAdded)               (THIS_ UINT16 uGroupIndex, IHXGroup* pGroup);
    STDMETHOD(GroupRemoved)             (THIS_ UINT16 uGroupIndex, IHXGroup* pGroup);
    STDMETHOD(AllGroupsRemoved)         (THIS);
    STDMETHOD(TrackAdded)               (THIS_ UINT16 uGroupIndex, UINT16 uTrackIndex, IHXValues* pTrack);
    STDMETHOD(TrackRemoved)             (THIS_ UINT16 uGroupIndex, UINT16 uTrackIndex, IHXValues* pTrack);
    STDMETHOD(TrackStarted)             (THIS_ UINT16 uGroupIndex, UINT16 uTrackIndex, IHXValues* pTrack);
    STDMETHOD(TrackStopped)             (THIS_ UINT16 uGroupIndex, UINT16 uTrackIndex, IHXValues* pTrack);
    STDMETHOD(CurrentGroupSet)          (THIS_ UINT16 uGroupIndex, IHXGroup* pGroup);

    /*
     * IHXSiteWatcher methods
     */
    STDMETHOD(AttachSite)               (THIS_ IHXSite*	pSite);
    STDMETHOD(DetachSite)               (THIS);
    STDMETHOD(ChangingPosition)         (THIS_ HXxPoint posOld, REF(HXxPoint) /*IN-OUT*/ posNew);
    STDMETHOD(ChangingSize)             (THIS_ HXxSize sizeOld, REF(HXxSize) /*IN-OUT*/ sizeNew);

  private:
    ~WebkitClientAdviseSink();

    void                                GetClipInfo();
    void                                SendClipProperties(IHXValues* pHeader);
    void                                TranslateToWebkitState(UINT16 uState);
	
    LONG32                              m_lRefCount;
    IUnknown*                           m_pUnknown;
    IHXRegistry*                        m_pRegistry;
    IHXScheduler*                       m_pScheduler;
    UINT32                              m_ulStartTime;
    UINT32                              m_ulStopTime;
    INT32                               m_lDuration;
    UINT32                              m_ulFileDurationFromHeader;
    UINT32                              m_ulPos;
    UINT32                              m_ulWidth;
    UINT32                              m_ulHeight;
    HXBOOL                              m_bIsLiveOrAdaptiveHTTP;
    HXBOOL                              m_bOpened;
    HXBOOL                              m_bOnStop;
    HXBOOL                              m_bPrepared;
    HXBOOL                              m_bSendPlayBackComplete;
    IHXPlayer*                          m_pPlayer;
    WebkitClientContext*               m_pWebkitContext;
    int                                 m_playerState;
};

}
#endif
#endif /* _WEBKIT_ADVISE_SINK_ */
