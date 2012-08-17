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


#ifndef _IHXSTRING_H_
#define _IHXSTRING_H_

/*!
    @singletype IHXString
    @abstract Abstract definition of a string.
    @discussion 
		This provides a mechanism for passing and manipulating a string without
		regard to the internal format.  Other interfaces are available that provide
		format-specific accessors.
 */

#include "hxcom.h"
#include "hxcomptr.h"

// $Private;

// {6C7B3680-2822-11d4-950F-00D0B71031B2}
DEFINE_GUID( IID_IHXString, 0x6c7b3680, 0x2822, 0x11d4, 0x95, 0xf, 0x0, 0xd0, 0xb7, 0x10, 0x31, 0xb2);


DECLARE_INTERFACE_( IHXString, IUnknown )
{
    /*!
	@function GetLength
	@abstract Get the length of the string in characters.
	@result The length of the string in characters
     */
    STDMETHOD_( UINT32, GetLength )( THIS ) CONSTMETHOD PURE;

    /*!
	@function IsOfType
	@abstract See if the string is of the given type. Strings of 
		  different types will have interfaces that inherit 
		  from IHXString. Pass in the IID of these interfaces 
		  to see if the string is of that type or not.
	@param iid  The iid to look for
	@result TRUE iff the string is of the given type.
     */
    STDMETHOD_( HXBOOL, IsOfType )( THIS_ REFIID iid ) CONSTMETHOD PURE;

    /*!
	@function Reserve
	@abstract Make sure that the string has sufficient space reserved to 
	  hold a given number of characters. Use this for efficiency to save 
	  a string being reallocated with bigger and bigger buffers. If you 
	  know at an early stage roughly how large the string will end up, 
	  use Reserve to save that space once, and save the inefficiency of 
	  reallocating.
	@param numCharacters The minimum number of characters the string 
	  should be able to store.
	@result HXR_OK if the space could be reserved.
     */
    STDMETHOD( Reserve )( THIS_ UINT32 numCharacters ) PURE;

    /*!
	@function Capacity
	@abstract Find out what capacity this string has.
	@result The number of characters this string has space to 
	  store.without reallocating memory
     */
    STDMETHOD_( UINT32, GetCapacity )( THIS ) CONSTMETHOD PURE;


    /*!
	@function GetAt
	@abstract Get the character at the given index.
     */
    STDMETHOD( GetAt )( THIS_ UINT32 index, UINT32* pChar ) CONSTMETHOD PURE;

    /*!
	@function SetAt
	@abstract Set the character at the given position. The character 
		  will be converted into the appropriate type for the string.
     */
    STDMETHOD( SetAt )( THIS_ UINT32 index, UINT32 ch ) PURE;

    /*!
	@function Replace
	@abstract Replace a portion of this string with a portion of another string.
     */
    STDMETHOD( Replace )( THIS_ UINT32 pos1, UINT32 n1, const IHXString*, UINT32 pos2, UINT32 n2 ) PURE;

    /*!
	@function Replace
	@abstract Replace a portion of this string with a portion of 
	  another string.that is passed in in its rawest form.
     */
    STDMETHOD( ReplaceRaw )( THIS_ UINT32 pos1, UINT32 n1, const void* pStringData, UINT32 charSize, UINT32 pos2, UINT32 n2 ) PURE;

    /*!
	@function Clone
	@abstract Produce a copy of this string
     */
    STDMETHOD( Clone )( THIS_ IHXString** ) CONSTMETHOD PURE;

    /*!
	@function CloneEmptyString
	@abstract Produce a new string of the same type as this one but with zero length
     */
    STDMETHOD( CloneEmptyString )( THIS_ IHXString** ) CONSTMETHOD PURE;

    /*!
	@function GetStringBuffer
	@abstract Get a pointer to the string's internal buffer
     */
    STDMETHOD_( const void*, GetStringBuffer )( THIS ) CONSTMETHOD PURE;

    /*!
	@function GetCharacterSize
	@abstract Get the character size used by this particular string
	@return The character size in bytes i.e. 1 = char, 2 = UINT16, 4 = UINT32
     */
    STDMETHOD_( UINT32, GetCharacterSize )( THIS ) CONSTMETHOD PURE;
};

#ifdef __cplusplus
    #include <iosfwd>

    std::ostream& operator <<( std::ostream& o, const IHXString& );
    std::istream& operator >>( std::istream& is, IHXString& );
#endif

DEFINE_SMART_PTR(IHXString);

// $EndPrivate.



#endif // _IHXSTRING_H_
