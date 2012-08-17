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

#include "hxtypes.h"
#include "hxcom.h"
#include "hxcomm.h"
#include "hxmon.h"
#include "hxcore.h"
#include "hxengin.h"
#include "hxclsnk.h"
#include "hxgroup.h"
#include "hxstrutl.h"
#include "hxstring.h"
#include "hxtick.h"
#include <stdio.h>

#include "clientcontext.h"
#include "advisesink.h"

namespace WebCore{

	WebkitClientAdviseSink::WebkitClientAdviseSink(IUnknown* pUnknown, WebkitClientContext* pContext)
		: m_lRefCount(0)
		  , m_pUnknown(NULL)
		  , m_pRegistry(NULL)
		  , m_pPlayer(NULL)
		  , m_bOpened(FALSE)
		  , m_bPrepared(FALSE)
		  , m_bSendPlayBackComplete(FALSE)
		  , m_lDuration(-1)
		  , m_ulFileDurationFromHeader(0)
		  , m_ulPos(0)
		  , m_pWebkitContext(NULL)
		  , m_ulStartTime(0)
		  , m_ulWidth(0)
		  , m_ulHeight(0)
		  , m_bIsLiveOrAdaptiveHTTP(FALSE)
	{
		m_pWebkitContext = pContext;
		m_pUnknown = pUnknown;

		HX_ADDREF(m_pWebkitContext);
		HX_ADDREF(m_pUnknown);

		if (m_pUnknown)
		{
			m_pUnknown->QueryInterface(IID_IHXRegistry, (void**)&m_pRegistry);
			m_pUnknown->QueryInterface(IID_IHXPlayer, (void**)&m_pPlayer);
		}

		if (m_pPlayer)
		{
			IHXGroupManager* pGroupMgr = NULL;
			if(HXR_OK == m_pPlayer->QueryInterface(IID_IHXGroupManager, (void**)&pGroupMgr))
			{
				pGroupMgr->AddSink((IHXGroupSink*)this);
				HX_RELEASE(pGroupMgr);
			}

			IHXClientStateAdviseSinkControl* pControl=NULL;
			if(HXR_OK == m_pPlayer->QueryInterface(IID_IHXClientStateAdviseSinkControl, (void**)&pControl))
			{
				pControl->AddClientStateAdviseSink(this);
				HX_RELEASE(pControl);
			}

			HX_RESULT retVal = HXR_FAIL;
			retVal = m_pPlayer->AddAdviseSink((IHXClientAdviseSink*)this);
			m_ulStartTime = HX_GET_BETTERTICKCOUNT();
			printf("HelixOverWebkit [%s] [%s] [%d] WebkitClientAdviseSink::AddAdviseSink() returned %d\n", __FILE__, __FUNCTION__, __LINE__, retVal);

		}	
	}

	WebkitClientAdviseSink::~WebkitClientAdviseSink(void)
	{
		HX_RELEASE(m_pRegistry);
		HX_RELEASE(m_pPlayer);
		HX_RELEASE(m_pUnknown);
		HX_RELEASE(m_pWebkitContext);
	}

	// *** IUnknown methods ***
	STDMETHODIMP WebkitClientAdviseSink::QueryInterface(REFIID riid, void** ppvObj)
	{
		if (IsEqualIID(riid, IID_IUnknown))
		{
			AddRef();
			*ppvObj = (IUnknown*)(IHXClientAdviseSink*)this;
			return HXR_OK;
		}
		else if (IsEqualIID(riid, IID_IHXClientAdviseSink))
		{
			AddRef();
			*ppvObj = (IHXClientAdviseSink*)this;
			return HXR_OK;
		}
		else if (IsEqualIID(riid, IID_IHXGroupSink))
		{
			AddRef();
			*ppvObj = (IHXGroupSink*)this;
			return HXR_OK;
		}
		else if (IsEqualIID(riid, IID_IHXSiteWatcher))
		{
			AddRef();
			*ppvObj = (IHXSiteWatcher*)this;
			return HXR_OK;
		}

		*ppvObj = NULL;
		return HXR_NOINTERFACE;
	}

	STDMETHODIMP_(ULONG32) WebkitClientAdviseSink::AddRef()
	{
		return InterlockedIncrement(&m_lRefCount);
	}

	STDMETHODIMP_(ULONG32) WebkitClientAdviseSink::Release()
	{
		if (InterlockedDecrement(&m_lRefCount) > 0)
		{
			return m_lRefCount;
		}

		delete this;
		return 0;
	}

	/*
	 *	IHXClientAdviseSink methods
	 */
	STDMETHODIMP
		WebkitClientAdviseSink::OnPosLength(UINT32 ulPosition, UINT32 ulLength)
		{
			//printf("HelixOverWebkit [%s] [%s] [%d]"WebkitClientAdviseSink::OnPosLength len = %d", ulLength);
			if (ulLength && (INT32)ulLength != m_lDuration)
			{
				printf("HelixOverWebkit [%s] [%s] [%d] WebkitClientAdviseSink::OnPosLength New duration: len = %d\n", 
						__FILE__, __FUNCTION__, __LINE__, ulLength);
				m_lDuration = (INT32)ulLength;
				m_pWebkitContext->SetDuration(m_lDuration);
			}
			if(m_lDuration == ulPosition)
			{
				if(m_pWebkitContext->m_bErrorFlag)
				{
					//m_pWebkitContext->SendEvent(Webkit::MEDIA_PLAYER_STOPPED);
					m_pWebkitContext->m_bErrorFlag = FALSE;
				}
				else if(!m_bSendPlayBackComplete)
				{
					m_bSendPlayBackComplete = TRUE;
					//hijack the Webkit::MEDIA_PLAYBACK_COMPLETE event is in track looping mode
					if(!m_pWebkitContext->IsTrackLooping())
					{
						//Set the player state to MEDIA_PLAYER_PLAYBACK_COMPLETE, as it maybe called
						//by onTimeSync, then set the player state and send event will be unsync
						//m_pWebkitContext->SetPlayerState(MEDIA_PLAYER_PLAYBACK_COMPLETE);
						//m_pWebkitContext->SendEvent(Webkit::MEDIA_PLAYBACK_COMPLETE);
					}
				}
			}
			else
			{
				m_bSendPlayBackComplete = FALSE;
			}
			m_ulPos = ulPosition;

			return HXR_OK;
		}

	STDMETHODIMP WebkitClientAdviseSink::OnPresentationOpened()
	{
		m_bOpened = TRUE;
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::OnPresentationClosed()
	{
		printf("HelixOverWebkit [%s] [%s] [%d] WebkitClientAdviseSink::OnPresentationClose\n", __FILE__, __FUNCTION__, __LINE__);
		if(m_bOpened)
		{
			//m_pWebkitContext->SetPlayerState(MEDIA_PLAYER_PLAYBACK_COMPLETE);
			m_bOpened = FALSE;
		}
		m_bPrepared = FALSE;
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::OnStatisticsChanged(void)
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::OnPreSeek(ULONG32	ulOldTime, ULONG32 ulNewTime)
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::OnPostSeek(ULONG32 ulOldTime, ULONG32 ulNewTime)
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::OnStop(void)
	{
		m_pWebkitContext->SetPlayerState(MEDIA_PLAYER_STOPPED);
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::OnPause(ULONG32 ulTime)
	{
		m_ulPos = ulTime;
		m_pWebkitContext->SetPlayerState(MEDIA_PLAYER_PAUSED);    
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::OnBegin(ULONG32 ulTime)
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::OnBuffering(ULONG32 ulFlags, UINT16 unPercentComplete)
	{
		//m_pWebkitContext->SendEvent(Webkit::MEDIA_BUFFERING_UPDATE, unPercentComplete);
		if(unPercentComplete == 100)
		{
			m_pWebkitContext->SeekCompleteEvent();
			if ((m_playerState == HX_CLIENT_STATE_PREFETCHED) && m_pWebkitContext->IsTrackLooping() && m_pWebkitContext->IsPlayerStarted())
			{
				m_pPlayer->Begin();
			}
		}
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::OnContacting(const char* pHostName)
	{
		printf("HelixOverWebkit [%s] [%s] [%d] WebkitClientAdviseSink::OnContacting\n", __FILE__, __FUNCTION__, __LINE__);
		return HXR_OK;
	}

	// IHXClientStateAdviseSink
	STDMETHODIMP WebkitClientAdviseSink::OnStateChange(UINT16 uOldState, UINT16 uNewState)
	{
		printf("HelixOverWebkit [%s] [%s] [%d] WebkitClientAdviseSink::OnStateChanged %d->%d\n", 
				__FILE__, __FUNCTION__, __LINE__, uOldState, uNewState);

		// make new state available to the Webkit MediaPlayer
		TranslateToWebkitState(uNewState);

		if (!m_bPrepared && uNewState == HX_CLIENT_STATE_PREFETCHED)
		{
			printf("HelixOverWebkit [%s] [%s] [%d] WebkitClientAdviseSink::OnStateChanged Sending prepared messages\n", __FILE__, __FUNCTION__, __LINE__);
			m_bPrepared = TRUE;
			// get duration and video size when connected to the source
			GetClipInfo();
			//m_pWebkitContext->SendEvent(Webkit::MEDIA_PREPARED);
		}
		else if (m_bPrepared && uNewState == HX_CLIENT_STATE_READY)
		{
			m_bPrepared = FALSE;
		}

		return HXR_OK;
	}

	void WebkitClientAdviseSink::SendClipProperties( IHXValues* pHeader )
	{
		if (pHeader == NULL)
		{
			return ;
		}

		const char* pName = NULL;
		UINT32 ulValue = 0, ulWidth = 0, ulHeight = 0;
		if(HXR_OK == pHeader->GetFirstPropertyULONG32(pName, ulValue))
		{
			do
			{
				if(strcmp(pName, "Duration") == 0)
				{
					if (ulValue && ulValue >= m_ulFileDurationFromHeader)
					{
						printf("HelixOverWebkit [%s] [%s] [%d] WebkitClientAdviseSink::SendClipProperties New duration: len = %d\n", __FILE__, __FUNCTION__, __LINE__, ulValue);
						m_ulFileDurationFromHeader = ulValue;
						m_pWebkitContext->SetDuration(ulValue);
					}
				}
				else if(strcmp(pName, "Width") == 0)
				{
					m_pWebkitContext->SetVideoWidth(ulValue);
					ulWidth = ulValue;
				}
				else if(strcmp(pName, "Height") == 0)
				{
					m_pWebkitContext->SetVideoHeight(ulValue);
					ulHeight = ulValue;
				}
			}
			while(HXR_OK == pHeader->GetNextPropertyULONG32(pName, ulValue));
		}

#ifndef Webkit_RELEASE_1
		if( ulWidth > 1 && ulHeight > 1 &&
				!(ulWidth == m_ulWidth && ulHeight == m_ulHeight) )
		{
			m_ulWidth  = ulWidth;
			m_ulHeight = ulHeight;
			//m_pWebkitContext->SendEvent(Webkit::MEDIA_SET_VIDEO_SIZE, m_ulWidth, m_ulHeight);
		}
#endif
	}

	void WebkitClientAdviseSink::GetClipInfo()
	{
		// Get HXSource and try to get clip infor. 
		UINT32 sourceCount = m_pPlayer->GetSourceCount();	
		for (UINT32 sourceID = 0; sourceID < sourceCount; sourceID ++)
		{
			// get HXSource
			IUnknown* pUnkSource = NULL;
			IHXStreamSource* pStreamSrc = NULL;

			if (HXR_OK != m_pPlayer->GetSource (sourceID, pUnkSource))
			{
				continue;
			}

			IHXValues* pFileHeader = NULL;
			if ( HXR_OK == pUnkSource->QueryInterface( IID_IHXValues, ( void ** )&pFileHeader ) )
			{
				/*
				IHXBuffer* pAutoLoopingBuf = NULL;
				if ( HXR_OK == pFileHeader->GetPropertyBuffer( "Webkit_LOOP", pAutoLoopingBuf ) )
				{
					if ( 0 == strcmp( pAutoLoopingBuf->GetBuffer(), "true" ) )
					{
						m_pWebkitContext->SetAutoLooping( TRUE );
					}
				}
				HX_RELEASE( pAutoLoopingBuf );
				*/

				static const char * PROPERTY_NAMES[] = {
					"LiveStream",
					"HttpLiveStream",
					"AdaptiveHTTP"
				};
				UINT32 ulTmp = 0;
				for (int i = 0; i < sizeof(PROPERTY_NAMES)/sizeof(const char *); ++i)
				{
					pFileHeader->GetPropertyULONG32(PROPERTY_NAMES[i], ulTmp);
					if (ulTmp)
					{
						m_bIsLiveOrAdaptiveHTTP = TRUE;
						break;
					}
				}
			}
			HX_RELEASE( pFileHeader );

			pUnkSource->QueryInterface(IID_IHXStreamSource, (void **)&pStreamSrc);

			HX_RELEASE(pUnkSource);

			if (!pStreamSrc)
			{
				continue;
			}

			UINT32 num_streams = pStreamSrc->GetStreamCount();
			// get information from Streams
			for (UINT32 streamID = 0; streamID < num_streams ; streamID++)
			{
				IUnknown* pUnkStream = NULL;

				if (HXR_OK == pStreamSrc->GetStream(streamID, pUnkStream))
				{
					IHXStream* pStream = NULL;

					if (HXR_OK == pUnkStream->QueryInterface(IID_IHXStream, (void**)&pStream))
					{
						IHXValues* pStreamHdr = pStream->GetHeader();
						if (pStreamHdr)
						{
							SendClipProperties(pStreamHdr);
						}
						HX_RELEASE(pStreamHdr);
					}
					HX_RELEASE(pStream);
				}
				HX_RELEASE(pUnkStream);
			}
			HX_RELEASE(pStreamSrc);
		}
	}

	/*
	 *  IHXGroupSink methods
	 */
	STDMETHODIMP WebkitClientAdviseSink::GroupAdded(UINT16 uGroupIndex, IHXGroup* pGroup)
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::GroupRemoved(UINT16 uGroupIndex, IHXGroup* pGroup)
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::AllGroupsRemoved()
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::TrackAdded(UINT16 uGroupIndex, UINT16 uTrackIndex,  IHXValues* pTrack)
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::TrackRemoved(UINT16  uGroupIndex, UINT16 uTrackIndex, IHXValues* pTrack)
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::TrackStarted(UINT16 uGroupIndex, UINT16 uTrackIndex, IHXValues* pTrack)
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::TrackStopped(UINT16 uGroupIndex, UINT16 uTrackIndex, IHXValues* pTrack)
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::CurrentGroupSet(UINT16 uGroupIndex, IHXGroup* pGroup)
	{
		return HXR_OK;
	}

	/*
	 *  IHXPassiveSiteWatcher methods
	 */
	STDMETHODIMP WebkitClientAdviseSink::AttachSite(IHXSite* pSite)
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::DetachSite()
	{
		return HXR_OK;
	}

	STDMETHODIMP WebkitClientAdviseSink::ChangingPosition(HXxPoint posOld, REF(HXxPoint) posNew)
	{
		return HXR_OK;
	}

	STDMETHODIMP
		WebkitClientAdviseSink::ChangingSize(HXxSize sizeOld, REF(HXxSize) sizeNew)
		{
			if ( sizeNew.cx > 1 && sizeNew.cy > 1 &&
					!(m_ulWidth == sizeNew.cx && m_ulHeight == sizeNew.cy) && 
					m_bIsLiveOrAdaptiveHTTP)
			{
				m_ulWidth  = sizeNew.cx;
				m_ulHeight = sizeNew.cy;
				m_pWebkitContext->SetVideoWidth(sizeNew.cx);
				m_pWebkitContext->SetVideoHeight(sizeNew.cy);
				/* workaround for cts r8:
				 * don't send MEDIA_SET_VIDEO_SIZE if isn't live streaming
				 * and we have sent the video size, because changing video
				 * size is not allowed in cts r8. See the following source
				 * codes (extracted from cts_r8_source/tests/tests/media/src/Webkit/media/cts/MediaPlayerTestBase.java, line 119):
				 mMediaPlayer.setOnVideoSizeChangedListener(new MediaPlayer.OnVideoSizeChangedListener() {
				 @Override
				 public void onVideoSizeChanged(MediaPlayer mp, int w, int h) {
				 mOnVideoSizeChangedCalled.signal();
				 assertEquals(width, w);
				 assertEquals(height, h);
				 }
				 });
				 */
				//m_pWebkitContext->SendEvent(Webkit::MEDIA_SET_VIDEO_SIZE, m_ulWidth, m_ulHeight);
			}
			return HXR_OK;
		}

	// TODO: check whether it's needed, webkit doesn't have state machine
	void WebkitClientAdviseSink::TranslateToWebkitState(UINT16 uState)
	{    
		   int eWebkitPlayerState = MEDIA_PLAYER_STATE_ERROR;

		   switch (uState)
		   	   {
		   case HX_CLIENT_STATE_READY:
		   eWebkitPlayerState = MEDIA_PLAYER_INITIALIZED;
		   break;
		   case HX_CLIENT_STATE_CONNECTING:
		   case HX_CLIENT_STATE_CONNECTED:
		   case HX_CLIENT_STATE_OPENING:
		   case HX_CLIENT_STATE_OPENED:
		   case HX_CLIENT_STATE_PREFETCHING:
		   eWebkitPlayerState = MEDIA_PLAYER_PREPARING;
		   break;
		   case HX_CLIENT_STATE_PREFETCHED:
		   eWebkitPlayerState = MEDIA_PLAYER_PREPARED;
		   break;
		   case HX_CLIENT_STATE_PLAYING:
		   eWebkitPlayerState = MEDIA_PLAYER_STARTED;
		   break;
		   case HX_CLIENT_STATE_PAUSED:
		   eWebkitPlayerState = MEDIA_PLAYER_PAUSED;
		   break;
		   case HX_CLIENT_STATE_SEEKING:
		// no change
		break;
		}

		if (eWebkitPlayerState != MEDIA_PLAYER_STATE_ERROR)
		{
		m_pWebkitContext->SetPlayerState(eWebkitPlayerState);
		}
		m_playerState = uState;
	}

}

#endif
