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

#ifndef _IHXDOWNLOADMANAGER_H_
#define _IHXDOWNLOADMANAGER_H_

#include "hxcom.h"

typedef _INTERFACE   IHXBuffer		    IHXBuffer;

typedef enum 
{
    DOWNLOAD_PENDING = 0,
    DOWNLOAD_DOWNLOADING,
    DOWNLOAD_PAUSED,
    DOWNLOAD_COMPLETED,
    DOWNLOAD_ABORTED,
    DOWNLOAD_ERROR
} DOWNLOAD_STATUS;

/****************************************************************************
 * 
 *  Interface:
 * 
 *	IHXDownloadAdviseSink
 * 
 *  Purpose:
 * 
 *	This interface provides methods to receive Download status
 * 
 *  IID_IHXDownloadAdviseSink:
 * 
 *	{00007002-0901-11d1-8B06-00A024406D59}
 * 
 */
DEFINE_GUID(IID_IHXDownloadAdviseSink,   0x00007002, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
				         0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE   IHXDownloadAdviseSink

DECLARE_INTERFACE_(IHXDownloadAdviseSink, IUnknown)
{
    /*
     *  IHXDownloadAdviseSink methods
     */
    STDMETHOD(OnDownloadStatus)	        (THIS_
                                         DOWNLOAD_STATUS  status) PURE;

    STDMETHOD(OnDownloadProgress)	(THIS_
                                         UINT32 ulCurrentSize, UINT32 ulTotalSize) PURE;

    STDMETHOD(OnDownloadError)          (THIS_
                                         HX_RESULT  error) PURE;
};

/****************************************************************************
 * 
 *  Interface:
 * 
 *	IHXDownload
 * 
 *  Purpose:
 * 
 *	This interface provides methods to perform download
 * 
 *  IID_IHXDownload:
 * 
 *	{00007001-0901-11d1-8B06-00A024406D59}
 * 
 */
DEFINE_GUID(IID_IHXDownload,   0x00007001, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
			       0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE   IHXDownload

DECLARE_INTERFACE_(IHXDownload, IUnknown)
{
    /*
     *  IHXDownload methods
     */
    STDMETHOD(DownloadToMem)	 (THIS_
                                  const char* pszURL,
                                  IHXBuffer* pBuffer) PURE;

    STDMETHOD(DownloadToFile)	 (THIS_
                                  const char* pszURL,
                                  const char* pszPath) PURE;

    STDMETHOD(AddAdviseSink)    (THIS_
                                 IHXDownloadAdviseSink* pSink) PURE;
    STDMETHOD(RemoveAdviseSink) (THIS_
                                 IHXDownloadAdviseSink* pSink) PURE;

    STDMETHOD(Resume)           (THIS) PURE;
    STDMETHOD(Pause)            (THIS) PURE;
    STDMETHOD(Cancel)           (THIS) PURE;
    STDMETHOD(Close)            (THIS) PURE;

    STDMETHOD(GetURL)           (REF(const char*) pszURL) PURE;
    STDMETHOD(GetProgress)      (REF(UINT32) ulCurrentSize, REF(UINT32) ulTotalSize) PURE;
    STDMETHOD(GetStatus)        (THIS_
                                 REF(DOWNLOAD_STATUS) status) PURE;
    STDMETHOD(GetError)         (THIS_
                                 REF(HX_RESULT) error) PURE;
    STDMETHOD_(IHXBuffer*, GetBuffer)(THIS) PURE;   
};

/****************************************************************************
 * 
 *  Interface:
 * 
 *	IHXDownloadManager
 * 
 *  Purpose:
 * 
 *	This interface provides methods to initiate download request
 * 
 *  IID_IHXDownloadManager:
 * 
 *	{00007000-0901-11d1-8B06-00A024406D59}
 * 
 */
DEFINE_GUID(IID_IHXDownloadManager,   0x00007000, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
				      0xa0, 0x24, 0x40, 0x6d, 0x59);

#define CLSID_IHXDownloadManager IID_IHXDownloadManager

#undef  INTERFACE
#define INTERFACE   IHXDownloadManager

DECLARE_INTERFACE_(IHXDownloadManager, IUnknown)
{
    /*
     *  IHXDownloadManager methods
     */
    STDMETHOD(CreateDownload)	(THIS_
                                 REF(IHXDownload*) pDownload) PURE;

    STDMETHOD(AddDownload)      (THIS_
                                 IHXDownload* pDownload) PURE;

    STDMETHOD(InsertDownload)   (THIS_
                                 UINT32 ulIndex,
                                 IHXDownload* pDownload) PURE;

    STDMETHOD(RemoveDownload)   (THIS_
                                 IHXDownload* pDownload) PURE;

    STDMETHOD(RemoveDownloadAt) (THIS_
                                 UINT32 ulIndex) PURE;

    STDMETHOD_(UINT32, GetCount)(THIS) PURE;

    STDMETHOD(GetDownloadAt)    (THIS_
                                 UINT32 ulIndex,
                                 REF(IHXDownload*) pDownload) PURE;

    STDMETHOD(Close)            (THIS) PURE;
};

#include "hxcomptr.h"
DEFINE_SMART_PTR(IHXDownloadAdviseSink)
DEFINE_SMART_PTR(IHXDownload)
DEFINE_SMART_PTR(IHXDownloadManager)

#endif /* _IHXDOWNLOADMANAGER_H_ */
