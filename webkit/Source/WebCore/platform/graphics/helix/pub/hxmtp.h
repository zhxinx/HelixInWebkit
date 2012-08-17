/* ***** BEGIN LICENSE BLOCK *****
* Source last modified: $Id: hxmtp.h,v 1.1.2.1 2008/05/08 07:53:58 vkathuria Exp $
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

#ifndef _HXMTP_H_
#define _HXMTP_H_

#define PLUGIN_MTPHANDLER_TYPE "PLUGIN_MTP_HANDLER"
#define MTPHANDLER_HOST_TYPE	"MTPHANDLER_HOST"
#define MTPHANDLER_TYPE "MTPHandlerType"
#define HXMTP_ID_WMMTP   "WMMTP"
#define HXMTP_NAME_MTPID	"JANUS"
#define MTP_HANDLER_GUID	"MTP_HANDLER_GUID"
#define MTPHANDLER_TYPE "MTPHandlerType"
#define MTPHANDLER_DRM_TYPE	"MTPHANDLER_DRM_TYPE"

DEFINE_GUID(IID_IHXMTPUSBController, 
0x9ab352e3, 0x2e02, 0x416e, 0xb3, 0x70, 0x64, 0x7f, 0xb1, 0x88, 0x45, 0xaf);


#undef  INTERFACE
#define INTERFACE   IHXMTPUSBController

DECLARE_INTERFACE_(IHXMTPUSBController, IUnknown)
{

    
    STDMETHOD(HXMTPUSB_Initialize)  (THIS_
			              ULONG32 ulKey, 
						  ULONG32& ulContext) PURE;


    STDMETHOD(HXMTPUSB_DeInitialize) (THIS_ 
			                   ULONG32 ulContext) PURE;
};


DEFINE_GUID(IID_IHXMTPIPController, 
0xd06881ee, 0x45a6, 0x468c, 0x99, 0x4e, 0x98, 0xd9, 0xfd, 0x87, 0xab, 0x67);

#undef  INTERFACE
#define INTERFACE   IHXMTPIPController

DECLARE_INTERFACE_(IHXMTPIPController, IUnknown)
{

    
    STDMETHOD(HXMTPIP_Initialize)  (THIS_
			              ULONG32 ulKey, 
						  ULONG32& ulContext) PURE;


    STDMETHOD(HXMTPIP_DeInitialize) (THIS_ 
			                   ULONG32 ulContext) PURE;
};


DEFINE_GUID(IID_HXIXMLElementHandler,
            0xa588f88b, 0x9be2, 0x4772, 0x97, 0xd4, \
            0x4f, 0xe2, 0x7, 0x12, 0xfc, 0x3e);

#endif /*_HXMTP_H_*/
