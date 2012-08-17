/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: ihxmetaeditor.h,v 1.1 2007/11/05 21:32:45 pbasic Exp $
 * 
 * Portions Copyright (c) 1995-2007 RealNetworks, Inc. All Rights Reserved.
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

#ifndef _IHXMETAEDITOR_H
#define _IHXMETAEDITOR_H


/****************************************************************************
 *  Includes
 */
#include "hxcom.h"
#include "hxcomptr.h"
#include "hxsrcin.h"


/****************************************************************************
 *
 *  Additional options (datatype-driver-chain):
 *
 *  METADATAFLAVOR_OPTION_NAME - ULONG32, value must be one of METADATA_FLAVOR
 *      constants. Notifies components about the flavor of meta-data they are
 *      about to process.
 *
 *  BLASTMETADATA_OPTION_NAME - ULONG32, if !=0, the meta-data incoming
 *      from the source will be erased before any new meta-data is added.
 *      Otherwise, new and existing meta-data will be merged.
 *  
 */
#define METADATAFLAVOR_OPTION_NAME  "MetaDataFlavor"
#define BLASTMETADATA_OPTION_NAME   "BlastMetaData"


/****************************************************************************
 *
 *  Meta-data flavors:
 *  Used by meta-data source-handler and meta-data processors to
 *  extract/inject correct set of properties from/to file-header.
 *
 */
typedef enum 
{
    METADATA_FLAVOR_UNKNOWN = 0,
    METADATA_FLAVOR_3GP
} METADATA_FLAVOR;


/****************************************************************************
 *
 *  Interface:
 *	IHXMetaDataProcessor
 *
 *  Purpose:
 *      Used by IHXMetaDataSourceHandler to process meta-data. Clients
 *      can implement this interface if there is a need for special processing.
 *      Meta-data editor provides default processor implementation.
 *
 *  IID_IHXMetaDataProcessor
 *      {241640A0-E73C-46a3-AA62-6C130BE884D6}
 *
 */
DEFINE_GUID(IID_IHXMetaDataProcessor,
            0x241640a0, 0xe73c, 0x46a3, 0xaa, 0x62, 0x6c, 0x13, 0x0b, 0xe8, 0x84, 0xd6);

#undef  INTERFACE
#define INTERFACE   IHXMetaDataProcessor

DECLARE_INTERFACE_(IHXMetaDataProcessor, IUnknown)
{
    /****************************************************************************
     *  Method:
     *       IHXMetaDataProcessor::InitMetaDataProcessor()
     *  Purpose:
     *       Called to initialize MetaDataProcessor. May be called multiple times
     *       if it's necessary to change the context or options used by processor.
     */
    STDMETHOD(InitMetaDataProcessor) (THIS_
                                      IUnknown* pContext,
                                      IHXValues* pOptions
                                     ) PURE;

    /****************************************************************************
     *  Method:
     *       IHXMetaDataProcessor::OnInboundMetaData()
     *  Purpose:
     *       Called by meta-data source-handler to notify the client about
     *       extracted meta-data, and to request new meta-data to be injected
     *       into the file-header. Extracted values contain only properties
     *       of currently processed meta-data flavor; they should be treated as
     *       read-only. Injected properties should also contain only properties of
     *       currently processed flavor; unrecognized properties will be ignored
     *       by meta-data source-handler anyway (they will not be written to the file).
     *       Final set of outbound properties also depends on the BLASTMETADATA_OPTION_NAME
     *       option passed to the components. See "Additional Options" section for
     *       details.
     */
    STDMETHOD(OnInboundMetaData) (THIS_
                                  IHXValues* pExtracted,
                                  IHXValues* pInjectSink
                                 ) PURE;

    /****************************************************************************
     *  Method:
     *       IHXMetaDataProcessor::OnOutboundMetaData()
     *  Purpose:
     *       Called by meta-data source-handler to notify the processor about the
     *       outbound meta-data which is about to be injected into the stream.
     *       Passed set of properties should be treated as read-only.
     */
    STDMETHOD(OnOutboundMetaData) (THIS_
                                   IHXValues* pValues
                                  ) PURE;
};

DEFINE_SMART_PTR(IHXMetaDataProcessor);


/****************************************************************************
 *
 *  Interface:
 *	IHXMetaDataSourceHandler
 *
 *  Purpose:
 *      Datatype-driver chain component which uses IHXMetaDataProcessor
 *      to process meta-data contained by file-header. It's primary purpose
 *      is to serve as a connection point between the driver and the editor.
 *      Any client that finds IHXMetaDataEditor interface too restricting,
 *      could perhaps reuse meta-data editor's source-handler implementation.
 *      An instance of default meta-data source-handler can be created
 *      separately by meta-data-editor component-plugin.
 *
 *  IID_IHXMetaDataSourceHandler
 *      {B4888D83-9A75-4331-B26C-C1C339080AFF}
 *
 */
DEFINE_GUID(IID_IHXMetaDataSourceHandler,
            0xb4888d83, 0x9a75, 0x4331, 0xb2, 0x6c, 0xc1, 0xc3, 0x39, 0x08, 0x0a, 0xff);

#undef  INTERFACE
#define INTERFACE   IHXMetaDataSourceHandler

DECLARE_INTERFACE_(IHXMetaDataSourceHandler, IHXSourceHandler)
{
    /****************************************************************************
     *  Method:
     *       IHXMetaDataSourceHandler::InitMetaDataSourceHandler()
     *  Purpose:
     *       Called to initialize MetaDataSourceHandler. May be called multiple times
     *       if it's necessary to change the context used by the handler. Options are
     *       passed by the driver through IHXSourceHandler::InitSourceHandler method.
     */
    STDMETHOD(InitMetaDataSourceHandler) (THIS_
                                          IUnknown* pContext
                                         ) PURE;

    /****************************************************************************
     *  Method:
     *       IHXMetaDataSourceHandler::SetProcessor()
     *  Purpose:
     *       Called to connect the processor to the handler. May be called multiple
     *       times if it's necessary to change the processor used by the handler.
     */
    STDMETHOD(SetProcessor) (THIS_
                             IHXMetaDataProcessor* pProcessor
                            ) PURE;
};

DEFINE_SMART_PTR(IHXMetaDataSourceHandler);

#define CLSID_IHXMetaDataSourceHandler IID_IHXMetaDataSourceHandler


/****************************************************************************
 *
 *  Interface:
 *	IHXMetaDataEditorResponse
 *
 *  Purpose:
 *      Used to check the progress of meta-data editor file operation. Clients
 *      can implement this interface if they need to be informed about the progress
 *      of file-operation (asynchronous mode). In synchronous mode, this is
 *      typically not needed, but it can be used nevertheless.
 *
 *  IID_IHXMetaDataEditorResponse
 *      {14A0C2CA-7B73-44E8-B0E8-FFB3BD2D8590}
 *
 */
DEFINE_GUID(IID_IHXMetaDataEditorResponse,
            0x14a0c2ca, 0x7b73, 0x44e8, 0xb0, 0xe8, 0xff, 0xb3, 0xbd, 0x2d, 0x85, 0x90);

#undef  INTERFACE
#define INTERFACE   IHXMetaDataEditorResponse

DECLARE_INTERFACE_(IHXMetaDataEditorResponse, IUnknown)
{
    /****************************************************************************
     *  Method:
     *       IHXMetaDataEditorResponse::InitMetaDataEditorResponse()
     *  Purpose:
     *       Called to initialize MetaDataEditorResponse. May be called multiple times
     *       if it's necessary to change the context or options used by response object.
     */
    STDMETHOD(InitMetaDataEditorResponse) (THIS_
                                           IUnknown* pContext,
                                           IHXValues* pOptions
                                          ) PURE;

    /****************************************************************************
     *  Method:
     *       IHXMetaDataEditorResponse::OnProgress()
     *  Purpose:
     *       Called to report file-operation progress.
     */
    STDMETHOD(OnProgress) (THIS_
                           UINT32 progress
                          ) PURE;

    /****************************************************************************
     *  Method:
     *       IHXMetaDataEditorResponse::OnTerminate()
     *  Purpose:
     *       Called once per file-operation to report it's final status.
     */
    STDMETHOD(OnTerminate) (THIS_
                            HX_RESULT result,
                            BOOL bWritingFile
                           ) PURE;
};

DEFINE_SMART_PTR(IHXMetaDataEditorResponse);


/****************************************************************************
 *
 *  Interface:
 *	IHXMetaDataEditor
 *
 *  Purpose:
 *      Provides framework for extraction/injection of meta-data information
 *      contained by the file. Default implementation can be created by
 *      meta-data-editor component-plugin.
 *
 *  IID_IHXMetaDataEditor
 *      {7A26B924-85B2-42E1-b981-A6E2363D54B7}
 *  
 */
DEFINE_GUID(IID_IHXMetaDataEditor,
            0x7a26b924, 0x85b2, 0x42e1, 0xb9, 0x81, 0xa6, 0xe2, 0x36, 0x3d, 0x54, 0xb7);

#undef  INTERFACE
#define INTERFACE   IHXMetaDataEditor

DECLARE_INTERFACE_(IHXMetaDataEditor, IUnknown)
{
    /****************************************************************************
     *  Method:
     *       IHXMetaDataEditor::InitMetaDataEditor()
     *  Purpose:
     *       Called to initialize MetaDataEditor. May be called multiple times
     *       if it's necessary to change the context used by the editor.
     */
    STDMETHOD(InitMetaDataEditor) (THIS_
                                   IUnknown* pContext
                                  ) PURE;

    /****************************************************************************
     *  Method:
     *       IHXMetaDataEditor::Drive()
     *  Purpose:
     *       Called to process file's meta-data. Output-file can be NULL, in which
     *       case only extraction of meta-data is performed. Response object can be
     *       NULL if there's no need for notifications. There is no need to perform
     *       any form of shutdown after file-operation.
     *
     *  Options relevant to usage of this component:
     *
     *       BLASTFILE_OPTION_NAME - if != 0, output file will be overwritten
     *            if it exists.
     *
     *       SYNCHRONOUS_OPTION_NAME - if != 0, response objects gets notifications
     *            in the same callstack that made the request. It means that Drive()
     *            method will not return before the file-operation is completed.
     *
     *       UTF16OUTPUT_OPTION_NAME - not used directly by meta-data editor;
     *            it is passed to file-writers which could use it to determine
     *            meta-data storage format.
     *
     *       METADATAFLAVOR_OPTION_NAME - specifies one of known meta-data flavors,
     *            which notifies all components about the flavor they're about to
     *            process. See "Additional Options" section for details.
     *
     *       BLASTMETADATA_OPTION_NAME - specifies whether the existing meta-data 
     *            should be discarded.  See "Additional Options" section for details.
     */
    STDMETHOD(Drive) (THIS_
                      const char* pszInputFilename,
                      const char* pszOutputFilename,
                      IHXMetaDataProcessor* pProcessor,
                      IHXValues* pOptions,
                      IHXMetaDataEditorResponse* pResponse
                     ) PURE;

    /****************************************************************************
     *  Method:
     *       IHXMetaDataEditor::Read()
     *  Purpose:
     *       This method uses default meta-data processor.
     *       Called to read file's meta-data. Response object can be NULL if
     *       there's no need for notifications. Extracted meta-data set is exported
     *       through <pMetaData> parameter. Caller is responsible for disposal
     *       of this object after use. See Drive() method for details on options
     *       and behaviour.
     */
    STDMETHOD(Read) (THIS_
                     const char* pszInputFilename,
                     REF(IHXValues*) pMetaData,
                     IHXValues* pOptions,
                     IHXMetaDataEditorResponse* pResponse
                    ) PURE;

    /****************************************************************************
     *  Method:
     *       IHXMetaDataEditor::Write()
     *  Purpose:
     *       This method uses default meta-data processor.
     *       Called to write a copy of file with modified meta-data. Response object
     *       can be NULL if there's no need for notifications. <pMetaData> should
     *       contain new meta-data properties to be written. Note that
     *       BLASTMETADATA_OPTION_NAME affects how the data is combined; see
     *       "Additional Options" section for details. See Drive() method for details
     *       on other options and behaviour.
     */
    STDMETHOD(Write) (THIS_
                      const char* pszInputFilename,
                      const char* pszOutputFilename,
                      IHXValues* pMetaData,
                      IHXValues* pOptions,
                      IHXMetaDataEditorResponse* pResponse
                     ) PURE;

    /****************************************************************************
     *  Method:
     *       IHXMetaDataEditor::Stop()
     *  Purpose:
     *       Can be called at any time from any thread to stop ongoing file-operation.
     */
    STDMETHOD(Stop) (THIS
                    ) PURE;
};

DEFINE_SMART_PTR(IHXMetaDataEditor);

#define CLSID_IHXMetaDataEditor IID_IHXMetaDataEditor


#endif // _IHXMETAEDITOR_H
