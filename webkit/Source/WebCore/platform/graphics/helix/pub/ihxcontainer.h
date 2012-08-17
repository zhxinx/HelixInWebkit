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

#ifndef _IHXCONTAINER_H_
#define _IHXCONTAINER_H_


/*!
    @singletype IHXContainer
    @abstract Specifies access to a collection of objects.
    @discussion This interface is implemented by objects that support management of a container of IUnknown interfaces.
    The intention of this design is to provide an STL like container in COM.
 */
 
#include "hxcom.h"
#include "hxcomptr.h"

_INTERFACE IHXIterator;

// $Private;

// {1F278782-B3DB-11d3-8802-00902790299C}
DEFINE_GUID( IID_IHXContainer, 0x1f278782, 0xb3db, 0x11d3, 0x88, 0x2, 0x0, 0x90, 0x27, 0x90, 0x29, 0x9c );

/*!
    @interface IHXContainer
 */
DECLARE_INTERFACE_( IHXContainer, IUnknown )
{
    /*!
	@function   IsContainerEmpty
	@result	    Returns TRUE if this Container contains NO IUnknown's.
     */
    STDMETHOD_( HXBOOL, IsContainerEmpty ) ( THIS ) CONSTMETHOD PURE;
    /*!
	@function   GetSizeOfContainer
	@result	    Number of IUnknown's this Container contains.
     */
    STDMETHOD_( UINT32, GetSizeOfContainer ) ( THIS ) CONSTMETHOD PURE;

    /*!
	@function   BeginContainer
	@param	    ppIIterator [out] Returns Iterator positioned at beginning element in Container. AddRef()'d
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( BeginContainer ) ( THIS_ IHXIterator** ppIIterator ) CONSTMETHOD PURE;
    /*!
	@function   EndContainer
	@param	    ppIIterator [out] Returns Iterator positioned one past end element in Container. AddRef()'d
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( EndContainer ) ( THIS_ IHXIterator** ppIIterator ) CONSTMETHOD PURE;
    /*!
	@function   FindInContainer
	@param	    pIUnknown [in] IUnknown to find in Container.
	@param	    ppIIterator [out] Returns Iterator positioned at found element in Container. AddRef()'d
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( FindInContainer ) ( THIS_ IUnknown* pIUnknown, IHXIterator** ppIIterator ) CONSTMETHOD PURE;

    /*!
	@function   GetAt
	@param	    index [in] Zero based index into Container.
	@param	    ppIUnknown [out] IUnknown at given index to return.
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( GetAt ) ( THIS_ UINT32 index, IUnknown** ppIUnknown ) CONSTMETHOD PURE;
    /*!
	@function   GetFront
	@abstract   Returns the IUnknown from the beginning of this Container.
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( GetFront ) ( THIS_ IUnknown** ppIUnknown ) CONSTMETHOD PURE;
    /*!
	@function   GetBack
	@abstract   Returns the IUnknown from the end of this Container.
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( GetBack ) ( THIS_ IUnknown** ppIUnknown ) CONSTMETHOD PURE;

    /*!
	@function   InsertBefore
	@abstract   Inserts an IUnknown immediately before the indicated position within this Container.
	@param	    pIPosition [in] Insert pINewIUnknown before this position.
	@param	    pINewUnknown [in] New IUnknown to insert.
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( InsertBefore ) ( THIS_ const IHXIterator* pIPosition, IUnknown* pINewIUnknown ) PURE;
    /*!
	@function   PushFront
	@abstract   Adds an IUnknown to the beginning of this Container.
	@param	    pINewIUnknown [in] New IUnknown to add.
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( PushFront ) ( THIS_ IUnknown* pINewIUnknown ) PURE;
    /*!
	@function   PushBack
	@abstract   Adds an IUnknown to the end of this Container.
	@param	    pINewIUnknown [in] New IUnknown to add.
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( PushBack ) ( THIS_ IUnknown* pINewIUnknown ) PURE;
	
    /*!
	@function   ReplaceAt
	@abstract   Replaces an IUnknown at the indicated position within this Container.
	@param	    pIPosition [in] Replace with pINewIUnknown at this position.
	@param	    pINewIUnknown [in] IUnknown to replace with.
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( ReplaceAt ) ( THIS_ const IHXIterator* pIPosition, IUnknown* pINewIUnknown ) PURE;

    /*!
	@function   EraseAt
	@abstract   Removes the IUnknown at the specified position.
	@param	    pIPosition [in] Position of IUnknown to remove.
     */
    STDMETHOD ( EraseAt ) ( THIS_ IHXIterator* pIPosition ) PURE;
    /*!
	@function   PopFront
	@abstract   Removes the IUnknown from the beginning of this Container.
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( PopFront ) ( THIS ) PURE;
    /*!
	@function   PopBack
	@abstract   Removes the IUnknown from the end of this Container.
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( PopBack ) ( THIS ) PURE;

    /*!
	@function   ClearContainer
	@abstract   Removes all this Container's contents.
     */
    STDMETHOD_( void, ClearContainer ) ( THIS ) PURE;
};

DEFINE_SMART_PTR(IHXContainer);

// $EndPrivate.




#endif // _IHXCONTAINER_H_
