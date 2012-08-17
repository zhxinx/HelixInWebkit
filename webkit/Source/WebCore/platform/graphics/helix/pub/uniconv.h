/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: uniconv.h,v 1.2.4.2 2008/03/21 11:18:15 pbasic Exp $
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


#ifndef _UNICONV_H
#define _UNICONV_H

#include "hxtypes.h"


// Returns TRUE if all code-points are ASCII ( <= 0x7F ).
// 
// If <uNumCodeUnits> != MAX_UINT32, maximum of <uNumCodeUnits> units are consumed.
// If <pCodeUnits> is NULL, TRUE is returned.
// After the function returns, <outNumUnits> contains the number of units successfully processed.
//
HXBOOL IsUTF8StringAsciiOnly(const UINT8* pCodeUnits, UINT32 uNumCodeUnits, UINT32& outNumUnits);


// Returns TRUE if all code-points are ASCII ( <= 0x7F ).
// 
// If <uNumCodeUnits> != MAX_UINT32, maximum of <uNumCodeUnits> units are consumed.
// If <pCodeUnits> is NULL, TRUE is returned.
// If <bBigEndian> is TRUE, code-units are consumed in big-endian byte-order;
// otherwise they're consumed in little-endian byte-order.
// After the function returns, <outNumUnits> contains the number of units successfully processed.
//
HXBOOL IsUTF16StringAsciiOnly(const UINT16* pCodeUnits, UINT32 uNumCodeUnits,
                            HXBOOL bBigEndian, UINT32& outNumUnits);


// Returns TRUE if all code-points are ASCII ( <= 0x7F ).
// 
// If <uNumCodeUnits> != MAX_UINT32, maximum of <uNumCodeUnits> units are consumed.
// If <pCodeUnits> is NULL, TRUE is returned.
// If <bBigEndian> is TRUE, code-units are consumed in big-endian byte-order;
// otherwise they're consumed in little-endian byte-order.
// After the function returns, <outNumUnits> contains the number of units successfully processed.
//
HXBOOL IsUTF32StringAsciiOnly(const UINT32* pCodeUnits, UINT32 uNumCodeUnits,
                            HXBOOL bBigEndian, UINT32& outNumUnits);


// Return codes:  0 indicates success.
//               -1 indicates that not enough units were available.
//               -2 indicates that invalid code-unit sequence was encountered.
// 
// If <uNumCodeUnits> != MAX_UINT32, maximum of <uNumCodeUnits> units are consumed.
// If <pInCodeUnits> is NULL, -1 is returned.
// In case of error <outCodePoint> and <outNumConsumedCodeUnits> are set to 0.
//
INT32 ConvertUTF8CodeUnitSequenceToUnicodeCodePoint(
                    UINT32& outCodePoint, UINT32& outNumConsumedCodeUnits,
                    const UINT8* pInCodeUnits, UINT32 uNumCodeUnits);


// Function always succeeds.
//                2 indicates success. Code-point was illegal and unicode
//                  replacement character (0xFFFD) was outputed instead of failing.
// Return codes:  0 indicates success. Code-point was legal.
// 
// If <bScanMode> is TRUE, the function only sets <outNumOutputedCodeUnits>,
// in this case 0 can be passed as an argument for <pOutCodeUnits>;
// Scan-mode can be used for calculation of output buffer size.
//
INT32 ConvertUnicodeCodePointToUTF8CodeUnitSequence(
                    UINT8* pOutCodeUnits, UINT32& outNumOutputedCodeUnits,
                    UINT32 codePoint, HXBOOL bScanMode);


// Return codes:  0 indicates success.
//               -1 indicates that not enough units were available.
//               -2 indicates that invalid code-unit sequence was encountered.
// 
// If <bInputBigEndian> is TRUE, code-units are consumed in big-endian byte-order;
// otherwise they're consumed in little-endian byte-order.
// If <uNumCodeUnits> != MAX_UINT32, maximum of <uNumCodeUnits> units are consumed.
// If <pInCodeUnits> is NULL, -1 is returned.
// In case of error <outCodePoint> and <outNumConsumedCodeUnits> are set to 0.
//
INT32 ConvertUTF16CodeUnitSequenceToUnicodeCodePoint(
                    UINT32& outCodePoint, UINT32& outNumConsumedCodeUnits,
                    const UINT16* pInCodeUnits, HXBOOL bInputBigEndian,
                    UINT32 uNumCodeUnits);


// Function always succeeds.
//                2 indicates success. Code-point was illegal and unicode
//                  replacement character (0xFFFD) was outputed instead of failing.
// Return codes:  0 indicates success. Code-point was legal.
// 
// If <bOutputBigEndian> is TRUE, code-units are outputed in big-endian byte-order;
// otherwise they're outputed in little-endian byte-order.
// If <bScanMode> is TRUE, the function only sets <outNumOutputedCodeUnits>,
// in this case 0 can be passed as an argument for <pOutCodeUnits>;
// Scan-mode can be used for calculation of output buffer size.
//
INT32 ConvertUnicodeCodePointToUTF16CodeUnitSequence(
                    UINT16* pOutCodeUnits, UINT32& outNumOutputedCodeUnits,
                    UINT32 codePoint, HXBOOL bOutputBigEndian, HXBOOL bScanMode);


// Return codes:   0 indicates success.
//                -1 indicates that not enough units were available.
//                -2 indicates that invalid code-unit sequence was encountered.
//               -11 indicates that output buffer was too short.
// 
// If <uNumInCodeUnits> != MAX_UINT32, maximum of <uNumInCodeUnits> units are consumed,
// otherwise extraction continues until the 0-terminator is reached.
// 0-terminator is included in output in 0-terminator mode.
// If <pInCodeUnits> is NULL, -1 is returned.
// After the function returns, <outNumConsumedCodeUnits> contains number of successfully consumed
// code-units, and <outNumOutputedCodeUnits> contains number of successfully outputed code-units.
// If <pOutCodeUnits> is NULL or <uMaxOutCodeUnits> is 0, <outNumOutputedCodeUnits> contains number of
// code-units that would be successfully outputed; this mode can be used for calculation of output
// buffer size. When passing non-NULL <pOutCodeUnits>, <uMaxOutCodeUnits> should contain the size of
// output buffer in code-units. If <bOutputBigEndian> is TRUE, code-units are outputed in big-endian
// byte-order; otherwise they're outputed in little-endian byte-order.
//
INT32 ConvertUTF8StringToUTF32String(
                    const UINT8* pInCodeUnits, UINT32 uNumInCodeUnits, UINT32& outNumConsumedCodeUnits,
                    UINT32* pOutCodeUnits, UINT32 uMaxOutCodeUnits, UINT32& outNumOutputedCodeUnits,
                    HXBOOL bOutputBigEndian);


// Return codes:   2 indicates success. One or more code-units were illegal and
//                   unicode replacement character (0xFFFD) was converted instead of failing.
//                 0 indicates success. All code-units were legal.
//                -1 indicates that not enough code-units were available.
//               -11 indicates that output buffer was too short.
// 
// If <uNumInCodeUnits> != MAX_UINT32, maximum of <uNumInCodeUnits> units are consumed,
// otherwise extraction continues until the 0-terminator is reached.
// 0-terminator is included in output in 0-terminator mode.
// If <pInCodeUnits> is NULL, -1 is returned.
// After the function returns, <outNumConsumedCodeUnits> contains number of successfully consumed
// code-units, and <outNumOutputedCodeUnits> contains number of successfully outputed code-units.
// If <pOutCodeUnits> is NULL or <uMaxOutCodeUnits> is 0, <outNumOutputedCodeUnits> contains number of
// code-units that would be successfully outputed; this mode can be used for calculation of output
// buffer size. When passing non-NULL <pOutCodeUnits>, <uMaxOutCodeUnits> should contain the size of
// output buffer in code-units. If <bInputBigEndian> is TRUE, code-units are consumed in big-endian
// byte-order; otherwise they're consumed in little-endian byte-order.
//
INT32 ConvertUTF32StringToUTF8String(
                    const UINT32* pInCodeUnits, UINT32 uNumInCodeUnits, UINT32& outNumConsumedCodeUnits,
                    HXBOOL bInputBigEndian,
                    UINT8* pOutCodeUnits, UINT32 uMaxOutCodeUnits, UINT32& outNumOutputedCodeUnits);


// Return codes:   0 indicates success.
//                -1 indicates that not enough input units were available.
//                -2 indicates that invalid code-unit sequence was encountered.
//               -11 indicates that output buffer was too short.
// 
// If <uNumInCodeUnits> != MAX_UINT32, maximum of <uNumInCodeUnits> units are consumed,
// otherwise extraction continues until the 0-terminator is reached.
// 0-terminator is included in output in 0-terminator mode.
// If <pInCodeUnits> is NULL, -1 is returned.
// After the function returns, <outNumConsumedCodeUnits> contains number of successfully consumed
// code-units, and <outNumOutputedCodeUnits> contains number of successfully outputed code-units.
// If <pOutCodeUnits> is NULL or <uMaxOutCodeUnits> is 0, <outNumOutputedCodeUnits> contains number of
// code-units that would be successfully outputed; this mode can be used for calculation of output
// buffer size. When passing non-NULL <pOutCodeUnits>, <uMaxOutCodeUnits> should contain the size of
// output buffer in code-units. If <bOutputBigEndian> is TRUE, code-units are outputed in big-endian
// byte-order; otherwise they're outputed in little-endian byte-order.
//
INT32 ConvertUTF8StringToUTF16String(
                    const UINT8* pInCodeUnits, UINT32 uNumInCodeUnits, UINT32& outNumConsumedCodeUnits,
                    UINT16* pOutCodeUnits, UINT32 uMaxOutCodeUnits, UINT32& outNumOutputedCodeUnits,
                    HXBOOL bOutputBigEndian);


// Return codes:   0 indicates success.
//                -1 indicates that not enough input units were available.
//                -2 indicates that invalid code-unit sequence was encountered.
//               -11 indicates that output buffer was too short.
// 
// If <uNumInCodeUnits> != MAX_UINT32, maximum of <uNumInCodeUnits> units are consumed,
// otherwise extraction continues until the 0-terminator is reached.
// 0-terminator is included in output in 0-terminator mode.
// If <pInCodeUnits> is NULL, -1 is returned.
// After the function returns, <outNumConsumedCodeUnits> contains number of successfully consumed
// code-units, and <outNumOutputedCodeUnits> contains number of successfully outputed code-units.
// If <pOutCodeUnits> is NULL or <uMaxOutCodeUnits> is 0, <outNumOutputedCodeUnits> contains number of
// code-units that would be successfully outputed; this mode can be used for calculation of output
// buffer size. When passing non-NULL <pOutCodeUnits>, <uMaxOutCodeUnits> should contain the size of
// output buffer in code-units. If <bInputBigEndian> is TRUE, code-units are consumed in big-endian
// byte-order; otherwise they're consumed in little-endian byte-order.
//
INT32 ConvertUTF16StringToUTF8String(
                    const UINT16* pInCodeUnits, UINT32 uNumInCodeUnits, UINT32& outNumConsumedCodeUnits,
                    HXBOOL bInputBigEndian,
                    UINT8* pOutCodeUnits, UINT32 uMaxOutCodeUnits, UINT32& outNumOutputedCodeUnits);

#endif// _UNICONV_H

