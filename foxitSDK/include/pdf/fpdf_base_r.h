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
 * @file	fpdf_base_r.h
 * @brief	Header file for \ref FPDFBASE "PDF Base" module of Foxit PDF SDK.
 * @details	This header file defines some basic or common support for PDF.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Initialize or finalize PDF module. </li>
 *			<li>2. Macro definitions for PDF permissions. </li>
 *			<li>3. Other common PDF definitions. </li>
 *			<li>4. PDF rendering context. </li>
 *			<li>5. Destination definitions. </li>
 *			<li>6. Access to trigger actions. </li>
 *			<li>7. Access and modify attachment. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> explicitly.
 */

#ifndef _FSPDF_BASE_R_H_
#define _FSPDF_BASE_R_H_

/** 
 * @defgroup	FPDFBASE PDF Base
 * @brief		Definitions for PDF basic and common process.<br>
 *				Definitions and functions in this module are included in fpdf_base_r.h.<br>
 *				Module: PDFBase<br>
 *				License Identifier: PDFBase/All<br>
 *				Available License Right: Unnecessary
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. PDF module:
 *					<ul>
 *					<li>a. Initialize or finalize PDF module.</li>
 *					<li>b. Note: PDF module should be initialized at first before using any PDF features.</li>
 *					</ul>
 *				</li>
 *				<li>2. Common definitions: involve PDF permissions, page areas, alignment and default appearance.
 *					   These definitions are used by features in PDF module.</li>
 *				<li>3. PDF rendering context:
 *					<ul>
 *					<li>a. Create a rendering context, and set its properties.</li>
 *					<li>b. PDF rendering context is used to render PDF page contents.
 *						   It uses a renderer to render PDF page objects into a device. Please refer to header file fs_renderer_r.h for renderer.</li>
 *					</ul>
 *				</li>
 *				<li>4. PDF Actions:
 *					<ul>
 *					<li>a. Definitions for PDF actions, initialize or clear action data object. </li>
 *					<li>b. Actions are executed when a trigger is fired. 
 *						   Application can retrieve action data by functions in the current version of Foxit PDF SDK, and execute actions according to types.
 *						   Document, bookmark, page, annotation and form field have their own actions.</li>
 *					<li>c. Reference: section 8.5 and 8.6.4 in PDF Reference 1.7 describe how to deal with PDF actions.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* PDF module                                                                  */
/*******************************************************************************/
/**
 * @brief	Initialize PDF module.
 *
 * @details	This is the first function that should be called if the user needs any PDF process.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_INVALIDMANAGER if Foxit PDF SDK manager is not initialized.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_ERROR if the function cannot initialize PDF module for any reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	Call function ::FSCRT_PDFModule_Finalize to destroy PDF module if there's no need to use any process of PDF.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PDFModule_Initialize();

/**
 * @brief	Finalize PDF module.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_INVALIDMANAGER if Foxit PDF SDK manager is not initialized.<br>
 * 			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	Function ::FSCRT_PDFModule_Initialize should be called to initialize PDF module, 
 *			and when there's no need to use PDF module anymore, this function should be called.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PDFModule_Finalize();

/*******************************************************************************/
/* Common definitions                                                          */
/*                                                                             */
/* PDF permissions, page areas, alignment, default appearance                  */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_PERMISSION_
#define _FSPDF_DEF_MACRO_PERMISSION_
/**
 * @name	Macro Definitions for PDF Document Permissions
 * @note 	According to PDF Reference, a 32-bit integer is used to represent permissions.<br>
 * 			Bits in permission value, 1-2 bits must be zero, 7-8, 13-32 bits must be 1, and leave other unused bits to 0.
 */
/**@{*/

/**
 * @brief	Bit 3. Print PDF document with normal mode.
 *
 * @details	If the user wants to print a higher quality level of PDF document, set it with bit 12 together.<br>
 * 			Please refer to macro ::FSPDF_PERMISSION_PRINT_HIGH.
 */
#define FSPDF_PERMISSION_PRINT			0x0004
/**
 * @brief	Bit 4. Modify PDF contents.
 *
 * @details	if this bit is set, the user can modify contents of PDF document by operations other than
 * 			those controlled by bits 6, 9, and 11.
 */
#define FSPDF_PERMISSION_MODIFY			0x0008
/**
 * @brief	Bit 5. Extract PDF contents.
 *
 * @details	if this bit is set, the user can copy or otherwise extract text and graphics
 * 			from the document by operations other than that controlled by bit 10.
 */
#define FSPDF_PERMISSION_EXTRACT		0x0010
/**
 * @brief	Bit 6. Operate text annotations and fill in interactive form fields.
 *
 * @details	If bit 4 is also set, user can create or modify interactive form fields (including signature fields).
 */
#define FSPDF_PERMISSION_ANNOTFORM		0x0020
/**
 * @brief	Bit 9. Fill PDF form.
 *
 * @details	if this bit is set, user can fill in interactive form fields (including signature fields),
 * 			even if bit 6 is clear. 
 */
#define FSPDF_PERMISSION_FILLFORM		0x0100
/**
 * @brief	Bit 10. Disabilities support.
 *
 * @details	If this bit set, user can extract text and graphics in support of accessibility
 *			to users with disabilities or for other purposes. 
 */
#define FSPDF_PERMISSION_EXTRACTACCESS	0x0200
/**
 * @brief	Bit 11. Assemble PDF document.
 *
 * @details	This bit enables to assemble the document (insert, rotate, or delete pages
 * 			and create bookmarks or thumbnail images), regardless if bit 4 is set or not. 
 */
#define FSPDF_PERMISSION_ASSEMBLE		0x0400
/**
 * @brief	Bit 12. Print PDF document with higher qualities.
 *
 * @details	If this bit is clear (and bit 3 is set), printing is limited to a low-level
 * 			representation of the appearance, possibly of degraded quality. 
 */
#define FSPDF_PERMISSION_PRINT_HIGH		0x0800

/**@}*/
#endif /* _FSPDF_DEF_MACRO_PERMISSION_ */

#ifndef _FSPDF_DEF_MACRO_PAGEBOX_
#define _FSPDF_DEF_MACRO_PAGEBOX_
/**
 * @name	Macro Definitions for Page Boundary Box
 * @note	For some purposes, PDF defines a set of page boxes.<br>
 * 			User can select a proper page box according to application intentions.
 */
/**@{*/

/** 
 * @brief	Media Box for page boundary.
 * 
 * @details	The boundary of the physical medium on which page is to be displayed or printed. 
 */
#define FSPDF_PAGEBOX_MEDIABOX			0
/** 
 * @brief	Crop Box for page boundary.
 *
 * @details	The region to which the contents of page are to be clipped (cropped) while displaying or printing. 
 */
#define FSPDF_PAGEBOX_CROPBOX			1
/** 
 * @brief	Trim Box for page boundary.
 * 
 * @details	The region to which the contents of page should be clipped while outputting in a production environment. 
 */
#define FSPDF_PAGEBOX_TRIMBOX			2
/** 
 * @brief	Art Box for page boundary.
 *
 * @details	The intended dimensions of a finished page after trimming. 
 */
#define FSPDF_PAGEBOX_ARTBOX			3
/** 
 * @brief	Bleed Box for page boundary.
 *
 * @details	The extent of page's meaningful content (including potential white space) as intended by page's creator. 
 */
#define FSPDF_PAGEBOX_BLEEDBOX			4

/**@}*/
#endif /* _FSPDF_DEF_MACRO_PAGEBOX_ */

#ifndef _FSPDF_DEF_MACRO_ALIGNMENT_
#define _FSPDF_DEF_MACRO_ALIGNMENT_
/**
 * @name	Macro Definitions for Alignments (horizontal).
 */
/**@{*/

/** @brief	Left alignment. */
#define FSPDF_ALIGNMENT_LEFT		0
/** @brief	Center alignment. */
#define FSPDF_ALIGNMENT_CENTER		1
/** @brief	Right alignment. */
#define FSPDF_ALIGNMENT_RIGHT		2	

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ALIGNMENT_ */

#ifndef _FSPDF_DEF_MACRO_DEFAULTAPPEARANCE_
#define _FSPDF_DEF_MACRO_DEFAULTAPPEARANCE_
/**
 * @name	Macro Definitions for Settings of Default Appearance
 */
/**@{*/

/** @brief	The font flag of default appearance. */
#define FSPDF_DEFAULTAPPEARANCE_FONT			0x0001
/** @brief	The text color flag of default appearance. */
#define FSPDF_DEFAULTAPPEARANCE_TEXTCOLOR		0x0002
/** @brief	The text matrix flag of default appearance flag. */
#define FSPDF_DEFAULTAPPEARANCE_TEXTMATRIX		0x0004

/**@}*/
#endif /* _FSPDF_DEF_MACRO_DEFAULTAPPEARANCE_ */

#ifndef _FSPDF_DEF_STRUCTURE_DEFAULTAPPEARANCE_
#define _FSPDF_DEF_STRUCTURE_DEFAULTAPPEARANCE_

/**
 * @brief	Structure for default appearance.
 * @note	It may be used for form and annotation.
 */ 

typedef struct _FSPDF_DEFAULTAPPEARANCE
{
	/** 
	 * @brief	Flags of default appearance. 
	 *
	 * @details	It can be one or a combination of the following flags: <br>
	 *			<ul>
	 *			<li>::FSPDF_DEFAULTAPPEARANCE_FONT</li>
	 *			<li>::FSPDF_DEFAULTAPPEARANCE_TEXTCOLOR</li>
	 *			<li>::FSPDF_DEFAULTAPPEARANCE_TEXTMATRIX</li>
	 *			</ul>
	 */
	FS_DWORD		flags;
	/** @brief	Reserved. */
	FS_DWORD		reserved;
	/** 
	 * @brief	Font object of default appearance. 
	 *
	 * @details	Meaningful only when FSPDF_DEFAULTAPPEARANCE::flags contains ::FSPDF_DEFAULTAPPEARANCE_FONT. 
	 */
	FSCRT_FONT		font;
	/** 
	 * @brief	Font size of default appearance. This should not be negative.
	 * 
	 * @details	Meaningful only when FSPDF_DEFAULTAPPEARANCE::flags contains ::FSPDF_DEFAULTAPPEARANCE_FONT. 
	 */
	FS_FLOAT		fontSize;
	/** 
	 * @brief	Text color of default appearance. Format: 0xAARRGGBB.
	 *
	 * @details	Meaningful only when FSPDF_DEFAULTAPPEARANCE::flags contains ::FSPDF_DEFAULTAPPEARANCE_TEXTCOLOR. 
	 */
	FS_ARGB			textColor;

	/** 
	 * @brief	Text matrix of default appearance.
	 *
	 * @details	Meaningful only when FSPDF_DEFAULTAPPEARANCE::flags contains ::FSPDF_DEFAULTAPPEARANCE_TEXTMATRIX. 
	 */
	FSCRT_MATRIX	textMatrix;
} FSPDF_DEFAULTAPPEARANCE;

#endif /* _FSPDF_DEF_STRUCTURE_DEFAULTAPPEARANCE_ */

/*******************************************************************************/
/* Handles Definition                                                          */
/*******************************************************************************/
#ifndef _FSPDF_DEF_HANDLE_OBJECT_
#define _FSPDF_DEF_HANDLE_OBJECT_

/** @brief	Handle type to PDF object. */
FSCRT_DEFINEHANDLE(FSPDF_OBJECT);

#endif /* _FSPDF_DEF_HANDLE_OBJECT_ */

#ifndef _FSPDF_DEF_HANDLE_ATTACHMENT_
#define _FSPDF_DEF_HANDLE_ATTACHMENT_

/** @brief	Handle type to PDF attachment. */
FSCRT_DEFINEHANDLE(FSPDF_ATTACHMENT);

#endif /* _FSPDF_DEF_HANDLE_ATTACHMENT_ */

/*******************************************************************************/
/* PDF rendering context                                                       */
/*******************************************************************************/
#ifndef _FSPDF_DEF_HANDLE_RENDERCONTEXT_
#define _FSPDF_DEF_HANDLE_RENDERCONTEXT_

/** @brief	Handle type to PDF rendering context. */
FSCRT_DEFINEHANDLE(FSPDF_RENDERCONTEXT);

#endif /* _FSPDF_DEF_HANDLE_RENDERCONTEXT_ */

#ifndef _FSPDF_DEF_MACRO_RENDEROPTION_
#define _FSPDF_DEF_MACRO_RENDEROPTION_
/**
 * @name	Macro Definitions for Rendering Options
 * @note	Currently, only one rendering option is defined.
 */
/**@{*/

/** @brief	Rendering option of color mode. */
#define FSPDF_RENDEROPTION_COLORMODE 	0

/**@}*/
#endif /* _FSPDF_DEF_MACRO_RENDEROPTION_ */

#ifndef _FSPDF_DEF_MACRO_COLORMODE_
#define _FSPDF_DEF_MACRO_COLORMODE_
/**
 * @name	Macro Definitions for Rendering Option of Color Mode
 */
/**@{*/

/** @brief	Normal color mode. */
#define FSPDF_COLORMODE_NORMAL			0
/** @brief	Gray color mode: map colors to background/foreground. */
#define FSPDF_COLORMODE_GRAY			1
/** @brief	Two color mode: map white/black to background/foreground, other unchanged. */
#define FSPDF_COLORMODE_TWOCOLOR		2

/**@}*/
#endif /* _FSPDF_DEF_MACRO_COLORMODE_ */

#ifndef _FSCRT_DEF_STRUCTURE_RENDEROPTIONPARAM_COLORMODE_
#define _FSCRT_DEF_STRUCTURE_RENDEROPTIONPARAM_COLORMODE_

/**
 * @brief	Structure for render option parameters of color mode.
 *
 * @note	While calling function ::FSPDF_RenderContext_SetOption, 
 *			set parameter <i>option</i> to ::FSPDF_RENDEROPTION_COLORMODE and pass an object of this structure to parameter <i>params</i>
 */ 
typedef struct _FSPDF_RENDEROPTIONPARAM_COLORMODE
{
	/** 
	 * @brief	Color mode. 
	 *
	 * @details	Please refer to macro definitions <b>FSPDF_COLORMODE_XXX</b> and this should be one of these macros. 
	 */
	FS_INT32	colorMode;
	/** @brief	Foreground color. Format: 0xAARRGGBB. */
	FS_ARGB		foreColor;
	/** @brief	Background color. Format: 0xAARRGGBB. */
	FS_ARGB		backColor;
} FSPDF_RENDEROPTIONPARAM_COLORMODE;

#endif /* _FSCRT_DEF_STRUCTURE_RENDEROPTIONPARAM_COLORMODE_ */

#ifndef _FSPDF_DEF_MACRO_RENDERCONTEXTFLAG_
#define _FSPDF_DEF_MACRO_RENDERCONTEXTFLAG_
/**
 * @name	Macro Definitions for Render Flags
 * @note	Pass one or a combination of the following flags to parameter <i>flags</i> when call function ::FSPDF_RenderContext_SetFlags.
 */
/**@{*/

/** @brief	Set if page annotations are to be rendered together. */
#define FSPDF_RENDERCONTEXTFLAG_ANNOT					0x0001
/**
 * @brief	Drop page content objects while rendering page automatically.
 *
 * @details	This will make the most complicated pages renderable within very limited memory.<br>
 * 			<b>HOWEVER</b>, after rendering a page, page content objects will not be used any more, and user has to re-parse page for any process on page contents.
 * @note	Do not use this flag when caller shares one rendering context object between multi-threads.
 */
#define FSPDF_RENDERCONTEXTFLAG_DROPOBJECTS				0x0002
/** @brief	Set if the form fields(widgets) are not to be rendered together. */
#define FSPDF_RENDERCONTEXTFLAG_NOWIDGET				0x0004
/**
 * @brief	Set if no need to rotate or scale annotation icon.
 *
 * @details	In PDF, "<b>Text</b>" and "<b>FileAttachment</b>" annotations show as icons.
 */
#define FSPDF_RENDERCONTEXTFLAG_NOTTRANSFORMICON		0x0008
/** 
 * @brief	Limit image cache size. 
 *
 * @details	This will help to save memory for a large amount of image data. 
 */
#define FSPDF_RENDERCONTEXTFLAG_LIMITEDIMAGECACHE		0x0010
/** @brief	This flag indicates not to render signatures. */
#define FSPDF_RENDERCONTEXTFLAG_NOSIGNATURE				0x0020
/** @brief	If this flag is set, only apply those content objects which allow to output to printer. */
#define FSPDF_RENDERCONTEXTFLAG_OCGPRINT				0x0100
/** @brief	If this flag is set, only apply those content objects which allow to output for design mode. */
#define FSPDF_RENDERCONTEXTFLAG_OCGDESIGN				0x0200
/** @brief	If this flag is set, only apply those content objects which allow to output for exportation. */
#define FSPDF_RENDERCONTEXTFLAG_OCGEXPORT				0x0400

/**@}*/
#endif /* _FSPDF_DEF_MACRO_RENDERCONTEXTFLAG_ */

/**
 * @brief	Create a PDF rendering context.
 * 
 * @param[out]	pdfRenderContext	Pointer to a <b>FSPDF_RENDERCONTEXT</b> handle that receives a new PDF rendering context object.
 *									If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>pdfRenderContext</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_ERROR if the function cannot create the PDF render context for any reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	PDF rendering context is designed specially to ensure rendering PDF contents on rendering engine.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_Create(FSPDF_RENDERCONTEXT* pdfRenderContext);

/**
 * @brief	Release a PDF rendering context.
 * 
 * @param[in]	pdfRenderContext	Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF rendering context object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>pdfRenderContext</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_Release(FSPDF_RENDERCONTEXT pdfRenderContext);

/**
 * @brief	Set flags to a rendering context.
 * 
 * @param[in]	pdfRenderContext	Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF rendering context object.
 * @param[in]	flags				Rendering flags value. All undefined bits are omitted.<br>
 *									Please refer to macro definitions <b>FSPDF_RENDERCONTEXTFLAG_XXX</b> and this can be one or a combination of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>pdfRenderContext</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_SetFlags(FSPDF_RENDERCONTEXT pdfRenderContext, FS_DWORD flags);

/**
 * @brief	Set a transformation matrix to a rendering context.
 * 
 * @param[in]	pdfRenderContext	Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF rendering context object.
 * @param[in]	matrix				Pointer to a ::FSCRT_MATRIX structure which gives a transformation matrix while rendering PDF contents.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>pdfRenderContext</i> or <i>matrix</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_SetMatrix(FSPDF_RENDERCONTEXT pdfRenderContext, const FSCRT_MATRIX *matrix);

/**
 * @brief	Set a halftone limit to a rendering context.
 *
 * @details By default, Foxit PDF SDK displays all bitmaps using down-sampling, 
 *			which means if an image is shrink onto the screen, only part of pixels will be picked and displayed. 
 *			This saves a lot of calculation, especially for big images with millions of pixels. However the display quality will be bad. <br>
 *			In order to reach a balance between performance and quality, application can use this function to set a limit: <br>
 *			if the count of pixels in an image is more than this limit, then Foxit PDF SDK will use down-sampling for quick drawing; <br>
 *			otherwise, if the image has less pixels, Foxit PDF SDK will use halftone for better quality.
 * 
 * @param[in]	pdfRenderContext	Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF rendering context object.
 * @param[in]	halftoneLimit		A halftone limit to a ::FS_INT32 value.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>pdfRenderContext</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_ERROR if the function cannot set the halftone limit into PDF render context for any reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	By default, halftone limit is 60M in the desktop platform.<br>
 *			If <i>halftoneLimit</i> which set by users is less than 60M, halftone limit is still 60M in the desktop platform.<br>
 * 
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_SetHalftoneLimit(FSPDF_RENDERCONTEXT pdfRenderContext, FS_INT32 halftoneLimit);

/**
 * @brief	Set option parameters to a rendering context.
 * 
 * @param[in]	pdfRenderContext	Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF rendering context object.
 * @param[in]	option				A rendering option identity code to a ::FS_DWORD value. Please refer to macro definitions <b>FSPDF_RENDEROPTION_XXX</b> and this should be one of these macros.
 * @param[in]	params				Pointer to ::FS_LPVOID object which indicates rendering parameters for parameter <i>option</i>.<br>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>pdfRenderContext</i> or <i>params</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	Only structure ::FSPDF_RENDEROPTION_COLORMODE option can be used at present, and parameter <i>params</i> should point to a structure ::FSPDF_RENDEROPTIONPARAM_COLORMODE.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_SetOption(FSPDF_RENDERCONTEXT pdfRenderContext, FS_DWORD option, FS_LPVOID params);

#ifndef _FSPDF_DEF_HANDLE_LAYERCONTEXT_
#define _FSPDF_DEF_HANDLE_LAYERCONTEXT_

/** @brief	Handle type to PDF layer context. */
FSCRT_DEFINEHANDLE(FSPDF_LAYERCONTEXT);
#endif /* _FSPDF_DEF_HANDLE_LAYERCONTEXT_ */

/**
 * @brief	Set layer context to render context handle.
 * 
 * @param[in]	pdfRenderContext	Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF rendering context object.
 * @param[in]	layerContext		Handle to a <b>FSPDF_LAYERCONTEXT</b> object which is a PDF layer context object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>pdfRenderContext</i> or <i>layerContext</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_ERROR if the function cannot set the layer context into PDF render context for any reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	In order to render one layer when to render PDF contents on a rendering context, 
 *			user should call this function to set the layer context to render context.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				<li> <i>layerContext</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_SetLayerContext(FSPDF_RENDERCONTEXT pdfRenderContext, FSPDF_LAYERCONTEXT layerContext);

/*******************************************************************************/
/* Destination                                                                 */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_ZOOM_
#define _FSPDF_DEF_MACRO_ZOOM_
/**
 * @name	Macro Definitions for Zoom Mode for The Destination
 */
/**@{*/

/** @brief	A specific zoom factor is used. */
#define FSPDF_ZOOM_FACTOR				1
/** @brief	Fit the whole page on the screen. */
#define FSPDF_ZOOM_FITPAGE				2
/** @brief	Fit the width of the page on the screen. */
#define FSPDF_ZOOM_FITWIDTH				3
/** @brief	Fit the height of the page on the screen. */
#define FSPDF_ZOOM_FITHEIGHT			4
/** @brief	Fit a particular rectangle on the screen. */
#define FSPDF_ZOOM_FITRECT				5
/** @brief	Fit the whole content of page on the screen. */
#define FSPDF_ZOOM_FITCONTENT			6
/** @brief	Fit the content width of page on the screen. */
#define FSPDF_ZOOM_FITCONTENTWIDTH		7
/** @brief	Fit the content height of page on the screen. */
#define FSPDF_ZOOM_FITCONTENTHEIGHT		8

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ZOOM_ */

#ifndef _FSPDF_DEF_STRUCTURE_DESTDATA_
#define _FSPDF_DEF_STRUCTURE_DESTDATA_

/** @brief	Structure for a destination data. */
typedef struct _FSPDF_DESTDATA
{
	/** @brief	A zero-based index for page.*/
	FS_INT32		pageIndex;
	/** 
	 * @brief	Zoom mode. 
	 *
	 * @details	Please refer to macro definitions <b>FSPDF_ZOOM_XXX</b> and this should be one of these macros. 
	 */
	FS_INT32		zoomMode;
	/**
	 * @brief	Params used to specify the position and zoom factor inside the page.
	 *
	 * @details	According to parameter <i>zoomMode</i>, different members of the params are used:<br>
	 *			<ul>
	 *			<li>::FSPDF_ZOOM_FACTOR:			0: left, 1: top, 2: zoom factor</li>
	 *			<li>::FSPDF_ZOOM_FITPAGE:			none</li>
	 *			<li>::FSPDF_ZOOM_FITWIDTH:			0: top</li>
	 *			<li>::FSPDF_ZOOM_FITHEIGHT:			0: left</li>
	 *			<li>::FSPDF_ZOOM_FITRECT:			0: left, 1: bottom, 2: right, 3: top</li>
	 *			<li>::FSPDF_ZOOM_FITCONTENT:		none</li>
	 *			<li>::FSPDF_ZOOM_FITCONTENTWIDTH:	0: top</li>
	 *			<li>::FSPDF_ZOOM_FITCONTENTHEIGHT:	0: left</li>
	 *			</ul>
	 *
	 * @note	When FSPDF_DESTDATA::zoomMode is ::FSPDF_ZOOM_FACTOR and <i>params[2]</i> is 0, it means the zoom factor(which is current used) should not be changed.
	 */
	FS_FLOAT		params[4];
}FSPDF_DESTDATA;

#endif /* _FSPDF_DEF_STRUCTURE_DESTDATA_ */

/*******************************************************************************/
/* Actions                                                                     */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_ACTION_
#define _FSPDF_DEF_MACRO_ACTION_
/**
 * @name	Macro Definitions for Action Type
 */
/**@{*/

/** @brief	Unsupported action type. */
#define FSPDF_ACTION_UNSUPPORTED	0
/** @brief	Go to a destination within current document. */
#define FSPDF_ACTION_GOTO			1
/** @brief	Go to a destination within another document. */
#define FSPDF_ACTION_REMOTEGOTO		2
/** @brief	Go to a destination within embedded another document. */
#define FSPDF_ACTION_EMBEDDEDGOTO	3
/** @brief	Universal Resource Identifier, including web pages and other Internet based resources. */
#define FSPDF_ACTION_URI			4
/** @brief	Launch an application or open a file. */
#define FSPDF_ACTION_LAUNCH			5
/** @brief	Run a javascript. */
#define FSPDF_ACTION_JAVASCRIPT		6
/** @brief	Hide or show one or more annotations. */
#define FSPDF_ACTION_HIDE			7
/** @brief	Run a named action. */
#define FSPDF_ACTION_NAMED			8
/** @brief	Transmit the names and values of selected interactive form fields. */
#define FSPDF_ACTION_SUBMITFORM		9
/** @brief	Reset selected interactive form fields to their default values. */
#define FSPDF_ACTION_RESETFORM		10
/** @brief	Import Forms Data Format (FDF) data into the document's interactive form. */
#define FSPDF_ACTION_IMPORTDATA		11
/** @brief	Play a multimedia.*/
#define FSPDF_ACTION_RENDITION		12

/**@}*/
#endif /* _FSPDF_DEF_MACRO_ACTION_ */

#ifndef _FSPDF_DEF_MACRO_TRIGGER_DOC_
#define _FSPDF_DEF_MACRO_TRIGGER_DOC_
/**
 * @name	Macro Definitions for Trigger Actions of Document
 */
/**@{*/

/** @brief	A JavaScript action to be performed after opening a document. */
#define FSPDF_TRIGGER_DOC_DO			0
/** @brief	A JavaScript action to be performed before closing a document. */
#define FSPDF_TRIGGER_DOC_WC			1
/** @brief	A JavaScript action to be performed before saving a document. */
#define FSPDF_TRIGGER_DOC_WS			2
/** @brief	A JavaScript action to be performed after saving a document. */
#define FSPDF_TRIGGER_DOC_DS			3
/** @brief	A JavaScript action to be performed before printing a document. */
#define FSPDF_TRIGGER_DOC_WP			4
/** @brief	A JavaScript action to be performed after printing a document. */
#define FSPDF_TRIGGER_DOC_DP			5

/**@}*/
#endif /* _FSPDF_DEF_MACRO_TRIGGER_DOC_ */

#ifndef _FSPDF_DEF_MACRO_TRIGGER_FORMFIELD_
#define _FSPDF_DEF_MACRO_TRIGGER_FORMFIELD_
/**
 * @name	Macro Definitions for Trigger Actions of Form Field
 */
/**@{*/

/**
 * @brief	A JavaScript action to be performed when the user types a keystroke into a text field or combo box or modifies the selection in a scrollable list box.
 *
 * @details	This action can check the keystroke for validity and reject or modify it.
 */
#define FSPDF_TRIGGER_FORMFIELD_KS		0 
/**
 * @brief	A JavaScript action to be performed before the field is formatted to display its current value.
 *
 * @details	This action can modify the field's value before formatting.
 */
#define FSPDF_TRIGGER_FORMFIELD_WF		1 
/**
 * @brief	A JavaScript action to be performed when the field's value is changed.
 *
 * @details	This action can check the new value for validity.
 */
#define FSPDF_TRIGGER_FORMFIELD_WV		2 
/** @brief	A JavaScript action to be performed to recalculate the value of this field when that of another field changes. */
#define FSPDF_TRIGGER_FORMFIELD_FC		3 

/**@}*/
#endif /* _FSPDF_DEF_MACRO_TRIGGER_FORMFIELD_ */

#ifndef _FSPDF_DEF_MACRO_TRIGGER_PAGE_
#define _FSPDF_DEF_MACRO_TRIGGER_PAGE_
/**
 * @name	Macro Definitions for Trigger Actions of Page
 */
/**@{*/

/** @brief	An action to be performed when the page is opened. */
#define FSPDF_TRIGGER_PAGE_PO			0 
/** @brief	An action to be performed when the page is closed. */
#define FSPDF_TRIGGER_PAGE_PC			1 

/**@}*/
#endif /* _FSPDF_DEF_MACRO_TRIGGER_PAGE_ */

#ifndef _FSPDF_DEF_MACRO_TRIGGER_ANNOT_
#define _FSPDF_DEF_MACRO_TRIGGER_ANNOT_
/**
 * @name	Macro Definitions for Trigger Actions of Annotation
 */
/**@{*/

/** brief	An action to be performed when the cursor enters the annotation's active area. */
#define FSPDF_TRIGGER_ANNOT_CE			0 
/** brief	An action to be performed when the cursor exits the annotation's active area. */
#define FSPDF_TRIGGER_ANNOT_CX			1 
/** brief	An action to be performed when the mouse button is pressed inside the annotation's active area. */
#define FSPDF_TRIGGER_ANNOT_MD			2 
/** brief	An action to be performed when the mouse button is released inside the annotation's active area. */
#define FSPDF_TRIGGER_ANNOT_MU			3 
/** brief	An action to be performed when the annotation receives the input focus. */
#define FSPDF_TRIGGER_ANNOT_FO			4 
/** brief	An action to be performed when the annotation loses the input focus. */
#define FSPDF_TRIGGER_ANNOT_FL			5 
/** brief	An action to be performed when the page containing the annotation is opened. */
#define FSPDF_TRIGGER_ANNOT_PO			6 
/** brief	An action to be performed when the page containing the annotation is closed. */
#define FSPDF_TRIGGER_ANNOT_PC			7 
/** brief	An action to be performed when the page containing the annotation becomes visible in the viewer application's user interface. */
#define FSPDF_TRIGGER_ANNOT_PV			8 
/** brief	An action to be performed when the page containing the annotation is no longer visible in the viewer application's user interface. */
#define FSPDF_TRIGGER_ANNOT_PI			9 

/**@}*/
#endif /* _FSPDF_DEF_MACRO_TRIGGER_ANNOT_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_

/** @brief	Structure for an action data. */
typedef struct _FSPDF_ACTIONDATA
{
	/** 
	 * @brief	Action type. 
	 *
	 * @details	Please refer to macro <b>FSPDF_ACTION_XXX</b> and this should be one of these macros. 
	 */
	FS_INT32		actionType;
	/**
	 * @brief	An action data. 
	 *
	 * @details	According to parameter <i>actionType</i>, different members of the data are used:<br>
	 *			It should be one of the following: <br>
	 *			<ul>
	 *			<li>::FSPDF_ACTION_UNSUPPORTED:		<b>NULL</b></li>
	 *			<li>::FSPDF_ACTION_GOTO:			::FSPDF_ACTIONDATA_GOTO</li>
	 *			<li>::FSPDF_ACTION_REMOTEGOTO:		::FSPDF_ACTIONDATA_REMOTEGOTO</li>
	 *			<li>::FSPDF_ACTION_EMBEDDEDGOTO:	::FSPDF_ACTIONDATA_EMBEDDEDGOTO</li>
	 *			<li>::FSPDF_ACTION_URI:				::FSPDF_ACTIONDATA_URI</li>
	 *			<li>::FSPDF_ACTION_LAUNCH:			::FSPDF_ACTIONDATA_LAUNCH</li>
	 *			<li>::FSPDF_ACTION_JAVASCRIPT:		::FSPDF_ACTIONDATA_JAVASCRIPT</li>
	 *			<li>::FSPDF_ACTION_HIDE:			::FSPDF_ACTIONDATA_HIDE</li>
	 *			<li>::FSPDF_ACTION_NAMED:			::FSPDF_ACTIONDATA_NAMED</li>
	 *			<li>::FSPDF_ACTION_SUBMITFORM:		::FSPDF_ACTIONDATA_SUBMITFORM</li>
	 *			<li>::FSPDF_ACTION_RESETFORM:		::FSPDF_ACTIONDATA_RESETFORM</li>
	 *			<li>::FSPDF_ACTION_IMPORTDATA:		::FSPDF_ACTIONDATA_IMPORTDATA</li>
	 *			</ul>
	 *
	 * @note	If the application wants to use the function FSPDF_ActionData_Clear() to release this structure data, 
	 *			FSPDF_ACTIONDATA::actionData should be allocated by function ::FSCRT_Memory_Alloc().
	 *			Otherwise, the application should release ::FSPDF_ACTIONDATA by itself.
	 */
	FS_LPVOID		actionData;
} FSPDF_ACTIONDATA;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_GOTO_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_GOTO_

/** @brief	Structure for action type ::FSPDF_ACTION_GOTO. */
typedef struct _FSPDF_ACTIONDATA_GOTO
{
	/** @brief	Destination data. */
	FSPDF_DESTDATA	destData;
} FSPDF_ACTIONDATA_GOTO;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_GOTO_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_REMOTEGOTO_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_REMOTEGOTO_

/** 
 * @brief	Structure for action type ::FSPDF_ACTION_REMOTEGOTO.
 *
 * @note	If this is a named destination, the field <i>destData</i> will not be used.
 */
typedef struct _FSPDF_ACTIONDATA_REMOTEGOTO
{
	/** 
	 * @brief	File name that remote to, encoded in UTF-8. 
	 *
	 * @note	If FSCRT_BSTR::str of <i>fileName</i> is a const string, 
	 *			the application should set this to NULL before callinging function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	 */
	FSCRT_BSTR		fileName;
	/** 
	 * @brief	Destination name, in UTF-8.
	 *
	 * @note	If FSCRT_BSTR::str of <i>destName</i> is a const string, 
	 *			the application should set this to NULL before callinging function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
 	 */
	FSCRT_BSTR		destName;
	/** 
	 * @brief	Destination data. 
	 *
	 * @note	If this structure is treated as a named destination, this will not be used.
	 */
	FSPDF_DESTDATA	destData;
} FSPDF_ACTIONDATA_REMOTEGOTO;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_REMOTEGOTO_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_EMBEDDEDGOTO_TARGET_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_EMBEDDEDGOTO_TARGET_

/** 
 * @brief	Structure for target of ::FSPDF_ACTIONDATA_EMBEDDEDGOTO.
 *
 * @note	Specify path information to a target document. 
 *			Each target specifies one element in the full path to the target and may have nested target
 *			specifying additional elements.
 */
typedef struct _FSPDF_ACTIONDATA_EMBEDDEDGOTO_TARGET
{
	/**
	 * @brief	Pointer to a ::FSPDF_ACTIONDATA_EMBEDDEDGOTO_TARGET structure which specifies additional path information to the target document.
	 *
	 * @details	If this entry is absent (NULL), the current document is the target file containing the destination.
	 */
	struct _FSPDF_ACTIONDATA_EMBEDDEDGOTO_TARGET*	next;
	/** 
	 * @brief	Relationship between current document and the target document, in UTF-8.
	 *			Valid values are "P"(the target is the parent of the current document) and
	 *			"C"(the target is a child of the current document).
	 *
	 * @note	If FSCRT_BSTR::str of <i>relationship</i> is a const string, 
	 *			application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
 	 */
	FSCRT_BSTR		relationship;
	/**
	 * @brief	Name of the file in the <i>EmbeddedFiles</i> name tree, in UTF-8.
	 *
	 * @details	Please refer to section 3.6.3 in PDF Reference 1.7.
 	 *
	 * @note	If FSCRT_BSTR::str of <i>filename</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
 	 */
	FSCRT_BSTR		filename;
	/** 
	 * @brief	A named destination in target document that provides the page index of the file attachment annotation, in UTF-8.
 	 *
	 * @note	If FSCRT_BSTR::str of <i>destname</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
 	 */
	FSCRT_BSTR		destname;
	/** 
	 * @brief	Value of NM in the annotation dictionary, in UTF-8.
	 *
	 * @note	If FSCRT_BSTR::str of <i>annotname</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	 */
	FSCRT_BSTR		annotname;
	/** 
	 * @brief	Page index(zero-based) in target document containing the file attachment annotation. 
	 *
	 * @details	It should use <i>destname</i> when parameter <i>pageindex</i> is -1.
	 */
	FS_INT32		pageindex;
	/** 
	 * @brief	Annotation index(zero-based) of the page specified by parameter <i>pageindex</i>.
	 *
	 * @details	It should use <i>annotname</i> when parameter <i>annotindex</i> is -1.
	 */
	FS_INT32		annotindex;
}FSPDF_ACTIONDATA_EMBEDDEDGOTO_TARGET;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_EMBEDDEDGOTO_TARGET_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_EMBEDDEDGOTO_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_EMBEDDEDGOTO_

/** 
 * @brief	Structure for action type ::FSPDF_ACTION_EMBEDDEDGOTO.
 *
 * @note	If this is a named destination, the field <i>destData</i> will not be used.
 */
typedef struct _FSPDF_ACTIONDATA_EMBEDDEDGOTO
{
	/** @brief	Pointer to a ::FSPDF_ACTIONDATA_EMBEDDEDGOTO_TARGET structure which specifies path information to the target document.*/
	FSPDF_ACTIONDATA_EMBEDDEDGOTO_TARGET*	target;
	/** @brief	Handle to a <b>FSPDF_ATTACHMENT</b> object which is the root document of the target. */
	FSPDF_ATTACHMENT	attachment;
	/** 
	 * @brief	Destination data. 
	 *
	 * @note	If this structure is treated as a named destination, this will not be used.
	 */
	FSPDF_DESTDATA		destData;
	/** 
	 * @brief	Destination name, in UTF-8.
	 *
	 * @note	If FSCRT_BSTR::str of <i>destName</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	 */
	FSCRT_BSTR			destName;
	/** @brief	Whether a new window should be opened or not. */
	FS_BOOL				newWindow;
} FSPDF_ACTIONDATA_EMBEDDEDGOTO;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_EMBEDDEDGOTO_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_URI_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_URI_

/** @brief	Structure for action type ::FSPDF_ACTION_URI. */
typedef struct _FSPDF_ACTIONDATA_URI
{
	/** 
	 * @brief	URL address, in UTF-8.
	 *
	 * @note	If FSCRT_BSTR::str of <i>url</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	 */
	FSCRT_BSTR		url;
	/**
	 * @brief	Whether to track the mouse position when the URI is resolved.
	 *
	 * @details	Please refer to section 8.5.3 in PDF Reference 1.7.
	 */
	FS_BOOL			mapPosition;
} FSPDF_ACTIONDATA_URI;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_URI_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_LAUNCH_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_LAUNCH_

/** @brief	Structure for action type ::FSPDF_ACTION_LAUNCH. */
typedef struct _FSPDF_ACTIONDATA_LAUNCH
{
	/** @brief	(Reserved, not support currently) Handle to a <b>FSPDF_ATTACHMENT</b> object which is the application or document to be launched. */
	FSPDF_ATTACHMENT	attachment;
	/**
	 * @brief	File name, in UTF-8.
	 *
	 * @note	If FSCRT_BSTR::str of <i>fileName</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	 */
	FSCRT_BSTR			fileName;
	/** 
	 * @brief	Default path, in UTF-8.
	 *
	 * @note	If FSCRT_BSTR::str of <i>defaultPath</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	 */
	FSCRT_BSTR			defaultPath;
	/** 
	 * @brief	Operation to perform, in UTF-8.
	 *
	 * @details	It should be one of the following: <br>
	 *			<ul>
	 *			<li>open:	Open a document.</li>
	 *			<li>print:	Print a document.</li>
	 *			</ul>
	 *
	 * @note	If FSCRT_BSTR::str of <i>operation</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	 */
	FSCRT_BSTR			operation;
	/** 
	 * @brief	A parameter string to be passed to the application, in UTF-8.
	 *
	 * @note	If FSCRT_BSTR::str of <i>parameters</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
 	 */
	FSCRT_BSTR			parameters;
	/** @brief	Whether a new window should be opened. */
	FS_BOOL				newWindow;
} FSPDF_ACTIONDATA_LAUNCH;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_LAUNCH_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_JAVASCRIPT_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_JAVASCRIPT_

/** @brief	Structure for action type ::FSPDF_ACTION_JAVASCRIPT. */
typedef struct _FSPDF_ACTIONDATA_JAVASCRIPT
{
	/**
	 * @brief	Javascript contents, in UTF-8.
	 *
	 * @note	If FSCRT_BSTR::str of <i>javascript</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	 */
	FSCRT_BSTR		javascript;
} FSPDF_ACTIONDATA_JAVASCRIPT;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_JAVASCRIPT_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_HIDE_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_HIDE_

/** @brief	Structure for action type ::FSPDF_ACTION_HIDE. */
typedef struct _FSPDF_ACTIONDATA_HIDE
{
	 /** 
	  * @brief	Pointer to an array which are names of fields to be included or excluded.
	  *
	  * @note	Each element in this array should be in UTF-8.<br>
	  *			If FSCRT_BSTR::str of <i>namedAction</i> is a const string, 
	  *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	  *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	  */ 
	FSCRT_BSTR*		fields; 
	/** @brief	Count of elements in <i>fields</i> array. */ 
	FS_INT32		count;
	/** @brief	Indicate to hide annotations or show them. */
	FS_BOOL			hide;
} FSPDF_ACTIONDATA_HIDE;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_HIDE_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_NAMED_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_NAMED_

/** @brief	Structure for action type ::FSPDF_ACTION_NAMED. */
typedef struct _FSPDF_ACTIONDATA_NAMED
{
	/** 
	 * @brief	A text string which is an action name, in UTF-8.
	 *
	 * @note	If FSCRT_BSTR::str of <i>namedAction</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	 */
	FSCRT_BSTR		namedAction;
} FSPDF_ACTIONDATA_NAMED;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_NAMED_ */

#ifndef _FSPDF_DEF_MACRO_SUBMITFORM_FLAGS_
#define _FSPDF_DEF_MACRO_SUBMITFORM_FLAGS_
/**
 * @name	Macro Definitions for Submit-Form Action Flags
 * @note 	According to PDF Reference, a 32-bit integer is used to represent submit-form action flags.<br>
 * 			Bits in flags value, leave unused bits to be 0.
 */
/**@{*/

/**
 * @brief	Bit 1. Include fields to submit.
 */
#define FSPDF_SUBMITFORMFLAGS_INCLUDE						0x0001
/**
 * @brief	Bit 2. Submit fields regardless of whether they have a value.
 *
 * @note 	For fields without a value, only the field name is transmitted. 
 */
#define FSPDF_SUBMITFORMFLAGS_INCLUDENOVALUEFIELDS			0x0002
/**
 * @brief	Bit 3. Field names and values are submitted in HTML Form format.
 *
 * @note	Meaningful only if the SubmitPDF and XFDF flags are clear.<br> 
 * 			If clear, they are submitted in Forms Data Format (FDF).
 */
#define FSPDF_SUBMITFORMFLAGS_EXPORTFORMAT					0x0004
/**
 * @brief	Bit 4. Field names and values are submitted using an HTTP GET request.
 *
 * @note	If clear, they are submitted using a POST request.<br>
 *			This flag is meaningful only when the ExportFormat flag is set.
 */
#define FSPDF_SUBMITFORMFLAGS_GETMETHOD						0x0008
/**
 * @brief	Bit 5. Coordinates of the mouse are transmitted as part of the form data.
 */
#define FSPDF_SUBMITFORMFLAGS_SUBMITCOORDINATES				0x0010
/**
 * @brief	Bit 6. Field names and values are submitted as XFDF.
 */
#define FSPDF_SUBMITFORMFLAGS_XFDF							0x0020
/**
 * @brief	Bit 7. Submitted FDF file includes contents as contained in differences entry in the FDF dictionary.
 *
 * @note	Meaningful only when the form is being submitted in Forms Data Format.
 */
#define FSPDF_SUBMITFORMFLAGS_INCLUDEAPPENDSAVES			0x0040
/**
 * @brief	Bit 8. Submitted FDF file includes all markup annotations in underlying PDF document.
 *
 * @note	Meaningful only when the form is being submitted in Forms Data Format. 
 */
#define FSPDF_SUBMITFORMFLAGS_INCLUDEANNOTATIONS			0x0080
/**
 * @brief	Bit 9. The document is submitted as PDF.
 */
#define FSPDF_SUBMITFORMFLAGS_SUBMITPDF						0x0100
/**
 * @brief	Bit 10. Any submitted field values representing dates are converted to the standard format.
 */
#define FSPDF_SUBMITFORMFLAGS_CANONICALFORMAT				0x0200
/**
 * @brief	Bit 11. Only those markup annotations whose T entry matches the name of the current user are being submitted.
 */
#define FSPDF_SUBMITFORMFLAGS_EXCLNONUSERANNOTS				0x0400
/**
 * @brief	Bit 12. Submitted FDF excludes F entry.
 */
#define FSPDF_SUBMITFORMFLAGS_EXCLFKEY						0x0800
/**
 * @brief	Bit 14. F entry of submitted FDF is an embedded file stream.
 */
#define FSPDF_SUBMITFORMFLAGS_EMBEDFORM						0x2000

/**@}*/
#endif /* _FSPDF_DEF_MACRO_SUBMITFORM_FLAGS_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_SUBMITFORM_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_SUBMITFORM_

/** @brief	Structure for action type ::FSPDF_ACTION_SUBMITFORM. */
typedef struct _FSPDF_ACTIONDATA_SUBMITFORM
{
	/**
	 * @brief	Handle to a <b>FSPDF_ATTACHMENT</b> object to which the form data is submitted.
	 *
	 * @details	This field is a URL address commonly. Call function ::FSPDF_Attachment_GetFileName to retrieve URL address.
	 */
	FSPDF_ATTACHMENT	attachment;
	/** 
	 * @brief	Pointer to an array which are names of fields.  
 	 *
	 * @note	Each element in this array should be in UTF-8.<br>
	 *			If FSCRT_BSTR::str of <i>namedAction</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	 */
	FSCRT_BSTR*			fields;
	/** @brief	Count of elements in <i>fields</i> array. */
	FS_INT32			count;
	/** 
	 * @brief	A set of flags specifying various characteristics of the action. 
	 *
	 * @details	Please refer to macro definitions <b>FSPDF_SUBMITFORMFLAGS_XXX</b> and this can be one or a combination of these macros. 
	 */
	FS_DWORD			flags;
} FSPDF_ACTIONDATA_SUBMITFORM;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_SUBMITFORM_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_RESETFORM_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_RESETFORM_

/** @brief	Structure for action type ::FSPDF_ACTION_RESETFORM. */
typedef struct _FSPDF_ACTIONDATA_RESETFORM
{
	/** 
	 * @brief	Pointer to an array which are names of fields to be included or excluded.
	 *
	 * @note	Each element in this array should be in UTF-8.<br>
	 *			If FSCRT_BSTR::str of <i>namedAction</i> is a const string, 
	 *			the application should set this to NULL before calling function ::FSPDF_ActionData_Clear() to release resources of action data.
	 *			Otherwise, the application should release action data by itself, instead of using function ::FSPDF_ActionData_Clear().
	 */
	FSCRT_BSTR*		fields;
	/** @brief	Count of elements in <i>fields</i> array. */
	FS_INT32		count;
	/**
	 * @brief	Flags specify including or excluding fields.
	 *
	 * @details	It should be one of the following values at present: <br>
	 *			<ul>
	 *			<li>0:	Include fields to reset.</li>
	 *			<li>1:	Exclude fields from resetting.</li>
	 *			</ul>
	 */
	FS_DWORD		flags;
} FSPDF_ACTIONDATA_RESETFORM;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_RESETFORM_ */

#ifndef _FSPDF_DEF_STRUCTURE_ACTIONDATA_IMPORTDATA_
#define _FSPDF_DEF_STRUCTURE_ACTIONDATA_IMPORTDATA_

/** @brief	Structure for action type ::FSPDF_ACTION_IMPORTDATA. */
typedef struct _FSPDF_ACTIONDATA_IMPORTDATA
{
	/** @brief	Handle to a <b>FSPDF_ATTACHMENT</b> object from which form data is imported. */
	FSPDF_ATTACHMENT	attachment;
} FSPDF_ACTIONDATA_IMPORTDATA;

#endif /* _FSPDF_DEF_STRUCTURE_ACTIONDATA_IMPORTDATA_ */

/**
 * @brief	Initialize PDF action data.
 *
 * @param[in]	actionData		Pointer to a ::FSPDF_ACTIONDATA structure which to be set.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>actionData</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_ActionData_Init(FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Clear PDF action data.
 *
 * @param[in]	actionData		Pointer to a ::FSPDF_ACTIONDATA structure which to be cleared.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>actionData</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_ActionData_Clear(FSPDF_ACTIONDATA* actionData);

/*******************************************************************************/
/* PDF Attachment			                                                   */
/*******************************************************************************/
/**
 * @brief	Create an attachment object.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	attachment		Pointer to a <b>FSPDF_ATTACHMENT</b> handle to receive the newly created PDF attachment.
 *								If there's any error, it will be <b>NULL</b>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid type of PDF document.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>document</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	When create a new attachment object, function ::FSPDF_Attachment_SetFile or ::FSPDF_Attachment_SetFileName should be called first 
 *			to initialize attachment object before setting other properties of it.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_Create(FSCRT_DOCUMENT document, FSPDF_ATTACHMENT* attachment);

/**
 * @brief	Release a attachment object.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	attachment		Handle to a <b>FSPDF_ATTACHMENT</b> object which is to be released.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_Release(FSCRT_DOCUMENT document, FSPDF_ATTACHMENT attachment);

/**
 * @brief	Check whether an attachment is an embedded file or not.
 * 
 * @details	The PDF attachment can take either of two forms.
 *			<ul>
 *			<li>
 *				A simple file specification gives just the name of the target file in a standard format, 
 *				independent of the naming conventions of any particular file system.<br>
 *				It can take the form of either a string or a dictionary.<br>
 *			</li>
 *			<li>
 *				A full file specification includes information related to one or more specific file systems.<br>
 *				It can only be represented as a dictionary.
 *			</li>
 *			</ul>
 *
 * @param[in]	attachment		Handle to a <b>FSPDF_ATTACHMENT</b> object returned by function ::FSPDF_Attachments_GetAttachment.
 * @param[out]	embedded		Pointer to a ::FS_BOOL object that receives whether the attachment is an embedded file or not.
 *								If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>embedded</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_IsEmbedded(FSPDF_ATTACHMENT attachment, FS_BOOL* embedded);

/**
 * @brief	Get file name of an attachment.
 *
 * @param[in]	attachment		Handle to a <b>FSPDF_ATTACHMENT</b> object returned by function ::FSPDF_Attachments_GetAttachment.
 * @param[out]	fileName		Pointer to a ::FSCRT_BSTR structure that receives file name of the attachment. It would be in UTF-8 format.<br>
 *								If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> while calling this function, 
 *								and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>fileName</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot get file name of attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_GetFileName(FSPDF_ATTACHMENT attachment, FSCRT_BSTR* fileName);

/**
 * @brief	Set the file name of an attachment.
 *
 * @details	For attachment created by function ::FSPDF_Attachment_Create, this function is used to initialize the newly created attachment object before setting other properties of it.<br>
 *			For attachment got from PDF document, this function is used to set new file name to this attachment.<br>
 *			ATTENTION: for initializing newly created attachment, only need to call one of funcions ::FSPDF_Attachment_SetFileName or ::FSPDF_Attachment_SetFile.
 *
 * @param[in]	attachment		Handle to a valid <b>FSPDF_ATTACHMENT</b> object which is a PDF attachment object.
 * @param[in]	fileName		Pointer to a ::FSCRT_BSTR structure which specifies file name of the attachment. It should be in UTF-8 format.
 * @param[in]	isURL			A ::FS_BOOL that specifies whether the set file is a remote file.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>fileName</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting file name of attachment is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot set file name of the attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_SetFileName(FSPDF_ATTACHMENT attachment, const FSCRT_BSTR* fileName, FS_BOOL isURL);

/**
 * @brief	Get description of an attachment.
 * 
 * @details	Descriptive text associated with the attachment. It is used for files in the EmbeddedFiles name tree.
 *
 * @param[in]	attachment		Handle to a <b>FSPDF_ATTACHMENT</b> object returned by function ::FSPDF_Attachments_GetAttachment.
 * @param[out]	description		Pointer to a ::FSCRT_BSTR structure that receives the description of attachment. It would be in UTF-8 format.<br>
 *								If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> while calling this function, 
 *								and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>description</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_GetDescription(FSPDF_ATTACHMENT attachment, FSCRT_BSTR* description);

/**
 * @brief	Set the description of an attachment.
 * 
 * @details	Descriptive text associated with the attachment. It is used for files in the EmbeddedFiles name tree.
 *
 * @param[in]	attachment		Handle to a valid <b>FSPDF_ATTACHMENT</b> object which is a PDF attachment object.
 * @param[in]	description		Pointer to a ::FSCRT_BSTR structure which specifies the description of the attachment. 
 *								It should be in UTF-8 format.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>description</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting description of attachment is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot set the description of the attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note 	For "FileAttachment" annotation, viewer applications should call function ::FSPDF_Annot_SetContents to set the descriptive text which relates to the attached file.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_SetDescription(FSPDF_ATTACHMENT attachment, const FSCRT_BSTR* description);

/**
 * @brief	Get the size of an attachment.
 * 
 * @details	The size of an embedded attachment is in bytes.
 *
 * @param[in]	attachment		Handle to a <b>FSPDF_ATTACHMENT</b> object returned by function ::FSPDF_Attachments_GetAttachment.
 * @param[out]	size			Pointer to a ::FSCRT_FILESIZE object that receives the size of attachment.
 							In order to keep forward compatibilities, use 64-bits here.<br>
 *							If there's any error, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>size</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot get size of attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_GetSize(FSPDF_ATTACHMENT attachment, FSCRT_FILESIZE* size);

/**
 * @brief	Get creation date and time of an attachment.
 *
 * @param[in]	attachment		Handle to a <b>FSPDF_ATTACHMENT</b> object returned by function ::FSPDF_Attachments_GetAttachment.
 * @param[out]	dt				Pointer to ::FSCRT_DATETIMEZONE structure that receives creation date and time.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>dt</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_FORMAT if the creation date and time of parameter <i>attachment</i> has a wrong format.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot get creation date of attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_GetCreationDateTime(FSPDF_ATTACHMENT attachment, FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Set the creation date and time of an attachment.
 * 
 * @details	The creation date represents when the attachment was created.
 *
 * @param[in]	attachment		Handle to a valid <b>FSPDF_ATTACHMENT</b> object which is a PDF attachment object.
 * @param[in]	dt				Pointer to ::FSCRT_DATETIMEZONE structure which specifies the creation date.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>dt</i> is a <b>NULL</b> pointer, or parameter <i>dt</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting creating date of attachment is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot set creation date of the attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_SetCreationDateTime(FSPDF_ATTACHMENT attachment, const FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Get the last modification date and time of an attachment.
 *
 * @param[in]	attachment		Handle to a <b>FSPDF_ATTACHMENT</b> object returned by function ::FSPDF_Attachments_GetAttachment.
 * @param[out]	dt				Pointer to ::FSCRT_DATETIMEZONE structure that receives the last modification date and time.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>dt</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_FORMAT if last modification date and time of parameter <i>attachment</i> has a wrong format.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot get modified date of attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_GetModifiedDateTime(FSPDF_ATTACHMENT attachment, FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Set the modification date of an attachment.
 * 
 * @details	The modification date represents when the attachment was last modified.
 *
 * @param[in]	attachment		Handle to a valid <b>FSPDF_ATTACHMENT</b> object which is a PDF attachment object.
 * @param[in]	dt				Pointer to ::FSCRT_DATETIMEZONE structure which specifies the modification date.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>dt</i> is a <b>NULL</b> pointer, or parameter <i>dt</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting modification date of attachment is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot set modified date of the attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_SetModifiedDateTime(FSPDF_ATTACHMENT attachment, const FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Get an attachment's checksum.
 *
 * @details	The checksum refers to checksum of the bytes of an uncompressed embedded file.<br>
 *			The checksum is calculated by applying the standard MD5 message-digest algorithm (described in Internet RFC 1321, 
 *			the MD5 Message-Digest Algorithm; see the Bibliography) to the bytes of the embedded file stream.
 *
 * @param[in]	attachment		Handle to a <b>FSPDF_ATTACHMENT</b> object returned by function ::FSPDF_Attachments_GetAttachment.
 * @param[out]	checksum		Pointer to a ::FSCRT_BSTR structure that receives the checksum of the attachment.<br>
 *								If there's any error, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> while calling this function, 
 *								and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>checksum</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot get checksum of attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_GetCheckSum(FSPDF_ATTACHMENT attachment, FSCRT_BSTR* checksum);

/**
 * @brief	Set the checksum of an attachment.
 *
 * @details	The checksum refers to checksum of the bytes of the uncompressed embedded file.<br>
 *			The checksum is calculated by applying the standard MD5 message-digest algorithm <br>
 *			(described in Internet RFC 1321, the MD5 Message-Digest Algorithm; see the Bibliography) to the bytes of the embedded file stream.<br>
 *
 * @param[in]	attachment		Handle to a valid <b>FSPDF_ATTACHMENT</b> object which is a PDF attachment object.
 * @param[in]	checksum		Pointer to a ::FSCRT_BSTR structure which specifies the checksum of the attachment.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>checksum</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting checksum of attachment is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot set checksum of the attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_SetCheckSum(FSPDF_ATTACHMENT attachment, const FSCRT_BSTR* checksum);

/**
 * @brief	Write the attachment data directly into a file.
 *
 * @param[in]	attachment		Handle to a valid <b>FSPDF_ATTACHMENT</b> object which is a PDF attachment object.
 * @param[in]	file			Handle to a <b>FSCRT_FILE</b> object.<br>
 *								When this function is called, it indicates the file that the attachment to be saved to.<br>
 *								When this function returns, it indicates to save the attachment to a file.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>file</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_FILE if the function cannot access parameter <i>file</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot save attachment to file because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_WriteToFile(FSPDF_ATTACHMENT attachment, FSCRT_FILE file);

/**
 * @brief	Get the attachment data with an asynchronous way.
 * 
 * @details	This function provides an asynchronous way to get the attachment data. This function is usually used to get a large
 *			size of attachment data in a progressive way. When this function returns, the application need to invoke function ::FSCRT_File_Read by
 *			passing the returned <b>FSCRT_FILE</b> to extract the needed data.
 *
 * @param[in]	attachment		Handle to a valid <b>FSPDF_ATTACHMENT</b> object which is a PDF attachment object.
 * @param[in]	isRawData		A boolean value indicates to get raw data if it's <b>TRUE</b>, or to get decoded data (original data) if it's <b>FALSE</b>.
 * @param[out]	file			Pointer to a <b>FSCRT_FILE</b> handle that receives the handle of file object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>file</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_FILE if the function cannot access parameter <i>file</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot get data of attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_GetData(FSPDF_ATTACHMENT attachment, FS_BOOL isRawData, FSCRT_FILE* file);

/**
 * @brief	Set the file of an attachment.
 *
 * @details	For attachment created by function ::FSPDF_Attachment_Create, this function is used to initialize the newly created attachment object before setting other properties of it.<br>
 *			For attachment got from PDF document, this function is used to set new file handle to this attachment.<br>
 *			ATTENTION: for initializing newly created attachment, only need to call one of functions ::FSPDF_Attachment_SetFileName or ::FSPDF_Attachment_SetFile.
 *
 * @param[in]	attachment		Handle to a valid <b>FSPDF_ATTACHMENT</b> object which is a PDF attachment object.
 * @param[in]	file			Handle to a <b>FSCRT_FILE</b> object which specifies the embedded file.<br>
 *								This object cannot be released until <i>attachment</i> has been released for no use 
 *								or <i>attachment</i> has been inserted to other object and document has been saved.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>attachment</i> or <i>file</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or setting file to attachment is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the function cannot set file of the attachment because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_SetFile(FSPDF_ATTACHMENT attachment, FSCRT_FILE file);

/**
 * @brief	Get a document handle related to an attachment.
 *
 * @param[in]	attachment	Handle to a <b>FSPDF_ATTACHMENT</b> object which is an attachment object. 
 * @param[out]	document	Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives a handle of document object associated with the parameter <i>attachment</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>attachment</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>attachment</i>: this handle is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Attachment_GetDocument(FSPDF_ATTACHMENT attachment, FSCRT_DOCUMENT* document);

/**
* @brief	Check whether a font is embedded in a PDF document.
* 
* @param[in]	font		Handle to a <b>FSCRT_FONT</b> object which is a PDF or non-PDF font.
* @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
* @param[out]	isEmbedded	Pointer to a ::FS_BOOL object which indicates whether parameter <i>font</i> is embedded in PDF document or not.
*							<b>TRUE</b> means parameter <i>font</i> is embedded in PDF document, otherwise it will be <b>FALSE</b>.
*
* @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
*			::FSCRT_ERRCODE_PARAM if the parameter <i>font</i>, <i>document</i> or <i>isEmbedded</i> is a <b>NULL</b> pointer.<br>
*			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
*			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
*			:FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
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
FS_RESULT FSPDF_Font_IsEmbedded(FSCRT_DOCUMENT document, FSCRT_FONT font, FS_BOOL* isEmbedded);

/**
* @brief	Get the dictionary of a font in a PDF document.
* 
* @param[in]	font			Handle to a <b>FSCRT_FONT</b> object which should be a PDF font.A PDF font is the font actually used in the PDF document. 
* @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
* @param[out]	fontDictionary	Pointer to a <b>FSPDF_OBJECT</b> object that receives the dictionary of the font.<br>
*								If there is any error, it will be <b>NULL</b>.
*
* @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
*			::FSCRT_ERRCODE_PARAM if the parameter <i>font</i>, <i>document</i> or <i>fontDictionary</i> is a <b>NULL</b> pointer.<br>
*			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid PDF document type.<br>
*			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
*			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
*			::FSCRT_ERRCODE_ERROR for the other errors.<br>
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
FS_RESULT FSPDF_Font_GetDict(FSCRT_DOCUMENT document, FSCRT_FONT font, FSPDF_OBJECT* fontDictionary);

/**
 * @brief	Check whether all features of the font can be embedded to a specific PDF document or not.
 *
 * @details	Due to various reasons, it's hard to always ensure the appearance of characters will stay the same after its font is embedded to PDF document.
 *			So this function can be used to check whether the font can be fully embedded or not before calling function ::FSPDF_Doc_EmbedFont.<br>
 *			Specially, 
 *			<ul>
 *			<li>If parameter <i>font</i> is got from another PDF document (different from parameter <i>document</i>), not support to embed this font to current specific PDF document.</li>
 *			<li>If parameter <i>font</i> has been embedded, it cannot be embedded again.</li>
 *			<li>If parameter <i>font</i> is one of the 14 standard fonts, it cannot be embedded.</li>
 *			</ul>
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	font			Handle to a <b>FSCRT_FONT</b> object.
 * @param[out]	isSupported		Pointer to a ::FS_BOOL object that receives the result:
 *								<ul>
 *								<li><b>TRUE</b> means parameter <i>font</i> can be embedded to parameter <i>document</i>;</li>
 *								<li><b>FALSE</b> means parameter <i>font</i> cannot be embedded to parameter <i>document</i>.</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if <i>document</i>, <i>font</i> or <i>isSupported</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to judge font object for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Font_IsSupportEmbedded(FSCRT_DOCUMENT document, FSCRT_FONT font, FS_BOOL* isSupported);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFBASE */

#endif /* _FSPDF_BASE_R_H_ */

