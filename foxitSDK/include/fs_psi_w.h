/**
 * Copyright (C) 2003-2015, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
 * It isn't allowed to distribute any parts of Foxit PDF SDK to any third parties or general public, unless there 
 * is a license agreement between Foxit Software Inc. and customers.
 *
 * @file	fs_psi_w.h
 * @brief	Header file for \ref FSPSI "Pressure Sensitive Ink" module.
 * @details	Functionality covered in this header file is based on pressure sensitivity technology. <br>
 *			Pressure Sensitive Ink is an imitation of handwriting. <br>
 *			Users can call APIs provided in this header file to:<br>
 *			<ul>
 *			<li>1. Connect to an external tablet and set a ARGB value or a diameter size of the brush.</li>
 *			<li>2. Initialize a transparent canvas in a client zone to enable users to write or draw on it.<li>
 *			<li>3. Display strokes with different states and pressure according to users' drawing speed and pressure.<li>
 *			<li>4. Generate Pressure Sensitive Ink information to PDF annotations and add annotations to pages.<li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>PSI Add-on</b> explicitly.
 */

#ifndef _FSCRT_PSI_W_H_
#define _FSCRT_PSI_W_H_

/** 
 * @defgroup	FSPSI Pressure Sensitive Ink
 * @brief		Definitions for Pressure Sensitive Ink.<br>
 *				Definitions and functions in this module are included in fs_psi_w.h.<br>
 *				Module: PSI<br>
 *				License Identifier: PSI/All<br>
 *				Available License Right: Writing
 * @details		This module contains the following features:<br>
 *				<ul>
 *				<li>1. Pressure sensitive ink (PSI):
 *					<ul>
 *					<li>a. Create a PSI object and initialize a canvas, set properties, add points data,
 *						   render PSI or convert PSI objects to PDF annotations.</li>
 *					<li>b. PSI is defined for manual signature especially, and usually works together with a handwriting board.
 *						   PSI contains private coordinates, and a canvas is created in its coordinates.
 *						   Canvas limits operating area and generates appearance of PSI. </li>
 *					<li>c. Note: ::FSCRT_PSI_ConvertToPDFAnnot requires that PDF module is intialized and a PDF page object is available.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Base definitions for PSI                                                    */
/*******************************************************************************/
#ifndef _FSCRT_DEF_HANDLE_PSI_
#define _FSCRT_DEF_HANDLE_PSI_

/** @brief	Handle type to Pressure Sensitive Ink. */
FSCRT_DEFINEHANDLE(FSCRT_PSI);

#endif /* _FSCRT_DEF_HANDLE_PSI_ */

#ifndef _FSCRT_DEF_MACRO_PSI_PT_
#define _FSCRT_DEF_MACRO_PSI_PT_

/**
 * @name	Macro Definitions for Point Flags 
 * @note	These definitions is used in the function ::FSCRT_PSI_AddPoint.
 */
/**@{*/

/** @brief	Point adding flags of LINE TO. */
#define FSCRT_PSI_PT_LINETO			FSCRT_POINTTYPE_LINETO
/** @brief	Point adding flags of MOVE TO. */
#define FSCRT_PSI_PT_MOVETO			FSCRT_POINTTYPE_MOVETO
/** @brief	Point adding flags of END PATH. */
#define FSCRT_PSI_PT_ENDPATH		0x08

/**@}*/
#endif /* _FSCRT_DEF_HANDLE_PSI_ */

/***********************************************************************/
/* PSI operations                                                      */
/***********************************************************************/
/**
 * @brief	Create a pressure sensitive ink object. 
 *
 * @param[in]	simulate		Turn on/off simulation of Pressure Sensitive Ink: 
 *								<b>TRUE</b> means to turn on simulation, and <b>FALSE</b> means to turn off simulation.<br>
 *								It can simulate handwriting weights by writing speed when simulation is on.
 * @param[out]	psi				Pointer to a <b>FSCRT_PSI</b> handle that receives a handle of Pressure Sensitive Ink.	
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>psi</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more definitions please see macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>psi</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PSI_Create(FS_BOOL simulate, FSCRT_PSI* psi);

/**
 * @brief	Destroy a pressure sensitive ink object.
 *
 * @param[in]	psi		Handle to a <b>FSCRT_PSI</b> object. 
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>psi</i> is <b>NULL</b>.<br>
 *			For more definitions please see macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
* @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves
*              when accessing the same objects during multi-thread environments..<br>
*              <b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
*				<ul>
*				<li> <i>psi</i>: this handle is long-term partially recoverable.</li>
*				</ul>
*				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PSI_Release(FSCRT_PSI psi);

/**
 * @brief	Initialize a canvas for pressure sensitive ink.
 *
 * @param[in]	psi			Handle to a <b>FSCRT_PSI</b> object.
 * @param[in]	width		Width of pressure sensitive ink canvas. This shall be greater than 0.	
 * @param[in]	height		Height of pressure sensitive ink canvas. This shall be greater than 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>psi</i> is <b>NULL</b>, or <i>width</i> or <i>height</i> is invalid.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the size of canvas(calculated as width*height*4) is greater than 2GB. <br>
 *			::FSCRT_ERRCODE_ERROR if fail to initialize the given canvas for other reasons.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more definitions please see macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe..<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>psi</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PSI_InitCanvas(FSCRT_PSI psi, FS_FLOAT width, FS_FLOAT height);

/**
 * @brief	Set ink color of a pressure sensitive ink object.
 *
 * @param[in]	psi			Handle to a <b>FSCRT_PSI</b> object.
 * @param[in]	color		Ink color. It's constructed by 0xrrggbb.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>psi</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more definitions please see macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe..<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>psi</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PSI_SetInkColor(FSCRT_PSI psi, FS_ARGB color);

/**
 * @brief	Set ink diameter of a pressure sensitive ink object.
 *
 * @param[in]	psi				Handle to a <b>FSCRT_PSI</b> object.
 * @param[in]	diameter		Ink diameter. This shall be a positive value.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>psi</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more definitions please see macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe..<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>psi</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PSI_SetInkDiameter(FSCRT_PSI psi, FS_INT32 diameter);

/**
 * @brief	Set ink opacity of a pressure sensitive ink object.
 *
 * @param[in]	psi				Handle to a <b>FSCRT_PSI</b> object.
 * @param[in]	opacity			Ink opacity. Valid range: from 0.0 to 1.0
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>psi</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more definitions please see macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe..<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>psi</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PSI_SetOpacity(FSCRT_PSI psi, FS_FLOAT opacity);

/**
 * @brief	Get contents rectangle of a pressure sensitive ink object.
 *
 * @param[in]	psi				Handle to a <b>FSCRT_PSI</b> object.
 * @param[out]	psiRect			Pointer to a valid ::FSCRT_RECTF structure that receives a rectangle of a pressure sensitive ink object in device coordinate.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>psi</i> or <i>psiRect</i> is <b>NULL</b>.<br>
 *			For more definitions please see macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>psi</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PSI_GetContentsRect(FSCRT_PSI psi, FSCRT_RECTF* psiRect);

/**
 * @brief	Add a point to a pressure sensitive ink object.
 *
 * @param[in]	psi				Handle to a <b>FSCRT_PSI</b> object.
 * @param[in]	x				The value of x-coordinate in canvas coordinate.
 * @param[in]	y				The value of y-coordinate in canvas coordinate.
 * @param[in]	pressure		Pressure value of current point, between 0 and 1. 
 * @param[in]	pointType		Point type. Please refer to macro definitions <b>FSCRT_PSI_PT_XXX</b> and this shall be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>psi</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more definitions please see macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Coordinate of canvas is the same with device coordinate.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>psi</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PSI_AddPoint(FSCRT_PSI psi, FS_FLOAT x, FS_FLOAT y, FS_FLOAT pressure, FS_DWORD pointType);

/**
 * @brief	Render a pressure sensitive ink object. 	
 *
 * @param[in]	psi			Handle to a <b>FSCRT_PSI</b> object.
 * @param[in]	renderer	Handle to a <b>FSCRT_RENDERER</b> object.
 * @param[in]	xDes		Left pixel position of the given area to render in coordinate of destination.
 * @param[in]	yDes		Top pixel position of the given area to render in coordinate of destination.
 * @param[in]	width		Width to render in coordinate of destination.
 * @param[in]	height		Height to render in coordinate of destination.
 * @param[in]	xSrc		Left pixel position of display area in coordinate of canvas.	
 * @param[in]	ySrc		Top pixel position of display area in coordinate of canvas.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>psi</i> or <i>renderer</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to render a pressure ink path for other reasons.<br>
 *			For more definitions please see macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Coordinate of canvas is the same as device coordinate.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>psi</i>: this handle is long-term partially recoverable.</li>
  *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PSI_Render(FSCRT_PSI psi, FSCRT_RENDERER renderer, FS_INT32 xDes, FS_INT32 yDes, 
							 FS_INT32 width, FS_INT32 height, FS_FLOAT xSrc, FS_FLOAT ySrc);

/***********************************************************************/
/* PSI annotation                                                      */
/***********************************************************************/
/**
 * @brief	Convert a pressure sensitive ink object to a PDF annotation.
 *
 * @param[in]	psi				Handle to a <b>FSCRT_PSI</b> handle.
 * @param[in]	psiRect			Pointer to a ::FSCRT_RECTF structure which is a psi rect in device coordinate.
 * @param[in]	pdfPage			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object. It should be valid.
 * @param[in]	annotRect		Pointer to a ::FSCRT_RECTF structure which is a annot rect in page coordinate.
 * @param[out]	annot			Pointer to a <b>FSCRT_ANNOT</b> handle that receives a newly added PSInk annotation.
 *								If there's any errors, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if kthe parameter <i>psi</i>, <i>psiRect</i>, <i>annotRect</i> or <i>annotIndex</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to generate Pressure Sensitive Ink information to a PDF page for other reasons.<br>
 *			For more definitions please see macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>psi</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pdfPage</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PSI_ConvertToPDFAnnot(FSCRT_PSI psi, const FSCRT_RECTF* psiRect, 
										FSCRT_PAGE pdfPage, const FSCRT_RECTF* annotRect, FSCRT_ANNOT* annot);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FSPSI */

#endif /* _FSCRT_PSI_W_H_ */
