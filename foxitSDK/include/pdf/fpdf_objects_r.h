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
 * @file	fpdf_objects_r.h
 * @brief	Header file for \ref FPDFOBJECTS "PDF Objects" module of Foxit PDF SDK.
 * @details	This header file provides direct access to PDF objects.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Get values from PDF objects. </li>
 *			<li>2. Get values form PDF array. </li>
 *			<li>3. Get values form PDF dictionary. </li>
 *			<li>4. Get data and dictionary form PDF stream. </li>
 *			<li>5. Get the referred object associated to a reference object.</li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> explicitly.
 */

#ifndef _FSPDF_OBJECTS_R_H_
#define _FSPDF_OBJECTS_R_H_

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
/* PDF object types                                                            */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_OBJECTYPE_
#define _FSPDF_DEF_MACRO_OBJECTYPE_
/**
 * @name	Macro Definitions for PDF Object Types.
 */
/**@{*/

/** @brief	Invalid PDF object. */
#define		FSPDF_OBJECTTYPE_INVALID		0
/** @brief	PDF object type for boolean. */
#define		FSPDF_OBJECTTYPE_BOOLEAN		1
/** @brief	PDF object type for integer or real number. */
#define		FSPDF_OBJECTTYPE_NUMBER			2
/** @brief	PDF object type for string. */
#define		FSPDF_OBJECTTYPE_STRING			3
/** @brief	PDF object type for name. */
#define		FSPDF_OBJECTTYPE_NAME			4
/** @brief	PDF object type for array. */
#define		FSPDF_OBJECTTYPE_ARRAY			5
/** @brief	PDF object type for dictionary. */
#define		FSPDF_OBJECTTYPE_DICTIONARY		6
/** @brief	PDF object type for stream. */
#define		FSPDF_OBJECTTYPE_STREAM			7
/** @brief	PDF object type for a null object. */
#define		FSPDF_OBJECTTYPE_NULL			8
/** @brief	PDF object type for a reference object. */
#define		FSPDF_OBJECTTYPE_REFERENCE		9

/**@}*/
#endif /* _FSPDF_DEF_MACRO_OBJECTYPE_ */

/*******************************************************************************/
/* Object data retrieval                                                       */
/*******************************************************************************/
/**
 * @brief	Get the type of an object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	object		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF object.
 * @param[out]	type		Pointer to a ::FS_INT32 object that receives the object type.
 *							Please refer to macro definitions <b>FSPDF_OBJECTTYPE_XXX</b> and this should be one of these macros.<br>
 *							If there's any error, it will become ::FSPDF_OBJECTTYPE_INVALID.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> or <i>type</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
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
FS_RESULT FSPDF_Object_GetType(FSCRT_DOCUMENT document, FSPDF_OBJECT object, FS_INT32* type);

/**
 * @brief	Get the object number.
 *
 * @details	If a PDF object is an indirect object, it will has a valid object number which is greater than 0.<br>
 * 			If object number is 0, it means this PDF object is a direct object.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	object		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF object.
 * @param[out]	objNum		Pointer to a ::FS_DWORD object that receives the object number.
 *							If there's any error, it will become 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> or <i>objNum</i> is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
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
FS_RESULT FSPDF_Object_GetObjNum(FSCRT_DOCUMENT document, FSPDF_OBJECT object, FS_DWORD* objNum);

/**
 * @brief	Get boolean value from a PDF object.
 *
 * @details	Applicable for number and boolean objects.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	object		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF object.
 * @param[out]	boolean		Pointer to a ::FS_BOOL object that receives the boolean value.
 *							If there's any error or if object type is not supported,it will be set <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> or <i>boolean</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.
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
FS_RESULT FSPDF_Object_GetBoolean(FSCRT_DOCUMENT document, FSPDF_OBJECT object, FS_BOOL* boolean);

/**
 * @brief	Get integer value from a PDF object.
 *
 * @details	Applicable for number and boolean objects.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	object		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF object.
 * @param[out]	number		Pointer to a ::FS_INT32 object that receives the integer value.
 *							If there's any error or if object type is not supported, it will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> or <i>number</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
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
FS_RESULT FSPDF_Object_GetInteger(FSCRT_DOCUMENT document, FSPDF_OBJECT object, FS_INT32* number);

/**
 * @brief	Get float value from a PDF object.
 *
 * @details	Applicable to number objects.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	object		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF object.
 * @param[out]	number		Pointer to a ::FS_FLOAT object that receives the float value.
 *							If there's any error or if object type not supported,it will be set 0.0f.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> or <i>number</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
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
FS_RESULT FSPDF_Object_GetFloat(FSCRT_DOCUMENT document, FSPDF_OBJECT object, FS_FLOAT* number);

/**
 * @brief	Get the raw byte string value from a PDF object.
 *
 * @details	The raw byte string is original string value in PDF, and is not encoded or decoded.<br>
 *			Applicable for string, name, number and boolean objects.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	object		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF object.
 * @param[out]	string		Pointer to a ::FSCRT_BSTR structure that receives the raw byte string value.<br>
 *							If there's any error or if object type not supported, FSCRT_BSTR::str will be empty if it's not <b>NULL</b>,
 *							and FSCRT_BSTR::len will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> or <i>string</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If <i>string</i> is empty or doesn't have enough memory, this function will allocate memory by calling function ::FSCRT_BStr_SetLength.<br>
 * 			It's better for caller to prepare enough space before calling this function if possible.
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
FS_RESULT FSPDF_Object_GetRawByteString(FSCRT_DOCUMENT document, FSPDF_OBJECT object, FSCRT_BSTR* string);

/**
 * @brief	Get the UTF-8 byte string value from a PDF object.
 *
 * @details	Applicable to string, name, number and boolean objects.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	object		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF object.
 * @param[out]	string		Pointer to a ::FSCRT_BSTR structure that receives the UTF-8 byte string value.<br>
 *							If there's any error or if object type not supported, FSCRT_BSTR::str will be empty if it's not <b>NULL</b>,
 *							and FSCRT_BSTR::len will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> or <i>string</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.<br>
 * 			If parameter <i>string</i> is empty or doesn't have enough memory, this function will allocate memory by calling ::FSCRT_BStr_SetLength.<br>
 * 			It's better for caller to prepare enough space before calling this function if possible.
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
FS_RESULT FSPDF_Object_GetUnicodeString(FSCRT_DOCUMENT document, FSPDF_OBJECT object, FSCRT_BSTR* string);

/**
 * @brief	Get the date value from a PDF object.
 *
 * @details	Date and time is a formatted string in PDF.
 *			Applicable to properly formatted string objects.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	object		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF object.
 * @param[out]	dt			Pointer to a ::FSCRT_DATETIMEZONE structure that receives the date and time value.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> or <i>dt</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>object</i> is empty or is not a date format.<br>
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
FS_RESULT FSPDF_Object_GetDateTime(FSCRT_DOCUMENT document, FSPDF_OBJECT object, FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Get rectangle value from a PDF object.
 *
 * @details	Rectangle is a four-element array in PDF.
 *			Applicable to array objects.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	object		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF object.
 * @param[out]	rect		Pointer to a ::FSCRT_RECTF structure that receives the rectangle value.
 *							If there's any error or if object type not supported, it will be [0 0 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> or <i>rect</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, or parameter <i>object</i> is not a PDF array object.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>object</i> is empty or is not a rectangle.<br>
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
FS_RESULT FSPDF_Object_GetRect(FSCRT_DOCUMENT document, FSPDF_OBJECT object, FSCRT_RECTF* rect);

/**
 * @brief	Get matrix value from a PDF object.
 *
 * @details	Matrix is a six-element array in PDF.
 *			Applicable to array objects.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	object		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF object.
 * @param[out]	matrix		Pointer to a ::FSCRT_MATRIX structure that receives the matrix value.
 *							If there's any error or if object type not supported, it will be set [1 0 0 1 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>object</i> or <i>matrix</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, or parameter <i>object</i> is not a PDF array object.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>object</i> is empty or is not a matrix.<br>
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
FS_RESULT FSPDF_Object_GetMatrix(FSCRT_DOCUMENT document, FSPDF_OBJECT object, FSCRT_MATRIX* matrix);

/*******************************************************************************/
/* PDF array access                                                            */
/*******************************************************************************/
/**
 * @brief	Get the count of elements in an array.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF array object.
 * @param[out]	count			Pointer to a ::FS_INT32 object that receives the count of array elements.
 *								If there's any error or if object type not supported, it will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>count</i> is a <b>NULL</b> pointer<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or <i>array</i> is not a type of PDF array.<br>
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
FS_RESULT FSPDF_Array_CountElements(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32* count);

/**
 * @brief	Get an element in an array.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	object			Pointer to a <b>FSPDF_OBJECT</b> handle that receives element object.
 *								If there's any error or if object type not supported, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>object</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, or <i>array</i> is not a type of PDF array.<br>
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
 *				<li> <i>object</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_GetElement(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FSPDF_OBJECT* object);

/**
 * @brief	Get a boolean element in an array.
 *
 * @details	Applicable to array elements of number and boolean type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	boolean			Pointer to a ::FS_BOOL object that receives a boolean value.
 *								If there's any error or if object type not supported, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>boolean</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, 
 *			or parameter <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or no element is found.<br>
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
FS_RESULT FSPDF_Array_GetBoolean(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FS_BOOL* boolean);

/**
 * @brief	Get an integer element in an array.
 *
 * @details	Applicable to array elements of number and boolean type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	number			Pointer to a ::FS_INT32 object that receives an integer value.
 *								If there's any error or if object type not supported, it will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>number</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, 
 *			or parameter <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or no element is found.<br>
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
FS_RESULT FSPDF_Array_GetInteger(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FS_INT32* number);

/**
 * @brief	Get a float element in an array.
 *
 * @details	Applicable to array elements of number type..
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	number			Pointer to a ::FS_FLOAT object that receives a float value.
 *								If there's any error or if object type not supported, it will be 0.0f.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>number</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document,
 *			or parameter <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range  or no element is found.<br>
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
FS_RESULT FSPDF_Array_GetFloat(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FS_FLOAT* number);

/**
 * @brief	Get a raw byte string element in an array.
 *
 * @details	Applicable to array elements of string, name, number and boolean type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	string			Pointer to a ::FSCRT_BSTR structure that receives a raw byte string value.<br>
 *								If there's any error or if object type not supported, FSCRT_BSTR::str will be empty if it's not <b>NULL</b> when call this function,
 *								and FSCRT_BSTR::len will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>string</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, 
 *			or parameter <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or no element is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If parameter <i>string</i> is empty or doesn't have enough memory, this function will allocate memory by calling function ::FSCRT_BStr_SetLength.<br>
 * 			It's better for caller to prepare enough space before calling this function if possible.
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
FS_RESULT FSPDF_Array_GetRawByteString(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FSCRT_BSTR* string);

/**
 * @brief	Get an UTF-8 byte string element in an array.
 *
 * @details	Applicable to array elements of string, name, number and boolean type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	string			Pointer to a ::FSCRT_BSTR structure that receives an UTF-8 byte string value.<br>
 *								If there's any error or if object type not supported, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b> when call this function, 
 *								and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>string</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, 
 *			or parameter <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or no element is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.<br>
 * 			If parameter <i>string</i> is empty or doesn't have enough memory, this function will allocate memory by calling function ::FSCRT_BStr_SetLength.<br>
 * 			It's better for caller to prepare enough space before calling this function if possible.
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
FS_RESULT FSPDF_Array_GetUnicodeString(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FSCRT_BSTR* string);

/**
 * @brief	Get a date and time element in an array.
 *
 * @details	Date and time expresses as a formatted string in PDF.
 *			Applicable to array elements of properly formatted string type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	dt				Pointer to a ::FSCRT_DATETIMEZONE structure that receives a date value.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>dt</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, 
 *			or parameter <i>array</i> is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range or no element is found.<br>
 * 			::FSCRT_ERRCODE_FORMAT if string content of element at parameter <i>index</i> position is empty or is not a date format.<br>
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
FS_RESULT FSPDF_Array_GetDateTime(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Get an array element in an array.
 *
 * @details	Applicable to array elements of array type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	subArray		Pointer to a <b>FSPDF_OBJECT</b> handle that receives an array value.
 * 								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>subArray</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, 
 *			parameter <i>array</i> is not a type of PDF array, or element at <i>index</i> position is not an array.<br>
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
FS_RESULT FSPDF_Array_GetArray(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FSPDF_OBJECT* subArray);

/**
 * @brief	Get a rectangle element in an array.
 *
 * @details	Rectangle expresses as a four-element array in PDF.
 *			Applicable to array elements of array type, especially for rectangle.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	rect			Pointer to a ::FSCRT_RECTF structure that receives a rectangle value.
 *								If there's any error, it will be [0 0 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>rect</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, 
 *			parameter <i>array</i> is not a type of PDF array, or element at <i>index</i> position is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_FORMAT if element at <i>index</i> position is empty or is not a rectangle.<br>
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
FS_RESULT FSPDF_Array_GetRect(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FSCRT_RECTF* rect);

/**
 * @brief	Get a matrix element in an array.
 *
 * @details	Matrix expresses as a six-element array in PDF.
 *			Applicable to array elements of array type, especially for matrix.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	matrix			Pointer to a ::FSCRT_MATRIX structure that receives a matrix value.
 *								If there's any error, it will be [1 0 0 1 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>matrix</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, 
 *			parameter <i>array</i> is not a type of PDF array, or element at <i>index</i> position is not a type of PDF array.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_FORMAT if element at <i>index</i> position is empty or is not a matrix.<br>
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
FS_RESULT FSPDF_Array_GetMatrix(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FSCRT_MATRIX* matrix);

/**
 * @brief	Get a dictionary element in an array.
 *
 * @details	Applicable to array elements of dictionary type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	dictionary		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a dictionary value.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>dictionary</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, 
 *			parameter <i>array</i> is not a type of PDF array, or element at <i>index</i> position is not a dictionary.<br>
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
  *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_GetDict(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FSPDF_OBJECT* dictionary);

/**
 * @brief	Get a stream element in an array.
 *
 * @details	Applicable to array elements of stream type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	array			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF array object.
 * @param[in]	index			Index of element. Range: 0 to (count-1).  <i>count</i> is returned by function ::FSPDF_Array_CountElements.
 * @param[out]	stream			Pointer to a <b>FSPDF_OBJECT</b> handle that receives a stream value.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>array</i> or <i>stream</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, 
 *			parameter <i>array</i> is not a type of PDF array, or element at <i>index</i> position is not a stream.<br>
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
 *				<li> <i>stream</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Array_GetStream(FSCRT_DOCUMENT document, FSPDF_OBJECT array, FS_INT32 index, FSPDF_OBJECT* stream);

/*******************************************************************************/
/* PDF dictionary access                                                       */
/*******************************************************************************/
/**
 * @brief	Determine whether a specific key exists in a dictionary or not.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it should be a valid pointer to ::FSCRT_BSTR.
 * @param[out]	exist			Pointer to a ::FS_BOOL object that receives a boolean value which indicates <i>key</i> exists or not: 
 *								<ul>
 *								<li><b>TRUE</b>: parameter <i>key</i> exists.</li>
 *								<li><b>FALSE</b>: parameter <i>key</i> doesn't exist.</li>
 *								</ul>
 *								If there's any error, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>exist</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 *			::FSCRT_ERRCODE_ERROR if this function gets error for any other reason.<br>
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
FS_RESULT FSPDF_Dictionary_HasKey(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FS_BOOL* exist);

/**
 * @brief	Get an element from dictionary.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it should be a valid pointer to ::FSCRT_BSTR.
 * @param[out]	object			Pointer to a <b>FSPDF_OBJECT</b> handle that receives a PDF object associated with <i>key</i>.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>object</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary or no object is found.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get elements from dictionary object for any other reason.<br>
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
FS_RESULT FSPDF_Dictionary_GetElement(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FSPDF_OBJECT* object);

/**
 * @brief	Enumerate entries in a dictionary and retrieve a key and a PDF object at a given position.
 *
 * @details	This function can be used to enumerate all entries in a dictionary by calling several times until ::FSCRT_ERRCODE_FINISHED is returned.
 *
 * @param[in]		document	Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]		dictionary	Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in,out]	position	Pointer to a <b>FSCRT_POSITION</b> object which represents the position of an entry.
 *								When this function is called, it represents the position of an entry -- the key and value of this entry are to be retrieved.
 *								If call this function for first time, please pass a <b>FSPDF_POSITION</b> object with value <b>NULL</b> , in order to retrieved the first entry in dictionary.<br>
 *								When this function returns, it will receive the position of next entry.
 *								If there's no more entry to be enumerated, a <b>FSPDF_POSITION</b> object with value -1 will be returned.
 * @param[out]		key			Pointer to a ::FSCRT_BSTR structure (a UTF-8 string) that receives value of an entry's key.<br>
 *								If there's any error, FSCRT_BSTR::str will be empty if it's not <b>NULL</b>,
 *								and FSCRT_BSTR::len will be set to 0.
 * @param[out]		object		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a PDF object which is the value of an entry and associated with parameter <i>key</i>.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_TOBECONTINUED if an entry is retrieved, and there're still other entries to be retrieved.<br>
 *			::FSCRT_ERRCODE_FINISHED if no more entries can be retrieved.<br> 
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>position</i>, <i>key</i> or <i>object</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, or parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to enumerate entry from dictionary object for any other reason.<br>
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
FS_RESULT FSPDF_Dictionary_EnumEntry(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, FSCRT_POSITION* position, FSCRT_BSTR* key, FSPDF_OBJECT* object);

/**
 * @brief	Get a boolean value from dictionary.
 *
 * @details	Applicable to dictionary elements of number and boolean type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it should be a valid pointer to ::FSCRT_BSTR.
 * @param[out]	boolean			Pointer to a ::FS_BOOL object that receives a boolean value associated with <i>key</i>.
 *								If there's any error or if object type not supported, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>boolean</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary or no object is found.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get boolean value from dictionary object for any other reason.<br>
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
FS_RESULT FSPDF_Dictionary_GetBoolean(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FS_BOOL* boolean);

/**
 * @brief	Get an integer value from dictionary.
 *
 * @details	Applicable to dictionary elements of number and boolean type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it is a valid pointer to ::FSCRT_BSTR.
 * @param[out] 	number			Pointer to a ::FS_INT32 object that receives an integer value associated with <i>key</i>.
 *								If there's any error or if object type not supported, it will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>number</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary or no object is found.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get integer number value from dictionary object for any other reason.<br>
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
FS_RESULT FSPDF_Dictionary_GetInteger(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FS_INT32* number);

/**
 * @brief	Get a float value from dictionary.
 *
 * @details	Applicable to dictionary elements of number type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it should be a valid pointer to ::FSCRT_BSTR.
 * @param[out]	number			Pointer to a ::FS_FLOAT object that receives a float value associated with <i>key</i>.
 *								If there's any error or if object type not supported, it will be set 0.0f.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>number</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary or no object is found.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get float value from dictionary object for any other reason.<br>
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
FS_RESULT FSPDF_Dictionary_GetFloat(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FS_FLOAT* number);

/**
 * @brief	Get a raw string value from dictionary.
 *
 * @details	Applicable to dictionary elements of string, name, number and boolean type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it is a valid pointer to ::FSCRT_BSTR.
 * @param[out]	string			Pointer to a ::FSCRT_BSTR structure that receives a raw string value associated with <i>key</i>.
 *								If there's any error or if object type not supported, FSCRT_BSTR::str will be empty if it's not <b>NULL</b>,
 *								and FSCRT_BSTR::len will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>string</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary or no object is found.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get raw byte string from dictionary object for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If <i>string</i> is empty or has not enough memory, this function will allocate memory by calling ::FSCRT_BStr_SetLength.<br>
 * 			It's better for caller to prepare enough space before calling this function if possible.
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
FS_RESULT FSPDF_Dictionary_GetRawByteString(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FSCRT_BSTR* string);

/**
 * @brief	Get an UTF-8 string value from dictionary.
 *
 * @details	Applicable to string, name, number and boolean dictionary elements.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it is a valid pointer to ::FSCRT_BSTR.
 * @param[out]	string			Pointer to a ::FSCRT_BSTR structure that receives an UTF-8 string value associated with <i>key</i>.
 *								If there's any error or if object type not supported, FSCRT_BSTR::str will be empty if it's not <b>NULL</b>,
 *								and FSCRT_BSTR::len will be 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>string</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary or no object is found.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get Unicode string from dictionary object for any other reason.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.<br>
 * 			If <i>string</i> is empty or doesn't have enough memory, this function will allocate memory by calling ::FSCRT_BStr_SetLength.<br>
 * 			It's better for caller to prepare enough space before calling this function if possible.
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
FS_RESULT FSPDF_Dictionary_GetUnicodeString(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FSCRT_BSTR* string);

/**
 * @brief	Get a date and time value from dictionary.
 *
 * @details	Date and time expresses as a formatted string in PDF.
 *			Applicable to dictionary elements of properly formatted string.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it should be a valid pointer to ::FSCRT_BSTR.
 * @param[out]	dt				Pointer to a ::FSCRT_DATETIMEZONE structure that receives a date and time value associated with <i>key</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>dt</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, parameter <i>dictionary</i> is not a type of PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary or no object is found.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string, 
 *			or element at parameter <i>key</i> position is empty or is not a date and time format.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get date and time format string from dictionary object for any other reason.<br>
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
FS_RESULT FSPDF_Dictionary_GetDateTime(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Get an array value from dictionary.
 *
 * @details	Applicable to dictionary elements of array type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it is a valid pointer to ::FSCRT_BSTR.
 * @param[out]	array			Pointer to a <b>FSPDF_OBJECT</b> object that receives a PDF array value associated with <i>key</i>.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>array</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, parameter <i>dictionary</i> is not a type of PDF dictionary 
 *			or element at parameter <i>key</i> position is not an array type.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get array from dictionary object for any other reason.<br>
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
 *				<li> <i>array</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_GetArray(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FSPDF_OBJECT* array);

/**
 * @brief	Get a rectangle value from dictionary.
 *
 * @details	Rectangle expresses as a four-element array in PDF.
 *			Applicable to dictionary elements of array type, especially for rectangle.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it is a valid pointer to ::FSCRT_BSTR.
 * @param[out]	rect			Pointer to a ::FSCRT_BSTR structure that receives a rectangle value associated with <i>key</i>.
 *								If there's any error, it will become [0 0 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>rect</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, parameter <i>dictionary</i> is not a type of PDF dictionary 
 *			or element at parameter <i>key</i> position is not an array.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string, 
 *			or element at <i>key</i> position is empty or is not a rectangle.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary or no object is found.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get rectangle value from dictionary object for any other reason.<br>
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
FS_RESULT FSPDF_Dictionary_GetRect(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FSCRT_RECTF* rect);

/**
 * @brief	Get a matrix value from dictionary.
 *
 * @details	Matrix expresses as a six-element array in PDF.
 *			Applicable to dictionary elements of array type, especially for matrix.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it is a valid pointer to ::FSCRT_BSTR.
 * @param[out]	matrix			Pointer to a ::FSCRT_BSTR structure that receives a matrix value associated with <i>key</i>.
 *								If there's any error, it will become [1 0 0 1 0 0].
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>matrix</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, parameter <i>dictionary</i> is not a type of PDF dictionary 
 *			or element at parameter <i>key</i> position is not an array.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string, 
 *			or element at <i>key</i> position is empty or is not a matrix.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary or no object is found.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get matrix value from dictionary object for any other reason.<br>
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
FS_RESULT FSPDF_Dictionary_GetMatrix(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FSCRT_MATRIX* matrix);

/**
 * @brief	Get a dictionary value from dictionary.
 *
 * @details	Applicable to dictionary elements of dictionary type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it is a valid pointer to ::FSCRT_BSTR.
 * @param[out]	subDictionary	Pointer to a <b>FSPDF_OBJECT</b> handle that receives a PDF dictionary value associated with <i>key</i>.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>subDictionary</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, parameter <i>dictionary</i> is not a type of PDF dictionary 
 *			or element at parameter <i>key</i> position is not a PDF dictionary.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get dictionary value from dictionary object for any other reason.<br>
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
 *				<li> <i>subDictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_GetDict(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FSPDF_OBJECT* subDictionary);

/**
 * @brief	Get a stream value from dictionary.
 *
 * @details	Applicable to dictionary elements of stream type.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	dictionary		Handle to a <b>FSPDF_OBJECT</b> object which is a PDF dictionary object.
 * @param[in]	key				Pointer to a UTF_8 string, it is a valid pointer to ::FSCRT_BSTR.
 * @param[out]	stream			Pointer to a <b>FSPDF_OBJECT</b> handle that receives a PDF stream value associated with <i>key</i>.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>dictionary</i>, <i>key</i> or <i>stream</i> is a <b>NULL</b> pointer, 
 *			or <i>key</i> is empty.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, parameter <i>dictionary</i> is not a type of PDF dictionary 
 *			or element at parameter <i>key</i> position is not a PDF stream.<br>
 * 			::FSCRT_ERRCODE_FORMAT if parameter <i>key</i> is not an UTF-8 format string.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>key</i> is not found in dictionary.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get stream value from dictionary object for any other reason.<br>
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
 *				<li> <i>stream</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Dictionary_GetStream(FSCRT_DOCUMENT document, FSPDF_OBJECT dictionary, const FSCRT_BSTR* key, FSPDF_OBJECT* stream);

/*******************************************************************************/
/* PDF stream access                                                           */
/*******************************************************************************/
/**
 * @brief	Get the dictionary object associated to a stream.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	stream			Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF stream object.
 * @param[out]	dictionary		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a PDF dictionary object associated with <i>stream</i>.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>stream</i> or <i>dictionary</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, or parameter <i>stream</i> is not a type of PDF stream.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get dictionary value from stream object for any other reason.<br>
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
 *				<li> <i>stream</i>: this handle is short-term.</li>
 *				<li> <i>dictionary</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Stream_GetDict(FSCRT_DOCUMENT document, FSPDF_OBJECT stream, FSPDF_OBJECT* dictionary);

/**
 * @brief	Get stream data.
 *
 * @param[in]		document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]		stream			Handle to a <b>FSPDF_OBJECT</b> object which is a PDF stream object.
 * @param[in]		rawData			A boolean value indicates to get raw data from <i>stream</i> if it's <b>TRUE</b>, or to get decoded data (original data) if it's <b>FALSE</b>.
 * @param[out]		buffer			Pointer to a memory block to receive stream data. If it's <b>NULL</b>, this function returns the needed buffer size into parameter <i>length</i>.
 * @param[in,out]	length			Pointer to a ::FS_DWORD to indicate data size in bytes.<br>
 *									When call this function, it means the size of parameter <i>buffer</i> if <i>buffer</i> isn't <b>NULL</b>, 
 *									When this function returns, it means the actual data size.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>stream</i> or <i>length</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>stream</i> is not a type of PDF stream.<br>
 * 			::FSCRT_ERRCODE_BUFFEROVERFLOW if parameter <i>buffer</i> doesn't have enough space or parameter <i>length</i> is too small.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Commonly, this function is called twice, pass <b>NULL</b> to <i>buffer</i> at first to retrieve necessary buffer size,
 *			and call it again when <i>buffer</i> contains enough space. <i>length</i> should never be empty.<br>
 *			It's better that caller prepares enough space before calling this function.<br>
 *			But it's not a good manner to get large data by using this function, instead of ::FSPDF_Stream_ExportData.
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
FS_RESULT FSPDF_Stream_GetData(FSCRT_DOCUMENT document, FSPDF_OBJECT stream, FS_BOOL rawData, FS_LPVOID buffer, FS_DWORD* length);

/**
 * @brief	Export stream data to a file asynchronously.
 *
 * @details	This function provides an asynchronous way to get the stream data. This function usually gets a large
 *			size of stream data in a progressive way. When this function returned, the application need to invoke function ::FSCRT_File_Read by
 *			passing the returned <b>FSCRT_FILE</b> to extract the data needed.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	stream			Handle to a <b>FSPDF_OBJECT</b> object that is a PDF stream object.
 * @param[in]	rawData			A boolean value indicates to export raw data from <i>stream</i> if it's <b>TRUE</b>, 
 *								or to export decoded data (original data) if it's <b>FALSE</b>.
 * @param[out]	file			Pointer to a <b>FSCRT_FILE</b> handle that receives the handle of file object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>stream</i> or <i>file</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document or parameter <i>stream</i> is not a type of PDF stream.<br>
 * 			::FSCRT_ERRCODE_FILE if the application cannot write <i>stream</i> data into parameter <i>file</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This function is more efficient than ::FSPDF_Stream_GetData to large stream data. 
 *			Application can optimize to write data through <i>file</i> stream.
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
FS_RESULT FSPDF_Stream_ExportData(FSCRT_DOCUMENT document, FSPDF_OBJECT stream, FS_BOOL rawData, FSCRT_FILE* file);

/*******************************************************************************/
/* PDF reference access                                                        */
/*******************************************************************************/

/**
 * @brief	Get the referred object associated to a reference object.
 *
 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object returned by function ::FSPDF_Doc_StartLoad.
 * @param[in]	reference		Handle to a <b>FSPDF_OBJECT</b> object which should be a PDF reference object.
 * @param[out]	referObj		Pointer to a <b>FSPDF_OBJECT</b> handle that receives a PDF referred object associated with <i>reference</i>.
 *								If there's any error, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>reference</i> or <i>referObj</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a PDF document, or parameter <i>reference</i> is not a type of PDF reference.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if <i>referObj</i> is not found in <i>document</i>.
 *			::FSCRT_ERRCODE_ERROR if fail to get <i>referObj</i> value from reference object for any other reason.<br>
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
 *				<li> <i>reference</i>: this handle is short-term.</li>
 *				<li> <i>referObj</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_Reference_GetReferObject(FSCRT_DOCUMENT document, FSPDF_OBJECT reference, FSPDF_OBJECT* referObj);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFOBJECTS */

#endif // _FSPDF_OBJECTS_R_H_
