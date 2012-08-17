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


#ifndef _IHXPROPERTYBAG_H_
#define _IHXPROPERTYBAG_H_

#include "hxcom.h"

_INTERFACE IHXBuffer;

// {605931B0-45A3-4538-B8A3-DDB45BA9B262}
DEFINE_GUID(IID_IHXPropertyBag, 0x605931b0, 0x45a3, 0x4538, 0xb8, 0xa3, 0xdd, 0xb4, 0x5b, 0xa9, 0xb2, 0x62);

#undef INTERFACE
#define INTERFACE IHXPropertyBag

DECLARE_INTERFACE_(IHXPropertyBag, IUnknown)
{
    /* AddProperty: Adds a property to the bag.
     * 
     * NOTE - MUST READ BEFORE USING:
     *      Do NOT reuse any of the parameters that are passed in.  For example, you allocated two IHXBuffer,
     *      and set a value IHXBufferName = "TempName" on one, and IHXBufferValue "TempValue" on the other.
     *      Then you do AddProperty(IHXBufferName, IHXBufferValue).  After that, do not modify IHXBufferName,
     *      but instead allocate a new buffer and call AddProperty with those new buffers!  This is necessary
     *      so that the propertybag does not waste memory and time copying buffers, but this up to the internal
     *      implementation, so do not lock down how it can be implemented!
     *
     * Parameters:
     *      - pName:  (in) The name associated with the value.  pName can possibly be addref-ed so DO NOT REUSE IT.
     *      - pValue: (in) The value.  pValue can possibly be addref-ed so DO NOT REUSE IT.
     */
    STDMETHOD(AddProperty)      (THIS_ IHXBuffer* pName, IHXBuffer* pValue) PURE;

    STDMETHOD(RemoveProperty)   (THIS_ IHXBuffer* pName) PURE;

    /* GetProperty: Gets a property from the bag via a name.
     * 
     * NOTE - MUST READ BEFORE USING:
     *      Do NOT modify the ppValue because it can be an addref-ed buffer that the internal representation
     *      also has a pointer to.  So if you do get back ppValue, and you decide to modify the value in ppValue,
     *      then that may cause ppValue to change everywhere.  THIS IS NOT GOOD!  Think of ppValue as a const.
     *      Instead use utilities to copy that buffer if needed, since in most cases, you just want to know the
     *      value not actually modify that value.
     *
     * Parameters:
     *      - pName:   (in) The name associated with the value.
     *      - ppValue: (out) IHXBuffer pointer that has the value associated with the name.  Do not modify
     *                       the contents of ppValue because it can possibly just be an addref-ed value.  Think
     *                       of this value as a const.
     */
    STDMETHOD(GetProperty)      (THIS_ IHXBuffer* pName, IHXBuffer** ppValue) PURE;

    /* GetIndexProperty: Gets a name/value property from the bag via an index.  The index is not always consistent.
     *      For example, if you have a property bag, and say at index 1 you get the name/value "tempname"/"tempvalue".
     *      Then you decide to add another name/value called "newname"/"newprop", the when you try to get the
     *      name/value pair in index 1, you are NOT guaranteed "tempname"/"tempvalue"
     * 
     * NOTE - MUST READ BEFORE USING:
     *      Do NOT modify the ppName and ppValue because it can be an addref-ed buffer that the internal
     *      representation also has a pointer to.  So if you do get back ppValue, and you decide to modify
     *      the value in ppValue, then that may cause ppValue to change everywhere.  THIS IS NOT GOOD!
     *      Think of ppValue as a const.  Instead use utilities to copy that buffer if needed, since in most
     *      cases, you just want to know the value not actually modify that value.
     *
     * Parameters:
     *      - iIndex:  (in) The index to get the property.
     *      - ppName:  (out) The name associated with the value, at the index.
     *      - ppValue: (out) Addref-ed pointer to an IHXBuffer pointer that has the value associated with the name.
     *                       Think of this value as a const.
     */
    STDMETHOD(GetIndexProperty) (THIS_ INT32 iIndex, IHXBuffer** ppName, IHXBuffer** ppValue) PURE;

    /* GetCount: Gets the number of name/value pairs contained in the property bag
     *
     * Parameters:
     *      - piIndex: (out) The number of name/value pairs contained in the property bag.
     */
    STDMETHOD(GetCount)         (THIS_ INT32* piCount) PURE;
};

#include "hxcomptr.h"
DEFINE_SMART_PTR(IHXPropertyBag)

#endif /* _IHXPROPERTYBAG_H_ */
