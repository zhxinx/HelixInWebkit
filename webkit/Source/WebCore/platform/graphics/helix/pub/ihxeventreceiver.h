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


#ifndef _IHXEVENTRECEIVER_H_
#define _IHXEVENTRECEIVER_H_

#include "hxcom.h"
#include "hxeventtypes.h"

// IID_IHXEventReceiver                         {00000100-6A98-42c9-9ABD-CB7F5C07155B}
// IID_IHXPlayerEventReceiver                   {00000101-6A98-42c9-9ABD-CB7F5C07155B}
// IID_IHXUIControlEventReceiver                {00000102-6A98-42c9-9ABD-CB7F5C07155B}
// IID_IHXUIGenericEventReceiver                {FB557DA8-B3EF-4f40-905F-FC4F7944FC04}
DEFINE_GUID(IID_IHXEventReceiver,               0x00000100, 0x6a98, 0x42c9, 0x9a, 0xbd, 0xcb, 0x7f, 0x5c, 0x7, 0x15, 0x5b);
DEFINE_GUID(IID_IHXPlayerEventReceiver,         0x00000101, 0x6a98, 0x42c9, 0x9a, 0xbd, 0xcb, 0x7f, 0x5c, 0x7, 0x15, 0x5b);
DEFINE_GUID(IID_IHXUIControlEventReceiver,      0x00000102, 0x6a98, 0x42c9, 0x9a, 0xbd, 0xcb, 0x7f, 0x5c, 0x7, 0x15, 0x5b);
DEFINE_GUID(IID_IHXUIGenericEventReceiver,      0xfb557da8, 0xb3ef, 0x4f40, 0x90, 0x5f, 0xfc, 0x4f, 0x79, 0x44, 0xfc, 0x4);

#undef INTERFACE
#define INTERFACE IHXEventReceiver

DECLARE_INTERFACE_(IHXEventReceiver, IUnknown)
{
};

#undef INTERFACE
#define INTERFACE IHXPlayerEventReceiver

DECLARE_INTERFACE_(IHXPlayerEventReceiver, IHXEventReceiver)
{
    STDMETHOD(OnEvent)  (THIS_ HXPlayerEvent event, void* pParam1, void* pParam2) PURE;
};

#undef INTERFACE
#define INTERFACE IHXUIControlEventReceiver

DECLARE_INTERFACE_(IHXUIControlEventReceiver, IHXEventReceiver)
{
    STDMETHOD(OnEvent)  (THIS_ HXUIControlEvent event, void* pParam1, void* pParam2) PURE;
};

#undef INTERFACE
#define INTERFACE IHXUIGenericEventReceiver

DECLARE_INTERFACE_(IHXUIGenericEventReceiver, IHXEventReceiver)
{
    STDMETHOD(OnEvent)  (THIS_ HXUIGenericEvent event, void* pParam1, void* pParam2) PURE;
};

#include "hxcomptr.h"
DEFINE_SMART_PTR(IHXEventReceiver)
DEFINE_SMART_PTR(IHXPlayerEventReceiver)
DEFINE_SMART_PTR(IHXUIControlEventReceiver)
DEFINE_SMART_PTR(IHXUIGenericEventReceiver)

#endif /* _IHXEVENTRECEIVER_H_ */
