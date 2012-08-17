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


#ifndef _IHXEVENTSENDER_H_
#define _IHXEVENTSENDER_H_

#include "hxcom.h"

typedef _INTERFACE IHXEventReceiver             IHXEventReceiver;
typedef _INTERFACE IHXPlayerEventReceiver       IHXPlayerEventReceiver;
typedef _INTERFACE IHXUIControlEventReceiver    IHXUIControlEventReceiver;
typedef _INTERFACE IHXUIGenericEventReceiver    IHXUIGenericEventReceiver;

// IID_IHXEventSender                       {00000100-DCC3-4adb-9BB5-D20BF028E5ED}
// IID_IHXPlayerEventReceiver               {00000101-DCC3-4adb-9BB5-D20BF028E5ED}
// IID_IHXControlEventReceiver              {00000102-DCC3-4adb-9BB5-D20BF028E5ED}
// IID_IHXGenericEventReceiver              {AC5A0A2C-4189-40d9-9486-2B572CB6FDE7}
DEFINE_GUID(IID_IHXEventSender,             0x00000100, 0xdcc3, 0x4adb, 0x9b, 0xb5, 0xd2, 0xb, 0xf0, 0x28, 0xe5, 0xed);
DEFINE_GUID(IID_IHXPlayerEventSender,       0x00000101, 0xdcc3, 0x4adb, 0x9b, 0xb5, 0xd2, 0xb, 0xf0, 0x28, 0xe5, 0xed);
DEFINE_GUID(IID_IHXUIControlEventSender,    0x00000102, 0xdcc3, 0x4adb, 0x9b, 0xb5, 0xd2, 0xb, 0xf0, 0x28, 0xe5, 0xed);
DEFINE_GUID(IID_IHXUIGenericEventSender,    0xac5a0a2c, 0x4189, 0x40d9, 0x94, 0x86, 0x2b, 0x57, 0x2c, 0xb6, 0xfd, 0xe7);

#undef INTERFACE
#define INTERFACE IHXEventSender

DECLARE_INTERFACE_(IHXEventSender, IUnknown)
{
    STDMETHOD(SendEvent)                    (THIS_ void* eEvent, void* pParam1, void* pParam2) PURE;
};

#undef INTERFACE
#define INTERFACE IHXPlayerEventSender

DECLARE_INTERFACE_(IHXPlayerEventSender, IUnknown)
{
    STDMETHOD(AddReceiver)                  (THIS_ IHXPlayerEventReceiver* pReceiver) PURE;
    STDMETHOD(RemoveReceiver)               (THIS_ IHXPlayerEventReceiver* pReceiver) PURE;
};

#undef INTERFACE
#define INTERFACE IHXUIControlEventSender

DECLARE_INTERFACE_(IHXUIControlEventSender, IUnknown)
{
    STDMETHOD(AddReceiver)                  (THIS_ IHXUIControlEventReceiver* pReceiver) PURE;
    STDMETHOD(RemoveReceiver)               (THIS_ IHXUIControlEventReceiver* pReceiver) PURE;
};

#undef INTERFACE
#define INTERFACE IHXUIGenericEventSender

DECLARE_INTERFACE_(IHXUIGenericEventSender, IUnknown)
{
    STDMETHOD(AddReceiver)                  (THIS_ IHXUIGenericEventReceiver* pReceiver) PURE;
    STDMETHOD(RemoveReceiver)               (THIS_ IHXUIGenericEventReceiver* pReceiver) PURE;
};

#include "hxcomptr.h"
DEFINE_SMART_PTR(IHXEventSender)
DEFINE_SMART_PTR(IHXUIControlEventSender)
DEFINE_SMART_PTR(IHXUIGenericEventSender)
DEFINE_SMART_PTR(IHXPlayerEventSender)

#endif /* _IHXEVENTSENDER_H_ */
