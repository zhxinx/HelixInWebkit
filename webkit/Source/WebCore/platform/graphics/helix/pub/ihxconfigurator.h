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


#ifndef _IHXCONFIGURATOR_H_
#define _IHXCONFIGURATOR_H_

#include "hxcom.h"
#include "hxcomptr.h"

_INTERFACE IHXBuffer;
_INTERFACE IHXValues;
_INTERFACE IHXContainer;
_INTERFACE IHXFileObject;
_INTERFACE IHXString;
_INTERFACE IHXAscii7String;
_INTERFACE IHXConfiguratorIterator;

/*!
    @interface IHXConfigurator
    @abstract Storage for key / value pairs that represent an XML description. 
      The key is an ascii char*, the value is an IHXString. For convenience, there 
      are methods to work with other value types - e.g. buffers, ints, doubles & bools 
      however all of these are just other ways to put information into the basic 
      ascii string -> IHXString map. I.e. setting an int property under a given 
      key will result in an IHXString being set for that key. The value of the IHXString 
      will be a text representation of the int.
 */

// $Private;

// {00003710-0901-11d1-8b06-00a024406d59}
DEFINE_GUID( IID_IHXConfigurator, 0x00003710, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 0xa0, 0x24, 0x40, 0x6d, 0x59 );


DECLARE_INTERFACE_( IHXConfigurator, IUnknown )
{
    /*!
	@function   GetType
	@abstract   Returns the tag name of this description.
	@result	    Returns the C style tag name.
     */
    STDMETHOD_( const char*, GetType ) ( THIS ) CONSTMETHOD PURE;

    /*!
	@function   SetType
	@abstract   Sets the tag name of this configurator / XML element.
	@param	    pName [in] Tag name of this description. Name is copied by object.
	@result	    Returns successful result if name is copied.
     */
    STDMETHOD ( SetType ) ( THIS_ const char* pName ) PURE;
    
    /*!
	@function   SetFileObject
	@abstract   Set the corresponding file object used in the construction of this object.
	@param	    pIFileObject [in] Corresponding file object.
	@result	    Returns successful result if file object exists.
     */
    STDMETHOD ( SetFileObject ) ( THIS_ IHXFileObject* pIFileObject ) PURE;

    /*!
	@function   GetFileObject
	@abstract   Get the corresponding file object used in the construction of this object.
	@param	    ppIFileObject [out] Corresponding file object.
		    NOTE: *ppIFileObject is AddRef()'d.
	@result     Returns successful result if an IHXFileObject was returned.
     */
    STDMETHOD ( GetFileObject ) ( THIS_ IHXFileObject** ppIFileObject ) CONSTMETHOD PURE;

    /*!
	@function   GetValues
	@abstract   Get the backend storarge interface for this object.
		    XXXSEH: Please don't use GetValues(). Use the Get/Set... methods instead. This implementation detail may not endure.
	@param	    ppIValues [out] Backend storage.
		    NOTE: *ppIValues is AddRef()'d.
	@result     Returns successful result if an IHXValues was returned.
     */
    STDMETHOD ( GetValues ) ( THIS_ IHXValues** ppIValues ) CONSTMETHOD PURE;

    /*!
	@function   SetValues
	@abstract   Set the backend storarge interface for this object.
		    Called internally by Gemini due to the XML parser communicating attributes through this interface.
	@param	    pIValues [in] Backend storage.
	@result	    Returns successful result if backend storage exists.
     */
    STDMETHOD ( SetValues ) ( THIS_ IHXValues* pIValues ) PURE;

    /*!
	@function   GetParent
	@abstract   Returns this object's parent container.
	@param	    ppIParent [out] Parent container of this object.
		    NOTE: *ppIParent is AddRef()'d.
	@result	    Returns successful result if parent exists.
     */
    STDMETHOD ( GetParent ) ( THIS_ IHXContainer** ppIParent ) CONSTMETHOD PURE;

    /*!
	@function   SetParent
	@abstract   Set this object's parent container.
	@param	    pIParent [in] The parent for this configurator.
	@result	    Successful if the parent is correctly set.
     */
    STDMETHOD ( SetParent ) ( THIS_ IHXContainer* pIParent ) PURE;

    /*!
	@function   CopyProperties
	@abstract   Turns this configurator into a copy of the supplied configurator. Any 
		    properties currently in this configurator will be discarded.
		    pIFromConfigurator's properties are copied NOT merely AddRef()'d.
	@param	    pIFromConfigurator Copy from this configurator's properties.
	@result	    HX_RESULT
     */
    STDMETHOD ( CopyProperties ) ( THIS_ IHXConfigurator* pIFromConfigurator ) PURE;

    /*!
	@function   MergeProperties
	@abstract   Merge the properties from pIFromConfigurator.
		    The properties are copied NOT merely AddRef()'d.
		    If duplicate's exist, pIFromConfigurator's attributes will prevail.
	@param	    pIFromConfigurator Merge from this configurator's properties.
	@result	    HX_RESULT
     */
    STDMETHOD ( MergeProperties ) ( THIS_ IHXConfigurator* pIFromConfigurator ) PURE;

    /*!
	@function   GetStringProperty
	@abstract   Get a property from this configurator as an ascii string in a buffer.
	@param	    pKey Key of property to get.
	@param	    pIBuffer [out]Buffer to set property to. 
	@result	    HX_RESULT
     */
    STDMETHOD ( GetStringProperty ) ( THIS_ const char* pKey, IHXBuffer** pIBuffer ) CONSTMETHOD PURE;

    /*!
	@function   SetStringProperty
	@abstract   Set a property for this configurator. 
	@param	    pKey Key of property to set.
	@param	    pIBuffer [in] New property value. This is assumed to be an ascii string and will
		    be converted to an IHXString for internal storage.
	@result	    HX_RESULT
     */
    STDMETHOD ( SetStringProperty ) ( THIS_ const char* pKey, IHXBuffer* pIBuffer ) PURE;

    /*!
	@function   GetIntProperty
	@abstract   Get a property from this configurator as an integer. This function looks up the IHXString 
		    corresponding to the key and converts it into an integer. No attempt is made to validate 
		    whether the value is really an integer.
	@param	    pKey Key of property to get.
	@param	    pValue [out]Integer Value returned.
	@result	    HX_RESULT
     */
    STDMETHOD ( GetIntProperty ) ( THIS_ const char* pKey, INT32* pValue ) CONSTMETHOD PURE;

    /*!
	@function   SetIntProperty
	@abstract   Set an integer property for this configurator.
	@param	    pKey Key of property to set.
	@param	    pValue [in] New integer value. This will be converted to an IHXString internally.
	@result	    HX_RESULT
     */
    STDMETHOD ( SetIntProperty ) ( THIS_ const char* pKey, INT32 value ) PURE;

    /*!
	@function   GetDoubleProperty
	@abstract   Get a property from this configurator as a double. This function looks up the IHXString 
		    corresponding to the key and converts it into a double. No attempt is made to validate 
		    whether the value is really a double.
	@param	    pKey Key of property to get.
	@param	    pValue [out]Double value returned.
	@result	    HX_RESULT
     */
    STDMETHOD ( GetDoubleProperty ) ( THIS_ const char* pKey, double* pValue ) CONSTMETHOD PURE;

    /*!
	@function   SetDoubleProperty
	@abstract   Set a double property for this configurator.
	@param	    pKey Key of property to set.
	@param	    pValue [in] New double value. This will be converted to an IHXString internally.
	@result	    HX_RESULT
     */
    STDMETHOD ( SetDoubleProperty ) ( THIS_ const char* pKey, double value ) PURE;

    /*!
	@function   GetBoolProperty
	@abstract   Get a property from this configurator as a boolean. This function looks up the IHXString 
		    corresponding to the key and converts it into a boolean. No attempt is made to validate 
		    whether the value is really a boolean.
	@param	    pKey Key of property to get.
	@param	    pValue [out]Boolean value returned.
	@result	    HX_RESULT
     */
    STDMETHOD ( GetBoolProperty ) ( THIS_ const char* pKey, HXBOOL* pValue ) CONSTMETHOD PURE;

    /*!
	@function   SetBoolProperty
	@abstract   Set a boolean property for this configurator.
	@param	    pKey Key of property to set.
	@param	    pValue [in] New boolean value.
	@result	    HX_RESULT
     */
    STDMETHOD ( SetBoolProperty ) ( THIS_ const char* pKey, HXBOOL value ) PURE;

    /*!
	@function   SetTypeAsString
	@abstract   Sets the tag name of this description as a (possibly shared) string. This 
		    function is provided for efficiency - since in a typical XML file there will be 
		    multiple occurances of tag names being able to share them saves memory.
	@param	    pIName [in] Tag name of this description.
	@result	    Returns successful result if name is correctly set.
     */
    STDMETHOD ( SetTypeAsString ) ( THIS_ IHXAscii7String* pIName ) PURE;

    /*!
	@function   SetIHXStringProperty
	@abstract   Adds a given key / value mapping to the configurator
	@param	    pKey Key of property to set.
	@param	    pIString The string to set.
	@result	    HX_RESULT
     */
    STDMETHOD ( SetIHXStringProperty ) ( THIS_ const char* pKey, IHXString* pIString ) PURE;

    /*!
	@function   SetIHXStringPropertyKeyAsString
	@abstract   Set a string property in the configurator.
	@param	    pIKey The key of the property. By making this an IHXAscii7String the same 
		    key text can be shared across multiple properties, thus reducing memory 
		    usage.
	@param	    pIString [in] The string value.
	@result	    HX_RESULT
     */
    STDMETHOD ( SetIHXStringPropertyKeyAsString ) ( THIS_ IHXAscii7String* pIKey, IHXString* pIString ) PURE;

    /*!
	@function   GetIHXStringProperty
	@abstract   Gets a given IHXString value given a key.
	@param	    pKey Key of property to get.
	@param	    ppIString [out]The string corresponding to the key.
	@result	    HX_RESULT - HXR_OK if the key was present, HXR_FAIL if it wasn't.
     */
    STDMETHOD ( GetIHXStringProperty ) ( THIS_ const char* pKey, IHXString** ppIString ) CONSTMETHOD PURE;

    /*!
	@function   BeginContainer
	@param	    ppIIterator [out] Returns an iterator positioned at the beginning element in the 
		    configurator. AddRef()'d. Note that calling any non-const method on this container 
		    will invalidate the iterator.
		    The order of iteration through the properties of the configurator is undefined and should not be relied on.
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( BeginConfigurator ) ( THIS_ IHXConfiguratorIterator** ppIIterator ) CONSTMETHOD PURE;
    /*!
	@function   EndContainer
	@param	    ppIIterator [out] Returns an iterator positioned one past the end element in the
		    configurator. AddRef()'d. Note that calling any non-const method on this container 
		    will invalidate the iterator.
		    The order of iteration through the properties of the configurator is undefined and should not be relied on.
	@result	    HXR_OK on success.	
     */
    STDMETHOD ( EndConfigurator ) ( THIS_ IHXConfiguratorIterator** ppIIterator ) CONSTMETHOD PURE;

    /*!
	@function   ErasePropertyFromKey
	@abstract   Erases a property given its key
	@param	    pKey The key of the property to erase
	@result	    Success if the given property exists and was correctly erased, failure otherwise.
     */
    STDMETHOD ( ErasePropertyFromKey )( THIS_ const char* pKey ) PURE;
    
    /*!
	@function   ClearConfigurator
	@abstract   Removes all properties from this configurator
	@result	    HXR_OK if successful
     */
    STDMETHOD ( ClearConfigurator )( THIS ) PURE;
    
    /*!
	@function   GetNumProperties
	@abstract   Gets the number of properties stored in the configurator
	@result	    The number of properties stored in this configurator
     */
    STDMETHOD_( UINT32, GetNumProperties )( THIS ) CONSTMETHOD PURE;

    /*!
	@function   SetUniqueIHXStringPropertyKeyAsString
	@abstract   Quickly set a string property in the configurator. This method does not check for
		    duplicates in the propert store, so use carefully.
	@param	    pIKey The key of the property. By making this an IHXAscii7String the same 
		    key text can be shared across multiple properties, thus reducing memory 
		    usage.
	@param	    pIString [in] The string value.
	@result	    HX_RESULT
     */
    STDMETHOD ( SetUniqueIHXStringPropertyKeyAsString ) ( THIS_ IHXAscii7String* pIKey, IHXString* pIString ) PURE;

};

DEFINE_SMART_PTR(IHXConfigurator);

// $EndPrivate.



#endif /* _IHXCONFIGURATOR_H_ */

