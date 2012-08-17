/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: chxinifreader.h,v 1.1.2.2 2008/08/12 18:58:28 ping Exp $
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
 * ***** END LICENSE BLOCK ***** */

#ifndef _CHXINIFREADER_H_
#define _CHXINIFREADER_H_

#include "hxcom.h"
#include "hxtypes.h"
#include "hxstring.h"

typedef union
{
    int         i;
    CHXString   *s;
} _IniVal_t;

class CHXIniFileReader
{
public:
    CHXIniFileReader( );
    virtual ~CHXIniFileReader( );

    // Files
    virtual HXBOOL LoadFile( const char *fileName );

    // Key values
    virtual HX_RESULT GetIntVal( const char *groupName, const char *keyName, int& val);
    virtual HX_RESULT GetStrVal( const char *groupName, const char *keyName, CHXString*& val);
    virtual HX_RESULT SetIntVal( const char *groupName, const char *keyName, int value );
    virtual HX_RESULT SetStrVal( const char *groupName, const char *keyName, CHXString* value);

private:
    // Private
    enum { INVALID, GROUP, NULVAL, INTVAL, STRVAL };

    HX_RESULT ReadLine(char *buf, int max, FILE *file);

    int CountKeys( const char *groupName );
    char* FindGroup( const char *groupName );
    int FindKey( const char *groupName, const char *keyName );
    int IdentifyLine( const char *buf );

    static HXBOOL ReadId( const char *buf, int *pos, char *dst );
    static int ReadInt( const char *buf, int *pos );
    static CHXString* ReadStr( const char *buf, int *pos );
    static void TrimLeft( const char *buf, int *pos );
    static HXBOOL ValidId( char chr );
    static HXBOOL ValidIdInit( char chr );

    // Values
    int m_groupx;
    int m_groupc;
    char **m_groupName;

    int m_keyx;
    int m_keyc;
    char **m_keyGroup;
    char **m_keyName;

    enum { NUL, INT, STR };
    int *m_keyType;
    _IniVal_t *m_keyVal;
};

#endif

