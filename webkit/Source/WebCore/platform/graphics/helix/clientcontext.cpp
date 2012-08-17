/* ***** BEGIN LICENSE BLOCK *****
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
 * terms of the GNU General Public License Version 2 or later (the
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


#include "config.h"

#if ENABLE(VIDEO) && USE(GSTREAMER)
#include "MediaPlayerPrivateHelix.h"
#include "hxtypes.h"
#include "hxwintyp.h"
#include "hxcom.h"
#include "hxcomm.h"
#include "hxwin.h"
#include "hxbuffer.h"
#include "hxmangle.h"
#include "hxclsnk.h"
#include "hxgroup.h"
#include "hxerror.h"
#include "hxprefs.h"
#include "hxstrutl.h"

#include "advisesink.h"
//#include "errorsink.h"
//#include "sitesupplier.h"
//#include "authmanager.h"
#include "clientcontext.h"
//#include <utils/RefBase.h>

namespace WebCore{

	WebkitClientContext::WebkitClientContext()
		: m_lRefCount(0)
		  , m_pClientSink(NULL)
		  //    , m_pErrorSink(NULL)
		  , m_bErrorFlag(FALSE)
		  , m_bAutoLooping(FALSE)
		  , m_bSeekCompleteNeedSend(FALSE)
	{
	}

	WebkitClientContext::~WebkitClientContext()
	{
		Close();
	};

	void WebkitClientContext::Init(IUnknown* pUnknown, MediaPlayerPrivateHelix* pPlayer)
	{
		//char* pszCipher = NULL;

		printf("HelixOverWebkit [%s] [%s] [%d] WebkitClientContext::Init", __FILE__, __FUNCTION__, __LINE__);

		m_pMediaPlayer = pPlayer;
		m_pClientSink = new WebkitClientAdviseSink(pUnknown, this);
		//m_pErrorSink = new WebkitErrorSink(pUnknown, this);

		//HX_ADDREF(m_pErrorSink);
		HX_ADDREF(m_pClientSink);

		/*
		   IHXSiteWatcher* pSiteWatcher = NULL;
		   m_pClientSink->QueryInterface(IID_IHXSiteWatcher,(void**)&pSiteWatcher);
		   if (pSiteWatcher)
		   {
		   m_pSiteSupplier->AddSiteWatcher(pSiteWatcher);
		   }
		   HX_RELEASE(pSiteWatcher);
		   */
	}

	void WebkitClientContext::Close()
	{
		HX_RELEASE(m_pClientSink);
		//    HX_RELEASE(m_pErrorSink);
	}

	/*
	 * IUnknown methods
	 */
	STDMETHODIMP WebkitClientContext::QueryInterface(REFIID riid, void** ppvObj)
	{
		if (IsEqualIID(riid, IID_IUnknown))
		{
			AddRef();
			*ppvObj = this;
			return HXR_OK;
		}
		else if (m_pClientSink && 
				m_pClientSink->QueryInterface(riid, ppvObj) == HXR_OK)
		{
			return HXR_OK;
		}
		/*
		   else if (m_pErrorSink && 
		   m_pErrorSink->QueryInterface(riid, ppvObj) == HXR_OK)
		   {
		   return HXR_OK;
		   }
		   else if(m_pAuthMgr &&
		   m_pAuthMgr->QueryInterface(riid, ppvObj) == HXR_OK)
		   {
		   return HXR_OK;
		   }
		   else if(m_pSiteSupplier &&
		   m_pSiteSupplier->QueryInterface(riid, ppvObj) == HXR_OK)
		   {
		   return HXR_OK;
		   }
		   */
		*ppvObj = NULL;
		return HXR_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG32) WebkitClientContext::AddRef()
	{
		return InterlockedIncrement(&m_lRefCount);
	}

	STDMETHODIMP_(ULONG32) WebkitClientContext::Release()
	{
		if (InterlockedDecrement(&m_lRefCount) > 0)
		{
			return m_lRefCount;
		}

		delete this;
		return 0;
	}

	void WebkitClientContext::SendEvent(int id, int ext1, int ext2)
	{
		//m_pMediaPlayer->sendEvent(id, ext1, ext2);
		//TODO: is there a report mechanism for webkit system
	}

	void WebkitClientContext::SetVideoWidth(int width)
	{
		//printf("HelixOverWebkit [%s] [%s] [%d]"WebkitClientContext::SetVideoWidth(%d)", width);
		//m_pMediaPlayer->setVideoWidth(width);
	}

	void WebkitClientContext::SetVideoHeight(int height)
	{
		//printf("HelixOverWebkit [%s] [%s] [%d]"WebkitClientContext::SetVideoHeight(%d)", height);
		//m_pMediaPlayer->setVideoHeight(height);
	}

	void WebkitClientContext::SetDuration(int duration)
	{
		printf("HelixOverWebkit [%s] [%s] [%d] WebkitClientContext::SetDuration(%d)\n",  __FILE__, __FUNCTION__, __LINE__, duration);
		m_pMediaPlayer->setDuration(duration);
	}

	void WebkitClientContext::SetPlayerState(int state)
	{
		m_pMediaPlayer->setPlayerState(state);
	}

	void WebkitClientContext::SeekCompleteEvent()
	{
		//TODO: how to implement seek operation
		/*
		   if (m_bSeekCompleteNeedSend)
		   {
		   SendEvent(Webkit::MEDIA_SEEK_COMPLETE);
		   m_bSeekCompleteNeedSend = false;
		   }
		   */
	}

	HXBOOL WebkitClientContext::IsTrackLooping()
	{
		//return m_pMediaPlayer->IsTrackLooping();
		return false;
	}

	HXBOOL WebkitClientContext::IsPlayerStarted()
	{
		return m_pMediaPlayer->IsPlayerStarted();
	}

}

#endif

