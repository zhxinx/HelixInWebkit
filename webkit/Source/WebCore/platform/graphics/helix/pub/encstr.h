/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: encstr.h,v 1.3.4.2 2008/03/21 11:18:15 pbasic Exp $
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


#ifndef _ENCSTR_H_
#define _ENCSTR_H_

#include "hxtypes.h"
#include "hxmemprb.h"
#include "hxsrcin.h"
#include "hxformt.h"
#include "hxvalues.h"
#include "pckunpck.h"


class EncStrUtils
{
public:

#ifndef HELIX_CONFIG_DISABLE_CONSOLE_PRINT
    
    // Prints string in hexadecimal format.
    static void HexDump(const char* psz, HX_TEXT_ENCODING_TYPE enc);

    // Prints encoding-type string, returns FALSE if encoding was of unknown type.
    static HXBOOL PrintEncodingType(HX_TEXT_ENCODING_TYPE enc);

    // Prints UTF8 string, returns FALSE if the sequence was invalid.
    static HXBOOL PrintTextUTF8(const char* psz);

    // Prints string, returns FALSE if the sequence was invalid.
    static HXBOOL PrintText(const char* psz, HX_TEXT_ENCODING_TYPE enc);

    // Prints string contents (encoding-type, byte-length, hex-dump, characters).
    static void Dump(const char* psz, HX_TEXT_ENCODING_TYPE enc);

#endif // End of #ifndef HELIX_CONFIG_DISABLE_CONSOLE_PRINT

    // Returns TRUE if the terminated string contains only ASCII characters.
    static HXBOOL IsAsciiOnly(const char* psz, HX_TEXT_ENCODING_TYPE enc);

    // Returns TRUE if the terminated string is empty (contains only terminator and possibly BOM).
    static HXBOOL IsEmpty(const char* psz, HX_TEXT_ENCODING_TYPE enc);

    // Returns TRUE if the string starts with "FEFF" big-endian byte-order-mark, FALSE otherwise.
    static HXBOOL IsUTF16BE(const char* psz);

    // Returns TRUE if the string starts with "FFFE" little-endian byte-order-mark, FALSE otherwise.
    static HXBOOL IsUTF16LE(const char* psz);

    // Return codes: 0 if the string does not start with byte-order-mark.
    //               1 if the string starts with "FFFE" little-endian byte-order-mark.
    //               2 if the string starts with "FEFF" big-endian byte-order-mark.
    static INT32 IsUTF16(const char* psz);

    // Scan flags.
    typedef enum {
        SCAN_FLAG_UTF16BE = 0x00000001,
        SCAN_FLAG_UTF16LE = 0x00000002,

        SCAN_FLAGS_UTF16 = SCAN_FLAG_UTF16BE | SCAN_FLAG_UTF16LE,
        SCAN_FLAGS_UTF = SCAN_FLAGS_UTF16,
        SCAN_FLAGS_ALL = SCAN_FLAGS_UTF
    } SCAN_FLAG;

    // Scans the string for byte-order-mark and tries to determine it's encoding.
    static HX_TEXT_ENCODING_TYPE ScanEncoding(const char* psz, UINT32 scanFlags = SCAN_FLAGS_ALL);

    // Scans the string for byte-order-mark and returns a pointer to the beginning of payload.
    static char* SkipBOM(char* psz, UINT32 scanFlags = SCAN_FLAGS_ALL);

    static inline const char* SkipBOM(const char* psz, UINT32 scanFlags = SCAN_FLAGS_ALL)
    {
        return SkipBOM((char*)psz, scanFlags);
    }

    // Writes byte-order-mark. If <bBigEndian> is TRUE, UTF16BE byte-order-mark is written;
    // otherwise UTF16LE byte-order-mark is written.
    static void WriteUTF16BOM(char* psz, HXBOOL bBigEndian);

    // Returns the number of bytes in the UTF-16 encoded string. If <bCountNullTerm>
    // is TRUE, the terminating character is included in final count.
    static UINT32 UTF16ByteLength(const char* psz, HXBOOL bCountNullTerm);

    // Returns the number of bytes in the UTF-16, UTF-8 or legacy encoded string.
    // If <bCountNullTerm> is TRUE, the terminating character is included in final count.
    static UINT32 ByteLength(const char* psz, HX_TEXT_ENCODING_TYPE enc, HXBOOL bCountNullTerm);

    // Returns the number of code-units in the UTF-16, UTF-8 or legacy encoded string.
    // If <bCountNullTerm> is TRUE, the terminating character is included in final count.
    // If <bCountBOM> is TRUE, leading byte-order-mark is included in final count if it's present.
    static UINT32 CodeUnitLength(const char* psz, HX_TEXT_ENCODING_TYPE enc, HXBOOL bCountNullTerm, HXBOOL bCountBOM);

    // Returns the number of bytes in the UTF-16, UTF-8 or legacy encoded string.
    // String is scaned for encodings specified by <scanFlags>.
    // If <bCountNullTerm> is TRUE, the terminating character is included in final count.
    static UINT32 ByteLengthScan(const char* psz, HXBOOL bCountNullTerm, UINT32 scanFlags = SCAN_FLAGS_ALL);

    // Swaps byte-order of UTF-16 terminated string.
    static void UTF16SwapByteOrder(char* psz);

    // Memory allocation flags.
    typedef enum {
        ALLOC_FLAG_NEW    = 0x00000001,
        ALLOC_FLAG_MALLOC = 0x00000002
    } ALLOC_FLAG;

    // Allocates memory for the string. If <byteSize> is 0, 0 is returned.
    static char* Allocate(UINT32 byteSize, UINT32 allocFlags = ALLOC_FLAG_NEW);

    // Deallocates memory for the string.
    static void Deallocate(char* psz, UINT32 allocFlags);

    // Allocates memory through Allocate and copies the string including the terminating character.
    // If <psz> is 0, 0 is returned.
    static char* Duplicate(const char* psz, HX_TEXT_ENCODING_TYPE enc, UINT32 allocFlags = ALLOC_FLAG_NEW);

    // Allocates memory through Allocate and copies the string including the terminating character.
    // BOM mark is prepended if it's missing.
    // If <psz> is 0, 0 is returned. Accepted values for <enc> are: HX_TEXT_ENCODING_TYPE_UTF16,
    // HX_TEXT_ENCODING_TYPE_UTF16BE, HX_TEXT_ENCODING_TYPE_UTF16LE. If <enc> is HX_TEXT_ENCODING_TYPE_UTF16
    // and <psz> does not start with BOM, big-endian BOM is assumed.
    static char* UTF16DuplicateWithBOM(const char* psz, HX_TEXT_ENCODING_TYPE enc, UINT32 allocFlags = ALLOC_FLAG_NEW);

    // Allocates memory through Allocate and converts UTF-8 encoded string to UTF-16BE encoded string
    // including the terminating character. If <psz> is 0, 0 is returned.
    // If <bBigEndian> is TRUE, function outputs UTF16BE code-units, otherwise it outputs UTF16LE code-units.
    // If <bPrependBOM> is TRUE, function prepends byte-order-mark to the output.
    static char* ConvertUTF8ToUTF16(const char* psz, HXBOOL bBigEndian, HXBOOL bPrependBOM, UINT32 allocFlags = ALLOC_FLAG_NEW);

    // Allocates memory through Allocate and converts UTF-16 encoded string to UTF-8 encoded string
    // including the terminating character. If <psz> is 0, 0 is returned.
    // Accepted values for <enc> are: HX_TEXT_ENCODING_TYPE_UTF16,
    // HX_TEXT_ENCODING_TYPE_UTF16BE, HX_TEXT_ENCODING_TYPE_UTF16LE.
    static char* ConvertUTF16ToUTF8(const char* psz, HX_TEXT_ENCODING_TYPE enc, UINT32 allocFlags = ALLOC_FLAG_NEW);

    // Allocates memory through Allocate and converts string to UTF-8 encoded string
    // including the terminating character. If <psz> is 0, 0 is returned.
    // Function fails if <enc> is one of {HX_TEXT_ENCODING_TYPE_UNKNOWN, HX_TEXT_ENCODING_TYPE_ISO8859_1}
    // and the string contains non-ascii characters.
    static char* ConvertToUTF8(const char* psz, HX_TEXT_ENCODING_TYPE enc, UINT32 allocFlags = ALLOC_FLAG_NEW);

    // Allocates memory through Allocate and converts string to UTF-16BE encoded string
    // including the terminating character. If <psz> is 0, 0 is returned.
    // Function fails if <enc> is one of {HX_TEXT_ENCODING_TYPE_UNKNOWN, HX_TEXT_ENCODING_TYPE_ISO8859_1}
    // and the string contains non-ascii characters.
    // If <bBigEndian> is TRUE, function outputs UTF16BE code-units, otherwise it outputs UTF16LE code-units.
    // If <bPrependBOM> is TRUE, function prepends byte-order-mark to the output string.
    static char* ConvertToUTF16(const char* psz, HX_TEXT_ENCODING_TYPE enc, HXBOOL bBigEndian, HXBOOL bPrependBOM,
                                UINT32 allocFlags = ALLOC_FLAG_NEW);

    // Returns TRUE if the terminated strings are equal. BOM marks are skipped before comparison.
    static HXBOOL UTF16Equal(const char* psz1, HX_TEXT_ENCODING_TYPE enc1, const char* psz2, HX_TEXT_ENCODING_TYPE enc2);

    // Returns TRUE if the terminated strings are equal.
    // Strings are considered equal if they have same UTF8 representation.
    static HXBOOL Equal(const char* psz1, HX_TEXT_ENCODING_TYPE enc1, const char* psz2, HX_TEXT_ENCODING_TYPE enc2);
};


// String buffer with encoding-type information.
class EncodedString
{
public:
    explicit EncodedString(const char* pszData = 0, HX_TEXT_ENCODING_TYPE encType = HX_TEXT_ENCODING_TYPE_UTF8);
    virtual ~EncodedString();

    EncodedString(const EncodedString& rhs);
    EncodedString& operator=(const EncodedString& rhs);

    bool operator==(const EncodedString& rhs) const;
    bool operator!=(const EncodedString& rhs) const { return !(*this == rhs); }

    void Set(const char* pszData = 0, HX_TEXT_ENCODING_TYPE encType = HX_TEXT_ENCODING_TYPE_UTF8);

    void Clear()
    {
        Set();
    }
    HXBOOL IsAsciiOnly() const
    {
        return EncStrUtils::IsAsciiOnly(m_data, m_encType);
    }
    HXBOOL IsEmpty() const
    {
        return EncStrUtils::IsEmpty(m_data, m_encType);
    }
    const char* GetData() const
    {
        return m_data;
    }
    HX_TEXT_ENCODING_TYPE GetEncoding() const
    {
        return m_encType;
    }
    UINT32 GetByteLength(HXBOOL bCountNullTerm = FALSE) const;
    UINT32 GetCodeUnitLength(HXBOOL bCountNullTerm = FALSE, HXBOOL bCountBOM = FALSE) const;

    void Dump() const
    {
#ifndef HELIX_CONFIG_DISABLE_CONSOLE_PRINT
        EncStrUtils::Dump(m_data, m_encType);
#endif
    }
    HXBOOL ConvertToUTF8(EncodedString& out) const;
    HXBOOL ConvertToUTF16(EncodedString& out, HXBOOL bBigEndian, HXBOOL bPrependBOM) const;

private:
    void Cleanup();

    char* m_data;
    UINT32 m_totalByteLength;
    HX_TEXT_ENCODING_TYPE m_encType;
};


#endif /* _ENCSTR_H_ */
