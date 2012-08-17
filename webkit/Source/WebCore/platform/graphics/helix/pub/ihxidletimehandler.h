/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: ihxidletimehandler.h,v 1.1 2008/05/20 05:57:12 vkathuria Exp $
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

#ifndef _IHXIDLETIME_HANDLER_H_
#define _IHXIDLETIME_HANDLER_H_

/*!
    @singletype IHXIdleTimeHandler
    @abstract Idle Time Handler definition
    @discussion This interface is implemented by objects that want to receive idle time.
 */

#include "hxcom.h"
#include "hxcomptr.h"


// $Private;

// {903C86E9-DA7A-11d3-94EE-00D0B7103550}
DEFINE_GUID( IID_IHXIdleTimeHandler, 0x903c86e9, 0xda7a, 0x11d3, 0x94, 0xee, 0x0, 0xd0, 0xb7, 0x10, 0x35, 0x50 );

/*!
    @interface IHXIdleTimeHandler
 */
DECLARE_INTERFACE_( IHXIdleTimeHandler, IUnknown )
{
    /*!
	@function   OnIdleTime
	@abstract   Called repeatedly during idle time.
	@param	    isInBackground [in] TRUE if this process/application is currently in the background.
     */
    STDMETHOD_( void, OnIdleTime ) ( THIS_ HXBOOL isInBackground ) PURE;
};

DEFINE_SMART_PTR(IHXIdleTimeHandler);

// $EndPrivate.


#endif // _IHXIDLETIME_HANDLER_H_
