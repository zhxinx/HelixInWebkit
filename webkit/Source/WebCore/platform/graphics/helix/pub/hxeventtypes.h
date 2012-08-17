/* ***** BEGIN LICENSE BLOCK *****
 * 
 * Portions Copyright (c) 1995-2008 RealNetworks, Inc. All Rights Reserved.
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
 * terms of the GNU General Public License Version 2 (the
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


#ifndef _HXEVENTTYPES_H_
#define _HXEVENTTYPES_H_

typedef enum _HXPlayerEvent
{
    HXPlayerEvent_PlayStateChanged = 0,                 // pParam1(RPPlayState) - Old state, pParam2(RPPlayState) - New state
    HXPlayerEvent_DurationChanged,                      // pParam1(UINT32) - New duration, pParam2(NULL)
    HXPlayerEvent_PositionChanged,                      // pParam1(UINT32) - New Position, pParam2(NULL)
    HXPlayerEvent_BufferingProgress,                    // pParam1(UINT32) - Buffering percent, pParam2(RPBufferingReason) - Buffering reason
    HXPlayerEvent_VideoWindowEvent,                     // pParam1(HXxEvent*) - Event information, pParam2(NULL)
    HXPlayerEvent_VideoStateChanged,                    // pParam1(BOOL) - TRUE if video is present otherwise FALSE, pParam2(NULL)
    HXPlayerEvent_AudioVolumeChanged,                   // pParam1(UINT32) - volume, pParam2(NULL)
    HXPlayerEvent_AudioMuteChanged,                     // pParam1(BOOL) - muted, pParam2(NULL)
    HXPlayerEvent_ErrorOccurred,                        // pParam1(RPErrorInfo*) - Detailed error information, pParam2(NULL)
    HXPlayerEvent_StatisticsChanged,                    // pParam1(IRPStatistics*) - Detailed statistics, pParam2(NULL)
    HXPlayerEvent_FullScreenChanged,                    // pParam1(BOOL) - TRUE = EnterFullScreen, FALSE = ExitFullScreen, pParam2(HX_RESULT) - status
    HXPlayerEvent_CachedPlayStateChanged,               // pParam1(BOOL) - TRUE = CachedPlayStarted FALSE = CachedPlayEnded
    HXPlayerEvent_CachedPlayProgress,                   // pParam1(UINT32) - ulMin, pParam2(UINT32) - ulMax
    HXPlayerEvent_MediaPropertyStringAdded,             // pParam1(const char*) - PropertyName, pParam2(const char*) - NewPropertyValue
    HXPlayerEvent_MediaPropertyStringChanged,           // pParam1(const char*) - PropertyName, pParam2(const char*) - NewPropertyValue
    HXPlayerEvent_MediaPropertyStringRemoved,           // pParam1(const char*) - PropertyName, pParam2(const char*) - CurrentPropertyValue
    HXPlayerEvent_MediaItemChanged,                     // pParam1(IRPMediaItem*) - RPMediaItem, pParam2(NULL)
    HXPlayerEvent_PlaylistChanged,                      // pParam1(IRPPlaylist*) - RPPlaylist, pParam2(NULL)
    HXPlayerEvent_PlaylistUpdateCurrentMediaItem,       // pParam1(const char*) - URL, pParam2(const char*) - MediaItem ID
    HXPlayerEvent_PlaylistAddMediaItem,                 // pParam1(const char*) - URL, pParam2(const char*) - MediaItem ID
    HXPlayerEvent_PlaylistCurrentMediaItemChanged,      // pParam1(const char*) - current MediaItem ID  
    HXPlayerEvent_EmbeddedUIReady,                      // pParam1(EmbeddedUIInfo*)  - embedded ui stuff, drm ptr
    HXPlayerEvent_EmbeddedUIDataReady,                  // pParam1(IHXValues*)  - embedded ui data collection
    HXPlayerEvent_HyperNavigate,                        // pParam1(const char*) - URL, pParam2(const char*) - target
    HXPlayerEvent_PlayAttempted,                        // pParam1(RPPlayState) -- current state, pParam2(NULL)
    HXPlayerEvent_AutoUpgradeNeeded			// pParam1(IHXUpgradeCollection*) missing component collection
    // After you added new HXPlayerEvent, please remember to add
    // DEFINE_EVENT_RCVR_METHOD and IMPLEMENT_EVENT_RCVR_METHOD in
    // client/common/system/pub/chxplayerevent.h and
    // client/common/system/chxplayerevent.cpp
}
HXPlayerEvent;

typedef enum _HXUIControlEvent
{
    // General control events
    HXUIControlEvent_Clicked = 0,                       // Param1(RPPluginUIControlId), Param2(NULL)
    HXUIControlEvent_Toggled,                           // Param1(RPPluginUIControlId), Param2(BOOL) - TRUE if the button is toggled on FALSE if it is off
    HXUIControlEvent_Layout,			        // Param1(RPPluginUIControlId), Param2(NULL) - Layout requested by the control
    HXUIControlEvent_DamageRect,			// Param1(RPPluginUIControlId), Param2(HXxRect*) - Control requesting GUI update (in sub-rect if HXxRect* != NULL)
    HXUIControlEvent_DistributeSysEvent,		// Param1(RPPluginUIControlId), Param2(HXxEvent*) - Control requesting distribution of a system event

    // Range control events
    HXUIControlEvent_BeginRangeValueChange,             // Param1(RPPluginUIControlId), Param2(double*) - Value indicating the current position within a range
    HXUIControlEvent_RangeValueChange,                  // Param1(RPPluginUIControlId), Param2(double*) - Value indicating the current position within a range
    HXUIControlEvent_EndRangeValueChange,               // Param1(RPPluginUIControlId), Param2(double*) - Value indicating the current position within a range

    // Video window control events
    HXUIControlEvent_SetVideoWindowPosition,            // Param1(RPPluginUIControlId), Param2(HXxRect*) - rect of the video window

    // After you added new HXUIControlEvent, please remember to add
    // DEFINE_EVENT_RCVR_METHOD and IMPLEMENT_EVENT_RCVR_METHOD in
    // client_rn/common/system/pub/chxuicontrolevent.h and
    // client_rn/common/system/chxuicontrolevent.cpp
}
HXUIControlEvent;

typedef enum _HXUIGenericEvent
{
    // Set URL events, used for setting the URL from within the controls UI
    HXUIGenericEvent_OpenURL,                           // Param1(const char*) - content URL sent to CRPPlayerBaseObj
    HXUIGenericEvent_HyperNavigate,                     // Param1(const char*) - URL to open, Param2(const char*) - target frame
    HXUIGenericEvent_StopInPrefetched,                  // Param1(HXBOOL), Param2(NULL) - Pause playback in prefetched mode
    HXUIGenericEvent_PlaybackCtlMode,                   // Param1(UINT32) - playback control mode
    HXUIGenericEvent_RedrawVideoWindow,                 // Param1(BOOL*) - Value indicating whether the video window should redraw itself
    HXUIGenericEvent_ErrorOccurred,                     // Param1(RPErrorInfo*) - Error info
    HXUIGenericEvent_AutoUpgradeNeeded,			// pParam1(IHXUpgradeCollection*) missing component collection
    HXUIGenericEvent_UIReady

    // After you added new HXUIGenericEvent, please remember to add
    // DEFINE_EVENT_RCVR_METHOD and IMPLEMENT_EVENT_RCVR_METHOD in
    // client_rn/common/system/pub/chxuigenericevent.h and
    // client_rn/common/system/chxuigenericevent.cpp
}
HXUIGenericEvent;

#endif /* _HXEVENTTYPES_H_ */
