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

#ifndef _IHXCONFIGURATORITERATOR_H_
#define _IHXCONFIGURATORITERATOR_H_


/*!
    @singletype IHXConfiguratorIterator
    @abstract Traversal over an IHXConfigurator
    @discussion 
 */
 
#include "hxcom.h"
#include "hxcomptr.h"

_INTERFACE IHXString;
_INTERFACE IHXAscii7String;

// $Private;

// {AE92A683-3AC0-42bb-855A-224C78792014}
DEFINE_GUID( IID_IHXConfiguratorIterator, 0xae92a683, 0x3ac0, 0x42bb, 0x85, 0x5a, 0x22, 0x4c, 0x78, 0x79, 0x20, 0x14);

DECLARE_INTERFACE_( IHXConfiguratorIterator, IUnknown )
{
    /*!
	@function   Increment 
	@abstract   Increments Iterator position to next configurator element.
	@discussion Equivalent of operator++
	@result     HXR_OK on success. Fails if incremented past configurator's end position.
     */
    STDMETHOD ( Increment ) ( THIS ) PURE;
    /*!
	@function   Decrement
	@abstract   Decrements Iterator position to previous configurator element.
	@discussion Equivalent of operator--
	@result     HXR_OK on success. Fails if decremented before configurator's beginning position.
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
	@abstract   Sets Iterator based on state returned by its configurator's BeginConfigurator() method.
	@result     HXR_OK on success. Fails if beginning cannot be determined.
     */
    STDMETHOD ( SetToBegin ) ( THIS ) PURE;
    /*!
	@function   SetToEnd
	@abstract   Sets Iterator based on state returned by its configurator's EndConfigurator(() method.
	@result     HXR_OK on success. Fails if end cannot be determined.
     */
    STDMETHOD ( SetToEnd ) ( THIS ) PURE;
    /*!
	@function   GetAt 
	@abstract   Returns the string at the iterator's current position
	@discussion Equivalent of operator*
	@param	    ppIUnknown [out] Returns the IUnknown at this iterator's current Position. AddRef()'d
	@result     HXR_OK on success. Fails if current Position is not dereferenceable.
     */
    STDMETHOD ( GetAt ) ( THIS_ IHXString** ppIUnknown ) CONSTMETHOD PURE;
    /*!
	@function   GetKey
	@abstract   Returns the key at the iterator's current position
	@param	    ppKey Set to point to the key. Note that the underlying configurator controls this 
		    memory which may vanish if the element is deleted from the configurator. If you 
		    need to hang on to this for any length of time make a copy of it.
	@result     HXR_OK on success. Fails if current Position is not dereferenceable.
     */
    STDMETHOD ( GetKey ) ( THIS_ IHXAscii7String** ppIKey) CONSTMETHOD PURE;
    /*!
	@function   IsEqual
	@abstract   Compares the state of two iterators
	@param	    pIIterator [in] Iterator for comparison
	@result	    Returns TRUE iff the two iterators point to the same position in the same configurator
     */
    STDMETHOD_( HXBOOL, IsEqual ) ( THIS_ const IHXConfiguratorIterator* pIIterator ) CONSTMETHOD PURE;
    /*!
	@function   Clone
	@abstract   Produce a copy of this iterator.
	@param	    ppIIterator [out] Cloned iterator.
	@result     HXR_OK on success.
     */
    STDMETHOD ( Clone ) ( THIS_ IHXConfiguratorIterator** ppIIterator ) CONSTMETHOD PURE;
};


DEFINE_SMART_PTR(IHXConfiguratorIterator);


// $EndPrivate.



#endif // _IHXCONFIGURATORITERATOR_H_
