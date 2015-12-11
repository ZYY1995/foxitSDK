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
 * @file	fpdf_document_r.h
 * @brief	Header file for \ref FPDFDOCUMENT "PDF Document" module of Foxit PDF SDK.
 * @details	This header file provides direct access to PDF document.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Load, reload or close document from file. </li>
 *			<li>2. Get catalog dictionary, document information dictionary and encryption dictionary.</li>
 *			<li>3. Get PDF document properties. </li>
 *			<li>4. Get PDF page objects. </li>
 *			<li>5. Support for document trigger actions. </li>
 *			<li>6. PDF page label support. </li>
 *			<li>7. Get PDF metadata. </li>
 *			<li>8. Access PDF bookmarks. </li>
 *			<li>9. Get PDF viewer preferences. </li>
 *			<li>10.Access attachments. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> explicitly.
 */

#ifndef _FSPDF_DOCUMENT_R_H_
#define _FSPDF_DOCUMENT_R_H_

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
#ifndef _FSPDF_DEF_MACRO_PASSWORDTYPE_
#define _FSPDF_DEF_MACRO_PASSWORDTYPE_
/**
 * @name	Macro Definitions for Password Types
 * @note 	A PDF document can have a user password and an owner password.<br>
 * 			While loading or reloading a PDF file, a password can be passed to the function ::FSPDF_Doc_StartLoad or ::FSPDF_Doc_StartReLoad.<br>
 * 			In order to check which type of password is used, applications can call the function ::FSPDF_Doc_GetPasswordType.
 */
/**@{*/
/** @brief	The password is invalid. */
#define		FSPDF_PASSWORDTYPE_INVALID			-1
/** @brief	No password is used in PDF document. */
#define		FSPDF_PASSWORDTYPE_NOPASSWORD		0
/** @brief	A user password is used in PDF document. */
#define		FSPDF_PASSWORDTYPE_USERPASSWORD		1
/** @brief	An owner password is used in PDF document. */
#define		FSPDF_PASSWORDTYPE_OWNERPASSWORD	2

/**@}*/
#endif /* _FSPDF_DEF_MACRO_PASSWORDTYPE_ */

#ifndef _FSPDF_DEF_MACRO_ENCRYPTIONTYPE_
#define _FSPDF_DEF_MACRO_ENCRYPTIONTYPE_
/**
 * @name	Macro Definitions for Encryption Types
 * @note	These types indicate PDF document's encrypted patterns.
 */
/**@{*/
/** @brief	No encrypt patterns. */
#define		FSPDF_ENCRYPTTYPE_NOENCRYPT		0
/** @brief	Encrypt type by password. */
#define		FSPDF_ENCRYPTTYPE_PASSWORD		1
/** @brief	Encrypt type by digital certificate. */
#define		FSPDF_ENCRYPTTYPE_CERTIFICATE	2
/** @brief	Encrypt type by Foxit DRM. */
#define		FSPDF_ENCRYPTTYPE_FOXITDRM		3
/** @brief	Encrypt type by customized encryption function. */
#define		FSPDF_ENCRYPTTYPE_CUSTOM		4
/** @brief	Encrypt type by Microsoft RMS encryption function. */
#define		FSPDF_ENCRYPTTYPE_RMS			5

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ENCRYPTIONTYPE_ */

#ifndef _FSPDF_DEF_MACRO_DISPLAYMODE_
#define _FSPDF_DEF_MACRO_DISPLAYMODE_
/**
 * @name	Macro Definitions for Display Modes
 * @note	PDF defines two situations for PDF applications: one is full-screen and the other one is normal screen.<br>
 *			Function ::FSPDF_Doc_GetDisplayMode specifies the base display mode, and function ::FSPDF_ViewerPref_GetNonFullScreenPageMode specifies normal display mode (non full-screen).<br>
 * 			Display modes tell how application displays PDF document.
 */
/**@{*/

/** @brief	Neither document outlines nor thumbnail images are visible. */
#define		FSPDF_DISPLAYMODE_USENONE			0
/** @brief	Document outlines (bookmarks) are visible. */
#define		FSPDF_DISPLAYMODE_USEOUTLINES		1
/** @brief	Thumbnail images are visible. */
#define		FSPDF_DISPLAYMODE_USETHUMBS			2
/** @brief	Full-screen mode, with no menu bar, window controls, or any other windows are visible. */
#define		FSPDF_DISPLAYMODE_FULLSCREEN		3
/** @brief	Optional content group panels are visible. */
#define		FSPDF_DISPLAYMODE_USEOC				4
/** @brief	Attachment panels are visible. */
#define		FSPDF_DISPLAYMODE_USEATTACHMENTS	5

/**@}*/
#endif /* _FSPDF_DEF_MACRO_DISPLAYMODE_ */

#ifndef _FSPDF_DEF_MACRO_LOADFLAG_
#define _FSPDF_DEF_MACRO_LOADFLAG_
/**
 * @name	Macro Definitions for document's loading flag
 * @note	Currently, only one flag is defined.
 */
/**@{*/

/** @brief	When load a PDF document, will not cache streams. Loading stream content into memory will improve performance for 
 *			frequent access, however, it will also consume a lot of memory space. Not to cache streams may reduce the performance a
 *			little bit, but greatly reduce the memory consumption, especially when the file is big.
 *			The function ::FSPDF_Doc_StartLoad will cache streams by default.
 */
#define FSPDF_LOADFLAG_NOSTREAMCACHES 0x1

/**@}*/
#endif /* _FSPDF_DEF_MACRO_LOADFLAG_ */



/*******************************************************************************/
/* PDF document load or reload                                                 */
/*******************************************************************************/
/**
 * @brief	Load a PDF file.
 *
 * @param[in]	file		Handle to a <b>FSCRT_FILE</b> object which is a file object to be loaded.	
 * @param[in]	password	Pointer to a ::FSCRT_BSTR structure which specifies a password. It can be user password or owner password.
 *							If no password is used, pass <b>NULL</b> or empty string directly.
 * @param[out]	document	Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives the PDF document.
 *							If there's any error, it will be <b>NULL</b>.
 * @param[out]  progress	Reserved, currently it will be <b>NULL</b>. Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *							If there's any error, it will be <b>NULL</b>. 
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>file</i> or <i>document</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access PDF document is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_FORMAT if the parameter <i>file</i> is not a PDF file.<br>
 * 			::FSCRT_ERRCODE_FILE if the function cannot read data from the parameter <i>file</i>.<br>
 *			::FSCRT_ERRCODE_UNKNOWNSECURITYHANDLER if there is an unknown security handler.<br>
 *			::FSCRT_ERRCODE_PASSWORD if the parameter <i>password</i> is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to load a PDF file because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	If applications only view PDF, only <b>READ</b> callback functions in ::FSCRT_FILEHANDLER needs to be implemented.<br>
 * 			If applications need to change PDF contents or save PDF files, <b>WRITE</b> callback functions should be implemented.<br>
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_StartLoad(FSCRT_FILE file, const FSCRT_BSTR* password, FSCRT_DOCUMENT* document, FSCRT_PROGRESS* progress);

/**
 * @brief	Load a PDF file with the extra flags.
 *
 * @note	If application want to use default option, please call ::FSPDF_Doc_StartLoad, or set <b>flag</b> to 0. 
 *
 * @param[in]	file				Handle to a <b>FSCRT_FILE</b> object which is a file object to be loaded.	
 * @param[in]	password			Pointer to a ::FSCRT_BSTR structure which specifies a password. It can be user password or owner password.
 *									If no password is used, pass <b>NULL</b> or empty string directly.
 * @param[in]	flag				Indicate the loading options, can be one of macro definitions <b>FSPDF_LOADFLAG_XXX</b>.
 * @param[out]	document			Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives the PDF document.
 *									If there's any error, it will be <b>NULL</b>.
 * @param[out]  progress			Reserved, currently it will be <b>NULL</b>. Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *									If there's any error, it will be <b>NULL</b>. 
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>file</i> or <i>document</i> is a <b>NULL</b> pointer or <b>flag</b> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access PDF document is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_FORMAT if the parameter <i>file</i> is not a PDF file.<br>
 * 			::FSCRT_ERRCODE_FILE if the function cannot read data from the parameter <i>file</i>.<br>
 *			::FSCRT_ERRCODE_UNKNOWNSECURITYHANDLER if there is an unknown security handler.<br>
 *			::FSCRT_ERRCODE_PASSWORD if the parameter <i>password</i> is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to load a PDF file because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	If applications only view PDF, only <b>READ</b> callback functions in ::FSCRT_FILEHANDLER needs to be implemented.<br>
 * 			If applications need to change PDF contents or save PDF files, <b>WRITE</b> callback functions should be implemented.<br>
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_StartLoadWithFlag(FSCRT_FILE file, const FSCRT_BSTR* password, FS_DWORD flag, FSCRT_DOCUMENT* document, FSCRT_PROGRESS* progress);

/**
 * @brief	Reload PDF file.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	file		Handle to a <b>FSCRT_FILE</b> object which is a file object to be reloaded. It should be the same <b>FSCRT_FILE</b> object with parameter <i>file</i> passed to function ::FSPDF_Doc_StartLoad or ::FSPDF_Doc_StartLoadWithFlag.	
 * @param[in]	password	Pointer to a ::FSCRT_BSTR structure which specifies a password. It can be user password or owner password.
 *							If no password is used, pass <b>NULL</b> or empty string directly.
 * @param[out]  progress	Reserved, currently it will be <b>NULL</b>. Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *							If there's any error, it will be <b>NULL</b>. 
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>file</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid type of PDF document.<br>
 * 			::FSCRT_ERRCODE_FORMAT if the parameter <i>file</i> is not a PDF file.<br>
 * 			::FSCRT_ERRCODE_FILE if the function cannot read data from the parameter <i>file</i>.<br>
 *			::FSCRT_ERRCODE_PASSWORD if the parameter <i>password</i> is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to reload a PDF file because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	Please refer to the note in function ::FSPDF_Doc_StartLoad.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_StartReLoad(FSCRT_DOCUMENT document, FSCRT_FILE file, const FSCRT_BSTR* password, FSCRT_PROGRESS* progress);

/**
 * @brief	Close a PDF document.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	Users should not use parameter <i>document</i> again after it has been closed.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_Close(FSCRT_DOCUMENT document);

/*******************************************************************************/
/* Document objects                                                            */
/*                                                                             */
/* Catalog, trailer, encrypt and document info dictionary                      */
/*******************************************************************************/
/**
 * @brief	Get the PDF document catalog object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives the catalog object.
 *							It should be a dictionary.<br>
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i> or <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the catalog object is not found in the PDF document.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to catalog object is not allowed.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready 
 *			when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 *			::FSCRT_ERRCODE_ERROR if catalog object of PDF document cannot be obtained for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Doc_GetCatalog(FSCRT_DOCUMENT document, FSPDF_OBJECT* object);

/**
 * @brief	Get the PDF document trailer dictionary.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[out]	trailer		Pointer to a <b>FSPDF_OBJECT</b> handle that receives the trailer dictionary.
 *							It should be a dictionary.<br>
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i> is <b>NULL</b> or <i>trailer</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to trailer object is not allowed.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 *			::FSCRT_ERRCODE_ERROR if trailer object of PDF document cannot be obtained for any other reason.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the trailer object is not found in the PDF document.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Doc_GetTrailer(FSCRT_DOCUMENT document, FSPDF_OBJECT* trailer);

/**
 * @brief	Get the PDF document info object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives the info object.
 *							It should be a dictionary.<br>
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i> or <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the info dictionary is not found in the PDF file.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to the info object is not allowed.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready 
 *			when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 *			::FSCRT_ERRCODE_ERROR if info object of PDF document cannot be obtained for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Doc_GetInfoDict(FSCRT_DOCUMENT document, FSPDF_OBJECT* object);

/**
 * @brief	Get the PDF document encrypt dictionary.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives the encrypt dictionary object.
 *							It should be a dictionary.<br>
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i> or <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if encryption dictionary is not found in the PDF document.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to the info object is not allowed.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready 
 *			when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 *			::FSCRT_ERRCODE_ERROR if encryption dictionary of PDF document cannot be obtained for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Doc_GetEncryptDict(FSCRT_DOCUMENT document, FSPDF_OBJECT* object);

/*******************************************************************************/
/* Access PDF document properties                                              */
/*******************************************************************************/
/**
 * @brief	Get current password type.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	type		Pointer to a ::FS_INT32 object that receives the password type. 
 *							Currently it can be one of the followings: <br>
 *							<ul>
 *							<li>::FSPDF_PASSWORDTYPE_INVALID</li>
 *							<li>::FSPDF_PASSWORDTYPE_NOPASSWORD</li>
 *							<li>::FSPDF_PASSWORDTYPE_USERPASSWORD</li>
 *							<li>::FSPDF_PASSWORDTYPE_OWNERPASSWORD</li>
 *							</ul>
 *							If there's any error, it will be set -2.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>type</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
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
FS_RESULT 	FSPDF_Doc_GetPasswordType(FSCRT_DOCUMENT document, FS_INT32* type);

/**
 * @brief	Get current encryption type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	type			Pointer to a ::FS_INT32 object that receives encryption type. 
 *								Currently it can be one of the followings: <br>
 *								<ul>
 *								<li>::FSPDF_ENCRYPTTYPE_NOENCRYPT</li>
 *								<li>::FSPDF_ENCRYPTTYPE_PASSWORD</li>
 *								<li>::FSPDF_ENCRYPTTYPE_CERTIFICATE</li>
 *								<li>::FSPDF_ENCRYPTTYPE_FOXITDRM</li>
 *								<li>::FSPDF_ENCRYPTTYPE_CUSTOM</li>
 *								<li>::FSPDF_ENCRYPTTYPE_RMS</li>
 *								</ul>
 *								If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>type</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
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
FS_RESULT 	FSPDF_Doc_GetEncryptionType(FSCRT_DOCUMENT document, FS_INT32* type);

/**
 * @brief	Get encryption filter value.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	filter		Pointer to a ::FSCRT_BSTR structure that receives encryption filter. It should not be <b>NULL</b>.<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> while calling this function, 
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>filter</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the encryption filter is not found in <i>document</i>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get encryption filter because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Encryption filter is a name of the preferred security handler for PDF document.<br>
 * 			It's common for an identity string to specify an encryption strategy, and sub-filter is subsidiary of filter for a particular implementation.<br>
 * 			"Standard" is the filter name of the built-in password-encryption.<br>
 * 			if the parameter <i>filter</i> is empty or doesn't have enough memory, this function will allocate memory by calling function ::FSCRT_BStr_SetLength.<br>
 * 			It's better that the caller prepares enough space before calling this function if possible.
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
FS_RESULT 	FSPDF_Doc_GetEncryptionFilter(FSCRT_DOCUMENT document, FSCRT_BSTR* filter);

/**
 * @brief	Get encryption sub-filter value.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	subFilter	Pointer to a ::FSCRT_BSTR structure that receives encryption sub-filter, it should not be <b>NULL</b>.<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> while calling this function, 
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>subFilter</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the encryption sub-filter is not found in parameter <i>document</i>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get encryption sub-filter because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	if the parameter <i>subFilter</i> is empty or doesn't have enough memory, this function will allocate memory by calling function ::FSCRT_BStr_SetLength.<br>
 * 			It's better that caller prepares enough space before calling this function if possible.
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
FS_RESULT 	FSPDF_Doc_GetEncryptionSubFilter(FSCRT_DOCUMENT document, FSCRT_BSTR* subFilter);

/** 
 * @brief	Get encryption parameter value.
 *
 * @details	Different encryption method will have different security dictionaries. 
 *			So the value of parameter <i>key</i> depends on the encryption dictionary.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	key			Pointer to a UTF-8 key string, it should be a valid pointer to ::FSCRT_BSTR structure.
 * @param[out]	value		Pointer to a ::FSCRT_BSTR structure that receives the string data.<br> 
 *							User should call function ::FSCRT_BStr_Clear to free the memory if not using it any more.<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> while calling this function, 
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>key</i> or <i>value</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the encryption key is not found in parameter <i>document</i>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get encryption parameter value because of any other reason.<br>
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
FS_RESULT	FSPDF_Doc_GetEncryptionParam(FSCRT_DOCUMENT document, const FSCRT_BSTR* key, FSCRT_BSTR* value);

/**
 * @brief	Get user permissions specified in PDF document.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	permissions	Pointer to a ::FS_DWORD object that receives user permissions. 
 *							Please refer to macro definition <b>FSPDF_PERMISSION_XXX</b> and this can be one or a combination of these macros.<br>
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>permissions</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Permissions are only applied to a common viewer. Owner has full permissions to a PDF document.
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
FS_RESULT	FSPDF_Doc_GetUserPermissions(FSCRT_DOCUMENT document, FS_DWORD* permissions);

/**
 * @brief	Get display mode specified in PDF document.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	displayMode	Pointer to a ::FS_INT32 object that receives display mode for the application. 
 *							Please refer to macro definition <b>FSPDF_DISPLAYMODE_XXX</b> and this should be one of these macros.<br>
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>displayMode</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get display mode because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This display mode is base mode for the application. For non full-screen display mode, call function ::FSPDF_ViewerPref_GetNonFullScreenPageMode to retrieve.
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
FS_RESULT	FSPDF_Doc_GetDisplayMode(FSCRT_DOCUMENT document, FS_INT32* displayMode);

/**
 * @brief	Get PDF file version stored in PDF header section.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	version		Pointer to a ::FS_INT32 object that receives the file version, such as 14 for 1.4, 15 for 1.5, and etc.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>version</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get PDF file version because of any other reason.<br>
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
FS_RESULT	FSPDF_Doc_GetFileVersion(FSCRT_DOCUMENT document, FS_INT32* version);

/** 
 * @brief	Get PDF document modify mark.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	isModified	Pointer to a ::FS_BOOL object that receives the modify mark.
 *							If there's any error, it will be set <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>modifyMark</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get modify mark because of any other reason.<br>
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
FS_RESULT	FSPDF_Doc_IsModified(FSCRT_DOCUMENT document, FS_BOOL* isModified);

/** 
 * @brief		Whether a document is a portfolio file or not.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	isPortfolio	Pointer to a ::FS_BOOL object that receives the boolean value which indicates whether the file is portfolio or not.<br>
 *							If there's any error, it will be set <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>isPortfolio</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get portfolio mark because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_IsPortfolio(FSCRT_DOCUMENT document, FS_BOOL* isPortfolio);

/*******************************************************************************/
/* Get PDF page object                                                         */
/*******************************************************************************/
/**
 * @brief	Get page count in document.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	count		Pointer to a ::FS_INT32 object that receives the count of total pages in parameter <i>document</i>.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>count</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get page count because of any other reason.<br>
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
FS_RESULT	FSPDF_Doc_CountPages(FSCRT_DOCUMENT document, FS_INT32* count);

/**
 * @brief	Get a page object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	index		Index of PDF page. Range: 0 to (pagecount-1). <i>pagecount</i> is returned by function ::FSPDF_Doc_CountPages.
 * @param[out]	page		Pointer to a <b>FSCRT_PAGE</b> handle that receives a page object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>page</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get a page object because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_GetPage(FSCRT_DOCUMENT document, FS_INT32 index, FSCRT_PAGE* page);


#ifndef _FSPDF_DEF_STRUCTURE_ENUMPAGESIZEHANDLER_
#define _FSPDF_DEF_STRUCTURE_ENUMPAGESIZEHANDLER_

/** 
 * @deprecated	Current structure has been deprecated with function ::FSPDF_Doc_EnumAllPageSize, since Foxit PDF SDK 4.5. 
 *				So, not recommend to use current structure any more. User can use structure ::FSPDF_ENUMPAGEINFOHANDLER instead.
 *
 * @brief	Structure for page size enumeration.
 *
 * @note	This is a handler and should be implemented by caller.<br>
 *			This handler provides method to allow application to enumerate page size.<br>
 */
typedef struct _FSPDF_ENUMPAGESIZEHANDLER
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Caller can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/*
	 * @brief	Enumerate page size of a PDF page.
	 *
	 * @details	Foxit SDK calls this function to enumerate page size for each page, and the application can get page size quickly 
	 *			from the parameter <i>pageWidth</i> and <i>pageHeight</i>, with <i>pageIndex</i> in this callback function.<br>
	 *			Application is not suggested to call any API of Foxit SDK inside this callback function since it may reduce the speed of enumerating all page size.
	 *
	 * @param[in]	clientData		Pointer to user-defined data.
	 * @param[in]	pageIndex		Index of a PDF page. starting from 0.
	 * @param[in]	pageWidth		Width of a PDF page.
	 * @param[in]	pageHeight		Height of a PDF page.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*EnumPageSize)(FS_LPVOID clientData, FS_INT32 pageIndex, FS_FLOAT pageWidth, FS_FLOAT pageHeight);
}FSPDF_ENUMPAGESIZEHANDLER;

#endif //_FSPDF_DEF_STRUCTURE_ENUMPAGESIZEHANDLER_

/**
 * @deprecated	Current function has been deprecated since Foxit PDF SDK 4.5. So, not recommend to use current function any more. User can use function ::FSPDF_Doc_EnumPagesInfo instead.
 *
 * @brief	Enumerate the size of all page.
 *
 * @details	This function is used for enumerating all page's size quickly. Application can get page size for each page from callback function FSPDF_ENUMPAGESIZEHANDLER::EnumPageSize.<br>
 *			if the parameter <i>document</i> is loaded in asynchronous mode, application should ensure that data of <i>document</i> is available, and the data of all pages are available as well.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	enumHandler		Pointer to a ::FSPDF_ENUMPAGESIZEHANDLER structure which is a page size enumeration handler.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> isn't available, or page data in PDF file isn't available.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> <i>enumHandler</i> or FSPDF_ENUMPAGESIZEHANDLER::EnumPageSize of <i>enumHandler</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to enumerate sizes of all pages because of any other reason.<br>
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
FS_RESULT FSPDF_Doc_EnumAllPageSize(FSCRT_DOCUMENT document, FSPDF_ENUMPAGESIZEHANDLER* enumHandler);

#ifndef _FSPDF_DEF_STRUCTURE_ENUMPAGEINFOHANDLER_
#define _FSPDF_DEF_STRUCTURE_ENUMPAGEINFOHANDLER_

/** 
 * @brief	Structure for page information enumeration.
 *
 * @note	This is a handler and should be implemented by caller.<br>
 *			This handler provides method to allow application to enumerate page information.<br>
 */
typedef struct _FSPDF_ENUMPAGEINFOHANDLER
{
	/**
	 * @brief	The size of this structure.
	 */
	FS_DWORD	pageInfoHandleSize;

	/**
	 * @brief	User-defined data.
	 *
	 * @note	Caller can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/*
	 * @brief	Enumerate page size for each PDF page.
	 *
	 * @details	Foxit SDK calls this function to enumerate page size for each page, and the application can get page size quickly 
	 *			from the parameter <i>pageWidth</i> and <i>pageHeight</i>, with <i>pageIndex</i> in this callback function.<br>
	 *			Application is not suggested to call any API of Foxit SDK inside this callback function since it may reduce the speed of enumerating all page size.
	 *
	 * @param[in]	clientData		Pointer to user-defined data.
	 * @param[in]	pageIndex		Index of a PDF page, starting from 0.
	 * @param[in]	pageWidth		Width of a PDF page.
	 * @param[in]	pageHeight		Height of a PDF page.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*EnumPageSize)(FS_LPVOID clientData, FS_INT32 pageIndex, FS_FLOAT pageWidth, FS_FLOAT pageHeight);

	/*
	 * @brief	Enumerate page rotation for each PDF page.
	 *
	 * @details	Foxit SDK calls this function to enumerate page rotation for each page, and the application can get page rotation quickly 
	 *			from the parameter <i>pageRotation</i>, with <i>pageIndex</i> in this callback function.<br>
	 *			Application is not suggested to call any API of Foxit SDK inside this callback function since it may reduce the speed of enumerating all page rotations.
	 *
	 * @param[in]	clientData		Pointer to user-defined data.
	 * @param[in]	pageIndex		Index of a PDF page, starting from 0.
	 * @param[in]	pageRotation	Rotation of a PDF page.
	 *								Please refer to macro definitions <b>FSCRT_PAGEROTATION_XXX</b> and this should be one of these macros.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*EnumPageRotation)(FS_LPVOID clientData, FS_INT32 pageIndex, FS_INT32 pageRotation);
}FSPDF_ENUMPAGEINFOHANDLER;

#endif //_FSPDF_DEF_STRUCTURE_ENUMPAGEINFOHANDLER_

/**
 * @brief	Enumerate the information of all PDF pages.
 *
 * @details	This function is used for enumerating the information of all pages quickly. Application can get page specified information for each page from the callback function of <i>enumHandler</i>.<br>
 *			If the parameter <i>document</i> is loaded in asynchronous mode, application should ensure that data of <i>document</i> is available, and the data of all pages are available as well.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	enumHandler		Pointer to a ::FSPDF_ENUMPAGEINFOHANDLER structure which is a page info enumeration handler.
 *								Unused callback function pointer of this handler should be set to <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> isn't available, or page data in PDF document isn't available.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> <i>enumHandler</i> is <b>NULL</b>, or all callback function pointers of parameter <i>enumHandler</i> are <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there is no available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to enumerate info of all pages because of any other reason.<br>
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
FS_RESULT FSPDF_Doc_EnumPagesInfo(FSCRT_DOCUMENT document, FSPDF_ENUMPAGEINFOHANDLER* enumHandler);

/*******************************************************************************/
/* Access PDF Wrapper	                                                       */
/*******************************************************************************/
#ifndef _FSPDF_DEF_STRUCTURE_WRAPPERDATA_
#define _FSPDF_DEF_STRUCTURE_WRAPPERDATA_

/**
 * @brief	Structure for wrapper data.
 *
 * @note	A wrapper PDF can contain some data to provide application information.
 */ 
typedef struct _FSPDF_WRAPPERDATA
{
	/** @brief	Wrapper version. */
	FS_INT32		version;
	/** @brief	Wrapper type to indicate a type of the current wrapper file. */
	FSCRT_BSTR		type;
	/** @brief	Application identity to indicate applications to open this wrapper data. */
	FSCRT_BSTR		appID;
	/** @brief	URI for consumers to access for more information.*/
	FSCRT_BSTR		uri;
	/** @brief	Description for wrapper file to show applications or confront users prompt information.*/
	FSCRT_BSTR		description;

}FSPDF_WRAPPERDATA;

#endif /* _FSPDF_DEF_STRUCTURE_WRAPPERDATA_ */

/**
 * @brief	Helper function to initialize a wrapper data object.
 *
 * @param[in]	wrapperData		Pointer to a ::FSPDF_WRAPPERDATA structure to be initialized.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>wrapperData</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to initialize a wrapper data variant. 
 *			It sets FSPDF_WRAPPERDATA::version field to zero and calls function ::FSCRT_BStr_Init to other string fields.<br>
 *			Do not initialize with a non-compatible method to Foxit PDF SDK.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_WrapperData_Init(FSPDF_WRAPPERDATA* wrapperData);

/**
 * @brief	Helper function to clear a wrapper data object.
 *
 * @param[in]	wrapperData		Pointer to a ::FSPDF_WRAPPERDATA structure to be cleared.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>wrapperData</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to clear string buffer. 
 *			It sets FSPDF_WRAPPERDATA::version field to zero and calls function ::FSCRT_BStr_Clear to other string fields.<br>
 *			Do not clear objects with a non-compatible method in Foxit PDF SDK.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_WrapperData_Clear(FSPDF_WRAPPERDATA* wrapperData);

/**
 * @brief	Determine whether the document is a wrapper document or not.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	isWrapper	Pointer to a ::FS_BOOL object that receives wrapper state.: 
 *							<ul>
 *							<li><b>TRUE</b>: parameter <i>document</i> is a wrapper.</li>
 *							<li><b>FALSE</b>: parameter <i>document</i> isn't a wrapper.</li>
 *							</ul>
 *							If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>isWrapper</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get the boolean value because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	PDF wrapper is an extended standard. It helps to hint some information to viewers.<br>
 *			PDF wrapper consists of wrapper type which is an identity string, wrapper offset which tells the end of original data,
 * 			and wrapper template which is the content of wrapper document.
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
FS_RESULT	FSPDF_Doc_IsWrapper(FSCRT_DOCUMENT document, FS_BOOL* isWrapper);

/**
 * @brief	Get wrapper offset.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	offset		Pointer to a ::FSCRT_FILESIZE structure that receives wrapper offset. 
 *							In order to keep forward compatibilities, use 64-bits here.<br>
 *							If there's any error, the value of ::FSCRT_FILESIZE will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>offset</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>document</i> isn't a wrapper document.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get wrapper offset because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	PDF wrapper is an extended standard, it helps to hint some information to viewers.<br>
 * 			PDF wrapper consists of wrapper type which is an identity string, of wrapper offset which tells the end of original data,<br>
 * 			and of wrapper template which is the content of wrapper document. They are specified while calling function ::FSPDF_Doc_SaveAsWrapperFile.<br>
 * 			Application can access original PDF contents by wrapper offset.
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
FS_RESULT	FSPDF_Doc_GetWrapperOffset(FSCRT_DOCUMENT document, FSCRT_FILESIZE* offset);

/**
 * @brief	Get wrapper data.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	wrapperData		Pointer to a ::FSPDF_WRAPPERDATA structure that receives wrapper data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>wrapperData</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type or is not a wrapper file.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>document</i> isn't a wrapper document.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get wrapper data because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	PDF wrapper is an extended standard, it helps to hint some information to viewers.<br>
 * 			PDF wrapper consists of wrapper type which is an identity string, wrapper offset which tells the end of original data <br>
 * 			and wrapper template which is the content of wrapper document. They are specified while calling function ::FSPDF_Doc_SaveAsWrapperFile.<br>
 * 			Application can determine whether to support current wrapper document based on this wrapper data.
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
FS_RESULT	FSPDF_Doc_GetWrapperData(FSCRT_DOCUMENT document, FSPDF_WRAPPERDATA* wrapperData);


/*******************************************************************************/
/* Document trigger actions                                                    */
/*******************************************************************************/
/**
 * @brief	Get the count of document trigger actions.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	trigger	 	An integer value for type of trigger action of document. 
 *							Please refer to macro definition <b>FSPDF_TRIGGER_DOC_XXX</b> and this should be one of these macros.
 * @param[out]	count		Pointer to a ::FS_INT32 object that receives trigger action counts.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>count</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get count of actions because of any other reason.<br>
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
FS_RESULT	FSPDF_Doc_CountActions(FSCRT_DOCUMENT document, FS_INT32 trigger, FS_INT32* count);

/**
 * @brief	Get document trigger action.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	trigger		An integer value for type of trigger action of document. 
 *							Please refer to macro definition <b>FSPDF_TRIGGER_DOC_XXX</b> and this should be one of these macros.
 * @param[in]	index		Index of trigger actions of document. Range: 0 to (actioncount-1).
 *							<i>actioncount</i> is returned by function ::FSPDF_Doc_CountActions, with same parameter <i>trigger</i>.
 * @param[out]	actionData	Pointer to a ::FSPDF_ACTIONDATA structure that receives trigger action data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>actionData</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of range or no action is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get action because of any other reason.<br>
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
FS_RESULT	FSPDF_Doc_GetAction(FSCRT_DOCUMENT document, FS_INT32 trigger, FS_INT32 index, FSPDF_ACTIONDATA* actionData);


/*******************************************************************************/
/* PDF action handler                                                          */
/*******************************************************************************/

#ifndef _FSPDF_DEF_STRUCTURE_IDENTITYPROPERTIES_
#define _FSPDF_DEF_STRUCTURE_IDENTITYPROPERTIES_

/** @brief	Structure for identity properties of the current user of the application. */
typedef struct _FSPDF_IDENTITYPROPERTIES
{
	/** @brief	The corporation name that the user has entered in the Identity preferences panel. */
	FSCRT_BSTR corporation;
	/** @brief	The email address that the user has entered in the Identity preferences panel. */
	FSCRT_BSTR email;
	/** @brief	The login name as registered by the operating system. */
	FSCRT_BSTR loginName;
	/** @brief	The user name that the user entered in the Identity preferences panel. */
	FSCRT_BSTR name;
} FSPDF_IDENTITYPROPERTIES;

#endif /* _FSPDF_IDENTITYPROPERTIES */

#ifndef _FSPDF_DEF_STRUCTURE_MENULIST_
#define _FSPDF_DEF_STRUCTURE_MENULIST_

/** @brief	Structure for menu list. */
typedef struct _FSPDF_MENULIST
{
	/** @brief	The level of menu. */
	FS_INT32 level;
	/** @brief	The title of menu. */
	FSCRT_BSTR name;
}FSPDF_MENULIST;

#endif /* _FSPDF_MENULIST */


#ifndef _FSPDF_DEF_HANDLER_ACTION_
#define _FSPDF_DEF_HANDLER_ACTION_

/** 
 * @brief	Structure for action handler information.
 *
 * @note	This is a handler and should be implemented by caller.<br>
 *			Action handler provides a number of interfaces to implement the actions.<br>
 */
typedef struct _FSPDF_ACTION_HANDLER
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Caller can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/**
	 * @brief	Optional callback function to release data.
	 *
	 * @details	This callback function gives the implementation a chance to release any data after the interface is no longer used.
	 *			An this will be called by Foxit PDF SDK during the final cleanup process.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*Release)(FS_LPVOID clientData);

	/**
	 * @brief	Required callback function to invalidate the client area within the specified rectangle.
	 *
	 * @details	All positions are measured in PDF "user space".
	 *			Implementation should call function ::FSPDF_RenderContext_StartPage for repainting a specified page area.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
	 * @param[in]	pageIndex	The page index which start from 0.
	 * @param[in]	pdfRect		Pointer to a <b>FSCRT_RECTF</b> structure, which specify the page area in PDF page coordinate.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 */
	FS_RESULT	(*InvalidateRect)(FS_LPVOID clientData, FSCRT_DOCUMENT document, FS_INT32 pageIndex, FSCRT_RECTF* pdfRect);

	/**
	 * @brief	Optional callback function to receives the current page index.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
	 * @param[out]	pageIndex	Pointer to a ::FS_INT32 object that receive the index of current PDF page.
	 *							This should be stared from 0 and less than page count of current document.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetCurrentPageIndex)(FS_LPVOID clientData, FSCRT_DOCUMENT document, FS_INT32* pageIndex);
 
	/**
	 * @brief	Optional callback function to set the current page index.
	 *
	 * @param[in]	clientData	Pointer to the interface structure itself.
	 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
	 * @param[in]	pageIndex	Index of page index which is to be set to current PDF page, starting from 0.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*SetCurrentPageIndex)(FS_LPVOID clientData, FSCRT_DOCUMENT document, FS_INT32 pageIndex);

	/**
	 * @brief	Optional callback function to receive current rotation of the page view.
	 *
	 * @param[in]	clientData	Pointer to the interface structure itself.
	 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
	 * @param[in]	pageIndex	The page index which starts from 0.
	 * @param[out]	rotation	The rotation of the page being displayed.
	 *							Please refer to macro definitions <b>FSCRT_PAGEROTATION_XXX</b> and this should be one of these macros.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetRotation)(FS_LPVOID clientData, FSCRT_DOCUMENT document, FS_INT32 pageIndex, FS_INT32* rotation);
	 
	/**
	 * @brief	Optional callback function to execute a named action.
	 *
	 * @details	Please refer to description of named actions description in PDF Reference 1.7 for more details. 
	 *
	 * @param[in]	clientData	Pointer to the interface structure itself.
	 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
	 * @param[in]	namedAction	Pointer to a ::FSCRT_BSTR structure to specify the named action. It would be a UTF-8 string.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*ExecuteNamedAction)(FS_LPVOID clientData, FSCRT_DOCUMENT document, const FSCRT_BSTR* namedAction);

	/** 
	 * @brief	Optional callback function to set the change mark which indicates whether the content of document is changed or not.
	 *
	 * @param[in]	clientData	Pointer to the interface structure itself.
	 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
	 * @param[in]	changeMark	A boolean value that indicates whether the content of document is changed or not.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*SetChangeMark)(FS_LPVOID clientData, FSCRT_DOCUMENT document, FS_BOOL changeMark);

	/** 
	 * @brief	Optional callback function to receive the change mark which indicates whether the content of document is changed or not.
	 *
	 * @param[in]	clientData	Pointer to the interface structure itself.
	 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
	 * @param[out]	changeMark	Pointer to a ::FS_BOOL object that receives the change mark.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetChangeMark)(FS_LPVOID clientData, FSCRT_DOCUMENT document, FS_BOOL* changeMark);
	
	/** 
	 * @brief	Optional callback function to receives handles of all documents which are opened now.
	 *
	 * @details	This function would be called by Foxit PDF SDK twice to get handles of opened document:<br>
	 *			For the first time, set parameter <i>docs</i> to <b>NULL</b> to get the actual count of opened document.
	 *			The count value will be set to parameter <i>count</i> as a result returned by first calling.
	 *			Then use <i>count</i> to allocate <i>docs</i>.<br>
	 *			For the second time, input the allocated <i>docs</i> and its size <i>count</i>. 
	 *			When this function returns successfully, <i>docs</i> will get an array of opened documents and <i>count</i> will get the actual count.<br>
	 *			The size of the input array should not be less than the actual count.<br>
	 *
	 * @param[in]		clientData	Pointer to the interface structure itself.
	 * @param[in,out]	docs		Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives a array storing handles of all opened documents.
	 *								This can be <b>NULL</b> for getting actual count of opened documents before allocate this array. <br>
	 *								Please see detail description about how this callback function will be used.
	 * @param[in,out]	count		Pointer to a ::FS_INT32 object.<br>
	 *								When this function is called, it should be the size of array <i>docs</i> if the parameter <i>docs</i> isn't <b>NULL</b>.<br>
	 *								When this function returns, it will receive actual count of opened documents which are got.<br>
	 *								Please see detail description about how this callback function will be used.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 * 			::FSCRT_ERRCODE_BUFFEROVERFLOW if the parameter <i>docs</i> is valid but <i>count</i> is less than required amount.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetOpenedDocs)(FS_LPVOID clientData, FSCRT_DOCUMENT* docs, FS_INT32* count);
	
	/** 
	 * @brief	Optional callback function to pop up a dialogue to show warnings or hints.
	 *
	 * @param[in]	clientData	Pointer to the interface structure itself.
	 * @param[in]	msg			Pointer to a ::FSCRT_BSTR structure to specify the message to be displayed. It should be a UTF-8 string.
	 * @param[in]	title		Pointer to a ::FSCRT_BSTR structure to specify the title of the dialogue. It should be a UTF-8 string.
	 * @param[in]	type		Type of button group. Its value can be:<br>
	 *							<ul>
	 *							<li>0: OK;(default value.)</li>
	 *							<li>1: OK, Cancel;</li>
	 *							<li>2: Yes, NO; </li>
	 *							<li>3: Yes, NO, Cancel.</li>
	 *							</ul>
	 * @param[in]	icon		Icon type. Its value can be:<br>
	 *							<ul>
	 *							<li>0: Error;(default value.)</li>
	 *							<li>1: Warning;</li>
	 *							<li>2: Question;</li>
	 *							<li>3: Status.</li>
	 *							</ul>
	 * @param[out]	retCode		Pointer to a ::FS_INT32 object. It can be:<br>
	 *							<ul>
	 *							<li>1: OK;</li>
	 *							<li>2: Cancel; </li>
	 *							<li>3: NO;</li>
	 *							<li>4: Yes;</li>
	 *							</ul>
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*Alert)(FS_LPVOID clientData, const FSCRT_BSTR* msg, const FSCRT_BSTR* title, FS_INT32 type, FS_INT32 icon, FS_INT32* retCode);
	
	/** 
	 * @brief	Optional callback function to cause the system to play a sound. 
	 *
	 * @param[in]	clientData	Pointer to the interface structure itself.
	 * @param[in]	type		Sound type. Its value can be:<br>
	 *							<ul>
	 *							<li>0: Error</li>
	 *							<li>1: Warning</li>
	 *							<li>2: Question</li>
	 *							<li>3: Status</li>
	 *							<li>4: Default (default value)</li>
	 *							</ul>
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*Beep)(FS_LPVOID clientData, FS_INT32 type);
	
	/** 
	 * @brief	Optional callback function to display a dialogue box containing a question and an entry field for the user to reply to the question.  
	 *
	 * @param[in]	clientData		The user-supplied data.
	 * @param[in]	question		Pointer to a ::FSCRT_BSTR structure to specify the question to be posed to the user. It should be a UTF-8 string.
	 * @param[in]	title			Pointer to a ::FSCRT_BSTR structure to specify the title of the dialogue box. It should be a UTF-8 string.
	 * @param[in]	defaultValue	Pointer to a ::FSCRT_BSTR structure to specify a default value for the answer to the question. It should be a UTF-8 string.
	 *								If the answer is not specified, no default value is presented.
	 * @param[in]	label			Pointer to a ::FSCRT_BSTR structure to specify a short string to appear in front of the edit text field. It should be a UTF-8 string.
	 * @param[in]	isPassword		A boolean value that indicates whether user's response should be masked to show:<br>
	 *								<b>TRUE</b> means that the user's response should show as asterisks (*) or bullets (?) 
	 *								to mask the response, which might be sensitive information. <br>
	 *								Default: <b>FALSE</b>.
	 * @param[out]	response		Pointer to a ::FSCRT_BSTR structure that receives the user's response. It can be <b>NULL</b>.
	 *								And it should be a UTF-8 string if it's not <b>NULL</b>.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*Response)(FS_LPVOID clientData, const FSCRT_BSTR* question, const FSCRT_BSTR* title, const FSCRT_BSTR* defaultValue, 
							const FSCRT_BSTR* label, FS_BOOL isPassword, FSCRT_BSTR* response);
	
	/**
	 * @brief	Optional callback function to get the file path of current document. 
	 *
	 * @param[in]	clientData	The user-supplied data.
	 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
	 * @param[out]	filePath	Pointer to a ::FSCRT_BSTR structure that receives the file path. It can be <b>NULL</b>
	 *							And it should be a UTF-8 string if it's not <b>NULL</b>.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetFilePath)(FS_LPVOID clientData, FSCRT_DOCUMENT document, FSCRT_BSTR* filePath);
	
	/**
	 * @brief	Optional callback function to mail current PDF document as an attachment to all recipients, with or without user interaction. 
	 *
	 * @param[in]	clientData	The user-supplied data.
	 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
	 * @param[in]	bUI			A boolean value:<br>
	 *							<b>TRUE</b> means that the rest of the parameters are used in a compose-new-message window 
	 *							which is displayed to the user.<br>
	 *							<b>FALSE</b> means that the parameter <i>To</i> is required and all others are optional.
	 * @param[in]	To			Pointer to a ::FSCRT_BSTR structure to specify a semicolon-delimited list of recipients for the message. It should be a UTF-8 string.
	 * @param[in]	Subject		Pointer to a ::FSCRT_BSTR structure to specify the subject of the message. It should be a UTF-8 string.<br>
	 *							The limit of its length is 64 KB.
	 * @param[in]	CC			Pointer to a ::FSCRT_BSTR structure to specify a semicolon-delimited list of CC recipients for the message. It should be a UTF-8 string.
	 * @param[in]	BCC			Pointer to a ::FSCRT_BSTR structure to specify a semicolon-delimited list of BCC recipients for the message. It should be a UTF-8 string.
	 * @param[in]	Msg			Pointer to a ::FSCRT_BSTR structure to specify the content of the message. It should be a UTF-8 string.<br>
	 *							The limit of its length is 64 KB.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*Mail)(FS_LPVOID clientData, FSCRT_DOCUMENT document, FS_BOOL bUI, const FSCRT_BSTR* To, 
					    const FSCRT_BSTR* Subject, const FSCRT_BSTR* CC, const FSCRT_BSTR* BCC, const FSCRT_BSTR* Msg); 

	/**
	 * @brief	Optional callback function to print all or a specific number of pages of the document.
	 *
	 * @param[in]	clientData		The user-supplied data.
	 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
	 * @param[in]	isUI			<b>TRUE</b> means that a UI will be presented to the user to obtain printing information and confirm the action.
	 * @param[in]	start			A zero-based index of the start of an inclusive range of pages.
	 * @param[in]	end				A zero-based index of the end of an inclusive page range.
	 * @param[in]	isSilent		<b>TRUE</b> means that the cancel dialogue box will be suppressed while the document is printing. 
	 *								The default is <b>FALSE</b>.
	 * @param[in]	isShrinkToFit	<b>TRUE</b> means that the page is shrunk (if necessary) to fit within the area of the printed page.
	 * @param[in]	isPrintAsImage	<b>TRUE</b> means that it will print pages as an image.
	 * @param[in]	isReverse		<b>TRUE</b> means that it will print from <i>nEnd</i> to <i>nStart</i>.
	 * @param[in]	isAnnotations	<b>TRUE</b> means that annotations will be printed.The default is <b>TRUE</b>.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*Print)(FS_LPVOID clientData, FSCRT_DOCUMENT document, FS_BOOL isUI, FS_INT32 start, FS_INT32 end, FS_BOOL isSilent ,
					     FS_BOOL isShrinkToFit, FS_BOOL isPrintAsImage, FS_BOOL isReverse, FS_BOOL isAnnotations);

	/**
	 * @brief	Optional callback function to submit the form data to a specified URL.
	 *
	 * @param[in]	clientData	The user-supplied data.
	 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
	 * @param[in]	formData	Pointer to a data buffer which is to be submit.
	 * @param[in]	length		The size(in bytes) of the buffer parameter<i>formData</i>.
	 * @param[in]	URL			Pointer to a ::FSCRT_BSTR structure to specify a URL, to which the form data will be submit. It should be a UTF-8 string.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*SubmitForm)(FS_LPVOID clientData, FSCRT_DOCUMENT document, FS_LPVOID formData, FS_DWORD length, const FSCRT_BSTR* URL);
	
	/**
	 * @brief	Optional callback function to launch to a specified URL.
	 *
	 * @param[in]	clientData	The user-supplied data.
	 * @param[in]	URL			Pointer to a ::FSCRT_BSTR structure to specify a URL. It should be a UTF-8 string.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*LaunchURL)(FS_LPVOID clientData, const FSCRT_BSTR* URL); 

	/**
	 * @brief	Optional callback function to show a file selection dialogue, and return the selected file path.
	 *
	 * @param[in]	clientData	The user-supplied data.
	 * @param[out]	filePath	Pointer to a ::FSCRT_BSTR structure that receives the file path. It can be <b>NULL</b>
	 *							And it should be a UTF-8 string if it's not <b>NULL</b>.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note		The <i>filePath</i> should be always inputted in the local encoding.
	 */
	FS_RESULT	(*BrowseFile)(FS_LPVOID clientData, FSCRT_BSTR* filePath);

	/**
	 * @brief	Optional callback function to get the language of the running viewer application.
	 *
	 * @param[in]	clientData	The user-supplied data.
	 * @param[out]	language	Pointer to a ::FS_INT32 object that receives the language.
	 *							Please refer to macro definitions <b>FSCRT_LANGUAGE_XXX</b> and this should be one of these macros.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetLanguage)(FS_LPVOID clientData, FS_INT32* language);

	/*
	 * @brief	Optional callback function to get identity properties of the current user.
	 *
	 * @param[in]	clientData			The user-supplied data.
	 * @param[out]	identityProperties	Pointer to a ::FSPDF_IDENTITYPROPERTIES structure that receives the identity properties.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetIdentityProperties)(FS_LPVOID clientData, FSPDF_IDENTITYPROPERTIES* identityProperties);

	/**
	 * @brief	Optional callback function to pop up a menu window.
	 * 
	 * @details	Application should call function ::FSCRT_BStr_Set to set the value of <i>seletedMenu</i>, and do not call function ::FSCRT_BStr_Clear to free <i>seletedMenu</i>.
	 *			The position of menu window is same as cursor's. 
	 *
	 * @param[in]	clientData		The user-supplied data.
	 * @param[in]	menus			Pointer to an array of ::FSPDF_MENULIST object which is the menus.
	 * @param[in]	count			The size of <i>menus</i>.
	 * @param[out]	seletedMenu		Pointer to a ::FSCRT_BSTR structure that receives selected menu.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*PopupMenu)(FS_LPVOID clientData, const FSPDF_MENULIST* menus, FS_INT32 count, FSCRT_BSTR* seletedMenu);

} FSPDF_ACTION_HANDLER;

#endif /* _FSPDF_DEF_HANDLER_ACTION_ */

/**
 * @brief	Set the action handler to the PDF document.
 *
 * @note	Some interaction features such as performing JavaScript actions or filling the form, would require caller to implement the callback functions of action handler,
 *			in order to function well.	
 *
 * @param[in]	document			Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	actionHandler		Pointer to a ::FSPDF_ACTION_HANDLER structure.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>actionHandler</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_HANDLER if FSPDF_ACTION_HANDLER::InvalidateRect of parameter <i>actionHandler</i> is <b>NULL</b><br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_SetActionHandler(FSCRT_DOCUMENT document, FSPDF_ACTION_HANDLER* actionHandler);

/**
 * @brief	Perform the document javascript when document is opened, defining JavaScript functions for use by other scripts in the document.
 *
 * @param[in]	document			Handle to a <b>FSCRT_DOCUMENT</b> object which is a document object. It should be valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 *			::FSCRT_ERRCODE_UNKNOWNSTATE if the form module isn't loaded.
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to initialize JavaScript because of any other reason.<br>
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
FS_RESULT	FSPDF_Doc_InitiateJavaScript(FSCRT_DOCUMENT document);

/**
 * @brief	Perform the document javascript which is specified by the trigger.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a document object. It should be valid.
 * @param[in]	trigger		Type of the trigger event. Please refer to macro definitions <b>FSPDF_TRIGGER_DOC_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>doc</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if no javascript in document level can be found.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to preform the document javascript because of any other reason.<br>
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
FS_RESULT	FSPDF_Doc_DoJavaScriptAction(FSCRT_DOCUMENT document, FS_INT32 trigger);

/**
 * @brief	Get a document JavaScript action by its action name.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	name		Pointer to a ::FSCRT_BSTR structure to specify the name of a JavaScript action. It should be a UTF-8 string.
 * @param[out]	actionData	Pointer to a ::FSPDF_ACTIONDATA structure that receives trigger action data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>actionData</i> is a <b>NULL</b> pointer, or <i>name</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the JavaScript action is not found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get action because of any other reason.<br>
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
FS_RESULT	FSPDF_Doc_GetJSActionByName(FSCRT_DOCUMENT document, const FSCRT_BSTR* name, FSPDF_ACTIONDATA* actionData);

/*******************************************************************************/
/* PDF page label                                                              */
/*******************************************************************************/

#ifndef _FSPDF_DEF_MACRO_PAGELABEL_STYLE_
#define _FSPDF_DEF_MACRO_PAGELABEL_STYLE_
/**
 * @name 	Macro Definitions for PDF page label style
 * @note 	These flags indicate numbering styles to be used for the numeric portion of each page label.
 */
/**@{*/

/** @brief	No numbering style. */
#define		FSPDF_PAGELABEL_STYLE_None		0
/** @brief	Decimal arabic numerals. */
#define		FSPDF_PAGELABEL_STYLE_D			1
/** @brief	Uppercase roman numerals. */
#define		FSPDF_PAGELABEL_STYLE_R			2
/** @brief	Lowercase roman numerals. */
#define		FSPDF_PAGELABEL_STYLE_r			3
/** @brief	Uppercase letters (A to Z for the first 26 pages, AA to ZZ for the next 26, and so on). */
#define		FSPDF_PAGELABEL_STYLE_A			4
/** @brief	Lowercase letters (a to z for the first 26 pages, aa to zz for the next 26, and so on). */
#define		FSPDF_PAGELABEL_STYLE_a			5

/**@}*/
#endif /* _FSPDF_DEF_MACRO_PAGELABEL_STYLE_ */

/**
 * @brief	Convert a page label to page index.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	noCase		A ::FS_BOOL value which indicates to use case-insensitive when its value is <b>TRUE</b>, 
 *							or to use case-sensitive when its value is <b>FALSE</b>.
 * @param[in]	pageLabel	Pointer to a ::FSCRT_BSTR structure which is a page label. It should be a valid UTF-8 string.
 * @param[out]	pageIndex	Pointer to a ::FS_INT32 object that receives the page index corresponding to parameter <i>pageLabel</i>.
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i>, <i>pageLabel</i> or <i>pageIndex</i> is a <b>NULL</b> pointer, or <i>pageLabel</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>pageLabel</i> cannot match to a page.<br> 
 *			::FSCRT_ERRCODE_FORMAT if the parameter <i>pageLabel</i> is not in UTF-8 format.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to convert a page label to page index because of any other reason.<br>
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
FS_RESULT	FSPDF_Doc_PageLabelToPageIndex(FSCRT_DOCUMENT document, FS_BOOL noCase, const FSCRT_BSTR* pageLabel, FS_INT32* pageIndex);

/**
 * @brief	Convert a page index to page label.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	pageIndex	The index of page. Range: 0 to (pagecount-1). <i>pagecount</i> is returned by function ::FSPDF_Doc_CountPages.
 * @param[out]	pageLabel	Pointer to a ::FSCRT_BSTR structure that receives page label string. It will be in UTF-8 format
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> while calling this function, 
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>pageLabel</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>pageIndex</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note 	if the parameter <i>pageLabel</i> is empty or doens't have enough memory, this function will allocate memory by calling function ::FSCRT_BStr_SetLength.<br>
 * 			It's better for callers to prepare enough memory before calling this function.
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
FS_RESULT	FSPDF_Doc_PageIndexToPageLabel(FSCRT_DOCUMENT document, FS_INT32 pageIndex, FSCRT_BSTR* pageLabel);

/**
 * @brief	Get count of ranges of page labels which use different numbering systems.
 *
 * @details	For purposes of page labeling, a document can be divided into labeling ranges, each of which is a series of consecutive pages using the same numbering system.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	count		Pointer to a ::FS_INT32 object that receives count of labeling ranges. 
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>count</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSPDF_PageLabels_CountRanges(FSCRT_DOCUMENT document, FS_INT32* count);

/**
 * @brief	Get information of page labels by a specified range.
 *
 * @details	For purposes of page labeling, a document can be divided into labeling ranges, each of which is a series of consecutive pages using the same numbering system.
 *			The numbering system consists of some information of page labels.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	rangeIndex	The index of the current labeling range.
 *							Valid value is from 0 to (<i>count</i> - 1). <i>count</i> is returned by function ::FSPDF_PageLabels_CountRanges.
 * @param[out]	start		Pointer to a ::FS_INT32 object that receives the index of first page in the current range.
 *							If there's any error, it will be set -1.
 * @param[out]	style		Pointer to a ::FS_INT32 object that receives the numbering style to be used for the numeric portion of each page label.
 *							Please refer to macro definitions <b>FSPDF_PAGELABEL_STYLE_XXX</b> and it should be one of these macros.
 *							If the value is <b>FSPDF_PAGELABEL_STYLE_None</b>, page labels consist solely of a label prefix with no numeric portion.
 *							If there's any error, it will be set -1.
 * @param[out]	prefix		Pointer to a ::FSCRT_BSTR structure that receives a label prefix for page labels in the current range. It will be in UTF-8 format.
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> while calling this function.
 * @param[out]	st			Pointer to a ::FS_INT32 object that receives the value of the numeric portion for the first page label in the current range.
 *							Subsequent pages are numbered sequentially from this value, which must be greater than or equal to 1.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>start</i> or <i>style</i> or <i>prefix</i> or <i>st</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>rangeIndex</i> is out of range, or no page labels exist.<br>
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
FS_RESULT	FSPDF_PageLabels_GetRangeInfo(FSCRT_DOCUMENT document, FS_INT32 rangeIndex, FS_INT32* start, FS_INT32* style, FSCRT_BSTR* prefix, FS_INT32* st);

/*******************************************************************************/
/* Access PDF metadata                                                         */
/*******************************************************************************/
/**
 * @brief	Get a UTF-8 string value from metadata.
 *
 * @details	Metadata provides some application level information about document, such as author, title, creation time and others. <br>
 *			There are two ways to store these information in PDF file: 
 *			<ul>
 *			<li> in "Info" dictionary in trail dictionary.</li>
 *			<li> in metadata stream (with XML format) in the "Catalog" dictionary. </li>
 *			</ul>
 *			Which information would be got depends on the information of modified date, which is defined in key "ModDate" in the "Info" dictionary and "MetadataDate" in XML.
 * 
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	key			Pointer to a UTF-8 key string, and it should be a valid pointer to ::FSCRT_BSTR structure.<br>
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
 *							</ul>
 * @param[out]	string		Pointer to a ::FSCRT_BSTR structure that receives a UTF-8 string value associated to parameter <i>key</i>.
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> while calling this function, 
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i>, <i>key</i> or <i>string</i> is a <b>NULL</b> pointer, or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>key</i> is not found in metadata or document doesn't have metadata information.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note 	if the parameter <i>string</i> is empty or doesn't have enough memory, this function will allocate memory by calling function ::FSCRT_BStr_SetLength.<br>
 * 			It's better for caller to prepare enough memory before calling this function.
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
FS_RESULT	FSPDF_Metadata_GetString(FSCRT_DOCUMENT document, const FSCRT_BSTR* key, FSCRT_BSTR* string);

/**
 * @brief	Get an UTF-8 string array value from metadata.
 *
 * @details	Metadata provides some application level information about document, such as author, title, creation time and others. <br>
 *			There are two ways to store these information in PDF file: 
 *			<ul>
 *			<li> in "Info" dictionary in trail dictionary.</li>
 *			<li> in metadata stream (with XML format) in the "Catalog" dictionary. </li>
 *			</ul>
 *			Which information would be got depends on the information of modified date, which is defined in key "ModDate" in the "Info" dictionary and "MetadataDate" in XML.<br>
 *			There could be multiple string values associated with the same key,so the result is received as an array. 
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.It should be valid.
 * @param[in]	key				Pointer to a UTF-8 key string, and it should be a valid pointer to ::FSCRT_BSTR structure.<br>
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
 * @param[out]	stringArray		Pointer to a ::FSCRT_ARRAY structure that receives an UTF-8 string array value associated to parameter <i>key</i>.
 *								Application should call function ::FSCRT_Array_Init to initialize it and ::FSCRT_Array_Clear to release it.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i>, <i>key</i>, or <i>stringArray</i> is a <b>NULL</b> pointer,
 *			<i>stringArray::dataType</i> is not FSCRT_VT_BSTR, or <i>key</i> is empty.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>key</i> is not found in metadata or document doesn't have metadata information.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
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
FS_RESULT	FSPDF_Metadata_GetStringArray(FSCRT_DOCUMENT document, const FSCRT_BSTR* key, FSCRT_ARRAY* stringArray);

/**
 * @brief	Get a date and time value from metadata.
 *
 * @details	Metadata provides some application level information about document, such as author, title, creation time and others. <br>
 *			There're two ways to store these information in PDF file: 
 *			<ul>
 *			<li> in "Info" dictionary in trail dictionary.</li>
 *			<li> in metadata stream (with XML format) in the "Catalog" dictionary. </li>
 *			</ul>
 *			Which information would be got depends on the information of modified date, which is defined in key "ModDate" in the "Info" dictionary and "MetadataDate" in XML.<br>
 *			This function will get the latest modified date time between these two ways.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	key			Pointer to a UTF-8 key string, it should be a valid pointer to ::FSCRT_BSTR structure.<br>
 *							Currently it can be one of the followings:
 *							<ul>
 *							<li>"CreationDate"</li>
 *							<li>"ModDate"</li>
 *							<li>Some other custom information keys, if they're supported by the PDF file.</li>
 *							</ul>
 * @param[out]	dt			Pointer to a ::FSCRT_DATETIMEZONE structure that receives a date and time value associated to parameters <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>key</i> or <i>dt</i> is a <b>NULL</b> pointer, or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>key</i> is not found in dictionary document doesn't have metadata information.<br>
 * 			::FSCRT_ERRCODE_FORMAT if the data and time at parameter <i>key</i> position is empty or is not a valid format.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
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
FS_RESULT	FSPDF_Metadata_GetDateTime(FSCRT_DOCUMENT document, const FSCRT_BSTR* key, FSCRT_DATETIMEZONE* dt);

/*******************************************************************************/
/* Access PDF bookmarks                                                        */
/*******************************************************************************/
#ifndef _FSPDF_DEF_HANDLE_BOOKMARK_ITERATOR_
#define _FSPDF_DEF_HANDLE_BOOKMARK_ITERATOR_

/** @brief	Handle type to PDF bookmark iterator. */
FSCRT_DEFINEHANDLE(FSPDF_BOOKMARK_ITERATOR);

#endif /* _FSPDF_DEF_HANDLE_BOOKMARK_ITERATOR_ */

#ifndef _FSPDF_DEF_HANDLE_BOOKMARK_POS_
#define _FSPDF_DEF_HANDLE_BOOKMARK_POS_

/** @brief	Handle type to PDF bookmark position. */
FSCRT_DEFINEHANDLE(FSPDF_BOOKMARKPOS);

#endif /* _FSPDF_DEF_HANDLE_BOOKMARK_POS_ */

#ifndef _FSPDF_DEF_MACRO_BOOKMARKSTATUS_
#define _FSPDF_DEF_MACRO_BOOKMARKSTATUS_
/**
 * @name	Macros for Bookmark Status
 * @note	Each bookmark item has the status to indicate how to display it.<br>
 * 			Combine the following flags while using them in FSPDF_BOOKMARKDATA::status.
 */
/**@{*/

/** @brief	Show title as normal text in bookmark. */
#define FSPDF_BOOKMARKSTATUS_NORMAL			0
/** @brief	Show title as bold text in bookmark. */
#define FSPDF_BOOKMARKSTATUS_BOLD			1
/** @brief	Show title as italic text in bookmark. */
#define FSPDF_BOOKMARKSTATUS_ITALIC			2
/** 
 * @brief	Expand bookmark.
 *
 * @details	Specify current bookmark is expanded or collapsed if it has children. It's insignificant if it's a leaf node. 
 */
#define FSPDF_BOOKMARKSTATUS_EXPANDED		4

/**@}*/
#endif /* _FSPDF_DEF_MACRO_BOOKMARKSTATUS_ */

#ifndef _FSPDF_DEF_MACRO_BOOKMARKPOS_
#define _FSPDF_DEF_MACRO_BOOKMARKPOS_
/**
 * @name	Macros for Bookmark Position
 * @note	Bookmark position specifies where a new bookmark item is inserted.<br>
 * 			Please refer to function ::FSPDF_Bookmark_Insert.
 */
/**@{*/

/** @brief	Position as first child. */
#define FSPDF_BOOKMARKPOS_FIRSTCHILD		0
/** @brief	Position as last child. */
#define FSPDF_BOOKMARKPOS_LASTCHILD			1
/** @brief	Position as previous sibling. */
#define FSPDF_BOOKMARKPOS_PREVIOUS			2
/** @brief	Position as next sibling. */
#define FSPDF_BOOKMARKPOS_NEXT				3
/** @brief	Position as first sibling. */
#define FSPDF_BOOKMARKPOS_FIRSTSIBLING		4
/** @brief	Position as last sibling. */
#define FSPDF_BOOKMARKPOS_LASTSIBLING		5

/**@}*/
#endif /* _FSPDF_DEF_MACRO_BOOKMARKPOS_ */

#ifndef _FSPDF_DEF_STRUCTURE_BOOKMARKDATA_
#define _FSPDF_DEF_STRUCTURE_BOOKMARKDATA_

/**
 * @brief	Structure for bookmark data.
 *
 * @note	This structure provides a way to access bookmark data as a whole.
 */
typedef struct _FSPDF_BOOKMARKDATA_
{
	/** @brief	Bookmark title, a UTF-8 string object. */
	FSCRT_BSTR		title;
	/** @brief	Color used for displaying title. Format:0xAARRGGBB and alpha component is omitted. */
	FS_ARGB			color;
	/**
	 * @brief	Current status of bookmark.
	 *
	 * @details	Please refer to macro definitions <b>FSPDF_BOOKMARKSTATUS_XXX</b> and this can be one or a combination of these macros.
	 */
	FS_DWORD		status;
} FSPDF_BOOKMARKDATA;

#endif /* _FSPDF_DEF_STRUCTURE_BOOKMARKDATA_ */

/**
 * @brief	Helper function to initialize a bookmark data object.
 *
 * @param[in]	bmData	Pointer to a ::FSPDF_BOOKMARKDATA structure which is a valid bookmark data object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bmData</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to initialize a bookmark data variant.<br>
 *			It sets FSPDF_BOOKMARKDATA::title as a <b>NULL</b> pointer, and sets FSPDF_BOOKMARKDATA::color, FSPDF_BOOKMARKDATA::status as 0.<br>
 *			Applications can initialize a ::FSPDF_BOOKMARKDATA structure in other ways instead of calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_BookmarkData_Init(FSPDF_BOOKMARKDATA* bmData);

/**
 * @brief	Helper function to clear a bookmark data.
 *
 * @param[in]	bmData	Pointer to a ::FSPDF_BOOKMARKDATA structure which is a valid bookmark data object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bmData</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to clear bookmark.<br>
 *			It frees FSPDF_BOOKMARKDATA::title at first and sets it to a <b>NULL</b> pointer, and then sets FSPDF_BOOKMARKDATA::color, FSPDF_BOOKMARKDATA::status to 0.<br>
 *			This function calls function ::FSCRT_Memory_Free to free FSPDF_BOOKMARKDATA::title.<br>
 *			Applications can free a ::FSPDF_BOOKMARKDATA structure in other ways instead of calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_BookmarkData_Clear(FSPDF_BOOKMARKDATA* bmData);

/**
 * @brief	Create an iterator to access bookmark in a document.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	iterator	Pointer to a <b>FSPDF_BOOKMARK_ITERATOR</b> handle that receives an iterator object which presents the root.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>iterator</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to create a bookmark iterator because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	When a bookmark iterator is created, its position is the root.<br>
 * 			call function ::FSPDF_Bookmark_ReleaseIterator to release a bookmark iterator.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_CreateBookmarkIterator(FSCRT_DOCUMENT document, FSPDF_BOOKMARK_ITERATOR* iterator);

/**
 * @brief	Get the bookmark position handle from a bookmark iterator.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a valid handle of bookmark iterator.
 * @param[out]	pos			Pointer to a <b>FSPDF_BOOKMARKPOS</b> handle that receives the bookmark position object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>pos</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get the bookmark position handle because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pos</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_GetPos(FSPDF_BOOKMARK_ITERATOR iterator, FSPDF_BOOKMARKPOS* pos);

/**
 * @brief	Clone an iterator to access bookmark in a document.
 *
 * @param[in]	srcIterator		Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a valid handle of bookmark iterator.
 * @param[out]	clonedIterator	Pointer to a <b>FSPDF_BOOKMARK_ITERATOR</b> handle that receives cloned iterator object.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>srcIterator</i> or <i>clonedIterator</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to clone bookmark iterator because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	A cloned bookmark iterator has the same properties as source iterators, including its position.<br>
 * 			Call function ::FSPDF_Bookmark_ReleaseIterator to release the clone bookmark iterator if no use.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>clonedIterator</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_CloneIterator(FSPDF_BOOKMARK_ITERATOR srcIterator, FSPDF_BOOKMARK_ITERATOR* clonedIterator);

/**
 * @brief	Release a bookmark iterator.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_ReleaseIterator(FSPDF_BOOKMARK_ITERATOR iterator);

/**
 * @brief	Release a bookmark position handle.
 *
 * @param[in]	pos		Handle to a <b>FSPDF_BOOKMARKPOS</b> object which is a bookmark position object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>pos</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pos</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_ReleasePos(FSPDF_BOOKMARKPOS pos);

/**
 * @brief	Move a bookmark iterator to root.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT	FSPDF_Bookmark_MoveToRoot(FSPDF_BOOKMARK_ITERATOR iterator);

/**
 * @brief	Determine whether a bookmark iterator is root or not.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[out]	isRoot		Pointer to a ::FS_BOOL object that receives the root state:
 *							<ul>
 *							<li><b>TRUE</b>: parameter <i>iterator</i> points to root.</li>
 *							<li><b>FALSE</b>: parameter <i>iterator</i> doesn't point to root.</li>
 *							</ul>
 *							If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>isRoot</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT	FSPDF_Bookmark_IsRoot(FSPDF_BOOKMARK_ITERATOR iterator, FS_BOOL* isRoot);

/**
 * @brief	Move a bookmark iterator to its parent if existing.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>iterator</i> has no parent.<br>
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
FS_RESULT	FSPDF_Bookmark_MoveToParent(FSPDF_BOOKMARK_ITERATOR iterator);

/**
 * @brief	Move a bookmark iterator to its first child if existing.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>iterator</i> has no child.<br>
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
FS_RESULT	FSPDF_Bookmark_MoveToFirstChild(FSPDF_BOOKMARK_ITERATOR iterator);

/**
 * @brief	Move a bookmark iterator to its next sibling if existing.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>iterator</i> has no next sibling.<br>
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
FS_RESULT	FSPDF_Bookmark_MoveToNextSibling(FSPDF_BOOKMARK_ITERATOR iterator);

/**
 * @brief	Move a bookmark iterator to its previous sibling if existing.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>iterator</i> has no previous sibling.<br>
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
FS_RESULT	FSPDF_Bookmark_MoveToPrevSibling(FSPDF_BOOKMARK_ITERATOR iterator);

/**
 * @brief	Move a bookmark iterator to a specific position.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[in]	newPos		Handle to a <b>FSPDF_BOOKMARKPOS</b> object which specific the new position to move to.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>newPos</i>is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>newPos</i> pointer to an invalid position.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>iterator</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>newPos</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Bookmark_MoveToPos(FSPDF_BOOKMARK_ITERATOR iterator, FSPDF_BOOKMARKPOS newPos);

/**
 * @brief	Detect whether a bookmark iterator has a child or not.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[out]	hasChild	Pointer to a ::FS_BOOL object that receives the state whether a bookmark itearator has child:
 *							<ul>
 *							<li><b>TRUE</b>: parameter <i>iterator</i> has the child node</li>
 *							<li><b>FALSE</b>: parameter <i>iterator</i> doesn't have the child node.</li>
 *							</ul>
 *							If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>hasChild</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
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
FS_RESULT	FSPDF_Bookmark_HasChild(FSPDF_BOOKMARK_ITERATOR iterator, FS_BOOL* hasChild);

/**
 * @brief	Determine whether a bookmark iterator is the first child of its parent or not.
 *
 * @param[in]	iterator		Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[out]	isFirstChild	Pointer to a ::FS_BOOL object that receives the position state: 
 *								<ul>
 *								<li><b>TRUE</b>: parameter <i>iterator</i> points to the first child of its parent.</li>
 *								<li><b>FALSE</b>: parameter <i>iterator</i> doesn't point to the first child of its parent.</li>
 *								</ul>
 *								If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>isFirstChild</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT	FSPDF_Bookmark_IsFirstChild(FSPDF_BOOKMARK_ITERATOR iterator, FS_BOOL* isFirstChild);

/**
 * @brief	Determine whether a bookmark iterator is the last child of its parent or not.
 *
 * @param[in]	iterator		Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[out]	isLastChild		Pointer to a ::FS_BOOL object that receives the position state.
 *								<ul>
 *								<li><b>TRUE</b>: parameter <i>iterator</i> points to the last child of its parent.</li>
 *								<li><b>FALSE</b>: parameter <i>iterator</i> doesn't point to the last child of its parent.</li>
 *								</ul>
 *								If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>isLastChild</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT	FSPDF_Bookmark_IsLastChild(FSPDF_BOOKMARK_ITERATOR iterator, FS_BOOL* isLastChild);

/**
 * @brief	Get current bookmark iterator's data which is indicated by parameter <i>iterator</i>.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[out]	bmData		Pointer to a ::FSPDF_BOOKMARKDATA structure that receives the bookmark data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>bmData</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
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
FS_RESULT	FSPDF_Bookmark_GetData(FSPDF_BOOKMARK_ITERATOR iterator, FSPDF_BOOKMARKDATA* bmData);

/**
 * @brief	Get counts of bookmark action.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[out]	count		Pointer to a ::FS_INT32 object that receives action counts.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>count</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT	FSPDF_Bookmark_CountActions(FSPDF_BOOKMARK_ITERATOR iterator, FS_INT32* count);

/**
 * @brief	Get bookmark action.
 *
 * @param[in]	iterator	Handle to a <b>FSPDF_BOOKMARK_ITERATOR</b> object which is a bookmark iterator object.
 * @param[in]	index		Index of bookmark action. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Bookmark_CountActions.
 * @param[out]	actionData	Pointer to a ::FSPDF_ACTIONDATA structure that receives action data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>iterator</i> or <i>actionData</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of rang or no action is found. <br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
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
FS_RESULT	FSPDF_Bookmark_GetAction(FSPDF_BOOKMARK_ITERATOR iterator, FS_INT32 index, FSPDF_ACTIONDATA* actionData);

/*******************************************************************************/
/* Access PDF viewer preferences                                               */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_READDIREC_
#define _FSPDF_DEF_MACRO_READDIREC_
/** @name	Macro Definitions for Reading Directions. */
/**@{*/

/** @brief	Reading direction from left to right. */
#define		FSPDF_READDIRECT_L2R			0
/** @brief	Reading direction from right to left. */
#define		FSPDF_READDIRECT_R2L			1

/**@}*/
#endif /* _FSPDF_DEF_MACRO_READDIREC_ */

/**
 * @brief	Get UI visibility status from viewer preferences.
 *
 * @details	Viewer preferences defines the way that a document is to be presented on the screen or in print.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	uiItem		Pointer to a UTF-8 key string, it should be a valid pointer to ::FSCRT_BSTR structure.<br>
 * 							Currently it can be one of the followings:<br>
 *							<ul>
 *							<li>"HideToolbar"</li>
 *							<li>"HideMenubar"</li>
 *							<li>"HideWindowUI"</li>
 *							<li>"FitWindow"</li>
 *							<li>"CenterWindow"</li>
 *							<li>"DisplayDocTitle"</li>
 *							<li>Some other custom UI item keys, if they're supported by PDF.</li>
 *							</ul>
 * @param[out]	uiVisible	Pointer to a ::FS_BOOL object that receives a boolean value. Default: <b>FALSE</b><br>
 *							If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>uiItem</i> or <i>uiVisible</i> is a <b>NULL</b> pointer, or <i>uiItem</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>uiItem</i> is not found in viewer preferences.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get UI visibility status because of any other reason.<br>
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
FS_RESULT	FSPDF_ViewerPref_GetUIVisibility(FSCRT_DOCUMENT document, const FSCRT_BSTR* uiItem, FS_BOOL* uiVisible);

/**
 * @brief	Get display mode for non full-screen mode from viewer preferences.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	displayMode		Pointer to a ::FS_INT32 object to get display mode. 
 * 								It should be one of the followings: <br>
 * 								<ul>
 * 								<li>::FSPDF_DISPLAYMODE_USENONE</li>
 * 								<li>::FSPDF_DISPLAYMODE_USEOUTLINES</li>
 * 								<li>::FSPDF_DISPLAYMODE_USETHUMBS</li>
 * 								<li>::FSPDF_DISPLAYMODE_USEOC</li>
 *								</ul>
 *								Default: ::FSPDF_DISPLAYMODE_USENONE<br>
 *								If there's any error, it will be set -1. 
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>displayMode</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get display mode for non full-screen because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	For normal document display mode, call function ::FSPDF_Doc_GetDisplayMode to retrieve.
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
FS_RESULT	FSPDF_ViewerPref_GetNonFullScreenPageMode(FSCRT_DOCUMENT document, FS_INT32* displayMode);

/**
 * @brief	Get reading direction from viewer preferences.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	direction	Pointer to a ::FS_INT32 object that receives reading direction:<br>
 *							<ul>
 *							<li>::FSPDF_READDIRECT_L2R: left-to-right reading order.</li>
 *							<li>::FSPDF_READDIRECT_R2L: right-to-left reading order.</li>
 *							</ul>
 *							Default: ::FSPDF_READDIRECT_L2R<br>
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>direction</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get reading direction because of any other reason.<br>
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
FS_RESULT	FSPDF_ViewerPref_GetReadingDirection(FSCRT_DOCUMENT document, FS_INT32* direction);

/**
 * @brief	Get the type of area item from viewer preferences.
 *
 * @details	Viewer preferences defines the way that a document is to be presented on the screen or in print.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	boxItem		Pointer to a UTF-8 key string, it should be a valid pointer to ::FSCRT_BSTR structure.<br>
 * 							Currently it can be one of the followings: <br>
 *							<ul>
 *							<li>"ViewArea"</li>
 *							<li>"ViewClip"</li>
 *							<li>"PrintArea"</li>
 *							<li>"PrintClip"</li>
 *							</ul>
 * @param[out]	boxType		Pointer to a ::FS_INT32 object that receives the page box type. 
 *							Please refer to macro definitions <b>FSPDF_PAGEBOX_XXX</b> and this should be one of these macros.<br>
 *							Default: ::FSPDF_PAGEBOX_CROPBOX<br>
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>boxItem</i> or <i>boxType</i> is a <b>NULL</b> pointer, or <i>boxItem</i> is empty or invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>boxItem</i> is not found in viewer preferences.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get area type because of any other reason.<br>
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
FS_RESULT	FSPDF_ViewerPref_GetAreaType(FSCRT_DOCUMENT document, const FSCRT_BSTR* boxItem, FS_INT32* boxType);

/**
 * @brief	Get page scaling option from viewer preferences.
 *
 * @details	Viewer preferences defines the way that a document is to be presented on the screen or in print.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	printScale	Pointer to a ::FSCRT_BSTR structure that receives a UTF-8 string value which specifies page scale.
 *							It would be one of following:
 *							<ul>
 *							<li>"None": the print dialogue should reflect no page scaling.</li>
 *							<li>"AppDefault": applications should use the current print scaling.</li>
 *							<li>Other: applications should use the current print scaling.</li>
 *							</ul>
 *							Default: "AppDefault"<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> while calling this function, 
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>printScale</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get print scale because of any other reason.<br>
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
FS_RESULT	FSPDF_ViewerPref_GetPrintScale(FSCRT_DOCUMENT document, FSCRT_BSTR* printScale);

/**
 * @brief	Get the number of copies to be printed.
 *
 * @details	Viewer preferences defines the way that a document is to be presented on the screen or in print.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	copies		Pointer to a ::FS_INT32 object that receives the number of copies to be printed when the print 
 *							dialogue is opened for this file.<br>
 *							Supported values are the integers 2 through 5. Values outside this range are ignored. 
 *							Default value: as defined by PDF viewer application, but typically 1.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>copies</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get print copies because of any other reason.<br>
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
FS_RESULT	FSPDF_ViewerPref_GetPrintCopies(FSCRT_DOCUMENT document, FS_INT32* copies);

/**
 * @brief	Get page ranges which allowed to print.
 *
 * @details	Viewer preferences defines the way that a document is to be presented on the screen or in print.
 *	
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	pageRanges	Pointer to a ::FS_INT32 object array that receives the page ranges to be printed. 
 * 							In this array, 2 numbers are a pair: the first integer is the starting page number, 
 *							and the second integer is the last page number. The first page of the PDF file is denoted by 1<br>
 *							If it's <b>NULL</b>, parameter <i>count</i> receives total count of elements of all page ranges.<br>
 * @param[out]	count		Pointer to a ::FS_INT32 object that receives the count of elements in parameter <i>pageRanges</i>.<br>
 *						
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>count</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if document doesn't have viewer preferences or viewer preferences doesn't have entry "PrintPageRange".<br>
 * 			::FSCRT_ERRCODE_BUFFEROVERFLOW if the parameter <i>pageRanges</i> is valid but <i>count</i> is less than required amount.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter <i>document</i> hasn't been parsed successfully when being loaded or reloaded.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to get print ranges because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Commonly, this function is called twice, pass <b>NULL</b> to parameter <i>pageRanges</i> at first to retrieve the count of page ranges, 
 *			and call it again when <i>pageRanges</i> contains enough space. Parameter <i>count</i> should never be empty.
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
FS_RESULT	FSPDF_ViewerPref_GetPrintRanges(FSCRT_DOCUMENT document, FS_INT32* pageRanges, FS_INT32* count);

/*******************************************************************************/
/* PDF attachments                                                             */
/*******************************************************************************/
#ifndef _FSPDF_DEF_HANDLE_ATTACHMENTS_
#define _FSPDF_DEF_HANDLE_ATTACHMENTS_

/** @brief	Handle type to PDF attachments. */
FSCRT_DEFINEHANDLE(FSPDF_ATTACHMENTS);

#endif /* _FSPDF_DEF_HANDLE_ATTACHMENTS_ */

/** 
 * @brief	Load all attachments of PDF document.
 * 
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	attachments		Pointer to a <b>FSPDF_ATTACHMENTS</b> handle that receives an attachments object.
 *								If there's any error, it will be <b>NULL</b>.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>attachments</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if cannot load attachments because of any other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>attachments</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_LoadAttachments(FSCRT_DOCUMENT document, FSPDF_ATTACHMENTS* attachments);

/**
 * @brief	Release a attachments object.
 *
 * @param[in]	attachments		Handle to a <b>FSPDF_ATTACHMENTS</b> object returned by function ::FSPDF_Doc_LoadAttachments.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachments</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>attachments</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachments_Release(FSPDF_ATTACHMENTS attachments);

/**
 * @brief	Get the count of attachments.
 *
 * @param[in]	attachments		Handle to a <b>FSPDF_ATTACHMENTS</b> object returned by function ::FSPDF_Doc_LoadAttachments.
 * @param[out]	count			Pointer to a ::FS_INT32 object that receives attachments counts.
 *								If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachments</i> or <i>count</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>attachments</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachments_CountAttachment(FSPDF_ATTACHMENTS attachments, FS_INT32* count);

/**
 * @brief	Get a specific attachment.
 *
 * @param[in]	attachments		Handle to a <b>FSPDF_ATTACHMENTS</b> object returned by function ::FSPDF_Doc_LoadAttachments.
 * @param[in]	index			Index of attachment. Range: 0 to (attachmentcount-1). <i>attachmentcount</i> is returned by function ::FSPDF_Attachments_CountAttachment.
 * @param[out]	attachment		Pointer to a <b>FSPDF_ATTACHMENT</b> handle that receives specific attachment.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachments</i> or <i>attachment</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of range.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>attachments</i>: this handle is long-term recoverable.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachments_GetAttachment(FSPDF_ATTACHMENTS attachments, FS_INT32 index, FSPDF_ATTACHMENT* attachment);

/*******************************************************************************/
/* PDF Fonts                                                                   */
/*******************************************************************************/
/**
 * @brief	Count all the PDF fonts in the document, this function would enumerate all the font resources for pages, annots, and AcroForm.
 * 
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	count		Pointer to a integer object that receives the count of fonts.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i>, or <i>count</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
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
FS_RESULT	FSPDF_Doc_CountFonts(FSCRT_DOCUMENT document, FS_INT32* count);

/**
 * @brief	Get the specific PDF font in the document.
 * 
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	index		The index of the specific font.
 * @param[out]	font		Pointer to a <b>FSCRT_FONT</b> handle that receives the specific font.<br>
 *							Caller may use functions <b>FSCRT_Font_XXX</b> to get the basic font information 
 *							or <b>FSPDF_Font_XXX</b> to get font information that related to PDF document.
 *							Function ::FSCRT_Font_Release should be called to release the font when it's not used.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i>, or <i>font</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
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
FS_RESULT FSPDF_Doc_GetFontByIndex(FSCRT_DOCUMENT document, FS_INT32 index, FSCRT_FONT* font);

/*******************************************************************************/
/* Memory optimition                                                           */
/*******************************************************************************/
/**
* @brief	Clear the cache of PDF document(temporarily only for rendering), to reduce the memory usage.
*
* @param[in]	document	 Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
*
* @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
*			::FSCRT_ERRCODE_PARAM if <i>document</i> is <b>NULL</b>.
*			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or removing action is not allowed.<br>
* 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
*			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
*			::FSCRT_ERRCODE_ERROR if failing to clear cache because of any other reason.
* 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
*			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
*
* @attention	<b>Thread Safety</b>: this function is thread safe.<br>
*				<b>OOM Information</b>:<br>
*				OOM handling is only for mobile platforms, not for server or desktop.<br>
*				<ul>
*				<li>This function is short-term.</li>
*				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
*				</ul>
*				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
*/
FS_RESULT	FSPDF_Doc_ClearCache(FSCRT_DOCUMENT document);


#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFDOCUMENT */

#endif /* _FSPDF_DOCUMENT_R_H_ */

