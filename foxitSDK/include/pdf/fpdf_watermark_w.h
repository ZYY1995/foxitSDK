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
 * @file	fpdf_watermark_w.h
 * @brief	Header file for \ref FPDFWATERMARK "PDF Watermark" module of Foxit PDF SDK.
 * @details	This header file provides access to PDF watermark related functionality.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Create a watermark from a text, image, bitmap or PDF page. </li>
 *			<li>2. Retrieve watermark size. </li>
 *			<li>3. Insert a watermark into a PDF page. </li>
 *			<li>4. Remove all watermarks from a PDF page. </li>
 *			<li>5. Remove a watermark by index from a PDF page. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Annotation Add-on</b> explicitly.
 */

#ifndef _FSPDF_WATERMARK_W_H_
#define _FSPDF_WATERMARK_W_H_

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

#ifndef _FSPDF_DEF_MACRO_WATERMARKPOS_
#define _FSPDF_DEF_MACRO_WATERMARKPOS_
/**
 * @name	Macro Definitions for Watermark Positions.
 */
/**@{*/

/** @brief	Watermark position: top left.*/
#define FSPDF_WATERMARKPOS_TOPLEFT			0
/** @brief	Watermark position: top center.*/
#define FSPDF_WATERMARKPOS_TOPCENTER		1
/** @brief	Watermark position: top right.*/
#define FSPDF_WATERMARKPOS_TOPRIGHT			2
/** @brief	Watermark position: center left.*/
#define FSPDF_WATERMARKPOS_CENTERLEFT		3
/** @brief	Watermark position: center.*/
#define FSPDF_WATERMARKPOS_CENTER			4
/** @brief	Watermark position: center right.*/
#define FSPDF_WATERMARKPOS_CENTERRIGHT		5
/** @brief	Watermark position: bottom left.*/
#define FSPDF_WATERMARKPOS_BOTTOMLEFT		6
/** @brief	Watermark position: bottom center.*/
#define FSPDF_WATERMARKPOS_BOTTOMCENTER		7
/** @brief	Watermark position: bottom right.*/
#define FSPDF_WATERMARKPOS_BOTTOMRIGHT		8

/**@}*/
#endif /* _FSPDF_DEF_MACRO_WATERMARKPOS_ */

#ifndef _FSPDF_DEF_MACRO_WATERMARKFLAG_
#define _FSPDF_DEF_MACRO_WATERMARKFLAG_
/**
 * @name	Macro Definitions for Watermark Setting Flags.
 */
/**@{*/

/** @brief	If set and insert a watermark as page content (default).*/
#define	FSPDF_WATERMARKFLAG_ASPAGECONTENTS	0
/** @brief	If set and insert a watermark as an annotation.*/
#define FSPDF_WATERMARKFLAG_ASANNOT			1
/** @brief	If set, show watermark above other page content.*/
#define FSPDF_WATERMARKFLAG_ONTOP			2
/** @brief	If set but do not print a watermark.*/
#define FSPDF_WATERMARKFLAG_NOPRINT			4
/** @brief	If set but do not display a watermark.*/
#define FSPDF_WATERMARKFLAG_INVISIBLE		8

/**@}*/
#endif /* _FSPDF_DEF_MACRO_WATERMARKFLAG_ */

#ifndef _FSPDF_DEF_MACRO_WATERMARK_FONTSTYLE_
#define _FSPDF_DEF_MACRO_WATERMARK_FONTSTYLE_
/**
 * @name	Macro Definitions for Watermark Text Font Style.
 */
/**@{*/

/** @brief	Watermark font style: normal.*/
#define FSPDF_WATERMARK_FONTSTYLE_NORMAL		0
/** @brief	Watermark font style: with underline.*/
#define FSPDF_WATERMARK_FONTSTYLE_UNDERLINE		1

/**@}*/
#endif /* _FSPDF_DEF_MACRO_WATERMARK_FONTSTYLE_ */

#ifndef _FSPDF_DEF_MACRO_WATERMARK_TEXTALIGNMENT_
#define _FSPDF_DEF_MACRO_WATERMARK_TEXTALIGNMENT_
/**
 * @name	Macro Definitions for a watermark alignment Mode.
 */
/**@{*/

/** @brief	Text watermark alignment: left.*/	
#define FSPDF_WATERMARK_TEXTALIGNMENT_LEFT		0
/** @brief	Text watermark alignment: center.*/
#define FSPDF_WATERMARK_TEXTALIGNMENT_CENTER	1
/** @brief	Text watermark alignment: right.*/	
#define FSPDF_WATERMARK_TEXTALIGNMENT_RIGHT		2

/**@}*/
#endif /* _FSPDF_DEF_MACRO_WATERMARK_TEXTALIGNMENT_ */

#ifndef _FSPDF_DEF_STRUCTURE_WATERMARK_SETTINGS_
#define _FSPDF_DEF_STRUCTURE_WATERMARK_SETTINGS_

/**
 * @brief	Structure for watermark settings.
 * @note	It is used for all four kinds of watermark.
 */ 

typedef struct _FSPDF_WATERMARK_SETTINGS
{
	/** 
	 * @brief	Position mode. 
	 *
	 * @details	Please refer to macro definitions <b>FSPDF_WATERMARKPOS_XXX</b> and this should be one of these macros.
	 */
	FS_DWORD 	position;
	/** @brief	Horizontal offset, in points. */
	FS_FLOAT 	offsetX;
	/** @brief	Vertical offset, in points. */
	FS_FLOAT 	offsetY;
	/** 
	 * @brief	Watermark flags. 
	 *
	 * @details	Please refer to macro definitions <b>FSPDF_WATERMARKFLAG_XXX</b> and this should be one or a combination of these macros.
	 */
	FS_DWORD 	flags;
	/** @brief	Horizontal scale coefficient. */	
	FS_FLOAT 	scaleX;
	/** @brief	Vertical scale coefficient. It should be greater than 0.001f. */	
	FS_FLOAT 	scaleY;
	/** @brief	Rotation angle in degrees. It should be greater than 0.001f. */	
	FS_FLOAT 	rotation;
	/** @brief	Opacity in percents. 0 for transparent and 100 for opaque. */
	FS_INT32 	opacity;
} FSPDF_WATERMARK_SETTINGS;

#endif /* _FSPDF_DEF_STRUCTURE_WATERMARK_SETTINGS_ */

#ifndef _FSPDF_DEF_STRUCTURE_WATERMARK_TEXTPROPERTIES_
#define _FSPDF_DEF_STRUCTURE_WATERMARK_TEXTPROPERTIES_

/**
 * @brief	Structure for watermark text properties.
 * @note	It is used only for a text watermark.
 */ 

typedef struct _FSPDF_WATERMARK_TEXTPROPERTIES
{
	/** @brief	Font object used for text. Not support using the function ::FSCRT_Font_CreateFromFile to create font object currently.*/
	FSCRT_FONT 	font;
	/** @brief	Font size in points. */
	FS_FLOAT 	fontSize;
	/** @brief	Text color. It's constructed by 0xAARRGGBB. Alpha component is ignored.*/
	FS_ARGB		color;
	/** 
	 * @brief	Font style, specifies if a text is underlined.
	 * 
	 * @details	It should be one of the followings: <br>
				<ul>
				<li>::FSPDF_WATERMARK_FONTSTYLE_NORMAL</li>
				<li>::FSPDF_WATERMARK_FONTSTYLE_UNDERLINE</li>
				</ul>
	*/
	FS_DWORD 	fontStyle;
	/** @brief	Space between vertical center of lines, in line heights.*/
	FS_FLOAT 	lineSpace;
	/** 
	 * @brief	Text horizontal alignment.
	 *
	 * @details	It should be one of the followings: <br>
				<ul>
				<li>::FSPDF_WATERMARK_TEXTALIGNMENT_LEFT</li>
				<li>::FSPDF_WATERMARK_TEXTALIGNMENT_CENTER</li>
				<li>::FSPDF_WATERMARK_TEXTALIGNMENT_RIGHT</li>
				</ul>
	*/
	FS_INT32 	alignment;
} FSPDF_WATERMARK_TEXTPROPERTIES;

#endif /* _FSPDF_DEF_STRUCTURE_WATERMARK_TEXTPROPERTIES_ */

/********************************************************************************/
/* Create and insert a watermark into pages                                       */
/*******************************************************************************/
/**
 * @brief	Create a text watermark.
 *
 * @param[in]	document		Handle to <b>FSCRT_DOCUMENT</b> object, and the PDF document object which the created watermark will be used for.
 * @param[in]	text			Pointer to a text string, it should be a valid pointer to ::FSCRT_BSTR. 
 *								It specifies the content of watermark.
 * @param[in]	properties		Pointer to a ::FSPDF_WATERMARK_TEXTPROPERTIES structure containing text specific properties for this watermark.
 * @param[in]	settings		Pointer to a ::FSPDF_WATERMARK_SETTINGS structure containing layout settings for this watermark.
 * @param[out]	watermark		Pointer to a <b>FSPDF_WATERMARK</b> handle that receives the watermark handle. <br>
 *								If no need to use this handle any more, please call function ::FSPDF_Watermark_Release to release it.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>text</i>, <i>properties</i>, <i>settings</i>, or <i>watermark</i> is <b>NULL</b>, or parameter <i>text</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or creating watermark is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if the current PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is an invalid type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>watermark</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
*/
FS_RESULT	FSPDF_Watermark_CreateFromText(FSCRT_DOCUMENT document, const FSCRT_BSTR* text, const FSPDF_WATERMARK_TEXTPROPERTIES* properties, 
										   const FSPDF_WATERMARK_SETTINGS* settings, FSPDF_WATERMARK* watermark);

/**
 * @brief	Create a bitmap watermark.
 *
 * @param[in]	document		Handle to <b>FSCRT_DOCUMENT</b> object, and the PDF document object which the created watermark will be used for.
 * @param[in]	bitmap			Handle to <b>FSCRT_BITMAP</b> object which is to be shown as watermark.
 * @param[in]	settings		Pointer to a ::FSPDF_WATERMARK_SETTINGS structure that contains layout settings for this watermark.
 * @param[out]	watermark		Pointer to a <b>FSPDF_WATERMARK</b> handle that receives the watermark handle. <br>
 *								If no need to use this handle any more, please call function ::FSPDF_Watermark_Release to release it.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i>, <i>bitmap</i>, <i>settings</i>, or <i>watermark</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or creating watermark is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if the current PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is an invalid type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				<li> <i>watermark</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Watermark_CreateFromBitmap(FSCRT_DOCUMENT document, FSCRT_BITMAP bitmap, 
											 const FSPDF_WATERMARK_SETTINGS* settings, FSPDF_WATERMARK* watermark);

/**
 * @brief	Create an image watermark.
 *
 * @details	The parameter <i>watermark</i> can only be set in one frame, 
 *			so callers shall call ::FSCRT_Image_LoadFrame first to obtain a frame.
 *
 * @param[in]	document		Handle to the <b>FSCRT_DOCUMENT</b> object, and a PDF document object which the created watermark will be used for.
 * @param[in]	image			Handle to the <b>FSCRT_IMAGE</b> object in which a frame will be shown as a watermark .
 * @param[in]	settings		Pointer to a ::FSPDF_WATERMARK_SETTINGS structure which contains layout settings for this watermark.
 * @param[out]	watermark		Pointer to a <b>FSPDF_WATERMARK</b> handle that receives a watermark handle. <br>
 *								If no need to use this handle any more, please call function ::FSPDF_Watermark_Release to release it.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i>, <i>image</i>, <i>settings</i>, or <i>watermark</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or creating watermark is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if the current PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is an invalid type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if callers don't load any one frame of the <i>image</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	A image file should be released after saving a document.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li> 
 *				<li> <i>watermark</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Watermark_CreateFromImage(FSCRT_DOCUMENT document, FSCRT_IMAGE image, 
											const FSPDF_WATERMARK_SETTINGS* settings, FSPDF_WATERMARK* watermark);

/**
 * @brief	Create a page watermark.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object, and a PDF document object which the created watermark will be used for.
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page shown as watermark.
 * @param[in]	settings		Pointer to a ::FSPDF_WATERMARK_SETTINGS structure which contains layout settings for this watermark.
 * @param[out]	watermark		Pointer to a <b>FSPDF_WATERMARK</b> handle that receives a watermark handle. <br>
 *								If no need to use this handle any more, please call function ::FSPDF_Watermark_Release to release it.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i>, <i>page</i>, <i>settings</i>, or <i>watermark</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or creating watermark is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if the current PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the <i>document</i> is an invalid type or the  <i>page</i> is an invalid type.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the <i>page</i> is not parsed when being converted to a watermark.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li> 
 *				<li> <i>watermark</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Watermark_CreateFromPage(FSCRT_DOCUMENT document, FSCRT_PAGE page, 
										   const FSPDF_WATERMARK_SETTINGS* settings, FSPDF_WATERMARK* watermark);

/**
 * @brief	Insert a watermark into a specific page.
 *
 * @details	The page content should have been already parsed. And there's no need to call function ::FSPDF_Page_LoadAnnots at first 
 *			for watermarks which are annotations.
 *
 * @param[in]	watermark		Handle to a <b>FSPDF_WATERMARK</b> object which is a water mark object.
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter parameter <i>watermark</i>, or <i>page</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>page</i> is an invalid type.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter<i>page</i> is not parsed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> For <i>watermark</i> created by function ::FSPDF_Watermark_CreateFromText, ::FSPDF_Watermark_CreateFromBitmap, ::FSPDF_Watermark_CreateFromImage,
 *					<i>watermark</i> is long-term recoverable.</li>
 *				<li> For <i>watermark</i> created by function ::FSPDF_Watermark_CreateFromPage, 
 *					<i>watermark</i> is long-term partially recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Watermark_InsertToPage(FSPDF_WATERMARK watermark, FSCRT_PAGE page);

/**
 * @brief	Release a watermark object.
 *
 * @param[in]	watermark		Handle to <b>FSPDF_WATERMARK</b> object which is a water mark object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>watermark</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> For <i>watermark</i> created by function ::FSPDF_Watermark_CreateFromText, ::FSPDF_Watermark_CreateFromBitmap, ::FSPDF_Watermark_CreateFromImage,
 *					<i>watermark</i> is long-term recoverable.</li>
 *				<li> For <i>watermark</i> created by function ::FSPDF_Watermark_CreateFromPage, 
 *					<i>watermark</i> is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Watermark_Release(FSPDF_WATERMARK watermark);

/**
 * @brief	Remove all watermarks from a specific page.
 *
 * @details	The page content should have been already parsed. And there's no need to call function ::FSPDF_Page_LoadAnnots at first 
 *			for watermarks which are annotations.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>page</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>page</i> is an invalid type.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter<i>page</i> is not parsed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
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
FS_RESULT	FSPDF_Page_RemoveWatermarks(FSCRT_PAGE page);

/**
 * @brief	Remove a watermark by index from a PDF page and it doesn't include the SDK trial watermark.
 *
 * @details	The page content should have been already parsed. And there's no need to call function ::FSPDF_Page_LoadAnnots at first 
 *			for watermarks which are annotations.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[in]	index		A zero-based index of watermark to be got. Range: 0 to (WatermarkCount-1).
 *							<i>WatermarkCount</i> is returned by function ::FSPDF_Watermark_GetCount with the same <i>page</i>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if <i>index</i> is out of range or there are no watermarks.<br>
 *			::FSCRT_ERRCODE_NOTPARSED if the parameter<i>page</i> is not parsed.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs internally.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if the watermark cannot be removed because of any other reason.<br>
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
FS_RESULT	FSPDF_Watermark_Remove(FSCRT_PAGE page, FS_INT32 index);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFWATERMARK */

#endif /* _FSPDF_WATERMARK_W_H_ */

