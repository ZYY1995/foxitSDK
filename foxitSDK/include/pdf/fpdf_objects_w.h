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
 * @file	fpdf_objects_w.h
 * @brief	Header file for \ref FPDFOBJECTS "PDF Objects" module of Foxit PDF SDK.
 * @details	This header file provides direct access to PDF objects.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Create PDF objects. </li>
 *			<li>2. Add values to PDF array. </li>
 *			<li>3. Add values to PDF dictionary. </li>
 *			<li>4. Set data to PDF stream. </li>
 *			<li>5. Delete PDF objects. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Edit Add-on</b> explicitly.
 */

#ifndef _FSPDF_OBJECTS_W_H_
#define _FSPDF_OBJECTS_W_H_

/**
 * @defgroup	FPDFOBJECTS PDF Objects
 * @brief		Definitions for access to PDF objects.<br>
 *				Definitions and functions in this module are included in fpdf_objects_r.h and fpdf_objects_w.h.<br>
 *				Module: PDFObjects<br>
 *				License Identifier: PDFObjects/All<br>
 *				Available License Right: Reading/Writing<br>
 *				For License Right <b>Reading</b>, see fpdf_objects_r.h.<br>
 *				For License Right <b>Writing</b>, see fpdf_objects_w.h.
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. Object data retrieval: get object number or object type, and get object data.</li>
 *				<li>2. Object creation: create a PDF object and initialize it with given data.</li>
 *				<li>3. PDF array: enumerate array elements, get or set element object, insert or add element object.</li>
 *				<li>4. PDF dictionary: get or set properties (key/value pairs) of dictionary.</li>
 *				<li>5. PDF stream: get stream dictionary, get or set stream data, and export or import stream data.</li>
 *				<li>6. PDF reference: get the referred object.
 *				<li>7. Note: most functions in this module are not thread safe, caller should ensure not to call them
 *					   to process one document across multi-threads or should maintain thread safety by user application.</li>
 *				<li>8. Reference: section 3.2 in PDF Reference 1.7 describes PDF objects.</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Object creation                                                             */
/*******************************************************************************/
/**
 * @brief	Create a boolean PDF object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	boolean		A boolean value, <b>TRUE</b> or <b>FALSE</b>.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateBoolean(FSCRT_DOCUMENT document, FS_BOOL boolean, FSPDF_OBJECT* object);

/**
 * @brief	Create an integer number PDF object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	number		An integer value.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateInteger(FSCRT_DOCUMENT document, FS_INT32 number, FSPDF_OBJECT* object);

/**
 * @brief	Create a float number PDF object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	number		A float value.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateFloat(FSCRT_DOCUMENT document, FS_FLOAT number, FSPDF_OBJECT* object);

/**
 * @brief	Create a raw string PDF object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	string		Pointer to a ::FSCRT_BSTR structure which is a raw byte string value. If it's empty, an empty PDF string object is created.
 * @param[in]	hexStr		A boolean value indicates parameter <i>string</i> is a hexadecimal string if it's <b>TRUE</b> or normal byte string if it's <b>FALSE</b>.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>string</i> or <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateRawByteString(FSCRT_DOCUMENT document, const FSCRT_BSTR* string, FS_BOOL hexStr, FSPDF_OBJECT* object);

/**
 * @brief	Create an UTF-8 string PDF object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	string		Pointer to a ::FSCRT_BSTR structure which is an UTF-8 byte string value. If it's empty, an empty PDF string object is created.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>string</i> or <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>string</i> is not an UTF-8 format string.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateUnicodeString(FSCRT_DOCUMENT document, const FSCRT_BSTR* string, FSPDF_OBJECT* object);

/**
 * @brief	Create a date PDF object.
 *
 * @details	Date time expresses as a formatted string in PDF.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dt			Pointer to a ::FSCRT_DATETIMEZONE structure which is a date value.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dt</i> or <i>object</i> is a <b>NULL</b> pointer, 
 *			or paramter <i>dt</i> is invalid.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateDateTime(FSCRT_DOCUMENT document, const FSCRT_DATETIMEZONE* dt, FSPDF_OBJECT* object);

/**
 * @brief	Create an UTF-8 name PDF object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	nameStr		Pointer to a ::FSCRT_BSTR structure which is an UTF-8 byte string value. It cannot be <b>NULL</b> or be empty.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>nameStr</i> or <i>object</i> is a <b>NULL</b> pointer, or <i>nameStr</i> is empty.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>nameStr</i> is not an UTF-8 format string.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateUnicodeName(FSCRT_DOCUMENT document, const FSCRT_BSTR* nameStr, FSPDF_OBJECT* object);

/**
 * @brief	Create an array PDF object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateArray(FSCRT_DOCUMENT document, FSPDF_OBJECT* object);

/**
 * @brief	Create a rectangle PDF object.
 *
 * @details	Rectangle is a four-element array in PDF.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	rect		Pointer to a ::FSCRT_RECTF structure which is a rectangle value.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>rect</i> or <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateRect(FSCRT_DOCUMENT document, const FSCRT_RECTF* rect, FSPDF_OBJECT* object);

/**
 * @brief	Create a matrix PDF object.
 *
 * @details	Matrix is a six-element array in PDF.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object
 * @param[in]	matrix		Pointer to a ::FSCRT_MATRIX structure which is a matrix value.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>matrix</i> or <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateMatrix(FSCRT_DOCUMENT document, const FSCRT_MATRIX* matrix, FSPDF_OBJECT* object);

/**
 * @brief	Create a dictionary PDF object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateDict(FSCRT_DOCUMENT document, FSPDF_OBJECT* object);

/**
 * @brief	Create a stream PDF object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dictionary	Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 *							If it's a <b>NULL</b> pointer, a new PDF dictionary object is created for the new stream object.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, or parameter <i>dictionary</i> is not a PDF dictionary if it's valid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
  *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateStream(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, FSPDF_OBJECT* object);

/**
 * @brief	Create a reference PDF object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	refObj		Handle to a <b>FSPDF_OBJECT</b> object which is the referenced PDF object.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>refObj</i> or <i>object</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>refObj</i>: this handle is short-term.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateReference(FSCRT_DOCUMENT document, FSPDF_OBJECT refObj, FSPDF_OBJECT* object);

/**
 * @brief	Create a reference PDF object with an object number.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	objNum		Object number of an indirect PDF object for which a referenced PDF object is created. It should be above 0.
 * @param[out]	object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a new PDF object.
 *							If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i> or <i>object</i> is a <b>NULL</b> pointer, or if parameter <i>objNum</i> is 0.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_CreateReferenceWithObjNum(FSCRT_DOCUMENT document, FS_DWORD objNum, FSPDF_OBJECT* object);

/**
 * @brief	Release a PDF object created but not inserted into any PDF document or other PDF objects.
 *
 * @details	This function is used to release PDF objects which are created by functions <b>FSPDF_Object_CreateXXX</b>, 
 *			but is not set to another PDF object associated with PDF document or inserted to PDF document.<br>
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	object		Handle to a <b>FSPDF_OBJECT</b> object which is an object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>object</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Object_Release(FSCRT_DOCUMENT document, FSPDF_OBJECT object);

/*******************************************************************************/
/* PDF array access                                                            */
/*******************************************************************************/
/**
 * @brief	Insert an element into array.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	index			The index starting from 0, indicates position where <i>element</i> inserts.<br>
 *								If this is below 0 or count of element in parameter <i>array</i> is 0, parameter <i>element</i> is to be set to the first.<br>
 *								If this is larger than count of element in parameter <i>array</i>, parameter <i>element</i> is to be set to the last.
 * @param[in]	element			Handle to a <b>FSPDF_OBJECT</b> object to be inserted as an element.
 *
 * @note	All elements in an array object will be managed with the array object, 
 *			so parameter <i>element</i> must <b>NOT</b> be freed by caller if successful.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>element</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If parameter <i>index</i> is out of range of count of <i>array</i>, <i>element</i> will be added to the last position.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
  *				<li> <i>array</i>: this handle is short-term.</li>
 *				<li> <i>element</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_InsertAt(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FSPDF_OBJECT element);

/**
 * @brief	Set a new element at parameter <i>index</i> position in array.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[in]	element			Handle to a <b>FSPDF_OBJECT</b> object to be set as a new element.
 *
 * @note	All elements in an array object will be managed with the array object, 
 *			so parameter <i>element</i> must <b>NOT</b> be freed by caller if successful.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>element</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
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
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				<li> <i>element</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_SetAt(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FSPDF_OBJECT element);

/**
 * @brief	Add an element into array, to the last position.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	element			Handle to a <b>FSPDF_OBJECT</b> object to be added as an element.
 *
 * @note	All elements in an array object will be managed with the array object, 
 *			so parameter <i>element</i> must <b>NOT</b> be freed by caller if successful.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>element</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				<li> <i>element</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_Add(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FSPDF_OBJECT element);

/**
 * @brief	Add a boolean element into array, to the last position.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	boolean			A boolean value to be added as an element.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i> or <i>array</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_AddBoolean(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_BOOL boolean);

/**
 * @brief	Add an integer element into array, to the last position.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	number			An integer value to be added as an element.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i> or <i>array</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_AddInteger(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 number);

/**
 * @brief	Add a float element into array, to the last position.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	number			A float value to be added as an element.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i> or <i>array</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_AddFloat(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_FLOAT number);

/**
 * @brief	Add a raw string element into array, to the last position.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	hexStr			A boolean value indicates <i>string</i> is a hexadecimal string if it's <b>TRUE</b> 
 *								or normal byte string if it's <b>FALSE</b>.
 * @param[in]	string			Pointer to a ::FSCRT_BSTR structure that is a raw byte string value to be added as an element.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>string</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_AddRawByteString(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_BOOL hexStr, const FSCRT_BSTR* string);

/**
 * @brief	Add an UTF-8 string element into array, to the last position.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	string			Pointer to a ::FSCRT_BSTR structure which is an UTF-8 byte string value to be added as an element.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>string</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>string</i> is not an UTF-8 string.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.<br>
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_AddUnicodeString(FSCRT_DOCUMENT document, FSPDF_OBJECT array, const FSCRT_BSTR* string);

/**
 * @brief	Add a date and time element into array, to the last position.
 *
 * @details	Date and time is a formatted string in PDF.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	dt				Pointer to a ::FSCRT_DATETIMEZONE structure which is a date value to be added as an element.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>dt</i> is a <b>NULL</b> pointer, 
 *			or parameter <i>dt</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_AddDateTime(FSCRT_DOCUMENT document, FSPDF_OBJECT array, const FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Add an UTF-8 name element into array, to the last position.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	nameStr			Pointer to a ::FSCRT_BSTR structure which is an UTF-8 name value to be added as an element.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>nameStr</i> is a <b>NULL</b> pointer, or <i>nameStr</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>nameStr</i> is not an UTF-8 string.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.<br>
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_AddUnicodeName(FSCRT_DOCUMENT document, FSPDF_OBJECT array, const FSCRT_BSTR* nameStr);

/**
 * @brief	Add a rectangle element into array, to the last position.
 *
 * @details	Rectangle is a four-element array in PDF.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	rect			Pointer to a ::FSCRT_RECTF structure which is a rectangle value to be added as an element.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>rect</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_AddRect(FSCRT_DOCUMENT document, FSPDF_OBJECT array, const FSCRT_RECTF* rect);

/**
 * @brief	Add a matrix element into array, to the last position.
 *
 * @details	Matrix is a six-element array in PDF.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	matrix			Pointer to a ::FSCRT_MATRIX structure which is a matrix value to be added as an element.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>matrix</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_AddMatrix(FSCRT_DOCUMENT document, FSPDF_OBJECT array, const FSCRT_MATRIX* matrix);

/**
 * @brief	Remove an element from array.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i> or <i>array</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
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
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_RemoveAt(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index);

/*******************************************************************************/
/* PDF dictionary access                                                       */
/*******************************************************************************/
/**
 * @brief	Set an object as value to specific key in dictionary.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it should be a valid pointer to ::FSCRT_BSTR.
 * @param[in]	object			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF object value associated with <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>object</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set an object in dictionary for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_SetAt(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FSPDF_OBJECT object);

/**
 * @brief	Set a boolean value with specific key in dictionary.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it is a valid pointer to ::FSCRT_BSTR.
 * @param[in]	boolean			A boolean value associated with <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i> or <i>key</i> is a <b>NULL</b> pointer, or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter<i>document</i> is not a PDF document or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if the parameter<i>key</i> is not an UTF-8 format string.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set a boolean value in dictionary for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_SetAtBoolean(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FS_BOOL boolean);

/**
 * @brief	Set an integer value to specific key in dictionary.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, a valid pointer to ::FSCRT_BSTR.
 * @param[in]	number			An integer value associated with <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i> or <i>key</i> is a <b>NULL</b> pointer, or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set an integer value in dictionary for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_SetAtInteger(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FS_INT32 number);

/**
 * @brief	Set a float value to specific key in dictionary.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, a valid pointer to ::FSCRT_BSTR.
 * @param[in]	number			A float value associated with <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i> or <i>key</i> is a <b>NULL</b> pointer, or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set a float value in dictionary for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_SetAtFloat(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FS_FLOAT number);

/**
 * @brief	Set a raw byte string value to specific key in dictionary.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, a valid pointer to ::FSCRT_BSTR.
 * @param[in]	hexStr			A boolean value indicates <i>string</i> is a hexadecimal string if it's <b>TRUE</b> 
 *								or normal byte string if it's <b>FALSE</b>.
 * @param[in]	string			Pointer to a ::FSCRT_BSTR which is a raw byte string value associated with <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>string</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set a raw byte string value in dictionary for any other reason.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_SetAtRawByteString(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, 
											  FS_BOOL hexStr, const FSCRT_BSTR* string);

/**
 * @brief	Set a UTF-8 byte string value to specific key in dictionary.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string. It should be a valid pointer to ::FSCRT_BSTR.
 * @param[in]	string			Pointer to a ::FSCRT_BSTR which is an UTF-8 byte string value associated with <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>string</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> or parameter <i>string</i> is not an UTF-8 string.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set a UTF-8 string value in dictionary for any other reason.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_SetAtUnicodeString(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, const FSCRT_BSTR* string);

/**
 * @brief	Set a date and time value to specific key in dictionary.
 *
 * @details	Date and time is a formatted string in PDF.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned which is a PDF document object.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, a valid pointer to ::FSCRT_BSTR.
 * @param[in]	dt				Pointer to a ::FSCRT_DATETIMEZONE which is a date value associated with <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>dt</i> is a <b>NULL</b> pointer, 
 *			<i>key</i> is empty, or parameter <i>dt</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set a date and time format string value in dictionary for any other reason.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_SetAtDateTime(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, const FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Set a UTF-8 name value to specific key in dictionary.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, a valid pointer to ::FSCRT_BSTR.
 * @param[in]	nameStr			Pointer to a ::FSCRT_BSTR which is an UTF-8 name value associated with <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>nameStr</i> is a <b>NULL</b> pointer, or either <i>key</i> or <i>nameStr</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> or parameter <i>nameStr</i> is not an UTF-8 string.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set a UTF-8 name value in dictionary for any other reason.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_SetAtUnicodeName(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, const FSCRT_BSTR* nameStr);

/**
 * @brief	Set a rectangle value to specific key in dictionary.
 *
 * @details	Rectangle is a four-element array in PDF.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, a valid pointer to ::FSCRT_BSTR.
 * @param[in]	rect			Pointer to a ::FSCRT_RECTF structure which is a rectangle value associated with <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>rect</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set a rectangle value in dictionary for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_SetAtRect(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, const FSCRT_RECTF* rect);

/**
 * @brief	Set a matrix value to specific key in dictionary.
 *
 * @details	Matrix is a six-element array in PDF.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, a valid pointer to ::FSCRT_BSTR.
 * @param[in]	matrix			Pointer to a ::FSCRT_MATRIX structure which is a matrix value associated with <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>matrix</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to set a matrix value in dictionary for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_SetAtMatrix(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, const FSCRT_MATRIX* matrix);

/**
 * @brief	Remove a specific key from dictionary.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, a valid pointer to ::FSCRT_BSTR.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i> or <i>key</i> is a <b>NULL</b> pointer, or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if the parameter<i> document</i> is not a PDF document or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to remove a specific key from dictionary for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_RemoveAt(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key);

/*******************************************************************************/
/* PDF stream access                                                           */
/*******************************************************************************/
/**
 * @brief	Set stream data.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	stream			Handle to a <b>FSPDF_OBJECT</b> object that is a PDF stream object.
 * @param[in]	buffer			Valid pointer to a memory block.
 * @param[in]	length			Size of <i>buffer</i> in bytes.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>stream</i> or <i>buffer</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>stream</i> is not a type of PDF stream.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	It's not a good manner to set a large data by using this function, instead of calling function ::FSPDF_Stream_ImportData.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>stream</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Stream_SetData(FSCRT_DOCUMENT document, FSPDF_OBJECT stream, FS_LPCVOID buffer, FS_DWORD length);

/**
 * @brief	Import stream data from a file.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	stream			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF stream object.
 * @param[in]	file			Handle to a <b>FSCRT_FILE</b> object that from which <i>stream</i> data imports.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>stream</i> or <i>file</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>stream</i> is not a type of PDF stream.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or using current function is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This function is more efficient than function ::FSPDF_Stream_SetData to large data. 
 *			Application can optimize to read data through parameter <i>file</i>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it for the same objects under multi-threaded environment;
 *				otherwise, the application should be synchronized.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>stream</i>: this handle is short-term.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Stream_ImportData(FSCRT_DOCUMENT document, FSPDF_OBJECT stream, FSCRT_FILE file);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFOBJECTS */

#endif // _FSPDF_OBJECTS_W_H_
