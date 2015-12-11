/**
 * Copyright (C) 2003-2015, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
 * You cannot distribute any part of Foxit PDF SDK to any third party or general public, 
 * unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
 *
 * @file	fpdf_async_r.h
 * @brief	Header file for \ref FPDFASYNC "PDF Async" module of Foxit PDF SDK.
 * @details	This header file provides asynchronous access to PDF document.<br>
 *			It allows reading and downloading of a PDF file to occur at the same time.
 *			For example, an application can display the first page of the document
 *			while the other pages are still downloading.
 *			It contains:<br>
 *			<ul>
 *			<li>1. Load, reload document. </li>
 *			<li>2. Get the first page. </li>
 *			<li>3. Check if the document, page or form is available now. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> explicitly.
 */

#ifndef _FSPDF_ASYNC_R_H_
#define _FSPDF_ASYNC_R_H_

/** 
 * @defgroup	FPDFASYNC PDF Async
 * @brief		Definitions for asynchronous access to PDF document.<br>
 *				Definitions and functions in this module are included in fpdf_async_r.h.<br>
 *				Module: PDFAsync<br>
 *				License Identifier: Async/All<br>
 *				Available License Right: Reading
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. Asynchronous PDF access:
 *					<ul>
 *					<li>a. Load a remote PDF file as asynchronous document, retrieve the first page index and determine whether the file data is available.</li>
 *					<li>b. Asynchronous PDF is a flexible way to access remote PDF easily. It's designed especially for PDF files from Internet.
 *						   Users need not download a remote PDF file fully before accessing it. Only a few data may be enough to display a page.
 *						   While retrieving a PDF document object, use the function ::FSPDF_Doc_IsDocAvail to determine whether the data of document level is ready.
 *						   While displaying a PDF page object, use the function ::FSPDF_Doc_IsPageAvail to determine whether the data of a page level is ready.
 *						   If the user wants to access PDF form, use the function ::FSPDF_Doc_IsFormAvail to determine whether the form is ready.</li>
 *					<li>c. Note: while getting a PDF document object which is returned by the function ::FSPDF_Doc_AsyncLoad, it is not a full available object,
 *						   call fucntion ::FSPDF_Doc_IsDocAvail to make sure it's available really.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _FSPDF_DEF_MACRO_DOC_LINEARIZED_
#define _FSPDF_DEF_MACRO_DOC_LINEARIZED_
/**
 * @name	Macro Definitions for PDF Document Linearized State.
 * @note 	Linearized state indicates whether a PDF document is a linearized file or not.
 */
/**@{*/
/** @brief	PDF document is a linearized file. */
#define FSPDF_DOC_LINEARIZED_YES		1
/** @brief	PDF document is not a linearized file. */
#define FSPDF_DOC_LINEARIZED_NO			0
/** @brief	Don't know whether PDF document is a linearize file or not. */
#define FSPDF_DOC_LINEARIZED_UNKNOW		-1

/**@}*/
#endif //_FSPDF_DEF_MACRO_DOC_LINEARIZED_

#ifndef _FSPDF_DEF_STRUCTURE_ASYNCFILEHANDLER_
#define _FSPDF_DEF_STRUCTURE_ASYNCFILEHANDLER_

/**
 * @brief	Structure for receiving download hints.
 */
typedef struct _FSPDF_ASYNCFILEHANDLER
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Caller can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/**
	 * @brief	Foxit PDF SDK calls this interface to get the file which is to be opened.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[out]  file		Pointer to a <b>FSCRT_FILE</b> handle that receives the file object.
	 *							If there's any error, it will be <b>NULL</b>.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_PARAM if the parameter <i>file</i> is a <b>NULL</b> pointer.<br>
	 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
	 *			For more error codes, please refer to the macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetFile)(FS_LPVOID clientData, FSCRT_FILE* file);

	/**
	 * @brief	Foxit PDF SDK calls this interface to report whether the specified data section is available or not.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	offset		The offset of the hint reported to be downloaded.
	 * @param[in]	size		The size of the hint reported to be downloaded.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if the data section is ready.<br>
	 *			::FSCRT_ERRCODE_DATANOTREADY if the data section is not ready.<br>
	 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
	 *			For more error codes, please refer to the macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	A data section is available only if all bytes in the section are available.
	 */
	FS_RESULT 	(*IsDataAvail)(FS_LPVOID clientData, FS_DWORD offset, FS_DWORD size);

	/**
	 * @brief	Foxit PDF SDK calls this interface to add a section which is to be downloaded.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	offset		The offset of the hit reported to be downloaded.
	 * @param[in]	size		The size of the hit reported to be downloaded.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
	 *			::FSCRT_ERRCODE_ERROR if any error occurs.<br>
	 *			For more error codes, please refer to the macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	Called by the Foxit PDF SDK to report downloading hints for the download manager.<br>
	 *			The position and size of the section may not be accurate because part of the section might
	 *			already be available. The download manager must manage this to maximize download efficiency.
	 */
	FS_RESULT 		(*AddDownloadHint)(FS_LPVOID clientData, FS_DWORD offset, FS_DWORD size);

} FSPDF_ASYNCFILEHANDLER;

#endif /* _FSPDF_DEF_STRUCTURE_ASYNCFILEHANDLER_ */

/**
 * @brief	Load PDF file in asynchronous mode.
 *
 * @param[in]	asyncFile	Pointer to a ::FSPDF_ASYNCFILEHANDLER structure for accessing file data.
 * @param[in]	password	Pointer to a ::FSCRT_BSTR structure which specifies password. It can be user password or owner one.
 *							If no password is used, use <b>NULL</b>. It should be a UTF-8 string if valid.
 * @param[out]	document	Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives the PDF document object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>asyncFile</i> or <i>document</i> is a <b>NULL</b> pointer, or FSPDF_ASYNCFILEHANDLER::GetFile is <b>NYLL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or load PDF document in asynchronous mode is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if the PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_FILE if cannot read data from parameter <i>asyncFile</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to load a PDF file in asynchronous mode because of any other reason.<br>
 *			For more error codes, please refer to the macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	For loading PDF file in asynchronous mode, FSPDF_ASYNCFILEHANDLER::GetFile should be implemented by application.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_AsyncLoad(FSPDF_ASYNCFILEHANDLER* asyncFile, const FSCRT_BSTR* password, FSCRT_DOCUMENT* document);

/**
 * @brief	Check if the asynchronous file is a linearized PDF and get the linearized state.
 *
 * @param[in]	document			Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	linearizedState		Pointer to a ::FS_INT32 object that receives an integer value that receives linearized state.
 *									Please refer to the macro definitions <b>FSPDF_DOC_LINEARIZED_XXX</b> and this should be one of these macros.<br>
 *									If there's any error, it will be ::FSPDF_DOC_LINEARIZED_UNKNOW.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>isLinearized</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a type of PDF document.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there is not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to check because of any other reason.<br>
 *			For more error codes, please refer to the macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Doc_IsLinearized(FSCRT_DOCUMENT document, FS_INT32* linearizedState);

/**
 * @brief	Get the page index of first available page in a linearized PDF.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	pageIndex	Pointer to a ::FS_INT32 object that receives the index of the first available page. 
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>pageIndex</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a type of PDF document.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			For more error codes, please refer to the macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Doc_GetFirstAvailPageIndex(FSCRT_DOCUMENT document, FS_INT32* pageIndex);

/**
 * @brief	Check whether the document is available.
 *
 * @details	If the document is not available, downloading the document should be continuous.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_AsyncLoad.
 * @param[out]	isAvail		Pointer to a ::FS_BOOL object that receives whether the document is available.<br>
 *							<ul>
 *							<li><b>TRUE</b>: the document is available.</li>
 *							<li><b>FALSE</b>: the document is unavailable.</li>
 *							</ul>
 *							If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>isAvail</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a type of PDF document.<br>
 * 			::FSCRT_ERRCODE_FORMAT if the data format in document is not recognized.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there is not available data for ASYNC documents.<br>
 *			For more error codes, please refer to the macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Doc_IsDocAvail(FSCRT_DOCUMENT document, FS_BOOL* isAvail);

/**
 * @brief	Check whether the page is available.
 *
 * @details	If the page is not available, downloading the page should be continuous.
 *			This function can only be called after the document is available, which can be checked by function ::FSPDF_Doc_IsDocAvail.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_AsyncLoad.
 * @param[in]	pageIndex	A zero-based index of page which is to be checked. Range:0 to (pagecount-1).
 *							<i>pagecount</i> is returned by function ::FSPDF_Doc_CountPages.
 * @param[out]	isAvail		Pointer to a ::FS_BOOL object that receives whether the page is available.<br>
 *							<ul>
 *							<li><b>TRUE</b>: the page is available.</li>
 *							<li><b>FALSE</b>: the page is unavailable.</li>
 *							</ul>
 *							If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>isAvail</i> is a <b>NULL</b> pointer, or <i>pageIndex</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a type of PDF document.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>pageIndex</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there is not available data for ASYNC documents.<br>
 *			For more error codes, please refer to the macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Doc_IsPageAvail(FSCRT_DOCUMENT document, FS_INT32 pageIndex, FS_BOOL* isAvail);

/**
 * @brief	Check whether the form is available.
 *
 * @details	If the form is not available, downloading the form should be continuous.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_AsyncLoad.
 * @param[out]	isAvail		Pointer to a ::FS_BOOL object that receives whether the form is available.<br> 
 *							<ul>
 *							<li><b>TRUE</b>: the form is available or no forms in parameter <i>document</i>.</li>
 *							<li><b>FALSE</b>: the form is unavailable.</li>
 *							</ul>
 *							If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>isAvail</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a type of PDF document.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there is not available data for ASYNC documents.<br>
 *			For more error codes, please refer to the macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Doc_IsFormAvail(FSCRT_DOCUMENT document, FS_BOOL* isAvail);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFASYNC */

#endif /* _FSPDF_ASYNC_R_H_ */
