/* ***** BEGIN LICENSE BLOCK *****
 * 
 * Portions Copyright (c) 1995-2006 RealNetworks, Inc. All Rights Reserved.
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

#ifndef _IHXEMBEDDEDUI_H
#define _IHXEMBEDDEDUI_H

#include "hxcom.h"
#include "hxcomptr.h"
#include "hxstring.h"
#include "ihxpckts.h"

struct EmbeddedUIInfo
{
    EmbeddedUIInfo(const char* pszURL, 
                   IUnknown*   pUnknown,
                   IHXValues*  pValues)
    {
        szContentURL = pszURL;

        pEmbeddedUnknown = pUnknown;
        pEmbeddedValues = pValues;

        HX_ADDREF(pEmbeddedUnknown);
        HX_ADDREF(pEmbeddedValues);
    }

    ~EmbeddedUIInfo()
    {
	HX_RELEASE(pEmbeddedUnknown);
        HX_RELEASE(pEmbeddedValues);
    }

    CHXString   szContentURL;       // Actual content URL the UI embedded within
    IUnknown*   pEmbeddedUnknown;   // Pointer to DRM
    IHXValues*  pEmbeddedValues;    // Embedded UI stuff
};

// {A788F545-ACCA-40f2-9F28-633F3056643F}
DEFINE_GUID(IID_IHXEmbeddedUIAdviseSink, 0xa788f545, 0xacca, 0x40f2, 0x9f, 0x28, 0x63, 0x3f, 0x30, 0x56, 0x64, 0x3f);

// {35FD37BB-500D-4465-A4C0-D0160D2CC235}
DEFINE_GUID(IID_IHXEmbeddedUI,           0x35fd37bb, 0x500d, 0x4465, 0xa4, 0xc0, 0xd0, 0x16, 0xd, 0x2c, 0xc2, 0x35);

DECLARE_INTERFACE_(IHXEmbeddedUIAdviseSink, IUnknown)
{
    STDMETHOD(OnEmbeddedUIReady)   (THIS_ EmbeddedUIInfo* pInfo) PURE;
    STDMETHOD(OnEmbeddedUIDataReady) (THIS_ IHXValues* pDataCollection) PURE;
};

DECLARE_INTERFACE_(IHXEmbeddedUI, IUnknown)
{
    STDMETHOD(SetEmbeddedUI)   (THIS_ EmbeddedUIInfo* pInfo) PURE;
    STDMETHOD(SetEmbeddedUIData) (THIS_ IHXValues* pDataCollection) PURE;

    STDMETHOD(AddSink) (THIS_ IHXEmbeddedUIAdviseSink* pSink) PURE;

    STDMETHOD(RemoveSink) (THIS_ IHXEmbeddedUIAdviseSink* pSink) PURE;
};

DEFINE_SMART_PTR(IHXEmbeddedUI);
DEFINE_SMART_PTR(IHXEmbeddedUIAdviseSink);

#endif // _IHXEMBEDDEDUI_H
