/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: stringtostringlistmap.h,v 1.2 2007/07/06 20:35:02 jfinnecy Exp $
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

#ifndef CHXMAPSTRINGTOSTRINGLIST_H
#define CHXMAPSTRINGTOSTRINGLIST_H

// This class implements a map which maps
// a string to a list of strings, as in:
//
// "animals"   -> {"dog", "cat", "parakeet"}
// "carBrands" -> {"Toyota", "Chevrolet", "Honda"}
//
//
// The nice thing about this map is that it handles
// all the string management for you. You don't have
// to worry about allocating the strings or destructing
// them.
//
// You specify upon creation whether you want to allow
// duplicates in the string list.


#include "hxtypes.h"
#include "hxstring.h"
#include "hxslist.h"
#include "chxmapstringtoob.h"


class CHXStringToStringListMap
{
public:
    CHXStringToStringListMap(HXBOOL bAllowDuplicatesInList = FALSE, HXBOOL bCaseSensitive = FALSE);
    ~CHXStringToStringListMap();

    int       GetCount() const; // number of keys in the map
    HXBOOL    IsKeyPresent(const char* pszKey) const; // Is this key in the map?
    int       GetStringCount(const char* pszKey) const; // for this key, number of strings in list
    HXBOOL    IsEmpty() const; // TRUE if no keys in map
    HXBOOL    IsEmpty(const char* pszKey) const; // TRUE if no strings in list for this key
    HX_RESULT AddStringToList(const char* pszKey, const char* pszStr);
    HX_RESULT GetFirstString(const char* pszKey, CHXString* pStr, LISTPOSITION& rPos);
    HX_RESULT GetNextString(const char* pszKey, CHXString* pStr, LISTPOSITION& rPos);
    void      RemoveAll();
private:
    HXBOOL            m_bAllowDuplicates;
    HXBOOL            m_bCaseSensitive;
    CHXMapStringToOb* m_pMap;
};

#endif /* #ifndef CHXMAPSTRINGTOSTRINGLIST_H */
