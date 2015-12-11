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
 * @file	fpdf_reflow_r.h
 * @brief	Header file for \ref FPDFREFLOW "PDF Reflow" module of Foxit PDF SDK.
 * @details	This header file defines PDF page reflow supports.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Rearrange the content of parsed PDF pages.</li>
 *			<li>2. Reparse PDF pages, which have been already parsed, according to the user's required page size.</li>
 *			<li>3. Render a reflowed page.</li>
 *			<li>4. Get data and coordinates to the current reading position.</li>
 *			<li>5. Get a <b>FSPDF_TEXTPAGE</b> object from reflowed result.</li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> explicitly.
 */

#ifndef _FSPDF_REFLOW_R_H_
#define _FSPDF_REFLOW_R_H_

/** 
 * @defgroup	FPDFREFLOW PDF Reflow
 * @brief		Definitions for reflow related operation.<br>
 *				Definitions and functions in this module are included in fpdf_reflow_r.h.<br>
 *				Module: PDFReflow<br>
 *				License Identifier: PDFReflow/All<br>
 *				Available License Right: Reading
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. Reflow PDF page:
 *					<ul>
 *					<li>a. Create or release a page-reflow object, set page size and line space for a page-reflow object, and start reflowing in a progressive process.</li>
 *					<li>b. PDF page-reflow is a common feature to display page contents in a small screen device. It re-lays out page contents.</li>
 *					<li>c. Note: the progressive process of page-reflow should finish before rendering reflowed result or accessing its data.</li>
 *					</ul>
 *				</li>
 *				<li>2. Render reflowed page:
 *					<ul>
 *					<li>a. Get content size of a reflowed page, get transformation matrix for a reflowed page, and render a reflowed page.</li>
 *					<li>b. When a page is reflowed, its coordinates are different. Caller should get a new transformation matrix to display.</li>
 *					</ul>
 *				</li>
 *				<li>3. Data of reflowed page:
 *					<ul>
 *					<li>a. Get focus data for a position, retrieve focus position from focus data, and get text page object.</li>
 *					<li>b. In order to track a position in a reflowed page, Foxit PDF SDK uses a focus data to represent the position.
 *						   Caller can store focus data or save the data to file so that the position can be retrieved later.
 *						   Focus is similar to bookmark or destination in PDF, but it's simpler.<br>
 *						   Functions defined in fpdf_textpage_r.h can be used to get text information.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Base Definitions for Reflow                                                 */
/*                                                                             */
/* Handle definitions, macro definitions                                       */
/*******************************************************************************/
#ifndef _FSPDF_DEF_HANDLE_REFLOWPAGE_
#define _FSPDF_DEF_HANDLE_REFLOWPAGE_

/** @brief	Handle type to PDF reflow page. */
FSCRT_DEFINEHANDLE(FSPDF_REFLOWPAGE);

#endif /* _FSPDF_DEF_HANDLE_REFLOWPAGE_ */

#ifndef _FSPDF_DEF_MACRO_REFLOWFLAG_
#define _FSPDF_DEF_MACRO_REFLOWFLAG_
/**
 * @name	Macro Definitions for Reflow Parser Flags
 */
/**@{*/

/** @brief	Reflow parsing flag for normal mode, without image. */
#define FSPDF_REFLOWFLAG_NORMAL			0x0
/** @brief	Reflow parsing flag for image mode. */
#define FSPDF_REFLOWFLAG_IMAGE			0x1 
/** 
 * @brief	Reflow parsing flag for single screen mode.
 *
 * @details	The flag can avoid that truncate problem the bottom of screen displaying the upper part of last text or image in single screen mode.
 *			The truncate problem is related to the height of the set by calling ::FSPDF_ReflowPage_SetSize and 
 *			if it isn't set this flag, the screen could display the upper part of text in the last line or image.
 *			It can improve the effect when reading single screen mode, however, the scroll screen mode would be affected.
 */
#define FSPDF_REFLOWFLAG_NOTRUNCATE		0x2 

/**@}*/
#endif /* _FSPDF_DEF_MACRO_REFLOWFLAG_ */

/*******************************************************************************/
/* PDF page reflow                                                             */
/*******************************************************************************/
/**
 * @brief	Create a reflow page from a PDF page.
 *
 * @param[in]	pdfPage			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[out]	reflowPage		Pointer to a <b>FSPDF_REFLOWPAGE</b> handle to receive the new reflow page handle if success.<br>
 *								Application should release this handle if not use it any more by calling function ::FSPDF_ReflowPage_Release.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pdfPage</i> or <i>reflowPage</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>pdfPage</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or reflow page is not allowed.<br>
 * 			::FSCRT_ERRCODE_NOTPARSED if parameter <i>pdfPage</i> is not parsed.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot create a reflow page because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pdfPage</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>reflowPage</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_ReflowPage_Create(FSCRT_PAGE pdfPage, FSPDF_REFLOWPAGE* reflowPage);

/**
 * @brief	Release all resources allocated for a PDF reflow page handle.
 *
 * @param[in]	reflowPage			Handle to a <b>FSPDF_REFLOWPAGE</b> object returned by function ::FSPDF_ReflowPage_Create.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>reflowPage</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>reflowPage</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_ReflowPage_Release(FSPDF_REFLOWPAGE reflowPage);

/**
 * @brief	Set screen size before calling function ::FSPDF_ReflowPage_StartParse.
 *
 * @param[in]	reflowPage			Handle to a <b>FSPDF_REFLOWPAGE</b> object returned by function ::FSPDF_ReflowPage_Create.
 * @param[in]	width				Width of desired page. This value should be more than 20.
 * @param[in]	height				Height of desired page. This value should be more than 20.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>reflowPage</i> is a <b>NULL</b> pointer, 
 *			or parameter <i>width</i> or <i>height</i> is equal to or less than 20.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>reflowPage</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_ReflowPage_SetSize(FSPDF_REFLOWPAGE reflowPage, FS_FLOAT width, FS_FLOAT height);

/**
 * @brief	Set line space before calling function ::FSPDF_ReflowPage_StartParse.
 *
 * @param[in]	reflowPage			Handle to a <b>FSPDF_REFLOWPAGE</b> object returned by function ::FSPDF_ReflowPage_Create.
 * @param[in]	lineSpace			The line space. Default value: 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>reflowPage</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>reflowPage</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_ReflowPage_SetLineSpace(FSPDF_REFLOWPAGE reflowPage, FS_FLOAT lineSpace);

/**
 * @brief	Set the top space of page before calling function ::FSPDF_ReflowPage_StartParse.
 *
 * @details	The function is used to set the distance between the page's top and the screen's top when to reflow a page.
 *
 * @param[in]	reflowPage			Handle to a <b>FSPDF_REFLOWPAGE</b> object returned by function ::FSPDF_ReflowPage_Create.
 * @param[in]	topSpace			The top space of page when to reflow and this value should be equal or greater than zero. Default value: 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>reflowPage</i> is a <b>NULL</b> pointer, or <i>topSpace</i> is less than zero.<br>.
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>reflowPage</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_ReflowPage_SetTopSpace(FSPDF_REFLOWPAGE reflowPage, FS_FLOAT topSpace);

/**
 * @brief	Start parsing process for a reflow page.
 *
 * @details	It may take a long time to parsing a reflow page, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should set parameter <i>reflowProgress</i> and call function ::FSCRT_Progress_Continue to continue parsing in steps if necessary, 
 *			and should call function ::FSCRT_Progress_Release to destroy <i>reflowProgress</i> object after parsing process.<br>
 * 			All the resources about reflow page will be loaded after the reflow page is parsed.<br>
 *			Function ::FSPDF_ReflowPage_SetSize must be called before this function sets the screen size.
 *			And this function should be called before any getting reflow method can be used.
 *
 * @param[in]	reflowPage			Handle to a <b>FSPDF_REFLOWPAGE</b> object returned by function ::FSPDF_ReflowPage_Create.
 * @param[in]	flags				Reflow parsing mode. It should be one of the following:
 *										<ul>
 *										<li>::FSPDF_REFLOWFLAG_NORMAL</li>
 *										<li>::FSPDF_REFLOWFLAG_IMAGE</li>
 *										<li>::FSPDF_REFLOWFLAG_NOTRUNCATE</li>			
 *										</ul>	
 * @param[out]	reflowProgress		Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process if successful.<br>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_FINISHED if parameter <i>reflowPage</i> has reflowed over.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>reflowPage</i> or <i>reflowProgress</i> is a <b>NULL</b> pointer, 
 *			or parameter <i>flags</i>is invalid.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot start reflowing page because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>reflowPage</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>reflowProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_ReflowPage_StartParse(FSPDF_REFLOWPAGE reflowPage, FS_DWORD flags, FSCRT_PROGRESS* reflowProgress);

/*******************************************************************************/
/* Rendering of PDF reflow                                                     */
/*******************************************************************************/
/**
 * @brief	Get width and height of a reflow page after calling function ::FSPDF_ReflowPage_StartParse.
 *
 * @param[in]	reflowPage			Handle to a <b>FSPDF_REFLOWPAGE</b> object returned by function ::FSPDF_ReflowPage_Create.
 * @param[out]	width				Pointer to a float that receives the width of reflow page.
 * @param[out]	height				Pointer to a float that receives the height of reflow page.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>reflowPage</i>, <i>width</i> or <i>height</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if parameter <i>reflowPage</i> hasn't been parsed yet.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>reflowPage</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_ReflowPage_GetContentSize(FSPDF_REFLOWPAGE reflowPage, FS_FLOAT* width, FS_FLOAT* height);

/**
 * @brief	Get matrix of a reflow page.
 *
 * @param[in]	reflowPage			Handle to a <b>FSPDF_REFLOWPAGE</b> object returned by function ::FSPDF_ReflowPage_Create.
 *									This should have been parsed successfully by calling function ::FSPDF_ReflowPage_StartParse.
 * @param[in]	x					Left pixel of the display area in the device coordinate system.
 * @param[in]	y					Top pixel of the display area in the device coordinate system.
 * @param[in]	width				Horizontal size (in pixels) for displaying the page.
 * @param[in]	height				Vertical size (in pixels) for displaying the page.
 * @param[in]	rotation			Page orientation. Valid values are:
 *									<ul>
 *									<li>0:	Normal</li>
 *									<li>1:	Rotate 90 degrees clockwise</li>
 *									<li>2:	Rotate 180 degrees</li>
 *									<li>3:	Rotate 90 degrees counter-clockwise</li>
 *									</ul>
 * @param[out]	matrix				Pointer to a ::FSCRT_MATRIX struct that receives the output matrix.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>reflowPage</i> or <i>matrix</i> is a <b>NULL</b> pointer, 
 *			or parameter <i>rotation</i> is invalid.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if parameter <i>reflowPage</i> hasn't been parsed yet.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot get matrix because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>reflowPage</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_ReflowPage_GetMatrix(FSPDF_REFLOWPAGE reflowPage, FS_INT32 x, FS_INT32 y, FS_INT32 width, FS_INT32 height, 
									   FS_INT32 rotation, FSCRT_MATRIX* matrix);

/**
 * @brief	Start rendering a reflow page.
 *
 * @details	It will take a long time to render reflow a page with complex or large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass <i>renderProgress</i> to ::FSCRT_Progress_Continue to continue rendering in steps, 
 *			and should call ::FSCRT_Progress_Release to destroy <i>renderProgress</i> object after rendering process.
 * 
 * @param[in]		pdfRenderContext	Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF rendering context, 
 *										created by function ::FSPDF_RenderContext_Create.
 * @param[in]		renderer			Handle to a <b>FSCRT_RENDERER</b> object which represents a rendering engine, 
 *										created by function ::FSCRT_Renderer_CreateOnBitmap or platform-dependednt renderer creating functions.
 * @param[in]		reflowPage			Handle to a <b>FSPDF_REFLOWPAGE</b> object returned by function ::FSPDF_ReflowPage_Create.
 *										This should have been parsed successfully by calling function ::FSPDF_ReflowPage_StartParse.
 * @param[out]		renderProgress		Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process if successful.<br>
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pdfRenderContext</i>, <i>renderer</i>, <i>reflowPage</i> or <i>renderProgress</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_NOTPARSED if parameter <i>reflowPage</i> is not parsed.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot start rendering a reflow page because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Among functions <b>FSPDF_RenderContext_SetXXX</b>, only ::FSPDF_RenderContext_SetMatrix is effective for the rendering of reflow page .
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				<li> <i>reflowPage</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>renderProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_StartReflowPage(FSPDF_RENDERCONTEXT pdfRenderContext, FSCRT_RENDERER renderer, 
											    FSPDF_REFLOWPAGE reflowPage, FSCRT_PROGRESS* renderProgress);

/*******************************************************************************/
/* Data of reflowed page                                                       */
/*******************************************************************************/
/**
 * @brief	Get focus data corresponding to a given position in device coordinate system.
 *
 * @details	Focus data of a specific content is fixed, and will not change because of different sizes of reflow pages,
 *			which are retrieved from the same PDF page of the same content.
 *			So focus data can be used to locate the same content of a PDF page in reflow pages with different sizes but same reflow content.
 *
 * @param[in]	reflowPage			Handle to a <b>FSPDF_REFLOWPAGE</b> object returned by function ::FSPDF_ReflowPage_Create.
 *									This should have been parsed successfully by calling function ::FSPDF_ReflowPage_StartParse.
 * @param[in]	matrix				Pointer to a ::FSCRT_MATRIX structure returned by function ::FSPDF_ReflowPage_GetMatrix.
 * @param[in]	x					X-coordinate of a specific position, in device coordinate system.
 * @param[in]	y					Y-coordinate of a specific position, in device coordinate system.
 * @param[out]	focusData			Pointer to a ::FSCRT_BSTR structure that receives the focus data corresponding to the specific position. 
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>reflowPage</i>, <i>matrix</i> or <i>focusData</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if parameter <i>reflowPage</i> hasn't been parsed yet.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot get focus data because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>reflowPage</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_ReflowPage_GetFocusData(FSPDF_REFLOWPAGE reflowPage, const FSCRT_MATRIX* matrix, FS_INT32 x, FS_INT32 y, FSCRT_BSTR* focusData);

/**
 * @brief	Get a point of a position in device coordinate system corresponding to a given focus data.
 *
 * @details	Focus data of a specific content is fixed, and will not change because of different sizes of reflow pages,
 *			which are retrieved from same PDF page and with same content.
 *			So focus data can be used to locate the same content of a PDF page in reflow pages with different sizes but same reflow content.
 *
 * @param[in]	reflowPage			Handle to a <b>FSPDF_REFLOWPAGE</b> object returned by function ::FSPDF_ReflowPage_Create.
 *									This should have been parsed successfully by calling function ::FSPDF_ReflowPage_StartParse.
 * @param[in]	matrix				Pointer to a ::FSCRT_MATRIX structure returned by function ::FSPDF_ReflowPage_GetMatrix.
 * @param[in]	focusData			Focus data used to get its corresponding position in device coordinate system, with specific matrix. 
 *									This is returned by function ::FSPDF_ReflowPage_GetFocusData.
 * @param[out]	x					Pointer to a ::FS_INT32 object that receives x-coordinate of a position. 
 *									This position is just corresponding to given focus data in device coordinate system.
 * @param[out]	y					Pointer to a ::FS_INT32 object that receives y-coordinate of a position. 
 *									This position is just corresponding to given focus data in device coordinate system.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>reflowPage</i>, <i>matrix</i>, <i>focusData</i>, <i>x</i> or <i>y</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if parameter <i>reflowPage</i> hasn't been parsed yet.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot get focus position because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>reflowPage</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_ReflowPage_GetFocusPosition(FSPDF_REFLOWPAGE reflowPage, const FSCRT_MATRIX* matrix, const FSCRT_BSTR* focusData, 
											  FS_INT32* x, FS_INT32* y);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFREFLOW */

#endif /* _FSPDF_REFLOW_H_ */

