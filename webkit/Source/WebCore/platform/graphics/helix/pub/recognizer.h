#ifndef _RECOGNIZER_H_
#define _RECOGNIZER_H_

#include "hxcom.h"
#include "hxfiles.h"
#include "hxfilerecognizer.h"

class CHXFileRecognizer : public IHXFileRecognizer, public IHXFileResponse 
{
public:
    CHXFileRecognizer(IUnknown* pContext);
    virtual ~CHXFileRecognizer();

    /*
     *	IUnknown methods
     */
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, void** ppvObj);

    STDMETHOD_(ULONG32,AddRef) (THIS);

    STDMETHOD_(ULONG32,Release) (THIS);

    /*
     *IHXFileRecognizer methods
     */

    /************************************************************************
     *Method:
     *    IHXFileRecognizer::GetMimeType
     *Purpose:
     */
    STDMETHOD(GetMimeType) (THIS_ IHXFileObject* /*IN*/ pFile, IHXFileRecognizerResponse* /*IN*/ pFileRecognizerResponse);

private:

    enum State
    {
        EFileRecognizerUnInit, 
        EFileRecognizerInit, 
        EFileRecognizerInitDone, 
        EFileRecognizerReadFileHeader, 
        EFileRecognizerReadFileHeaderDone, 
        EFileRecognizerReadMoreData, 
        EFileRecognizerReadMoreDataDone, 
    };

    // IHXFileResponse methods
    STDMETHOD(InitDone)  (THIS_ HX_RESULT status);
    STDMETHOD(SeekDone)  (THIS_ HX_RESULT status);
    STDMETHOD(ReadDone)  (THIS_ HX_RESULT status, IHXBuffer *pBuffer);
    STDMETHOD(WriteDone) (THIS_ HX_RESULT status);
    STDMETHOD(CloseDone) (THIS_ HX_RESULT status);

    STDMETHOD(DoFileRecognize) (THIS_);

    STDMETHOD(GetMimeType) (THIS_ const char* /* IN */pFileName,IHXBuffer* /* IN */ pBuffer, REF(IHXBuffer*) /* OUT*/ pMimeType);

    HX_RESULT  RegisterMediaTypeRecognizers();

    INT32 IsQuickTimeFile(UCHAR* pData, UINT32 ulSize);
    HXBOOL IsStringStart( const UCHAR* src, const UCHAR* test );
    INT32 IsSDPFile( UCHAR* pData, UINT32 ulSize );
    INT32 IsRMFile(UCHAR* pData, UINT32 ulSize);
    HX_RESULT GetEBMLSizeField( UCHAR* pData, UINT32 ulSize, UINT64& llLength, INT32& lSize );
    INT32 IsMKVFile(UCHAR* pData, UINT32 ulSize);
    INT32 IsWMFile(UCHAR* pData, UINT32 ulSize);
    INT32 IsAVIFile(UCHAR* pData, UINT32 ulSize);
    INT32 IsFLVFile(UCHAR* pData, UINT32 ulSize);
    INT32 IsOGGFile(UCHAR* pData, UINT32 ulSize);
    INT32 IsMIDIFile(UCHAR* pData, UINT32 ulSize);
    INT32 IsWAVEFile(UCHAR* pData, UINT32 ulSize);
    INT32 IsAIFFFile(UCHAR* pData, UINT32 ulSize);
    INT32 IsAUFile(UCHAR* pData, UINT32 ulSize);
    INT32 IsAMRFile(UCHAR* pData, UINT32 ulSize);

    INT32 IsAACFile(UCHAR* pData, UINT32 ulSize);
    UINT32 FindADTSSyncword(UCHAR* pBuffer, UINT32 ulSize);
    HXBOOL IsValidADTSHeader(UCHAR* pData, UINT32 ulSize);

    INT32 IsAPEFile(UCHAR* pData, UINT32 ulSize);
    INT32 IsFLACFile(UCHAR* pData, UINT32 ulSize);
    INT32 IsMPEGFile(UCHAR* pData, UINT32 ulSize);

    INT32 IsMPEG2TSFile(UCHAR* pData, UINT32 ulSize);
    HXBOOL AnalyzeTS(UCHAR* pData, UINT32 ulSize, UINT32 ulPacketSize);

    INT32 IsMP3File(UCHAR* pData, UINT32 ulSize);
    UINT32 LoadMP3Header(UCHAR* pData);
    HXBOOL IsValidMP3Header(UINT32 ulHdr);

    INT32 getFrameSync(UINT32 ulHdr)	  { return (int)((ulHdr>>21) & 2047); };
    INT32 getVersionIndex(UINT32 ulHdr)   { return (int)((ulHdr>>19) & 3); };
    INT32 getLayerIndex(UINT32 ulHdr)	   { return (int)((ulHdr>>17) & 3); };
    INT32 getBitrateIndex(UINT32 ulHdr)   { return (int)((ulHdr>>12) & 15); };
    INT32 getFrequencyIndex(UINT32 ulHdr) { return (int)((ulHdr>>10) & 3); };
    INT32 getEmphasisIndex(UINT32 ulHdr)  { return (int)(ulHdr & 3); };
    
private:
    State m_State;
    LONG32 m_lRefCount;
    IUnknown* m_pContext;
    IHXFileRecognizerResponse* m_pResponse;
    IHXFileObject* m_pFile;
    IHXBuffer* m_pBuffer;
    HXBOOL m_bGetMimeTypeDone;

    typedef INT32 ( CHXFileRecognizer::* MediaTypeRecognizer )( UCHAR* pData, UINT32 ulSize );

    struct MediaTypeRecognizerItem
    {
        MediaTypeRecognizer pMediaTypeRecognizer;
        const char* pszMimeType;
        const char** const ppszFileExtension;
    };

    MediaTypeRecognizerItem* m_pMediaTypeRecognizerArray;
};

#endif // _RECOGNIZER_H_
