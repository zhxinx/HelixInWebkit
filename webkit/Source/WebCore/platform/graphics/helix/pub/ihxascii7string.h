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


#ifndef _IHXASCII7STRING_H_
#define _IHXASCII7STRING_H_

/*!
    @singletype IHXAscii7String
    @abstract An interface for handling 7 bit Ascii strings.
 */

#include "hxcom.h"
#include "hxcomptr.h"
#include "ihxstring.h"


// $Private;

// {6C7B3681-2822-11d4-950F-00D0B71031B2}
DEFINE_GUID( IID_IHXAscii7String, 0x6c7b3681, 0x2822, 0x11d4, 0x95, 0xf, 0x0, 0xd0, 0xb7, 0x10, 0x31, 0xb2);

DECLARE_INTERFACE_( IHXAscii7String, IHXString )
{
    /*!
	@function 	SetAscii7String
	@abstract 	Set the string using a 7 bit ascii C style string
	@param 		newString [in] The NULL terminated string to set this to.
	@result 	HXR_OK if the string could be set. HXR_FAIL otherwise.
     */
    STDMETHOD( SetAscii7String )( THIS_ const char* pNewString ) PURE;

    /*!
	@function 	SetAscii7StringOfLength
	@abstract 	Set the string using a given number of characters from a 7 bit 
			ascii C style string.
	@param 		newString [in] The NULL terminated string to set this to.
	@param 		numCharacters [in] The number of characters to use.
	@result 	HXR_OK if the string could be set. HXR_FAIL otherwise.
     */
    STDMETHOD( SetAscii7StringOfLength )( THIS_ const char* pNewString, UINT32 numCharacters ) PURE;

    /*!
	@function GetAscii7Buffer
	@abstract Get a pointer to the raw buffer used to store the data.
	@param ppString This is set to point to the raw buffer. Note that 
	  the buffer will always be null terminated.
	@result HXR_OK if the buffer could be obtained. HXR_FAIL otherwise.
     */
    STDMETHOD( GetAscii7Buffer )( THIS_ /* out */ const char** ppString ) CONSTMETHOD PURE;

    /*!
	@function GetAscii7At
	@abstract Get a single character from the string
	@param pos The position in the string to get the character from. This value 
	           should be smaller than the length of the string.
	@result The character at the given position.
     */
    STDMETHOD_( char, GetAscii7At )( THIS_ UINT32 pos ) CONSTMETHOD PURE;

    /*!
	@function SetAscii7At
	@abstract Set a single character in the string
	@param pos The position in the string to set the chaarcter at. This value 
	           should be smaller than the length of the string.
	@param c The character to be set.
	@result HXR_OK if the character could be set. HXR_FAIL otherwise.
     */
    STDMETHOD ( SetAscii7At )( THIS_ UINT32 pos, char c ) PURE;
};

#ifdef __cplusplus
    #include <iosfwd>

    std::ostream& operator <<( std::ostream& o, const IHXAscii7String& );
    std::istream& operator >>( std::istream& is, IHXAscii7String& );
#endif

DEFINE_SMART_PTR(IHXAscii7String);

// $EndPrivate.



#endif // _IHXASCII7STRING_H_
