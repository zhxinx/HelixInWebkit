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

#ifndef _UPGPIDS_H_
#define _UPGPIDS_H_

#define UPGP_PROTOCOL_NAME	"UPGP"
#define UPGP_PROTOCOL_VERSION	"0.5"

// Request/Response types
#define UPGP_REQ_MISSING_PLUGIN	    0
#define UPGP_REQ_AUTOMATIC          1
#define UPGP_REQ_MANUAL_ALLPRODUCTS 2
#define UPGP_REQ_UPGRADE_EXISTING   3	// Reserved
#define UPGP_REQ_CHANNELS           4
#define UPGP_REQ_MANUAL_ONE_PRODUCT 5
#define UPGP_REQ_MSG_BACKGROUND	    6
#define UPGP_REQ_MSG_MANUAL	    7

#define UPGP_RESP_UPGRADE           64
#define UPGP_RESP_UPSELL            65	// Reserved
#define UPGP_RESP_MSG		    66

//Flags that will be found in the header of the UPGP_DATA_RESP_HEADER block.
#define UPGP_RESP_FLAGS_SILENT	    0x10

// DATA BLOCK IDs
#define UPGP_DATA_PRODUCT_DESC		0
#define UPGP_DATA_LOCATION		1
#define UPGP_DATA_INST_COMPONENTS	2
#define UPGP_DATA_REQ_COMPONENTS	3	// Reserved
#define UPGP_DATA_INST_PLUGINS		4	// Reserved
#define UPGP_DATA_REQ_PLUGINS		5
#define UPGP_DATA_REQ_VALIDATE		6
#define UPGP_DATA_LOG_INFO		7
#define UPGP_DATA_INST_PRODUCTS		8
#define UPGP_DATA_INST_PRODUCT_EX	9	//Move information about each product.
#define UPGP_DATA_RESP_PRODUCT		10	//Bloc of the response that contains one product available on the server.
#define UPGP_DATA_REQ_SYSTEM_DESC	11	//Request bloc describing the system.
#define UPGP_DATA_LOCATION2		12
//New block IDs
#define UPGP_DATA_INST_PRODUCT_EX2	13	//Move information about each product.
#define UPGP_DATA_REQ_SYSTEM_DESC2	14	//Request bloc describing the system.
#define UPGP_DATA_LOCATION3		15
#define UPGP_DATA_AU_CONFIGURATION	16	// New Block:  AU Contacting Configuration Block

#define UPGP_DATA_RESP_HEADER		64
#define UPGP_DATA_AVAIL_COMPONENT	65
#define UPGP_DATA_UPSELL_COMPONENT	66
#define UPGP_DATA_HTML_UI		67
#define UPGP_DATA_RESP_CLASS		68

#define UPGP_DATA_MESSAGE_REQ		100
#define UPGP_DATA_MESSAGE_RESP		101
#define UPGP_DATA_MESSAGE_DES		102
#define UPGP_DATA_MESSAGE_CMD		103
#define UPGP_DATA_MESSAGE_SYS		104
#define UPGP_DATA_MESSAGE_INTERVAL	105
#define UPGP_DATA_MESSAGE_NOTIF_DISPLAY_DURATION 106    // notification display duration: number of seconds for the 
							// toaster notification to remain displayed before removing 
							// it from the screen
#define UPGP_DATA_MESSAGE_CONFIGURATION	107		// new block: this block replaces UPGP_DATA_MESSAGE_SYS block by including 
							// all fields from UPGP_DATA_MESSAGE_SYS block plus: contacting method 
							// (Client Polling Settings) and state change & last check


#define UPGP_DATA_CHANNELS_REQ		110	// Channel headlines update
#define UPGP_DATA_CHANNELS_RESP		111

#define UPGP_DATA_MAC			253
#define UPGP_DATA_CUSTOM		254	// Reserved
#define UPGP_DATA_END			255

#define UPGP_NAMED_SOURCE_BEGIN		256
#define UPGP_NAMED_SOURCE_END		257

// Server return status codes (errors, etc)
#define UPGP_STAT_OK			100 //Unknown Server Error
#define UPGP_SERVER_ERROR		101 //Unknown Server Error
#define UPGP_SERVER_UNAVAILABLE		102 //server is temporarily unavailable.
#define UPGP_REQ_ERROR			103 //Error in request (invalid/scrambled/expired/etc)
#define UPGP_CLIENT_UNSUPPORTED		104 //Client Product type/version not supported (right server, but we can't help you)
#define UPGP_CLIENT_UNKNOWN		105 //Client Product type/version unknown (wrong server)
#define UPGP_BLACKLISTED		106 //Client has blacklisted serial #
#define UPGP_INVALID_SERIAL		107 //Client has bad/invalid serial #

// #define SEND_OLD_BLOCK_WITH_NEW_BLOCKS

#endif // _UPGPIDS_H_
