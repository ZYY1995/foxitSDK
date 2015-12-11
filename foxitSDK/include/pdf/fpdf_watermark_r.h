/**
 * Copyright (C) 2003-2015, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It's not allowed to 
 * distribute any parts of Foxit PDF SDK to third party or public without permission unless an agreement 
 * is signed between Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file	fpdf_watermark_r.h
 * @brief	Header file for \ref FPDFWATERMARK "PDF Watermark" module of Foxit PDF SDK.
 * @details	This header file provides access to PDF watermark related functionality.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Get the watermark count in a PDF page. </li>
 *			<li>2. Retrieve watermark size. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Annotation Add-on</b> explicitly.
 */

#ifndef _FSPDF_WATERMARK_R_H_
#define _FSPDF_WATERMARK_R_H_

/** 
 * @defgroup	FPDFWATERMARK PDF Watermark 
 * @brief		Definitions for PDF watermarks.<br>
 *				Definitions and functions in this module are included in fpdf_watermark_r.h and fpdf_watermark_w.h.<br>
 *				Module: PDFWatermark<br>
 *				License Identifier: PDFWatermark/All<br>
 *				Available License Right: Reading/Writing<br>
 *				For License Right <b>Reading</b>, see fpdf_watermark_r.h.<br>
 *				For License Right <b>Writing</b>, see fpdf_watermark_w.h.<br>
 * @details		This module contains the following features:<br>
 *				<ul>
 *				<li>1. Watermark:
 *					<ul>
 *					<li>a. Count watermarks in a specific page.</li>
 *					<li>b. Get size from a specific watermark.</li> 
 *					<li>c. Create a watermark from a text, image, bitmap or PDF page, retrieve watermark size, insert or remove a watermark.</li>
 *					<li>d. A watermark can be created as the content of a page directly, or be created as an annotation in a page.
 *						   If create a watermark from a text, call the function::FSPDF_Watermark_CreateFromText.
 *						   If create a watermark from an image, call the function ::FSPDF_Watermark_CreateFromImage.
 *						   If create a watermark from a bitmap, call the function ::FSPDF_Watermark_CreateFromBitmap. 
 *						   If create a watermark from a PDF page, call the function ::FSPDF_Watermark_CreateFromPage.</li>
 *					<li>e. Reference: it's described in section 8.4.5 of PDF Reference 1.7 about watermark annotation.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Definitions for watermark                                                   */
/*******************************************************************************/
#ifndef _FSPDF_DEF_HANDLE_WATERMARK_
#define _FSPDF_DEF_HANDLE_WATERMARK_

/** @brief	Handle type to PDF watermark. */
FSCRT_DEFINEHANDLE(FSPDF_WATERMARK);

#endif /* _FSPDF_DEF_HANDLE_WATERMARK_ */

/**
 * @brief	Get count of watermarks in a specific page and it doesn't include the SDK trial watermark.
 *
 * @details	The page content should have been already parsed. And there's no need to call function ::FSPDF_Page_LoadAnnots at first 
 *			for watermarks which are annotations.
 *
 * @param[in]	page	Handle to a <b>FSCRT_PAGE</b> which is a PDF page object.
 * @param[out]	count	Pointer to a ::FS_INT32 object that receives count of watermarks.
 *						If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, or <i>count</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter<i>page</i> is not parsed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if count cannot be obtained because of any other reason.<br>
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
FS_RESULT	FSPDF_Watermark_GetCount(FSCRT_PAGE page, FS_INT32* count);

/**
 * @brief	Retrieve the size (width and height) of a specific watermark.
 *
 * @param[in]	watermark		Handle to <b>FSPDF_WATERMARK</b> object which is a water mark object.
 * @param[out]	width			Pointer to a ::FS_FLOAT object that retrieves the width of watermark.
 * @param[out]	height			Pointer to a ::FS_FLOAT object that retrieves the height of watermark.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>watermark</i>, <i>width</i>, or <i>height</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li> For <i>watermark</i> created by function ::FSPDF_Watermark_CreateFromText, ::FSPDF_Watermark_CreateFromBitmap, ::FSPDF_Watermark_CreateFromImage:
 *					<ul>
 *					<li>This function is long-term recoverable.</li>
 *					<li><i>watermark</i> is long-term recoverable.</li>
 *					</ul>
 *				<li> For <i>watermark</i> created by function ::FSPDF_Watermark_CreateFromPage: 
 *					<ul>
 *					<li>This function is long-term unrecoverable.</li>
 *					<li><i>watermark</i> is long-term partially recoverable.</li>
 *					</ul>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Watermark_GetSize(FSPDF_WATERMARK watermark, FS_FLOAT* width, FS_FLOAT* height);


#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFWATERMARK */

#endif /* _FSPDF_WATERMARK_R_H_ */