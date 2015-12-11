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
 * @file	fs_image_r.h
 * @brief	Header file for \ref FSIMAGE "Image" module of Foxit PDF SDK.
 * @details	This header file defines image utilities.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Definitions for image. </li>
 *			<li>2. Create bitmap. </li>
 *			<li>3. Access bitmap properties. </li>
 *			<li>4. High-level features on bitmap process. </li>
 *			<li>5. Load image file and get frame bitmap. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b>, <b>Edit Add-on</b>, <b>Image Conversion Add-on</b>, or <b>Anntoation Add-on</b> explicitly. 
 *			Especially, if only request for enabling <b>Standard module</b>, only APIs which relates to bitmap reading/writing can be used.
 */

#ifndef _FSCRT_IMAGE_R_H_
#define _FSCRT_IMAGE_R_H_

/** 
 * @defgroup	FSIMAGE Image
 * @brief		Definitions for image functionality.<br>
 *				Definitions and functions in this module are included in fs_image_r.h and fs_image_w.h.<br>
 *				Module: Image<br>
 *				License Identifier: Image/All<br>
 *				Available License Right: Reading/Writing<br>
 *				For license Right <b>Reading</b>, see fs_image_r.h.<br>
 *				For license Right <b>Writing</b>, see fs_image_w.h.
 * @details		This module contains the following features:<br>
 *				<ul>
 *				<li>1. Bitmap:
 *					<ul>
 *					<li>a. Create or release a bitmap object, retrieve bitmap data, transform a bitmap, 
 *						   conversion of bitmap formats and calculate the bounding box of bitmap contents.</li>
 *					<li>b. Bitmap is one of most important data structures in Foxit PDF SDK. It's commonly used for rendering PDF pages.</li>
 *					<li>c. Note: On several platforms, there are different bitmap formats defined, 
 *						   but it's very important to ensure performance to use compatible formats defined by Foxit PDF SDK in applications.</li>
 *					</ul>
 *				</li>
 *				<li>2. Image reading:
 *					<ul>
 *					<li>a. Load an image file, retrieve an image file format, get frame data and image properties (EXIF informations).</li>
 *					<li>b. Foxit PDF SDK supports six formats of image files:<br>
 *						   BMP, bitmap image files;<br>
 *						   JPG, joint photographic experts group image files;<br>
 *						   PNG, portable network graphics image files;<br>
 *						   GIF, graphics interchange format image files;<br>
 *						   TIF, tagged image file format;<br>
 *						   JPX, JPEG-2000 image files.</li>
 *					<li>c. Note: Only GIF and TIF images support multiple frames, while the others only support single frame.</li>
 *					</ul>
 *				</li>
 *				<li>3. Image writing:
 *					<ul>
 *					<li>a. Create an image file, add a frame into a bitmap, and set image properties (EXIF informations).</li>
 *					<li>b. Foxit PDF SDK doesn't support to create an image file with GIF format.</li>
 *					<li>c. Note: For all supported image formats here, only TIF image supports multiple frames, 
 *								 the others only support a single frame.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Base definitions for bitmap                                                 */
/*******************************************************************************/
#ifndef _FSCRT_DEF_HANDLE_BITMAP_
#define _FSCRT_DEF_HANDLE_BITMAP_

/** @brief	Handle type to bitmap. */
FSCRT_DEFINEHANDLE(FSCRT_BITMAP);

#endif /* _FSCRT_DEF_HANDLE_BITMAP_ */

#ifndef _FSCRT_DEF_MACRO_BITMAPFORMAT_
#define _FSCRT_DEF_MACRO_BITMAPFORMAT_
/**
 * @name	Macro Definitions for Bitmap Format
 */
/**@{*/

/** @brief	24bpp format, bits order: Blue, Green, Red. Blue is the lowest order. */
#define FSCRT_BITMAPFORMAT_24BPP_BGR		1
/** @brief	32bpp format, bits order: Blue, Green, Red, not used. Blue is the lowest order. */
#define FSCRT_BITMAPFORMAT_32BPP_BGRx		2
/** @brief	32bpp format, bits order: Blue, Green, Red, Alpha. Blue is the lowest order. */
#define FSCRT_BITMAPFORMAT_32BPP_BGRA		3
/** @brief	8bpp format, gray scale. */
#define FSCRT_BITMAPFORMAT_8BPP_GRAY		4
/** @brief	24bpp format, bits order: Red, Green, Blue. Red is the lowest order. */
#define FSCRT_BITMAPFORMAT_24BPP_RGB		5
/** @brief	32bpp format, bits order: Red, Green, Blue, not used. Red is the lowest order. */
#define FSCRT_BITMAPFORMAT_32BPP_RGBx		6
/** @brief	32bpp format, bits order: Red, Green, Blue, Alpha. Red is the lowest order. */
#define FSCRT_BITMAPFORMAT_32BPP_RGBA		7
/** @brief	16bpp format, bits order: Red 5 bits, Green 6 bits, Blue 5 bits. Red is the lowest order. */
#define FSCRT_BITMAPFORMAT_16BPP_RGB565		8
/** @brief	8bpp alpha mask. */
#define FSCRT_BITMAPFORMAT_8BPP_MASK		9
/** @brief	1bpp format, 0 for black, 1 for white. */
#define FSCRT_BITMAPFORMAT_1BPP_RGB			10

/**@}*/
#endif /* _FSCRT_DEF_MACRO_BITMAPFORMAT_ */

#ifndef _FSCRT_DEF_MACRO_ARGB_
#define _FSCRT_DEF_MACRO_ARGB_
/**
 * @name	Macro Definitions for ARGB Color Format
 */
/**@{*/

/** @brief	Used for encode ARGB color format. */
#define FSCRT_ARGB_Encode(a,r,g,b)		((((FS_DWORD)(((FS_BYTE)(b) | ((FS_DWORD)((FS_BYTE)(g)) << 8)) | (((FS_DWORD)(FS_BYTE)(r)) << 16)))) | (((FS_DWORD)(FS_BYTE)(a)) << 24))
/** @brief	Used for get the A value from ARGB color format. */
#define FSCRT_ARGB_GetAValue(argb)		((FS_BYTE)(((FS_DWORD)(argb)) >> 24))
/** @brief	Used for get the R value from ARGB color format. */
#define FSCRT_ARGB_GetRValue(argb)		((FS_BYTE)(((FS_DWORD)(argb)) >> 16))
/** @brief	Used for get the G value from ARGB color format. */
#define FSCRT_ARGB_GetGValue(argb)		((FS_BYTE)(((FS_DWORD)(argb)) >> 8))
/** @brief	Used for get the B value from ARGB color format. */
#define FSCRT_ARGB_GetBValue(argb)		((FS_BYTE)(argb))

/**@}*/
#endif /* _FSCRT_DEF_MACRO_ARGB_ */

#ifndef _FSCRT_DEF_MACRO_INTERPOLATION_
#define _FSCRT_DEF_MACRO_INTERPOLATION_
/**
 * @name	Macro Definitions for stretching or transforming
 */
/**@{*/

/** @brief	When set, don't do halftone for shrinking or rotating. */
#define FSCRT_INTERPOLATION_DOWNSAMPLE		0x04
/** @brief	When set, do interpolation for stretching or transforming. */
#define FSCRT_INTERPOLATION_QUADRATIC		0x20
/** @brief	When set, do bicubic interpolation for stretching or transforming. */
#define FSCRT_INTERPOLATION_BICUBIC			0x80
/*@}*/ 
#endif /* _FSCRT_DEF_MACRO_INTERPOLATION_ */

#ifndef _FSCRT_DEF_MACRO_BITMAPBBOX_
#define _FSCRT_DEF_MACRO_BITMAPBBOX_
/**
 * @name	Macro Definitions for calculation methods of bitmap bounding.
 */
/**@{*/

/** @brief	Matching the given background color exactly. */
#define FSCRT_BITMAPBBOX_DETECTION		0
/** @brief	Detecting a bounding box by analyzing a bitmap. */
#define FSCRT_BITMAPBBOX_BACKCOLOR		1

/**@}*/
#endif /* _FSCRT_DEF_MACRO_BITMAPBBOX_ */

#ifndef _FSCRT_DEF_STRUCTURE_BITMAPINFOHEADER_
#define _FSCRT_DEF_STRUCTURE_BITMAPINFOHEADER_

/**
 * @brief	Structure for information about dimensions and color format of a device-independent bitmap (DIB).
 */
typedef struct _FSCRT_BITMAPINFOHEADER
{
	/** @brief	The number of bytes required by the structure. */	
	FS_DWORD		size;
	/** @brief	The width of a bitmap, in pixels. */	
	FS_INT32		width;
	/** @brief	The height of a bitmap, in pixels. */	
	FS_INT32		height;
	/** @brief	The number of planes for a target device. This value must be set to 1. */	
	FS_WORD			planes;
	/** @brief	The number of bits per pixel (bpp). */	
	FS_WORD			bitCount;
	/** @brief	The type of compression for a compressed bottom-up bitmap (top-down DIBs cannot be compressed). */	
	FS_DWORD		compression;
	/** @brief	The size of an image, in bytes. */	
	FS_DWORD		sizeImage;
	/** @brief	The horizontal resolution, in pixels per meter, of the target device for the bitmap. */	
	FS_INT32		xPelsPerMeter;
	/** @brief	The vertical resolution, in pixels per meter, of the target device for the bitmap. */	
	FS_INT32		yPelsPerMeter;
	/** @brief	The number of color indices in the color table which are actually used by the bitmap. */	
	FS_DWORD		clrUsed;
	/** 
	 * @brief	The number of color indicates which is important for displaying a bitmap. 
	 * 
	 * @details	If this value is zero, all colors are important. 
	 */	
	FS_DWORD		clrImportant;
} FSCRT_BITMAPINFOHEADER;

#endif /* _FSCRT_DEF_STRUCTURE_BITMAPINFOHEADER_ */

#ifndef _FSCRT_DEF_STRUCTURE_RGBQUAD_
#define _FSCRT_DEF_STRUCTURE_RGBQUAD_

/**
 * @brief	Structure for a color consisting of relative intensities of red, green, and blue.
 */
typedef struct _FSCRT_RGBQUAD
{
	/** @brief	The intensity of blue in the color. */
	FS_BYTE		rgbBlue;
	/** @brief	The intensity of green in the color.*/
	FS_BYTE		rgbGreen;
	/** @brief	The intensity of red in the color.*/
	FS_BYTE		rgbRed;
	/** @brief	This member is reserved and shall be zero.*/
	FS_BYTE		rgbReserved;
} FSCRT_RGBQUAD;

#endif /* _FSCRT_DEF_STRUCTURE_RGBQUAD_ */

#ifndef _FSCRT_DEF_STRUCTURE_BITMAPINFO_
#define _FSCRT_DEF_STRUCTURE_BITMAPINFO_

/**
 * @brief	Structure for dimensions and color information of a device-independent bitmap(DIB).
 */
typedef struct _FSCRT_BITMAPINFO
{
	/** @brief	A ::FSCRT_BITMAPINFOHEADER structure that contains information about dimensions and color formats of a DIB. */
	FSCRT_BITMAPINFOHEADER		bmiHeader;
	/** @brief	An array of ::FSCRT_RGBQUAD or FS_DWORD data types that define colors in a bitmap.*/
	FSCRT_RGBQUAD				bmiColors[1];
} FSCRT_BITMAPINFO;

#endif /* _FSCRT_DEF_STRUCTURE_BITMAPINFO_ */

/*******************************************************************************/
/* Bitmap access                                                               */
/*******************************************************************************/
/**
 * @brief	Create a bitmap.
 *
 * @details	If the parameter <i>buffer</i> is not <b>NULL</b>, it should be initialized by application; 
 *			otherwise, Foxit PDF SDK will allocate and initialize the pixels buffer internally. <br>
 *			Application is suggested to use the same colors to initialize bitmaps' pixels buffer as Foxit PDF SDK uses internally:
 *			<ul>
 *			<li>For the bitmap without alpha channel, initialize the pixels buffer with 0xFFFFFFFF.</li>
 *			<li>For the bitmap with alpha channel, initialize the pixels buffer with 0x00000000.</li>
 *			</ul>
 *
 * @param[in]	width		Width of a bitmap, in pixels.
 * @param[in]	height		Height of a bitmap, in pixels.
 * @param[in]	format		Bitmap format type. Please refer to macro definitions <b>FSCRT_BITMAPFORMAT_XXX</b> and this should be one of these macros.
 * @param[in]	buffer		Pointer to a buffer that specifies bitmap data.<br>
 *							If it's not <b>NULL</b>, this function will use the parameter <i>buffer</i> to initialize a bitmap. 
 *							In this case, please do not free the parameter <i>buffer</i> before the parameter <i>bitmap</i> is released.<br>
 * 							If it's <b>NULL</b>, a new bitmap buffer will be created internally.
 * @param[in]	stride		The number of bytes for each scan line, for an external buffer only. If not specified, 4-byte alignment is assumed.
 * @param[out]	bitmap		Pointer to a <b>FSCRT_BITMAP</b> handle that receives a created bitmap handle.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 * 			::FSCRT_ERRCODE_UNSUPPORTED if the size of bitmap buffer is greater than 2 GB.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_Create(FS_INT32 width, FS_INT32 height, FS_INT32 format, FS_LPVOID buffer, FS_INT32 stride, FSCRT_BITMAP* bitmap);

/**
 * @brief	Destroy a bitmap and release related resources.
 *
 * @details	If an external buffer is used (specified by the parameter <i>buffer</i> in calling the function ::FSCRT_Bitmap_Create), it will not be destroyed.
 *
 * @param[in]	bitmap	Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_Release(FSCRT_BITMAP bitmap);

/**
 * @brief	Fill a bitmap object with a specified color.
 *
 * @details	If the format of bitmap is ::FSCRT_BITMAPFORMAT_8BPP_GRAY, the gray value for parameter <i>color</i> 
 *			is computed according to the NTSC video standard, which determines how a color television signal 
 *			is rendered on a black-and-white television set:<br>
 *			<b>gray = 0.3*red + 0.59*green + 0.11*blue</b><br>
 *			For more details, please refer to session 6.2.1 "Conversion between DeviceGray and DeviceRGB" in PDF Reference1.7 page 481.
 *
 * @param[in]	bitmap		Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object.
 * @param[in]	color		Color to fill. If the alpha component is 0 and the filling rectangle is specified, then no color would be filled.
 * @param[in]	fillRect	Pointer to a ::FSCRT_RECT structure to specify a filling rectangle. If it's <b>NULL</b>, the whole bitmap will be filled with a specific color.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_FillRect(FSCRT_BITMAP bitmap, FS_ARGB color, const FSCRT_RECT* fillRect);

/**
 * @brief	Get format of a bitmap object.
 *
 * @param[in]	bitmap		Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object. 
 * @param[out]	format		Pointer to a ::FS_INT32 object that receives the current bitmap format. 
 *							Please refer to macro definitions <b>FSCRT_BITMAPFORMAT_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> or <i>format</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_GetFormat(FSCRT_BITMAP bitmap, FS_INT32* format);

/**
 * @brief	Get the size of a bitmap object.
 *
 * @param[in]	bitmap		Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object.
 * @param[out]	width		Pointer to a ::FS_INT32 object that receives the width of bitmap in pixels.
 * @param[out]	height		Pointer to a ::FS_INT32 object that receives the height of bitmap in pixels.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i>, <i>width</i> or <i>height</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_GetSize(FSCRT_BITMAP bitmap, FS_INT32* width, FS_INT32* height);

/**
 * @brief	Get a line buffer of a bitmap object.
 *
 * @details	Bitmap data are organized in scan-lines, from top to down.
 *
 * @param[in]	bitmap		Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object.
 * @param[in]	lineIndex	The index of scan-line, from 0 to the (height-1) of <i>bitmap</i>.
 * @param[out]	buffer		Pointer to a ::FS_LPVOID object that receives the buffer address of scan-line.
 *							The bitmap buffer is continuous in the memory, so if want to receive the whole bitmap buffer, please set <i>lineIndex</i> to 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> or <i>buffer</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>lineIndex</i> is out of range.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_GetLineBuffer(FSCRT_BITMAP bitmap, FS_INT32 lineIndex, FS_LPVOID* buffer);

/**
 * @brief	Get a row stride of the bitmap.
 *
 * @param[in]	bitmap		Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object.
 * @param[out]	stride		Pointer to a ::FS_INT32 object that receives the row stride of the bitmap.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> or <i>stride</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_GetLineStride(FSCRT_BITMAP bitmap, FS_INT32* stride);

/**
 * @brief	Swap X/Y dimensions of a bitmap object to generate rotated one.
 *
 * @param[in]	srcBitmap		Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object.
 * @param[in]	flipX			A boolean value to indicate whether a flipping image is in horizontal direction (left/right). 
 *								If it's <b>TRUE</b>, a bitmap will be flipped in horizontal direction.
 * @param[in]	flipY			A boolean value to indicate whether a flipping image is in vertical direction (up/down). 
 *								If it's <b>TRUE</b>, a bitmap will be flipped in vertical direction.
 * @param[out]	dstBitmap		Pointer to a <b>FSCRT_BITMAP</b> handle that receives a result bitmap handle.<br>
 *								Applications should release it by calling the function ::FSCRT_Bitmap_Release.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>srcBitmap</i> or <i>dstBitmap</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNSUPPORTED if the type of bitmap is ::FSCRT_BITMAPFORMAT_16BPP_RGB565.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>srcBitmap</i>: this handle is long-term recoverable.</li>
  *				<li> <i>dstBitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_GetFlipped(FSCRT_BITMAP srcBitmap, FS_BOOL flipX, FS_BOOL flipY, FSCRT_BITMAP* dstBitmap);

/**
 * @brief	Stretch the source bitmap into a new bitmap with different size.
 *
 * @param[in]	srcBitmap		Handle to a <b>FSCRT_BITMAP</b> object which is the source bitmap object.
 * @param[in]	dstBitmap		Handle to a <b>FSCRT_BITMAP</b> object which is the destination bitmap object.
 * @param[in]	dstLeft			Left position in the destination bitmap from which the source bitmap stretch.
 * @param[in]	dstTop			Top position in the destination bitmap from which the source bitmap stretch.
 * @param[in]	dstWidth		Width in the destination bitmap.
 * @param[in]	dstHeight		Height in the destination bitmap.
 * @param[in]	dstClipRect		Pointer to a ::FSCRT_RECT structure which is the clipping rectangle in the destination bitmap.
 * @param[in]	interpolation	An integer value, representing which interpolation algorithm will be used to stretch a bitmap.
 *								Please refer to macro definitions <b>FSCRT_INTERPOLATION_XXX</b> 
 *								and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>srcBitmap</i>, <i>dstBitmap</i> or <i>dstClipRect</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNSUPPORTED if the type of bitmap is ::FSCRT_BITMAPFORMAT_16BPP_RGB565.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>srcBitmap</i>: this handle is long-term recoverable.</li>
 *				<li> <i>dstBitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_StretchTo(FSCRT_BITMAP srcBitmap,
								   FSCRT_BITMAP dstBitmap, FS_INT32 dstLeft, FS_INT32 dstTop, FS_INT32 dstWidth, FS_INT32 dstHeight,
								   const FSCRT_RECT* dstClipRect, FS_INT32 interpolation);

/**
 * @brief	Transform a source bitmap into destination one.
 *
 * @param[in]	srcBitmap		Handle to a <b>FSCRT_BITMAP</b> object which is a source bitmap object.
 * @param[in]	dstBitmap		Handle to a <b>FSCRT_BITMAP</b> object which is a destination bitmap object.
 * @param[in]	matrix			Pointer to a ::FSCRT_MATRIX structure to specify a transformation matrix.
 * @param[in]	dstClipRect		Pointer to a ::FSCRT_RECT structure which is the clipping rectangle in destination bitmap.
 * @param[in]	interpolation	An integer value, representing which interpolation algorithm will be used to transform a bitmap.
 *								Please refer to macro definitions <b>FSCRT_INTERPOLATION_XXX</b> 
 *								and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>srcBitmap</i>, <i>dstBitmap</i>, <i>matrix</i> or <i>dstClipRect</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNSUPPORTED if the type of bitmap is ::FSCRT_BITMAPFORMAT_16BPP_RGB565.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>srcBitmap</i>: this handle is long-term recoverable.</li>
 *				<li> <i>dstBitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_TransformTo(FSCRT_BITMAP srcBitmap,
									 FSCRT_BITMAP dstBitmap, const FSCRT_MATRIX* matrix,
									 const FSCRT_RECT* dstClipRect, FS_INT32 interpolation);

/**
 * @brief	Convert a bitmap to another specific format.
 *
 * @param[in]	bitmap		Handle to a bitmap object which is a source bitmap.
 * @param[in]	format		New bitmap format type. Please refer to macro definitions <b>FSCRT_BITMAPFORMAT_XXX</b> 
 *							and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_FORMAT if the parameter <i>format</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_UNSUPPORTED if the type of bitmap is ::FSCRT_BITMAPFORMAT_16BPP_RGB565.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_ConvertFormat(FSCRT_BITMAP bitmap, FS_INT32 format);

/**
 * @brief	Clone a bitmap.
 * 
 * @param[in]	bitmap	Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object.
 * @param[out]				clonedBitmap	Pointer to a <b>FSCRT_BITMAP</b> handle that receives a cloned bitmap.<br>
 *										Applications should release it by calling function ::FSCRT_Bitmap_Release.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> or <i>clonedBitmap</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				<li> <i>clonedBitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_Clone(FSCRT_BITMAP bitmap, FSCRT_BITMAP* clonedBitmap);

/**
 * @brief	Get bitmap information from a given Foxit DIB.
 * 
 * @details	Usually, this function needs to be called twice:<br>
 *			At the first time, set the parameter <i>bitmapInfo</i> to be <b>NULL</b> and get the buffer size, 
 *			which is returned in the parameter <i>size</i>.<br>
 *			The <i>size</i> is used to allocate <i>bitmapInfo</i>.<br>
 *			At the second time, input <i>bitmapInfo</i> and its <i>size</i>. 
 *			When this function returns successfully, <i>bitmapInfo</i> will get bitmap information.<br>
 *			The size of <i>bitmapInfo</i> shall not be less than buffer size, and the parameter <i>size</i> shall not be empty.
 *
 * @param[in]		bitmap			Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object.
 * @param[out]		bitmapInfo		Pointer to a ::FSCRT_BITMAPINFO object that recieves dimensions and color information of a bitmap.<br>
 *									If this parameter is <b>NULL</b>, the parameter <i>size</i> will receive buffer size of <i>bitmapInfo</i> in bytes.
 * @param[in,out]	size			Pointer to a <b>FS_DWORD</b> object. It shall not be <b>NULL</b>.<br>
 *									When it's an input parameter, it should be the size of the structure of the parameter <i>bitmapInfo</i> points to.<br>
 *									When it's a return value, it receives an actual buffer size, 
 *									which is necessary for allocating <i>bitmapInfo</i> when input <i>bitmapInfo</i> is <b>NULL</b>.<br>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_BUFFEROVERFLOW if the parameter <i>bitmapInfo</i> is not <b>NULL</b> and <i>size</i> is less than the required buffer size.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_GetBitmapInfo(FSCRT_BITMAP bitmap, FSCRT_BITMAPINFO* bitmapInfo, FS_DWORD* size);

/**
 * @brief	Calculate the bounding box of a bitmap.
 * 
 * @param[in]	bitmap			Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object.
 * @param[in]	flag			Method flag is used to specify how to calculate a bounding box, ::FSCRT_BITMAPBBOX_DETECTION means matching a given background color <i>backColor</i> exactly,
 *								::FSCRT_BITMAPBBOX_BACKCOLOR means detecting bounding box by analyzing bitmap contents.
 * @param[in]	backColor		Background color. It shall be valid only when the parameter <i>flag</i> is 0.
 * @param[in]	windowSize		Detection size to analyze background, it shall valid only when parameter <i>flag</i> is 1.
 * @param[in]	tolerance		Tolerance to indicate color difference when detecting a bounding box, it shall be valid only when the parameter <i>flag</i> is 1. Its value should be between 0 and 255, and the suggested value is 64.
 * @param[out]	rectBBox		Pointer to a <b>FSCRT_RECT</b> structure that receives a bounding box rectangle.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> or <i>rectBBox</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_CalcBBox(FSCRT_BITMAP bitmap, FS_INT32 flag, FS_ARGB backColor, FS_INT32 windowSize, FS_INT32 tolerance, FSCRT_RECT* rectBBox);

/**
 * @brief	Get the mask bitmap of a bitmap.
 * 
 * @param[in]	bitmap	Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object.
 * @param[out]	mask	Pointer to a <b>FSCRT_BITMAP</b> handle that receives the mask bitmap. If there is no mask bitmap, <i>mask</i> will be <b>NULL</b>.<br>
 *						Applications should release it by calling function ::FSCRT_Bitmap_Release.
 *
 * @note	Only ARGB format of bitmap is supported now.				
 *	
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bitmap</i> or <i>mask</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if a bitmap don't contain the alpha channel.<br>
 *			::FSCRT_ERRCODE_ERROR if some other error happened.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				<li> <i>mask</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Bitmap_GetMask(FSCRT_BITMAP bitmap, FSCRT_BITMAP* mask);

/*******************************************************************************/
/* Image access                                                                */
/*******************************************************************************/
#ifndef _FSCRT_DEF_HANDLE_IMAGE_
#define _FSCRT_DEF_HANDLE_IMAGE_

/** @brief	Handle type to image. */
FSCRT_DEFINEHANDLE(FSCRT_IMAGE);

#endif /* _FSCRT_DEF_HANDLE_IMAGE_ */

#ifndef _FSCRT_DEF_HANDLE_IMAGEFILE_
#define _FSCRT_DEF_HANDLE_IMAGEFILE_

/** @brief	Handle type to image file. */
FSCRT_DEFINEHANDLE(FSCRT_IMAGEFILE);

#endif /* _FSCRT_DEF_HANDLE_IMAGEFILE_ */

#ifndef _FSCRT_DEF_MACRO_IMAGETYPE_
#define _FSCRT_DEF_MACRO_IMAGETYPE_
/**
 * @name	Macro definitions for image types
 */
/**@{*/

/** @brief	Image type is BMP. */
#define FSCRT_IMAGETYPE_BMP			1
/** @brief	Image type is JPG or JPeg. */
#define FSCRT_IMAGETYPE_JPG			2
/** @brief	Image type is PNG. */
#define FSCRT_IMAGETYPE_PNG			3
/** @brief	Image type is GIF. */
#define FSCRT_IMAGETYPE_GIF			4
/** @brief	Image type is TIF or TIFF. */
#define FSCRT_IMAGETYPE_TIF			5
/** @brief	Image type is JPX or JPeg-2000. */
#define FSCRT_IMAGETYPE_JPX			6
/** @brief	Image type is JBIG2. 
 *  @note	Currently, Only a few image APIs support this type. If API dose not support this type, ::FSCRT_ERRCODE_UNSUPPORTED would be returned.
 */
#define FSCRT_IMAGETYPE_JBIG2		8

/**@}*/
#endif /* _FSCRT_DEF_MACRO_IMAGETYPE_ */

#ifndef _FSCRT_DEF_MACRO_IMAGEPROPERTY_
#define _FSCRT_DEF_MACRO_IMAGEPROPERTY_
/**
 * @name	Macro definitions for image properties
 * @note	Image properties are used in the function ::FSCRT_Image_GetProperty and ::FSCRT_ImageFile_SetProperty.
 */
/**@{*/

/**
 * @brief	DPI, that is Dot-Per-Inch.
 *
 * @note	Contains 2 values: the first is DPI value for X-axis, and the second is DPI value for Y-axis.
 * 			Two values are integer, FSCRT_VAR::type should be ::FSCRT_VT_INT32.
 */
#define FSCRT_IMAGEPROPERTY_DPI			"dpi"

/**@}*/
#endif /* _FSCRT_DEF_MACRO_IMAGEPROPERTY_ */

/**
 * @brief	Load an image from an image file.
 *
 * @details	Foxit PDF SDK supports six types of image files, and they are specified by macro definitions <b>FSCRT_IMAGETYPE_XXX</b>.
 *
 * @param[in]	imageFile	Handle to a <b>FSCRT_FILE</b> object which is an image file object.
 * @param[out]	image		Pointer to a <b>FSCRT_IMAGE</b> handle that receives a handle of image object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>imageFile</i> or <i>image</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to some type of image is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to load an image for any other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>imageFile</i>: this handle is long-term recoverable.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Image_LoadFromFile(FSCRT_FILE imageFile, FSCRT_IMAGE* image);

/**
 * @brief	Get an image type.
 * 
 * @param[in]	image	Handle to a <b>FSCRT_IMAGE</b> object which is an image object.
 * @param[out]	type	Pointer to a ::FS_INT32 object that receives an image type. 
 *						Please refer to macro definitions <b>FSCRT_IMAGETYPE_XXX</b> and this shall be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>image</i> or <i>type</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Image_GetType(FSCRT_IMAGE image, FS_INT32* type);

/**
 * @brief	Get width and height of an image.
 * 
 * @details	Currently, this function doesn't support TIF format images. If use this function for TIF image, width and height of TIF image will be <b>0</b>.
 *
 * @param[in]	image		Handle to a <b>FSCRT_IMAGE</b> object which is an image object.
 * @param[out]	width		Pointer to a ::FS_INT32 object that receives width of image.
 * @param[out]	height		Pointer to a ::FS_INT32 object that receives height of image.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>image</i>, <i>width</i> or <i>height</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Image_GetSize(FSCRT_IMAGE image, FS_INT32* width, FS_INT32* height);

/**
 * @brief	Count frames of an image.
 * 
 * @param[in]	image		Handle to a <b>FSCRT_IMAGE</b> object which is an image object.
 * @param[out]	count		Pointer to a ::FS_INT32 object that receives count of all image frames.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the image type is ::FSCRT_IMAGETYPE_JBIG2.
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>image</i> or <i>count</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Image_CountFrames(FSCRT_IMAGE image, FS_INT32* count);

/**
 * @brief	Load an image frame by index.
 * 
 * @note	If you want to get the information of the specific frame, you should call this function first.
 *
 * @param[in]	image			Handle to a <b>FSCRT_IMAGE</b> object which is an image object.
 * @param[in]	frameIndex		The index of a given frame.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>image</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>frameIndex</i> is out of range.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the image type is ::FSCRT_IMAGETYPE_JBIG2.
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to load frames for any other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Image_LoadFrame(FSCRT_IMAGE image, FS_INT32 frameIndex);

/**
 * @brief	Get width and height of the current frame.
 * 
 * @param[in]	image		Handle to a <b>FSCRT_IMAGE</b> object which is an image object.
 * @param[out]	width		Pointer to a ::FS_INT32 object that receives width of the current frame.
 * @param[out]	height		Pointer to a ::FS_INT32 object that receives height of current frame.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>image</i>, <i>width</i> or <i>height</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the image type is ::FSCRT_IMAGETYPE_JBIG2.
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get current frame size for any other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Image_GetCurrentFrameSize(FSCRT_IMAGE image, FS_INT32* width, FS_INT32* height);

/**
 * @brief	Retrieve the bitmap of the current frame.
 * 
 * @param[in]	image		Handle to a <b>FSCRT_IMAGE</b> object which is an image object.
 * @param[out]	bitmap		Pointer to a <b>FSCRT_BITMAP</b> object that receives the retrieved bitmap object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>image</i> or <i>bitmap</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the image type is ::FSCRT_IMAGETYPE_JBIG2.
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get the current frame bitmap for any other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	The parameter <i>bitmap</i> shall be released by caller.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Image_GetCurrentFrameBitmap(FSCRT_IMAGE image, FSCRT_BITMAP* bitmap);

/**
 * @brief	Get properties of an image.
 * 
 * @param[in]		image		Handle to a <b>FSCRT_IMAGE</b> object which is an image object.
 * @param[in]		property	Pointer to a <b>FSCRT_BSTR</b> structure that specifies the property information of the image, such as EXIF info. 
 *								Currently, only dpi property is supported. Please refer to macro definition ::FSCRT_IMAGEPROPERTY_DPI.
 * @param[in,out]	values		Pointer to a <b>FSCRT_VAR</b> object that receives values, it can be <b>NULL</b>.
 * @param[in,out]	count		Pointer to a <b>FS_INT32</b> object that receives count of values.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>image</i>, <i>property</i> or <i>count</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the image type is ::FSCRT_IMAGETYPE_JBIG2.
 *			::FSCRT_ERRCODE_UNSUPPORTED if the string of the parameter <i>property</i> is not "dpi" or the length of parameter <i>property</i> is not 3.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if  an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get values of specified image property for any other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Image_GetProperty(FSCRT_IMAGE image, const FSCRT_BSTR* property, FSCRT_VAR* values, FS_INT32* count);

/**
 * @brief	Release an image object.
 * 
 * @param[in]	image		Handle to a <b>FSCRT_IMAGE</b> object which is an image object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>image</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>image</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Image_Release(FSCRT_IMAGE image);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FSIMAGE */

#endif /* _FSCRT_IMAGE_R_H_ */
