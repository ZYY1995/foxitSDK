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
 * @file	fpdf_page_w.h
 * @brief	Header file for \ref FPDFPAGE "PDF Page" module of Foxit PDF SDK.
 * @details	This header file provides direct access to PDF page.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Set PDF page attributes. </li>
 *			<li>2. Modify PDF page trigger actions. </li>
 *			<li>3. Page edition: create, delete and flatten. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Edit Add-on</b> explicitly.
 */

#ifndef _FSPDF_PAGE_W_H_
#define _FSPDF_PAGE_W_H_

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

/*******************************************************************************/
/* Access PDF page attributes                                                  */
/*******************************************************************************/
/**
 * @brief	Change page index of a PDF page.
 *
 * @details	To change page index is just like moving specific PDF page to a new place in current PDF document.
 *			So, indexes of PDF pages between old and new index of specific PDF page will also be changed as well.
 *
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	index		New index of page.Range: 0 to (pagecount-1). <i>pagecount</i> is returned by function ::FSPDF_Doc_CountPages.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is a <b>NULL</b> pointer or <i>index</i> is out of range. <br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting page index is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to change page index of a PDF page for any other reason.<br>
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
FS_RESULT	FSPDF_Page_SetIndex(FSCRT_PAGE page, FS_INT32 index);

/**
 * @brief	Set page size.
 *
 * @details	New page size should be greater than 0, and cannot be greater than the original one. 
 *			But for the newly created page (by function ::FSPDF_Page_Create),it can be set with any valid size, 
 *
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	width		A ::FS_FLOAT value for page width, unit is 1/72 inch.
 * @param[in]	height		A ::FS_FLOAT value for page height, unit is 1/72 inch.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is a <b>NULL</b> pointer, or <i>width</i> or <i>height</i> is not greater than 0,
 *			or <i>width</i> or <i>height</i> is greater than original value when <i>page</i> is loaded, not created by function ::FSPDF_Page_Create.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting page size is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set page size for any other reason.<br>
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
FS_RESULT	FSPDF_Page_SetSize(FSCRT_PAGE page, FS_FLOAT width, FS_FLOAT height);

/**
 * @brief	Set page rotation.
 * 
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	rotation	An integer value for page rotation state. 
 *							Please refer to macro definitions <b>FSCRT_PAGEROTATION_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is a <b>NULL</b> pointer, or <i>rotation</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting page rotation is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set page rotation for any other reason.<br>
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
FS_RESULT	FSPDF_Page_SetRotation(FSCRT_PAGE page, FS_INT32 rotation);

/**
 * @brief	Set page box which is a rectangle type of value.
 * 
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	boxType		Page box to a ::FS_INT32 value. 
 *							Please refer to macro definitions <b>FSPDF_PAGEBOX_XXX</b> and this should be one of these macros.
 * @param[in]	pageBox		Pointer to a ::FSCRT_RECTF structure to be set.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>pageBox</i> is a <b>NULL</b> pointer, or <i>boxType</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting page box rectangle is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set page box for any other reason.<br>
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
FS_RESULT	FSPDF_Page_SetBox(FSCRT_PAGE page, FS_INT32 boxType, const FSCRT_RECTF* pageBox);

/********************************************************************************/
/* Page trigger actions                                                         */
/********************************************************************************/
/**
 * @brief	Set a page trigger action.
 *
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object. 
 * @param[in]	trigger		The page trigger type. 
 *							Please refer to macro definitions <b>FSPDF_TRIGGER_PAGE_XXX</b> and this should be one of these macros.
 * @param[in]	index		Index of trigger action. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Page_CountActions.
 * @param[in]	actionData	Pointer to a ::FSPDF_ACTIONDATA structure to be set.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>actionData</i> is a <b>NULL</b> pointer, or <i>actionData</i> is empty, 
 *			or any member of FSPDF_ACTIONDATA::actionData is invalid, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting page action is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or no action is found.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set page action for any other reason.<br>
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
FS_RESULT	FSPDF_Page_SetAction(FSCRT_PAGE page, FS_INT32 trigger, FS_INT32 index, const FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Insert a page trigger action.
 *
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	trigger		The page trigger type. 
 *							Please refer to macro definitions <b>FSPDF_TRIGGER_PAGE_XXX</b> and this should be one of these macros.	
 * @param[in]	index		Zero-base index, where action will be inserted. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Page_CountActions.<br>
 *							If it's out of range or no action found, the <i>actionData</i> will be inserted to the last.
 * @param[in]	actionData	Pointer to a ::FSPDF_ACTIONDATA structure which to be inserted.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>actionData</i> or FSPDF_ACTIONDATA::actionDatais a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or inserting page action is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to insert page action for any other reason.<br>
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
FS_RESULT	FSPDF_Page_InsertAction(FSCRT_PAGE page, FS_INT32 trigger, FS_INT32 index, const FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Remove a page trigger action.
 *
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.<br>
 *							Returned by function ::FSPDF_Doc_GetPage or ::FSPDF_Page_Create.
 * @param[in]	trigger		The page trigger type. Please refer to macro definitions <b>FSPDF_TRIGGER_PAGE_XXX</b> and this should be one of these macros.	
 * @param[in]	index		index of trigger action which is to be removed. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_Page_CountActions.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or removing page action is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or no action is found.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to remove page action for any other reason.<br>
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
FS_RESULT	FSPDF_Page_RemoveAction(FSCRT_PAGE page, FS_INT32 trigger, FS_INT32 index);

/**
 * @brief	Remove all trigger actions of a PDF page.
 *
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.<br>
 *							Returned by function ::FSPDF_Doc_GetPage or ::FSPDF_Page_Create.
 * @param[in]	trigger		The page trigger type. Please refer to macro definitions <b>FSPDF_TRIGGER_PAGE_XXX</b> and this should be one of these macros.	
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or removing all actions of a PDF page is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no action of PDF page is found.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to remove all actions of a PDF page for any other reason.<br>
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
FS_RESULT	FSPDF_Page_RemoveAllActions(FSCRT_PAGE page, FS_INT32 trigger);

/**
 * @brief	Transform a PDF page, including the annotations and form fields on the page.
 *
 * @note	This function only supports scaling and translating.
 *			and after this operation, the page should be reloaded to display expected content.
 *
 * @param[in]	page					Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	matrix					Pointer to a ::FSCRT_MATRIX structure object.
 * @param[in]	needTransformClipPath	A ::FS_BOOL value which indicates whether to transform the page with clip rect or not.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is a <b>NULL</b> pointer, or <i>matrix</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or transform a PDF page is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to transform a PDF page for any other reason.<br>
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
FS_RESULT	FSPDF_Page_Transform(FSCRT_PAGE page, const FSCRT_MATRIX* matrix, FS_BOOL needTransformClipPath);

/**
 * @brief	Set clip rectangle for all page objects on PDF page.
 *
 * @details	It will save time to set all page objects clip rectangle, and no need to call function ::FSPDF_PageObject_SetClipRect for every page object.
 *
 * @param[in]	page					Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	clipRect				Pointer to a ::FSCRT_RECTF structure for clip rectangle which is to be set to all page objects.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>clipRect</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting page objects clip rectangle is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
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
FS_RESULT	FSPDF_Page_SetClipRect(FSCRT_PAGE page, const FSCRT_RECTF* clipRect);

/********************************************************************************/
/* Page editing                                                                 */
/********************************************************************************/
#ifndef _FSPDF_DEF_MACRO_FLATTENFLAG_
#define _FSPDF_DEF_MACRO_FLATTENFLAG_
/**
 * @name	Macro Definitions for Flatten Option
 * @note	These are used for indicating the option of flatten.
 */
/**@{*/

/** @brief	Flatten contents for displaying and it can be combined with any flags except ::FSPDF_FLATTENFLAG_PRINT. */
#define FSPDF_FLATTENFLAG_DISPLAY			0
/** 
 * @brief	Flatten contents for printing and it can be combined with any flags except ::FSPDF_FLATTENFLAG_DISPLAY. 
 * @note	Specially, text, file attachment and sound annotations will be ignored. 
 */
#define FSPDF_FLATTENFLAG_PRINT				1
/** @brief	Flatten contents without annotations except widget annotations and it should be combined with ::FSPDF_FLATTENFLAG_PRINT or ::FSPDF_FLATTENFLAG_DISPLAY. */
#define FSPDF_FLATTENFLAG_NOANNOT			2
/** @brief  Flatten contents without form controls and it should be combined with ::FSPDF_FLATTENFLAG_PRINT or ::FSPDF_FLATTENFLAG_DISPLAY. */
#define FSPDF_FLATTENFLAG_NOFORMCONTROL		4

/**@}*/
#endif /* _FSPDF_DEF_MACRO_FLATTENFLAG_ */

/**
 * @brief	Create a new page to a position specified by the index.
 *
 * @param[in]	document		Valid handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	index			A zero-based index which specifies the position of the created page in PDF document.<br>
 *								Range: 0 to (pagecount-1). <i>pagecount</i> is returned by function ::FSPDF_Doc_CountPages.<br>
 *								If this is out of range, the new page will be added to the end in PDF document.
 * @param[out]	page			Pointer to a <b>FSCRT_PAGE</b> handle that receives a handle of the newly created page.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if any of two parameters <i>document</i> or <i>page</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a valid PDF document type.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or creating PDF page is not allowed.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if the data of parameter <i>document</i> is not ready 
 *			when <i>document</i> is returned by function ::FSPDF_Doc_AsyncLoad.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to create a new PDF page for any other reason.<br>
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
FS_RESULT	FSPDF_Page_Create(FSCRT_DOCUMENT document, FS_INT32 index, FSCRT_PAGE* page);

/**
 * @brief	Delete a page from document.
 *
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or deleting PDF page is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to delete a PDF page for any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Page_Delete(FSCRT_PAGE page);

/**
 * @brief	Flatten a PDF page, and annotations or form fields will be made to be a part of the page contents.
 *
 * @param[in]	page		Handle to a valid <b>FSCRT_PAGE</b> object.
 * @param[in]	flags		The flatten option. 
 *							Please refer to macro definitions <b>FSPDF_FLATTENFLAG_XXX</b> and this should be one or combination of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is a <b>NULL</b> pointer, or <i>flags</i> out of range.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or flattening is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to flatten a PDF page for any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Callers can use ::FSPDF_FLATTENFLAG_NOANNOT or ::FSPDF_FLATTENFLAG_NOFORMCONTROL to flatten a PDF page without
 *			annotations or forms, however, It will do nothing if <i>flags</i> ::FSPDF_FLATTENFLAG_NOANNOT is combined with ::FSPDF_FLATTENFLAG_NOFORMCONTROL.<br>
 *			After flattening a PDF page, callers should re-parse this page.<br>
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
FS_RESULT 	FSPDF_Page_Flatten(FSCRT_PAGE page, FS_DWORD flags);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFPAGE */

#endif /* _FSPDF_PAGE_W_H_ */

