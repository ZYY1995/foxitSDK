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
 * @file	ffdf_document_w.h
 * @brief	Header file for \ref FFDFDOCUMENT "FDF Document" module of Foxit PDF SDK.
 * @details	This header file defines FDF document data supports.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Create and save FDF document. </li>
 *			<li>2. Set FDF data. </li>
 *			<li>3. Import or export PDF annotations. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Annotation Add-on</b> or <b>Form Add-on</b> explicitly.
 */

#ifndef _FSFDF_DOCUMENT_W_H_
#define _FSFDF_DOCUMENT_W_H_

/** 
 * @defgroup	FFDFDOCUMENT FDF Document
 * @brief		Definitions for access to FDF document.<br>
 *				Definitions and functions in this module are included in ffdf_document_r.h and ffdf_document_w.h.<br>
 *				Module: FDFDocument<br>
 *				License Identifier: FDFDocument/All<br>
 *				Available License Right: Reading/Writing<br>
 *				For License Right <b>Reading</b>, see ffdf_document_r.h.<br>
 *				For License Right <b>Writing</b>, see ffdf_document_w.h.<br>
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. FDF document:
 *					<ul>
 *					<li>a. Load, create or save FDF document, and get or set PDF path.</li>
 *					<li>b. FDF is used to store PDF form data or annotation data, and it can be shared separately without original PDF file.
 *						   FDF data can be saved as traditional FDF file or other file formats. At present, only FDF is supported.</li>
 *					</ul>
 *				</li>
 *				<li>2. FDF annotation:
 *					<ul>
 *					<li>a. Enumerate annotations in FDF, export markup annotation from PDF to FDF or import markup annotation from FDF into PDF page.</li>
 *					<li>b. FDF annotation and PDF annotation use the same presentation, but they are different.
 *						   User can use functions defined in fpdf_annot_r.h to retrieve properties.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* FDF document                                                                */
/*******************************************************************************/
/**
 * @brief	Create a new FDF document.
 *
 * @param[in]	format		FDF document format type. Currently only ::FSCRT_DOCUMENTTYPE_FDF is supported.
 * @param[out]	fdfDoc		Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives a FDF document.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fdfDoc</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to FDF document is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>format</i> is invalid.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if FDF document cannot be created because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>fdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSFDF_Doc_Create(FS_INT32 format, FSCRT_DOCUMENT* fdfDoc);

/**
 * @brief	Save a FDF document.
 *
 * @param[in]	fdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a FDF document object.
 * @param[in]	fdfFile		Handle to a <b>FSCRT_FILE</b> object to which <i>fdfDoc</i> is to be saved.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fdfDoc</i> or <i>fdfFile</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>fdfDoc</i> is not a valid FDF document.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_FILE if data cannot be written into <i>fdfFile</i>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>fdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>fdfFile</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSFDF_Doc_Save(FSCRT_DOCUMENT fdfDoc, FSCRT_FILE fdfFile);

/**
 * @brief	Set the path of PDF document to FDF document. It's a UTF-8 string. 
 *
 * @details	The path can be either an absolute one, or a relative one.<br>
 *			The function applies to the ::FSCRT_DOCUMENTTYPE_FDF document, which contains elements required to export or import interactive form data.
 *
 * @param[in]	fdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a FDF document object.
 * @param[in]	pdfPath		A ::FSCRT_BSTR pointer to a const path UTF-8 string.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fdfDoc</i> or <i>pdfPath</i> is <b>NULL</b> or <i>pdfPath->str</i> is <b>NULL</b> or <i>pdfPath->len</i> is less than 1.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>fdfDoc</i> is not a valid FDF document.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>fdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSFDF_Doc_SetPDFPath(FSCRT_DOCUMENT fdfDoc, const FSCRT_BSTR* pdfPath);

/*******************************************************************************/
/* FDF annotation                                                              */
/*******************************************************************************/
/**
 * @brief	Export a PDF annotation into a FDF document.
 * 
 * @details	This function only support following annotation types:
 *					::FSPDF_ANNOTTYPE_TEXT, ::FSPDF_ANNOTTYPE_FREETEXT, ::FSPDF_ANNOTTYPE_LINE, ::FSPDF_ANNOTTYPE_SQUARE, ::FSPDF_ANNOTTYPE_CIRCLE, 
 *					::FSPDF_ANNOTTYPE_POLYGON, ::FSPDF_ANNOTTYPE_POLYLINE, ::FSPDF_ANNOTTYPE_HIGHLIGHT, ::FSPDF_ANNOTTYPE_UNDERLINE, ::FSPDF_ANNOTTYPE_SQUIGGLY, 
 *					::FSPDF_ANNOTTYPE_STRIKEOUT, ::FSPDF_ANNOTTYPE_STAMP, ::FSPDF_ANNOTTYPE_CARET, ::FSPDF_ANNOTTYPE_INK, ::FSPDF_ANNOTTYPE_FILEATTACHMENT.
 *
 * @param[in]	pdfAnnot	Handle to a <b>FSCRT_ANNOT</b> object in a PDF page.
 * @param[in]	fdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a FDF document object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pdfAnnot</i> or <i>fdfDoc</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>pdfAnnot</i> is not a valid PDF annotation, or <i>fdfDoc</i> is not a valid FDF document, or the annotation is not markup.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If the annotation contains a Popup annotation, the Popup annotation will be also exported along in the meantime, but it could not be exported separately.
 * 
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>pdfAnnot</i>: this handle is short-term.</li>
 *				<li> <i>fdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_ExportToFDFDoc(FSCRT_ANNOT pdfAnnot, FSCRT_DOCUMENT fdfDoc);

/**
 * @brief	Export an annotation object loaded from a FDF document into a PDF page
 *
 * @details	This function only support following annotation types:
 *					::FSPDF_ANNOTTYPE_TEXT, ::FSPDF_ANNOTTYPE_FREETEXT, ::FSPDF_ANNOTTYPE_LINE, ::FSPDF_ANNOTTYPE_SQUARE, ::FSPDF_ANNOTTYPE_CIRCLE, 
 *					::FSPDF_ANNOTTYPE_POLYGON, ::FSPDF_ANNOTTYPE_POLYLINE, ::FSPDF_ANNOTTYPE_HIGHLIGHT, ::FSPDF_ANNOTTYPE_UNDERLINE, ::FSPDF_ANNOTTYPE_SQUIGGLY, 
 *					::FSPDF_ANNOTTYPE_STRIKEOUT, ::FSPDF_ANNOTTYPE_STAMP, ::FSPDF_ANNOTTYPE_CARET, ::FSPDF_ANNOTTYPE_INK, ::FSPDF_ANNOTTYPE_FILEATTACHMENT.
 *					
 * @param[in]	fdfAnnot		Handle to a <b>FSCRT_ANNOT</b> object loaded from a FDF document.
 * @param[in]	pdfPage			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[out]	pdfAnnot		Pointer to a <b>FSCRT_ANNOT</b> handle that receives specific annotation in PDF page.
 *								If there's any error, it will be <b>NULL</b>.
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fdfAnnot</i>, <i>pdfPage</i>, or <i>annotIndex</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>fdfAnnot</i> is not a valid FDF annotation or <i>pdfPage</i> is not a valid PDF page, or the annotation is not markup.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if FDF annotation cannot be imported to PDF page because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If the annotation contains a Popup annotation, the Popup annotation will be also imported along in the meantime, but it could not be imported separately.
 * 
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>fdfAnnot</i>: this handle is short-term.</li>
 *				<li> <i>pdfPage</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pdfAnnot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details. 
 */
FS_RESULT	FSFDF_Annot_ExportToPDFPage(FSCRT_ANNOT fdfAnnot, FSCRT_PAGE pdfPage, FSCRT_ANNOT* pdfAnnot);

/**
 * @brief	Export all annotations from a PDF document into a FDF document.
 * 
 * @details	This function only support following annotation types:<br>
 *			::FSPDF_ANNOTTYPE_TEXT, ::FSPDF_ANNOTTYPE_FREETEXT, ::FSPDF_ANNOTTYPE_LINE, ::FSPDF_ANNOTTYPE_SQUARE, ::FSPDF_ANNOTTYPE_CIRCLE, 
 *			::FSPDF_ANNOTTYPE_POLYGON, ::FSPDF_ANNOTTYPE_POLYLINE, ::FSPDF_ANNOTTYPE_HIGHLIGHT, ::FSPDF_ANNOTTYPE_UNDERLINE, ::FSPDF_ANNOTTYPE_SQUIGGLY, 
 *			::FSPDF_ANNOTTYPE_STRIKEOUT, ::FSPDF_ANNOTTYPE_STAMP, ::FSPDF_ANNOTTYPE_CARET, ::FSPDF_ANNOTTYPE_INK, ::FSPDF_ANNOTTYPE_FILEATTACHMENT.
 *
 * @param[in]	pdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	fdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a FDF document object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pdfDoc</i> or <i>fdfDoc</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>pdfDoc</i> is not a valid PDF document, or <i>fdfDoc</i> is not a valid FDF document.<br>
 *			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to FDF document is not allowed.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if any other error.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>pdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>fdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_ExportAnnotsToFDFDoc(FSCRT_DOCUMENT pdfDoc, FSCRT_DOCUMENT fdfDoc);

/**
 * @brief	Export all annotations from a FDF document into a PDF document.
 *
 * @details	This function only support following annotation types:<br>
 *			::FSPDF_ANNOTTYPE_TEXT, ::FSPDF_ANNOTTYPE_FREETEXT, ::FSPDF_ANNOTTYPE_LINE, ::FSPDF_ANNOTTYPE_SQUARE, ::FSPDF_ANNOTTYPE_CIRCLE, 
 *			::FSPDF_ANNOTTYPE_POLYGON, ::FSPDF_ANNOTTYPE_POLYLINE, ::FSPDF_ANNOTTYPE_HIGHLIGHT, ::FSPDF_ANNOTTYPE_UNDERLINE, ::FSPDF_ANNOTTYPE_SQUIGGLY, 
 *			::FSPDF_ANNOTTYPE_STRIKEOUT, ::FSPDF_ANNOTTYPE_STAMP, ::FSPDF_ANNOTTYPE_CARET, ::FSPDF_ANNOTTYPE_INK, ::FSPDF_ANNOTTYPE_FILEATTACHMENT.
 *					
 * @param[in]	fdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a FDF document object.
 * @param[in]	pdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fdfDoc</i> or <i>pdfDoc</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>fdfDoc</i> is not a valid FDF document, or <i>pdfDoc</i> is not a valid PDF document.<br>
 *			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to FDF document is not allowed.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if any other error.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	<ul>
 *			<li> When call this function, annotations of any page shouldn't be loaded. </li>
 *			<li> If the original PDF page index(on which the annotation should appear) in FDF document is out of the page range of the PDF document, 
 *			the annotation won't be exported into PDF document.</li>
 *			</ul>
 * 
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>fdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details. 
 */
FS_RESULT	FSFDF_Doc_ExportAnnotsToPDFDoc(FSCRT_DOCUMENT fdfDoc, FSCRT_DOCUMENT pdfDoc);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FFDFDOCUMENT */

#endif /* _FSFDF_DOCUMENT_W_H_ */

