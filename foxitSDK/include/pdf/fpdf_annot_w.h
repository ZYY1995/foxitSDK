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
 * @file	fpdf_annot_w.h
 * @brief	Header file for \ref FPDFANNOT "PDF Annotation" module of Foxit PDF SDK.
 * @details	This header file defines PDF annotation supports, mainly about "writing" methods.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Add and remove annotations. </li>
 *			<li>2. Set properties of annotations. </li>
 *			<li>3. Supports to markup annotations. </li>
 *			<li>4. Set annotation trigger actions.</li>
 *			<li>5. Reset appearance of annotation.</li>
 *			</ul><br>
 *			Special attention:
 *			<ul>
 *			<li>
 *				For watermark annotation, it can be set properties 
 *				but cannot be added , removed or reset appearance by using functions in this header file.<br>
 *				User is suggested to use functions in \ref FPDFWATERMARK "PDF Watermark" module for most operations of watermark.<br>
 *			</li>
 *			<li>
 *				For PSInk annotation, it can be removed, set properties or reset appearance
 *				but cannot be added by using functions in this header file.<br>
 *				User should use function ::FSCRT_PSI_ConvertToPDFAnnot in \ref FSPSI "Pressure Sensitive Ink" to generate a PSInk annotation from a PSI object.<br>
 *			</li>
 *			<li>
 *				For Sound, Movie, Screen, PrinterMark, TrapNet and 3D annotations, they can be set basic properties and removed, 
 *				but cannot be added or reset appearance. Currently Foxit PDF SDK doesn't support to set their data.
 *			</li>
 *			<li>
 *				For annotation which is not defined in PDF Reference but consists of some standard annotations, 
 *				it will be treated as different standard annotations.
 *				If user wants to treat these standard annotations as one special annotation, user should do this in application layer.
 *			</li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Annotation Add-on</b> explicitly.
 */

#ifndef _FSPDF_ANNOT_W_H_
#define _FSPDF_ANNOT_W_H_

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
/* Add and remove annotation                                                   */
/*******************************************************************************/
/**
 * @brief	Add an annotation with a specific index, by specific filter.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>, 
 *			except PSInk, 3D, PrinterMark, TrapNet, Sound, Movie, Screen, Watermark and Widget annotations.<br>
 *			For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
 *			For watermark annotation, user is suggested to use functions in \ref FPDFWATERMARK "PDF Watermark" module for most operations of watermark.<br>
 *			For PSInk annotation, user should use function ::FSCRT_PSI_ConvertToPDFAnnot in \ref FSPSI "Pressure Sensitive Ink" 
 *			to generate a PSInk annotation from a PSI object.<br>
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[in]	rect		Pointer to a ::FSCRT_RECTF object to specify the rectangle of an annotation, in PDF page coordinate system.<br>
 *							The value can be set as (0,0,0,0) except for the following annotation types:
 *							::FSPDF_ANNOTTYPE_TEXT, ::FSPDF_ANNOTTYPE_FREETEXT, ::FSPDF_ANNOTTYPE_SQUARE, ::FSPDF_ANNOTTYPE_CIRCLE, 
 *							::FSPDF_ANNOTTYPE_FILEATTACHMENT, ::FSPDF_ANNOTTYPE_STAMP, ::FSPDF_ANNOTTYPE_CARET.
 * @param[in]	annotType	Pointer to a ::FSCRT_BSTR object to specify the type of an annotation. 
 *							Please refer to	macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> and this should be one of these macros.<br>
 *							This should be in the type range defined by parameter <i>filter</i>.
 * @param[in]	filter		Pointer to a filter string.<br>
 *							If it's <b>NULL</b>, parameter <i>index</i> is to all existing annotation.<br>
 *							If it's a valid pointer to ::FSCRT_BSTR, it specifies the annotation type:<br>
 *							<ul>
 *							<li>For single type filter: Please refer to macro definitions <b>FSPDF_ANNOTTYPE_XXX</b> and it should be one of these macros.</li>
 *							<li>For multiple types filter: Use comma to separate different types, for example, "Text, Link, Circle".</li>
 *							</ul>
 * @param[in]	index		The index that this new annotation is to be added in. Range: 0 to (annotcount-1).
 *							<i>annotcount</i> is returned by function ::FSPDF_Annot_GetCount with same <i>filter</i>.<br>
 *							If this is out of the count range(according to parameter <i>filter</i>), 
 *							the new annotation will be added to the last within the range defined by parameter <i>filter</i>.
 * @param[out]	annot		Pointer to a <b>FSCRT_ANNOT</b> handle that receives the newly added annotation.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>annotType</i>, or <i>annot</i> is <b>NULL</b>, 
 *			or parameter <i>rect</i> is empty for text, freetext, square, circle, file attachment, stamp, or caret annotations.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if annotations in parameter <i>page</i> haven't been loaded.<br>
 * 			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>annotType</i> isn't supported currently.<br>
 *			::FSCRT_ERRCODE_ERROR if annotations cannot be added because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_Add(FSCRT_PAGE page, const FSCRT_RECTF* rect, const FSCRT_BSTR* annotType, const FSCRT_BSTR* filter, 
							FS_INT32 index, FSCRT_ANNOT* annot);

/**
 * @brief	Remove an annotation from page.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>, except ::FSPDF_ANNOTTYPE_WATERMARK.<br>
 *			For widget annotation, this function can remove it but user is still strongly suggested not to do so. 
 *			User is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
 *			For watermark annotation, user is suggested to use functions in \ref FPDFWATERMARK "PDF Watermark" module for most operations of watermark.<br>
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>annot</i> is a watermark annotation.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if annotation cannot be removed because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_Remove(FSCRT_ANNOT annot);

/*******************************************************************************/
/* Annotation common properties                                                */
/*******************************************************************************/
/**
 * @brief	Move an annotation to a new position specified by a rectangle.
 *
 * @details	To move an annotation is to reset its rectangle.
 *			This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	newRect		Pointer to a ::FSCRT_RECTF structure that specifies the new position.<br>
 *							The rect should be "normalized" for PDF page coordination: left is always smaller than right, and bottom is always smaller than top.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>newRect</i> is <b>NULL</b>, or <i>newRect</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if annotation cannot be moved because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_Move(FSCRT_ANNOT annot, const FSCRT_RECTF* newRect);

/**
 * @brief	Set flags of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	flags		The flags to be set to the annotation. 
 *							Please refer to macros <b>FSPDF_ANNOTFLAG_XXX</b> and this can be one or a combination of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b> or parameter <i>flags</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if flags cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetFlags(FSCRT_ANNOT annot, FS_DWORD flags);

/**
 * @brief	Set name of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	name		Pointer to a ::FSCRT_BSTR structure that specifies value of name property. It can be <b>NULL</b> or empty.
 *							When it's valid, it should be a valid UTF-8 string.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>name</i> is not in UTF-8 format if it's valid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the name cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetName(FSCRT_ANNOT annot, const FSCRT_BSTR* name);

/**
 * @brief	Set subject of a markup annotation.
 *
 * @details	Only markup annotations can have subject property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	subject		Pointer to a ::FSCRT_BSTR structure that specifies value of subject property. It can be <b>NULL</b> or empty.
 *							When it's valid, it should be a valid UTF-8 string.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>subject</i> is not in UTF-8 format if it's valid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the subject cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetSubject(FSCRT_ANNOT annot, const FSCRT_BSTR* subject);

/**
 * @brief	Set title of a markup annotation.
 *
 * @details	Only markup annotations can have title property.
 *			By convention, this entry can used to identify the user who added the annotation.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	title		Pointer to a ::FSCRT_BSTR structure that specifies value of title property. It can be <b>NULL</b> or empty.
 *							When it's valid, it should be a valid UTF-8 string.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>title</i> is not in UTF-8 format if it's valid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the title cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetTitle(FSCRT_ANNOT annot, const FSCRT_BSTR* title);

/**
 * @brief	Set contents of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.<br>
 *			Specially, for free text annotation, please ensure that it has already got a default appearance. 
 *			If not, please use function ::FSPDF_Annot_SetDefaultAppearance to set it.
 * 
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	contents	Pointer to a ::FSCRT_BSTR structure that specifies value of contents property. It can be <b>NULL</b> or empty.
 *							When it's valid, it should be a valid UTF-8 string.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>contents</i> is not in UTF-8 format if it's valid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the contents cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetContents(FSCRT_ANNOT annot, const FSCRT_BSTR* contents);

/**
 * @brief	Set icon name of an annotation.
 *
 * @details	Only text, file attachment, stamp and sound annotations can have icon name property.<br>
 *			Currently, Foxit PDF SDK doesn't support to set icon name of sound annotations.<br>
 *			Parameter <i>iconName</i> is relative with the type of parameter <i>annot</i>.
 *			ATTENTION: for stamp annotation, Foxit PDF SDK doesn't define default icon appearance currently. 
 *			So if application set icon name of stamp annotation, application should ensure to implement ::FSPDF_ICONPROVIDER for stamp annotation.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	iconName	Pointer to a ::FSCRT_BSTR structure to specify value of icon name property. 
 *							Please refer to macros <b>FSPDF_ANNOT_ICONNAME_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, 
 *			or parameter <i>iconName</i> or FSCRT_BSTR::str is <b>NULL</b> or the FSCRT_BSTR::len is zero.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNSUPPORTED if type of input annotation isn't supported currently .<br>
 *			::FSCRT_ERRCODE_ERROR if the icon name cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetIconName(FSCRT_ANNOT annot, const FSCRT_BSTR* iconName);

/**
 * @brief	Set border of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.<br>
 *			The dash pattern array's elements of ::FSPDF_ANNOTBORDER structure must be nonnegative and not all zeros.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	border		Pointer to a ::FSPDF_ANNOTBORDER structure to specify border information.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>border</i> is <b>NULL</b>,
 *			or FSPDF_ANNOTBORDER::borderStyle is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the border cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetBorder(FSCRT_ANNOT annot, const FSPDF_ANNOTBORDER* border);

/**
 * @brief	Set filling or bordering color of an annotation.
 *
 * @details	For border color, this function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.<br>
 *			For fill color, this function only supports square, circle, polygon, polyline, and free text annotations.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	isFillColor	A boolean value used to decide to set the fill color or the border color:<br>
 *							<b>TRUE</b> for fill color, and <b>FALSE</b> for border color.
 * @param[in]	color		Pointer to a ::FS_ARGB object that sets value of specific type color property.
 *							Format: 0xAARRGGBB, and alpha value is ignored.<br>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the color cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetColor(FSCRT_ANNOT annot, FS_BOOL isFillColor, FS_ARGB color);

/**
 * @brief	Set opacity of an annotation.
 *
 * @details	Only markup annotations can have opacity property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	opacity		Opacity value to be set to the annotation. Valid range is from 0.0 to 1.0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>opacity</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the opacity cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetOpacity(FSCRT_ANNOT annot, FS_FLOAT opacity);

/**
 * @brief	Set alignment of a free text annotation.
 *
 * @details	Only free text annotation can have alignment property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	alignment	Alignment value to be set to the annotation. It should be one of the followings: <br>
 *							<ul>
 *							<li>0: Left-justified</li>
 *							<li>1: Centered</li>
 *							<li>2: Right-justified</li>
 *							</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>alignment</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the alignment cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetAlignment(FSCRT_ANNOT annot, FS_INT32 alignment);

/**
 * @brief	Set creation time of a markup annotation.
 *
 * @details	Only markup annotations can have creation time property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	dt			Pointer to a ::FSCRT_DATETIMEZONE structure that specifies value of creation time property.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>dt</i> is <b>NULL</b>, or parameter <i>dt</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation time is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the creation time cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetCreationDateTime(FSCRT_ANNOT annot, const FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Set modification time of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>.
 * 
 * @param[in]	annot	Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	dt		Pointer to a ::FSCRT_DATETIMEZONE structure that specifies value of modification time property.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>dt</i> is <b>NULL</b>, or parameter <i>dt</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the modified time cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetModifiedDateTime(FSCRT_ANNOT annot, const FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Set intent of a markup annotation.
 *
 * @details	Only markup annotations can have intent property.<br>
 *			For annotations such as FreeText, Line, Polygon, and Polyline, the intent name has been predefined.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	intent		Pointer to a ::FSCRT_BSTR structure that specifies value of intent property.
 *							Please refer to macro definitions <b>FSPDF_ANNOT_INTENTNAME_XXX</b> and this should be one of these macros.
 *							Currently, "PolyLineDimension","PolygonDimension","LineDimension" are not supported.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>intent</i> is invalid.<br>
 *			or parameter <i>intent</i> or FSCRT_BSTR::str is <b>NULL</b> or the FSCRT_BSTR::len is zero.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the intent cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetIntent(FSCRT_ANNOT annot, const FSCRT_BSTR* intent);

/**
 * @brief	Set open status of a text or popup annotation.
 *
 * @details	Only text and popup annotations can have the open status property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	status		A boolean value used to specify the open status to be set to the annotation.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the open status cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetOpenStatus(FSCRT_ANNOT annot, FS_BOOL status);

/**
 * @brief	Set highlighting mode of a link or widget annotation.
 *
 * @details	Only link and widget annotations can have the highlighting mode property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	hlMode		Highlighting mode to be set to the annotation. It should be one of the followings:
 *							<ul>
 *							<li>::FSPDF_ANNOT_HIGHLIGHTINGMODE_NONE</li>
 *							<li>::FSPDF_ANNOT_HIGHLIGHTINGMODE_INVERT</li>
 *							<li>::FSPDF_ANNOT_HIGHLIGHTINGMODE_OUTLINE</li>
 *							<li>::FSPDF_ANNOT_HIGHLIGHTINGMODE_PUSH</li>
 *							<li>::FSPDF_ANNOT_HIGHLIGHTINGMODE_TOGGLE</li>
 *							</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>hlMode</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the highlighting mode cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetHighlightingMode(FSCRT_ANNOT annot, FS_INT32 hlMode);

/**
 * @brief	Set quadrilaterals points of an annotation.
 *
 * @details	Only link, highlight, underline, squiggly-underline and strikeout annotations can have quad-points property.<br>
 *			The order of quadrilaterals points should be as follow:
 *			<pre>
 *			(x1, y1)           (x2, y2)
 *				----------------
 *				|               |
 *				|               |
 *				----------------
 *			(x3, y3)           (x4, y4)
 *			</pre>
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	quadPoints	Pointer to a ::FSCRT_QUADPOINTSF structure that specifies quadrilaterals points to be set to the annotation.
 *							This must be valid.
 * @param[in]	count		Count of quadrilaterals points(parameter <i>quadPoints</i>). And the value should be at least 1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>quadPoints</i> is <b>NULL</b>, or <i>count</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the quadrilaterals points cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetQuadPoints(FSCRT_ANNOT annot, FSCRT_QUADPOINTSF* quadPoints, FS_INT32 count);

/**
 * @brief	Set callout line points of a free text annotation.
 *
 * @details	Only free text annotation can have callout line points property. 
 *			When intent of freetext is set as ::FSPDF_ANNOT_INTENTNAME_FREETEXT_CALLOUT, this property would be necessary.<br>
 *			Callout line points property can have 4 or 6 numbers:<br>
 *			<ul>
 *			<li> 6 numbers represent the starting, knee point, and ending coordinates of a line annotation in PDF page space.</li>
 *			<li> 
 *				4 numbers represent the starting and ending coordinates of a line annotation. 
 *				In this case, parameter <i>x3</i> and <i>y3</i> should set the same value as <i>x2</i> and <i>y2</i>.
 *			</li>
 *			</ul>
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	x1			A float value to specify the new first x position.
 * @param[in]	y1			A float value to specify the new first y position.
 * @param[in]	x2			A float value to specify the new second x position.
 * @param[in]	y2			A float value to specify the new second y position.
 * @param[in]	x3			A float value to specify the new third x position.
 * @param[in]	y3			A float value to specify the new third y position.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the callout line points cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetCalloutLinePoints(FSCRT_ANNOT annot, FS_FLOAT x1, FS_FLOAT y1, FS_FLOAT x2, FS_FLOAT y2, FS_FLOAT x3, FS_FLOAT y3);

/**
 * @brief	Set the margin between inner rectangle and rectangle of an annotation.
 *
 * @details	Only free text, square, circle, and caret annotations can have inner rectangle margin property.<br>
 *			For free text annotation, inner rectangle is where the annotation's text should be displayed. <br>
 *			For square, circle, and caret annotation, inner rectangle means the actual boundaries of underlying square, circle or caret.
 *			Especially for caret annotation, this property is necessary and should be set for display. <br>
 *			When setting inner rectangle margin, application should ensure that:
 *			the sum of top and bottom margin values should be less than the height of annotation's rectangle, 
 *			and the sum of left and right margin values should be less than the width of annotation's rectangle.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	left		A float value to specify the new left margin value. It should not be negative.
 * @param[in]	top			A float value to specify the new top margin value. It should not be negative.
 * @param[in]	right		A float value to specify the new right margin value. It should not be negative.
 * @param[in]	bottom		A float value to specify the new bottom margin value. It should not be negative.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b> 
 *			or parameter <i>left</i>, <i>top</i>, <i>right</i>, or <i>bottom</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the inner rectangle cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Currently, application should ensure this property has been set valid to newly added caret annotation.
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
FS_RESULT	FSPDF_Annot_SetInnerRectMargin(FSCRT_ANNOT annot, FS_FLOAT left, FS_FLOAT top, FS_FLOAT right, FS_FLOAT bottom);

/**
 * @brief	Set line ending styles of an annotation.
 *
 * @details	Only free text, line, and polyline annotations can have line ending styles property.
 *			Specially, for free text annotation, only when its intent is "FreeTextCallout", it can have line ending styles property.
 *
 * @param[in]	annot				Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	startingStyle		Pointer to a ::FSCRT_BSTR structure that specifies value of starting property.
 *									Please refer to macro definitions <b>FSPDF_ANNOT_LINEENDINGSTYLE_XXX</b> and this should be one of these macros.
 * @param[in]	endingStyle			Pointer to a ::FSCRT_BSTR structure that specifies value of ending style property.
 *									Please refer to macro definitions <b>FSPDF_ANNOT_LINEENDINGSTYLE_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>,
 *			or parameter <i>startingStyle</i>, or <i>endingStyle</i>or FSCRT_BSTR::str is <b>NULL</b>, or the FSCRT_BSTR::len is zero.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the line ending styles cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetLineEndingStyles(FSCRT_ANNOT annot, const FSCRT_BSTR* startingStyle, const FSCRT_BSTR* endingStyle);

/**
 * @brief	Set line position of a line annotation.
 *
 * @details	Only line annotation can have line position property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	x1			A float value to specify the new starting point in horizontal direction.
 * @param[in]	y1			A float value to specify the new starting point in vertical direction.
 * @param[in]	x2			A float value to specify the new ending point in horizontal direction.
 * @param[in]	y2			A float value to specify the new ending point in vertical direction.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the line position cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetLinePosition(FSCRT_ANNOT annot, FS_FLOAT x1, FS_FLOAT y1, FS_FLOAT x2, FS_FLOAT y2);

/**
 * @brief	Set leader line length of a line annotation.
 *
 * @details	Only line annotation can have leader line length property.
 *			The length of leader lines in PDF page coordination extends from each endpoint of the line perpendicular to the line itself.
 *			A positive value means that the leader lines appear in the direction 
 *			that is clockwise when traversing the line from its starting point to its ending point, 
 *			while a negative value indicates the opposite direction. 
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	length		A float value to specify new value of leader line length property.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the leader line length cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetLeaderLineLength(FSCRT_ANNOT annot, FS_FLOAT length);

/**
 * @brief	Set leader line extension of a line annotation.
 *
 * @details	Only line annotation can have leader line extension property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	extLength	A float value to specify new value of leader line extension property. It should be non-negative.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>extLength</i> is negative.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the leader line extension cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetLeaderLineExtension(FSCRT_ANNOT annot, FS_FLOAT extLength);

/**
 * @brief	Set leader line offset of a line annotation.
 *
 * @details	Only line annotation can have leader line offset property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	offset		A float value to specify new value of leader line offset property. It should be non-negative.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>offset</i> is negative.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the leader line offset cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetLeaderLineOffset(FSCRT_ANNOT annot, FS_FLOAT offset);

/**
 * @brief	Set flag which decides whether to set a caption to the annotation or not.
 *
 * @details	Only line annotation can have caption contents property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	hasCap		A boolean value that specifies whether to set a caption the annotation or not.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if caption contents cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetCaptionContents(FSCRT_ANNOT annot, FS_BOOL hasCap);

/**
 * @brief	Set caption position of a line annotation.
 *
 * @details	Only line annotation can have caption position property.<br>
 *			Caption position has a meaning only when key "Cap" is true, which can be checked by function ::FSPDF_Annot_HasCaptionContents.
 *			Valid values for caption position are:<br>
 *			<ul>
 *			<li>Inline: means the caption will be centered inside the line.</li>
 *			<li>Top: means the caption will be on top of the line.</li>
 *			</ul>
 *			Usually, the default value is Inline.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	captionPos	Pointer to a ::FSCRT_BSTR structure to specify value of caption position property. 
 *							Please see "details" description part for more information.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>,<br>
 *			or parameter <i>captionPos</i> or FSCRT_BSTR::str is <b>NULL</b> or the FSCRT_BSTR::len is zero.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if caption position cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetCaptionPosition(FSCRT_ANNOT annot, const FSCRT_BSTR* captionPos);

/**
 * @brief	Set caption offset of a line annotation.
 *
 * @details	Only line annotation can have caption offset property.<br>
 *			Caption offset is the offset of caption from its normal position.
 *			It is meaningful only when key "Cap" is true, which can be checked by function ::FSPDF_Annot_HasCaptionContents.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	offsetx		A float value that specifies the new horizontal offset along the annotation line from its midpoint. <br>
 *							A positive value indicates offset to the right and a negative value indicates offset to the left. 
 * @param[in]	offsety		A float value that specifies the new vertical offset perpendicular to the annotation line. <br>
 *							A positive value indicates a shift up and a negative value indicates a shift down.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if caption offset cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetCaptionOffset(FSCRT_ANNOT annot, FS_FLOAT offsetx, FS_FLOAT offsety);

/**
 * @brief	Set vertices of a polygon or polyline annotation.
 *
 * @details	Only polygon, and polyline annotations can have vertices property. And this property is necessary for polygon and polyline annotation.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	vertices		Pointer to a ::FS_FLOAT object that specifies the new vertices array. This should be valid.<br>
 *								And the count of elements in this array must be a multiple of 2.
 * @param[in]	count			An integer value that specifies the count of elements in new vertices array(parameter <i>vertices</i>) for the annotation.<br>
 *								It must be a multiple of 2.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>vertices</i> is <b>NULL</b>, or <i>count</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if vertices cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetVertices(FSCRT_ANNOT annot, FS_FLOAT* vertices, FS_INT32 count);

/**
 * @brief	Set symbol of a caret annotation.
 *
 * @details	Only caret annotation can have symbol property.<br>
*			A symbol is associated with the caret. Valid values are:<br>
 *			<ul>
 *			<li>P: A new paragraph symbol should be associated with the caret.</li>
 *			<li>None: No symbol should be associated with the caret.</li>
 *			</ul>
 *			Usually, default value is None. Currently SDK can only support to set "None".
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	symbol		Pointer to a ::FSCRT_BSTR structure that specifies value of symbol property.
 *							Please see details description part for more information.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, <br>
 *			or parameter <i>symbol</i> or FSCRT_BSTR::str is <b>NULL</b> or the FSCRT_BSTR::len is zero.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if symbol cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Currently, application should ensure this property has been set valid to newly added caret annotation.
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
FS_RESULT	FSPDF_Annot_SetSymbol(FSCRT_ANNOT annot, const FSCRT_BSTR* symbol);

/**
 * @brief	Set ink list data of an ink annotation.
 *
 * @details	Only ink annotation can have ink list property. And this property is necessary for ink annotation.<br>
 *			InkList is an array of N arrays, each representing a stroked path.
 *			Each array is a series of alternating horizontal and vertical coordinates in PDF page space, 
 *			specifying points along the path.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	pathData	Handle to a <b>FSCRT_PATHDATA</b> object to specify the new path data of ink list property.
 *							In Foxit PDF SDK, the type of first point will be treated as ::FSCRT_POINTTYPE_MOVETO. 
 *							And for the point type of rest points:
 *							<ul>
 *							<li>If the first point type is ::FSCRT_POINTTYPE_LINETO, all the rest will be treated as ::FSCRT_POINTTYPE_LINETO.</li>
 *							<li>If the first point type is ::FSCRT_POINTTYPE_BEZIERTO, all the rest will be treated as ::FSCRT_POINTTYPE_BEZIERTO.</li>
 *							</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>pathData</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if ink list data cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetInkList(FSCRT_ANNOT annot, FSCRT_PATHDATA pathData);

/**
 * @brief	Set attachment of a file attachment annotation.
 *
 * @details	Only file attachment annotation can have attachment property.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	attachment	Pointer to a <b>FSPDF_ATTACHMENT</b> handle to be set to a file attachment annotation.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>attachment</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no attachment property is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if attachment cannot be set because of any other reasons.<br>
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
FS_RESULT	FSPDF_Annot_SetAttachment(FSCRT_ANNOT annot, FSPDF_ATTACHMENT attachment);

/**
 * @brief	Set default appearance of a free text annotation, which can be used in formatting the text.
 *
 * @details	Only free text annotation can have default appearance property. And this property is necessary for free text annotation, 
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	defAppearance	Pointer to a ::FSPDF_DEFAULTAPPEARANCE structure to specify default appearance.<br>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>defAppearance</i> is <b>NULL</b>, 
 *			or some members of <i>defAppearance</i> are invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if default appearance cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_SetDefaultAppearance(FSCRT_ANNOT annot, const FSPDF_DEFAULTAPPEARANCE* defAppearance);

/**
 * @brief	Set icon fit of a widget annotation.
 *
 * @details	Only widget annotation(pushbutton field only) can have icon-fit property in MK dictionary.<br>
 *			The icon fit property belongs to MK dictionary. It specifies how to display the widget annotation's icon within the annotation rectangle. 
 *			If present, the icon fit property applies to all of the annotation's icons (normal, rollover, and alternate).<br>
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	iconFit		Pointer to a ::FSPDF_ANNOTICONFIT structure to specify icon fit.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>iconFit</i> is <b>NULL</b>, 
 *			or some members of <i>iconFit</i> are invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if icon fit cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetIconFit(FSCRT_ANNOT annot, const FSPDF_ANNOTICONFIT* iconFit);

/**
 * @brief	Remove a specified entry in MK dictionary.
 *
 * @details	Only screen and widget annotations can have MK dictionary.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	mkEntry		An integer value used to specify an entry in MK dictionary. 
*							Please refer to macro definitions <b>FSPDF_ANNOT_MKENTRY_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>mkEntry</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no MK dictionary is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if specified entry cannot be removed because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_RemoveMKEntry(FSCRT_ANNOT annot, FS_INT32 mkEntry);

/**
 * @brief	Set rotation in MK dictionary.
 *
 * @details	Only screen and widget annotations can have rotation property in MK dictionary.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	degree		An integer that specifies the new value of rotation entry. The value must be a multiple of 90.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>degree</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if rotation cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetMKRotation(FSCRT_ANNOT annot, FS_INT32 degree);

/**
 * @brief	Set color of specific type in MK dictionary.
 *
 * @details	Only screen and widget annotations can have color property in MK dictionary.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	mkEntry		An integer to specify the type of color entry in MK dictionary. It should be one of the followings:<br>
 *							<ul>
 *							<li>::FSPDF_ANNOT_MKENTRY_BORDERCOLOR</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_BACKGROUNDCOLOR</li>
 *							</ul>
 * @param[in]	color		Pointer to a ::FS_ARGB object that receives color of specific type. Format: 0xAARRGGBB, and alpha value is ignored.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>mkEntry</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if specified color cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetMKColor(FSCRT_ANNOT annot, FS_INT32 mkEntry, FS_ARGB color);

/**
 * @brief	Set caption of a specific type in MK dictionary.
 *
 * @details	Only widget annotation can have caption property in MK dictionary.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	mkEntry		An integer to specify the type of caption entry in MK dictionary. It should be one of the followings:<br>
 *							<ul>
 *							<li>::FSPDF_ANNOT_MKENTRY_NORMALCAPTION</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_ROLLOVERCAPTION</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_DOWNCAPTION</li>
 *							</ul>
 * @param[in]	caption		Pointer to a ::FSCRT_BSTR structure to specify the new caption. It can be <b>NULL</b> or empty. 
 *							When it's valid, it should be a valid UTF-8 string.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>caption</i> is <b>NULL</b>, or <i>mkEntry</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>caption</i> is not in UTF-8 format if it's valid.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if specified caption cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetMKCaption(FSCRT_ANNOT annot, FS_INT32 mkEntry, const FSCRT_BSTR* caption);

/**
 * @brief	Set a bitmap to a specific icon entry in MK dictionary.
 *
 * @details	Only widget annotation can have icon property in MK dictionary.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	mkEntry		An integer to specify the type of icon entry in MK dictionary. It should be one of the followings:<br>
 *							<ul>
 *							<li>::FSPDF_ANNOT_MKENTRY_NORMALICON</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_ROLLOVERICON</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_DOWNICON</li>
 *							</ul>
 * @param[in]	bitmap		Pointer to a <b>FSCRT_BITMAP</b> handle which specifies the new icon bitmap.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>bitmap</i> is <b>NULL</b>, or <i>mkEntry</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if specified icon bitmap cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetMKIconBitmap(FSCRT_ANNOT annot, FS_INT32 mkEntry, FSCRT_BITMAP bitmap);

/**
 * @brief	Set an image to a specific icon entry in MK dictionary.
 *
 * @details	Only widget annotation can have icon property in MK dictionary.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	mkEntry		An integer to specify the type of icon entry in MK dictionary. It should be one of the followings:<br>
 *							<ul>
 *							<li>::FSPDF_ANNOT_MKENTRY_NORMALICON</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_ROLLOVERICON</li>
 *							<li>::FSPDF_ANNOT_MKENTRY_DOWNICON</li>
 *							</ul>
 * @param[in]	image		Pointer to a <b>FSCRT_IMAGE</b> handle which specifies the new icon image.
 *							This image handle can be created by function ::FSCRT_Image_LoadFromFile.
 *							And before use it, applicaion should also call function ::FSCRT_Image_LoadFrame 
 *							to make sure which frame of the image will be used to set MK icon.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>image</i> is <b>NULL</b>, or <i>mkEntry</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if specified icon image cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_SetMKIconImage(FSCRT_ANNOT annot, FS_INT32 mkEntry, FSCRT_IMAGE image);

#ifndef _FSPDF_DEF_ICONPROVIDER_
#define _FSPDF_DEF_ICONPROVIDER_
/** 
 * @brief	Structure for the provider of alternate icons. 
 */
typedef struct _FSPDF_ICONPROVIDER
{
	/** @brief	The size of the data structure. It must be set to <I>sizeof</I>(::FSPDF_ICONPROVIDER). */
	FS_DWORD	lStructSize;

	/** @brief	A user pointer, used by the application. */
	FS_LPVOID	clientData;

	/**
	 * @brief	A callback function can be called when to release everything.
	 *
	 * @param[in]	clientData			The user-supplied data.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
	 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT			(*Release)(FS_LPVOID clientData);

	/**
	 * @brief	A callback function retrieves identity info of icon provider.
	 *
	 * @param[in]	clientData		The user-supplied data.
	 * @param[out]	str				Pointer to a ::FSCRT_BSTR structure that receives a UTF-8 string which indicates the identity name string of icon provider.
	 * @param[out]	ver				Pointer to a ::FS_DWORD object that receives the version number of icon provider.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
	 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	This callback function should return valid identity name string and version number.
	 */
	FS_RESULT			(*GetProviderID)(FS_LPVOID clientData, FSCRT_BSTR* str, FS_DWORD* ver);
	
	/**
	 * @brief	A callback function determines whether icon provider supports an icon.
	 *
	 * @param[in]	clientData		The user-supplied data.
	 * @param[in]	iconType		Pointer to a ::FSCRT_BSTR structure that specifies a UTF-8 string which indicates the type string of icon.
	 *								Support types: "Text", "FileAttachment", and "Stamp".
	 * @param[in]	iconID			Pointer to a ::FSCRT_BSTR structure that specifies a UTF-8 string which indicates the identity string of icon.
	 *								Please refer to note part for more information.
	 * @param[out]	hasIcon			Whether an icon is provided.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if application supports this icon.<br>
	 *			::FSCRT_ERRCODE_ERROR if application cannot support this icon.<br>
	 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	For <b>Text</b> annotation, valid icon identity strings should be one of macro definitions <b>FSPDF_ANNOT_ICONNAME_TEXT_XXX</b>.<br>
	 *			For <b>FileAttachment</b> annotation, valid icon identity strings should be one of macro definitions <b>FSPDF_ANNOT_ICONNAME_FILEATTACH_XXX</b>.<br>
	 *			For <b>Stamp</b> annotation, valid icon identity strings should be one of macro definitions <b>FSPDF_ANNOT_ICONNAME_STAMP_XXX</b>.<br>
	 */
	FS_RESULT			(*HasIcon)(FS_LPVOID clientData, const FSCRT_BSTR* iconType, const FSCRT_BSTR* iconID, FS_BOOL* hasIcon);
	
	/**
	 * @brief	A callback function determines whether supports to change icon color.
	 *
	 * @param[in]	clientData			The user-supplied data.
	 * @param[in]	iconType			Pointer to a ::FSCRT_BSTR structure that specifies a UTF-8 string which indicates the type string of icon.
	 *									Support types: "Text", "FileAttachment", and "Stamp".
	 * @param[in]	iconID				Pointer to a ::FSCRT_BSTR structure that specifies a UTF-8 string which indicates the identity string of icon.
	 *									Please refer to "note" description part in callback function FSPDF_ICONPROVIDER::HasIcon for more information.
	 * @param[out]	canChange			Pointer to a ::FS_BOOL object that receives a boolean value which indicates whether the color of icon could be changed or not.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if application supports to change color.<br>
	 *			::FSCRT_ERRCODE_ERROR if application cannot support to change color.<br>
	 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT			(*CanChangeColor)(FS_LPVOID clientData, const FSCRT_BSTR* iconType, const FSCRT_BSTR* iconID, FS_BOOL* canChange);
	
	/**
	 * @brief	A callback function retrieves icon as PDF page contents.
	 *
	 * @param[in]	clientData			The user-supplied data.
	 * @param[in]	iconType			Pointer to a ::FSCRT_BSTR structure that specifies a UTF-8 string which indicates the type string of icon.
	 *									Support types: "Text", "FileAttachment", and "Stamp".
	 * @param[in]	iconID				Pointer to a ::FSCRT_BSTR structure that specifies a UTF-8 string which indicates the identity string of icon.
	 *									Please refer to "note" description part in callback function FSPDF_ICONPROVIDER::HasIcon for more information.
	 * @param[in]	color				Color if icon needs. Format: 0xAARRGGBB and alpha value is ignored.
	 * @param[out]	page				Pointer to a <b>FSCRT_PAGE</b> handle that receives a page object.
	 *									If there's any error, it will be <b>NULL</b>.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
	 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT			(*GetIcon)(FS_LPVOID clientData, const FSCRT_BSTR* iconType, const FSCRT_BSTR* iconID, FS_ARGB color, FSCRT_PAGE* page);

	/**
	 * @brief	A callback function sets shading colors if an icon supports shading.
	 *			Currently, we support only Type-2 shading settings with two color values.
	 *
	 * @param[in]	clientData			The user-supplied data.
	 * @param[in]	iconType			Pointer to a ::FSCRT_BSTR structure that specifies a UTF-8 string which indicates the type string of icon.
	 *									Support types: "Text", "FileAttachment", and "Stamp".
	 * @param[in]	iconID				Pointer to a ::FSCRT_BSTR structure that specifies a UTF-8 string which indicates the identity string of icon.
	 *									Please refer to "note" description part in callback function FSPDF_ICONPROVIDER::HasIcon for more information.
	 * @param[in]	refColor			referenced color to set, alpha component is ignored.
	 * @param[in]	shadingIndex		Index color of shading. If shading colors are more than one, this function will be called multiple times.
	 * @param[out]	c1					Pointer to a ::FS_ARGB object that receives the first color value of shading.
	 * @param[out]	c2					Pointer to a ::FS_ARGB object that receives the second color value of shading.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if runs well.<br>
	 *			::FSCRT_ERRCODE_ERROR if any error occurs.<br>
	 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT			(*SetShadingColor)(FS_LPVOID clientData, const FSCRT_BSTR* iconType, const FSCRT_BSTR* iconID, FS_ARGB refColor, 
									   FS_INT32 shadingIndex, FS_ARGB* c1, FS_ARGB* c2);

	/**
	 * @brief	A callback function retrieves icon size when display, in device size(pixel normally).
	 *
	 * @param[in]	clientData			The user-supplied data.
	 * @param[in]	iconType			Pointer to a ::FSCRT_BSTR structure that specifies a UTF-8 string which indicates the type string of icon.
	 *									Support types: "Text", "FileAttachment", and "Stamp".
	 * @param[in]	iconID				Pointer to a ::FSCRT_BSTR structure that specifies a UTF-8 string which indicates the identity string of icon.
	 *									Please refer to "note" description part in callback function FSPDF_ICONPROVIDER::HasIcon for more information.
	 * @param[out]	width				Pointer to a ::FS_FLOAT object that receives the width of icon.
	 * @param[out]	height				Pointer to a ::FS_FLOAT object that receives the height of icon.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
	 *			::FSCRT_ERRCODE_ERROR if any error occurs.<br>
	 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT			(*GetDisplaySize)(FS_LPVOID clientData, const FSCRT_BSTR* iconType, const FSCRT_BSTR* iconID, FS_FLOAT* width, FS_FLOAT* height);

}FSPDF_ICONPROVIDER;
#endif //_FSPDF_DEF_ICONPROVIDER_

/**
 * @brief	Set icon provider to SDK management.
 *
 * @details	For annotation type "Text", "FileAttachment", "Sound"(not support now) and "Stamp", they appear on the page in some distinctive icons.<br>
 *			For annotation with type "Text" and "FileAttachment", Foxit PDF SDK has defined their default icon appearance. 
 *			For stamp annotation, Foxit PDF SDK doesn't define default icon appearance currently.
 *			If you want to use private application icon appearance, this function should be called to set an icon provider.
 *
 * @param[in]	iconProvider		Pointer to a ::FSPDF_ICONPROVIDER structure.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS means success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>iconProvider</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set icon provider because of any other reason.<br>
 *			For more definitions please see macro definitions <b>FS_ERR_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_SetIconProvider(FSPDF_ICONPROVIDER* iconProvider);

/**
 * @brief	Set image to stamp annotation.
 *
 * @details	This function can only be used for stamp annotation.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object. This should be a stamp annotation.
 * @param[in]	image		Handle to a <b>FSCRT_IMAGE</b> object which is an image object to be set to stamp annotation.<br>
 *							This object cannot be released until funcion ::FSPDF_Annot_ResetAppearance has been called for this stamp anntoation.
 *							And application should call function ::FSCRT_Image_Release to release this <b>FSCRT_IMAGE</b> object.
 * @param[in]	compress	Compress algorithm type used to compress image data. Currently, it only supports 2 valid value:<br>
 *							<ul>
 *							<li>0: no compress.</li>
 *							<li>1: do default compress.</li>
 *							</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS means success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>image</i> is <b>NULL</b>, or <i>compress</i> is out of valid range.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if annotation type of parameter <i>annot</i> is not Stamp.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if stamp cannot be set because of any other reason.<br>
 *			For more definitions please see macro definitions <b>FS_ERR_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Annot_SetStamp(FSCRT_ANNOT annot, FSCRT_IMAGE image, FS_INT32 compress);

/**
 * @brief	Set bitmap to stamp annotation.
 *
 * @details	This function can only be used for stamp annotation.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object. This should be a stamp annotation.
 * @param[in]	bitmap		Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object to be set to stamp annotation.<br>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS means success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>bitmap</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if annotation type of parameter <i>annot</i> is not "Stamp".<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if stamp cannot be set because of any other reason.<br>
 *			For more definitions please see macro definitions <b>FS_ERR_XXX</b>.
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
FS_RESULT FSPDF_Annot_SetStampWithBitmap(FSCRT_ANNOT annot, FSCRT_BITMAP bitmap);

/*******************************************************************************/
/* Markup controls                                                             */
/*******************************************************************************/
/**
 * @brief	Add a specific state to a markup annotation.
 *
 * @details	This function only supports markup annotations.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	stateModel	An integer value that specifies the state model. 
 *							Please refer to macro definitions <b>FSPDF_ANNOTSTATEMODEL_XXX</b> and this should be one of these macros.
 * @param[in]	state		An integer value that specifies the state. 
 *							Please refer to macro definitions <b>FSPDF_ANNOTSTATE_XXX</b> and this should be one of these macros.
 * @param[out]	stateAnnot	Pointer to a <b>FSCRT_ANNOT</b> handle which receive the state annotation.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>stateAnnot</i> is <b>NULL</b>, 
 *			or <i>stateModel</i>, <i>state</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the specified state annotation cannot be added because of any other reason.<br>
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
FS_RESULT 	FSPDF_Annot_AddState(FSCRT_ANNOT annot, FS_INT32 stateModel, FS_INT32 state, FSCRT_ANNOT* stateAnnot);

/**
 * @brief	Set state model and state out of a state annotation.
 *
 * @details	This function only supports markup annotations.
 *
 * @param[in]	stateAnnot	Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	stateModel	An integer value that specifies the state model. 
 *							Please refer to macro definitions <b>FSPDF_ANNOTSTATEMODEL_XXX</b> and this should be one of these macros.
 * @param[in]	state		An integer value that specifies the state. 
 *							Please refer to macro definitions <b>FSPDF_ANNOTSTATE_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>stateAnnot</i> is <b>NULL</b>, or <i>stateModel</i>, <i>state</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 *			::FSCRT_ERRCODE_ERROR if the state model and state cannot be set because of any other reason.<br>
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
FS_RESULT 	FSPDF_Annot_SetState(FSCRT_ANNOT stateAnnot, FS_INT32 stateModel, FS_INT32 state);

/**
 * @brief	Remove all the state annotations associated with an annotation.
 *
 * @details	This function only supports markup annotations.
 *
 * @param[in]	annot	Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if all the state annotations cannot be removed because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_RemoveAllStates(FSCRT_ANNOT annot);

/**
 * @brief	Group all the input annotations.
 *
 * @details	This function only supports markup annotations.
 *
 * @param[in]	annots			Pointer to a <b>FSCRT_ANNOT</b> handle which is an annotation array. 
 *								This array should contain at least 2 elements.
 * @param[in]	count			Size of the annotation array.
 * @param[in]	headerIndex		Index of an annotation in the annotation array. Annotation with this index will become the group header. 
 *								Range: 0 to (<i>count</i>-1).
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annots</i> is <b>NULL</b>, or <i>count</i>, <i>headerIndex</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 *			::FSCRT_ERRCODE_ERROR if input annotation is not a markup annotation or all the annotations cannot be grouped because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annots</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Annot_SetGroup(FSCRT_ANNOT* annots, FS_INT32 count, FS_INT32 headerIndex);

/**
 * @brief	Ungroup an annotation from the group it belongs to.
 *
 * @details	This function only supports markup annotations.
 *
 * @param[in]	annot 			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if input annotation is not a markup annotation or annotation cannot be un-grouped because of any other reason.<br>
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
FS_RESULT 	FSPDF_Annot_Ungroup(FSCRT_ANNOT annot);

/**
 * @brief	Insert a new empty reply with a specified index to a markup annotation.
 *
 * @details	This function only supports markup annotations. Currently, this function only support to insert reply to the last.
 *			Parameter <i>index</i> is reserved and should be -1.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	index			(Reserved and no effect currently. It should be -1 and new reply will be inserted to the last.)<br>
 *								Index of the reply annotations. Range: 0 to (replycount-1). <i>replycount</i> is returned by function ::FSPDF_Annot_CountReplies.<br>
 *								If it's out of the range, the new reply will be inserted to the last.
 * @param[out]	replyAnnot		Pointer to a <b>FSCRT_ANNOT</b> handle that receives the new reply annotation.<br>
 *								Application can call other annotation related functions to set this new reply annotation.<br>
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> or <i>replyAnnot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if a reply cannot be inserted because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_InsertReply(FSCRT_ANNOT annot, FS_INT32 index, FSCRT_ANNOT* replyAnnot);

/**
 * @brief	Remove a reply with specified index to a markup annotation.
 *
 * @details	This function only supports markup annotations.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	index			Index of the reply annotations to be removed. Range: 0 to (replycount-1). 
 *								<i>replycount</i> is returned by function ::FSPDF_Annot_CountReplies.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the reply cannot be removed because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_RemoveReply(FSCRT_ANNOT annot, FS_INT32 index);

/**
 * @brief	Remove all the replies of a markup annotation.
 *
 * @details	This function only supports markup annotations.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if all replies cannot be removed because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_RemoveAllReplies(FSCRT_ANNOT annot);

/*******************************************************************************/
/* Annotation trigger actions                                                  */
/*******************************************************************************/
/**
 * @brief	Set action data of specified index associated with an annotation.
 *
 * @details	Only link , screen and widget annotations can have action.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	trigger			The trigger of action. 
 *								Please refer to macro definition <b>FSPDF_TRIGGER_ANNOT_XXX</b> and this should be one of these macros.
 * @param[in]	index			Index of actions. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Annot_CountActions.
 * @param[in]	actionData		Pointer to a ::FSPDF_ACTIONDATA structure which specifies the action data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>actionData</i> is <b>NULL</b>, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or no action is found.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if action data cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_SetAction(FSCRT_ANNOT annot, FS_INT32 trigger, FS_INT32 index, const FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Insert an action of specified index associated with an annotation.
 *
 * @details	Only link , screen and widget annotations can have action.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	trigger			Trigger of action. 
 *								Please refer to macro definition <b>FSPDF_TRIGGER_ANNOT_XXX</b> and this should be one of these macros.
 * @param[in]	index			Index of actions. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Annot_CountActions.<br>
 *								If it's out of the range, parameter <i>actionData</i> will be inserted to the last.
 * @param[in]	actionData		Pointer to a ::FSPDF_ACTIONDATA structure which specifies the action data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, or <i>actionData</i> is <b>NULL</b>, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 *			::FSCRT_ERRCODE_ERROR if the action cannot be inserted because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_InsertAction(FSCRT_ANNOT annot, FS_INT32 trigger, FS_INT32 index, const FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Remove an action of specified index associated with an annotation.
 *
 * @details	Only link , screen and widget annotations can have action.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	trigger			Trigger of action. 
 *								Please refer to macro definition <b>FSPDF_TRIGGER_ANNOT_XXX</b> and this should be one of these macros.
 * @param[in]	index			Index of actions. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Annot_CountActions.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or no action is found.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the action cannot be removed because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_RemoveAction(FSCRT_ANNOT annot, FS_INT32 trigger, FS_INT32 index);

/**
 * @brief	Remove all the actions associated with an annotation.
 *
 * @details	Only link , screen and widget annotations can have action.
 *
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 * @param[in]	trigger			Trigger of action. 
 *								Please refer to macro definition <b>FSPDF_TRIGGER_ANNOT_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no trigger action is found. <br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if all actions cannot be removed because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
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
FS_RESULT	FSPDF_Annot_RemoveAllActions(FSCRT_ANNOT annot, FS_INT32 trigger);

/*******************************************************************************/
/* Reset annotation                                                          */
/*******************************************************************************/
/**
 * @brief	Reset(regenerate) appearance of an annotation.
 *
 * @details	This function can support all types defined in macro definitions <b>FSPDF_ANNOTTYPE_XXX</b>, 
 *			except PSInk, 3D, PrinterMark, TrapNet, sound, movie, screen, watermark, and signature(a subtype of widget annot).<br>
 *			For watermark annotation, user is suggested to use functions in \ref FPDFWATERMARK "PDF Watermark" module for most operations of watermark.<br>
 *			Foxit PDF SDK assume that a widget annot should be a form field's control. So, for widget annotation, 
 *			application should load form module by function ::FSPDF_Form_Load first. If not, this function will return ::FSCRT_ERRCODE_UNKNOWNSTATE.
 *			For a signature field, we suggest that use function ::FSPDF_Signature_ResetAppearance to handle it.
 *			 
 * @param[in]	annot	Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_UNSUPPORTED if type of input annotation isn't currently supported.<br>
 *			::FSCRT_ERRCODE_UNKNOWNSTATE if some necessary property of parameter <i>annot</i> doesn't be set correctly, or form module hasn't been loaded for widget annot.
 *			For annotation's property, please refer to comment of property relative functions.<br>
 *			::FSCRT_ERRCODE_ERROR if the appearance cannot be reset because of any other reason.<br>
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
FS_RESULT	FSPDF_Annot_ResetAppearance(FSCRT_ANNOT annot);
    
/**
 * @brief	Serialize the annotation.
 *
 @ @details	This function can serialize the specified annotation data into memory and then call function ::FSPDF_Archive_DeserializeAnnot to de-serialize 
 *			annotations to any other PDF pages to recover the annotations into that page.
 *
 * @param[in]	archive			Handle to a <b>FSCRT_ARCHIVE</b> object which is an annotation object. This should be returned by function ::FSCRT_Archive_Create.
 *								Call function ::FSCRT_Archive_Release to release this handle when no need to use it any more.
 * @param[in]	page			Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	annot			Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> or <i>annot</i> is not a relative type of PDF.<br>
 *			::FSCRT_ERRCODE_ERROR if the annotation cannot be serialized because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.<br>
 *
 * @attention	<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>archive</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Archive_SerializeAnnot(FSCRT_ARCHIVE archive, FSCRT_PAGE page,  FSCRT_ANNOT annot);

/**
 * @brief	De-serialize the annotation.
 *
 * @details	This function can de-serialize the serialized information of annotations' data into the specified PDF page.
 *			Currently, this function doesn't support to de-serialize annotations of following types: 
 *			Watermark, 3D, PrinterMark, TrapNet, Sound, Movie, Screen, PSInk.<br>
 *			This function should be called after function ::FSPDF_Archive_SerializeAnnot.
 *
 * @param[in]	archive			Handle to a <b>FSCRT_ARCHIVE</b> object which is an annotation object.
 *								Call function ::FSCRT_Archive_Release to release this handle when no need to use it any more.
 * @param[in]	page			Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[out]	annot			Pointer to a <b>FSCRT_ANNOT</b> handle that receives the annotation as the deseralized result.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>annot</i>, <i>archive</i> or <i>page</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or accessing annotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_UNSUPPORTED if type of input annotation isn't currently supported.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the annotation cannot be de-serialized because of any other reason, or this function is called repeatedly with same <i>archive</i>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	<ul>
 *			<li>This function only allow to be called once for a <b>FSCRT_ARCHIVE</b> object.</li>
 *			<li>For widget annotation, user is strongly suggested to use functions in \ref FPDFFORM "PDF Form" module for widget related to form object.</li>
 *			</ul>
 *
 * @attention	<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>archive</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Archive_DeserializeAnnot(FSCRT_ARCHIVE archive, FSCRT_PAGE page, FSCRT_ANNOT* annot);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFANNOT */

#endif /* _FSPDF_ANNOT_W_H_ */

