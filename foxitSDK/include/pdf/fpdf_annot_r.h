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
 * @file	fpdf_annot_r.h
 * @brief	Header file for \ref FPDFANNOT "PDF Annotation" module of Foxit PDF SDK.
 * @details	This header file defines PDF annotation supports, mainly about "reading" methods.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Load or unload annotations from a PDF page. </li>
 *			<li>2. Enumerate annotations. </li>
 *			<li>3. Get common properties of annotations. </li>
 *			<li>4. Supports to markup annotations. </li>
 *			<li>5. Get annotation trigger actions. </li>
 *			<li>6. Render annotations. </li>
 *			</ul><br>
 *			Special attention:
 *			<ul>
 *			<li>
 *				For watermark annotation, user should use functions in \ref FPDFWATERMARK "PDF Watermark" module for most operations of watermark.<br>
 *			</li>
 *			<li>
 *				For PSInk annotation, user should use function ::FSCRT_PSI_ConvertToPDFAnnot in \ref FSPSI "Pressure Sensitive Ink" 
 *				to generate a PSInk annotation from a PSI object.<br>
 *			</li>
 *			<li>
 *				For Sound, Movie, Screen, PrinterMark, TrapNet and 3D annotations, currently Foxit PDF SDK provides common access to them and their basic properties, 
 *				not support access to their data.
 *			</li>
 *			<li>
 *				For annotation which is not defined in PDF Reference but consists of some standard annotations, 
 *				it will be treated as different standard annotations.
 *				If user wants to treat these standard annotations as one special annotation, user should do this in application layer.
 *			</li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Annotation Add-on</b> or <b>Form Add-on</b> explicitly.
 */

#ifndef _FSPDF_ANNOT_R_H_
#define _FSPDF_ANNOT_R_H_

/**
 * @defgroup	FPDFANNOT PDF Annotation
 * @brief		Definitions for PDF annotations access.<br>
 *				Definitions and functions in this module are included in fpdf_annot_r.h and fpdf_annot_w.h.<br>
 *				Module: PDFAnnot<br>
 *				License Identifier: PDFAnnot/All<br>
 *				Available License Right: Reading/Writing<br>
 *				For License Right <b>Reading</b>, see fpdf_annot_r.h.<br>
 *				For License Right <b>Writing</b>, see fpdf_annot_w.h.<br>
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. Annotation:
 *					<ul>
 *					<li>a.	Load, add or remove annotations in page, enumerate annotations by filter, access common properties of annotations, 
 *							control markups, access trigger actions of annotations, render annotations or reset appearance.</li>
 *					<li>b.	Annotations contain a lot of interactive operations in PDF. They increase practicability and provide valuable extension to applications. 
 *							Markup consists of several advanced features which involve contents and replies, state, group managements. 
 *							Widget is a special type of annotation which represents a terminal node of PDF form field. 
 *							In Foxit PDF SDK, form control is a synonym to widget.</li>
 *					<li>c.	Note: 
 *							<ul>
 *							<li>Sound, Movie, Screen, PrinterMark, TrapNet and 3D annotations are not fully supported in the current version of Foxit PDF SDK. 
 *								Current functions only provide common access to them, not support access to their data.</li>
 *							<li>Widget and watermark annotations: Foxit PDF SDK only provides common access to widget , watermark and PSInk annotation in this module. <br>
 *								For widget related to form object, please refer to \ref FPDFFORM "PDF Form" module.<br>
 *								For watermark annotation, please refer to \ref FPDFWATERMARK "PDF Watermark" module. <br>
 *								For PSInk annotation, please refer to \ref FSPSI "Pressure Sensitive Ink" </li>
 *							</ul>
 *					<li>d. Reference: section 8.4 in PDF Reference 1.7 describes annotations in detail.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Load or unload annotations from page                                        */
/*******************************************************************************/
/**
 * @brief	Load annotations from a PDF page. 
 *
 * @details	This should be called before any other functions in PDF annotation module are used.<br>
 *			For widget annotation, use functions in \ref FPDFFORM "PDF Form" module for most operations of widget.<br>
 *			For watermark annotation, use functions in \ref FPDFWATERMARK "PDF Watermark" module for most operations of watermark.<br>
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if annotations cannot be loaded because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Page_LoadAnnots(FSCRT_PAGE page);

/**
 * @brief	Unload annotations of a PDF page. 
 *
 * @details	This should be called when there's no more operation on annotations in this PDF page.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if annotations cannot be unloaded because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Page_UnloadAnnots(FSCRT_PAGE page);

/*******************************************************************************/
/* Enumerate annotation types                                                  */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_ANNOTTYPE_
#define _FSPDF_DEF_MACRO_ANNOTTYPE_
/**
 * @name	Macro Definitions for Annotation Types
 * @note	Annotation types are used as parameter like <i>filter</i> or <i>type</i> in some functions.
 */
/**@{*/

/** @brief	Text annotation, markup type. */
#define FSPDF_ANNOTTYPE_TEXT				"Text"
/** @brief	Link annotation. */
#define FSPDF_ANNOTTYPE_LINK				"Link"
/** @brief	Free text annotation, markup type. */
#define FSPDF_ANNOTTYPE_FREETEXT			"FreeText"
/** @brief	Line annotation, markup type. */
#define FSPDF_ANNOTTYPE_LINE				"Line"
/** @brief	Square annotation, markup type. */
#define FSPDF_ANNOTTYPE_SQUARE				"Square"
/** @brief	Circle annotation, markup type. */
#define FSPDF_ANNOTTYPE_CIRCLE				"Circle"
/** @brief	Polygon annotation, markup type. */
#define FSPDF_ANNOTTYPE_POLYGON				"Polygon"
/** @brief	Polyline annotation, markup type. */
#define FSPDF_ANNOTTYPE_POLYLINE			"PolyLine"
/** @brief	Highlight annotation, markup type. */
#define FSPDF_ANNOTTYPE_HIGHLIGHT			"Highlight"
/** @brief	Underline annotation, markup type. */
#define FSPDF_ANNOTTYPE_UNDERLINE			"Underline"
/** @brief	Squiggly-underline annotation, markup type. */
#define FSPDF_ANNOTTYPE_SQUIGGLY			"Squiggly"
/** @brief	Strikeout annotation, markup type. */
#define FSPDF_ANNOTTYPE_STRIKEOUT			"StrikeOut"
/** @brief	Rubber stamp annotation, markup type. */
#define FSPDF_ANNOTTYPE_STAMP				"Stamp"
/** @brief	Caret annotation, markup type. */
#define FSPDF_ANNOTTYPE_CARET				"Caret"
/** @brief	Ink annotation, markup type. */
#define FSPDF_ANNOTTYPE_INK					"Ink"
/** @brief	Pop-up annotation. */
#define FSPDF_ANNOTTYPE_POPUP				"Popup"
/** @brief	File attachment annotation, markup type. */
#define FSPDF_ANNOTTYPE_FILEATTACHMENT		"FileAttachment"
/** 
 * @brief	Sound annotation, markup type. 
 * @note	Currently, Foxit PDF SDK only provides functions for common access to sound annotation.
 */
#define FSPDF_ANNOTTYPE_SOUND				"Sound"
/** 
 * @brief	Movie annotation. 
 * @note	Currently, Foxit PDF SDK only provides functions for common access to movie annotation.
 */
#define FSPDF_ANNOTTYPE_MOVIE				"Movie"
/** 
 * @brief	Widget annotation. 
 * @note	In current module, Foxit PDF SDK only provides functions for common access to widget annotation.<br>
 *			For widget related to form object, please refer to \ref FPDFFORM "PDF Form" module.<br>
 */
#define FSPDF_ANNOTTYPE_WIDGET				"Widget"
/** 
 * @brief	Screen annotation. 
 * @note	Currently, Foxit PDF SDK only provides functions for common access to screen annotation.
 */
#define FSPDF_ANNOTTYPE_SCREEN				"Screen"
/** 
 * @brief	Printer's mark annotation. 
 * @note	Currently, Foxit PDF SDK only provides functions for common access to printer's mark annotation.
 */
#define FSPDF_ANNOTTYPE_PRINTERMARK			"PrinterMark"
/** 
 * @brief	Trap network annotation. 
 * @note	Currently, Foxit PDF SDK only provides functions for common access to trap network annotation.
 */
#define FSPDF_ANNOTTYPE_TRAPNET				"TrapNet"
/** 
 * @brief	Watermark annotation. 
 * @note	In current module, Foxit PDF SDK only provides functions for common access to watermark annotation.<br>
 *			For watermark annotation, please refer to \ref FPDFWATERMARK "PDF Watermark" module.
 */
#define FSPDF_ANNOTTYPE_WATERMARK			"Watermark"
/** 
 * @brief	Pressure Sensitive Ink annotation. Currently not support. 
 * @note	In current module, Foxit PDF SDK only provides functions for common access to pressure sensitive ink annotation.<br>
 *			For pressure sensitive ink annotation, please refer to \ref FPDFWATERMARK "PDF Watermark" module.
 */
#define FSPDF_ANNOTTYPE_PSI					"PSInk"
/** 
 * @brief	3D annotation. 
 * @note	Currently, Foxit PDF SDK only provides functions for common access to 3D annotation.
 */
#define FSPDF_ANNOTTYPE_3D					"3D"

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOTTYPE_ */

/**
 * @brief	Get count of annotations, by specific filter.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> which is a PDF page object.
 * @param[in]	filter		Pointer to a filter string.<br>
 *							If it's <b>NULL</b> or <i>filter->str</i> is <b>NULL</b> or <i>filter->len</i> is less than 1, this function will count all annotations.
 *							If it's a valid pointer to ::FSCRT_BSTR, it specifies annotation type:<br>
 *							<ul>
 *							<li>For single type filter: please refer to macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> and it should be one of these macros.</li>
 *							<li>For multiple types filter: use comma to separate different types, for example, "Text, Link, Circle".</li>
 *							</ul>
 * @param[out]	count		Pointer to a ::FS_INT32 object that receives count of annotations. 
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, or <i>count</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if count cannot be obtained by specified filter because of any other reason.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if annotations in parameter <i>page</i> are not loaded.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetCount(FSCRT_PAGE page, const FSCRT_BSTR* filter, FS_INT32* count);

/**
 * @brief	Get annotation with specified index, by specific filter.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[in]	filter		Pointer to a filter string.<br>
 *							If it's <b>NULL</b> or <i>filter->str</i> is <b>NULL</b> or <i>filter->len</i> is less than 1, this function will get annotation from all annotations.
 *							If it's a valid pointer to ::FSCRT_BSTR, it specifies annotation type:<br>
 *							<ul>
 *							<li>For single type filter: Please refer to macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> and it should be one of these macros.</li>
 *							<li>For multiple types filter: Use comma to separate different types, for example, "Text, Link, Circle".</li>
 *							</ul>
 * @param[in]	index		A zero-based index of annotation to be got. Range: 0 to (AnnotCount-1).
 *							<i>annotcount</i> is returned by function ::FSPDF_Annot_GetCount with same <i>filter</i>.
 * @param[out]	annot		Pointer to a <b>FSCRT_ANNOT</b> handle that receives specific annotation.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, or <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or there are no annotations.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if annotations in parameter <i>page</i> are not loaded.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_Get(FSCRT_PAGE page, const FSCRT_BSTR* filter, FS_INT32 index, FSCRT_ANNOT* annot);

/**
 * @brief	Get annotation at a specific position in PDF page, by specific filter.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[in]	filter		Pointer to a filter string.<br>
 *							If it's <b>NULL</b>, this function will get annotation from all annotations.
 *							If it's a valid pointer to ::FSCRT_BSTR, it specifies annotation type:<br>
 *							<ul>
 *							<li>For single type filter: Please refer to macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> and it should be one of these macros.</li>
 *							<li>For multiple types filter: Use comma to separate different types, for example, "Text, Link, Circle".</li>
 *							</ul>
 * @param[in]	x			Horizontal position in PDF page coordinate system.
 * @param[in]	y			Vertical position in PDF page coordinate system.
 * @param[in]	tolerance	Tolerance value for point, in PDF page coordinate system. Valid value: from 0.0f to 30.0f.
 * @param[out]	annot		Pointer to a <b>FSCRT_ANNOT</b> handle that receives specified annotation.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, or <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if there's no annotations.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if annotations in parameter <i>page</i> are not loaded.<br>
 *			::FSCRT_ERRCODE_ERROR if annotation cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetAtPos(FSCRT_PAGE page, const FSCRT_BSTR* filter, FS_FLOAT x, FS_FLOAT y, FS_FLOAT tolerance, FSCRT_ANNOT* annot);

/**
 * @brief	Get annotation at a specific position in device (in pixel), by specific filter.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[in]	filter		Pointer to a filter string.<br>
 *							If it's <b>NULL</b>, this function will get all annotations.
 *							If it's a valid pointer to ::FSCRT_BSTR, it specifies annotation type:<br>
 *							<ul>
 *							<li>For single type filter: Please refer to macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> and it should be one of these macros.</li>
 *							<li>For multiple types filter: Use comma to separate different types, for example, "Text, Link, Circle".</li>
 *							</ul>
 * @param[in]	matrix		A matrix used to transform from device coordinate system to PDF page coordinate system.
 * @param[in]	x			Horizontal position in device coordinate system (in pixel).
 * @param[in]	y			Vertical position in device coordinate system (in pixel).
 * @param[in]	tolerance	Tolerance value for point, in device coordinate system. Valid value: from 0.0f to 30.0f.
 * @param[out]	annot		Pointer to a <b>FSCRT_ANNOT</b> handle that receives specified annotation.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>matrix</i>, or <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if there's no annotations.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if annotations in parameter <i>page</i> are not loaded.<br>
 *			::FSCRT_ERRCODE_ERROR if annotation cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetAtDevicePos(FSCRT_PAGE page, const FSCRT_BSTR* filter, const FSCRT_MATRIX* matrix, FS_INT32 x, FS_INT32 y, FS_INT32 tolerance, FSCRT_ANNOT* annot);

/**
 * @brief	Get index of a specific annotation, by specific filter.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	filter		Pointer to a filter string.<br>
 *							If it's <b>NULL</b>, this function will get index of specific annotation from all annotations.
 *							If it's a valid pointer to ::FSCRT_BSTR, it specifies annotation type:<br>
 *							<ul>
 *							<li>For single type filter: Please refer to macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> and it should be one of these macros.</li>
 *							<li>For multiple types filter: Use comma to separate different types, for example, "Text, Link, Circle".</li>
 *							</ul>
 * @param[out]	index		Pointer to a ::FS_INT32 object that receives index of an annotation. 
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>index</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if cannot get index because of any other reason.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>annot</i> isn't found with specific filter.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetIndex(FSCRT_ANNOT annot, const FSCRT_BSTR* filter, FS_INT32* index);

/**
 * @brief	Get annotations by tab order, with specific filter (except Popup).
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> except ::FSPDF_ANNOTTYPE_POPUP.<br>
 *			It needs to be called twice to get annotArray:<br>
 *			For the first time, set parameter <i>annotArray</i> to <b>NULL</b> to get the actual size of annotations to be got.
 *			The count value will be set to parameter <i>count</i> as a result returned by the first calling.<br>
 *			Then use <i>count</i> to allocate <i>annotArray</i>.<br>
 *			For the second time, input the allocated <i>annotArray</i> and its size <i>count</i> to get the annotArray. 
 *			When this function returns successfully, <i>annotArray</i> will get the annot array and <i>count</i> will get the actual count.<br>
 *			The size of the input array should not be less than the actual count, and the parameter <i>count</i> shall not be empty.
 *
 * @param[in]		page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[in]		filter		Pointer to a filter string.<br>
 *								If it's <b>NULL</b>, this function will get annotations by tab order from all annotations.
 *								If it's a valid pointer to ::FSCRT_BSTR, it specifies annotation type:<br>
 *								<ul>
 *								<li>For single type filter: Please refer to macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> and it should be one of these macros.</li>
 *								<li>For multiple types filter: Use comma to separate different types, for example, "Text, Link, Circle".</li>
 *								</ul>
 * @param[out]		annotArray	Pointer to a <b>FSCRT_ANNOT</b> handle array that receives specific annotation. 
 *								If there's any error, it will be <b>NULL</b>.
 * @param[in,out]	count		Pointer to a ::FS_INT32 object. <br>
 *								When this function is called, it should be the size of parameter <i>annotArray</i> if parameter <i>annotArray</i> isn't <b>NULL</b>.<br>
 *								When this function returns, it will receive the actual count of annotations which are got.<br>
 *								Please see detail description about how to use this function.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>count</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if no annotation is found with specific filter.<br>
 * 			::FSCRT_ERRCODE_BUFFEROVERFLOW if parameter <i>annotArray</i> is valid but <i>count</i> is less than required amount.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if annots cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetAllByTabOrder(FSCRT_PAGE page, const FSCRT_BSTR* filter, FSCRT_ANNOT* annotArray, FS_INT32* count);

/*******************************************************************************/
/* Annotation common properties                                                */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_ANNOTFLAG_
#define _FSPDF_DEF_MACRO_ANNOTFLAG_
/**
 * @name	Macro Definitions for Annotation Flags
 */
/**@{*/

/* @brief	Annotation flag: invisible */
#define	FSPDF_ANNOTFLAG_INVISIBLE			0x0001
/* @brief	Annotation flag: hidden */
#define FSPDF_ANNOTFLAG_HIDDEN				0x0002
/* @brief	Annotation flag: print */
#define FSPDF_ANNOTFLAG_PRINT				0x0004
/* @brief	Annotation flag: no zoom */
#define FSPDF_ANNOTFLAG_NOZOOM				0x0008
/* @brief	Annotation flag: no rotate */
#define FSPDF_ANNOTFLAG_NOROTATE			0x0010
/* @brief	Annotation flag: no view */
#define FSPDF_ANNOTFLAG_NOVIEW				0x0020
/* @brief	Annotation flag: read only */
#define FSPDF_ANNOTFLAG_READONLY			0x0040
/* @brief	Annotation flag: locked */
#define FSPDF_ANNOTFLAG_LOCKED				0x0080
/* @brief	Annotation flag: toggle no view */
#define FSPDF_ANNOTFLAG_TOGGLENOVIEW		0x0100
/* @brief	Annotation flag: locked contents */
#define FSPDF_ANNOTFLAG_LOCKEDCONTENTS		0x0200

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOTFLAG_ */

#ifndef _FSPDF_DEF_MACRO_ANNOT_ICONNAME_
#define _FSPDF_DEF_MACRO_ANNOT_ICONNAME_
/**
 * @name	Macro Definitions for Icon Names
 */
/**@{*/

/** @brief	Note icon type: Checkmark. */
#define FSPDF_ANNOT_ICONNAME_TEXT_CHECKMARK				"Checkmark"
/** @brief	Note icon type: Circle. */
#define FSPDF_ANNOT_ICONNAME_TEXT_CIRCLE				"Circle"
/** @brief	Note icon type: Comment. */
#define FSPDF_ANNOT_ICONNAME_TEXT_COMMENT				"Comment"
/** @brief	Note icon type: Cross. */
#define FSPDF_ANNOT_ICONNAME_TEXT_CROSS					"Cross"
/** @brief	Note icon type: Help. */
#define FSPDF_ANNOT_ICONNAME_TEXT_HELP					"Help"
/** @brief	Note icon type: Insert. */
#define FSPDF_ANNOT_ICONNAME_TEXT_INSERT				"Insert"
/** @brief	Note icon type: Key. */
#define FSPDF_ANNOT_ICONNAME_TEXT_KEY					"Key"
/** @brief	Note icon type: New Paragraph. */
#define FSPDF_ANNOT_ICONNAME_TEXT_NEWPARAGRAPH			"NewParagraph"
/** @brief	Note icon type: Note. */
#define FSPDF_ANNOT_ICONNAME_TEXT_NOTE					"Note"
/** @brief	Note icon type: Paragraph. */
#define FSPDF_ANNOT_ICONNAME_TEXT_PARAGRAPH				"Paragraph"
/** @brief	Note icon type: Right Arrow. */
#define FSPDF_ANNOT_ICONNAME_TEXT_RIGHARROW				"RightArrow"
/** @brief	Note icon type: Right Pointer. */
#define FSPDF_ANNOT_ICONNAME_TEXT_RIGHPOINTER			"RightPointer"
/** @brief	Note icon type: Star. */
#define FSPDF_ANNOT_ICONNAME_TEXT_STAR					"Star"
/** @brief	Note icon type: Up Arrow. */
#define FSPDF_ANNOT_ICONNAME_TEXT_UPARROW				"UpArrow"
/** @brief	Note icon type: Up-left Arrow. */
#define FSPDF_ANNOT_ICONNAME_TEXT_UPLEFTARROW			"UpleftArrow"

/** @brief	File attachment icon type: Graph. */
#define FSPDF_ANNOT_ICONNAME_FILEATTACH_GRAPH			"Graph"
/** @brief	File attachment icon type: PaperClip. */
#define FSPDF_ANNOT_ICONNAME_FILEATTACH_PAPERCLIP		"Paperclip"
/** @brief	File attachment icon type: PushPin. */
#define FSPDF_ANNOT_ICONNAME_FILEATTACH_PUSHPIN			"PushPin"
/** @brief	File attachment icon type: Tag. */
#define FSPDF_ANNOT_ICONNAME_FILEATTACH_TAG				"Tag"

/** @brief	Stamp annotation icon type: Approved. */
#define FSPDF_ANNOT_ICONNAME_STAMP_APPROVED				"Approved"
/** @brief	Stamp annotation icon type: AsIs. */
#define FSPDF_ANNOT_ICONNAME_STAMP_ASIS					"AsIs"
/** @brief	Stamp annotation icon type: Confidential. */
#define FSPDF_ANNOT_ICONNAME_STAMP_CONFIDENTIAL			"Confidential"
/** @brief	Stamp annotation icon type: Departmental. */
#define FSPDF_ANNOT_ICONNAME_STAMP_DEPARTMENTAL			"Departmental"
/** @brief	Stamp annotation icon type: Draft. */
#define FSPDF_ANNOT_ICONNAME_STAMP_DRAFT				"Draft"
/** @brief	Stamp annotation icon type: Experimental. */
#define FSPDF_ANNOT_ICONNAME_STAMP_EXPERIMENTAL			"Experimental"
/** @brief	Stamp annotation icon type: Expired. */
#define FSPDF_ANNOT_ICONNAME_STAMP_EXPIRED				"Expired"
/** @brief	Stamp annotation icon type: Final. */
#define FSPDF_ANNOT_ICONNAME_STAMP_FINAL				"Final"
/** @brief	Stamp annotation icon type: ForComment. */
#define FSPDF_ANNOT_ICONNAME_STAMP_FORCOMMENT			"ForComment"
/** @brief	Stamp annotation icon type: ForPublicRelease. */
#define FSPDF_ANNOT_ICONNAME_STAMP_FORPUBLICRELEASE		"ForPublicRelease"
/** @brief	Stamp annotation icon type: NotApproved. */
#define FSPDF_ANNOT_ICONNAME_STAMP_NOTAPPROVED			"NotApproved"
/** @brief	Stamp annotation icon type: NotForPublicRelease. */
#define FSPDF_ANNOT_ICONNAME_STAMP_NOTFORPUBLICRELEASE	"NotForPublicRelease"
/** @brief	Stamp annotation icon type: Sold. */
#define FSPDF_ANNOT_ICONNAME_STAMP_SOLD					"Sold"
/** @brief	Stamp annotation icon type: TopSecret. */
#define FSPDF_ANNOT_ICONNAME_STAMP_TOPSECRET			"TopSecret"

/** @brief	Sound annotation icon type: Speaker. */
#define FSPDF_ANNOT_ICONNAME_SOUND_SPEAKER				"Speaker"
/** @brief	Sound annotation icon type: Mic. */
#define FSPDF_ANNOT_ICONNAME_SOUND_MIC					"Mic"

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOT_ICONNAME_ */

#ifndef _FSPDF_DEF_MACRO_ANNOT_INTENTNAME_
#define _FSPDF_DEF_MACRO_ANNOT_INTENTNAME_
/**
 * @name	Macro Definitions for Intent Names
 */
/**@{*/

/** @brief	FreeText annotation intent name: FreeTextCallout. */
#define FSPDF_ANNOT_INTENTNAME_FREETEXT_CALLOUT			"FreeTextCallout"
/** @brief	FreeText annotation intent name: FreeTextTypewriter. */
#define FSPDF_ANNOT_INTENTNAME_FREETEXT_TYPEWRITER		"FreeTextTypewriter"

/** @brief	Line annotation intent name: LineArrow. */
#define FSPDF_ANNOT_INTENTNAME_LINE_ARROW				"LineArrow"
/** @brief	Line annotation intent name: LineDimension. */
#define FSPDF_ANNOT_INTENTNAME_LINE_DIMENSION			"LineDimension"

/** @brief	Polygon annotation intent name: PolygonCloud. */
#define FSPDF_ANNOT_INTENTNAME_POLYGON_CLOUD			"PolygonCloud"
/** @brief	Polygon annotation intent name: PolygonDimension. */
#define FSPDF_ANNOT_INTENTNAME_POLYGON_DIMENSION		"PolygonDimension"

/** @brief	PolyLine annotation intent name: PolyLineDimension. */
#define FSPDF_ANNOT_INTENTNAME_POLYLINE_DIMENSION		"PolyLineDimension"

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOT_INTENTNAME_ */

#ifndef _FSPDF_DEF_MACRO_ANNOT_LINEENDINGSTYLE_
#define _FSPDF_DEF_MACRO_ANNOT_LINEENDINGSTYLE_
/**
 * @name	Macro Definitions for Line Ending Styles
 */
/**@{*/

/** @brief	Line annotation ending style name: None. */
#define FSPDF_ANNOT_LINEENDINGSTYLE_NONE					"None"
/** @brief	Line annotation ending style name: Square. */
#define FSPDF_ANNOT_LINEENDINGSTYLE_SQUARE					"Square"
/** @brief	Line annotation ending style name: Circle. */
#define FSPDF_ANNOT_LINEENDINGSTYLE_CIRCLE					"Circle"
/** @brief	Line annotation ending style name: Diamond. */
#define FSPDF_ANNOT_LINEENDINGSTYLE_DIAMOND					"Diamond"
/** @brief	Line annotation ending style name: OpenArrow. */
#define FSPDF_ANNOT_LINEENDINGSTYLE_OPENARROW				"OpenArrow"
/** @brief	Line annotation ending style name: ClosedArrow. */
#define FSPDF_ANNOT_LINEENDINGSTYLE_CLOSEDARROW				"ClosedArrow"
/** @brief	Line annotation ending style name: Butt. */
#define FSPDF_ANNOT_LINEENDINGSTYLE_BUTT					"Butt"
/** @brief	Line annotation ending style name: ROpenArrow. */
#define FSPDF_ANNOT_LINEENDINGSTYLE_REVERSEOPENARROW		"ROpenArrow"
/** @brief	Line annotation ending style name: RClosedArrow. */
#define FSPDF_ANNOT_LINEENDINGSTYLE_REVERSECLOSEDARROW		"RClosedArrow"
/** @brief	Line annotation ending style name: Slash. */
#define FSPDF_ANNOT_LINEENDINGSTYLE_SLASH					"Slash"

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOT_LINEENDINGSTYLE_ */

#ifndef _FSPDF_DEF_MACRO_ANNOT_HIGHLIGHTINGMODE_
#define _FSPDF_DEF_MACRO_ANNOT_HIGHLIGHTINGMODE_
/**
 * @name	Macro Definitions for Highlighting Modes
 */
/**@{*/

/** @brief	Highlighting mode: None */
#define FSPDF_ANNOT_HIGHLIGHTINGMODE_NONE		0
/** @brief	Highlighting mode: Invert */
#define FSPDF_ANNOT_HIGHLIGHTINGMODE_INVERT		1
/** @brief	Highlighting mode: Outline */
#define FSPDF_ANNOT_HIGHLIGHTINGMODE_OUTLINE	2
/** @brief	Highlighting mode: Push */
#define FSPDF_ANNOT_HIGHLIGHTINGMODE_PUSH		3
/** @brief	Highlighting mode: Toggle */
#define FSPDF_ANNOT_HIGHLIGHTINGMODE_TOGGLE		4

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOT_HIGHLIGHTINGMODE_ */

#ifndef _FSPDF_DEF_MACRO_ANNOT_BORDERSTYLE_
#define _FSPDF_DEF_MACRO_ANNOT_BORDERSTYLE_
/**
 * @name	Macro Definitions for Border Style
 */
/**@{*/

/** @brief	Border style: Solid */
#define FSPDF_ANNOT_BORDERSTYLE_SOLID		0
/** @brief	Border style: Dashed */
#define FSPDF_ANNOT_BORDERSTYLE_DASHED		1
/** @brief	Border style: Underline */
#define FSPDF_ANNOT_BORDERSTYLE_UNDERLINE	2
/** @brief	Border style: Beveled */
#define FSPDF_ANNOT_BORDERSTYLE_BEVELED		3
/** @brief	Border style: Inset */
#define FSPDF_ANNOT_BORDERSTYLE_INSET		4
/** @brief	Border style: Cloudy */
#define FSPDF_ANNOT_BORDERSTYLE_CLOUDY		5

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOT_BORDERSTYLE_ */

#ifndef _FSPDF_DEF_MACRO_ANNOT_ICONFITFLAG_
#define _FSPDF_DEF_MACRO_ANNOT_ICONFITFLAG_
/**
 * @name	Macro Definitions for Icon Fit Flags
 */
/**@{*/

/** @brief	Icon fit flag: Scale way */
#define FSPDF_ANNOT_ICONFITFLAG_SCALEWAY		1
/** @brief	Icon fit flag: Aspect ratio */
#define FSPDF_ANNOT_ICONFITFLAG_ASPECTRATIO		2
/** @brief	Icon fit flag: Set position */
#define FSPDF_ANNOT_ICONFITFLAG_POSITION		4
/** @brief	Icon fit flag: Fit boundaries */
#define FSPDF_ANNOT_ICONFITFLAG_FITBOUNDS		8

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOT_ICONFITFLAG_ */

#ifndef _FSPDF_DEF_MACRO_ANNOT_ICONSCALEWAY_
#define _FSPDF_DEF_MACRO_ANNOT_ICONSCALEWAY_
/**
 * @name	Macro Definitions for Icon Scale Way
 */
/**@{*/
/** @brief	A: Always scale. */
#define FSPDF_ANNOT_ICONSCALEWAY_ALWAYS		0	
/** @brief	B: Scale only when icon is bigger than annotation rectangle. */
#define FSPDF_ANNOT_ICONSCALEWAY_BIGGER		1	
/** @brief	S: Scale only when icon is smaller than annotation rectangle. */
#define FSPDF_ANNOT_ICONSCALEWAY_SMALLER	2	
/** @brief	N: Never scale. */
#define FSPDF_ANNOT_ICONSCALEWAY_NEVER		3	

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOT_ICONSCALEWAY_ */

#ifndef _FSPDF_DEF_MACRO_ANNOT_MKENTRY_
#define _FSPDF_DEF_MACRO_ANNOT_MKENTRY_
/**
 * @name	Macro Definitions for Entries in Appearance Characteristics (MK)
 */
/**@{*/

/** @brief	Entry of appearance characteristics dictionary: R. */
#define	FSPDF_ANNOT_MKENTRY_ROTATION			0
/** @brief	Entry of appearance characteristics dictionary: BC. */
#define	FSPDF_ANNOT_MKENTRY_BORDERCOLOR			1
/** @brief	Entry of appearance characteristics dictionary: BG. */
#define	FSPDF_ANNOT_MKENTRY_BACKGROUNDCOLOR		2
/** @brief	Entry of appearance characteristics dictionary: CA, only for widget annotation with any button fields. */
#define	FSPDF_ANNOT_MKENTRY_NORMALCAPTION		3
/** @brief	Entry of appearance characteristics dictionary: RC, only for widget annotation with pushbutton fields.*/
#define	FSPDF_ANNOT_MKENTRY_ROLLOVERCAPTION		4
/** @brief	Entry of appearance characteristics dictionary: AC, only for widget annotation with pushbutton fields. */
#define	FSPDF_ANNOT_MKENTRY_DOWNCAPTION			5
/** @brief	Entry of appearance characteristics dictionary: I, only for widget annotation with pushbutton fields. */
#define	FSPDF_ANNOT_MKENTRY_NORMALICON			6
/** @brief	Entry of appearance characteristics dictionary: RI, only for widget annotation with pushbutton fields. */
#define	FSPDF_ANNOT_MKENTRY_ROLLOVERICON		7
/** @brief	Entry of appearance characteristics dictionary: IX, only for widget annotation with pushbutton fields. */
#define	FSPDF_ANNOT_MKENTRY_DOWNICON			8
/** @brief	Entry of appearance characteristics dictionary: IF, only for widget annotation with pushbutton fields. */
#define	FSPDF_ANNOT_MKENTRY_ICONFIT				9
/** @brief	Entry of appearance characteristics dictionary: TP, only for widget annotation with pushbutton fields. */
#define	FSPDF_ANNOT_MKENTRY_TEXTPOSITION		10

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOT_MKENTRY_ */

#ifndef _FSPDF_DEF_STRUCTURE_ANNOTICONFIT_
#define _FSPDF_DEF_STRUCTURE_ANNOTICONFIT_
/**
 * @brief	Structure for annotation icon fit.
 */
typedef struct _FSPDF_ANNOTICONFIT
{
	/** 
	 * @brief	Icon fit flag. 
	 *
	 * @details	It can be one or combination of the following: <br>
	 *			<ul>
	 *			<li>::FSPDF_ANNOT_ICONFITFLAG_SCALEWAY</li>
	 *			<li>::FSPDF_ANNOT_ICONFITFLAG_ASPECTRATIO</li>
	 *			<li>::FSPDF_ANNOT_ICONFITFLAG_POSITION</li>
	 *			<li>::FSPDF_ANNOT_ICONFITFLAG_FITBOUNDS</li>
	 *			</ul>
	 */
	FS_DWORD	flags;
	/** 
	 * @brief	The circumstances under which the icon should be scaled inside the annotation rectangle. 
	 * 
	 * @details	It should be one of the following:<br>
	 *			<ul>
	 *			<li>::FSPDF_ANNOT_ICONSCALEWAY_ALWAYS</li>
	 *			<li>::FSPDF_ANNOT_ICONSCALEWAY_BIGGER</li>
	 *			<li>::FSPDF_ANNOT_ICONSCALEWAY_SMALLER</li>
	 *			<li>::FSPDF_ANNOT_ICONSCALEWAY_NEVER</li>
	 *			</ul>
	 *			Meaningful only when FSPDF_ANNOTICONFIT::flags contains ::FSPDF_ANNOT_ICONFITFLAG_SCALEWAY.
	 */
	FS_INT32	scaleWay;
	/** 
	 * @brief	A boolean value that indicates which type of scaling is to be used.
	 *
	 * @details	<b>TRUE</b> means to fill the annotation rectangle exactly, without regard to its original aspect ratio (ratio of width to height).<br>
	 *			<b>FALSE</b> means scale the icon to scale the icon to fit the width or height of the annotation rectangle 
	 *			while maintaining the icon's original aspect ratio.<br>
	 *			Meaningful only when FSPDF_ANNOTICONFIT::flags contains ::FSPDF_ANNOT_ICONFITFLAG_ASPECTRATIO.
	 */
	FS_BOOL		aspectRatio;
	/** 
	 * @brief	Left-over space to allocate at the left of the icon.
	 *
	 * @details	It's only valid for proportional scaling. Valid range: 0.0 to 1.0. <br>
	 *			Meaningful only when FSPDF_ANNOTICONFIT::flags contains ::FSPDF_ANNOT_ICONFITFLAG_POSITION.
	 */
	FS_FLOAT	left;
	/** 
	 * @brief	Left-over space to allocate at the bottom of the icon.
	 *
	 * @details	It's only valid for proportional scaling. Valid range: 0.0 to 1.0. <br>
	 *			Meaningful only when FSPDF_ANNOTICONFIT::flags contains ::FSPDF_ANNOT_ICONFITFLAG_POSITION.
	 */
	FS_FLOAT	bottom;
	/** 
	 * @brief	A boolean value that indicates whether to scale button appearance to fit fully within bounds or not.
	 *
	 * @details	<b>TRUE</b> indicates that the button appearance should be scaled to fit fully 
	 *			within the bounds of the annotation without taking into consideration the line width of the border. <br>
	 *			Meaningful only when FSPDF_ANNOTICONFIT::flags contains ::FSPDF_ANNOT_ICONFITFLAG_FITBOUNDS.
	 */
	FS_BOOL		fitBounds;
} FSPDF_ANNOTICONFIT;

#endif /* _FSPDF_DEF_STRUCTURE_ANNOTICONFIT_ */

#ifndef _FSPDF_DEF_STRUCTURE_ANNOTBORDER_
#define _FSPDF_DEF_STRUCTURE_ANNOTBORDER_
/**
 * @brief	Structure for annotation border.
 */
typedef struct _FSPDF_ANNOTBORDER
{
	/** 
	 * @brief	Width of border, in points. 
	 *
	 * @details	If this value is 0, no border is drawn. This value should not be negative.
	 */
	FS_FLOAT	borderWidth;
	/** 
	 * @brief	Border style. 
	 *
	 * @details	Please refer to macro definitions <b>FSPDF_ANNOT_BORDERSTYLE_XXX</b> and this should be one of these macros.
	 */
	FS_INT32	borderStyle;
	/** 
	 * @brief	Intensity of the cloudy effect.
	 *
	 * @details	Only free text, square, circle, polygon, and polyline annotations can have cloud intensity property.<br>
	 *			Suggested values range from 0 to 2. -1 mean no cloudy border effect.<br>
	 *			Only useful when <i>borderStyle</i> is FSPDF_ANNOT_BORDERSTYLE_CLOUDY; otherwise -1.
	 */
	FS_FLOAT	cloudIntensity;
	/** 
	 * @brief	Dash phase.
	 *			
	 * @details	Only useful when <i>borderStyle</i> is FSPDF_ANNOT_BORDERSTYLE_DASHED. 
	 */
	FS_FLOAT	dashPhase;
	/** 
	 * @brief	Count of useful elements in array <i>dashPattern</i>.
	 *
	 * @details	Only useful when <i>borderStyle</i> is FSPDF_ANNOT_BORDERSTYLE_DASHED.
	 */
	FS_INT32	dashCount;
	/** 
	 * @brief	Dash array. 
	 *
	 * @details	The value of elements in this array should not be negative.<br> 
	 *			Only be useful when <i>borderStyle</i> is FSPDF_ANNOT_BORDERSTYLE_DASHED.
	 */
	FS_FLOAT	dashPattern[16];
} FSPDF_ANNOTBORDER;

#endif /* _FSPDF_DEF_STRUCTURE_ANNOTBORDER_ */

/**
 * @brief	Get type of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	annotType	Pointer to a UTF-8 string that receives type of an annotation. 
 *							Please refer to macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> and this should be one of these macros.<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> when call this function, 
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>annotType</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no type property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if type cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetType(FSCRT_ANNOT annot, FSCRT_BSTR* annotType);

/**
 * @brief	Get rectangle of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	rect		Pointer to a ::FSCRT_RECTF structure that receives rectangle of an annotation.
 *							If there's any error, it will be set [0 0 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>rect</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no rectangle property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if rectangle cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetRect(FSCRT_ANNOT annot, FSCRT_RECTF* rect);

/**
 * @brief	Get rectangle of an annotation in device coordinations.
 *
 * @details	This is a useful function to get the device rectangle of an annotation, but not support popup annotation.<br>
 *			For the rectangle conversion, the result rectangle is always "normalized", 
 *			which is using device coordinations: left is always smaller than right, and top is always smaller than bottom.
 *
 * @param[in]	annot				Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object. 
 * @param[in]	bTransformIcon		A boolean value which indicates that whether to transform (like rotate or scale) the icon with page: 
 *									<b>TRUE</b> means to transform icon's rectangle with page, 
 *									while <b>FALSE</b> means not transform icon's rectangle with page.<br>
 *									This parameter only affects on "Text" and "FileAttachment" annotations, because they are shown as icon.
 * @param[in]	matrix				A matrix used to transform from PDF page coordinate system to device coordinate system. 
 * @param[out]	deviceRect			Pointer to a ::FSCRT_RECT structure that receives rectangle of an annotation in device coordinations.
 *									If there's any error, it will be set [0 0 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, <i>matrix</i> or <i>deviceRect</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no rectangle property is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if type of <i>annot</i> is popup.<br>
 *			::FSCRT_ERRCODE_ERROR if rectangle cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Annot_GetDeviceRect(FSCRT_ANNOT annot, FS_BOOL bTransformIcon, const FSCRT_MATRIX* matrix, 
									FSCRT_RECT* deviceRect);

/**
 * @brief	Get flags of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	flags		Pointer to a ::FS_DWORD object that receives flags of an annotation.
 *							Please refer to macros <b>FSPDF_ANNOTFLAG_XXX</b> and this can be one or a combination of these macros.<br>
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>flags</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no flags property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if flags cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetFlags(FSCRT_ANNOT annot, FS_DWORD* flags);

/**
 * @brief	Get name of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	name		Pointer to a ::FSCRT_BSTR structure (a UTF-8 string) that receives value of name property.<br>
 *							If there's any error, FSCRT_BSTR::str will be empty if it's not <b>NULL</b>,
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>name</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no name property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if name cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetName(FSCRT_ANNOT annot, FSCRT_BSTR* name);

/**
 * @brief	Get contents of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	contents	Pointer to a ::FSCRT_BSTR structure (a UTF-8 string) that receives value of contents property.<br>
 *							If there's any error, FSCRT_BSTR::str will be empty if it's not <b>NULL</b>,
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>contents</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no content data is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if contents cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetContents(FSCRT_ANNOT annot, FSCRT_BSTR* contents);

/**
 * @brief	Get border of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	border		Pointer to a ::FSPDF_ANNOTBORDER structure that receives border information.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>border</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no border property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if border cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetBorder(FSCRT_ANNOT annot, FSPDF_ANNOTBORDER* border);

/**
 * @brief	Get fill or border color of an annotation.
 *
 * @details	For border color, this function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.<br>
 *			For filling color, this function only supports square, circle, polygon, polyline, and free text annotations.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	isFillColor	A boolean value used to decide to get the fill color or the border color:<br>
 *							<b>TRUE</b> for fill color, and <b>FALSE</b> for border color.
 * @param[out]	color		Pointer to a ::FS_ARGB object that receives value of specific type color property.
 *							Format: 0xAARRGGBB, and alpha value is ignored.<br>
 *							If there's any error, it will be set 0x00000000.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>color</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no border or fill color property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if color cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetColor(FSCRT_ANNOT annot, FS_BOOL isFillColor, FS_ARGB* color);

/**
 * @brief	Get modification time of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	dt			Pointer to a ::FSCRT_DATETIMEZONE structure that receives value of modification time property.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>dt</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no modification time property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if modification time cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetModifiedDateTime(FSCRT_ANNOT annot, FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Get creation time of a markup annotation.
 *
 * @details	Only markup annotations can have creation time property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	dt			Pointer to a ::FSCRT_DATETIMEZONE structure that receives value of creation time property.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>dt</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no creation time property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if creation time cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetCreationDateTime(FSCRT_ANNOT annot, FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Get subject of a markup annotation.
 *
 * @details	Only markup annotations can have subject property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	subject		Pointer to a ::FSCRT_BSTR structure (a UTF-8 string) that receives value of subject property.<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b>,
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>subject</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no subject property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if subject cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetSubject(FSCRT_ANNOT annot, FSCRT_BSTR* subject);

/**
 * @brief	Get title of a markup annotation.
 *
 * @details	Only markup annotations can have title property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	title		Pointer to a ::FSCRT_BSTR structure (a UTF-8 string) that receives value of title property.<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b>,
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>title</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no title property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if title cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetTitle(FSCRT_ANNOT annot, FSCRT_BSTR* title);

/**
 * @brief	Get opacity of a markup annotation.
 *
 * @details	Only markup annotations can have opacity property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	opacity		Pointer to a ::FS_FLOAT object that receives value of opacity property. Valid range is from 0.0 to 1.0.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>opacity</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no opacity property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if opacity cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetOpacity(FSCRT_ANNOT annot, FS_FLOAT* opacity);

/**
 * @brief	Get intent of a markup annotation.
 *
 * @details	Only markup annotations can have intent property.<br>
 *			For annotations such as FreeText, Line, Polygon, and Polyline, intent name has been predefined.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	intent		Pointer to a ::FSCRT_BSTR structure (a UTF-8 string) that receives value of intent property. 
 *							Please refer to macro definitions <b>FSPDF_ANNOT_INTENTNAME_XXX</b> and this should be one of these macros.<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b>,
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>intent</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no intent property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if intent time cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetIntent(FSCRT_ANNOT annot, FSCRT_BSTR* intent);

/**
 * @brief	Get open status of a text or popup annotation.
 *
 * @details	Only text and popup annotation can have open status property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	isOpen		Pointer to a ::FS_BOOL object that receives value of open status property. 
 *							If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>status</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no open status property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if open status cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetOpenStatus(FSCRT_ANNOT annot, FS_BOOL* isOpen);

/**
 * @brief	Get icon name of an annotation.
 *
 * @details	Only text, file attachment, stamp and sound annotation can have icon name property.<br>
 *			Parameter <i>iconName</i> is relative to type of parameter <i>annot</i>.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	iconName	Pointer to a ::FSCRT_BSTR structure (a UTF-8 string) that receives value of icon name property.
 *							Please refer to	macros <b>FSPDF_ANNOT_ICONNAME_XXX</b> and this should be one of these macros.<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b>,
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>iconName</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no icon name property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if icon name cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetIconName(FSCRT_ANNOT annot, FSCRT_BSTR* iconName);

/**
 * @brief	Get alignment of a free text annotation.
 *
 * @details	Only free text annotation can have alignment property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	alignment	Pointer to a ::FS_INT32 object that receives value of alignment property. 
 *							It should be one of the following: <br>
 *							<ul>
 *							<li>0: Left-justified</li>
 *							<li>1: Centered</li>
 *							<li>2: Right-justified</li>
 *							</ul>
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>alignment</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no alignment (justification) property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if alignment cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetAlignment(FSCRT_ANNOT annot, FS_INT32* alignment);

/**
 * @brief	Get highlighting mode of a link or widget annotation.
 *
 * @details	Only link and widget annotations can have highlighting mode property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	hlMode		Pointer to a ::FS_INT32 object that receives value of highlighting mode property. 
 *							Please refer to macro definitions <b>FSPDF_ANNOT_HIGHLIGHTINGMODE_XXX</b> and this should be one of these macros.<br>
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>hlMode</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no highlighting mode property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if highlighting mode cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetHighlightingMode(FSCRT_ANNOT annot, FS_INT32* hlMode);

/**
 * @brief	Get quadrilaterals points of an annotation.
 *
 * @details	Only link, highlight, underline, squiggly-underline and strikeout annotation can have quad-points property.<br>
 *			This function needs to be called twice to get quadrilaterals points:<br>
 *			For the first time, set parameter <i>quadPoints</i> to <b>NULL</b> to get the actual count of quadrilaterals points.
 *			The count value will be set to parameter <i>count</i> as a result returned by the first calling.<br>
 *			Then use <i>count</i> to allocate <i>quadPoints</i>.<br>
 *			For the second time, input the allocated <i>quadPoints</i> and its size <i>count</i> to get the quadrilaterals points. 
 *			When this function returns successfully, <i>quadPoints</i> will get the quadrilaterals points array and <i>count</i> will get the actual count.<br>
 *			The size of the input array should not be less than the actual count.<br>
 *			The order of quadrilaterals points will be as follow:
 *			<pre>
 *			(x1, y1)           (x2, y2)
 *				----------------
 *				|               |
 *				|               |
 *				----------------
 *			(x3, y3)           (x4, y4)
 *			</pre>
 *
 * @param[in]		annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]		quadPoints	Pointer to a ::FSCRT_QUADPOINTSF structure that receives array of quadrilaterals points of an annotation. 
 *								This can be <b>NULL</b> for getting actual count of quadrilaterals points before allocate this array. <br>
 *								Please see detail description about how to use this function.
 * @param[in,out]	count		Pointer to a ::FS_INT32 object. <br>
 *								When this function is called, it should be the size of array <i>quadPoints</i> if parameter <i>quadPoints</i> isn't <b>NULL</b>.<br>
 *								When this function returns, it will receive actual count of quadrilaterals points which are got.<br>
 *								Please see detail description about how to use this function.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>count</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no quad-points property is found.<br>
 * 			::FSCRT_ERRCODE_BUFFEROVERFLOW if parameter <i>quadPoints</i> is valid but <i>count</i> is less than required amount.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if quadrilaterals points cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetQuadPoints(FSCRT_ANNOT annot, FSCRT_QUADPOINTSF* quadPoints, FS_INT32* count);

/**
 * @brief	Get callout line points of a free text annotation.
 *
 * @details	Only free text annotation can have callout line points property.<br>
 *			Callout line points property can have 4 or 6 numbers:<br>
 *			<ul>
 *			<li> 6 numbers represent the starting, knee point, and ending coordinates of a line annotation in PDF page space.</li>
 *			<li> 4 numbers represent the starting and ending coordinates of a line annotation.
 *				In this situation, parameter <i>x3</i> and <i>y3</i> will have the same value as <i>x2</i> and <i>y2</i>.</li>
 *			</ul>
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	x1			Pointer to a ::FS_FLOAT object that receives first x position. If there's any error, it will be set 0.
 * @param[out]	y1			Pointer to a ::FS_FLOAT object that receives first y position. If there's any error, it will be set 0.
 * @param[out]	x2			Pointer to a ::FS_FLOAT object that receives second x position. If there's any error, it will be set 0.
 * @param[out]	y2			Pointer to a ::FS_FLOAT object that receives second y position. If there's any error, it will be set 0.
 * @param[out]	x3			Pointer to a ::FS_FLOAT object that receives third x position. If there's any error, it will be set 0.
 * @param[out]	y3			Pointer to a ::FS_FLOAT object that receives third y position. If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, <i>x1</i>, <i>y1</i>, <i>x2</i>, <i>y2</i>, <i>x3</i>, or <i>y3</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no callout line points property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if callout line points cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetCalloutLinePoints(FSCRT_ANNOT annot, FS_FLOAT* x1, FS_FLOAT* y1, FS_FLOAT* x2, FS_FLOAT* y2, FS_FLOAT* x3, FS_FLOAT* y3);

/**
 * @brief	Get the margin between inner rectangle and rectangle of an annotation.
 *
 * @details	Only free text, square, circle, and caret annotation can have inner rectangle margin property.
 *			For free text annotation, inner rectangle is where the annotation's text should be displayed. <br>
 *			For square, circle, and caret annotation, inner rectangle means the actual boundaries of underlying square, circle or caret.
 *			Usually, the sum of top and bottom margin values should be less than the height of annotation's rectangle, 
 *			and the sum of left and right margin values should be less than the width of annotation's rectangle.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	left		Pointer to a ::FS_FLOAT object that receives the left margin value. If there's any error, it will be set 0.
 * @param[out]	top			Pointer to a ::FS_FLOAT object that receives the top margin value. If there's any error, it will be set 0.
 * @param[out]	right		Pointer to a ::FS_FLOAT object that receives the right margin value. If there's any error, it will be set 0.
 * @param[out]	bottom		Pointer to a ::FS_FLOAT object that receives the bottom margin value. If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, <i>left</i>, <i>top</i>, <i>right</i>, or <i>bottom</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no inner rectangle margin property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if inner rectangle cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetInnerRectMargin(FSCRT_ANNOT annot, FS_FLOAT* left, FS_FLOAT* top, FS_FLOAT* right, FS_FLOAT* bottom);

/**
 * @brief	Get line ending styles of an annotation.
 *
 * @details	Only free text, line, and polyline annotation can have line ending styles property.
 *			Specially, for free text annotation, only when its intent is "FreeTextCallout", it can have line ending styles property.
 *
 * @param[in]	annot				Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	startingStyle		Pointer to a ::FSCRT_BSTR structure (a UTF-8 string) that receives value of starting style property.<br>
 *									Please refer to macro definitions <b>FSPDF_ANNOT_LINEENDINGSTYLE_XXX</b> and this should be one of these macros.<br>
 *									If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b>,
 *									and FSCRT_BSTR::len will be set 0.
 * @param[out]	endingStyle			Pointer to a ::FSCRT_BSTR structure (a UTF-8 string) that receives value of ending style property.<br>
 *									Please refer to macro definitions <b>FSPDF_ANNOT_LINEENDINGSTYLE_XXX</b> and this should be one of these macros.<br>
 *									If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b>,
 *									and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, <i>startingStyle</i>, or <i>endingStyle</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no line ending styles property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if line ending styles cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetLineEndingStyles(FSCRT_ANNOT annot, FSCRT_BSTR* startingStyle, FSCRT_BSTR* endingStyle);

/**
 * @brief	Get line position of a line annotation.
 *
 * @details	Only line annotation can have line position property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	x1			Pointer to a ::FS_FLOAT object that receives starting point in horizontal direction. If there's any error, it will be set 0.
 * @param[out]	y1			Pointer to a ::FS_FLOAT object that receives starting point in vertical direction. If there's any error, it will be set 0.
 * @param[out]	x2			Pointer to a ::FS_FLOAT object that receives ending point in horizontal direction. If there's any error, it will be set 0.
 * @param[out]	y2			Pointer to a ::FS_FLOAT object that receives ending point in vertical direction. If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, <i>x1</i>, <i>y1</i>, <i>x2</i>, or <i>y2</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no line position property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if line position cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetLinePosition(FSCRT_ANNOT annot, FS_FLOAT* x1, FS_FLOAT* y1, FS_FLOAT* x2, FS_FLOAT* y2);

/**
 * @brief	Get leader line length of a line annotation.
 *
 * @details	Only line annotation can have leader line length property.
 *			The length of leader lines in PDF page coordination extends from each endpoint of the line perpendicular to the line itself.
 *			A positive value means that the leader lines appear in the direction 
 *			that is clockwise when traversing the line from its starting point to its ending point, 
 *			while a negative value indicates the opposite direction. 
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	length		Pointer to a ::FS_FLOAT object that receives value of leader line length property. 
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>length</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no leader line length property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if leader line length cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetLeaderLineLength(FSCRT_ANNOT annot, FS_FLOAT* length);

/**
 * @brief	Get leader line extension of a line annotation.
 *
 * @details	Only line annotation can have leader line extension property. 
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	extLength	Pointer to a ::FS_FLOAT object that receives value of leader line extension property.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>extLength</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no leader line extension property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if leader line extension cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetLeaderLineExtension(FSCRT_ANNOT annot, FS_FLOAT* extLength);

/**
 * @brief	Get leader line offset of a line annotation.
 *
 * @details	Only line annotation can have leader line offset property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	offset		Pointer to a ::FS_FLOAT object that receives value of leader line offset property.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>offset</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no leader line offset property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if leader line offset cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetLeaderLineOffset(FSCRT_ANNOT annot, FS_FLOAT* offset);

/**
 * @brief	Check if there's a caption to a line annotation.
 *
 * @details	Only line annotation can have caption contents property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	hasCap		Pointer to a ::FS_BOOL object that receives a boolean value that specifies whether there's a caption to annotation or not.<br>
 *							If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>isCap</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no caption contents property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if caption contents cannot be checked because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_HasCaptionContents(FSCRT_ANNOT annot, FS_BOOL* hasCap);

/**
 * @brief	Get caption position of a line annotation.
 *
 * @details	Only line annotation can have caption position property.<br>
 *			Caption position is meaningful only when key "Cap" is true, which can be checked by function ::FSPDF_Annot_HasCaptionContents.
 *			Valid values for caption position are:<br>
 *			<ul>
 *			<li>Inline: means caption will be centered inside the line.</li>
 *			<li>Top: means caption will be on top of the line.</li>
 *			</ul>
 *			Usually, the default value is Inline.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	captionPos	Pointer to a ::FSCRT_BSTR structure that receives value of caption position property. 
 *							Please see details description part for more information.<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> when call this function, 
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>captionPos</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no caption position property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if caption position cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetCaptionPosition(FSCRT_ANNOT annot, FSCRT_BSTR* captionPos);

/**
 * @brief	Get caption offset of a line annotation.
 *
 * @details Only line annotation can have caption offset property.<br>
 *			Caption offset is the offset of caption from its normal position.
 *			It is meaningful only when key "Cap" is true, which can be checked by function ::FSPDF_Annot_HasCaptionContents.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	offsetx		Pointer to a ::FS_FLOAT object that receives horizontal offset along annotation line from its midpoint:<br>
 *							<ul>
 *							<li>A positive value indicates offset to the right.</li>
 *							<li>A negative value indicates offset to the left. </li>
 *							</ul>
 *							If there's any error, it will be set 0.
 * @param[out]	offsety		Pointer to a ::FS_FLOAT object that receives vertical offset perpendicular to annotation line:<br>
 *							<ul>
 *							<li>A positive value indicates a shift up.</li>
 *							<li>A negative value indicates a shift down. </li>
 *							</ul>
 *							If there's any error, it will be set 0.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, <i>offsetx</i> or <i>offsety</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no valid caption offset property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if caption offset cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetCaptionOffset(FSCRT_ANNOT annot, FS_FLOAT* offsetx, FS_FLOAT* offsety);

/**
 * @brief	Get vertices of a polygon or polyline annotation.
 *
 * @details	Only polygon, and polyline annotation can have vertices property.<br>
 *			This function needs to be called twice to get vertices:<br>
 *			For the first time, set parameter <i>vertices</i> to <b>NULL</b> to get the actual count of vertices.
 *			The count value will be set to parameter <i>count</i> as a result returned by the first calling.<br>
 *			Then use <i>count</i> to allocate <i>vertices</i>.<br>
 *			For the second time, input the allocated <i>vertices</i> and its size <i>count</i> to get the vertices. 
 *			When this function returns successfully, <i>vertices</i> will get the vertices array and <i>count</i> will get the actual count.<br>
 *			The size of the input array should not be less than the actual count.
 *
 * @param[in]		annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]		vertices		Pointer to a ::FS_FLOAT object that receives vertices array of an annotation. 
 *									In this array, 2 numbers is a pair, representing a point in PDF page coordinate system.
 *									This can be <b>NULL</b> for getting actual count of quadrilaterals points before allocate this array.<br>
 *									Please see detail description about how to use this function.
 * @param[in,out]	count			Pointer to a ::FS_INT32 object. Usually, it should be a multiple of 2.<br>
 *									When this function is called, it should be the size of array <i>vertices</i> if parameter <i>vertices</i> isn't <b>NULL</b>.<br>
 *									When this function returns, it will receive actual count of vertices array which are got.<br>
 *									Please see detail description about how to use this function.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>count</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no vertices property is found.<br>
 * 			::FSCRT_ERRCODE_BUFFEROVERFLOW if parameter <i>vertices</i> is valid but <i>count</i> is less than required amount.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if vertices cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.	
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetVertices(FSCRT_ANNOT annot, FS_FLOAT* vertices, FS_INT32* count);

/**
 * @brief	Get symbol of a caret annotation.
 *
 * @details	Only caret annotation can have symbol property.<br>
 *			A symbol is associated with caret. Valid values are:<br>
 *			<ul>
 *			<li>P: A new paragraph symbol should be associated with the caret.</li>
 *			<li>None: No symbol should be associated with the caret.</li>
 *			</ul>
 *			Usually, default value is None.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	symbol		Pointer to a ::FSCRT_BSTR structure that receives value of symbol property.<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> when call this function, 
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>symbol</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no symbol property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if symbol cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetSymbol(FSCRT_ANNOT annot, FSCRT_BSTR* symbol);

/**
 * @brief	Get ink list data of an ink annotation.
 *
 * @details	Only ink annotation can have ink list property.<br>
 *			InkList is an array of N arrays, each representing a stroked path.
 *			Each array is a series of alternating horizontal and vertical coordinates in PDF page space, 
 *			specifying points along the path.
*
 * @param[in]		annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]		pathData	Pointer to a <b>FSCRT_PATHDATA</b> handle to receive path data of ink list property.<br>
 *								When this is not used any more, application should release this handle by calling function ::FSCRT_PathData_Release.<br>
 *								Currently, types of points in <i>pathData</i> are limited.<br>
 *								By default, the type of first point in <i>pathData</i> is ::FSCRT_POINTTYPE_MOVETO, 
 *								and the rest is ::FSCRT_POINTTYPE_BEZIERTO.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>pathData</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no ink list property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if ink list data cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetInkList(FSCRT_ANNOT annot, FSCRT_PATHDATA* pathData);

/**
 * @brief	Get attachment of a file attachment annotation.
 *
 * @details	Only file attachment annotation can have attachment property.
 *
 * @param[in]		annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]		attachment	Pointer to a <b>FSPDF_ATTACHMENT</b> handle to receive a PDF attachment handle if successful.<br>
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>attachment</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no attachment property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if attachment cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetAttachment(FSCRT_ANNOT annot, FSPDF_ATTACHMENT* attachment);

/**
 * @brief	Get default appearance of a free text annotation, which can be used in formatting text.
 *
 * @details	Only free text annotation can have default appearance property.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	defAppearance	Pointer to a ::FSPDF_DEFAULTAPPEARANCE structure that receives default appearance of a free text annotation.<br>
 *								ATTENTION: no support for getting FSPDF_DEFAULTAPPEARANCE::font currently.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>defAppearance</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no default appearance property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if default appearance cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetDefaultAppearance(FSCRT_ANNOT annot, FSPDF_DEFAULTAPPEARANCE* defAppearance);

/**
 * @brief	Get icon fit of a widget annotation.
 *
 * @details	Only widget annotation(pushbutton field only) can have icon-fit property in MK dictionary.<br>
 *			The icon fit property belongs to MK dictionary. It specifies how to display widget annotation's icon within the annotation rectangle. 
 *			If present, icon fit property applies to all of annotation's icons (normal, rollover, and alternate).<br>
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	iconFit		Pointer to a ::FSPDF_ANNOTICONFIT structure that receives value of icon fit property.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>iconFit</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if there's no valid MK dictionary, or no icon-fit property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if icon fit cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetIconFit(FSCRT_ANNOT annot, FSPDF_ANNOTICONFIT* iconFit);

/**
 * @brief	Check if specific entry is in MK dictionary.
 *
 * @details	Only screen and widget annotation can have MK dictionary.<br>
 *			MK entry can be used to provide an appearance characteristics dictionary 
*			containing additional information for constructing the annotation's appearance stream.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	mkEntry		An integer value used to specify entry in MK dictionary. 
 *							Please refer to macro definitions <b>FSPDF_ANNOT_MKENTRY_XXX</b> and this should be one of these macros.
 * @param[out]	hasEntry	Pointer to a ::FS_BOOL object that receives a boolean value which specifies 
 *							whether specific entry is in MK dictionary or not.<br>
 *							If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>hasEntry</i> is <b>NULL</b>, or <i>mkEntry</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no MK dictionary is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if specified entry cannot be checked because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_HasMKEntry(FSCRT_ANNOT annot, FS_INT32 mkEntry, FS_BOOL* hasEntry);

/**
 * @brief	Get rotation (the number of degrees) in MK dictionary.
 * 
 * @details	Only screen and widget annotation can have rotation property in MK dictionary.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	degree		Pointer to a ::FS_INT32 object which that receives rotation entry in MK dictionary. 
 *							The value will be a multiple of 90.<br>
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>degree</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no MK dictionary or no MK rotation property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if rotation cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetMKRotation(FSCRT_ANNOT annot, FS_INT32* degree);

/**
 * @brief	Get color of specific type in MK dictionary.
 *
 * @details	Only screen and widget annotations can have color property in MK dictionary.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	mkEntry		An integer to specify the type of color entry in MK dictionary. It should be one of the followings:<br>
 *							<ul>
 *							<li>::FSPDF_ANNOT_MKENTRY_BORDERCOLOR</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_BACKGROUNDCOLOR</li>
 *							</ul>
 * @param[out]	color		Pointer to a ::FS_ARGB object that receives color of specific type. Format: 0xAARRGGBB, and alpha value is ignored.
 *							If there's any error, it will be set 0x00000000.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>color</i> is <b>NULL</b>, or <i>mkEntry</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no MK dictionary or no MK color property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if specified color cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetMKColor(FSCRT_ANNOT annot, FS_INT32 mkEntry, FS_ARGB* color);

/**
 * @brief	Get caption of a specific type in MK dictionary.
 *
 * @details	Only widget annotation can have caption property in MK dictionary.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	mkEntry		An integer to specify type of caption entry in MK dictionary. It should be one of the followings:<br>
 *							<ul>
 *							<li>::FSPDF_ANNOT_MKENTRY_NORMALCAPTION</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_ROLLOVERCAPTION</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_DOWNCAPTION</li>
 *							</ul>
 * @param[out]	caption		Pointer to a ::FSCRT_BSTR structure (a UTF-8 string) that receives caption in MK dictionary.<br>
 *							If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b>,
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>caption</i> is <b>NULL</b>, or <i>mkEntry</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no MK dictionary or no MK caption property is found.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if specified caption cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetMKCaption(FSCRT_ANNOT annot, FS_INT32 mkEntry, FSCRT_BSTR* caption);

/**
 * @brief	Get icon bitmap of specific icon type in MK dictionary.
 *
 * @details	Widget and screen annotation can have icon property in MK dictionary.<br>
 *			Actually, icon of widget annotation is defined by a form XObject. 
 *			Foxit PDF SDK only supports to get icon bitmap if this form XObject's appearance is an image object.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	mkEntry		An integer to specify the type of icon entry in MK dictionary. It should be one of the followings:<br>
 *							<ul>
 *							<li>::FSPDF_ANNOT_MKENTRY_NORMALICON</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_ROLLOVERICON</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_DOWNICON</li>
 *							</ul>
 * @param[out]	bitmap		Pointer to a <b>FSCRT_BITMAP</b> handle to receive a bitmap handle of specific icon if successful.<br>
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>bitmap</i> is <b>NULL</b>, or <i>mkEntry</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no MK dictionary or no MK icon property is found.<br>
 * 			::FSCRT_ERRCODE_UNSUPPORTED if appearance of icon is not an image object.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if icon bitmap cannot be obtained specified because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetMKIconBitmap(FSCRT_ANNOT annot, FS_INT32 mkEntry, FSCRT_BITMAP* bitmap);

/**
 * @brief	Get a PDF form control from a widget annotation handle.
 *
 * @details	This function is only valid for widget annotations. A form control could be got only if the function ::FSPDF_Form_Load is called before.
 * 
 * @param[in]	widgetAnnot		Handle to a <b>FSPDF_ANNOT</b> object which is a PDF annotation.
 * @param[out]	formControl		Pointer to a <b>FSCRT_FORMCONTROL </b> handle that receives a PDF form control.
 *								If there's any error, it'll be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>widgetAnnot</i>, or <i> formControl</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>widgetAnnot</i> is not a widget annotation.<br>
 *			::FSCRT_ERRCODE_ERROR if ::FSPDF_Form_Load isn't called before, or other errors occur.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>formControl</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetFormControl(FSCRT_ANNOT widgetAnnot, FSPDF_FORMCONTROL* formControl);

/**
 * @brief	Get the dictionary of an annotation.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	dictionary	Pointer to a <b>FSPDF_OBJECT</b> handle that receives the annotation dictionary object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>dictionary</i> is a <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if the dictionary object of annotation cannot be obtained for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Annot_GetDict(FSCRT_ANNOT annot, FSPDF_OBJECT* dictionary);

/*******************************************************************************/
/* Markup controls                                                             */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_ANNOTSTATEMODEL_
#define _FSPDF_DEF_MACRO_ANNOTSTATEMODEL_
/**
 * @name	Macro Definition for Annotation State Model
 */
/**@{*/

/** @brief	State model is marked */
#define FSPDF_ANNOTSTATEMODEL_MARKED		0
/** @brief	State model is review */
#define FSPDF_ANNOTSTATEMODEL_REVIEW		1

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOTSTATEMODEL_ */

#ifndef _FSPDF_DEF_MACRO_ANNOTSTATE_
#define _FSPDF_DEF_MACRO_ANNOTSTATE_
/** 
 * @name	Macro Definition for Annotation Marked State
 * @brief	These are meaningful when state model is ::FSPDF_ANNOTSTATEMODEL_MARKED.
 */
/**@{*/

/** @brief	The state of marked model is marked */
#define FSPDF_ANNOTSTATE_MARKED_MARKED			0
/** @brief	The state of marked model is unmarked */
#define FSPDF_ANNOTSTATE_MARKED_UNMARKED		1

/** @brief	The state of review model is accepted */
#define FSPDF_ANNOTSTATE_REVIEW_ACCEPTED		0
/** @brief	The state of review model is rejected */
#define FSPDF_ANNOTSTATE_REVIEW_REJECTED		1
/** @brief	The state of review model is canceled */
#define FSPDF_ANNOTSTATE_REVIEW_CANCELLED		2
/** @brief	The state of review model is completed */
#define FSPDF_ANNOTSTATE_REVIEW_COMPLETED		3
/** @brief	The state of review model is none */
#define FSPDF_ANNOTSTATE_REVIEW_NONE			4

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ANNOTSTATE_ */

/**
 * @brief	Count specific state annotations associated with a markup annotation.
 *
 * @details	This function only supports markup annotations. The markup annotations may have an author-specific state associated with them.
 * The state is not specified in the annotation itself but in a separate text annotation that refers to the original annotation by means of
 * its IRT entry. 
 * This function provided to count these state text annotations with the specific state model. 
 * For more details, please refer to PDF Reference 1.7 P620 "Annotation States".
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an markup annotation object.
 * @param[in]	stateModel	An integer value that specifies state model. 
 *							Please refer to macro definitions <b>FSPDF_ANNOTSTATEMODEL_XXX</b> and this should be one of these macros.
 * @param[out]	count		Pointer to a ::FS_INT32 object that receives count of state annotations.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>count</i> is <b>NULL</b>, or <i>stateModel</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if specific state annotations cannot be counted because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_CountStateAnnots(FSCRT_ANNOT annot, FS_INT32 stateModel, FS_INT32* count);

/**
 * @brief	Get specified state annotation associated with a markup annotation.
 *
 * @details	This function only supports markup annotations.The markup annotations may have an author-specific state associated with them.
 * The state is not specified in the annotation itself but in a separate text annotation that refers to the original annotation by means of
 * its IRT entry. 
 * This function provided to get the specific state text annotation with the specific state model.
 * For more details, please refer to PDF Reference 1.7 P620 "Annotation States".
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	stateModel		An integer value that specifies state model. 
 *								Please refer to macro definitions <b>FSPDF_ANNOTSTATEMODEL_XXX</b> and this should be one of these macros.
 * @param[in]	index			The index of state annotations to be got. Range: 0 to (<i>annotcount</i>-1). 
 *								<i>annotcount</i> is returned by by function ::FSPDF_Annot_CountStateAnnots with the same parameter <i>stateModel</i>.
 * @param[out]	stateAnnot		Pointer to a <b>FSCRT_ANNOT</b> handle that receives a specific state annotation.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>stateAnnot</i> is <b>NULL</b>, or <i>stateModel</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if specified state annotation cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>stateAnnot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetStateAnnot(FSCRT_ANNOT annot, FS_INT32 stateModel, FS_INT32 index, FSCRT_ANNOT* stateAnnot);

/**
 * @brief	Get state model and state out of a state text annotation.
 *
 * @details	This function only supports markup annotations.The markup annotations may have an author-specific state associated with them.
 * The state is not specified in the annotation itself but in a separate text annotation that refers to the original annotation by means of
 * its IRT entry. 
 * This function provided to get the state and stateModel of a state text annotation.
 * For more details, please refer to PDF Reference 1.7 P620 "Annotation States".
 *
 * @param[in]	stateAnnot	Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	stateModel	Pointer to ::FS_INT32 object that receives state model. 
 *							Please refer to macro definitions <b>FSPDF_ANNOTSTATEMODEL_XXX</b> and this should be one of these macros.<br>
 *							If there's any error, it will be set -1.
 * @param[out]	state		Pointer to ::FS_INT32 object that receives state. 
 *							Please refer to macro definitions <b>FSPDF_ANNOTSTATE_XXX</b> and this should be one of these macros.<br>
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>stateAnnot</i>, <i>stateModel</i>, or <i>state</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if state model or state cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>stateAnnot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Annot_GetState(FSCRT_ANNOT stateAnnot, FS_INT32* stateModel, FS_INT32* state);

/**
 * @brief	Check whether an annotation is in a group.
 *
 * @details	This function only supports markup annotations.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	isGrouped	Pointer to a ::FS_BOOL object that receives the result.
 *							If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>isGrouped</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if input annotation is not a markup annotation or the check cannot be done because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_IsGrouped(FSCRT_ANNOT annot, FS_BOOL* isGrouped);

/**
 * @brief	Get header annotation of a group, to which an annotation belongs.
 *
 * @details	This function only supports markup annotations.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	groupHeader		Pointer to a <b>FSCRT_ANNOT</b> handle that receives header annotation.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>groupHeader</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no header annotation is found.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if input annotation is not a markup annotation or header annotation of group cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>groupHeader</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetGroupHeader(FSCRT_ANNOT annot, FSCRT_ANNOT* groupHeader);

/**
 * @brief	Get group elements if annotation is in a group, including itself.
 *
 * @details	This function only supports markup annotations.<br>
 *			This function needs to be called twice to get the group elements:<br>
 *			For the first time, set parameter <i>elements</i> to <b>NULL</b> to get the actual count of group elements.
 *			The count value will be set to parameter <i>count</i> as a result returned by first calling.<br>
 *			Then use <i>count</i> to allocate <i>elements</i>.<br>
 *			For the second time, input the allocated <i>elements</i> and its size <i>count</i> to get the group elements. 
 *			When this function returns successfully, <i>elements</i> will get the group elements and <i>count</i> will get the actual count.<br>
 *			The size of the input array should not be less than the actual count.
 *
 * @param[in]		annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]		elements	Pointer to a <b>FSCRT_ANNOT</b> handle that receives array of group elements. 
 *								This can be <b>NULL</b> for getting actual count of group elements before allocate this array. <br>
 *								Please see detail description about how to use this function.
 * @param[in,out]	count		Pointer to a ::FS_INT32 object.<br>
 *								When this function is called, it should be the size of array <i>elements</i> if parameter <i>elements</i> isn't <b>NULL</b>.<br>
 *								When this function returns, it will receive actual count of group elements which are got.<br>
 *								Please see detail description about how to use this function.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>count</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_BUFFEROVERFLOW if parameter <i>elements</i> is valid but <i>count</i> is less than required amount.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if input annotation is not a markup annotation or group elements cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>elements</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetGroupElements(FSCRT_ANNOT annot, FSCRT_ANNOT* elements, FS_INT32* count);

/**
 * @brief	Count replies of a markup annotation.
 *
 * @details	This function only supports markup annotations.
 *
 * @param[in]	annot 			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	count			Pointer to a ::FS_INT32 object which that receives count of replies. 
 *								If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>count</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if cannot count replies because of any other reason.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_CountReplies(FSCRT_ANNOT annot, FS_INT32* count);

/**
 * @brief	Get reply with specifies index of a markup annotation.
 *
 * @details	This function only supports markup annotations.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	index			The index of reply annotations. Range: 0 to (replycount-1). 
 *								<i>replycount</i> is returned by function ::FSPDF_Annot_CountReplies.
 * @param[out]	replyAnnot		Pointer to a <b>FSCRT_ANNOT</b> handle that receives reply annotation.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>replyAnnot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if cannot insert a reply because of any other reason.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>replyAnnot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetReply(FSCRT_ANNOT annot, FS_INT32 index, FSCRT_ANNOT* replyAnnot);

/**
 * @brief	Get a pop-up annotation from a specific markup annotation.
 *
 * @details	Only markup annotations can have pop-up annotations.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[out]	popupAnnot	Pointer to a <b>FSCRT_ANNOT</b> handle that receives a pop-up annotation.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>popupAnnot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>annot</i> doesn't have a pop-up annotation.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>annot</i> is not markup annotation.
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the Pop-up annotation cannot be obtained because of any other reason.
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT        FSPDF_Annot_GetPopup(FSCRT_ANNOT annot, FSCRT_ANNOT* popupAnnot);

/*******************************************************************************/
/* Annotation trigger actions                                                  */
/*******************************************************************************/
/**
 * @brief	Count actions associated with an annotation.
 *
 * @details	Only link , screen and widget annotations can have action.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	trigger			The trigger of action. Please refer to macro definition <b>FSPDF_TRIGGER_ANNOT_XXX</b> and 
 *								this should be one of these macros.
 * @param[out]	count			Pointer to a ::FS_INT32 object that receives count of actions.
 *								If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>count</i> is <b>NULL</b>, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if actions cannot be counted because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_CountActions(FSCRT_ANNOT annot, FS_INT32 trigger, FS_INT32* count);

/**
 * @brief	Get action data of specific index associated with an annotation.
 *
 * @details	Only link , screen and widget annotations can have action.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	trigger			The trigger of action. Please refer to macro definition <b>FSPDF_TRIGGER_ANNOT_XXX</b> and 
 *								this should be one of these macros.
 * @param[in]	index			The index of actions. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Annot_CountActions.
 * @param[out]	actionData		Pointer to a ::FSPDF_ACTIONDATA structure that receives action data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>actionData</i> is <b>NULL</b>, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or no action is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if action data cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_GetAction(FSCRT_ANNOT annot, FS_INT32 trigger, FS_INT32 index, FSPDF_ACTIONDATA* actionData);

/*******************************************************************************/
/* Annotation display                                                          */
/*******************************************************************************/
/**
 * @brief	Render annotations on render context.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>, except ::FSPDF_ANNOTTYPE_WIDGET.<br>
 *			It will take a long time to render annotations with complex or large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass parameter <i>renderProgress</i> to function ::FSCRT_Progress_Continue to continue rendering in steps.
 *			It is necessary to call function ::FSCRT_Progress_Release to destroy <i>renderProgress</i> object if rendering process is done.
 *			<b>ATTENTION</b>: This function doesn't support to render form controls. 
 *			Please use render method in \ref FPDFFORM "PDF Form" module.
 *
 * @param[in]	pdfRenderContext			Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a render context object.
 * @param[in]	renderer					Handle to a <b>FSCRT_RENDERER</b> object which is a renderer object.
 * @param[in]	annots						Pointer to a <b>FSCRT_ANNOT</b> handle which specifies an annotation array. 
 *											Annotations in this array should be on the same page.
 * @param[in]	count						Size of an annotation array.
 * @param[out]	renderProgress				Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *											If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pdfRenderContext</i>, <i>renderer</i>, <i>annots</i> or elements in <i>annots</i>, or <i>renderProgress</i> is <b>NULL</b>, or <i>count</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if render annotations fails because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				<li> <i>annots</i>: this handle is short-term.</li>
 *				<li> <i>renderProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_StartAnnots(FSPDF_RENDERCONTEXT pdfRenderContext, FSCRT_RENDERER renderer, 
											const FSCRT_ANNOT* annots, FS_INT32 count, FSCRT_PROGRESS* renderProgress);

/**
 * @brief	Render all annotations of a page on render context.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>, except ::FSPDF_ANNOTTYPE_WIDGET.<br>
 *			It will take a long time to render annotations with complex or large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass parameter <i>renderProgress</i> to function ::FSCRT_Progress_Continue to continue rendering in steps, 
 *			and should call function ::FSCRT_Progress_Release to destroy <i>renderProgress</i> object if rendering process is done.
 *			<b>ATTENTION</b>: This function doesn't support to render form controls. 
 *			Please use render method in \ref FPDFFORM "PDF Form" module.
 *
 * @param[in]	pdfRenderContext		Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF render context object.
 * @param[in]	renderer				Handle to a <b>FSCRT_RENDERER</b> object which is a renderer object.
 * @param[in]	page					Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[out]	renderProgress			Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *										If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pdfRenderContext</i>, <i>renderer</i>, <i>page</i>, or <i>renderProgress</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if page annotations are not loaded.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if render annotations fails because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>renderProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_StartPageAnnots(FSPDF_RENDERCONTEXT pdfRenderContext, FSCRT_RENDERER renderer, 
												FSCRT_PAGE page, FSCRT_PROGRESS* renderProgress);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFANNOT */

#endif /* _FSPDF_ANNOT_R_H_ */

