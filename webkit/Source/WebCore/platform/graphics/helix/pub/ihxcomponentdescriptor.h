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

#ifndef _IHXCOMPONENT_H_
#define _IHXCOMPONENT_H_

#include "hxcom.h"

typedef _INTERFACE   IHXBuffer		    IHXBuffer;

/****************************************************************************
 * 
 *  Interface:
 * 
 *	IHXComponentDescriptor
 * 
 *  Purpose:
 * 
 *	This interface provides methods to component's properties
 * 
 *  IID_IHXComponentDescriptor:
 * 
 *	{00006000-0901-11d1-8B06-00A024406D59}
 * 
 */
DEFINE_GUID(IID_IHXComponentDescriptor,   0x00006000, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
				          0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE   IHXComponentDescriptor

DECLARE_INTERFACE_(IHXComponentDescriptor, IUnknown)
{
    /*
     *  IHXComponentDescriptor methods
     */
    STDMETHOD(SetProperty)                  (THIS_
                                             const char* pName,
                                             IHXBuffer* pValue) PURE;
    
    STDMETHOD(GetProperty)                  (THIS_
                                             const char* pName,
                                             REF(IHXBuffer*) pValue) PURE;

    STDMETHOD(RemoveProperty)               (THIS_
                                             const char* pName) PURE;

    STDMETHOD_(UINT32, GetPropertyCount)    (THIS) PURE;
    
    STDMETHOD(GetPropertyAt)                (THIS_
                                             UINT32 ulIndex,
                                             REF(const char*) pName,
                                             REF(IHXBuffer*) pValue) PURE;

    STDMETHOD(RemovePropertyAt)             (THIS_
                                             UINT32 ulIndex) PURE;

    STDMETHOD(RemoveAll)                    (THIS) PURE;
};

/****************************************************************************
 * 
 *  Interface:
 * 
 *	IHXComponentDescriptorsCollection
 * 
 *  Purpose:
 * 
 *	This interface provides methods to access properties of Helix components
 * 
 *  IID_IHXComponentDescriptorsCollection:
 * 
 *	{00006001-0901-11d1-8B06-00A024406D59}
 * 
 */
DEFINE_GUID(IID_IHXComponentDescriptorsCollection,   0x00006001, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
				                     0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE   IHXComponentDescriptorsCollection

DECLARE_INTERFACE_(IHXComponentDescriptorsCollection, IUnknown)
{
    /*
     *  IHXComponentDescriptorsCollection methods
     */

    STDMETHOD(Create)		    (THIS_
				     REF(IHXComponentDescriptor*) pComponent) PURE;

    STDMETHOD(Add)	            (THIS_
                                     IHXComponentDescriptor* pComponent) PURE;

    STDMETHOD(Remove)	            (THIS_
                                     IHXComponentDescriptor* pComponent) PURE;

    STDMETHOD_(UINT32, GetCount)    (THIS) PURE;

    STDMETHOD(GetAt)                (THIS_
                                     UINT32 ulIndex,
                                     REF(IHXComponentDescriptor*) pComponent) PURE;

    STDMETHOD(RemoveAt)             (THIS_
                                     UINT32 ulIndex) PURE;

    STDMETHOD(RemoveAll)            (THIS) PURE;
};

#include "hxcomptr.h"
DEFINE_SMART_PTR(IHXComponentDescriptor)
DEFINE_SMART_PTR(IHXComponentDescriptorsCollection)

#endif /* _IHXCOMPONENT_H_ */
