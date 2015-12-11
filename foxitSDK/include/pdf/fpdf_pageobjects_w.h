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
 * @file	fpdf_pageobjects_w.h
 * @brief	Header file for \ref FPDFPAGEOBJECTS "PDF Page Objects" module of Foxit PDF SDK.
 * @details	This header file provides direct access to PDF page objects.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Add and remove page object. </li>
 *			<li>2. Generate page content. </li>
 *			<li>3. Clone page object. </li>
 *			<li>4. Set page object common attributes. </li>
 *			<li>5. Create text object and set particular attributes. </li>
 *			<li>6. Create path object and set particular attributes. </li>
 *			<li>7. Create image object and set particular attributes. </li>
 *			<li>8. Create Form XObject objects. </li>
 *			<li>9. Add and delete path clip. </li>
 *			<li>10. Add and delete text clip. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Edit Add-on</b> explicitly.
 */

#ifndef _FSPDF_PAGEOBJECTS_W_H_
#define _FSPDF_PAGEOBJECTS_W_H_

/**
 * @defgroup	FPDFPAGEOBJECTS PDF Page Objects
 * @brief		Definitions for access to PDF Page Objects, PDF Marked Content, and PDF Layers.<br>
 *				Definitions and functions in this module are included in fpdf_pageobjects_r.h, fpdf_pageobjects_w.h, fpdf_markedcontent_r.h, fpdf_markedcontent_w.h, fpdf_layer_r.h, and fpdf_layer_w.h.<br>
 *				Module: PDFPageObjects<br>
 *				License Identifier: PDFPageObjects/All<br>
 *				Available License Right: Reading/Writing<br>
 *				For License Right <b>Reading</b>, see fpdf_pageobjects_r.h, fpdf_markedcontent_r.h, and fpdf_layer_r.h.<br>
 *				For License Right <b>Writing</b>, see fpdf_pageobjects_w.h, fpdf_markedcontent_w.h, and fpdf_layer_w.h.
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. Page objects:
 *					<ul>
 *					<li>a. Enumerate page objects, get page objects by position, insert or remove page objects, and generate contents of page objects.</li>
 *					<li>b. Page content consists of page objects. Each page object contains its state information, data and instructions for rendering.
 *						   A form XObject is not only a page object, but also a container. A form XObject consists of a set of page objects or sub Form XObjects.</li>
 *					<li>c. Note: PDF page should be parsed before page objects can be accessed.</li>
 *					<li>d. Reference: Chapter 4 and 5 in PDF Reference 1.7 describe how page contents are expressed.</li>
 *					</ul>
 *				</li>
 *				<li>2. Page object: get type of a page object, clone a page object, and access properties or state data.</li>
 *				<li>3. Text object: get or set text state, access unicode string of a text object, and create a text object.</li>
 *				<li>4. Path object: get or set path data, access fill mode and stroke state, and create a path object.</li>
 *				<li>5. Image object: clone bitmap object associated to an image object, create an image object, and set image data.</li>
 *				<li>6. Form XObject object: get page objects associated to a Form XObject object, and create a Form XObject object.</li>
 *				<li>7. Clipping data:
 *					<ul>
 *					<li>a. Enumerate clipping path objects or clipping text objects, add or delete clipping path and text object,
 *						   and clear all clipping data.</li>
 *					<li>b. Each page object may have its own clipping data. In PDF, clipping data may be path objects or text objects.
 *						   Multiple clipping objects form intersections or union results.</li>
 *					</ul>
 *				</li>
 *				<li>8. PDF marked content:
 *					<ul>
 *					<li>a. Access to PDF page object's marked content, retrieve marked content object, add a new marked content item and delete a marked content item..</li>
 *					<li>b. Reference: Section 10.5 in PDF Reference 1.7 describes Marked Content of PDF Content Stream.</li>
 *					</ul>
 *				</li>
 *				<li>9. PDF Layer Context access: create and release PDF layer context, merge or copy state of PDF layer context objects. </li>
 *				<li>10. PDF Layer access:
 *					<ul>
 *					<li>a. Enumerate all layers of a PDF document , get name of a PDF layer, set and get visibility of a PDF layer. </li>
 *					<li>b. Note: If a PDF layer is invalid, it can't be viewed, designed, printed or exported.</li>
 *					</ul>
 *				</li>
 *				<li>11. Note: most functions in this module are not thread safe, caller should ensure not to call them
 *					   to process page objects in a same page across multi-threads or should maintain thread safety by application self.</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Page objects                                                                */
/*******************************************************************************/
/**
 * @brief	Insert a page object and it will be automatically freed.
 *
 * @details	If parameter <i>typeFilter</i> is ::FSPDF_PAGEOBJECT_ALL, parameter <i>index</i> is for all page objects.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObjs		Handle to a <b>FSPDF_PAGEOBJECTS</b> object which is the page objects. It should be valid.
 * @param[in]	typeFilter		A filter flag for the type of page objects.
 *								Please refer to macro definitions <b>FSPDF_PAGEOBJECT_XXX</b> and this should be one of these macros.
 * @param[in]	index			Index of page object. Range: 0 to (objcount-1). <i>objcount</i> is returned by function ::FSPDF_PageObjects_CountObjects.<br>
 *								If <i>index</i> is larger than (objcount-1), <i>pageObj</i> will be inserted to be the last one.
 *								if <i>index</i> is smaller than 0, <i>pageObj</i> will be inserted to be the first one.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObjs</i> or <i>pageObj</i> is a <b>NULL</b> pointer, or <i>typeFilter</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or inserting page object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_CONFLICT if parameter <i>pageObj</i> has existed in parameter <i>pageObjs</i>.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to insert page object for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Parameter <i>pageObj</i> can be returned by function ::FSPDF_TextObject_Create, ::FSPDF_PathObject_Create, ::FSPDF_ImageObject_Create, 
 *			::FSPDF_FormXObject_Create, or ::FSPDF_PageObject_Clone.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObjs</i>: this handle is short-term.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObjects_InsertObject(FSCRT_PAGE page, FSPDF_PAGEOBJECTS pageObjs, FS_INT32 typeFilter, FS_INT32 index, FSPDF_PAGEOBJECT pageObj);

/**
 * @brief	Remove a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObjs		Handle to a <b>FSPDF_PAGEOBJECTS</b> object which is the page objects. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is one page object. It should be valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObjs</i> or <i>pageObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or removing page object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if specific page object is not found in current page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObjs</i>: this handle is short-term.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObjects_RemoveObject(FSCRT_PAGE page, FSPDF_PAGEOBJECTS pageObjs, FSPDF_PAGEOBJECT pageObj);

/**
 * @brief	Generate PDF Page content.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObjs		Handle to a <b>FSPDF_PAGEOBJECTS</b> object which is the page objects. It should be valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>pageObjs</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or generating content is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to generate content of page objects for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Application must call this function before saving the page to a file or reload the page, otherwise all changes to the page objects will be lost.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObjs</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_PageObjects_GenerateContents(FSCRT_PAGE page, FSPDF_PAGEOBJECTS pageObjs);

/*******************************************************************************/
/* Page object                                                                 */
/*******************************************************************************/
/**
 * @brief	Clone a new page object.
 *
 * @details	Newly cloned page object is relative with input PDF page. 
 *			So it can only be used inside the document which contains the input page.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[out]	clonedPageObj	Pointer to a <b>FSPDF_PAGEOBJECT</b> handle that receives a cloned page object.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>clonedPageObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or cloning page object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				<li> <i>clonePageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_Clone(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FSPDF_PAGEOBJECT* clonedPageObj);

/**
 * @brief	Set matrix of a page object.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.<br>
 *							If it's a text object, matrix of this object can be set only if it has a font.
 * @param[in]	matrix		Pointer to a ::FSCRT_MATRIX structure object to be set.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>matrix</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting page object matrix is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>pageObj</i> doesn't have a valid page object type.<br>
 *			::FSCRT_ERRCODE_UNKNOWNSTATE if parameter <i>pageObj</i> is a text object but has no font.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_SetMatrix(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, const FSCRT_MATRIX* matrix);

/**
 * @brief	Transform a page object.
 *
 * @note	After call this function, caller might need call function ::FSPDF_PageObjects_GenerateContents to generate its contents,
 *			Or the change of page object could not be saved to document.
 *
 * @param[in]	page					Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj					Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.<br>
 *										If it's a text object, matrix of this object can be set only if it has a font.
 * @param[in]	matrix					Pointer to a ::FSCRT_MATRIX structure object.
 * @param[in]	needTransformClipPath	A ::FS_BOOL to indicate whether to transform the clip path with page object, or transform the page object only.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>matrix</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting page object matrix is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_Transform(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, const FSCRT_MATRIX* matrix, FS_BOOL needTransformClipPath);

/**
 * @brief	Set  graph states of a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj 		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[in]	graphState		Pointer to a ::FSPDF_GRAPHSTATE structure to be set.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>graphState</i> is a <b>NULL</b> pointer,  
 *			or if FSPDF_GRAPHSTATE::dashCount of parameter <i>graphState</i> is not between 0 and 16.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting page object graph states is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_SetGraphState(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, const FSPDF_GRAPHSTATE* graphState);

/**
 * @brief	Set color of a page object .
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj 		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[in]	isStroke		A ::FS_BOOL to set stroke color if <b>TRUE</b>, or to set fill color if <b>FALSE</b>.
 * @param[in]	color			A ::FS_ARGB is to be set. Format: 0xAARRGGBB.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting page object color is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_PageObject_SetColor(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FS_BOOL isStroke, FS_ARGB color);

/**
 * @brief	Set clip rectangle of a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[in]	clipRect		Pointer to a ::FSCRT_RECTF structure of clip rectangle to be set.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>pageObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting page object clip rectangle is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_SetClipRect(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, const FSCRT_RECTF* clipRect);

/********************************************************************************/
/* Text object                                                                  */
/********************************************************************************/
/**
 * @brief	Create a new text Object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[out]	textObj			Pointer to a <b>FSPDF_PAGEOBJECT</b> handle that receives the newly created text object.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>textObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or creating text object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>textObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_TextObject_Create(FSCRT_PAGE page, FSPDF_PAGEOBJECT* textObj);

/**
 * @brief	Set text states of a text object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	textObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a text object. It should be valid.
 * @param[in]	textState		Pointer to a ::FSPDF_TEXTSTATE structure to be set.
 * @param[in]	italic			A boolean which indicates whether the set text is italic or not.
 * @param[in]	weight			Original font weight. 0 means not specified.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>textObj</i> or <i>textState</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting text object text state is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>textObj</i> is not a text object.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set text state of a text object for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>textObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_TextObject_SetTextState(FSCRT_PAGE page, FSPDF_PAGEOBJECT textObj, 
										  const FSPDF_TEXTSTATE* textState, FS_BOOL italic, FS_INT32 weight);

/**
 * @brief	Set unicode string for a text object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	textObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a text object. It should be valid.
 * @param[in]	unicodeStr		Pointer to a ::FSCRT_BSTR structure to be set. It should be in UTF-8 format.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>textObj</i> or <i>unicodeStr</i> is a <b>NULL</b> pointer,
 *			 or <i>textObj</i> isn't set the font.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting text object string is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>textObj</i> is not a text object.<br>
 *			::FSCRT_ERRCODE_FORMAT if parameter <i>unicodeStr</i> is not in UTF-8 format.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set unicode string for a text object for any other reason.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	User must call ::FSPDF_TextObject_SetTextState to set a font for <i>textObj</i> if return ::FSCRT_ERRCODE_PARAM because font isn't to be set.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>textObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_TextObject_SetUnicodeString(FSCRT_PAGE page, FSPDF_PAGEOBJECT textObj, const FSCRT_BSTR* unicodeStr);

/*******************************************************************************/
/* Path object                                                                 */
/*******************************************************************************/
/**
 * @brief	Create a new path object.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[out]	pathObj		Pointer to a <b>FSPDF_PAGEOBJECT</b> object that receives the newly created path object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pathObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or creating path object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pathObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_PathObject_Create(FSCRT_PAGE page, FSPDF_PAGEOBJECT* pathObj);

/**
 * @brief	Set path data of a path object.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pathObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a path object. It should be valid.
 * @param[in]	pathData	Handle to a <b>FSCRT_PATHDATA</b> object to be set.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pathObj</i> or <i>pathData</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting path object path data is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>pathObj</i> is not a path object.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pathObj</i>: this handle is short-term.</li>
  *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PathObject_SetPathData(FSCRT_PAGE page, FSPDF_PAGEOBJECT pathObj, FSCRT_PATHDATA pathData);

/**
 * @brief	Set fill mode of a path object.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pathObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a path object. It should be valid.
 * @param[in]	fillMode	Please refer to macro definitions <b>FSCRT_FILLMODE_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pathObj</i> is a <b>NULL</b> pointer, or <i>fillMode</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting path object fill mode is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>pathObj</i> is not a path object.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pathObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PathObject_SetFillMode(FSCRT_PAGE page, FSPDF_PAGEOBJECT pathObj, FS_INT32 fillMode);

/**
 * @brief	Set stroke state of a path object.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pathObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a path object. It should be valid.
 * @param[in]	isStroke	A ::FS_BOOL value that specifies the stroke state:
 *							<ul>
 *							<li><b>TRUE</b>: the path object of parameter <i>pathObj</i> to be stroked.</li>
 *							<li><b>FALSE</b> the path object of parameter <i>pathObj</i> not to be stroked</li>
 *							</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>pathObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting path object stroke state is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>pathObj</i> is not a path object.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pathObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PathObject_SetStrokeState(FSCRT_PAGE page, FSPDF_PAGEOBJECT pathObj, FS_BOOL isStroke);

/*******************************************************************************/
/* Image object                                                                */
/*******************************************************************************/
/**
 * @brief	Create an image object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[out]	imageObj		Pointer to a <b>FSPDF_PAGEOBJECT</b> handle that receives the newly created image object.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>imageObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or creating image object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>imageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_ImageObject_Create(FSCRT_PAGE page, FSPDF_PAGEOBJECT* imageObj);

/**
 * @brief	Set a bitmap to an image object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	imageObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is an image object. It should be valid.
 * @param[in]	bitmap			Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object, and it can be returned by function ::FSCRT_Bitmap_Create or ::FSCRT_Bitmap_Clone.
 * @param[in]	mask			Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object for mask, and its format should be ::FSCRT_BITMAPFORMAT_8BPP_MASK.
 *								This is valid only when parameter <i>bitmap</i> doesn't have an alpha channel.
 *								It can be <b>NULL</b> or returned by function ::FSCRT_Bitmap_Create or ::FSCRT_Bitmap_Clone.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>imageObj</i> or <i>bitmap</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting bitmap to image object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>imageObj</i> is not an image object.<br>
 * 			::FSCRT_ERRCODE_UNSUPPORTED if format of parameter <i>mask</i> is not ::FSCRT_BITMAPFORMAT_8BPP_MASK when <i>mask</i> is valid.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set bitmap to an image object for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>imageObj</i>: this handle is short-term.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				<li> <i>mask</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_ImageObject_SetBitmap(FSCRT_PAGE page, FSPDF_PAGEOBJECT imageObj, FSCRT_BITMAP bitmap, FSCRT_BITMAP mask);

/**
 * @brief	Set an image to an image object.
 *
 * @details	Parameter <i>imageObj</i> can be set only one frame, so that caller must call function ::FSCRT_Image_LoadFrame 
 *			to load a frame of parameter <i>image</i> which is to be set.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	imageObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is an image object. It should be valid.
 * @param[in]	image			Handle to a <b>FSCRT_IMAGE</b> object which is a bitmap object, and it is returned or by function ::FSCRT_Image_LoadFromFile.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>imageObj</i> or <i>image</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting image to image object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>imageObj</i> is not an image object.<br>
 * 			::FSCRT_ERRCODE_DATANOTREADY if no frame of parameter <i>image</i> is loaded.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If callers need to reduce the memory during setting ::FSCRT_IMAGETYPE_TIF image, please use the function ::FSPDF_ImageObject_SetImageFromFileName.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>imageObj</i>: this handle is short-term.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_ImageObject_SetImage(FSCRT_PAGE page, FSPDF_PAGEOBJECT imageObj, FSCRT_IMAGE image);

/**
 * @brief	Set an image to an image object from a specific file path.
 *
 * @details The function can optimize the consume of memory for image in type ::FSCRT_IMAGETYPE_TIF, 
 *			however, it may reduce the performance a little bit. 
 *			For other image types, this function is just the same as function ::FSPDF_ImageObject_SetImage.<br>
 *			Users must not move or remove the image file specified by parameter <i>imageFileName</i> until current document is closed.
 *
 * @param[in]	page				Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	imageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is an image object. It should be valid.
 * @param[in]	imageFileName		Pointer to a UTF-8 encoded string that specifies a path of image file. It should be a valid pointer to ::FSCRT_BSTR.
 * @param[in]	frameIndexOfImage	The zero-based index of the frame in the image specified by parameter <i>imageFileName</i>.
 *									Range: 0 to (FrameCount-1). <i>FrameCount</i> is the count of frames in the image.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>imageObj</i> or <i>imageFileName</i> is <b>NULL</b> pointer or <i>imageFileName</i> is empty.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if parameter <i>frameIndexOfImage</i> is out of range.<br>
 *			::FSCRT_ERRCODE_FORMAT if the parameter <i>imageFileName</i> is not in UTF-8 format.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting image to image object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>imageObj</i> is not an image object.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set image to an image object for any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>imageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_ImageObject_SetImageFromFileName(FSCRT_PAGE page, FSPDF_PAGEOBJECT imageObj, const FSCRT_BSTR* imageFileName, FS_INT32 frameIndexOfImage);

/*******************************************************************************/
/* Form XObject object                                                               */
/*******************************************************************************/
/**
 * @brief	Create a Form XObject object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[out]	formXObj		Pointer to a <b>FSPDF_PAGEOBJECT</b> handle that receives the newly created Form XObject object.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>formXObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or creating Form XObject object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>formXObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormXObject_Create(FSCRT_PAGE page, FSPDF_PAGEOBJECT* formXObj);

/**
 * @brief	Extract appearance of contents and annotations from a source page to a Form XObject object.
 *
 * @param[in]	page				Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid. Parameter <i>formXObj</i> comes from this page.
 * @param[in]	formXObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object that receives the extracted appearance data of contents and annotations in parameter <i>srcPage</i>.
 *									This is returned by function ::FSPDF_FormXObject_Create.
 * @param[in]	srcPage				Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid. The extracted data comes from this source page.
 * @param[in]	isAnnotsIncluded	A boolean value that indicates whether annotations are included when extracting appearance.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>formXObj</i> or <i>srcPage</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or creating Form XObject object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> or <i>srcPage</i> is not a type of PDF page, or parameter <i>formXObject</i> is not a Form XObject object.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>formXObj</i>: this handle is short-term.</li>
 *				<li> <i>srcPage</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormXObject_ExtractAPFromPage(FSCRT_PAGE page, FSPDF_PAGEOBJECT formXObj, FSCRT_PAGE srcPage, FS_BOOL isAnnotsIncluded);

/*******************************************************************************/
/* Clipping data                                                               */
/*******************************************************************************/
/**
 * @brief	Add path for clipping to a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[in]	pathData		Handle to a <b>FSCRT_PATHDATA</b> object to be set.
 * @param[in]	fillMode		Please refer to macro definitions <b>FSCRT_FILLMODE_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i>, <i>pathData</i> is a <b>NULL</b> pointer.<br>,or <i>fillMode</i> is invalid.<br>.
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or adding clip path to page object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_AddClipPath(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FSCRT_PATHDATA pathData, FS_INT32 fillMode);

/**
 * @brief	Delete a path for clipping from a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[in]	index			Index of path to be deleted. Range: 0 to (pathcount-1). <i>pathcount</i> is returned by function ::FSPDF_PageObject_CountClipPath.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObjs</i> or <i>pageObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or deleting clip path from page object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or there is no path clip associated to <i>pageObj</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_DeleteClipPath(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FS_INT32 index);

/**
 * @brief	Add text for clipping to a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[in]	textObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a text object. It should be valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i>or <i>textObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or adding text clip to page object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				<li> <i>textObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_AddClipText(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FSPDF_PAGEOBJECT textObj);

/**
 * @brief	Delete a text for clipping from a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[in]	index			Index of path to be deleted. Range: 0 to (pathcount-1). <i>pathcount</i> is returned by function ::FSPDF_PageObject_CountClipText.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>pageObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or deleting text clip from page object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or there is no text clip associated to <i>pageObj</i>.<br>
 *			::FSCRT_ERRCODE_ERROR if failed to delete text clip from the page object for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_DeleteClipText(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FS_INT32 index);

/**
 * @brief	Clear all clips from a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>pageObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or clearing all clip from page object is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_ClearClips(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj);

/*******************************************************************************/
/* Page object release                                                         */
/*******************************************************************************/
/**
 * @brief	Release a page object which is created or which is cloned but not inserted into any PDF page.
 *
 * @details	This function is used to release page objects which are created by functions ::FSPDF_TextObject_Create, ::FSPDF_PathObject_Create, 
 *			::FSPDF_ImageObject_Create, ::FSPDF_FormXObject_Create, or ::FSPDF_PageObject_Clone, but not be inserted to PDF page.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>pageObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_Release(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj);

#ifdef __cplusplus
};
#endif
/**@}*/ /* group FPDFPAGEOBJECTS */


#endif // _FSPDF_PAGEOBJECTS_W_H_
