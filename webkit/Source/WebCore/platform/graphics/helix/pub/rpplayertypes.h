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

#ifndef _RPPLAYERTYPES_H_
#define _RPPLAYERTYPES_H_

#include "hxresult.h"

DEFINE_CONSTANT_STRING(kPlayStateText_Stopped, "Stopped");
DEFINE_CONSTANT_STRING(kPlayStateText_Paused, "Paused");
DEFINE_CONSTANT_STRING(kPlayStateText_Playing, "Playing");
DEFINE_CONSTANT_STRING(kPlayStateText_Buffering, "Buffering");
DEFINE_CONSTANT_STRING(kPlayStateText_Seeking, "Seeking");
DEFINE_CONSTANT_STRING(kPlayStateText_Connecting, "Connecting");
DEFINE_CONSTANT_STRING(kPlayStateText_Opening, "Opening");

typedef enum _RPPlayState
{
    PlayState_Stopped = 0,
    PlayState_Paused,
    PlayState_Playing,
    PlayState_Buffering,
    PlayState_Seeking,
    PlayState_Connecting,
    PlayState_Opening
}
RPPlayState;

typedef enum _RPBufferingReason
{
    BufferingReason_Unknown = -1,
    BufferingReason_Initial = 0,
    BufferingReason_Seek,
    BufferingReason_Congestion,
    BufferingReason_LivePause
}
RPBufferingReason;

typedef enum _RPAspectRatioMode
{
    AspectRatioMode_PreserveRatio = 0,
    AspectRatioMode_Stretch,
    AspectRatioMode_Center
}
RPAspectRatioMode;

typedef struct _RPErrorInfo
{
    UINT32          ulSeverity;     // Defined in common/include/hxerror.h
    HX_RESULT       ulHXResult;     // Defined in common/include/hxresult.h
    UINT32          ulUserCode;     // User defined at the point the error occured.  For display or logging only since this value has no meaning for the receiver.
    const char*     pUserString;    // User defined at the point the error occured.  For display or logging only since this value has no meaning for the receiver.
    const char*     pMoreInfoURL;   // User defined at the point the error occured.  For display or logging only since this value has no meaning for the receiver.
}
RPErrorInfo;

// Playback Control Mode value
const UINT32 kPlaybackCtlMode_DEFAULT   = 0x000F;
const UINT32 kPlaybackCtlMode_PLAY      = 0x00000001;
const UINT32 kPlaybackCtlMode_PAUSE     = 0x00000002;
const UINT32 kPlaybackCtlMode_SEEK      = 0x00000004;
const UINT32 kPlaybackCtlMode_STOP      = 0x00000008;
// please update kPlaybackCtlMode_ALLON above if new playback
// control mode is added

// Playback Mode value
const UINT32 kPlaybackMode_Shuffle      = 0x00000001;
const UINT32 kPlaybackMode_Loop         = 0x00000002;

#endif /* _RPPLAYERTYPES_H_ */

