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
 * @file	fs_barcode_w.h
 * @brief	Header file for \ref FSBARCODE "Barcode" module of Foxit PDF SDK.
 * @details	This header file defines barcode operations.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Definitions for a barcode module. </li>
 *			<li>2. Initialize or finalize a barcode module. </li>
 *			<li>3. Generate a bitmap in a barcode format. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Barcode Add-on</b> explicitly.
 */

#ifndef _FSCRT_BARCODE_W_H_
#define _FSCRT_BARCODE_W_H_

/** 
 * @defgroup	FSBARCODE Barcode
 * @brief		Definitions for barcode.<br>
 *				Definitions and functions in this module are included in fs_barcode_w.h.<br>
 *				Module: Barcode<br>
 *				License Identifier: Barcode/All<br>
 *				Available License Right: Writing
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. Barcode module: initialize or finalize a barcode module.</li>
 *				<li>2. Barcode encoding:
 *					<ul>
 *					<li>a. Generate a barcode bitmap for the given barcode format and content.</li>
 *					<li>b. There are eight barcode formats supported in Foxit PDF SDK.
 *						   When a barcode is encoded, width and height of bitmap are calculated internally.</li>
 *					<li>c. Note: the ::FSCRT_BCModule_Initialize function should be called at first before calling ::FSCRT_Barcode_GenerateBitmap.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Barcode module                                                              */
/*******************************************************************************/
/**
 * @brief	Initialize barcode module.
 *
 * @details	This is the first function that should be called if applications need to process barcode.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or accessing barcode module is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMANAGER if Foxit PDF SDK manager is not initialized.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 * 			::FSCRT_ERRCODE_ERROR if the current barcode module cannot be intialized for any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	Call function ::FSCRT_BCModule_Finalize to destroy barcode module if no further process of barcode is needed.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_BCModule_Initialize();

/**
 * @brief	Finalize barcode module.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_INVALIDMANAGER if Foxit PDF SDK manager is not initialized.<br>
 * 			::FSCRT_ERRCODE_INVALIDMODULE if the current barcode module is not initialized.<br>
 *			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or accessing barcode module is not allowed.<br> 
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Function ::FSCRT_BCModule_Initialize should be called to initialize barcode module.
 *			This function should be called if no further process of barcode is needed.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_BCModule_Finalize();

/*******************************************************************************/
/* Barcode formats                                                             */
/*******************************************************************************/
#ifndef _FSCRT_DEF_MACRO_BARCODEFORMAT_
#define _FSCRT_DEF_MACRO_BARCODEFORMAT_
/**
 * @name	Macro Definitions for Barcode formats
 */
/**@{*/

/** @brief	The format is unspecified. */
#define FSCRT_BARCODEFORMAT_UNSPECIFIED		-1
/** @brief	The format is standard 39 code. */
#define FSCRT_BARCODEFORMAT_CODE_39			0
/** @brief	The format is Code128,includes EAN128 code. */
#define FSCRT_BARCODEFORMAT_CODE_128		1
/** @brief	The format is EAN-8 code. */
#define FSCRT_BARCODEFORMAT_EAN_8			2
/** @brief	The format is UPC-A code. */
#define FSCRT_BARCODEFORMAT_UPC_A			3
/** @brief	The format is EAN-13 code. */
#define FSCRT_BARCODEFORMAT_EAN_13			4
/** @brief	The format is ITF code. */
#define FSCRT_BARCODEFORMAT_ITF				5
/** @brief	The format is PDF-417 code. */
#define FSCRT_BARCODEFORMAT_PDF_417			6
/** @brief	The format is Quick Response Code. */
#define FSCRT_BARCODEFORMAT_QR_CODE			7

/**@}*/
#endif /* _FSCRT_DEF_MACRO_BARCODEFORMAT_ */

/*******************************************************************************/
/* Barcode QR format correction levels                                         */
/*******************************************************************************/
#ifndef _FSCRT_DEF_MACRO_BARCODE_QRERRORCORRECTION_
#define _FSCRT_DEF_MACRO_BARCODE_QRERRORCORRECTION_
/**
 * @name	Macro Definitions for Format Error Correction Level of QR Code
 */
/**@{*/

/** @brief	The capability of recovery from 7% amounts of damage. */
#define FSCRT_BARCODE_QRERRORCORRECTION_L			0
/** @brief	The capability of recovery from 15% amounts of damage. */
#define FSCRT_BARCODE_QRERRORCORRECTION_M			1
/** @brief	The capability of recovery from 25% amounts of damage. */
#define FSCRT_BARCODE_QRERRORCORRECTION_Q			2
/** @brief	The capability of recovery from 30% amounts of damage. */
#define FSCRT_BARCODE_QRERRORCORRECTION_H			3

/**@}*/
#endif /* _FSCRT_DEF_MACRO_BARCODE_QRERRORCORRECTION_ */

/*******************************************************************************/
/* Barcode encoding                                                            */
/*******************************************************************************/
/**
 * @brief	Generate a bitmap of barcode with a given information string and a specific barcode format.
 *
 * @param[in]	info			Pointer to a ::FSCRT_BSTR structure that is input content used to generate a bitmap. It should be valid.
 * @param[in]	codeFormat		Barcode format. Please refer to macro definitions <b>FSCRT_BARCODEFORMAT_XXX</b> and this should be one of these macros.
 * @param[in]	unitWidth		Unit width for barcode in pixels, and preferred value is 1-5 pixels. For QR Code, use min(unitWidth, unitHeight) instead of initial values.
 * @param[in]	unitHeight		Unit height for barcode in pixels, and preferred value is >= 20 pixels. For QR Code, use min(unitWidth, unitHeight) instead of initial values.
 * @param[in]	qrLevel			Error correction level, required only for QR Code.<br> 
 *								It should be one of the following: <br>
 *								<ul>
 *								<li>::FSCRT_BARCODE_QRERRORCORRECTION_L</li>
 *								<li>::FSCRT_BARCODE_QRERRORCORRECTION_M</li>
 *								<li>::FSCRT_BARCODE_QRERRORCORRECTION_Q</li>
 *								<li>::FSCRT_BARCODE_QRERRORCORRECTION_H</li>
 *								</ul>
 * @param[out]	bitmap			Pointer to a <b>FSCRT_BITMAP</b> handle that receives a bitmap handle generated by this function.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>info</i>, <i>bitmap</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDMODULE if the current barcode module is not initialized.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or generate a bitmap of barcode is not allowed.<br>
 *			::FSCRT_ERRCODE_FORMAT if the parameter <i>codeFormat</i> contains unsupported format, or value in <i>unitWidth</i>, <i>unitHeight</i>, or <i>qrLevel</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 * 			::FSCRT_ERRCODE_ERROR if any errors not covered as above occur.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	<ul>
 *			<li>::FSCRT_BCModule_Initialize should be called to initialize barcode module before any functions of barcode module are called.</li>
 *			<li>Currently, for Windows8.1 store app and WindowsPhone 8.1 store app, this function doesn't support to generate a barcode with format ::FSCRT_BARCODEFORMAT_ITF.</li>
 *			</ul>
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
FS_RESULT	FSCRT_Barcode_GenerateBitmap(const FSCRT_BSTR* info, FS_INT32 codeFormat, FS_INT32 unitWidth, FS_INT32 unitHeight, FS_INT32 qrLevel, FSCRT_BITMAP* bitmap);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FSBARCODE */

#endif/* _FSCRT_BARCODE_W_H_ */

