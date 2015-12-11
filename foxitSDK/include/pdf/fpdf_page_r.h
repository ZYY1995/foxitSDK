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
 * @file	fpdf_page_r.h
 * @brief	Header file for \ref FPDFPAGE "PDF Page" module of Foxit PDF SDK.
 * @details	This header file provides direct access to PDF page.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Parse PDF page contents. </li>
 *			<li>2. Access PDF page attributes. </li>
 *			<li>3. Supports for page trigger actions. </li>
 *			<li>4. PDF page matrix process. </li>
 *			<li>5. Calculate page margin and render PDF page. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> explicitly.
 */

#ifndef _FSPDF_PAGE_R_H_
#define _FSPDF_PAGE_R_H_

/** 
 * @defgroup	FPDFPAGE PDF Page
 * @brief		Definitions for access to PDF page.<br>
 *				Definitions and functions in this module are included in fpdf_page_r.h and fpdf_page_w.h.<br>
 *				Module: PDFPage<br>
 *				License Identifier: PDFPage/All<br>
 *				Available License Right: Reading/Writing<br>
 *				For License Right <b>Reading</b>, see fpdf_page_r.h.<br>
 *				For License Right <b>Writing</b>, see fpdf_page_w.h.
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. PDF page:
 *					<ul>
 *					<li>a. Parse page contents, and clear resources occupied by page.</li>
 *					<li>b. Before rendering page or accessing page objects, a page should be parsed at first.
 *						   When call function ::FSPDF_Page_Clear to clear a page, all page contents and relative resources will be released.</li>
 *					<li>c. Note: a page handle will not be invalid until the current document is closed.</li>
 *					</ul>
 *				</li>
 *				<li>2. Page attributes: get or set page index, page size, rotation and page boundaries.</li>
 *				<li>3. Page trigger actions:
 *					<ul>
 *					<li>a. Enumerate trigger actions of PDF page object, modify or remove trigger actions.</li>
 *					<li>b. Note: Foxit PDF SDK doesn't contain functions to execute actions. In a viewer or reader, action should be executed by application.</li>
 *					<li>c. Reference: section 8.5.2 in PDF Reference 1.7 describes trigger actions.</li>
 *					</ul>
 *				</li>
 *				<li>4. Page matrix:
 *					<ul>
 *					<li>a. Get page transformation matrix between PDF page coordinates and rendering device coordinates.</li>
 *					<li>b. PDF page has private coordinates which Y-axis is upward but most types of rendering devices have downward Y-axis.
 *						   Besides, some other metrics are different as well, such as DPI.<br>
 *						   Transformation matrix is used to output page contents to accurate position and size in rendering devices.
 *						   Caller can call functions for matrix defined in fs_base_r.h header file to do transformations for points or rectangles.</li>
 *					</ul>
 *				</li>
 *				<li>5. Page rendering:
 *					<ul>
 *					<li>a. Calculate bounding box of page contents by analyzing page contents, and render page contents as a progressive process.</li>
 *					<li>b. Bounding box of page contents may be not clear and different to trimming box, for example, a page is a scanned image.</li>
 *					<li>c. Reference: section 10.10.1 in PDF Reference 1.7 describes information about page boundaries.</li>
 *					</ul>
 *				</li>
 *				<li>6. Page editing:
 *					<ul>
 *					<li>a. Create a new page, delete a page, and flatten page.</li>
 *					<li>b. Flattening process is to merge contents of annotations into page contents.
 *						   Annotations separate from page contents, and they are for interaction purpose.</li>
 *					</ul>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************/
/* Macros definition                                                            */
/*                                                                              */
/* Page parsing flags, page rotation                                            */
/********************************************************************************/
#ifndef _FSPDF_DEF_MACRO_PAGEPARSEFLAG_
#define _FSPDF_DEF_MACRO_PAGEPARSEFLAG_
/**
 * @name	Macro Definitions for PDF Page Parsing Flags
 * @note	There are two PDF page parsing modes: one is normal, and the other one is for text only. Non-text objects in page will be omitted.
 */
/**@{*/

/** @brief	PDF page parsing flag for normal mode. */
#define FSPDF_PAGEPARSEFLAG_NORMAL			0
/** @brief	PDF page parsing flag for text-only mode. */
#define FSPDF_PAGEPARSEFLAG_TEXTONLY		1

/**@}*/
#endif /* _FSPDF_DEF_MACRO_PAGEPARSEFLAG_ */

/*******************************************************************************/
/* Parse and clear PDF page                                                    */
/*******************************************************************************/
/**
 * @brief	Start parsing a PDF page.
 *
 * @details	It will take a long time to parse a page with large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass <i>parseProgress</i> to function ::FSCRT_Progress_Continue to continue parsing in steps, 
 *			Call function ::FSCRT_Progress_Release to destroy <i>parseProgress</i> object if parsing process is done.<br>
 * 			All page content objects will be loaded after page is parsed.
 * 
 * @param[in]	page			Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	flag			Page parsing mode: ::FSPDF_PAGEPARSEFLAG_NORMAL for normal mode, or ::FSPDF_PAGEPARSEFLAG_TEXTONLY for text-only mode.
 * @param[out]	parseProgress	Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_FINISHED if parameter <i>page</i> has been parsed over.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>parseProgress</i> is a <b>NULL</b> pointer, or parameter <i>flag</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to start parsing a PDF page for any other reason.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	To execute any page content related process, page should be parsed at first, 
 *			for example, call function ::FSPDF_Page_CalcContentBBox to get content rect, call function ::FSPDF_RenderContext_StartPage to render page, or call page objects accessing functions.<br>
 * 			It's very important to call function ::FSPDF_Page_Clear to release all page content objects to save memory if page contents are unnecessary any more.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>parseProgress</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Page_StartParse(FSCRT_PAGE page, FS_DWORD flag, FSCRT_PROGRESS* parseProgress);

/**
 * @brief	Determine whether <i>page</i> has been parsed or not.
 * 
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[out]	isParsed	Pointer to a ::FS_BOOL object that receives the current page parsing state: 
 *							<ul>
 *							<li><b>TRUE</b>: parameter <i>page</i> has been parsed.</li>
 *							<li><b>FALSE</b>: parameter <i>page</i> hasn't been parsed.</li>.
 *							</ul>
 *							If there's any error, it will be set <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>isParsed</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Page_IsParsed(FSCRT_PAGE page, FS_BOOL* isParsed);

/**
 * @brief	Release all page contents and relative resources.
 * 
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to release all page contents and relative resources for any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	Call this function to release page content objects and shared resources to save memory.<br>
 * 			Clearing parameter <i>page</i> will not destroy page object, <i>page</i> object can be used again.
 *			And if it is reused again, call the clear function again.
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
FS_RESULT	FSPDF_Page_Clear(FSCRT_PAGE page);

/*******************************************************************************/
/* Access PDF page attributes                                                  */
/*******************************************************************************/
/**
 * @brief	Get page index.
 * 
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[out]	index		Pointer to a ::FS_INT32 object that receives page index which starts from 0.
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>index</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
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
FS_RESULT	FSPDF_Page_GetIndex(FSCRT_PAGE page, FS_INT32* index);

/**
 * @brief	Get page size.
 * 
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[out]	width		Pointer to a ::FS_FLOAT object that receives page width, and unit is 1/72 inch.
 *							If there's any error, it will be set 0.
 * @param[out]	height		Pointer to a ::FS_FLOAT object that receives page height, and unit is 1/72 inch.
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>width</i> or <i>height</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
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
FS_RESULT	FSPDF_Page_GetSize(FSCRT_PAGE page, FS_FLOAT* width, FS_FLOAT* height);

/**
 * @brief	Get page rotation.
 *
 * @details	Page size is the size of PDF page when value of "/Rotate" in page dictionary is 0.
 * 
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[out]	rotation	Pointer to a ::FS_INT32 object that receives page rotation state. 
 *							Please refer to macro definitions <b>FSCRT_PAGEROTATION_XXX</b> and this should be one of these macros.<br>
 *							Default: FSCRT_PAGEROTATION_0.<br>
 *							If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>rotation</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get page rotation for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
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
FS_RESULT	FSPDF_Page_GetRotation(FSCRT_PAGE page, FS_INT32* rotation);

/**
 * @brief	Get page boundary which is a rectangle type value.
 * 
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	boxType		Page boundary type to a ::FS_INT32 value. 
 *							Please refer to macro definitions <b>FSPDF_PAGEBOX_XXX</b> and this should be one of these macros.
 * @param[out]	pageBox		Pointer to a ::FSCRT_RECTF structure that receives a rectangle value.
 *							If there's any error, it will be set [0 0 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>pageBox</i> is a <b>NULL</b> pointer, or <i>boxType</i> is invalid.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if no suitable page boundary can be found.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get page boundary for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	In PDF, coordinates of page is upward to Y-axis and rightward to X-axis, so left is less than right and top is greater than bottom.<br>
 * 			The location of origin of coordinate is at the corner of bottom-left of page, and page unit is 1/72 inch.
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
FS_RESULT	FSPDF_Page_GetBox(FSCRT_PAGE page, FS_INT32 boxType, FSCRT_RECTF* pageBox);

/**
 * @brief	Get the PDF page dictionary object.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[out]	dictionary	Pointer to a <b>FSPDF_OBJECT</b> handle that receives the page dictionary object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>dictionary</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if the dictionary object of PDF page cannot be obtained for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. 
 *				Do not call it for the same objects under multi-threaded environment;otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Page_GetDict(FSCRT_PAGE page, FSPDF_OBJECT* dictionary);

/**
 * @brief	Estimate the size of PDF page content.
 *
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[out]	contentSize	Pointer to a ::FS_DWORD object to receive the content size. If there's any error, it will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>contentSize</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to estimate size of page content for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
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
FS_RESULT	FSPDF_Page_EstimateContentSize(FSCRT_PAGE page, FS_DWORD* contentSize);

/**
 * @brief	Check whether a PDF page has transparency.
 * 
 * @param[in]	page			Handle to a valid <b>FSCRT_PAGE</b> object. It should be a valid handle of PDF page that has been parsed.
 * @param[out]  hasTransparency	Pointer to a ::FS_BOOL object that receives a boolean value which indicates whether <i>page</i> has transparency: 
 *								<ul>
 *								<li><b>TRUE</b>: parameter <i>page</i> has transparency.</li>
 *								<li><b>FALSE</b>: parameter <i>page</i> has no transparency.</li>.
 *								</ul>
 *								If there's any error, it will be set <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>hasTransparency</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if parameter <i>page</i> hasn't been parsed.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to check whether a PDF page has transparency for any other reason.<br>
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
FS_RESULT	FSPDF_Page_HasTransparency(FSCRT_PAGE page, FS_BOOL* hasTransparency);

/********************************************************************************/
/* Page trigger actions                                                         */
/********************************************************************************/
/**
 * @brief	Count trigger actions of a PDF page.
 *
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	trigger		The page trigger type. 
 *							Please refer to macro definitions <b>FSPDF_TRIGGER_PAGE_XXX</b> and this should be one of these macros.
 * @param[out]	count		Pointer to a ::FS_INT32 object that receives the count of the page actions.
 *							If there's any error, it will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>count</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to count trigger actions of a PDF page for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
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
FS_RESULT	FSPDF_Page_CountActions(FSCRT_PAGE page, FS_INT32 trigger, FS_INT32* count);

/**
 * @brief	Get a trigger action of a PDF page.
 *
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	trigger		The page trigger type. 
 *							Please refer to macro definitions <b>FSPDF_TRIGGER_PAGE_XXX</b> and this should be one of these macros.	
 * @param[in]	index		Index of trigger action. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Page_CountActions.
 * @param[out]	actionData	Pointer to a ::FSPDF_ACTIONDATA structure that receives the page action.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>actionData</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or no action is found.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get a trigger actions of a PDF page for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
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
FS_RESULT	FSPDF_Page_GetAction(FSCRT_PAGE page, FS_INT32 trigger, FS_INT32 index, FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Perform the page javascript which is specified by the trigger.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a document object. It should be valid.
 * @param[in]	trigger		The type of the trigger event. Please refer to macro definitions <b>FSPDF_TRIGGER_PAGE_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to perform the page javascript action for any other reason.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no suitable action is found.<br>
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
FS_RESULT	FSPDF_Page_DoJavaScriptAction(FSCRT_PAGE page, FS_INT32 trigger);

/********************************************************************************/
/* Page transformation matrix                                                   */
/********************************************************************************/
/**
 * @brief	Get page transformation matrix.
 * 
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	x			Left position of the transformation area in device coordinate, a ::FS_INT32 value, commonly in pixels.
 * @param[in]	y			Top position of the transformation area in device coordinate, a ::FS_INT32 value, commonly in pixels.
 * @param[in]	width		Width of the transformation area in device coordinate, a ::FS_INT32 value, commonly in pixels.
 * @param[in]	height		Height of the transformation area in device coordinate, a ::FS_INT32 value, commonly in pixels.
 * @param[in]	rotation	Page rotation value. 
 *							Please refer to macro definitions <b>FSCRT_PAGEROTATION_XXX</b> and this should be one of these macros.
 * @param[out]	matrix		Pointer to a ::FSCRT_MATRIX structure that receives the transformation matrix.
 *							If there's any error, it will be [1 0 0 1 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>matrix</i> is a <b>NULL</b> pointer, or <i>rotation</i> is an invalid value.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get page matrix for any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	The location of origin of coordinate is at the corner of bottom-left of page, and page unit is 1/72 inch.<br>
 * 			Transformation matrix is used to transform PDF page coordinate to device coordinate. Call function ::FSCRT_Matrix_GetReverse to get a reversed matrix to transform to opposite direction.
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
FS_RESULT	FSPDF_Page_GetMatrix(FSCRT_PAGE page, FS_INT32 x, FS_INT32 y, FS_INT32 width, FS_INT32 height, FS_INT32 rotation, FSCRT_MATRIX* matrix);

/**
 * @brief	Get a transformation matrix from PDF page coordinate to device coordinate.
 * 
 * @param[out]	matrix		Pointer to a ::FSCRT_MATRIX structure that receives the transformation matrix.
 *							If there's any error, it will be [1 0 0 1 0 0].
 * @param[in]	srcRect		Pointer to a ::FSCRT_RECTF structure which is a rectangle in PDF page coordinate.
 * @param[in]	dstRect		Pointer to a ::FSCRT_RECT structure which is a rectangle in device coordinate.
 * @param[in]	rotation	Rotation value for parameter <i>srcRect</i> to map <i>dstRect</i>.
 *							Please refer to macro definitions <b>FSCRT_PAGEROTATION_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>matrix</i> or <i>srcRect</i> or <i>dstRect</i> is a <b>NULL</b> pointer, or <i>rotation</i> is an invalid value.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	This is a helper function to get a transformation matrix from PDF page coordinate to device coordinate.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Matrix_TransformPageToDevice(FSCRT_MATRIX* matrix, const FSCRT_RECTF* srcRect, const FSCRT_RECT* dstRect, FS_INT32 rotation);

/**
 * @brief	Get a transformation matrix from device coordinate to PDF page coordinate.
 * 
 * @param[out]	matrix		Pointer to a ::FSCRT_MATRIX structure that receives the transformation matrix.
 *							If there's any error, it will be [1 0 0 1 0 0].
 * @param[in]	srcRect		Pointer to a ::FSCRT_RECT structure which is a rectangle in device coordinate.
 * @param[in]	dstRect		Pointer to a ::FSCRT_RECTF structure which is a rectangle in PDF page coordinate.
 * @param[in]	rotation	Rotation value for parameter <i>srcRect</i> to map <i>dstRect</i>.
 *							Please refer to macro definitions <b>FSCRT_PAGEROTATION_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>matrix</i> or <i>srcRect</i> or <i>dstRect</i> is a <b>NULL</b> pointer, or <i>rotation</i> is an invalid value.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	This is a helper function to get a transformation matrix from device coordinate to PDF page coordinate.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Matrix_TransformDeviceToPage(FSCRT_MATRIX* matrix, const FSCRT_RECT* srcRect, const FSCRT_RECTF* dstRect, FS_INT32 rotation);

/*******************************************************************************/
/* Calculate content margin and page rendering                                 */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_PAGEMARGIN_
#define _FSPDF_DEF_MACRO_PAGEMARGIN_
/**
 * @name 	Macro Definitions for Page Margin
 * @note	Currently Foxit PDF SDK supports two modes to calculate page margin:<br>
 * 			1) analyzing bounding box of all page contents.
 * 			2) detecting paths for background and images.
 */
/**@{*/

/** @brief	Calculate margin according to bounding box of all contents. */
#define FSPDF_PAGEMARGIN_CONTENTSBBOX		0
/** @brief	Calculate margin by detecting paths or images. */
#define FSPDF_PAGEMARGIN_DETECTION			1

/**@}*/
#endif /* _FSCRT_DEF_MACRO_ERRCODE_ */

/**
 * @brief	Calculate content box rectangle in PDF page.
 * 
 * @param[in]	page			Handle to a valid <b>FSCRT_PAGE</b> object. It should be a valid handle of PDF page that has been parsed.
 * @param[in]	mode			Mode to calculate page margin. 
 *								Please refer to macro definitions <b>FSPDF_PAGEMARGIN_XXX</b> and this should be one of these macros.
 * @param[out]	rectBBox		Pointer to a ::FSCRT_RECTF structure that receives the content box rectangle, in 1/72 inch.
 *								If there's any error, it will be [0 0 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if any of five parameters <i>page</i> and <i>rectBBox</i> is a <b>NULL</b> pointer, or <i>mode</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTPARSED if parameter <i>page</i> hasn't been parsed.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to calculate content box rectangle in PDF page for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
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
FS_RESULT	FSPDF_Page_CalcContentBBox(FSCRT_PAGE page, FS_INT32 mode, FSCRT_RECTF* rectBBox);

#ifndef _FSPDF_DEF_MACRO_PAGERENDERFLAG_
#define _FSPDF_DEF_MACRO_PAGERENDERFLAG_
/**
 * @name	Macro Definitions for PDF Page Render Flags
 * @note	There are two PDF page render modes: one is normal, and the other one is for quick draw page content.
 */
/**@{*/

/** @brief	PDF page render flag for normal mode. */
#define FSPDF_PAGERENDERFLAG_NORMAL			0
/** @brief	PDF page parsing flag for quick draw mode. */
#define FSPDF_PAGERENDERFLAG_QUICKDRAW		1

/**@}*/
#endif /* _FSPDF_DEF_MACRO_PAGERENDERFLAG_ */

/**
 * @brief	Start rendering a PDF page in a renderer with a PDF rendering context.
 *
 * @details	It will take a long time to render a page with complex or large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass parameter <i>renderProgress</i> to function ::FSCRT_Progress_Continue to continue rendering in steps, 
 *			and call function ::FSCRT_Progress_Release to destroy <i>renderProgress</i> object if rendering process is done.
 * 
 * @param[in]	pdfRenderContext	Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF rendering context, created by function ::FSPDF_RenderContext_Create.
 * @param[in]	renderer			Handle to a <b>FSCRT_RENDERER</b> object which is a rendering engine, created by function ::FSCRT_Renderer_CreateOnBitmap or platform-dependednt renderer creating functions.
 * @param[in]	page				Handle to a valid <b>FSCRT_PAGE</b> object. It should be a valid handle of PDF page that has been parsed.
 * @param[in]	flag				Page render flag to a ::FS_INT32 value. 
 *									Please refer to macro definitions <b>FSPDF_PAGERENDERFLAG_XXX</b> and this should be one of these macros.
 * @param[out]	renderProgress		Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *									If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if any of four parameters <i>pdfRenderContext</i>, <i>renderer</i>, <i>page</i> and <i>renderProgress</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTPARSED if parameter <i>page</i> hasn't been parsed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	To call this function, parameter <i>page</i> should be parsed. 
 *			Please refer to function ::FSPDF_Page_StartParse for how to parse a page.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				<li> <i>renderProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_StartPage(FSPDF_RENDERCONTEXT pdfRenderContext, FSCRT_RENDERER renderer, 
										  FSCRT_PAGE page, FS_INT32 flag, FSCRT_PROGRESS* renderProgress);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFPAGE */

#endif /* _FSPDF_PAGE_R_H_ */

