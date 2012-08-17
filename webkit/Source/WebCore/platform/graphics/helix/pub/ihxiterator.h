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

#ifndef _IHXITERATOR_H_
#define _IHXITERATOR_H_


/*!
    @singletype IHXIterator
    @abstract Traversal over an IHXContainer
    @discussion This Interface is supported by objects that also support a Container interface.
    The corresponding container for this iterator will invalidate its position when applicable.
 */
 
#include "hxcom.h"
#include "hxcomptr.h"

// $Private;

// {E636D295-FF70-11d3-94F0-00D0B7103550}
DEFINE_GUID( IID_IHXIterator, 0xe636d295, 0xff70, 0x11d3, 0x94, 0xf0, 0x0, 0xd0, 0xb7, 0x10, 0x35, 0x50 );

DECLARE_INTERFACE_( IHXIterator, IUnknown )
{
    /*!
	@function   Increment 
	@abstract   Increments Iterator position to next container element.
	@discussion Equivalent of operator++
	@result     HXR_OK on success. Fails if incremented past container's end position.
     */
    STDMETHOD ( Increment ) ( THIS ) PURE;
    /*!
	@function   Decrement
	@abstract   Decrements Iterator position to previous container element.
	@discussion Equivalent of operator--
	@result     HXR_OK on success. Fails if decremented before container's beginning position.
     */
    STDMETHOD ( Decrement ) ( THIS ) PURE;
    /*!
	@function   IncrementBy
	@abstract   Increments Iterator position by given increment.
	@discussion Equivalent of operator+=( increment )
	@param	    increment [in] Increment by amount.
	@result     HXR_OK on success. Fails if incremented past container's end position.
     */
    STDMETHOD ( IncrementBy ) ( THIS_ INT32 increment ) PURE;
    /*!
	@function   DecrementBy
	@abstract   Decrements Iterator position to previous container element.
	@discussion Equivalent of operator-=( increment )
	@param	    decrement [in] Decrement by amount.
	@result     HXR_OK on success. Fails if decremented before container's beginning position.
     */
    STDMETHOD ( DecrementBy ) ( THIS_ INT32 decrement ) PURE;
    /*!
	@function   SetToBegin
	@abstract   Sets Iterator based on state returned by its Container's BeginContainer() method.
	@result     HXR_OK on success. Fails if beginning cannot be determined.
     */
    STDMETHOD ( SetToBegin ) ( THIS ) PURE;
    /*!
	@function   SetToEnd
	@abstract   Sets Iterator based on state returned by its Container's EndContainer() method.
	@result     HXR_OK on success. Fails if end cannot be determined.
     */
    STDMETHOD ( SetToEnd ) ( THIS ) PURE;
    /*!
	@function   IsValid
	@abstract   Checks validity of iterator state
	@result	    Returns TRUE if this iterator points to a valid Position. (Note that end is a valid position )
     */
    STDMETHOD_( HXBOOL, IsValid ) ( THIS ) CONSTMETHOD PURE;
    /*!
	@function   IsDereferenceable
	@abstract   Checks validity of iterator position
	@result	    Returns TRUE if this iterator points to a Position that can be dereferenced. (Note that the end position cannot be dereferenced. )
     */
    STDMETHOD_( HXBOOL, IsDereferenceable ) ( THIS ) CONSTMETHOD PURE;
    /*!
	@function   GetAt 
	@abstract   Returns object at the iterator's current position
	@discussion Equivalent of operator*
	@param	    ppIUnknown [out] Returns the IUnknown at this iterator's current Position. AddRef()'d
	@result     HXR_OK on success. Fails if current Position is not dereferenceable.
     */
    STDMETHOD ( GetAt ) ( THIS_ IUnknown** ppIUnknown ) CONSTMETHOD PURE;
    /*!
	@function   IsEqual
	@abstract   Compares the state of two iterators
	@param	    pIIterator [in] Iterator for comparison
	@result	    Returns TRUE iff the two iterators point to the same position in the same container
     */
    STDMETHOD_( HXBOOL, IsEqual ) ( THIS_ IHXIterator* pIIterator ) CONSTMETHOD PURE;
    /*!
	@function   Clone
	@abstract   Produce a copy of this iterator.
	@param	    ppIIterator [out] Cloned iterator.
	@result     HXR_OK on success.
     */
    STDMETHOD ( Clone ) ( THIS_ IHXIterator** ppIIterator ) CONSTMETHOD PURE;
};

DEFINE_SMART_PTR(IHXIterator);

// $EndPrivate.



#endif // _IHXITERATOR_H_
