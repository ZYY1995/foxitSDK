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
 * @file	ffdf_document_r.h
 * @brief	Header file for \ref FFDFDOCUMENT "FDF Document" module of Foxit PDF SDK.
 * @details	This header file defines FDF document data supports.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Load and close FDF document. </li>
 *			<li>2. Get FDF data. </li>
 *			<li>3. Get annotations. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Annotation Add-on</b> or <b>Form Add-on</b> explicitly.
 */

#ifndef _FSFDF_DOCUMENT_R_H_
#define _FSFDF_DOCUMENT_R_H_

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
 * @brief	Load a FDF document.
 *
 * @param[in]	fdfFile		Handle to a <b>FSCRT_FILE</b> object which is a file object to be loaded.
 * @param[out]	fdfDoc		Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives a FDF document.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fdfFile</i> or <i>fdfDoc</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to FDF document is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>fdfFile</i> is not a FDF file.<br>
 * 			::FSCRT_ERRCODE_FILE if data from parameter <i>fdfFile</i> cannot be read.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if cannot load FDF document because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>fdfFile</i>: this handle is long-term recoverable.</li>
 *				<li> <i>fdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSFDF_Doc_Load(FSCRT_FILE fdfFile, FSCRT_DOCUMENT* fdfDoc);

/**
 * @brief	Close a FDF document
 *
 * @param[in]	fdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a FDF document object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fdfDoc</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>fdfDoc</i> is not a valid FDF document.<br>
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
FS_RESULT 	FSFDF_Doc_Close(FSCRT_DOCUMENT fdfDoc); 

/**
 * @brief	Get the path of PDF document from FDF document in UTF-8 string. 
 *
 * @details	The path can be either an absolute one, or a relative one.<br>
 *			This function applies to ::FSCRT_DOCUMENTTYPE_FDF document, which contains elements required to export or import interactive form data.
 *
 * @param[in]	fdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a FDF document object.
 * @param[in]	pdfPath		Pointer to a const UTF-8 path string.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fdfDoc</i> or <i>pdfPath</i> is <b>NULL</b> or <i>pdfPath->str</i> is <b>NULL</b> or <i>pdfPath->len</i> is less than 1.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>fdfDoc</i> is not a valid FDF document.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if there is no path data found in FDF document.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
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
FS_RESULT 	FSFDF_Doc_GetPDFPath(FSCRT_DOCUMENT fdfDoc, FSCRT_BSTR* pdfPath);

/*******************************************************************************/
/* FDF annotation                                                              */
/*******************************************************************************/
/**
 * @brief	Count annotations in a FDF document by specific filter.
 *
 * @param[in]	fdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a FDF document object.
 * @param[in]	filter		Pointer to a filter string.<br>
 *							If it's <b>NULL</b> or <i>filter->str</i> is <b>NULL</b> or <i>filter->len</i> is less than 1, this function will count all annotations.
 *							If it's a valid pointer to ::FSCRT_BSTR, it specifies annotation types:<br>
 *							<ul>
 *							<li>For single type filter: please refer to macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> and it should be one of these macros.</li>
 *							<li>For multiple types filter: use comma to separate different types, for example, "Text, Link, Circle".</li>
 *							</ul>
 * @param[out]	count		Pointer to a ::FS_INT32 object that receives the count of annotations.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fdfDoc</i> or <i>count</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>fdfDoc</i> is not a valid FDF document.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>fdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSFDF_Annot_GetCount(FSCRT_DOCUMENT fdfDoc, const FSCRT_BSTR* filter, FS_INT32* count);

/**
 * @brief	Get an annotation from FDF document by specific filter and index.
 *
 * @param[in]	fdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a FDF document object.
 * @param[in]	filter		Pointer to a filter string.<br>
 *							If it's <b>NULL</b> or <i>filter->str</i> is <b>NULL</b> or <i>filter->len</i> is less than 1, this function will get all annotations.
 *							If it's a valid pointer to ::FSCRT_BSTR, it specifies annotation types:<br>
 *							<ul>
 *							<li>For single type filter: Please refer to macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> and it should be one of these macros.</li>
 *							<li>For multiple types filter: Use comma to separate different types, for example, "Text, Link, Circle".</li>
 *							</ul>
 * @param[in]	index		A zero-based annotation index based on the annotations which are specified by <i>filter</i>.
 * @param[out]	fdfAnnot	Pointer to a <b>FSCRT_ANNOT</b> handle that receives the annotation from FDF file.
 *							This annotation can be used in function ::FSFDF_Annot_ExportToPDFPage.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fdfDoc</i> or <i>fdfAnnot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>fdfDoc</i> is not a valid FDF document.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or there are no annotations which are specified by <i>filter</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if annotation cannot be obtained from FDF document because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>fdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>fdfAnnot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSFDF_Annot_Get(FSCRT_DOCUMENT fdfDoc, const FSCRT_BSTR* filter, FS_INT32 index, FSCRT_ANNOT *fdfAnnot);

/**
 * @brief	Get the ordinal PDF page index, on which the FDF annotation should appear.
 *
 * @param[in]	fdfAnnot	Handle to a <b>FSCRT_ANNOT</b> object loaded from an FDF document.
 * @param[out]	pageIndex	Pointer to a ::FS_INT32 object that receives the original PDF page index which starts from 0.
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fdfAnnot</i> or <i>pageIndex</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>fdfAnnot</i> is not a valid FDF annotation.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if annotation cannot be obtained from FDF document because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>fdfAnnot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSFDF_Annot_GetPageIndex(FSCRT_ANNOT fdfAnnot, FS_INT32 *pageIndex);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FFDFDOCUMENT */

#endif /* _FSFDF_DOCUMENT_R_H_ */

