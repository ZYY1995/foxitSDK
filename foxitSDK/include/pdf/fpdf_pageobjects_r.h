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
 * @file	fpdf_pageobjects_r.h
 * @brief	Header file for \ref FPDFPAGEOBJECTS "PDF Page Objects" module of Foxit PDF SDK.
 * @details	This header file provides direct access to PDF page objects.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Get page and form XObject objects. </li>
 *			<li>2. Get a specific page object. </li>
 *			<li>3. Render page objects. </li>
 *			<li>4. Get page object common attributes. </li>
 *			<li>5. Get text object particular attributes. </li>
 *			<li>6. Get path object particular attributes. </li>
 *			<li>7. Get image object particular attributes. </li>
 *			<li>8. Get path clip. </li>
 *			<li>9. Get text clip. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Edit Add-on</b> explicitly.
 */

#ifndef _FSPDF_PAGEOBJECTS_R_H_
#define _FSPDF_PAGEOBJECTS_R_H_

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
/* Definitions for page objects                                                */
/*******************************************************************************/
#ifndef _FSPDF_DEF_HANDLE_PAGEOBJECT_
#define _FSPDF_DEF_HANDLE_PAGEOBJECT_

/** @brief	Handle type to page object. */
FSCRT_DEFINEHANDLE(FSPDF_PAGEOBJECT);

#endif /* _FSPDF_DEF_HANDLE_PAGEOBJECT_ */

#ifndef _FSPDF_DEF_HANDLE_PAGEOBJECTS_
#define _FSPDF_DEF_HANDLE_PAGEOBJECTS_

/** @brief	Handle type to page objects, which indicates a set of page objects. */
FSCRT_DEFINEHANDLE(FSPDF_PAGEOBJECTS);

#endif /* _FSPDF_DEF_HANDLE_PAGEOBJECTS_ */

#ifndef _FSPDF_DEF_MACRO_PAGEOBJECT_
#define _FSPDF_DEF_MACRO_PAGEOBJECT_
/**
 * @name	Macro Definitions for Page Object Type
 */
/**@{*/

/** @brief	Page object for all types. */
#define FSPDF_PAGEOBJECT_ALL				0
/** @brief	Text object. */
#define FSPDF_PAGEOBJECT_TEXT				1
/** @brief	Path object. */
#define FSPDF_PAGEOBJECT_PATH				2
/** @brief	Image object. */
#define FSPDF_PAGEOBJECT_IMAGE				3
/** @brief	Shading object. */
#define FSPDF_PAGEOBJECT_SHADING			4
/** @brief	Form XObject object. */
#define FSPDF_PAGEOBJECT_FORMXOBJECT		5

/**@}*/
#endif /* _FSPDF_DEF_MACRO_PAGEOBJECT_ */

#ifndef _FSPDF_DEF_MACRO_TEXTMODE_
#define _FSPDF_DEF_MACRO_TEXTMODE_
/**
 * @name	Macro Definitions for Text Rendering Modes
 */
/**@{*/

/** @brief	Fill text.*/
#define	FSPDF_TEXTMODE_FILL						0
/** @brief	Stroke text. */
#define	FSPDF_TEXTMODE_STROKE					1
/** @brief	Fill, and stroke text. */
#define	FSPDF_TEXTMODE_FILLSTROKE				2
/** @brief	Neither fill nor stroke text (invisible). */
#define	FSPDF_TEXTMODE_INVISIBLE				3
/** @brief	Fill text and add to path for clipping.*/
#define	 FSPDF_TEXTMODE_FILLClIP				4
/** @brief	Stroke text and add to path for clipping. */
#define	FSPDF_TEXTMODE_STROKECLIP				5
/** @brief	Fill, then stroke text and add to path for clipping. */
#define	FSPDF_TEXTMODE_FILLSTROKECLIP			6
/** @brief	Add text to path for clipping. */
#define	FSPDF_TEXTMODE_CLIP						7

/**@}*/
#endif /* _FSPDF_DEF_MACRO_TEXTMODE_ */

#ifndef _FSPDF_DEF_MACRO_IMAGEOBJECTCS_
#define _FSPDF_DEF_MACRO_IMAGEOBJECTCS_
/**
 * @name	Macro Definitions for Image object Color space
 */
/**@{*/
/** @brief Color space: Invalid. */
#define FSPDF_IMAGECS_INVALID					0
/** @brief Color space: DeviceGray. */
#define FSPDF_IMAGECS_DEVICEGRAY				1
/** @brief Color space: DeviceRGB. */	
#define FSPDF_IMAGECS_DEVICERGB					2
/** @brief Color space: DeviceCMYK. */
#define FSPDF_IMAGECS_DEVICECMYK				3
/** @brief Color space: CalGray. */
#define FSPDF_IMAGECS_CALGRAY					4
/** @brief Color space: CalRGB. */
#define FSPDF_IMAGECS_CALRGB					5
/** @brief Color space: Lab. */
#define FSPDF_IMAGECS_LAB						6
/** @brief Color space: Separation. */
#define FSPDF_IMAGECS_SEPARATION				8
/** @brief Color space: DeviceN. */
#define FSPDF_IMAGECS_DEVICEN					9
/** @brief Color space: Pattern. */
#define FSPDF_IMAGECS_PATTERN					11
/** @brief Color space: ICCBased. */
#define FSPDF_IMAGECS_ICCBASED_DEVICEGRAY		12
/** @brief Color space: ICCBased. */
#define FSPDF_IMAGECS_ICCBASED_DEVICERGB		13
/** @brief Color space: ICCBased. */
#define FSPDF_IMAGECS_ICCBASED_DEVICECMYK		14

/**@}*/
#endif /* _FSPDF_DEF_MACRO_IMAGEOBJECTCS_ */

#ifndef _FSPDF_DEF_STRUCTURE_GRAPHSTATE_
#define _FSPDF_DEF_STRUCTURE_GRAPHSTATE_
/**
 * @brief	Structure for PDF graph states
*/
typedef struct _FSPDF_GRAPHSTATE
{
	/** 
	 * @brief	Blend mode for transparent imaging model.
	 *
	 * @details	Please refer to macro definitions <b>FSCRT_RENDERERBLEND_XXX</b> and this should be one of these macros.
	 */
	FS_INT32	blendMode;
	/** @brief	Line width.*/
	FS_FLOAT	lineWidth;
	/** 
	 * @brief	Line join style.
	 *
	 * @details	Please refer to macro definitions <b>FSCRT_LINEJOIN_XXX</b> and this should be one of these macros.
	 */
	FS_INT32	lineJoin;
	/** @brief	The miter limit for line join.*/
	FS_FLOAT	miterLimit;
	/** 
	 * @brief	Line cap style.
	 *
	 * @details	Please refer to macro definitions <b>FSCRT_LINECAP_XXX</b> and this should be one of these macros.
	 */
	FS_INT32	lineCap;
	/** @brief	Dash phase for line dash pattern.*/
	FS_FLOAT	dashPhase;
	/** @brief	Length of the dash array.*/
	FS_INT32	dashCount;
	/** @brief	Dash array for line dash pattern.*/
	FS_FLOAT	dashArray[16];
} FSPDF_GRAPHSTATE;

#endif /* _FSPDF_DEF_STRUCTURE_GRAPHSTATE_ */

#ifndef _FSPDF_DEF_STRUCTURE_TEXTSTATE_
#define _FSPDF_DEF_STRUCTURE_TEXTSTATE_

/**
 * @brief	Structure for PDF text states
 */
typedef struct	_FSPDF_TEXTSTATE
{
	/** @brief	Font object.*/
	FSCRT_FONT	font;
	/** @brief	Font size.*/
	FS_FLOAT	fontSize;
	/** 
	 * @brief	Character spacing.
	 *
	 * @details	For horizontal writing, a positive value has the effect of expanding the distance between glyphs, 
	 *			whereas for vertical writing, a negative value has this effect.
	 */	
	FS_FLOAT	charSpace;
	/**
	 * @brief	Word spacing. It applies only to the space character, code 32.
	 *
	 * @details	For horizontal writing, a positive value has the effect of increasing the spacing between words. 
	 *			For vertical writing, a positive value decreases the spacing between words (and a negative value increases it), 
	 *			since vertical coordinates increase from bottom to top.
	 */
	FS_FLOAT	wordSpace;
	/** 
	 * @brief	Text mode.
	 *
	 * @details	Please refer to macro definitions <b>FSPDF_TEXTMODE_XXX</b> and this should be one of these macros.
	 */
	FS_INT32	textMode;
	/** @brief	X-coordinate of origin in PDF "user space".*/
	FS_FLOAT	x;
	/** @brief	Y-coordinate of origin in PDF "user space".*/
	FS_FLOAT	y;
	/** @brief	Text transformation matrix.*/
	FS_FLOAT	textMatrix[4];	
	/** @brief	Text leading. Not support yet, and it should be 0.*/
	FS_FLOAT	textLeading;
} FSPDF_TEXTSTATE;

#endif /* _FSPDF_DEF_STRUCTURE_TEXTSTATE_ */

/*******************************************************************************/
/* Page objects                                                                */
/*******************************************************************************/
/**
 * @brief	Get page objects in a PDF page.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[out]	pageObjs		Pointer to a <b>FSPDF_PAGEOBJECTS</b> handle that receives page objects.<br>
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>pageObjs</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or get page objects is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTPARSED if parameter <i>page</i> hasn't been parsed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	To call this function, parameter <i>page</i> should be parsed. 
 *			Please refer to function ::FSPDF_Page_StartParse for how to parse a PDF page.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObjs</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Page_GetPageObjects(FSCRT_PAGE page, FSPDF_PAGEOBJECTS* pageObjs);

/**
 * @brief	Get the count of page objects with specific type.
 *
 * @details	Count all page objects if parameter <i>typeFilter</i> is ::FSPDF_PAGEOBJECT_ALL.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObjs		Handle to a <b>FSPDF_PAGEOBJECTS</b> object which is the page objects. It should be valid.
 * @param[in]	typeFilter		A filter flag which specifies what type of page objects is to be counted out. 
 *								Please refer to macro definitions <b>FSPDF_PAGEOBJECT_XXX</b> and this should be one of these macros.
 * @param[out]	count			Pointer to a ::FS_INT32 object that receives count of specific type. If there's any error, it will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObjs</i> or <i>count</i> is a <b>NULL</b> pointer, or <i>typeFilter</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Parameter <i>pageObjs</i> is returned by function ::FSPDF_Page_GetPageObjects or ::FSPDF_FormXObject_GetObjects.
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
FS_RESULT	FSPDF_PageObjects_CountObjects(FSCRT_PAGE page, FSPDF_PAGEOBJECTS pageObjs, FS_INT32 typeFilter, FS_INT32* count);

/**
 * @brief	Get a page object from page objects.
 *
 * @details	The type of page object(which is to be got) is specified by parameter <i>typeFilter</i>. 
 *			If parameter <i>typeFilter</i> is ::FSPDF_PAGEOBJECT_ALL, parameter <i>index</i> is of all page objects.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObjs		Handle to a <b>FSPDF_PAGEOBJECTS</b> object which is the page objects. It should be valid.
 * @param[in]	typeFilter		A filter flag for the type of page objects.
 *								Please refer to macro definitions <b>FSPDF_PAGEOBJECT_XXX</b> and this should be one of these macros.
 * @param[in]	index			Index of page object. Range: 0 to (objcount-1). <i>objcount</i> is returned by function ::FSPDF_PageObjects_CountObjects.
 * @param[out]	pageObj			Pointer to a <b>FSPDF_PAGEOBJECT</b> handle that receives a specific page object.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObjs</i> or <i>pageObj</i> is a <b>NULL</b> pointer, or <i>typeFilter</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range.<br>
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
FS_RESULT	FSPDF_PageObjects_GetObject(FSCRT_PAGE page, FSPDF_PAGEOBJECTS pageObjs, FS_INT32 typeFilter, FS_INT32 index, FSPDF_PAGEOBJECT* pageObj);

/**
 * @brief	Enumerate page objects and retrieve a page object at a given position from page objects.
 *
 * @details	The type of page object(which is to be got) is specified by parameter <i>typeFilter</i>. 
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObjs		Handle to a <b>FSPDF_PAGEOBJECTS</b> object which is the page objects. It should be valid.
 * @param[in]	typeFilter		A filter flag for the type of page objects.
 *								Please refer to macro definitions <b>FSPDF_PAGEOBJECT_XXX</b> and this should be one of these macros.
 * @param[in,out]	position	Pointer to a <b>FSCRT_POSITION</b> object which represents the position of a page object.
 *								When this function is called, it represents the position of a page object which is to be retrieved.
 *								If call this function for first time, please pass a <b>FSPDF_POSITION</b> object with value <b>NULL</b> , in order to retrieved the first page object.<br>
 *								When this function returns, it will receive the position of next page object.
 *								If there's no more page objects to be enumerated, a <b>FSPDF_POSITION</b> object with value -1 will be returned.
 * @param[out]	pageObj			Pointer to a <b>FSPDF_PAGEOBJECT</b> handle that receives a specific page object.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_TOBECONTINUED if a page object is founded,and it's possible that there will be more.<br>
 *			::FSCRT_ERRCODE_FINISHED if no more entries can be retrieved.<br> 
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObjs</i> ,<i>position</i> or <i>pageObj</i> is a <b>NULL</b> pointer, or <i>typeFilter</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. 
 *				Do not call it for the same objects under multi-threaded environment; otherwise, the application should be synchronized.<br>
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
FS_RESULT	FSPDF_PageObjects_EnumerateObject(FSCRT_PAGE page, FSPDF_PAGEOBJECTS pageObjs, FS_INT32 typeFilter, FSCRT_POSITION* position, FSPDF_PAGEOBJECT* pageObj);

/**
 * @brief	Get index of a page object.
 *
 * @details	If parameter <i>typeFilter</i> is ::FSPDF_PAGEOBJECT_ALL, parameter <i>index</i> is of all page objects.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObjs		Handle to a <b>FSPDF_PAGEOBJECTS</b> object which is the page objects. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[in]	typeFilter		A filter flag for the type of page objects.
 *								Please refer to macro definitions <b>FSPDF_PAGEOBJECT_XXX</b> and this should be one of these macros.
 * @param[out]	index			Pointer to a ::FS_INT32 object that receives the index, which is zero-based. 
 *								If there's any error, it will be -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if no page object within specific filter is found.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObjs</i>, <i>pageObj</i> or <i>index</i> is a <b>NULL</b> pointer, 
 *			or <i>typeFilter</i> is invalid.<br>
 *			::FSCRT_ERRCODE_FORMAT if type of parameter <i>pageObj</i> doesn't match parameter <i>typeFilter</i>.<br>
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
 *				<li> <i>pageObjs</i>: this handle is short-term.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObjects_GetObjectIndex(FSCRT_PAGE page, FSPDF_PAGEOBJECTS pageObjs, FSPDF_PAGEOBJECT pageObj, FS_INT32 typeFilter, FS_INT32* index);

/**
 * @brief	Get a page object at a specific point, in PDF page coordinate system.
 *
 * @details	Get any type page object if parameter <i>typeFilter</i> is ::FSPDF_PAGEOBJECT_ALL at the point.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObjs		Handle to a <b>FSPDF_PAGEOBJECTS</b> object which is the page objects. It should be valid.
 * @param[in]	typeFilter		A filter flag for the type of page objects.
 *								Please refer to macro definitions <b>FSPDF_PAGEOBJECT_XXX</b> and this should be one of these macros.
 * @param[in]	x				X position in PDF page coordinate system.
 * @param[in]	y				Y position in PDF page coordinate system.
 * @param[in]	tolerance		Tolerance value for a page object hit detection, in point units. It should not be a negative.
 * @param[out]	pageObj			Pointer to a <b>FSPDF_PAGEOBJECT</b> handle that receives a specific page object.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObjs</i> or <i>pageObj</i> is a <b>NULL</b> pointer, or <i>typeFilter</i> is invalid, 
*			or <i>tolerance</i> is negative value.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no page object is at the specified position.<br>
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
FS_RESULT	FSPDF_PageObjects_GetObjectAtPos(FSCRT_PAGE page, FSPDF_PAGEOBJECTS pageObjs, FS_INT32 typeFilter, 
											 FS_FLOAT x, FS_FLOAT y, FS_FLOAT tolerance, 
											 FSPDF_PAGEOBJECT *pageObj);

/**
 * @brief	Get an array of all page objects at a specific point, in PDF page coordinate system.
 *
 * @details	Get any kind of page object if parameter <i>typeFilter</i> is ::FSPDF_PAGEOBJECT_ALL at the point.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	typeFilter		A filter flag for the type of page objects.
 *								Please refer to macro definitions <b>FSPDF_PAGEOBJECT_XXX</b> and this should be one of these macros.
 * @param[in]	x				X position in PDF page coordinate system.
 * @param[in]	y				Y position in PDF page coordinate system.
 * @param[in]	tolerance		Tolerance value for a page object hit detection, in point units. It should not be a negative.
 * @param[out]	pageObjList		Pointer to a ::FSCRT_ARRAY structure that receives specific page objects whose handle is FSPDF_PAGEOBJECT.
 *								Application should call function ::FSCRT_Array_Init to initialize it and ::FSCRT_Array_Clear to release it.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>pageObjList</i> is NULL, 
 *			or <i>pageObjList::dataType</i> is not ::FSCRT_VT_OBJECT_PAGEOBJECT, or <i>typeFilter</i> is invalid, 
*			or <i>tolerance</i> is negative value.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no page object is at the specified position.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. 
 *				Do not call it for the same objects under multi-threaded environment; otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObjList::data</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObjects_GetObjectListAtPos(FSCRT_PAGE page, FS_INT32 typeFilter,  FS_FLOAT x, FS_FLOAT y, FS_FLOAT tolerance, FSCRT_ARRAY* pageObjList);

/*******************************************************************************/
/* Page object                                                                 */
/*******************************************************************************/
/**
 * @brief	Get type of a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[out]	type			Pointer to a ::FS_INT32 object that receives the type. 
 *								Please refer to macro definitions <b>FSPDF_PAGEOBJECT_XXX</b> and this should be one of these macros.<br>
 *								If there's any error, it will be set -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>type</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT	FSPDF_PageObject_GetType(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FS_INT32* type);

/**
 * @brief	Get rectangle of a page object.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[out]	rect		Pointer to a ::FSCRT_RECTF structure that receives the rect.
 *							If there's any error, it will be [0 0 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>rect</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT	FSPDF_PageObject_GetRect(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FSCRT_RECTF* rect);

/**
 * @brief	Get matrix of a page object.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[out]	matrix		Pointer to a ::FSCRT_MATRIX structure that receives matrix of <i>pageObj</i>.
 *							If there's any error, it will be set [1 0 0 1 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>matrix</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>pageObj</i> has an invalid page object type.<br>
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
FS_RESULT	FSPDF_PageObject_GetMatrix(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FSCRT_MATRIX* matrix);

/**
 * @brief	Get graph states of a page object .
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj 		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[out]	graphState		Pointer to a ::FSPDF_GRAPHSTATE structure that receives the graph state.<br>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>graphState</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT	FSPDF_PageObject_GetGraphState(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FSPDF_GRAPHSTATE* graphState);

/**
 * @brief	Get color of a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj 		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[in]	isStroke		A ::FS_BOOL indicates to get stroke color if <b>TRUE</b>, or to get fill color if <b>FALSE</b>.
 * @param[out]	color			Pointer to a ::FS_ARGB object that receives color. Format: 0xAARRGGBB.<br>
 *								If there's any error, it will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>color</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT 	FSPDF_PageObject_GetColor(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FS_BOOL isStroke, FS_ARGB* color);

/**
 * @brief	Get clip rectangle of a page object .
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[out]	clipRect		Pointer to a ::FSCRT_RECTF structure that receives the clip rect.
 *								If there's any error, it will be [0 0 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>clipRect</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if there is no clipping rectangle associated to parameter <i>pageObj</i>.<br>
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
FS_RESULT	FSPDF_PageObject_GetClipRect(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FSCRT_RECTF* clipRect);

/**
 * @brief	Check whether a page object has transparency.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[out]	hasTransparency	Pointer to a ::FS_BOOL object that receives a boolean value which indicates whether <i>pageObj</i> has transparency: 
 *								<ul>
 *								<li><b>TRUE</b>: parameter <i>pageObj</i> has transparency.</li>
 *								<li><b>FALSE</b>: parameter <i>pageObj</i> has no transparency.</li>.
 *								</ul>
 *								If there's any error, it will be set <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>hasTransparency</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
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
FS_RESULT	FSPDF_PageObject_HasTransparency(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FS_BOOL* hasTransparency);

/********************************************************************************/
/* Text object                                                                  */
/********************************************************************************/
/**
 * @brief	Get text states of a text object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	textObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a text object. It should be valid.
 * @param[out]	textState		Pointer to a ::FSPDF_TEXTSTATE structure that receives text state.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>textObj</i>, <i>page</i> or <i>textState</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>textObj</i> is not a text object.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get text states of a text object for any other reason.<br>
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
FS_RESULT	FSPDF_TextObject_GetTextState(FSCRT_PAGE page, FSPDF_PAGEOBJECT textObj, FSPDF_TEXTSTATE* textState);

/**
 * @brief	Get unicode string of a text object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	textObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a text object. It should be valid.
 * @param[out]	unicodeStr		Pointer to a ::FSCRT_BSTR structure that receives the unicode string, and it should not be <b>NULL</b>. 
 *								The result will be in UTF-8.<br>
 *								If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b>,
 *								and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>textObj</i> or <i>unicodeStr</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>textObj</i> is not a text object.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If paramter <i>unicodeStr</i> is empty or has not enough memory, this function will allocate memory by calling function ::FSCRT_BStr_SetLength.<br>
 *			If it allocates memory by function ::FSCRT_BStr_SetLength, caller must call function ::FSCRT_BStr_Clear to free memory.<br>
 * 			It's better that caller prepares enough space before calling this function if possible.
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
FS_RESULT	FSPDF_TextObject_GetUnicodeString(FSCRT_PAGE page, FSPDF_PAGEOBJECT textObj, FSCRT_BSTR* unicodeStr);

/*******************************************************************************/
/* Path object                                                                 */
/*******************************************************************************/
/**
 * @brief	Get of path data of a path object .
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pathObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a path object. It should be valid.
 * @param[out]	pathData	Handle to a <b>FSCRT_PATHDATA</b> handle that receives path data.<br>
 *							When this is not used any more, application should release this handle by calling function ::FSCRT_PathData_Release.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pathObj</i> or <i>pathData</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>pathObj</i> is not a path object.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
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
FS_RESULT	FSPDF_PathObject_GetPathData(FSCRT_PAGE page, FSPDF_PAGEOBJECT pathObj, FSCRT_PATHDATA* pathData);

/**
 * @brief	Get fill mode of a path object.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pathObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a path object. It should be valid.
 * @param[out]	fillMode	Pointer to a ::FS_INT32 object that receives the fill mode. 
 *							Please refer to macro definitions <b>FSCRT_FILLMODE_XXX</b> and this should be one of these macros.<br>
 *							If there's any error, it will be set ::FSCRT_FILLMODE_NONE.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pathObj</i> or <i>fillMode</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, <i>pathObj</i> is not a path object.<br>
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
FS_RESULT	FSPDF_PathObject_GetFillMode(FSCRT_PAGE page, FSPDF_PAGEOBJECT pathObj, FS_INT32* fillMode);

/**
 * @brief	Get stroke state of a path object.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pathObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a path object. It should be valid.
 * @param[out]	isStroke	Pointer to a ::FS_BOOL object that receives a boolean value to indicate stroke state of path object:
 *							<ul>
 *							<li><b>TRUE</b>: the path object is stroked.</li>
 *							<li><b>FALSE</b>: the path object isn't stroked.</li>
 *							</ul>
 *							If there's any error, it will be set FALSE.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pathObj</i> or <i>isStroke</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT	FSPDF_PathObject_GetStrokeState(FSCRT_PAGE page, FSPDF_PAGEOBJECT pathObj, FS_BOOL* isStroke);

/*******************************************************************************/
/* Image object                                                                */
/*******************************************************************************/
/**
 * @brief	Clone a bitmap from an image object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	imageObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is an image object. It should be valid.
 * @param[out]	bitmap			Pointer to a <b>FSCRT_BITMAP</b> handle that receives a bitmap.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>imageObj</i> or <i>bitmap</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>imageObj</i> is not an image object.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_FORMAT if bitmap format of parameter <i>imageObj</i> is invalid.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to clone bitmap from an image object for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	User must call function ::FSCRT_Bitmap_Release to destroy the parameter <i>bitmap</i> and release all resources associated 
*			when no need to use <i>bitmap</i> any more.
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
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_ImageObject_CloneBitmap(FSCRT_PAGE page, FSPDF_PAGEOBJECT imageObj, FSCRT_BITMAP* bitmap);

/**
 * @brief	Get the color space for an image object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	imageObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is an image object. It should be valid.
 * @param[out]	colorspace		Pointer to a ::FS_INT32 object that receives colorspace for an image object.
 *								Please refer to macro definitions <b>FSPDF_IMAGECS_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>imageObj</i> or <i>colorspace</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>imageObj</i> is not an image object.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to clone bitmap from an image object for any other reason.<br>
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
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_ImageObject_GetColorSpace(FSCRT_PAGE page,FSPDF_PAGEOBJECT imageObj, FS_INT32* colorspace);

/**
 * @brief	Get the image stream of an image object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	imageObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is an image object. It should be valid.
 * @param[out]	stream			Pointer to a <b>FSPDF_OBJECT</b> object that receives the image stream for an image object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>imageObj</i> or <i>stream</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>imageObj</i> is not an image object.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the object don't exist.
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. 
 *				Do not call it for the same objects under multi-threaded environment; otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>imageObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_ImageObject_GetStream(FSCRT_PAGE page,FSPDF_PAGEOBJECT imageObj, FSPDF_OBJECT* stream);

/*******************************************************************************/
/* Form XObject object                                                               */
/*******************************************************************************/
/**
 * @brief	Get page objects from a Form XObject object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	formXObj		Handle to a<b>FSPDF_PAGEOBJECT</b> object which is a Form XObject object. It should be valid.
 * @param[out]	pageObjs		Pointer to a <b>FSPDF_PAGEOBJECTS</b> handle that receives the page objects.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>formXObject</i> or <i>pageObjs</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>formXObject</i> is not a Form XObject object.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
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
 *				<li> <i>pageObjs</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_FormXObject_GetObjects(FSCRT_PAGE page, FSPDF_PAGEOBJECT formXObj, FSPDF_PAGEOBJECTS* pageObjs);

/**
 * @brief	Get the stream of a form XObject.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	formXObj		Handle to a<b>FSPDF_PAGEOBJECT</b> object which is a form XObject object. It should be valid.
 * @param[out]	stream			Pointer to a <b>FSPDF_OBJECT</b> handle that receives the stream of a form XObject.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>formXObj</i> or <i>stream</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>formXObject</i> is not a Form XObject object.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the object or it's stream don't exist.
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. 
 *				Do not call it for the same objects under multi-threaded environment; otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>formXObj</i>: this handle is short-term.</li>
 *				<li> <i>stream</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormXObject_GetStream(FSCRT_PAGE page,FSPDF_PAGEOBJECT formXObj, FSPDF_OBJECT* stream);

/**
 *@brief	Get the PDF shading dictionary or stream object of a shading page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	shadingObj		Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a shading object. It should be valid.
 * @param[out]	shadingPDFObj	Pointer to a <b>FSPDF_OBJECT</b> handle that receives the shading PDF object, it would be a dictionary or stream object.<br>
 *								If there's any error, it will be set NULL.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>shadingObj</i> or <i>shadingPDFObj</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if there is no shading PDF object found.
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page, or parameter <i>shadingObj</i> is not a shading object.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>shadingObj</i>: this handle is short-term.</li>
 *				<li> <i>shadingPDFObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_ShadingObject_GetShading(FSCRT_PAGE page, FSPDF_PAGEOBJECT shadingObj, FSPDF_OBJECT* shadingPDFObj);

/*******************************************************************************/
/* Clipping                                                                    */
/*******************************************************************************/
/**
 * @brief	Get count of path clip in a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[out]	count			Pointer to a ::FS_INT32 object that receives count of path clips.
 *								If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>count</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT	FSPDF_PageObject_CountClipPath(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FS_INT32* count);

/**
 * @brief	Get a path clip from a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[in]	index			Index of path clip. Range: 0 to (clippathcount-1). <i>clippathcount</i> is returned by function ::FSPDF_PageObject_CountClipPath.
 * @param[out]	pathData		Pointer to a <b>FSCRT_PATHDATA</b> handle that receives path data.
 *								If there's any error, path data will be cleared and count of points will be 0.
 * @param[out]	fillMode		Pointer to a ::FS_INT32 object that receives the fill mode. 
 *								Please refer to macro definitions <b>FSCRT_FILLMODE_XXX</b> and this should be one of these macros.<br>
 *								If there's any error, it will be set ::FSCRT_FILLMODE_NONE.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i>, <i>pathData</i> or <i>fillMode</i> is a <b>NULL</b> pointer.
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range, or there is no path clip associated to <i>pageObj</i>.<br>
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
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_GetClipPath(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FS_INT32 index, FSCRT_PATHDATA* pathData, FS_INT32* fillMode);

/**
 * @brief	Get count of text clip in a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[out]	count			Pointer to a ::FS_INT32 object that receives count of text clips.
 *								If there's any error, it will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>count</i> is a <b>NULL</b> pointer.<br>
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
FS_RESULT	FSPDF_PageObject_CountClipText(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FS_INT32* count);

/**
 * @brief	Get a text clip from a page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object. It should be valid.
 * @param[in]	index			Index of clip text. Range: 0 to (textclipcount-1). <i>textclipcount</i> is returned by function ::FSPDF_PageObject_CountClipText.
 * @param[out]	textObj			Pointer to a <b>FSPDF_PAGEOBJECT</b> handle that receives a specific text page object.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>textObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range, or there is no text clip associated to parameter <i>pageObj</i>.<br>
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
 *				<li> <i>textObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_PageObject_GetClipText(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FS_INT32 index, FSPDF_PAGEOBJECT* textObj);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFPAGEOBJECTS */

#endif /* _FSPDF_PAGEOBJECTS_R_H_ */
