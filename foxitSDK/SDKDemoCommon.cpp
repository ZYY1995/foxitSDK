#include "pch.h"
#include <iostream>
#include "SDKDemoCommon.h"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage::Streams;

using namespace concurrency;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::ApplicationModel;
using namespace Windows::Storage::FileProperties;
using namespace Windows::Storage::Streams;
using namespace Windows::Graphics::Imaging;
using namespace Windows::UI::Popups;

/*#if defined (_DEMOVIEW_)
using namespace demo_view;
#elif defined(_DEMOANNOT_)
using namespace demo_annotations;
#else
using namespace foxitSDK;
#endif*/

using namespace foxitSDK;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Class CMy_File
CMy_File::CMy_File()
{
}

CMy_File::~CMy_File()
{
}

void CMy_File::InitFileHandle(CMy_FileReadWrite* pFileHandle)
{
	clientData = pFileHandle;
	Release = g_PrivateRelease;
	GetSize = g_PrivateGetSize;
	ReadBlock = g_PrivateReadBlock;
	WriteBlock = g_PrivateWriteBlock;
	Flush = g_PrivateFlush;
	Truncate = g_PrivateTruncate;
}

void CMy_File::ReleaseFileHandle()
{
	if (clientData)
		delete clientData;
	clientData = NULL;
	Release = NULL;
	GetSize = NULL;
	ReadBlock = NULL;
	WriteBlock = NULL;
	Flush = NULL;
	Truncate = NULL;
}


void CMy_File::g_PrivateRelease(FS_LPVOID clientData)
{
	CMy_FileReadWrite* pFileData = (CMy_FileReadWrite*)clientData;

	if (pFileData)
	{
		delete pFileData;
	}
	pFileData = NULL;
}

FS_DWORD CMy_File::g_PrivateGetSize(FS_LPVOID clientData)
{
	CMy_FileReadWrite* pFileData = (CMy_FileReadWrite*)clientData;
	return pFileData->GetSize();
}

FS_RESULT CMy_File::g_PrivateReadBlock(FS_LPVOID clientData, FS_DWORD offset, FS_LPVOID buffer, FS_DWORD size)
{
	CMy_FileReadWrite* pFileData = (CMy_FileReadWrite*)clientData;

	size_t tSize = (size_t)size;

	if (!pFileData->ReadBlock(buffer, offset, tSize))
		return FSCRT_ERRCODE_ERROR;
	else
		return FSCRT_ERRCODE_SUCCESS;
	return FSCRT_ERRCODE_SUCCESS;
}

FS_RESULT CMy_File::g_PrivateWriteBlock(FS_LPVOID clientData, FS_DWORD offset, FS_LPCVOID buffer, FS_DWORD size)
{
	if (!clientData) return FSCRT_ERRCODE_FILE;

	//Change file pointer to offset
	CMy_FileReadWrite* pFileData = (CMy_FileReadWrite*)clientData;
	size_t tSize = (size_t)size;

	if (!pFileData->WriteBlock(buffer, offset, tSize))
		return FSCRT_ERRCODE_ERROR;
	else
		return FSCRT_ERRCODE_SUCCESS;
}

FS_RESULT CMy_File::g_PrivateFlush(FS_LPVOID clientData)
{
	return FSCRT_ERRCODE_SUCCESS;
}

FS_RESULT CMy_File::g_PrivateTruncate(FS_LPVOID clientData, FS_DWORD size)
{
	return FSCRT_ERRCODE_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class CMy_FileReadWrite
CMy_FileReadWrite::CMy_FileReadWrite()
{
	m_pFile = nullptr;
}

CMy_FileReadWrite::~CMy_FileReadWrite()
{
	Release();
}

void CMy_FileReadWrite::SetSize(int nSize)
{
	m_iFileSize = nSize;
}

void CMy_FileReadWrite::CreateFileRead(Windows::Storage::StorageFile^ pFile, int nFileSize)
{
	m_pFile = pFile;
	m_iFileSize = nFileSize;
}

void CMy_FileReadWrite::Release()
{
	m_pFile = nullptr;
	if (m_Buffer && m_Buffer->Size > 0)
	{
		m_Buffer->Clear();
	}
}

int	CMy_FileReadWrite::GetSize()
{
	return m_iFileSize;
}

bool CMy_FileReadWrite::ReadBlock(void* buffer, int offset, size_t size)
{
	if (m_pFile == nullptr)
		return FALSE;

	bool _bIsReadOk = false;
	HANDLE processingHandle = CreateEventEx(
		NULL,
		NULL,
		false,
		EVENT_ALL_ACCESS
		);
	auto  OpenOp = m_pFile->OpenAsync(Windows::Storage::FileAccessMode::Read);
	OpenOp->Completed = ref new AsyncOperationCompletedHandler<IRandomAccessStream^>([buffer, offset, size, processingHandle, &_bIsReadOk](IAsyncOperation<IRandomAccessStream^>^ operation, Windows::Foundation::AsyncStatus status)
	{
		if (status == Windows::Foundation::AsyncStatus::Completed)
		{
			IRandomAccessStream^ readStream = operation->GetResults();
			readStream->Seek(offset);
			DataReader^ dataReader = ref new DataReader(readStream);
			auto LoadOp = dataReader->LoadAsync(size);
			LoadOp->Completed = ref new AsyncOperationCompletedHandler<unsigned int>([buffer, dataReader, processingHandle, &_bIsReadOk](IAsyncOperation<unsigned int>^ operation, Windows::Foundation::AsyncStatus status)
			{
				if (status == Windows::Foundation::AsyncStatus::Completed)
				{
					int numBytesLoaded = operation->GetResults();
					if (numBytesLoaded > 0)
					{
						Array<unsigned char, 1>^ fileContent = ref new Array<unsigned char, 1>(numBytesLoaded);
						dataReader->ReadBytes(fileContent);
						memcpy(buffer, fileContent->Data, numBytesLoaded);
						dataReader->DetachStream();
					}
					_bIsReadOk = true;
					SetEvent(processingHandle);
				}
				else
				{
					_bIsReadOk = false;
					OutputDebugString(L"LoadAsync status ERROR!!!!!\n");
					SetEvent(processingHandle);
				}
			});
		}
		else
		{
			_bIsReadOk = false;
			OutputDebugString(L"status ERROR!!!!!\n");
			SetEvent(processingHandle);
		}
	});
	WaitForSingleObjectEx(processingHandle, INFINITE, true);
	CloseHandle(processingHandle);
	return _bIsReadOk ? TRUE : FALSE;

}

bool CMy_FileReadWrite::WriteBlock(const void* buffer, int offset, size_t size)
{
	if (nullptr == m_Buffer)
	{
		m_Buffer = ref new Vector<Object^>();
	}

	Platform::Array<unsigned char>^ fileContent = ref new Platform::Array<unsigned char>((unsigned char*)buffer, size);
	m_Buffer->Append(fileContent);
	int size1 = m_Buffer->Size;
	return TRUE;
}

void CMy_FileReadWrite::ReleaseTempWriteBuffer()
{
	if (m_Buffer->Size > 0)
	{
		m_Buffer->Clear();
		m_Buffer = nullptr;
	}
}

Platform::Collections::Vector<Platform::Object^>^ CMy_FileReadWrite::GetFileBuffer()
{
	return m_Buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class FSDK_Document
FSDK_Document::FSDK_Document()
{
	m_pFileReader = NULL;
	m_pFileStream = NULL;

	FileHandle tempFile;
	tempFile.pointer = NULL;
	m_hFile = tempFile;

	DocHandle tempDoc;
	tempDoc.pointer = NULL;
	m_hDoc = tempDoc;

	PageHandle tempPage;
	tempPage.pointer = NULL;
	m_hPage = tempPage;
}

FSDK_Document::~FSDK_Document()
{
}

void		FSDK_Document::ReleaseResource()
{
	if (m_hPage.pointer)
	{
		FSPDF_Page_Clear((FSCRT_PAGE)(m_hPage.pointer));
		PageHandle tempPage;
		tempPage.pointer = NULL;
		m_hPage = tempPage;
	}
	if (m_hDoc.pointer)
	{
		FSPDF_Doc_Close((FSCRT_DOCUMENT)(m_hDoc.pointer));
		DocHandle tempDoc;
		tempDoc.pointer = NULL;
		m_hDoc = tempDoc;
	}
	if (m_hFile.pointer)
	{
		FSCRT_File_Release((FSCRT_FILE)(m_hFile.pointer));
		FileHandle tempFile;
		tempFile.pointer = NULL;
		m_hFile = tempFile;
	}
	if (m_pFileStream)
		delete m_pFileStream;
	m_pFileStream = NULL;

	m_pFileReader = NULL;
}


IAsyncOperation<IRandomAccessStreamWithContentType^>^ FSDK_Document::RenderPageAsync(PixelSource^ pxsrc, int iStartX, int iStartY, int iSizeX, int iSizeY, int iRotation)
{
	return create_async([=]()->task < IRandomAccessStreamWithContentType^ > {

		bool ret = GetRenderBitmapData(pxsrc, iStartX, iStartY, iSizeX, iSizeY, iRotation);
		if (true != ret)
		{
			return create_task([]()->IRandomAccessStreamWithContentType^ {return nullptr; });
		}

		InMemoryRandomAccessStream^ _stream = ref new InMemoryRandomAccessStream();
		return task<BitmapEncoder^>(BitmapEncoder::CreateAsync(BitmapEncoder::BmpEncoderId, _stream)).then([=](BitmapEncoder^ encoder)->task < IRandomAccessStreamWithContentType^ > {
			DataReader^ reader = DataReader::FromBuffer(pxsrc->PixelBuffer);
			unsigned int bmp_length = pxsrc->PixelBuffer->Length;
			Array<unsigned char, 1>^ buffer = ref new Array<unsigned char, 1>(pxsrc->PixelBuffer->Length);
			if (!buffer)
			{
				return create_task([]()->IRandomAccessStreamWithContentType^ {return nullptr; });
			}
			reader->ReadBytes(buffer);

			encoder->SetPixelData(BitmapPixelFormat::Rgba8, BitmapAlphaMode::Straight, pxsrc->Width, pxsrc->Height, 96.0, 96.0, buffer);
			return task<void>(encoder->FlushAsync()).then([=]()->task < IRandomAccessStreamWithContentType^ > {
				RandomAccessStreamReference^ streamReference = RandomAccessStreamReference::CreateFromStream(_stream);
				return task<IRandomAccessStreamWithContentType^>(streamReference->OpenReadAsync()).then([=](IRandomAccessStreamWithContentType^ ad)->IRandomAccessStreamWithContentType^ {
					return ad;
				});
			});
		});
	});
}

IAsyncOperation<FS_RESULT>^ FSDK_Document::OpenDocumentAsync(Windows::Storage::StorageFile^ pdfFile, int32 iFileSize, Platform::String^ password)
{
	return create_async([=]()->FS_RESULT {
		FS_RESULT iRet = FSCRT_ERRCODE_ERROR;
		if (nullptr == pdfFile)
			return iRet;

		m_pFileReader = new CMy_FileReadWrite();
		m_pFileReader->CreateFileRead(pdfFile, iFileSize);
		m_pFileStream = new CMy_File();
		m_pFileStream->InitFileHandle(m_pFileReader);
		FSCRT_FILE sdkFile;
		//Create a FSCRT_FILE object used for loading PDF document.
		iRet = FSCRT_File_Create(m_pFileStream, &sdkFile);
		if (iRet != FSCRT_ERRCODE_SUCCESS)
		{
			return iRet;
		}

		auto sdkPassword = ConvertToFoxitString(password);

		FSCRT_DOCUMENT sdkDoc;
		//Load PDF document
		iRet = FSPDF_Doc_StartLoad(sdkFile, &*sdkPassword, &sdkDoc, NULL);
		if (iRet != FSCRT_ERRCODE_SUCCESS)
		{
			return iRet;
		}

		DocHandle CurDoc;
		FileHandle CurFile;
		CurDoc.pointer = (int64)sdkDoc;
		CurFile.pointer = (int64)sdkFile;

		m_hFile = CurFile;
		m_hDoc = CurDoc;
		return iRet;
	});
}

FS_RESULT FSDK_Document::LoadPageSync(int32 iPageIndex)
{
	FS_RESULT iRet = FSCRT_ERRCODE_ERROR;
	FSCRT_PAGE pageGet;
	FSCRT_DOCUMENT sdkDoc = (FSCRT_DOCUMENT)m_hDoc.pointer;
	//Get page with specific page index.
	iRet = FSPDF_Doc_GetPage(sdkDoc, iPageIndex, &pageGet);
	if (iRet != FSCRT_ERRCODE_SUCCESS)
	{
		return iRet;
	}

	//Start to parse page
	FSCRT_PROGRESS progressParse = NULL;
	iRet = FSPDF_Page_StartParse(pageGet, FSPDF_PAGEPARSEFLAG_NORMAL, &progressParse);
	if (iRet != FSCRT_ERRCODE_FINISHED)
	{
		if (iRet != FSCRT_ERRCODE_SUCCESS)
		{
			return iRet;
		}
		//Continue parsing page.
		//If want to do progressive saving, please use the second parameter of FSCRT_Progress_Continue.
		//See FSCRT_Progress_Continue for more details.
		iRet = FSCRT_Progress_Continue(progressParse, NULL);
		FSCRT_Progress_Release(progressParse);
	}
	PageHandle CurPage;
	CurPage.pointer = (int64)pageGet;

	m_hPage = CurPage;
	return FSCRT_ERRCODE_SUCCESS;
}

bool FSDK_Document::GetRenderBitmapData(PixelSource^ pxsrc, int iStartX, int iStartY, int iSizeX, int iSizeY, int iRotation)
{
	FSCRT_BITMAP renderBmp = NULL;
	FSCRT_PAGE pdfPage = (FSCRT_PAGE)m_hPage.pointer;
	//Render page to SDK bitmap.
	FS_RESULT iRet = FSDK_PageToBitmap(pdfPage, pxsrc->Width, pxsrc->Height, iStartX, iStartY, iSizeX, iSizeY, iRotation, &renderBmp);
	if (FSCRT_ERRCODE_SUCCESS != iRet)
	{
		return false;
	}

	//Get data of SDK bitmap.
	iRet = FSDK_GetSDKBitmapData(renderBmp, pxsrc);
	FSCRT_Bitmap_Release(renderBmp);
	if (FSCRT_ERRCODE_SUCCESS != iRet)
	{
		return false;
	}
	else
	{
		return true;
	}
}

IObservableVector<Object^>^ FSDK_Document::SaveAsPDF()
{
	FSCRT_DOCUMENT pDoc = (FSCRT_DOCUMENT)m_hDoc.pointer;
	FSCRT_FILE fxFile = (FSCRT_FILE)m_hFile.pointer;
	if (!pDoc || !fxFile)
		return nullptr;

	Platform::Collections::Vector<Platform::Object^>^ filebytes = nullptr;

	//Start saving PDF file
	FSCRT_PROGRESS progress = NULL;
	FS_RESULT ret = FSPDF_Doc_StartSaveToFile(pDoc, fxFile, FSPDF_SAVEFLAG_INCREMENTAL, &progress);
	if (ret == FSCRT_ERRCODE_SUCCESS)
	{
		//Continue to finish saving
		//If want to do progressive saving, please use the second parameter of FSCRT_Progress_Continue.
		//See FSCRT_Progress_Continue for more details.
		ret = FSCRT_Progress_Continue(progress, NULL);
		//Release saving progress object
		FSCRT_Progress_Release(progress);
	}

	if (m_pFileReader)
	{
		filebytes = ref new Vector<Object^>();
		filebytes = m_pFileReader->GetFileBuffer();
	}

	return filebytes;
}

concurrency::task<IOutputStream^> FSDK_Document::WriteByteToFile(StorageFile^ file, IObservableVector<Object^>^ fileBytes)
{
	std::shared_ptr<DataWriter^> _spDataWriter = std::make_shared<DataWriter^>(nullptr);
	if (nullptr == file)
	{
		return create_task([]()->IOutputStream^ {return nullptr; });
	}
	auto OpenOp = file->OpenAsync(FileAccessMode::ReadWrite);
	return create_task(OpenOp).then([=](IRandomAccessStream^ writeStream)
	{
		writeStream->Seek(0);
		*_spDataWriter = ref new DataWriter(writeStream);
		auto size = fileBytes->Size;
		for (unsigned int i = 0; i < size; i++)
		{
			Platform::Array<unsigned char>^ fileContent = safe_cast<Platform::Array<unsigned char>^>(fileBytes->GetAt(i));
			(*_spDataWriter)->WriteBytes(fileContent);
		}
		return (*_spDataWriter)->StoreAsync();
	}).then([=](unsigned int bytesStored) {
		return (*_spDataWriter)->FlushAsync();
	}).then([=](bool flushSucceeded) {
		fileBytes->Clear();
		return (*_spDataWriter)->DetachStream();
	});
}

Windows::Foundation::IAsyncOperation<Boolean>^ FSDK_Document::SaveAsDocument(Windows::Storage::StorageFile^ file)
{
	return concurrency::create_async([=]()
	{
		if (nullptr == file)
		{
			return create_task([]()->Boolean {return false; });
		}
		return concurrency::create_task([=]()
		{
			Windows::Foundation::Collections::IObservableVector<Object^>^ buffer = SaveAsPDF();
			return buffer;
		})
			.then([=](Windows::Foundation::Collections::IObservableVector<Object^>^ fileBytes)
		{
			return WriteByteToFile(file, fileBytes);
		})
			.then([=](concurrency::task<IOutputStream^> t)
		{
			if (nullptr == t.get())
				return false;
			return true;
		});
	});
}
///////////////////////////////////////////////////////

/* Callback functions for FSCRT_MEMMGRHANDLER*/
//Extension to allocate memory buffer. Implementation to FSCRT_MEMMGRHANDLER::Alloc
static FS_LPVOID	FSDK_Alloc(FS_LPVOID clientData, FS_DWORD size)
{
	return malloc((size_t)size);
}

//Extension to reallocate memory buffer. Implementation to FSCRT_MEMMGRHANDLER::Realloc
static FS_LPVOID	FSDK_Realloc(FS_LPVOID clientData, FS_LPVOID ptr, FS_DWORD newSize)
{
	return realloc(ptr, (size_t)newSize);
}

//Extension to free memory buffer. Implementation to FSCRT_MEMMGRHANDLER::Free
static void			FSDK_Free(FS_LPVOID clientData, FS_LPVOID ptr)
{
	free(ptr);
}
/* END: Callback functions for FSCRT_MEMMGRHANDLER*/

static FSCRT_MEMMGRHANDLER	g_MemMgrHandler = { NULL, FSDK_Alloc, FSDK_Realloc, FSDK_Free };


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Inherited_PDFFunction::Inherited_PDFFunction()
{

}

FS_RESULT	Inherited_PDFFunction::My_Page_Clear(PageHandle page)
{
	return FSPDF_Page_Clear((FSCRT_PAGE)(page.pointer));
}

FS_RESULT Inherited_PDFFunction::My_Page_GetSize(PageHandle page, FS_FLOAT* width, FS_FLOAT* height)
{
	return FSPDF_Page_GetSize((FSCRT_PAGE)(page.pointer), width, height);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined (_DEMOVIEW_)
FS_RESULT demo_view::FSDK_Initialize()
#elif defined(_DEMOANNOT_)
FS_RESULT demo_annotations::FSDK_Initialize()
#else
FS_RESULT foxitSDK::FSDK_Initialize()
#endif
{
	FS_RESULT ret = FSCRT_Library_CreateDefaultMgr();
	if (ret == FSCRT_ERRCODE_SUCCESS)
	{
		//Unlock library, otherwise no methods of SDK can be used
		FSCRT_BSTR license_id;
		FSCRT_BStr_Init(&license_id);
		license_id.str = (FS_LPSTR)"eZYIIG5pU+kg8I27xHQayAkk0lqZrRnJdcIP8ftI74z8OELWUiioiw==";
		license_id.len = strlen(license_id.str);
		FSCRT_BSTR unlockCode;
		unlockCode.str = (FS_LPSTR)"8f3o18ONtRkJBDdKtFJS8bag2amLgQDM5FPEGj3yDnut43GW9tBT6kcyfKOH77HHnqQrwVNtHI6DrcE9f2eLb0wGaKDSEvEZfBNORSR2zqne7VboQHCI+4IWFaN+FUUzO1U5Ms2/u6pj4w8opS7yMcAYKAY0CzkbZCjzVFNNItM+Yd6n9HSxQnBSIWXdH1fquVN9YhgYe1ub6c+JxsmvvWZYCfLITOvcnHOpnDTw1+mmBBQ9X4Vqb6zC+rlCh4M3A4XLagZwoYUnTlmMkU65g5Dtj9oDp3hkuQQxTIO3wNppYhxJ+jdQmpWhWo+qI0WZbqEBCFUpVWollnLbrI81AriVD+E2Joiyhdcs3tkjNoVKZmxCUerxUas1mqEn9b8M88sqmXujLMlpHm4mmJxtiNQ8O8tYgJqksyTVW4sAPlQvJT7YjZJo10xcuenIfnUACMMEVGKSHAAZXW+1nhq+Z4ZiRU8WY/GwLpQebOeb4HnrQosvEHHEH0DRg9DKZSPlYGH+5mLFzriZifGxPF4+j5dwJC0s8iccvB9FfqN89TVCAi1t39eJjPUQ9AoZOFrGvdtKp6FIm1otagbyl/RUjx5AqlDX0IyM8NPoaObOB0Bp1na4aU3tygaliDdtngOiV1njGxDmNBVYYp3iJLQQiDpTOvOCBYHvM5gA0KINWRqLgeKfzkwm2CMWd/hUpZgyZGVJf3TTEmYWUq+j8gylEWttQ9XQKgesIolkK//u1LyFgr1RejAIBEZylcC6eedi2XfIaQJeIMAHIxzhfICJJt+h81cNkoe6mXBN7gJSlWe6y+OE3rZ1tw3qHcpAVCBKxV686NBEhA3iToktYEzSGMUCPxU/F7nkQCxhyTJgeT9/auDYrGtUeiLqA4aVTuMkgxlOSoM+T+sEg7MctBqoCn3v1m2kPBdLuwFVxE30CwS9Csrn3vQ6xhc7PdQLdVRZ26Uy+PU4HAaimrd/yskBI3pGjBhyfmrHvL6RfEb/PtQxUO8xTyWqwr6v6n8EIbn+FNpOoTrAsLfqJrndcnHaDj8/IyB+nmcyL3fQh5Ni2DTDNQlUQ2Ic5yLU1rTRd3+rRhY6dvh4kWYm3BfSsFsv9LbM4LgPq9tXWaMZCIezL9H2Cs1Dx/i0m7o97l8b7yHtad+LNktEWDU9WAu5sgWu3Jgj/N//XAMC08JfJEEVlHtzvh1usU+6FIyH9h6g1Clsaxya2udViSNpiUH7wbfM7EprJwr2MoYi+a2cFhhl6+h/2SsAQ5q+Lae7Yg4U2SYS8V6oHpirqcQjcYTWY4LcK5de7GHYXTDDq6aAKrgB84ONn+i8hoA7pyXE+UC3mLA2dIYa9+LkqdbNRFvibJC3hcw1Ch0WmKwkH7npCqv/4nJHl96tkZ3hX+rJwHoCrOgMf/xajqi+nl1z/R18SbELp9XS7dSVDeM5JMBT4xbAPAfrSibA/FW5kgHGtnJdAs+nEqxHNSyEyMDKs3suKLUodmO8nwOsMrlLZwNSKQz9xR+xE6vLlNZg68Lu37ppQscCByv9pD3PQsLnqHrAwnuR+kt+X7xzYS8J3swvszLZwtgorODcljOL0WoVQ+jVHiSEbIXyIREl7pquP0/+XL9pHCdqVjsixwtedXcTxOj363Q9YDUKRvHfj1fZnL4J6VR6y1xqg5osvv6r+LAxGVk8aR2RayTMncRIuS6rgBAw/tdYNehhNPeNHBiDrA6BVkla27LzJUrR5KIm0Bn9yZWxFyQwehiKgCLQExRg0w==";
		unlockCode.len = strlen(unlockCode.str);
		ret = FSCRT_License_UnlockLibrary(&license_id, &unlockCode);
		if (FSCRT_ERRCODE_SUCCESS == ret)
		{
			//Load system font.
			FSCRT_Library_LoadSystemFonts();
			//Initialize PDF module in order to use methods about PDF.
			ret = FSCRT_PDFModule_Initialize();
			if (FSCRT_ERRCODE_SUCCESS != ret)
			{
				FSDK_Finalize();
			}
		}
	}

	return ret;
}

#if defined (_DEMOVIEW_)
void demo_view::FSDK_Finalize()
#elif defined(_DEMOANNOT_)
void demo_annotations::FSDK_Finalize()
#else
void foxitSDK::FSDK_Finalize()
#endif
{
	//Finitialize PDF module.
	FSCRT_PDFModule_Finalize();

	//Destroy manager
	FSCRT_Library_DestroyMgr();

}

#if defined (_DEMOVIEW_)
FS_RESULT demo_view::FSDK_PageToBitmap(FSCRT_PAGE page, int bmpWidth, int bmpHeight, int iStartX, int iStartY, int iSizeX, int iSizeY, int iRotation, FSCRT_BITMAP *renderBmp)
#elif defined(_DEMOANNOT_)
FS_RESULT demo_annotations::FSDK_PageToBitmap(FSCRT_PAGE page, int bmpWidth, int bmpHeight, int iStartX, int iStartY, int iSizeX, int iSizeY, int iRotation, FSCRT_BITMAP *renderBmp)
#else
FS_RESULT foxitSDK::FSDK_PageToBitmap(FSCRT_PAGE page, int bmpWidth, int bmpHeight, int iStartX, int iStartY, int iSizeX, int iSizeY, int iRotation, FSCRT_BITMAP *renderBmp)
#endif
{
	FS_RESULT ret = FSCRT_ERRCODE_ERROR;
	//Get a bitmap handler to hold bitmap data from rendering progress.
	ret = FSCRT_Bitmap_Create((FS_INT32)bmpWidth, (FS_INT32)bmpHeight, FSCRT_BITMAPFORMAT_32BPP_RGBx, NULL, 0, renderBmp);
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		return ret;
	}

	//Set rect area and fill the color of bitmap.
	FSCRT_RECT rect = { 0, 0, (FS_INT32)bmpWidth, (FS_INT32)bmpHeight };
	ret = FSCRT_Bitmap_FillRect(*renderBmp, FSCRT_ARGB_Encode(0xff, 0xff, 0xff, 0xff), &rect);
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		FSCRT_Bitmap_Release(*renderBmp);
		return ret;
	}

	//Get the page's matrix.
	FSCRT_MATRIX mt;
	ret = FSPDF_Page_GetMatrix(page, iStartX, iStartY, iSizeX, iSizeY, iRotation, &mt);
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		FSCRT_Bitmap_Release(*renderBmp);
		return ret;
	}

	//Create a renderer based on a given bitmap, and page will be rendered to this bitmap.
	FSCRT_RENDERER renderer;
	ret = FSCRT_Renderer_CreateOnBitmap(*renderBmp, &renderer);
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		FSCRT_Bitmap_Release(*renderBmp);
		return ret;
	}

	//Create a render context used for rendering page.
	FSPDF_RENDERCONTEXT rendercontext;
	ret = FSPDF_RenderContext_Create(&rendercontext);
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		FSCRT_Renderer_Release(renderer);
		FSCRT_Bitmap_Release(*renderBmp);
		return ret;
	}

	ret = FSPDF_RenderContext_SetFlags(rendercontext, FSPDF_RENDERCONTEXTFLAG_ANNOT);
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		//Release render
		FSCRT_Renderer_Release(renderer);
		FSPDF_RenderContext_Release(rendercontext);
		FSCRT_Bitmap_Release(*renderBmp);
		return ret;
	}

	//Set the matrix of the given render context.
	ret = FSPDF_RenderContext_SetMatrix(rendercontext, &mt);
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		FSCRT_Renderer_Release(renderer);
		FSPDF_RenderContext_Release(rendercontext);
		FSCRT_Bitmap_Release(*renderBmp);
		return ret;
	}

	//Start to render page.
	FSCRT_PROGRESS renderProgress = NULL;
	ret = FSPDF_RenderContext_StartPage(rendercontext, renderer, page, FSPDF_PAGERENDERFLAG_NORMAL, &renderProgress);
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		FSCRT_Renderer_Release(renderer);
		FSPDF_RenderContext_Release(rendercontext);
		FSCRT_Bitmap_Release(*renderBmp);
		return ret;
	}

	//Continue render progress.
	//If want to do progressive rendering, please use the second parameter of FSCRT_Progress_Continue.
	//See FSCRT_Progress_Continue for more details.
	ret = FSCRT_Progress_Continue(renderProgress, NULL);

	FSCRT_Progress_Release(renderProgress);
	FSCRT_Renderer_Release(renderer);
	FSPDF_RenderContext_Release(rendercontext);
	if (FSCRT_ERRCODE_FINISHED == ret)
		ret = FSCRT_ERRCODE_SUCCESS;
	else
		FSCRT_Bitmap_Release(*renderBmp);

	return ret;
}

#if defined (_DEMOVIEW_)
FS_RESULT demo_view::FSDK_GetSDKBitmapData(FSCRT_BITMAP bmp, PixelSource^ dib)
#elif defined(_DEMOANNOT_)
FS_RESULT demo_annotations::FSDK_GetSDKBitmapData(FSCRT_BITMAP bmp, PixelSource^ dib)
#else
FS_RESULT foxitSDK::FSDK_GetSDKBitmapData(FSCRT_BITMAP bmp, PixelSource^ dib)
#endif
{
	void *lpBmpBuf = 0;
	FS_RESULT ret = FSCRT_Bitmap_GetLineBuffer(bmp, 0, &lpBmpBuf);
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		return ret;
	}
	unsigned int width = 0, height = 0;
	ret = FSCRT_Bitmap_GetSize(bmp, (FS_INT32 *)(&width), (FS_INT32 *)(&height));
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		return ret;
	}
	unsigned int stride = 0;
	ret = FSCRT_Bitmap_GetLineStride(bmp, (FS_INT32 *)(&stride));
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		return ret;
	}
	unsigned int size = stride * height;
	FSCRT_BITMAPINFO bitmapInfo;
	FS_DWORD bmp_infosize;
	FSCRT_Bitmap_GetBitmapInfo(bmp, NULL, &bmp_infosize);
	FSCRT_Bitmap_GetBitmapInfo(bmp, &bitmapInfo, &bmp_infosize);
	Array<unsigned char, 1>^ buffer = ref new Array<unsigned char, 1>(size);
	memcpy(buffer->Data, lpBmpBuf, size);
	DataWriter ^writer = ref new DataWriter();
	writer->WriteBytes(buffer);
	dib->Format = PixelFormat::BGRx;
	dib->PixelBuffer = writer->DetachBuffer();
	if (!dib->PixelBuffer)
	{
		ret = FSCRT_ERRCODE_ERROR;
	}

	return ret;
}

#if defined (_DEMOVIEW_)
std::shared_ptr<FSCRT_BSTR>  demo_view::ConvertToFoxitString(Platform::String^ str)
#elif defined(_DEMOANNOT_)
std::shared_ptr<FSCRT_BSTR>  demo_annotations::ConvertToFoxitString(Platform::String^ str)
#else
std::shared_ptr<FSCRT_BSTR> foxitSDK::ConvertToFoxitString(Platform::String^ str)
#endif
{
	//shared_ptr is a smart pointer class. The first param in construct is the pointer, the second param is a dtor.
	std::shared_ptr<FSCRT_BSTR> _FSstr(new FSCRT_BSTR(), [](FSCRT_BSTR* param)
	{
		if (param)
			FSCRT_BStr_Clear(param);
	});

	FSCRT_BStr_Init(&*_FSstr);
	const wchar_t* _strptr = str->Data();
	int size = WideCharToMultiByte(CP_UTF8, 0, _strptr, -1, NULL, 0, NULL, NULL);
	char *temp = new char[size + 1];
	WideCharToMultiByte(CP_UTF8, 0, _strptr, -1, temp, size, NULL, NULL);
	FSCRT_BStr_Set(&*_FSstr, (FS_LPSTR)temp, strlen(temp));
	delete temp;

	return _FSstr;
}

#if defined (_DEMOVIEW_)
void  demo_view::ShowErrorLog(Platform::String^ errorContent, UICommandInvokedHandler^ returnInvokedHandler/* = nullptr*/,
	bool bSDKError/* = false*/, FS_RESULT errorcode/* = FSCRT_ERRCODE_ERROR*/)
#elif defined(_DEMOANNOT_)
void  demo_annotations::ShowErrorLog(Platform::String^ errorContent, UICommandInvokedHandler^ returnInvokedHandler/* = nullptr*/,
	bool bSDKError/* = false*/, FS_RESULT errorcode/* = FSCRT_ERRCODE_ERROR*/)
#else
void foxitSDK::ShowErrorLog(Platform::String^ errorContent, UICommandInvokedHandler^ returnInvokedHandler,
	bool bSDKError/* = false*/, FS_RESULT errorcode/* = FSCRT_ERRCODE_ERROR*/)
#endif
{
	if (bSDKError)
		errorContent += "\r\nError status value: " + errorcode.ToString() + "."
		+ "\r\nPlease check the value in macro definitions FSCRT_ERRCODE_XXX.";

	MessageDialog^ msgDialog = ref new MessageDialog(errorContent);
	// Add "OK" command.
	UICommand^ defaultCommand = ref new UICommand("OK", nullptr);
	msgDialog->Commands->Append(defaultCommand);
	// Set the command that will be invoked by default
	msgDialog->DefaultCommandIndex = 0;
	if (nullptr != returnInvokedHandler)
	{
		//Add "Back To MainPage" command and set its callback.
		UICommand^ returnCommand = ref new UICommand("Back To MainPage", returnInvokedHandler);
		msgDialog->Commands->Append(returnCommand);
		// Set the command to be invoked when escape is pressed
		msgDialog->CancelCommandIndex = 1;
	}

	msgDialog->ShowAsync();
}

