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

#ifndef _IHXAUTOUPGRADE_H_
#define _IHXAUTOUPGRADE_H_

#include "hxcom.h"
//#include "hxupgrd.h"

//  Forward Declarations
typedef _INTERFACE   IHXComponentDescriptorsCollection  IHXComponentDescriptorsCollection;
typedef _INTERFACE   IHXUpgradeCollection		IHXUpgradeCollection;
typedef _INTERFACE   IHXValues		                IHXValues;
typedef _INTERFACE   IHXBuffer		                IHXBuffer;

typedef enum 
{
    AU_UNKNOWN = 0,
    AU_PENDING,
    AU_REQUESTING,
    AU_DOWNLOADING,
    AU_UNPACKING,
    AU_INSTALLING,
    AU_PAUSED,
    AU_DONE,
    AU_ABORTED,
    AU_ERROR
} AU_STATUS;

typedef struct _HXUpgradeRequestInfo
{
    UINT32			    m_ulUpgradeType;
    IHXBuffer*			    m_pProductName;
    IHXBuffer*			    m_pProductVersion;
    IHXUpgradeCollection*	    m_pUpgradeCollection;
    IHXBuffer*			    m_pInstallerArgs;
} HXUpgradeRequestInfo;

/****************************************************************************
 * 
 *  Interface:
 * 
 *	IHXAutoUpgradeAdviseSink
 * 
 *  Purpose:
 * 
 *	This interface provides methods to receive AU status
 * 
 *  IID_IHXAutoUpgradeAdviseSink:
 * 
 *	{00005002-0901-11d1-8B06-00A024406D59}
 * 
 */
DEFINE_GUID(IID_IHXAutoUpgradeAdviseSink,   0x00005002, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
				           0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE   IHXAutoUpgradeAdviseSink

DECLARE_INTERFACE_(IHXAutoUpgradeAdviseSink, IUnknown)
{
    /*
     *  IHXAutoUpgradeAdviseSink methods
     */
    STDMETHOD(OnComponents)     (THIS_
                                 IHXComponentDescriptorsCollection* pComponents) PURE;

    STDMETHOD(OnStatus)	        (THIS_
                                 AU_STATUS  status, UINT32 PercentDone) PURE;

    STDMETHOD(OnError)          (THIS_
                                 HX_RESULT  error) PURE;
};

/****************************************************************************
 * 
 *  Interface:
 * 
 *	IHXAutoUpgrade
 * 
 *  Purpose:
 * 
 *	This interface provides methods to perform AU
 * 
 *  IID_IHXAutoUpgrade:
 * 
 *	{00005001-0901-11d1-8B06-00A024406D59}
 * 
 */
DEFINE_GUID(IID_IHXAutoUpgrade,   0x00005001, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
				 0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE   IHXAutoUpgrade

DECLARE_INTERFACE_(IHXAutoUpgrade, IUnknown)
{
    /*
     *  IHXAutoUpgrade methods
     */
    STDMETHOD(Prepare)	        (THIS_
                                 HXUpgradeRequestInfo* pClientRequestInfo) PURE;

    STDMETHOD(AddAdviseSink)    (THIS_
                                 IHXAutoUpgradeAdviseSink* pSink) PURE;
    STDMETHOD(RemoveAdviseSink) (THIS_
                                 IHXAutoUpgradeAdviseSink* pSink) PURE;

    STDMETHOD(Resume)           (THIS) PURE;
    STDMETHOD(Pause)            (THIS) PURE;
    STDMETHOD(Cancel)           (THIS) PURE;
    STDMETHOD(Close)            (THIS) PURE;

    STDMETHOD(GetStatus)        (THIS_
                                 REF(AU_STATUS) status) PURE;
    STDMETHOD(GetError)         (THIS_
                                 REF(HX_RESULT) error) PURE;
};

/****************************************************************************
 * 
 *  Interface:
 * 
 *	IHXAutoUpgradeManager
 * 
 *  Purpose:
 * 
 *	This interface provides methods to initiate AU request
 * 
 *  IID_IHXAutoUpgradeManager:
 * 
 *	{00005000-0901-11d1-8B06-00A024406D59}
 * 
 */
DEFINE_GUID(IID_IHXAutoUpgradeManager,   0x00005000, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
				         0xa0, 0x24, 0x40, 0x6d, 0x59);

#define CLSID_IHXAutoUpgradeManager IID_IHXAutoUpgradeManager

#undef  INTERFACE
#define INTERFACE   IHXAutoUpgradeManager

DECLARE_INTERFACE_(IHXAutoUpgradeManager, IUnknown)
{
    /*
     *  IHXAutoUpgradeManager methods
     */

    /************************************************************************
     *	Method:
     *	    IHXAutoUpgradeManager::CreateAutoUpgrade
     */
    STDMETHOD(CreateAutoUpgrade)    (THIS_
                                     REF(IHXAutoUpgrade*) pAU) PURE;

    STDMETHOD(AddAutoUpgrade)       (THIS_
                                     IHXAutoUpgrade* pAU) PURE;

    STDMETHOD(RemoveAutoUpgrade)    (THIS_
                                     IHXAutoUpgrade* pAU) PURE;

    STDMETHOD(Close)                (THIS) PURE;
};

#include "hxcomptr.h"
DEFINE_SMART_PTR(IHXAutoUpgradeAdviseSink)
DEFINE_SMART_PTR(IHXAutoUpgrade)
DEFINE_SMART_PTR(IHXAutoUpgradeManager)

#endif /* _IHXAUTOUPGRDE_H_ */
