/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: ihxmedpltfm.h,v 1.10.2.3.8.2 2011/05/25 03:48:29 xzhao Exp $
 *
 * Portions Copyright (c) 1995-2004 RealNetworks, Inc. All Rights Reserved.
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

#ifndef _IHXMEDPLTFM_H_
#define _IHXMEDPLTFM_H_

#include "hxcom.h"

typedef _INTERFACE	IUnknown			IUnknown;
typedef _INTERFACE	IHXClientEngine			IHXClientEngine;
typedef _INTERFACE	IHXMediaPlatform		IHXMediaPlatform;

#if defined(_WINDOWS) || defined(_SYMBIAN) || defined(_BREW)
# define HX_MEDIA_PLATFORM_DLLNAME   "hxmedpltfm.dll"
#elif defined(_UNIX)
# define HX_MEDIA_PLATFORM_DLLNAME   "hxmedpltfm.so"
#elif defined(_MAC_UNIX)
# define HX_MEDIA_PLATFORM_DLLNAME   "hxmedpltfm.bundle"
#else
# error "Need to define for your platform"
#endif

STDAPI HXMediaPlatformOpen(void);
STDAPI HXCreateMediaPlatform(IHXMediaPlatform** ppIHXMediaPlatform);
STDAPI HXMediaPlatformClose(void);

#ifdef HELIX_CONFIG_USE_EXTENDED
STDAPI HXCreateMediaPlatformAndExtension(IHXMediaPlatform** ppIHXMediaPlatform, IUnknown** ppUnkExtension);
STDAPI HXCreateMediaPlatformEx(IHXMediaPlatform** ppIHXMediaPlatform);
STDAPI HXMediaPlatformCloseEx(void);
#endif

// legacy
STDAPI CreateEngine(IHXClientEngine** ppClientEngine);
STDAPI CloseEngine(IHXClientEngine* pEngine);
STDAPI SetDLLAccessPath(const char* pszPath);

typedef HX_RESULT (HXEXPORT_PTR FPHXMEDIAPLATFORMOPEN)(void);
typedef HX_RESULT (HXEXPORT_PTR FPHXCREATEMEDIAPLATFORM)(IHXMediaPlatform** ppIHXMediaPlatform);
typedef HX_RESULT (HXEXPORT_PTR FPHXMEDIAPLATFORMCLOSE) (void);

#ifdef HELIX_CONFIG_USE_EXTENDED
typedef HX_RESULT (HXEXPORT_PTR FPHXCREATEMEDIAPLATFORMANDEXTENSION)(IHXMediaPlatform** ppIHXMediaPlatform, IUnknown** ppUnkExtension);
typedef HX_RESULT (HXEXPORT_PTR FPHXCREATEMEDIAPLATFORMEX)(IHXMediaPlatform** ppIHXMediaPlatform);
typedef HX_RESULT (HXEXPORT_PTR FPHXMEDIAPLATFORMCLOSEEX) (void);
#endif

typedef HX_RESULT (HXEXPORT_PTR FPRMCREATEENGINE)(IHXClientEngine** ppEngine);
typedef HX_RESULT (HXEXPORT_PTR FPRMCLOSEENGINE) (IHXClientEngine*  pEngine);
typedef HX_RESULT (HXEXPORT_PTR FPRMSETDLLACCESSPATH) (const char* pszPath);

/****************************************************************************
 * 
 *  Interface:
 * 
 *	IHXMediaPlatform
 * 
 *  Purpose:
 * 
 *	This interface provides methods to access Media Platform 
 * 
 *  IID_IHXMediaPlatform:
 * 
 *	{0000080-0901-11d1-8B06-00A024406D59}
 * 
 */
DEFINE_GUID(IID_IHXMediaPlatform,   0x00000080, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
				    0xa0, 0x24, 0x40, 0x6d, 0x59);

#define CLSID_IHXMediaPlatform IID_IHXMediaPlatform

#undef  INTERFACE
#define INTERFACE   IHXMediaPlatform

DECLARE_INTERFACE_(IHXMediaPlatform, IUnknown)
{
    /*
     *  IUnknown methods
     */
    STDMETHOD(QueryInterface)	(THIS_
				REFIID riid,
				void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)	(THIS) PURE;

    STDMETHOD_(ULONG32,Release)	(THIS) PURE;

    /*
     *  IHXMediaPlatform methods
     */

    /************************************************************************
     *	Method:
     *	    IHXMediaPlatform::GetVersion
     *	Purpose:
     *	    Retrieve the version of Media Platform:
     *	    bits:   24 – 31 major version
     *		    16 – 23 minor version
     *		     8 – 15 release number
     *		     0 – 7  build number
     */
    STDMETHOD(GetVersion)	(THIS_
			         UINT32* pVersion) PURE;

    /************************************************************************
     *	Method:
     *	    IHXMediaPlatform::AddPluginPath
     *	Purpose:
     *	    Add plugin path to be loaded by the media platform. It can be 
     *      called multiple times if there are more than one plugin path 
     *      needs to be loaded. 
     *	    
     *	    If AddPluginPath is called before Init(), then it won't be taken
     *	    effect till Init() is called.     
     */
    STDMETHOD(AddPluginPath)	(THIS_
				 const char* pszName,
				 const char* pszPath) PURE;

    /************************************************************************
     *	Method:
     *	    IHXMediaPlatform::Init
     *	Purpose:
     *	    Initialize the media platform. If pContext is not NULL, then 
     *	    pContext will be used as the extension to the media platform own
     *	    context.
     */
    STDMETHOD(Init)		(THIS_
				 IUnknown* pContext) PURE;

    /************************************************************************
     *	Method:
     *	    IHXMediaPlatform::Close
     *	Purpose:
     *	    Close the media platform to its un-initialized state
     */
    STDMETHOD(Close)		(THIS) PURE;

    /************************************************************************
     *	Method:
     *	    IHXMediaPlatform::Reset
     *	Purpose:
     *	    Reset the media platform, it not only closes the media platform
     *	    but also clears persistent information maintained by the platform. 
     *
     *	    If pContext is not NULL, the platform will QI for the persistent 
     *	    storage interface (IHXPreferences) from pContext and clear it up. 
     *
     *	    Note, the caller needs to pass the same pContext to Reset() as it 
     *	    passes to Init() if Init() is called earlier. On the other hand, 
     *	    the caller is allowed to call Reset() without Init() if the caller 
     *	    only wants to clear up the persistent information, one example is 
     *	    the uninstaller of the application.
     *
     *      If bPlatformOnly is TRUE(by default), then only the platform will be reset. 
     *      Otherwise, all the plugins loaded by the Platform will also be reset.
     */
    STDMETHOD(Reset)		(THIS_
				 IUnknown* pContext,
				 HXBOOL	   bPlatformOnly) PURE;

    /************************************************************************
     *	Method:
     *	    IHXMediaPlatform::Purge
     *	Purpose:
     *	    Force unloading of any unused plugins by the platform
     */
    STDMETHOD(Purge)		(THIS) PURE;

    /************************************************************************
     *	Method:
     *	    IHXMediaPlatform::CreateChildContext
     *	Purpose:
     *	    Create a new media platform context from the current context
     */
    STDMETHOD(CreateChildContext)   (THIS_
				     IHXMediaPlatform** ppChildContext) PURE;
};

/****************************************************************************
 * 
 *  Interface:
 * 
 *	IHXMediaPlatformKicker
 * 
 *  Purpose:
 * 
 *	This interface is intended for systems that do not support asynchronous 
 *	timer. For systems that support asynchronous timer, the interface will
 *	be no-op when it’s called.
 * 
 *  IID_IHXMediaPlatformKicker:
 * 
 *	{0000081-0901-11d1-8B06-00A024406D59}
 * 
 */
DEFINE_GUID(IID_IHXMediaPlatformKicker, 0x00000081, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
					0xa0, 0x24, 0x40, 0x6d, 0x59);

#define CLSID_IHXMediaPlatformKicker IID_IHXMediaPlatformKicker

#undef  INTERFACE
#define INTERFACE   IHXMediaPlatformKicker

DECLARE_INTERFACE_(IHXMediaPlatformKicker, IUnknown)
{
    /*
     *  IUnknown methods
     */
    STDMETHOD(QueryInterface)	(THIS_
				REFIID riid,
				void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)	(THIS) PURE;

    STDMETHOD_(ULONG32,Release)	(THIS) PURE;

    /*
     *  IHXMediaPlatformKicker methods
     */

    /************************************************************************
     *	Method:
     *	    IHXMediaPlatformKicker::Kick
     *	Purpose:
     *	    Kick the scheduler on a specified thread
     *
     *  Returns:
     *      Returns the number of *MICRO*seconds that a caller
     *      Should sleep before calling Kick() again. That is,
     *      Kick() wants to be called after that many microseconds
     *      have expired.
     */
    STDMETHOD(Kick) (THIS_
                     UINT32  ulThreadID,
                     UINT32* pulSuggestedSleep) PURE;
};

/****************************************************************************
 * 
 *  Interface:
 * 
 *	IHXMediaPlatformKicker2
 * 
 *  Purpose:
 * 
 * 
 *  IID_IHXMediaPlatformKicker2:
 * 
 *	{a16a8692-15df-49b9-866b-31fae2680856}
 * 
 */
DEFINE_GUID(IID_IHXMediaPlatformKicker2, 0xa16a8692, 0x15df, 0x49b9, 0x86, 0x6b, 0x31, 
				         0xfa, 0xe2, 0x68, 0x08, 0x56);

#define CLSID_IHXMediaPlatformKicker2 IID_IHXMediaPlatformKicker2

#undef  INTERFACE
#define INTERFACE   IHXMediaPlatformKicker2

DECLARE_INTERFACE_(IHXMediaPlatformKicker2, IUnknown)
{
    /*
     *  IUnknown methods
     */
    STDMETHOD(QueryInterface)	(THIS_
				REFIID riid,
				void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)	(THIS) PURE;

    STDMETHOD_(ULONG32,Release)	(THIS) PURE;

    /*
     *  IHXMediaPlatformKicker2 methods
     */
    /************************************************************************
     *	Method:
     *	    IHXMediaPlatformKicker2::StartOnDemandKick
     *	Purpose:
     *      This function should be called before Kick2 and Wait2, to do some prepare work
     *
     */
    STDMETHOD(StartOnDemandKick)      (THIS_
		                      UINT32  ulThreadID) PURE;

    /************************************************************************
     *	Method:
     *	    IHXMediaPlatformKicker2::Kick2
     *	Purpose:
     *	    Kick all scheduler in the list, and check minimum delta due time to the most recent
     *  Callback in all schedulers. 
     *
     *  Returns:
     *      Return minimal due time to next recent CB in specified scheduler list
     */
    STDMETHOD(Kick2)      (THIS_
		           UINT32  ulThreadID,
                           UINT32* pulSuggestedSleep) PURE;
    /************************************************************************
     *	Method:
     *	    IHXMediaPlatformKicker2::Wait2
     *	Purpose:
     *  Wait for passed-in due time, and if it is signalled, re-evaluate due time in specified 
     *  scheduler list and may wait again; if it is time-out or immediate CB needs to be processed
     *  return immediately.
     *  Caller should check Kick2 return value to ensure ulThreadID is correct
     *
     *  Returns:
     *      Return IHXEvent::Wait's result
     */
    STDMETHOD(Wait2)      (THIS_
                           UINT32 ulThreadID,
                           UINT32 ulDueTime) PURE;
};
#include "hxcomptr.h"
DEFINE_SMART_PTR(IHXMediaPlatform)
DEFINE_SMART_PTR(IHXMediaPlatformKicker)
DEFINE_SMART_PTR(IHXMediaPlatformKicker2)

#endif /* _IHXMEDPLTFM_H_ */

