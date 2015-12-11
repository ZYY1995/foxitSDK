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
 * @file	fpdf_document_w.h
 * @brief	Header file for \ref FPDFDOCUMENT "PDF Document" module of Foxit PDF SDK.
 * @details	This header file provides direct access to PDF document.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Set PDF document properties. </li>
 *			<li>2. Save PDF document. </li>
 *			<li>3. Support for document trigger actions. </li>
 *			<li>4. Set PDF metadata. </li>
 *			<li>5. Modify PDF bookmarks. </li>
 *			<li>6. Set PDF viewer preferences. </li>
 *			<li>7. Modify attachments. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Edit Add-on</b> explicitly.
 */

#ifndef _FSPDF_DOCUMENT_W_H_
#define _FSPDF_DOCUMENT_W_H_

/** 
 * @defgroup	FPDFDOCUMENT PDF Document
 * @brief		Definitions for access to PDF document.<br>
 *				Definitions and functions in this module are included in fpdf_document_r.h and fpdf_document_w.h.<br>
 *				Module: PDFDocument<br>
 *				License Identifier: PDFDocument/All<br>
 *				Available License Right: Reading/Writing<br>
 *				For License Right <b>Reading</b>, see fpdf_document_r.h.<br>
 *				For License Right <b>Writing</b>, see fpdf_document_w.h.
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. PDF document:
 *					<ul>
 *					<li>a. Load, reload, create or close document, import PDF pages from another document, and save PDF files.</li>
 *					<li>b. Users can reload a PDF document when they need to reset password, change decryption settings or other purposes.</li>
 *					<li>c. Note: function ::FSPDF_Doc_StartImportPages can merge the same resources in one call,
 *						   and duplicate objects may be generated in several calls to one source document.</li>
 *					</ul>
 *				</li>
 *				<li>2. Document objects: get catalog dictionary, document information dictionary and encryption dictionary.</li>
 *				<li>3. Document properties:
 *					<ul>
 *					<li>a. Get password type, retrieve encryption parameters, and get user permissions, display mode, file version or modification mark.</li>
 *					<li>b. Modification mark is used to tell user whether the contents of document is changed or not.</li>
 *					</ul>
 *				</li>
 *				<li>4. PDF page: get the count of total pages, and get a PDF page object by index.</li>
 *				<li>5. PDF wrapper:
 *					<ul>
 *					<li>a. Judge whether a document is a wrapper or not, and get wrapper offset and information data.</li>
 *					<li>b. PDF wrapper is an extension standard which is created by Foxit Software Inc.. It's used to display some prompt information
 *						   in a wrapper document commonly. For example, use wrapper document to prompt readers to order special viewer to open an encrypted file.</li>
 *					</ul>
 *				</li>
 *				<li>6. Document trigger actions:
 *					<ul>
 *					<li>a. Enumerate trigger actions of PDF document object, modify or remove trigger actions.</li>
 *					<li>b. Note: Foxit PDF SDK doesn't contain functions to execute actions. In a viewer or reader, action should be executed by application.</li>
 *					<li>c. Reference: section 8.5.2 in PDF Reference 1.7 describes trigger actions.</li>
 *					</ul>
 *				</li>
 *				<li>7. Page label:
 *					<ul>
 *					<li>a. Convert between page index and page label.</li>
 *					<li>b. Reference: section 8.3.1 in PDF Reference 1.7 describes page labels.</li>
 *					</ul>
 *				</li>
 *				<li>8. PDF metadata:
 *					<ul>
 *					<li>a. Get or set string types of metadata, and get or set date and time types of metadata.</li>
 *					<li>b. Metadata contains some general information about document title, author, creation or modification date, or others.</li>
 *					<li>c. Reference: section 10.2 in PDF Reference 1.7 describes metadata.</li>
 *					</ul>
 *				</li>
 *				<li>9. PDF bookmark:
 *					<ul>
 *					<li>a. Create, clone or release iterator of bookmark, change position of iterator, get or set properties of bookmark,
 *						   access actions of bookmark, insert or remove bookmark item.</li>
 *					<li>b. PDF bookmark is also called outline. It allows user to navigate PDF document easily by selecting one outline.
 *						   One bookmark contains a destination or actions to indicate how to response when user selects it.
 *						   PDF bookmark is a tree-structured hierarchy.</li>
 *					<li>c. Note: some PDF files may contain a lot of bookmarks. It takes a long time to enumerate all data in a whole PDF file.
 *						   It's recommended that only expanded children are retrieved at once.</li>
 *					<li>d. Reference: section 8.2.2 in PDF Reference 1.7 describes bookmark.</li>
 *					</ul>
 *				</li>
 *				<li>10. Viewer preferences:
 *					<ul>
 *					<li>a. Get or set properties of viewer preferences.</li>
 *					<li>b. Viewer preferences contain some settings about how a PDF viewer should be presented on screen or in print.</li>
 *					<li>c. Reference: section 8.1 in PDF Reference 1.7 describes viewer preferences.</li>
 *					</ul>
 *				</li>
 *				<li>11. PDF attachments:
 *					<ul>
 *					<li>a. Load, enumerate, create or remove document-level attachments, retrieve or change properties of an attachment,
 *						   save attachment data to file or set a file to attachment object.</li>
 *					<li>b. There are two levels of attachments: one is document-level, and the other one is page-level.
 *						   Attachments in document level are embedded in PDF file without appearance, and attachments in page level present as annotations.</li>
 *					<li>c. Reference: section 3.10 in PDF Reference 1.7 describes something on document-level attachments,
 *						   and <b>FileAttachment</b> annotation in section 8.4.5 describes page-level attachments.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Document level macros                                                       */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_SAVEAS_
#define _FSPDF_DEF_MACRO_SAVEAS_
/**
 * @name 	Macro Definitions for PDF Saving Flags
 * @note 	These flags indicate how to save PDF document.
 */
/**@{*/

/** @brief	Save PDF document incrementally. Normally, this flag shouldn't be combined with ::FSPDF_SAVEFLAG_NOORIGINAL.*/
#define		FSPDF_SAVEFLAG_INCREMENTAL			0x1
/** @brief	Save PDF document without original data or unchanged objects. */
#define		FSPDF_SAVEFLAG_NOORIGINAL			0x2
/** @brief	Save PDF document remove security. */
#define		FSPDF_SAVEFLAG_REMOVESECURITY		0x4
/** @brief	Save PDF document by using object stream, in order to reduce the file size. */
#define		FSPDF_SAVEFLAG_OBJECTSTREAM			0x8
/** @brief	Remove the unused objects/resources when saving the document, in order to reduce the file size. It could be combined with ::FSPDF_SAVEFLAG_INCREMENTAL, but that would be meaningless. Only support desktop platforms for now. */
#define		FSPDF_SAVEFLAG_OPTIMIZE				0x10
/** 
 * @brief	Save PDF document and only offer the data of increment. Normally, this flag shouldn't be combined with any other saving flags.
 * @details	If use this flag to save PDF, Foxit PDF SDK will return only the data of increment as result: 
 *			<ul>
 *			<li>For <b>FSCRT_FILE</b> created by callback structure ::FSCRT_FILEHANDLER, these data will be returned to application in callback function FSCRT_FILEHANDLER::WriteBlock.</li>
 *			<li>For <b>FSCRT_FILE</b> created by function ::FSCRT_File_CreateFromFileName, these data will be saved to the specific file.</li>
 *			</ul>
 *			And then application should add these data to the end of source PDF to generate the final saved PDF file.
 * @note	<ul>
 *			<li>This flag can only be used in function ::FSPDF_Doc_StartSaveToFile.</li>
 *			<li>Using this flag may reduce the time spent in saving PDF, especially when using callback structure ::FSCRT_FILEHANDLER and FSCRT_FILEHANDLER::WriteBlock costs a lot of time.
 *			But the size of final saved PDF file will always be larger than the original one.</li>
 *			</ul>
 */
#define		FSPDF_SAVEFLAG_INCREMENTONLY		0x20

/**@}*/
#endif /* _FSPDF_DEF_MACRO_SAVEAS_ */

#ifndef _FSPDF_DEF_MACRO_IMPORTFLAG_
#define _FSPDF_DEF_MACRO_IMPORTFLAG_
/**
* @name Macro Definitions for Importing Pages Flags
* @note These flags indicate how to import pages from source document.
*/
/**@{*/

/** @brief    Import pages normally and it equals to call function ::FSPDF_Doc_StartImportPages. */
#define       FSPDF_IMPORTFLAG_NORMAL			0x00
/** @brief    Import pages with layers and it equals to call function ::FSPDF_Doc_StartImportPagesWithLayers. */
#define       FSPDF_IMPORTFLAG_WITHLAYERS		0x01
/** @brief    Import pages without cloning stream objects into memory and it will reduce memory overhead.*/
#define       FSPDF_IMPORTFLAG_SHARESTREAM		0x02

/**@}*/
#endif /* _FSPDF_DEF_MACRO_IMPORTFLAG_ */



/*******************************************************************************/
/* Create PDF document or import pages from another one                        */
/*******************************************************************************/
/** 
 * @brief	Create a new document object.
 *
 * @param[out]	document	Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives a PDF document object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or creating document is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot create a document because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_Doc_Create(FSCRT_DOCUMENT* document);

/** 
 * @brief	To start a progressive process of inserting a range of pages from a extra source document into the target document.
 *
 * @details	It will take a long time to complete this process with large range of pages, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass <i>importProgress</i> to function ::FSCRT_Progress_Continue to continue processing in steps, 
 *			and should call function ::FSCRT_Progress_Release to destroy <i>importProgress</i> object if importing process is over.<br> 
 *
 * @param[in]	dstDoc			Handle to a <b>FSCRT_DOCUMENT</b> object which specifies the destination PDF document handle.
 * @param[in]	startIndex		A page index in parameter <i>dstDoc</i> where the imported pages will be inserted. 
 *								Range: 0 to pagecount. <i>pagecount</i> is returned by function ::FSPDF_Doc_CountPages. 
 *								If it equals to <i>pagecount</i>, it means the imported page will be added to the end of destination PDF document.
 * @param[in]	srcDoc			Handle to a <b>FSCRT_DOCUMENT</b> object which specifies the source PDF document handle.
 * @param[in]	pageRanges		Pointer to a ::FS_INT32 object which specifies a array to record the page ranges to be imported.<br>
 *								In this array, 2 numbers are a pair: the first integer is the starting page number, and the second integer is the page count.<br>
 *								If this parameter to be set <b>NULL</b> pointer, it means importing the whole source document.
 * @param[in]	count			An integer value which indicates the count of elements in parameter <i>pageRanges</i>. 
 *								It should be an even number when <i>pageRanges</i> isn't <b>NULL</b>.
 * @param[out]	importProgress	Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process. 
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>dstDoc</i> or <i>srcDoc</i> or <i>importProgress</i> is a <b>NULL</b> pointer, 
 *			or <i>count</i> is not an even number when <i>pageRanges</i> isn't <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the parameter <i>srcDoc</i> has an XFA form.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or importing page is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>dstDoc</i> or <i>srcDoc</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>startIndex</i> is out of range.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>dstDoc</i> or <i>srcDoc</i> is not ready when <i>dstDoc</i> or <i>srcDoc</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot import pages because of any other reason.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>srcDoc</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If the user calls this function and then calls function ::FSPDF_Doc_StartSaveToFile to save PDF file, 
 *			the saving flag will be converted to ::FSPDF_SAVEFLAG_NOORIGINAL.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>dstDoc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>srcDoc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>importProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Doc_StartImportPages(FSCRT_DOCUMENT dstDoc, FS_INT32 startIndex,
									   FSCRT_DOCUMENT srcDoc, const FS_INT32* pageRanges, FS_INT32 count,
									   FSCRT_PROGRESS* importProgress);

/** 
 * @brief	To start a progressive process of inserting a range of pages from a extra source document with its layer information into the target document.
 *
 * @details	It will take a long time to complete this process with large range of pages, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass <i>importProgress</i> to function ::FSCRT_Progress_Continue to continue processing in steps, 
 *			and should call function ::FSCRT_Progress_Release to destroy <i>importProgress</i> object if importing process is over.<br> 
 *
 * @param[in]	dstDoc			Handle to a <b>FSCRT_DOCUMENT</b> object which specifies the destination PDF document handle.
 * @param[in]	startIndex		A page index in parameter <i>dstDoc</i> where the imported pages will be inserted. 
 *								Range: 0 to pagecount. <i>pagecount</i> is returned by function ::FSPDF_Doc_CountPages. 
 *								If it equals to <i>pagecount</i>, it means the imported page will be added to the end of destination PDF document.
 * @param[in]	srcDoc			Handle to a <b>FSCRT_DOCUMENT</b> object which specifies the source PDF document handle.
 * @param[in]	layerName		Pointer to a ::FSCRT_BSTR structure. If all content of source document is imported, the layer name in the <b>OCProperties</b> dictionary would be 
 *								same with <i>layerName</i>. Otherwise, <i>layerName</i> would be the prefix name of the layer name in the <b>OCProperties</b> dictionary.
 * @param[in]	pageRanges		Pointer to a ::FS_INT32 object which specifies a array to record the page ranges to be imported.<br>
 *								In this array, 2 numbers are a pair: the first integer is the starting page number, and the second integer is the page count.<br>
 *								If this parameter to be set <b>NULL</b> pointer, it means importing the whole source document.
 * @param[in]	count			An integer value which indicates the count of elements in parameter <i>pageRanges</i>. 
 *								It should be an even number when <i>pageRanges</i> isn't <b>NULL</b>.
 * @param[out]	importProgress	Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process. 
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>dstDoc</i> or <i>srcDoc</i> or <i>srcDocName</i> or <i>importProgress</i> is a <b>NULL</b> pointer, 
 *			or <i>count</i> is not an even number when <i>pageRanges</i> isn't <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the parameter <i>srcDoc</i> has an XFA form.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or importing page with layer is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>dstDoc</i> or <i>srcDoc</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>startIndex</i> is out of range.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>dstDoc</i> or <i>srcDoc</i> is not ready when <i>dstDoc</i> or <i>srcDoc</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot import pages with layers because of any other reason.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>srcDoc</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If the user calls this function and then calls function ::FSPDF_Doc_StartSaveToFile to save PDF file, 
 *			the saving flag will be converted to ::FSPDF_SAVEFLAG_NOORIGINAL.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>dstDoc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>srcDoc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>importProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Doc_StartImportPagesWithLayers(FSCRT_DOCUMENT dstDoc, FS_INT32 startIndex,
												 FSCRT_DOCUMENT srcDoc, const FSCRT_BSTR* layerName, const FS_INT32* pageRanges, FS_INT32 count, 
												 FSCRT_PROGRESS* importProgress);

/** 
 * @brief	To start a progressive process of inserting a range of pages from an extra source document which specified by file path to the target document.
 *
 * @details		It will take a long time to complete this process with large range of pages, so Foxit PDF SDK uses a progressive process to do this.<br>
 *				Callers should pass <i>importProgress</i> to function ::FSCRT_Progress_Continue to continue processing in steps, 
 *				and should call function ::FSCRT_Progress_Release to destroy <i>importProgress</i> object if importing process is over.
 *				If callers want to reduce memory usage during importing, <i>flags</i> should be with ::FSPDF_IMPORTFLAG_SHARESTREAM, howerver, it may reduce the performance a little bit.
 *				The files specified by <i>srcFileName</i> can't be removed unless <i>dstDoc</i> is closed.
 *
 * @param[in]	dstDoc			Handle to a <b>FSCRT_DOCUMENT</b> object which specifies the destination PDF document handle.
 * @param[in]	startIndex		A page index in parameter <i>dstDoc</i> where the imported pages will be inserted. 
 *								Range: 0 to pagecount. <i>pagecount</i> is returned by function ::FSPDF_Doc_CountPages. 
 *								If it equals to <i>pagecount</i>, it means the imported page will be added to the end of destination PDF document.
 * @param[in]	srcFileName		Pointer to a UTF-8 encoded string which specifies the source file name. It should be a valid pointer to a ::FSCRT_BSTR structure.
 * @param[in]	password		Pointer to a ::FSCRT_BSTR structure which specifies a password to the <i>srcFileName</i>. It can be user password or owner password.
 *								If no password is used, please pass <b>NULL</b> or empty string directly.
 * @param[in]	layerName		Pointer to a ::FSCRT_BSTR structure. If all content of source document is imported, the layer name in the <b>OCProperties</b> dictionary would be 
 *								same with <i>layerName</i>. Otherwise, <i>layerName</i>  would be the prefix name of the layer name in the <b>OCProperties</b> dictionary.
 *								It only works with ::FSPDF_IMPORTFLAG_WITHLAYERS and it should be <b>NULL</b> without this flag.
 * @param[in]	pageRanges		Pointer to a ::FS_INT32 object which specifies a array to record the page ranges to be imported.<br>
 *								In this array, 2 numbers are a pair: the first integer is the starting page index, and the second integer is the page count.<br>
 *								If this parameter is set to <b>NULL</b>, all pages in the source document will be imported.
 * @param[in]	count			An integer value which indicates the count of elements in parameter <i>pageRanges</i>. 
 *								It should be an even number when <i>pageRanges</i> isn't <b>NULL</b>.
 * @param[in]	flags			Indicate the importing options, can be one or a combination of macro definitions <b>FSPDF_IMPORTPAGES_XXX</b>.
 * @param[out]	importProgress	Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process. 
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameters meet the following conditions:
 *			<ul>
 *			<li>parameter <i>dstDoc</i>, <i>srcFileName</i>, <i>pageRanges</i> or <i>importProgress</i> is <b>NULL</b>.</li>
 *			<li>parameter <i>srcFileName</i> is an empty string or the file specified by <i>srcFileName</i> can't be opened.</li>
 *			<li>parameter <i>flags</i> is not supported.</li>
 *			<li>if parameter <i>flags</i> is with ::FSPDF_IMPORTFLAG_WITHLAYERS and <i>layerName</i> is <b>NULL</b>.</li>
 *			<li>if parameter <i>flags</i> is without ::FSPDF_IMPORTFLAG_WITHLAYERS and <i>layerName</i> is not <b>NULL</b>.</li>
 *			</ul>
 *			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or importing page with layer is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>dstDoc</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the source document has an XFA form.<br>
 *			::FSCRT_ERRCODE_FORMAT if the parameter <i>srcFileName</i> is not in UTF-8 format or the file specified by <i>srcFileName</i> is not a PDF document..<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>startIndex</i> or <i>pageRanges</i> is out of range.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>dstDoc</i> is not ready when <i>dstDoc</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot import pages because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If the user calls this function and then calls function ::FSPDF_Doc_StartSaveToFile to save PDF file, 
 *			the saving flag will be converted to ::FSPDF_SAVEFLAG_NOORIGINAL.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>dstDoc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>importProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_StartImportPagesFromFileName(FSCRT_DOCUMENT dstDoc, FS_INT32 startIndex,
														const FSCRT_BSTR* srcFileName, const FSCRT_BSTR* password,
														const FSCRT_BSTR* layerName, const FS_INT32* pageRanges, FS_INT32 count, 
														FS_INT32 flags, FSCRT_PROGRESS* importProgress);

/*******************************************************************************/
/* Save PDF document                                                           */
/*******************************************************************************/
/**
 * @brief	Start saving a PDF document to another file in a progressive manner.
 *
 * @details	It will take a long time to save a document with complex or large content, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass parameter <i>saveProgress</i> to function ::FSCRT_Progress_Continue to continue saving progressively, 
 *			and should call function ::FSCRT_Progress_Release to destroy parameter <i>saveProgress</i> if the saving process is over.<br>
 *			To change the saved file version, the user can call function ::FSCRT_Progress_SetProperty to set <b>"fileversion"</b>.<br>
 *			And the type of parameter <i>values</i> in function ::FSCRT_Progress_SetProperty must be ::FSCRT_VT_INT32.
 * 
 * @param[in]	document		Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	file			Handle to a <b>FSCRT_FILE</b> object which specifies another file used to save current PDF document object <i>document</i>.
 * @param[in]	flag			An integer value to specify saving mode. 
 *								Please refer to macro definitions <b>FSPDF_SAVEFLAG_XXX</b> and this should be one or a combination of these macros.
 * @param[out]	saveProgress	Pointer to a <b>FSCRT_PROGRESS</b> handle that receives progressive process.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if any of three parameters <i>document</i>, <i>file</i> or <i>saveProgress</i> is a <b>NULL</b> pointer, 
 *			or parameter <i>flag</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or saving file is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by functoion ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot save document because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	<ul>
 *			<li>When pass a <b>FSCRT_FILE</b> object to this function, pay attention to the following limitations:
 *				<ul>
 *				<li>It should not be created by function ::FSCRT_File_CreateFromMemory. </li>
 *				<li>It should have <b>WRITE</b> callback functions implemented in ::FSCRT_FILEHANDLER if it's created based on a ::FSCRT_FILEHANDLER object.</li>
 *				</ul>
 * 				Meanwhile, if it cannot write data into parameter <i>file</i>, ::FSCRT_ERRCODE_FILE will be returned 
 *				while calling function ::FSCRT_Progress_Continue for next steps.
 *			</li>
 *			<li>Before saving PDF document, we suggest customer to update the "ModDate" by calling function ::FSPDF_Metadata_SetDateTime,
 *			especially when the document has been modified.
 *			</li>
 *			<li>If user wants to make the size of saved PDF file smaller, ::FSPDF_SAVEFLAG_OBJECTSTREAM is suggested to be used for parameter <i>flag</i>.
 *			</li>
 *			</ul>
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				<li> <i>saveProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_StartSaveToFile(FSCRT_DOCUMENT document, FSCRT_FILE file, FS_INT32 flag, FSCRT_PROGRESS* saveProgress);

/**
 * @brief	Save a PDF document as a wrapper file.
 *
 * @details	PDF wrapper is an extended standard, and it helps to hint some information to viewers.<br>
 * 			PDF wrapper consists of 
 *			<ul>
 *			<li>wrapper type: it's an identity string, </li>
 *			<li>wrapper offset: it tells the end of original data, </li>
 * 			<li>wrapper template: it's the content of wrapper document. </li>
 *			</ul>
 *			This function uses the current size of parameter <i>file</i> to set wrapper offset.
 *
 * @param[in]	wrapperDoc			Handle to a <b>FSCRT_DOCUMENT</b> object which is a wrapper document. This function save parameter <i>wrapperDoc</i> as wrapper by the end of <i>file</i>.
 * @param[in]	file				Handle to a <b>FSCRT_FILE</b> object. Parameter <i>wrapperDoc</i> will be saved into it.
 * @param[in]	wrapperData			Pointer to a ::FSPDF_WRAPPERDATA structure which contains wrapper data. If it's <b>NULL</b>, no wrapper data is used.
 * @param[in]	userPermissions		User permissions for the wrapper document. Pass 0xFFFFFFFC if it needs no special permissions.
 *									Please refer to macro definitions <b>FSPDF_PERMISSION_XXX</b> and this can be one or a combination of these macros.
 * @param[in]	ownerPassword		Pointer to a ::FSCRT_BSTR structure which is owner password. If it's <b>NULL</b>, parameter <i>userPermissions</i> is ignored.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameters <i>wrapperDoc</i> or <i>file</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or saving as wrapper file is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>wrapperDoc</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_FILE if the function cannot output data into <i>file</i>.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>wrapperDoc</i> is not ready when <i>wrapperDoc</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to save as wrapper file because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	<ul>
 *			<li>Parameter <i>file</i> should have <b>WRITE</b> callback functions implemented in ::FSCRT_FILEHANDLER if it's created based on a ::FSCRT_FILEHANDLER object.</li>
 *			<li>Before saving PDF document, we suggest customer to update the "ModDate" by calling function ::FSPDF_Metadata_SetDateTime,
 *			especially when the document has been modified.
 *			</li>
 *			</ul>
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>wrapperDoc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_SaveAsWrapperFile(FSCRT_DOCUMENT wrapperDoc, FSCRT_FILE file, const FSPDF_WRAPPERDATA* wrapperData, 
										FS_DWORD userPermissions, const FSCRT_BSTR* ownerPassword);

/*******************************************************************************/
/* Document trigger actions                                                    */
/*******************************************************************************/
/**
 * @brief	Set document trigger action.
 *
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	trigger		An integer value for trigger actions of document. 
 *							Please refer to macro definition <b>FSPDF_TRIGGER_DOC_XXX</b> and this should be one of these macros.
 * @param[in]	index		The index of trigger actions of document. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Doc_CountActions.
 * @param[in]	actionData	Pointer to a ::FSPDF_ACTIONDATA structure used to set.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>actionData</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting action is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of range or no action is found.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set action because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_Doc_SetAction(FSCRT_DOCUMENT document, FS_INT32 trigger, FS_INT32 index, const FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Insert document trigger action.
 *
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	trigger		An integer value for trigger actions of document. 
 *							Please refer to macro definition <b>FSPDF_TRIGGER_DOC_XXX</b> and this should be one of these macros.
 * @param[in]	index		The index of trigger actions of document. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Doc_CountActions.<br>
 *							If it's out of the range, parameter <i>actionData</i> will be inserted to the last.
 * @param[in]	actionData	Pointer to a ::FSPDF_ACTIONDATA structure which to be inserted.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>actionData</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or inserting action is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to insert action because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	The document action will be inserted to the last position, if the parameter <b>index</b> is out of range.
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
FS_RESULT	FSPDF_Doc_InsertAction(FSCRT_DOCUMENT document, FS_INT32 trigger, FS_INT32 index, const FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Remove document trigger action.
 *
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	trigger		An integer value for trigger actions of document. 
 *							Please refer to macro definition <b>FSPDF_TRIGGER_DOC_XXX</b> and this should be one of these macros.
 * @param[in]	index		The index of trigger actions of document. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Doc_CountActions.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or removing action is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of range or no action is found.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to remove action because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_Doc_RemoveAction(FSCRT_DOCUMENT document, FS_INT32 trigger, FS_INT32 index);

/**
 * @brief	Remove all document trigger action.
 *
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	trigger		An integer value for trigger actions of document. 
 *							Please refer to macro definition <b>FSPDF_TRIGGER_DOC_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or removing all actions is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to remove all actions because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_Doc_RemoveAllActions(FSCRT_DOCUMENT document, FS_INT32 trigger);

/**
 * @brief	Remove a javascript action from the PDF document by the name of javascript action.
 *
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	name		Pointer to a ::FSCRT_BSTR structure to specify the name of a JavaScript action. It should be a UTF-8 string.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>name</i> is a <b>NULL</b> pointer or empty.<br>
 *			::FSCRT_ERRCODE_FORMAT if parameter <i>name</i> is not in UTF-8 format.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or removing action is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>name</i> is not a javascript action name.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to remove action because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_Doc_RemoveJSActionByName(FSCRT_DOCUMENT document, const FSCRT_BSTR *name);

/**
 * @brief	Specify the PDF file version which will be stored in PDF header section. This function doesn't check whether the PDF matches the specified version.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	version		An integer specify the file version, such as 14 for 1.4, 15 for 1.5, and etc. Its value should be between 10 and 17,
 *							If it's out of range, then it would be reset as the closest version (10 or 17).
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set PDF file version because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_Doc_SetFileVersion(FSCRT_DOCUMENT document, FS_INT32 version);

/*******************************************************************************/
/* PDF page label                                                              */
/*******************************************************************************/

/**
 * @brief	Set page labels of PDF pages with a specified range.
 *
 * @details	For purposes of page labeling, a document can be divided into labeling ranges, each of which is a series of consecutive pages using the same numbering system.
 *			Pages within a range are numbered sequentially in ascending order. Page labels are consecutively until a next new range.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	start		The index of first page in the current range.
 *							Valid value is from 0 to (<i>count</i> - 1). <i>count</i> is returned by function ::FSPDF_Doc_CountPages.
 * @param[in]	style		An integer value which is a numbering style to be used for the numeric portion of each page label.
 *							Please refer to macro definitions <b>FSPDF_PAGELABEL_STYLE_XXX</b> and this should be one of these macros.
 *							If the value is <b>FSPDF_PAGELABEL_STYLE_None</b>, page labels consist solely of a label prefix with no numeric portion.
 * @param[in]	prefix		Pointer to a ::FSCRT_BSTR structure which is a label prefix for page labels in the current range. It should be a valid UTF-8 string.
 *							If it's <b>NULL</b> or <i>prefix->str</i> is <b>NULL</b> or <i>prefix->len</i> is less than 1, it means no label prefix.
 * @param[in]	st			An integer value which is the numeric portion for the first page label in the current range.
 *							Subsequent pages are numbered sequentially from this value, which must be greater than or equal to 1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> is a <b>NULL</b>, or <i>style</i> or <i>st</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>start</i> is out of range.<br>
 *			::FSCRT_ERRCODE_FORMAT if the parameter <i>prefix</i> is not in UTF-8 format.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_PageLabels_SetRangeInfo(FSCRT_DOCUMENT document, FS_INT32 start, FS_INT32 style, const FSCRT_BSTR* prefix, FS_INT32 st);

/**
 * @brief	Delete all page labels in the PDF document.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> is a <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_PageLabels_RemoveAll(FSCRT_DOCUMENT document);

/*******************************************************************************/
/* Access PDF metadata                                                         */
/*******************************************************************************/
/**
 * @brief	Set a UTF-8 string value to parameter <i>key</i> in metadata.
 *
 * @details	Metadata provides some application level information to tell a viewer something about this document, such as author, title, creation time and others.<br>
 * 
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	key			Pointer to a UTF-8 key string, it should be a valid pointer to ::FSCRT_BSTR structure.<br>
 *							Currently it can be one of the followings:<br>
 *							<ul>
 *							<li>"Title"</li> 
 *							<li>"Author"</li>
 *							<li>"Subject"</li>
 *							<li>"Keywords"</li>
 *							<li>"Creator"</li>
 *							<li>"Producer"</li>
 *							<li>"Trapped"</li>
 *							<li>"pdfaid"</li>
 *							<li>Some other custom information keys, if they're supported by the PDF file.</li>
 *							</ul>
 * @param[in]	string		Pointer to a metadata UTF-8 string, associated to parameter <i>key</i>, it should be a valid pointer to ::FSCRT_BSTR structure.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>key</i> or <i>string</i> is a <b>NULL</b> pointer, or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting metadata string is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set metadata string because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_Metadata_SetString(FSCRT_DOCUMENT document, const FSCRT_BSTR* key, const FSCRT_BSTR* string);

/**
 * @brief	Set an UTF-8 string array value to parameter <i>key</i> in metadata.
 *
 * @details	Metadata provides some application level information to tell a viewer something about this document, such as author, title, creation time and others.
 *			The information exists in two ways: "info" dictionary in trail and metadata stream in the format of XML in the "catalog" dictionary. The information 
 *			in the XML metadata stream could be format of array, this function is used to set array value.
 *			The function is compatible with the function:: FSPDF_Metadata_SetString and would both set information in two places if the key is compatible.
 *
 * @param[in]	document		Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	key				Pointer to a UTF-8 key string, it should be a valid pointer to ::FSCRT_BSTR structure.<br>
 *								Currently it can be one of the followings:<br>
 *								<ul>
 *								<li>"Title"</li> 
 *								<li>"Author"</li>
 *								<li>"Subject"</li>
 *								<li>"Keywords"</li>
 *								<li>"Creator"</li>
 *								<li>"Producer"</li>
 *								<li>"Trapped"</li>
 *								<li>"pdfaid"</li>
 *								</ul>
 * @param[in]	stringArray		Pointer to an UTF-8 string array. Elements in this are metadata information, which is associated to parameter <i>key</i>. 
 *								Each element in this array should be an object of ::FSCRT_BSTR structure.
 * @param[in]	count			The count of elements in parameter <i>stringArray</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>key</i> or <i>stringArray</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty, or <i>count</i> is less than or equal to zero.
 *			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting metadata string is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set metadata string because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_Metadata_SetStringArray(FSCRT_DOCUMENT document, const FSCRT_BSTR* key, const FSCRT_BSTR* stringArray, const FS_INT32 count);

/**
 * @brief	Set a date value to parameter <i>key</i> in metadata.
 *
 * @details	Metadata provides some application level information to tell the viewer document properties, such as author, title, creation time and others.
 *
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	key			Pointer to a UTF-8 key string, it should be a valid pointer to ::FSCRT_BSTR structure.<br>
 *							Currently it can be one of the followings:<br>
 *							<ul>
 *							<li>"CreationDate"</li>
 *							<li>"ModDate"</li>
 *							<li>Some other custom information keys, if they're supported by the PDF file.</li>
 *							</ul>
 * @param[in]	dt			Pointer to a ::FSCRT_DATETIMEZONE structure which is a date and time value associated to parameter <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i>, <i>key</i> or <i>dt</i> is a <b>NULL</b> pointer, or <i>key</i> is empty, 
 *			or paramter <i>dt</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting date value is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set date value because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_Metadata_SetDateTime(FSCRT_DOCUMENT document, const FSCRT_BSTR* key, const FSCRT_DATETIMEZONE* dt);

/*******************************************************************************/
/* Access PDF bookmarks                                                        */
/*******************************************************************************/
/**
 * @brief	Set data to current bookmark positioned by parameter <i>iterator</i>.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[in]	bmData		Pointer to a ::FSPDF_BOOKMARKDATA structure used to set.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>bmData</i> is a <b>NULL</b> pointer, or <i>bmData</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting bookmark data is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_SetData(FSPDF_BOOKMARK_ITERATOR iterator, const FSPDF_BOOKMARKDATA* bmData);

/**
 * @brief	Insert a new bookmark at parameter <i>pos</i> bookmark position and set the data.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[in]	pos			Position where the new bookmark item is to be inserted. 
 *							Please refer to macro definitions <b>FSPDF_BOOKMARKPOS_XXX</b> and this should be one of these macros.
 * @param[in]	bmData		Pointer to a ::FSPDF_BOOKMARKDATA structure to insert the bookmark data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>bmData</i> is a <b>NULL</b> pointer, or parameter <i>pos</i> or <i>bmData</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or inserting a new bookmark is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This function inserts a new bookmark at the current position specified by parameter <i>iterator</i>.
 * 			Parameter <i>iterator</i> points to the new position.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_Insert(FSPDF_BOOKMARK_ITERATOR iterator, FS_INT32 pos, const FSPDF_BOOKMARKDATA* bmData);

/**
 * @brief	Insert a bookmark to be the child (with specific index) of another bookmark with specific position and old one with the specific index will be the next sibling.
 *
 * @param[in]	iterator		Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object and specifies the bookmark which is to be inserted to specific position.
 * @param[in]	newParentPos	Handle to a <b>FSPDF_BOOKMARKPOS</b> object which specific the position of new parent bookmark of parameter <i>iterator</i>.
 * @param[in]	childIndex		Index of child, which indicates where parameter <i>iterator</i> should be inserted under <i>newParentPos</i>.
 *								If this is below 0, bookmark relative with <i>iterator</i> will be set to be the first child.<br>
 *								If this is above current children count of new parent bookmark, bookmark relative with <i>iterator</i> will be set to be the last child.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>bmData</i> is a <b>NULL</b> pointer, or parameter <i>pos</i> or <i>bmData</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or inserting bookmark to specific position is not allowed.<br>
 *			::FSCRT_ERRCODE_UNKNOWNSTATE if bookmark relative with parameter <i>newParentPos</i> is a descendant of <i>iterator</i>, or bookmark relative with <i>newParentPos</i> is just <i>iterator</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to insert bookmark at specific position for any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	<ul>
 *			<li>Root cannot be inserted to be child of other bookmark.</li>
 *			<li>Ancestor bookmarks cannot be inserted to be a child of their descendant bookmarks.</li>
 *			</ul>
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>newParentPos</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_InsertAtPos(FSPDF_BOOKMARK_ITERATOR iterator, FSPDF_BOOKMARKPOS newParentPos, FS_INT32 childIndex);

/**
 * @brief	Remove the current bookmark item positioned by parameter <i>iterator</i>.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or removing bookmark is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the parameter <i>iterator</i> is root or any other error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	After the current bookmark is deleted, if the current bookmark has a next sibling, parameter <i>iterator</i> points to this one; otherwise points to its parent.<br>
 * 			Root cannot be deleted.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_Remove(FSPDF_BOOKMARK_ITERATOR iterator);

/**
 * @brief	Set bookmark action.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[in]	index		The index of a bookmark action. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Bookmark_CountActions.
 * @param[in]	actionData	Pointer to a ::FSPDF_ACTIONDATA structure which to be set.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>actionData</i> is a <b>NULL</b> pointer, or <i>actionData</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting bookmark action is not allowed.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of rang or no action is found. <br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the parameter <i>iterator</i> is root or any other error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_SetAction(FSPDF_BOOKMARK_ITERATOR iterator, FS_INT32 index, const FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Insert bookmark action.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[in]	index		The index where the bookmark action to be inserted is. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Bookmark_CountActions.<br>
 *							If it's out of the range, parameter <i>actionData</i> will be inserted to the last.
 * @param[in]	actionData	Pointer to a ::FSPDF_ACTIONDATA structure which to be inserted.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>actionData</i> is a <b>NULL</b> pointer, or <i>actionData</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or inserting bookmark action is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the parameter <i>iterator</i> is root or any other error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	The bookmark action will be inserted to the last position if the parameter <b>index</b> is out of range.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_InsertAction(FSPDF_BOOKMARK_ITERATOR iterator, FS_INT32 index, const FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Remove a specific bookmark action.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[in]	index		The index of the bookmark action to be deleted. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Bookmark_CountActions.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or removing bookmark action is not allowed.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of rang or no action is found. <br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the parameter <i>iterator</i> is root or any other error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_RemoveAction(FSPDF_BOOKMARK_ITERATOR iterator, FS_INT32 index);

/**
 * @brief	Remove all bookmark actions.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or removing all actions of bookmark is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the parameter <i>iterator</i> is root or any other error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_RemoveAllActions(FSPDF_BOOKMARK_ITERATOR iterator);

/**
 * @brief	Update specific bookmark iterator object after structure of bookmark tree has been changed.
 *
 * @details	Structure of bookmark tree may be changed by adding a new bookmark node , remove a existed bookmark node, or move a bookmark node to a new place.
 *			After doing these changes, the application should call this function to update bookmark iterators which are kept by application and are not used directly in these changes.
 *			If the bookmark node which is relative to parameter <i>iterator</i> has been removed, <i>iterator</i> will be set to root 
 *			and return value of this function will be ::FSCRT_ERRCODE_NOTFOUND.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is to be updated.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or updating bookmark is not allowed.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if bookmark node which is relative to parameter <i>iterator</i> cannot be found.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or add annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the parameter <i>iterator</i> is root or any other error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_Update(FSPDF_BOOKMARK_ITERATOR iterator);

/*******************************************************************************/
/* Access PDF viewer preferences                                               */
/*******************************************************************************/

/**
 * @brief	Set UI visibility in viewer preferences.
 *
 * @details	Viewer preferences define the way that a document is to be presented on the screen or for printing.
 *
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	uiItem		Pointer to a UTF-8 key string, it should be a valid pointer to ::FSCRT_BSTR structure.<br>
 * 							Currently it can be one of the followings:<br>
 *							<ul>
 *							<li>"HideToolbar"</li>
 *							<li>"HideMenubar"</li>
 *							<li>"HideWindowUI"</li>
 *							<li>"FitWindow"</li>
 *							<li>"CenterWindow"</li>
 *							<li>"DisplayDocTitle"</li>
 *							<li>Some other custom UI item keys, if they're supported by the PDF.</li>
 *							</ul>
 * @param[in]	uiVisible	A boolean value that specifies the UI visibility.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>uiItem</i> is a <b>NULL</b> pointer, or <i>uiItem</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting UI visibility is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set UI visibility because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_ViewerPref_SetUIVisibility(FSCRT_DOCUMENT document, const FSCRT_BSTR* uiItem, FS_BOOL uiVisible);

/**
 * @brief	Set display mode for non full-screen mode in viewer preferences.
 *
 * @param[in]	document		Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	displayMode		Pointer to a ::FS_INT32 object to indicate display mode. 
 * 								It should be one of the followings:<br>
 * 								<ul>
 * 								<li>::FSPDF_DISPLAYMODE_USENONE</li>
 * 								<li>::FSPDF_DISPLAYMODE_USEOUTLINES</li>
 * 								<li>::FSPDF_DISPLAYMODE_USETHUMBS</li>
 * 								<li>::FSPDF_DISPLAYMODE_USEOC</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> is a <b>NULL</b> pointer, or <i>displayMode</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting display mode is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set display mode for non full-screen mode because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_ViewerPref_SetNonFullScreenPageMode(FSCRT_DOCUMENT document, FS_INT32 displayMode);

/**
 * @brief	Set reading direction in viewer preferences.
 *
 * @param[in]	document		Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	direction		An integer value which specifies reading direction:<br>
 *								<ul>
 *								<li>::FSPDF_READDIRECT_L2R: left-to-right reading order.</li>
 *								<li>::FSPDF_READDIRECT_R2L: right-to-left reading order.</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> is a <b>NULL</b> pointer, or <i>direction</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting reading direction is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set reading direction because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_ViewerPref_SetReadingDirection(FSCRT_DOCUMENT document, FS_INT32 direction);

/**
 * @brief	Set the page box type in viewer preferences.
 *
 * @details	Viewer preferences define the way that a document is to be presented on the screen or for printing.
 *
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	boxItem		Pointer to a UTF-8 key string, it should be a valid pointer to ::FSCRT_BSTR structure.<br>
 * 							Currently it can be one of the followings:<br> 
 *							<ul>
 *							<li>"ViewArea"</li>
 *							<li>"ViewClip"</li>
 *							<li>"PrintArea"</li>
 *							<li>"PrintClip"</li>
 *							</ul>
 * @param[in]	boxType		An integer value which specifies a page box type. Please refer to macro definitions <b>FSPDF_PAGEBOX_XXX</b> and this should be one of these macros.<br>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>boxItem</i> is a <b>NULL</b> pointer, or <i>boxItem</i> is empty or invalid, or <i>boxType</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting box type is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set area type because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_ViewerPref_SetAreaType(FSCRT_DOCUMENT document, const FSCRT_BSTR* boxItem, FS_INT32 boxType);

/**
 * @brief	Set page scaling in viewer preferences.
 *
 * @details	Viewer preferences define the way that a document is to be presented on the screen or for printing.
 *
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	printScale	Pointer to a ::FSCRT_BSTR structure which is a UTF-8 string value to specify page scale.
 *							It should be one of following:
 *							<ul>
 *							<li>"None": the print dialog should reflect no page scaling.</li>
 *							<li>"AppDefault": applications should use the current print scaling.</li>
 *							</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>printScale</i> is a <b>NULL</b> pointer, or <i>printScale</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting print scaling is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set print scaling because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_ViewerPref_SetPrintScale(FSCRT_DOCUMENT document, const FSCRT_BSTR* printScale);

/**
 * @brief	Set the number of copies to be printed.
 *
 * @details	Viewer preferences define the way that a document is to be presented on the screen or for printing.
 *
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	copies		An integer value which specifies the number of copies to be printed 
 *							when the print dialog is opened for this file. If this is below 0, this function will typically set the number of copies to 1.
 *							Supported values are the integers 2 through  5. Values outside this range are ignored.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> is a <b>NULL</b> pointer, or <i>copies</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting print copies is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set the number of copies because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_ViewerPref_SetPrintCopies(FSCRT_DOCUMENT document, FS_INT32 copies);

/**
 * @brief	Set the page ranges to be printed.
 *
 * @details	Viewer preferences define the way that a document is to be presented on the screen or for printing.
 *
 * @param[in]	document	Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	pageRanges	Pointer to a ::FS_INT32 object which specifies a array to record the page ranges to print.<br>
 * 							In this array, 2 numbers are a pair: the first integer is the starting page number, and the second integer is the ending page number.<br>
 * @param[in]	count		An integer value which indicates the count of elements in the parameter <i>pageRanges</i>. It should be an even number.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>pageRanges</i> is a <b>NULL</b> pointer, or <i>count</i> is not an even number.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting print rages is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to set the page ranges because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT	FSPDF_ViewerPref_SetPrintRanges(FSCRT_DOCUMENT document, const FS_INT32* pageRanges, FS_INT32 count);

/*******************************************************************************/
/* PDF attachments                                                             */
/*******************************************************************************/
/** 
 * @brief	Insert an attachment.
 *
 * @param[in]	attachments		Handle to a <b>FSPDF_ATTACHMENTS</b> object returned by function ::FSPDF_Doc_LoadAttachments.
 * @param[in]	index			The index of attachment. Range: 0 to (attachementcount-1). <i>attachementcount</i> is returned by function ::FSPDF_Attachments_CountAttachment.
 * @param[in]	attachment		Handle to a <b>FSPDF_ATTACHMENT</b> object that specifies the handle of the attachment to be inserted.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachments</i> or <i>attachment</i> is a <b>NULL</b> pointer, or parameter <i>index</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or inserting attachment is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot insert attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachments</i>: this handle is long-term recoverable.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachments_InsertAttachment(FSPDF_ATTACHMENTS attachments, FS_INT32 index, FSPDF_ATTACHMENT attachment);

/** 
 * @brief	Remove an attachment.
 *
 * @param[in]	attachments		Handle to a <b>FSPDF_ATTACHMENTS</b> object returned or the parameter ::FSPDF_Doc_LoadAttachments.
 * @param[in]	attachment		Handle to a valid <b>FSPDF_ATTACHMENT</b> object which is a PDF attachment object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachments</i> or <i>attachment</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or removing attachment is not allowed.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the function cannot find parameter <i>attachment</i>.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot remove attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachments</i>: this handle is long-term recoverable.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachments_RemoveAttachment(FSPDF_ATTACHMENTS attachments, FSPDF_ATTACHMENT attachment);

/*******************************************************************************/
/* PDF Fonts                                                                   */
/*******************************************************************************/
/**
 * @brief	Embed a PDF font to the PDF document.
 *
 * @details	Currently, this function can only support to embed a non-embedded PDF font.
 *			"PDF font" here means that the font has been used for any text object in a PDF document.
 *			User should embed a font by following process:
 *			<ul>
 *			<li>1. Create a new font and use it to a text object, or get a non-embedded font(used for text object) from PDF document.</li>
 *			<li>2. Embed the font.</li>
 *			Once the font is embedded successfully, user is strongly recommended not to use the font for other text objects any more.
 *			Otherwise, unexpected result may occur when showing the text.
 *			</ul>
 *			For other process to embed a font, this function may still run successfully, but in the saved PDF text objects may be wrong or unexpected.<br>
 *			Some unsupported situation:
 *			<ul>
 *			<li>If parameter <i>font</i> is got from another PDF document (different from parameter <i>document</i>), not support to embed this font to current specific PDF document.</li>
 *			<li>If parameter <i>font</i> has been embedded, it cannot be embedded again.</li>
 *			<li>If parameter <i>font</i> is one of the 14 standard fonts, it cannot be embedded.</li>
 *			</ul>
 *
 * @param[in]	document		Handle to a valid <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	font			Handle to a <b>FSCRT_FONT</b> object, which should have been used for text objects in parameter <i>document</i> and hasn't been embedded yet.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i>, <i>font</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED parameter <i>font</i> has already been embedded, or doesn't support to be embedded.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to create a embedded font object for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_EmbedFont(FSCRT_DOCUMENT document, FSCRT_FONT font);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFDOCUMENT */

#endif /* _FSPDF_DOCUMENT_W_H_ */

