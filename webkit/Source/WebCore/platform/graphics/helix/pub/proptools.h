/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: proptools.h,v 1.2.4.2 2008/03/21 11:18:15 pbasic Exp $
 * 
 * Portions Copyright (c) 1995-2007 RealNetworks, Inc. All Rights Reserved.
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


#ifndef _PROPTOOLS_H_
#define _PROPTOOLS_H_

#include "hxtypes.h"
#include "hxmemprb.h"
#include "hxsrcin.h"
#include "hxformt.h"
#include "hxvalues.h"
#include "encstr.h"


class PropTools
{
public:
    // Removes <propertyName> from <pValues>.
    // If found, matching "<propertyName>_@@_TextEncodingType" property is also removed.
    static void RemovePropertyBuffer(HX_RESULT& retVal, IHXValues* pValues, const char* propertyName);
    static HX_RESULT RemovePropertyBuffer(IHXValues* pValues, const char* propertyName);

    // Removes <propertyName> from <pValues>.
    static void RemovePropertyCString(HX_RESULT& retVal, IHXValues* pValues, const char* propertyName);
    static HX_RESULT RemovePropertyCString(IHXValues* pValues, const char* propertyName);

    static void RemovePropertyULONG32(HX_RESULT& retVal, IHXValues* pValues, const char* propertyName);
    static HX_RESULT RemovePropertyULONG32(IHXValues* pValues, const char* propertyName);

    // Removes all properties from <pValues>.
    static void RemoveAllProperties(HX_RESULT& retVal, IHXValues* pValues);
    static HX_RESULT RemoveAllProperties(IHXValues* pValues);

    // If <propertyName>'s encoding is not found, <notFoundResult> is returned.
    static ULONG32 GetPropertyBufferEncodingType(IHXValues* src, const char* propertyName,
                                    ULONG32 notFoundResult = HX_TEXT_ENCODING_TYPE_UTF8);

    // If <bBlast> is TRUE, properties not found in <src> are removed from <dst>.
    static void CopyPropertyBuffer(HX_RESULT& retVal, IHXValues* dst, IHXValues* src,
                                    const char* propertyName, HXBOOL bBlast);

    static void CopyPropertyCString(HX_RESULT& retVal, IHXValues* dst, IHXValues* src,
                                    const char* propertyName, HXBOOL bBlast);

    static void CopyPropertyULONG32(HX_RESULT& retVal, IHXValues* dst, IHXValues* src,
                                    const char* propertyName, HXBOOL bBlast);

    static void CopyAllProperties(HX_RESULT& retVal, IHXValues* dst, IHXValues* src);

    // Returns TRUE if <propertyName> is found in <src>. <out> is set to empty string if <propertyName> is not found.
    static HXBOOL CopyPropertyBuffer(EncodedString& out, IHXValues* src, const char* propertyName);

    // Returns TRUE if <propertyName> is found in <src>.  <out> is set to 0 if <propertyName> is not found.
    static HXBOOL CopyPropertyULONG32(ULONG32& out, IHXValues* src, const char* propertyName);

    // If <bBlast> is TRUE, property is removed if <val> is empty.
    static void CopyPropertyBuffer(IHXValues* dst, const EncodedString& val, const char* propertyName, HXBOOL bBlast);

    // If <bBlast> is TRUE, property is removed if <bValid> is FALSE.
    static void CopyPropertyULONG32(IHXValues* dst, HXBOOL bValid, ULONG32 val, const char* propertyName, HXBOOL bBlast);

    // Returns TRUE if <val> can be converted to fixed-point number.
    // If <bNormalize> is TRUE and <val> can be converted, <val> is updated to normalized format, e.g. "-0" -> "0".
    static HXBOOL IsFixedPointNumber(EncodedString& val, HXBOOL bNormalize);

    // Returns TRUE if <val> can be converted to number which falls inside specified range.
    static HXBOOL ExtractUInt32(UINT32& out, const EncodedString& val, UINT32 minVal = 0, UINT32 maxVal = 0xFFFFFFFF);

    // Returns TRUE if <val> can be converted to number which falls inside specified range.
    static HXBOOL ExtractUInt16(UINT16& out, const EncodedString& val, UINT16 minVal = 0, UINT16 maxVal = 0xFFFF);

    // Returns TRUE if <val> can be converted to number which falls inside specified range.
    static HXBOOL ExtractUInt8(UINT8& out, const EncodedString& val, UINT8 minVal = 0, UINT8 maxVal = 0xFF);
};

#endif /* _PROPTOOLS_H_ */
