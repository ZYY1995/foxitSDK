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
 * @file	fs_renderer_r.h
 * @brief	Header file for \ref FSRENDERER "Renderer" module of Foxit PDF SDK.
 * @details	This header file defines a rendering engine.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Base definitions for a rendering engine. </li>
 *			<li>2. Create or release a rendering engine. </li>
 *			<li>3. Set properties of a rendering engine. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> explicitly.
 */

#ifndef _FSCRT_RENDERER_R_H_
#define _FSCRT_RENDERER_R_H_

/** 
 * @defgroup	FSRENDERER Renderer
 * @brief		Definitions for a rendering engine.<br>
 *				Definitions and functions in this module are included in fs_renderer_r.h.<br>
 *				Module: Renderer<br>
 *				License Identifier: Renderer/All<br>
 *				Available License Right: Unnecessary
 * @details		This module contains the following features:<br>
 *				<ul>
 *				<li>1. Renderer:
 *					<ul>
 *					<li>a. Create a renderer object, set properties of renderer and draw a bitmap on a renderer.</li>
 *					<li>b. A renderer is a graphics engine. It is created upon a device which is usually a bitmap or graphics devices.
 *						   In PDF module, a renderer is used by PDF context object to render PDF pages.
 *						   If applications change properties of a renderer, it will affect subsequent drawing results.
 *						   Flags for blend modes, constants for line joins and line caps are defined in this header file but not supported at present.</li>
 *					<li>c. Note: currently a windows renderer can be created as a platform-based engine which is defined in windows/fs_renderer_windows_r.h.</li>
 *					<li>d. Reference: It's described in chapter 4 in PDF Reference 1.7 about graphics states.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Base definitions for renderer                                               */
/*******************************************************************************/
#ifndef _FSCRT_DEF_HANDLE_RENDERER_
#define _FSCRT_DEF_HANDLE_RENDERER_

/** @brief	Handle type for a renderer. */
FSCRT_DEFINEHANDLE(FSCRT_RENDERER);

#endif /* _FSCRT_DEF_HANDLE_RENDERER_ */

#ifndef _FSCRT_DEF_MACRO_RENDERERFLAG_
#define _FSCRT_DEF_MACRO_RENDERERFLAG_
/**
 * @name	Macros Definitions for renderer flags 
 * @note	Pass one or a combination of following flags to the function ::FSCRT_Renderer_SetFlags.
 */
/**@{*/

/** @brief	Set if it needs text rendering optimization for LCD display. */
#define FSCRT_RENDERERFLAG_LCDTEXT				0x01
/** @brief	Set if device is using BGR LCD stripe. */
#define FSCRT_RENDERERFLAG_BGRSTRIPE			0x02
/** @brief	Use anti-aliasing to render graphics objects. */
#define FSCRT_RENDERERFLAG_USEANTIALIAS			0x04
/** @brief	Gray scale output. */
#define FSCRT_RENDERERFLAG_GRAYSCALE			0x08
/** @brief	Disable native text rendering feature (like GDI+, CGContext). */
#define FSCRT_RENDERERFLAG_NONATIVETEXT			0x10
/** @brief	Enable gamma to support to display small characters. */
#define FSCRT_RENDERERFLAG_TEXTGAMMA			0x20

/**@}*/
#endif /* _FSCRT_DEF_MACRO_RENDERERFLAG_ */

#ifndef _FSCRT_DEF_MACRO_BLENDMODE_
#define _FSCRT_DEF_MACRO_BLENDMODE_
/**
 * @name	Macros Definitions for render blend mode
 */
/**@{*/
/**
 * @brief	Selecting source color and ignoring backdrop color.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = Cs.<br> 
 */
#define FSCRT_RENDERERBLEND_NORMAL				0
/**
 * @brief	Multiply backdrop by source color values.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = Cb * Cs.
 */
#define FSCRT_RENDERERBLEND_MULTIPLY			1
/**
 * @brief	Multiply complements of backdrop by source color values, and then complement the result.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = 1 - [(1 - Cb) * (1 - Cs)] = Cb + Cs - Cb * Cs.
 */
#define FSCRT_RENDERERBLEND_SCREEN				2
/**
 * @brief	Multiply or screens colors, depending on backdrop color value.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = HardLight(Cs, Cb).
 */
#define FSCRT_RENDERERBLEND_OVERLAY				3
/**
 * @brief	Select darker one of backdrop and source colors.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = min(Cb, Cs).
 */
#define FSCRT_RENDERERBLEND_DARKEN				4
/**
 * @brief	Select lighter one of backdrop and source colors.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = max(Cb, Cs).
 */
#define FSCRT_RENDERERBLEND_LIGHTEN				5
/**
 * @brief	Brightens backdrop color to reflect source colors. 
 * 
 * @details	Painting with black produces no changes.<br>
 *			Here's the formula :<br>
 *			B(Cb, Cs) = <br>
 *			- min(1, Cb / (1 - Cs))		if Cs < 1 <br>
 *			- 1							if Cs = 1 
 */
#define FSCRT_RENDERERBLEND_COLORDODGE			6
/**
 * @brief	Darkens backdrop color to reflect the source color. 
 * 
 * @details	Painting with white produces no changes.<br>
 *			Here's the formula :<br>
 *			B(Cb, Cs) =  <br>
 *			- 1 - min(1, (1 - Cb) / Cs)	if Cs > 0 <br>
 *			- 0							if Cs = 0 
 */
#define FSCRT_RENDERERBLEND_COLORBURN			7
/**
 * @brief	Multiply or screens colors, depending on source color value.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) =  <br>
 *			- Multiply(Cb, 2 * Cs)		if Cs <= 0.5 <br>
 *			- Screen(Cb, 2 * Cs - 1)	if Cs > 0.5 
 */
#define FSCRT_RENDERERBLEND_HARDLIGHT			8
/**
 * @brief	Darkens or lightens colors, depending on source color value.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) =  <br>
 *			- Cb - (1 - 2 * Cs) * Cb * (1 - Cb)		if Cs <= 0.5 <br>
 *			- Cb + (2 * Cs - 1) * (D(Cb) - Cb)		if Cs > 0.5 <br>
 *			where D(x) = <br>
 *			- ((16 * x - 12) * x + 4) * x			if x <= 0.25 <br>
 *			- sqrt(x)								if x > 0.25 
 */
#define FSCRT_RENDERERBLEND_SOFTLIGHT			9
/**
 * @brief	Subtracts the darker of the two constituent colors from lighter colors.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = |Cb - Cs|.
 */
#define FSCRT_RENDERERBLEND_DIFFERENCE			10
/**
 * @brief	Produces an effect similar to that of different modes but lower in contrast.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = Cb + Cs - 2 * Cb * Cs. 
 */
#define FSCRT_RENDERERBLEND_EXCLUSION			11
/**
 * @brief	Creates a color with the hue of the source color, and the saturation and luminosity of the backdrop color.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = SetLum(SetSat(Cs, Sat(Cb)), Lum(Cb)).
 */
#define FSCRT_RENDERERBLEND_HUE					21
/**
 * @brief	Creates a color with the saturation of the source color, and the hue and luminosity of the backdrop color.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = SetLum(SetSat(Cb, Sat(Cs)), Lum(Cb)). 
 */
#define FSCRT_RENDERERBLEND_SATURATION			22
/**
 * @brief	Creates a color with the hue and saturation of the source color, and the luminosity of the backdrop color.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = SetLum(Cs, Lum(Cb)).
 */
#define FSCRT_RENDERERBLEND_COLOR				23
/**
 * @brief	Creates a color with the luminosity of the source color, and the hue and saturation of the backdrop color.
 * 
 * @details	Here's the formula :<br>
 *			B(Cb, Cs) = SetLum(Cb, Lum(Cs)).
 */
#define FSCRT_RENDERERBLEND_LUMINOSITY			24

/**@}*/
#endif /* _FSCRT_DEF_MACRO_BLENDMODE_ */


#ifndef _FSCRT_DEF_MACRO_LINECAP_
#define _FSCRT_DEF_MACRO_LINECAP_
/**
 * @name	Macro Definitions for Line Cap Styles
 */
/**@{*/

/**
 * @brief	The Butt Line Cap Type. 
 *
 * @details	The stroke is squared off at the endpoint of a path. There is no projection beyond the end of a path.
 */
#define FSCRT_LINECAP_BUTT			0
/**
 * @brief	The Round Line Cap Type. 
 *
 * @details	A semicircular arc with a diameter equal to the line width is drawn around the endpoint and filled in.
 */
#define FSCRT_LINECAP_ROUND			1
/**
 * @brief	The Projecting Square Line Cap Type.
 *
 * @details	The stroke continues beyond the endpoint of the path for a distance equal to half the line width and is squared off.
 */
#define FSCRT_LINECAP_SQUARE		2

/**@}*/
#endif /* _FSCRT_DEF_MACRO_LINECAP_ */

#ifndef _FSCRT_DEF_MACRO_LINEJOIN_
#define _FSCRT_DEF_MACRO_LINEJOIN_
/**
 * @name	Macro Definitions for Line Join Styles
 */
/**@{*/

/**
 * @brief	Miter line join type. 
 *
 * @details	The outer edges of the strokes for the two segments are extended until they meet at an angle.
 */
#define FSCRT_LINEJOIN_MITER		0

/**
 * @brief	Round line join type. 
 *
 * @details An arc of a circle with a diameter equal to the line width is drawn around the point where the two segments meet,
 *			connecting the outer edges of the strokes for the two segments.
 */
#define FSCRT_LINEJOIN_ROUND		1
/**
 * @brief	Bevel line join type. 
 *
 * @details The two segments are finished with butt caps and the resulting notch beyond the end of the segments is filled with a triangle.
 */
#define FSCRT_LINEJOIN_BEVEL		2

/**@}*/
#endif /* _FSCRT_DEF_MACRO_LINEJOIN_ */

/*******************************************************************************/
/* Renderer                                                                    */
/*******************************************************************************/
/**
 * @brief	Create a renderer on a bitmap object.
 *
 * @details	Renderer is a term of graphics engine in Foxit PDF SDK. It provides basic management and drawing operations as a common feature.<br>
 * 			There are two approaches to use a renderer: one is to draw on a renderer directly, and the other one is to output document contents by using a graphics context.<br>
 * 			PDF module provides a rendering context to output page contents. Please refer to function ::FSPDF_RenderContext_Create.
 * 
 * @param[in]	bitmap			Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object used to create a renderer.<br>
 *								ATTENTION: ::FSCRT_BITMAPFORMAT_16BPP_RGB565 is only supported in Android Platform.
 * @param[out]	renderer		Pointer to a <b>FSCRT_RENDERER</b> handle that receives a new renderer.
 *
 * @return 	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> or <i>renderer</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 * 			::FSCRT_ERRCODE_ERROR if fail to create renderer on the specified parameter <i>bitmap</i>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the format of parameter <i>bitmap</i> is ::FSCRT_BITMAPFORMAT_1BPP_RGB, 
 *			or the format of parameter <i>bitmap</i> is ::FSCRT_BITMAPFORMAT_16BPP_RGB565 but used in non-Android Platform. <br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Renderer_CreateOnBitmap(FSCRT_BITMAP bitmap, FSCRT_RENDERER* renderer);

/**
 * @brief	Release a given renderer object.
 *
 * @param[in]	renderer	Handle to a <b>FSCRT_RENDERER</b> object which is a renderer object 
 *							created by the function ::FSCRT_Renderer_CreateOnBitmap or platform-dependednt renderer creating functions.
 *
 * @return 	::FSCRT_ERRCODE_SUCCESS if the current process finishes successfully.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>renderer</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Renderer_Release(FSCRT_RENDERER renderer);

/**
 * @brief	Set flags of a renderer.
 * 
 * @param[in]	renderer	Handle to a <b>FSCRT_RENDERER</b> object which is a renderer object.
 * @param[in]	flags		An integer value for renderer flags. All undefined bits are omitted.<br>
 * 							Please refer to macro definitions <b>FSCRT_RENDERERFLAG_XXX</b> and this can be one or a combination of these macros.
 *
 * @return 	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>renderer</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Renderer_SetFlags(FSCRT_RENDERER renderer, FS_DWORD flags);

/**
 * @brief	Set bitmap dither bits of a renderer, support for 8bpp bitmap device.
 * 
 * @param[in]	renderer	Handle to a <b>FSCRT_RENDERER</b> object which is a renderer object.
 * @param[in]	bits		An integer value for number of bitmap dither bits. The valid values are 2,3,4.
 *
 * @return 	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>renderer</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note		This function only support for mobile platforms, not for desktop platforms.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Renderer_SetDitherBits(FSCRT_RENDERER renderer, FS_INT32 bits);

/**
 * @brief	Set gamma value for text rendering.
 *
 * @param[in]	gamma		Gamma value. It should be greater than 0. The default value is 2.2.
 *
 * @return 	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>gamma</i> is invalid.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Renderer_SetGamma(FS_FLOAT gamma);

/**
 * @brief	Set the current clipping rectangle into a renderer.
 * 
 * @param[in]	renderer	Handle to a <b>FSCRT_RENDERER</b> object which is a renderer object.
 * @param[in]	clipRect	Pointer to a ::FSCRT_RECT structure which specifies a clipping rectangle. 
 *							Set it to <b>NULL</b> if clear the current clipping region.
 *
 * @return 	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>renderer</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Renderer_SetClipRect(FSCRT_RENDERER renderer, const FSCRT_RECT* clipRect);

/**
 * @brief	Render a bitmap object. 
 * 
 * @param[in]	renderer	Handle to a <b>FSCRT_RENDERER</b> object which is a renderer object.
 * @param[in]	dstLeft		Left pixel position of a given area to render in the coordinate of destination.
 * @param[in]	dstTop		Top pixel position of a given area to render in the coordinate of destination.
 * @param[in]	srcBitmap	Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object used to render.
 * @param[in]	srcRect		Pointer to a ::FSCRT_RECT structure which specifies a rectangle of the bitmap.
 *
 * @return 	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>renderer</i> or parameter <i>srcBitmap</i> or parameter <i>srcRect</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the bitmap format is one of these formats:FSCRT_BITMAPFORMAT_16BPP_RGB565, FSCRT_BITMAPFORMAT_24BPP_RGB,
 *			FSCRT_BITMAPFORMAT_32BPP_RGBx, FSCRT_BITMAPFORMAT_32BPP_RGBA.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				<li> <i>srcBitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Renderer_DrawBitmap(FSCRT_RENDERER renderer, FS_INT32 dstLeft, FS_INT32 dstTop, FSCRT_BITMAP srcBitmap, const FSCRT_RECT* srcRect);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FSRENDERER */

#endif /* _FSCRT_RENDERER_R_H_ */
