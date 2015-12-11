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
 * @file	fs_image_w.h
 * @brief	Header file for \ref FSIMAGE "Image" module of Foxit PDF SDK.
 * @details	This header file defines image utilities.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Create image file. </li>
 *			<li>2. Add frame to image file. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> or <b>Image Conversion Add-on</b> explicitly. 
 *			Especially, if only request for enabling <b>Standard module</b>, only APIs which relates to bitmap reading/writing can be used.
 */

#ifndef _FSCRT_IMAGE_W_H_
#define _FSCRT_IMAGE_W_H_

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
/* Image file creation                                                         */
/*******************************************************************************/
/**
 * @brief	Create an image file.
 * 
 * @details	Currently, this function doesn't support GIF format.
 * 
 * @param[in]	file			Handle to a <b>FSCRT_FILE</b> object which is a file object. It should be a new image file, which is to be created.
 * @param[in]	imageType		Image type. It should be one of the following: <br>
 *								<ul>
 *								<li>::FSCRT_IMAGETYPE_BMP</li>
 *								<li>::FSCRT_IMAGETYPE_JPG</li>
 *								<li>::FSCRT_IMAGETYPE_PNG</li>
 *								<li>::FSCRT_IMAGETYPE_TIF</li>
 *								<li>::FSCRT_IMAGETYPE_JPX</li>
 *								</ul>
 * @param[in]	frameCount		How many frames to be created. 
 *								This parameter can be larger than 1 for TIF because only TIF format supports multiple frames. 
 *								Return ::FSCRT_ERRCODE_UNSUPPORTED when it's larger than 1 for the other formats.
 * @param[out]	imageFile		Pointer to a <b>FSCRT_IMAGEFILE</b> handle which is an image file object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>file</i> or <i>imageFile</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to some types of image is not allowed.<br>
 *			::FSCRT_ERRCODE_FORMAT if the parameter <i>imageType</i> indicating is an invalid type.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the parameter <i>imageType</i> indicating is ::FSCRT_IMAGETYPE_GIF or ::FSCRT_IMAGETYPE_JBIG2, or the frame count is larger than 1 but it's not TIF format.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to create an image file for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				<li> <i>imageFile</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_ImageFile_Create(FSCRT_FILE file, FS_INT32 imageType, FS_INT32 frameCount, FSCRT_IMAGEFILE* imageFile);

/**
 * @brief	Set properties of image.
 * 
 * @details	Currently, this function doesn't support JPX, GIF and TIF format.
 *
 * @note	This function is only effective for the frames added later.
 *
 * @param[in]	imageFile		Handle to a <b>FSCRT_IMAGEFILE</b> object which is an image file object.
 * @param[in]	property		Pointer to a <b>FSCRT_BSTR</b> structure which specifies a property name of an image, such as "dpi".<br>
 *								Currently only dpi property is supported. Please refer to macro definition ::FSCRT_IMAGEPROPERTY_DPI.
 * @param[in]	values			Pointer to a <b>FSCRT_VAR</b> structure array which represents the values associated to some property.
 * @param[in]	count			Count of elements in parameter <i>values</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>imageFile</i>, <i>property</i> or <i>values</i> is <b>NULL</b>, or <i>count</i> is invalid.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the image type is ::FSCRT_IMAGETYPE_JBIG2 ::FSCRT_IMAGETYPE_JPX ::FSCRT_IMAGETYPE_GIF
 *			or the string of parameter <i>property</i> is not "dpi" or the length of it is not 3.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<ul>
 *				<li>
 *				<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>imageFile</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 *				</li>
 *				<li>If user wants to set the properties of image, this function should be called before calling function ::FSCRT_ImageFile_AddFrame.</li>
 *				</ul>
 */
FS_RESULT	FSCRT_ImageFile_SetProperty(FSCRT_IMAGEFILE imageFile, const FSCRT_BSTR* property, const FSCRT_VAR* values, FS_INT32 count);

/**
 * @brief	Add a frame to image file.
 * 
 * @details	Frame number should match image type. For example, a TIF file supports multiple frames. 
 *			Applications can add a frame or multiple frames several times.
 *
 * @param[in]	imageFile		Handle to a <b>FSCRT_IMAGEFILE</b> object which is an image file object.
 * @param[in]	bitmap			Handle to a <b>FSCRT_BITMAP</b> object which is a bitmap object to be inserted an image file as a new frame.
 *								Currently, it can not support:
 *								<ul>
 *								<li>format ::FSCRT_BITMAPFORMAT_16BPP_RGB565.</li>
 *								<li>format ::FSCRT_BITMAPFORMAT_8BPP_GRAY if the type of parameter <i>imageFile</i> is ::FSCRT_IMAGETYPE_JPG.</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>imageFile</i> or <i>bitmap</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the type of parameter <i>imageFile</i> is ::FSCRT_IMAGETYPE_JBIG2, 
 *			or the format of parameter <i>bitmap</i> is ::FSCRT_BITMAPFORMAT_16BPP_RGB565. 
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to add image frames for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>imageFile</i>: this handle is long-term recoverable.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_ImageFile_AddFrame(FSCRT_IMAGEFILE imageFile, FSCRT_BITMAP bitmap);

/**
 * @brief	Release an image file object.
 *
 * @details	Save all image data into a file, and destroy image file objects.
 *
 * @param[in]	imageFile		Handle to a <b>FSCRT_IMAGEFILE</b> object which is an image file object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>imageFile</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the image type is ::FSCRT_IMAGETYPE_JBIG2.
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>imageFile</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_ImageFile_Release(FSCRT_IMAGEFILE imageFile);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FSIMAGE */

#endif
/* _FSCRT_IMAGE_W_H_ */

