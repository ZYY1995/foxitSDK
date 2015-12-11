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
 * @file	fs_base_r.h
 * @brief	Header file for \ref FSBASE "Base" module of Foxit PDF SDK.
 * @details	This header file defines basic data types and functions which are used in the other modules.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Basic type and error code definitions. </li>
 *			<li>2. Utilities for byte string. </li>
 *			<li>3. File stream access. </li>
 *			<li>4. Library and memory management controls. </li>
 *			<li>5. Supports for multiple thread environment. </li>
 *			<li>6. Common structures: date, rectangle, matrix, and some helper functions. </li>
 *			<li>7. Private data access. </li>
 *			<li>8. Common objects: document, page, and helper functions. </li>
 *			<li>9. Progress controls: pause callback handler, progressive functions. </li>
 *			<li>10. Font supports: font mapper, creation and properties access. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> explicitly.
 */

#ifndef _FSCRT_BASE_R_H_
#define _FSCRT_BASE_R_H_

/** 
 * @defgroup	FSBASE Base
 * @brief		Base data structure and operation definitions for Foxit PDF SDK.<br>
 *				Definitions and functions in this module are included in fs_base_r.h and fs_codec_r.h.<br>
 *				Module: Base<br>
 *				License Identifier: Base/All<br>
 *				Available License Right: unnecessary
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. Basic definitions: involve definitions for basic types, error codes and variable types.</li>
 *				<li>2. Byte string:
 *					<ul>
 *					<li>a. In Foxit PDF SDK, byte string is defined as ::FSCRT_BSTR structure.
 *						   It is commonly used as input or output parameters.</li>
 *					<li>b. Related functions can used to initialize, clear string data, or set its contents.
 *						   ::FSCRT_BSTR shall be UTF-8 format for common string data.
 *						   It can be used as binary string data in some functions.</li>
 *					<li>c. Note: length is used to judge whether a byte string is terminated rather than '\0'.</li>
 *					</ul>
 *				</li>
 *				<li>3. UTF-8 conversion: convert strings from UTF-8 to UTF-16LE, UTF-16BE, UTF-32LE or UTF-32BE and reversion.</li>
 *				<li>4. Base-64: encode data to Base-64 string or decode data from Base-64 string.</li>
 *				<li>5. Digest: calculate digest by algorithms: MD5, SHA1, SHA256, SHA384, SHA512.</li>
 *				<li>6. Flate: compress or decompress data by flate or deflate algorithms.</li>
 *				<li>7. File access:
 *					<ul>
 *					<li>a. Create file object from ::FSCRT_FILEHANDLER or from file name directly, and retrieve file size.</li>
 *					<li>b. ::FSCRT_FILEHANDLER is an extension interface to support variant stream I/O.</li>
 *					<li>c. Note: implementers of ::FSCRT_FILEHANDLER shall make sure thread safety if applications need to support multi-thread.</li>
 *					</ul>
 *				</li>
 *				<li>8. Library management:
 *					<ul>
 *					<li>a. Initialize library manager or destroy library manager, unlock library with license data, support log file and allocate or free memory.</li>
 *					<li>b. Any applications shall initialize Foxit PDF SDK before call PDF SDK API functions.</li>
 *					<li>c. Note: a log file is used to collect information for debugging. It's not recommended to set a log file without debugging.</li>
 *					</ul>
 *				</li>
 *				<li>9. Multi-thread:
 *					<ul>
 *					<li>a. Provide ::FSCRT_THREADHANDLER to support multi-thread in PDF SDK level.</li>
 *					<li>b. The support to multi-thread makes PDF SDK and applications more robust than before.</li>
 *					</ul>
 *				</li>
 *				<li>10. Common data structures: 
 *					<ul>
 *					<li>a. Involve date, integer or float rectangle, quad points, matrix and path data.</li>
 *					<li>b. These features provide common supports on coordinates.</li>
 *					</ul>
 *				</li>
 *				<li>11. Private data: applications can set some private data into PDF SDK library.
 *						Private data can be shared among several executive modules.</li>
 *				<li>12. Common objects: documents, pages and annotations are three types of common objects.</li>
 *				<li>13. Progressive control: 
 *					<ul>
 *					<li>a. Progressive control is designed for long-time-occupancy processes.</li>
 *					<li>b. PDF SDK provide some important functionalities, such as saving PDF or encrypting PDF. They usually take long time to finish.
 *						   In order to avoid occupying too much time in one thread, PDF SDK introduces the mechanism of progressive control. 
                           It can divide one process into several phases and leave time to other threads or processes during between two phases.</li>
 *					</ul>
 *				</li>
 *				<li>14. Font access: 
 *					<ul>
 *					<li>a. Create font, retrieve font properties, or set font mapper.</li>
 *					<li>b. Font is one of the most important resources and is used for text display.
 *						   Applications can create a new font or get a existing font in PDF.</li>
 *					<li>c. Reference: It's described in chapter 5 of PDF Reference 1.7 about PDF text and font.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Base types                                                                  */
/*                                                                             */
/* Basic types, handle definitions, error codes and variants                   */
/*******************************************************************************/
#ifndef _FSCRT_DEF_TYPE_BASETYPES_
#define _FSCRT_DEF_TYPE_BASETYPES_
/**
 * @name	Basic Types Definitions
 * @note	In order to support cross platforms, PDF SDK defines basic types for applications or other modules 
 *			to use. It's highly recommended for applications to use these types rather than other types.
 *			Applications need to convert C/C++ standard types to PDF SDK supporting types.
 */
/**@{*/

/** @brief	A pointer to any types. */
typedef void*					FS_LPVOID;

/** @brief	A constant pointer to any types. */
typedef void const*				FS_LPCVOID;

/** @brief	Boolean type (This should be <b>TRUE</b> or <b>FALSE</b>). */
typedef int						FS_BOOL;

/** @brief	An unsigned byte integer (8 bits). */
typedef unsigned char			FS_BYTE;

/** @brief	16-bit unsigned integer. */
typedef unsigned short			FS_WORD;

/** @brief	32-bit unsigned integer. */
typedef unsigned int			FS_DWORD;

/** @brief	ARGB color type, 32 bits, ((b) | ((g) << 8) | ((r) << 16)) | ((a) << 24) */
typedef unsigned int			FS_ARGB;

/** @brief	32-bit floating-point number, single precision. */
typedef float					FS_FLOAT;

/** @brief	8-bit character. */
typedef char					FS_CHAR;

/** @brief	A pointer to string */
typedef char*					FS_LPSTR;

/** @brief	A constant pointer to string */
typedef char const*				FS_LPCSTR;

/** @brief	Result code for functions in Foxit PDF SDK. */
typedef int						FS_RESULT;

/** @brief	8-bit signed integer. */
typedef char					FS_INT8;

/** @brief	8-bit unsigned integer. */
typedef unsigned char			FS_UINT8;

/** @brief	16-bit signed integer. */
typedef short					FS_INT16;

/** @brief	16-bit unsigned integer. */
typedef unsigned short			FS_UINT16;

/** @brief	32-bit signed integer. */
typedef int						FS_INT32;

/** @brief	32-bit unsigned integer. */
typedef unsigned int			FS_UINT32;

/**@}*/
#endif /* _FSCRT_DEF_TYPE_BASETYPES_ */

#ifndef _FSCRT_DEF_HANDLE_DEFINE_
#define _FSCRT_DEF_HANDLE_DEFINE_

/* Macro to define variant handle type. */
#define FSCRT_DEFINEHANDLE(name)	typedef struct _##name {FS_LPVOID pData;} * name;

#endif /* _FSCRT_DEF_HANDLE_DEFINE_ */

#ifndef _FSCRT_DEF_MACRO_ERRCODE_
#define _FSCRT_DEF_MACRO_ERRCODE_
/**
 * @name	Macro Definitions for Error Codes
 * @note	In PDF SDK, error codes are returned to callers as ::FS_RESULT type.<br>
 *			0 indicates normal success status, positive value indicates current running status, and negative value indicates a failure. 
 */
/**@{*/

/** @brief	Success. */
#define FSCRT_ERRCODE_SUCCESS					0
/** @brief	Common error for any kind. */
#define FSCRT_ERRCODE_ERROR						-1
/** @brief	Invalid Foxit PDF SDK manager. */
#define FSCRT_ERRCODE_INVALIDMANAGER			-2
/** @brief	Invalid module or module uninitialized. */
#define FSCRT_ERRCODE_INVALIDMODULE				-3
/** @brief	The function can't be recovered. */
#define FSCRT_ERRCODE_UNRECOVERABLE				-4
/** @brief	Memory out of memory. */
#define FSCRT_ERRCODE_OUTOFMEMORY				-5
/** @brief	Incorrect password. */
#define FSCRT_ERRCODE_PASSWORD					-6
/** @brief	Data format error. */
#define FSCRT_ERRCODE_FORMAT					-7
/** @brief	File access error, cannot read or write file data. */
#define FSCRT_ERRCODE_FILE						-8
/** @brief	Parameter error. */
#define FSCRT_ERRCODE_PARAM						-9
/** @brief	License authorization error. */
#define FSCRT_ERRCODE_INVALIDLICENSE			-10
/** @brief	Callback functions in handler are error. */
#define FSCRT_ERRCODE_HANDLER					-11
/** @brief	Unknown security handler or cannot find availably one. */
#define FSCRT_ERRCODE_UNKNOWNSECURITYHANDLER	-12
/** @brief	Incorrect certificate or its data error. */
#define FSCRT_ERRCODE_INVALIDCERTIFICATE		-13
/** @brief	Data cannot be found. */
#define FSCRT_ERRCODE_NOTFOUND					-14
/** @brief	Invalid object type. */
#define FSCRT_ERRCODE_INVALIDTYPE				-15
/** @brief	Some features are not implemented, cannot be used, usually for user-side callback functions. */
#define FSCRT_ERRCODE_UNSUPPORTED				-16
/** @brief	Contents are not parsed. */
#define FSCRT_ERRCODE_NOTPARSED					-17
/** @brief	State is error or unknown. */
#define FSCRT_ERRCODE_UNKNOWNSTATE				-18
/** @brief	Buffer is overflow, need more space. */
#define FSCRT_ERRCODE_BUFFEROVERFLOW			-19
/** @brief	Data or values conflict. */
#define FSCRT_ERRCODE_CONFLICT					-20
/** @brief	Data not ready. */
#define FSCRT_ERRCODE_DATANOTREADY				-21
/** @brief	Memory is rebuilded. */
#define FSCRT_ERRCODE_MEMORYREBUILT				-22
/**
 * @brief	To be continued.
 *
 * @note	It's used under progressive calls, and tells caller to call function ::FSCRT_Progress_Continue again.
 */
#define FSCRT_ERRCODE_TOBECONTINUED				1
/** @brief	Current process has finished, need not do again. */
#define FSCRT_ERRCODE_FINISHED					2
/** @brief	To rollback the application process. */
#define FSCRT_ERRCODE_ROLLBACK					3

/** @brief	Helper macro to test for success on any result value. */
#define FSCRT_SUCCEEDED(result)					((FS_RESULT)(result) >= 0) 
/** @brief	Helper macro to test for failure on any result value. */
#define FSCRT_FAILED(result)					((FS_RESULT)(result) < 0)

/**@}*/
#endif /* _FSCRT_DEF_MACRO_ERRCODE_ */

#ifndef _FSCRT_DEF_MACRO_VT_
#define _FSCRT_DEF_MACRO_VT_
/**
 * @name	Macro Definitions for IDs of Variant Types
 * @note	Variant types are used by FSCRT_VAR::type.
 */
/**@{*/

/** @brief	Synonymous variant type ID for void. */
#define FSCRT_VT_EMPTY			0x00000000
/** @brief	Variant type ID for ::FS_INT8. */
#define FSCRT_VT_INT8			0x00000001
/** @brief	Variant type ID for ::FS_UINT8. */
#define FSCRT_VT_UINT8			0x00000002
/** @brief	Variant type ID for ::FS_INT16. */
#define FSCRT_VT_INT16			0x00000003
/** @brief	Variant type ID for ::FS_UINT16. */
#define FSCRT_VT_UINT16			0x00000004
/** @brief	Variant type ID for ::FS_INT32. */
#define FSCRT_VT_INT32			0x00000005
/** @brief	Variant type ID for ::FS_UINT32. */
#define FSCRT_VT_UINT32			0x00000006
/** @brief	Variant type ID for ::FS_BOOL. */
#define FSCRT_VT_BOOL			0x00000007
/** @brief	Variant type ID for ::FS_FLOAT. */
#define FSCRT_VT_FLOAT			0x00000008
/** @brief	Variant type ID for ::FS_LPVOID. */
#define FSCRT_VT_LPVOID			0x80000000
/** @brief	Variant type ID for pointer type of ::FS_INT8*. */
#define FSCRT_VT_LPINT8			(FSCRT_VT_LPVOID | FSCRT_VT_INT8)
/** @brief	Variant type ID for pointer type of ::FS_UINT8*. */
#define FSCRT_VT_LPUINT8		(FSCRT_VT_LPVOID | FSCRT_VT_UINT8)
/** @brief	Variant type ID for pointer type of ::FS_INT16*. */
#define FSCRT_VT_LPINT16		(FSCRT_VT_LPVOID | FSCRT_VT_INT16)
/** @brief	Variant type ID for pointer type of ::FS_UINT16*. */
#define FSCRT_VT_LPUINT16		(FSCRT_VT_LPVOID | FSCRT_VT_UINT16)
/** @brief	Variant type ID for pointer type of ::FS_INT32*. */
#define FSCRT_VT_LPINT32		(FSCRT_VT_LPVOID | FSCRT_VT_INT32)
/** @brief	Variant type ID for pointer type of ::FS_UINT32*. */
#define FSCRT_VT_LPUINT32		(FSCRT_VT_LPVOID | FSCRT_VT_UINT32)
/** @brief	Variant type ID for pointer type of ::FS_BOOL*. */
#define FSCRT_VT_LPBOOL			(FSCRT_VT_LPVOID | FSCRT_VT_BOOL)
/** @brief	Variant type ID for pointer type of ::FS_FLOAT*. */
#define FSCRT_VT_LPFLOAT		(FSCRT_VT_LPVOID | FSCRT_VT_FLOAT)
/** @brief	Synonymous variant type ID for ::FS_CHAR. */
#define FSCRT_VT_CHAR			FSCRT_VT_INT8
/** @brief	Synonymous variant type ID for ::FS_BYTE. */
#define FSCRT_VT_BYTE			FSCRT_VT_UINT8
/** @brief	Synonymous variant type ID for ::FS_WORD. */
#define FSCRT_VT_WORD			FSCRT_VT_UINT16
/** @brief	Synonymous variant type ID for ::FS_RESULT. */
#define FSCRT_VT_RESULT			FSCRT_VT_INT32
/** @brief	Synonymous variant type ID for ::FS_DWORD. */
#define FSCRT_VT_DWORD			FSCRT_VT_UINT32
/** @brief	Synonymous variant type ID for ::FS_ARGB. */
#define FSCRT_VT_ARGB			FSCRT_VT_UINT32
/** @brief	Synonymous variant type ID for ::FS_LPSTR. */
#define FSCRT_VT_LPSTR			FSCRT_VT_LPINT8
/** @brief	Synonymous variant type ID for ::FS_LPCSTR. */
#define FSCRT_VT_LPCSTR			FSCRT_VT_LPINT8
/** @brief	Synonymous variant type ID for ::FS_BYTE*. */
#define FSCRT_VT_LPBYTE			FSCRT_VT_LPUINT8
/** @brief	Synonymous variant type ID for ::FS_WORD*. */
#define FSCRT_VT_LPWORD			FSCRT_VT_LPUINT16
/** @brief	Synonymous variant type ID for ::FS_RESULT*. */
#define FSCRT_VT_LPRESULT		FSCRT_VT_LPINT32
/** @brief	Synonymous variant type ID for ::FS_DWORD*. */
#define FSCRT_VT_LPDWORD		FSCRT_VT_LPUINT32
/** @brief	Synonymous variant type ID for ::FS_ARGB*. */
#define FSCRT_VT_LPARGB			FSCRT_VT_LPUINT32
/** @brief	Synonymous variant type ID for ::FSCRT_BSTR. */
#define FSCRT_VT_BSTR			(FSCRT_VT_LPVOID|0x00000010)
/** @brief	Synonymous variant type ID for common objects. Please refer more macros definitions of <b>FSPDF_VT_OBJECT_XXX</b>*/
#define	FSCRT_VT_OBJECT			(FSCRT_VT_LPVOID|0x00001000)	
/**@}*/
#endif /* _FSCRT_DEF_MACRO_VT_ */

/*******************************************************************************/
/* Extend of Object Types                                                      */
/*                                                                             */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_VT_OBJECT_
#define _FSPDF_DEF_MACRO_VT_OBJECT_
/** 
 * @name	Macro Definitions for Extend of Variant Types
 */
/**@{*/
/** @brief	Object type ID for <b>FSPDF_LAYER</b>. */
#define	FSCRT_VT_OBJECT_LAYER		(FSCRT_VT_OBJECT|0x000000001)
/** @brief	Object type ID for <b>FSPDF_PAGEOBJECT</b>. */
#define	FSCRT_VT_OBJECT_PAGEOBJECT	(FSCRT_VT_OBJECT|0x000000002)
/**@}*/
#endif /* _FSPDF_DEF_MACRO_VT_OBJECT_ */

#ifndef _FSCRT_DEF_STRUCTURE_VAR_
#define _FSCRT_DEF_STRUCTURE_VAR_

/**
 * @brief	Structure for variant definitions
 * 
 * @note	::FSCRT_VAR structure is used to express common data as formal format, such as a set of the parameters or any type of result.<br>
 */
typedef struct _FSCRT_VAR
{
	/** @brief	Variant type. Please refer to macro definitions <b>FSCRT_VT_XXX</b> and this should be one of these macros. */
	FS_DWORD	type;
	/** @brief	Reserved field, should be 0. */
	FS_DWORD	reserved;
	/** @brief	Union expression to variant data. */
	union
	{
		/** @brief	A signed 8-bit integer value, or a ::FS_CHAR value. */
		FS_INT8		int8Var;
		/** @brief	An unsigned 8-bit integer value, or a ::FS_BYTE value. */
		FS_UINT8	uint8Var;
		/** @brief	A signed 16-bit integer value. */
		FS_INT16	int16Var;
		/** @brief	An unsigned 16-bit integer value, or a ::FS_WORD value. */
		FS_UINT16	uint16Var;
		/** @brief	A signed 32-bit integer value. */
		FS_INT32	int32Var;
		/** @brief	An unsigned 32-bit integer value, or a ::FS_DWORD, ::FS_ARGB value. */
		FS_UINT32	uint32Var;
		/** @brief	A 32-bit boolean value. */
		FS_BOOL		boolVar;
		/** @brief	A 32-bit floating point value. */
		FS_FLOAT	floatVar;
		/** @brief	A pointer to variant data. */
		FS_LPVOID	voidPtrVar;
		/** @brief	A pointer to signed 8-bit data. */
		FS_INT8*	int8PtrVar;
		/** @brief	A pointer to unsigned 8-bit data. */
		FS_UINT8*	uint8PtrVar;
		/** @brief	A pointer to signed 16-bit data. */
		FS_INT16*	int16PtrVar;
		/** @brief	A pointer to unsigned 16-bit data. */
		FS_UINT16*	uint16PtrVar;
		/** @brief	A pointer to signed 32-bit data. */
		FS_INT32*	int32PtrVar;
		/** @brief	A pointer to unsigned 32-bit data. */
		FS_UINT32*	uint32PtrVar;
		/** @brief	A pointer to boolean data. */
		FS_BOOL*	boolPtrVar;
		/** @brief	A pointer to float point data. */
		FS_FLOAT*	floatPtrVar;
	} var;
} FSCRT_VAR;

/**
 * @brief	Macro to set ::FS_INT8 value for a ::FSCRT_VAR structure.
 * 
 * @note	Here are examples:<br>
 * @code
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetInt8Value(val, 1);
 * @endcode
 */
#define FSCRT_Var_SetInt8Value(variant, value)			(variant).type = FSCRT_VT_INT8, (variant).var.int8Var = (value);
/**
 * @brief	Macro to set ::FS_UINT8 value for a ::FSCRT_VAR structure.
 * 
 * @note	Here are examples:<br>
 * @code
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetUInt8Value(val, 1);
 * @endcode
 */
#define FSCRT_Var_SetUInt8Value(variant, value)			(variant).type = FSCRT_VT_UINT8, (variant).var.uint8Var = (value);
/**
 * @brief	Macro to set ::FS_INT16 value for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetInt16Value(val, 1);
 * @endcode
 */
#define FSCRT_Var_SetInt16Value(variant, value)			(variant).type = FSCRT_VT_INT16, (variant).var.int16Var = (value);
/**
 * @brief	Macro to set ::FS_UINT16 value for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetUInt16Value(val, 1);
 * @endcode
 */
#define FSCRT_Var_SetUInt16Value(variant, value)		(variant).type = FSCRT_VT_UINT16, (variant).var.uint16Var = (value);
/**
 * @brief	Macro to set ::FS_INT32 value for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetInt32Value(val, 1);
 * @endcode
 */
#define FSCRT_Var_SetInt32Value(variant, value)			(variant).type = FSCRT_VT_INT32, (variant).var.int32Var = (value);
/**
 * @brief	Macro to set ::FS_UINT32 value for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetUInt32Value(val, 1);
 * @endcode
 */
#define FSCRT_Var_SetUInt32Value(variant, value)		(variant).type = FSCRT_VT_UINT32, (variant).var.uint32Var = (value);
/**
 * @brief	Macro to set ::FS_BOOL value for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetBooleanValue(val, TRUE);
 * @endcode
 */
#define FSCRT_Var_SetBooleanValue(variant, value)		(variant).type = FSCRT_VT_BOOL, (variant).var.boolVar = (value);
/**
 * @brief	Macro to set ::FS_FLOAT value for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetFloatValue(val, 1.0);
 * @endcode
 */
#define FSCRT_Var_SetFloatValue(variant, value)			(variant).type = FSCRT_VT_FLOAT, (variant).var.floatVar = (value);
/**
 * @brief	Macro to set ::FS_LPVOID value for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetVoidPtrValue(val, NULL);
 * @endcode
 */
#define FSCRT_Var_SetVoidPtrValue(variant, value)		(variant).type = FSCRT_VT_LPVOID, (variant).var.voidPtrVar = (value);
/**
 * @brief	Macro to set ::FS_INT8 pointer for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FS_INT8 key = 1;
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetInt8PtrValue(val, &key);
 * @endcode
 */
#define FSCRT_Var_SetInt8PtrValue(variant, value)		(variant).type = FSCRT_VT_LPINT8, (variant).var.int8PtrVar = (value);
/**
 * @brief	Macro to set ::FS_UINT8 pointer for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FS_UINT8 key = 1;
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetUInt8PtrValue(val, &key);
 * @endcode
 */
#define FSCRT_Var_SetUInt8PtrValue(variant, value)		(variant).type = FSCRT_VT_LPUINT8, (variant).var.uint8PtrVar = (value);
/**
 * @brief	Macro to set ::FS_INT16 pointer for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FS_INT16 key = 1;
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetInt16PtrValue(val, &key);
 * @endcode
 */
#define FSCRT_Var_SetInt16PtrValue(variant, value)		(variant).type = FSCRT_VT_LPINT16, (variant).var.int16PtrVar = (value);
/**
 * @brief	Macro to set ::FS_UINT16 pointer for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FS_UINT16 key = 1;
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetUInt16PtrValue(val, &key);
 * @endcode
 */
#define FSCRT_Var_SetUInt16PtrValue(variant, value)		(variant).type = FSCRT_VT_LPUINT16, (variant).var.uint16PtrVar = (value);
/**
 * @brief	Macro to set ::FS_INT32 pointer for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FS_INT32 key = 1;
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetInt32PtrValue(val, &key);
 * @endcode
 */
#define FSCRT_Var_SetInt32PtrValue(variant, value)		(variant).type = FSCRT_VT_LPINT32, (variant).var.int32PtrVar = (value);
/**
 * @brief	Macro to set ::FS_UINT32 pointer for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FS_UINT32 key = 1;
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetUInt32PtrValue(val, &key);
 * @endcode
 */
#define FSCRT_Var_SetUInt32PtrValue(variant, value)		(variant).type = FSCRT_VT_LPUINT32, (variant).var.uint32PtrVar = (value);
/**
 * @brief	Macro to set ::FS_BOOL pointer for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FS_BOOL key = TRUE;
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetBooleanPtrValue(val, &key);
 * @endcode
 */
#define FSCRT_Var_SetBooleanPtrValue(variant, value)	(variant).type = FSCRT_VT_LPBOOL, (variant).var.boolPtrVar = (value);
/**
 * @brief	Macro to set ::FS_FLOAT pointer for a ::FSCRT_VAR structure.
 *
 * @note	Here are examples:<br>
 * @code
 *	FS_FLOAT key = 1.0;
 *	FSCRT_VAR val;
 *	FSCRT_Var_SetFloatPtrValue(val, &key);
 * @endcode
 */
#define FSCRT_Var_SetFloatPtrValue(variant, value)		(variant).type = FSCRT_VT_LPFLOAT, (variant).var.floatPtrVar = (value);

#endif /* _FSCRT_DEF_STRUCTURE_VAR_ */

/*******************************************************************************/
/* String                                                                      */
/*                                                                             */
/* Byte string - UTF8, string encode and decode                                */
/*******************************************************************************/
#ifndef _FSCRT_DEF_STRUCTURE_BSTR_
#define _FSCRT_DEF_STRUCTURE_BSTR_

/**
 * @brief	Structure for byte string.
 *
 * @note	In PDF SDK, a byte string commonly means a UTF-8 format string, except for explicit explanation.<br>
 *			Foxit PDF SDK will call function ::FSCRT_Memory_Alloc, ::FSCRT_Memory_Realloc or ::FSCRT_Memory_Free to maintain string buffer internally.<br>
 *			Applications can manage private memory by themselves and need to make sure there is enough memory in this case.
 */
typedef struct _FSCRT_BSTR
{
	/**
	 * @brief	String buffer.
	 *
	 * @note	It's not allowed to use stack space for string buffer. It's recommended to use 
	 *			heap space to allocate memory for string buffer.
	 * 			PDF SDK provides functions <b>FSCRT_BStr_XXX</b> to help applications maintain string buffer.
	 */
	FS_LPSTR	str;
	/**
	 * @brief	Length of a string, in bytes.
	 *
	 * @note	In PDF SDK, if a function returns a string by a ::FSCRT_BSTR structure, string buffer will be extended if the given length is not enough.
	 */
	FS_DWORD	len;
} FSCRT_BSTR;

/**
 * @brief	Macro to construct a byte string with constant string value.The encoding of string should be UTF-8 compatible.
 *
 * @note	Here are examples:<br>
 * @code
 *	FSCRT_DOCUMENT pdfDoc;
 *	... // load PDF document and other codes
 *	FSCRT_BSTR key = FSCRT_BSTRD("Author");
 *	FSCRT_BSTR value = FSCRT_BSTRD("Foxit PDF SDK");
 *	FSPDF_Metadata_SetString(pdfDoc, &key, &value);
 * @endcode
 */
#define FSCRT_BSTRD(str)						{str, sizeof(str) - 1}

/**
 * @brief	Macro to construct a byte string with constant string value.The encoding of string should be UTF-8 compatible.
 *
 * @note	Here are examples:<br>
 * @code
 *	FSCRT_DOCUMENT pdfDoc;
 *	... // load PDF document and other codes
 *	FSCRT_BSTRC(key, "Author");
 *	FSCRT_BSTRC(value, "Foxit PDF SDK");
 *	FSPDF_Metadata_SetString(pdfDoc, &key, &value);
 * @endcode
 */
#define FSCRT_BSTRC(v, str)						FSCRT_BSTR v = FSCRT_BSTRD(str)

/**
 * @brief	Macro to initialize constant string value.The encoding of string should be UTF-8 compatible.
 *
 * @note	This macro sets constant string value to a ::FSCRT_BSTR directly.<br>
 *			Here are examples:<br>
 * @code
 *	FSCRT_BSTR key;
 *	FSCRT_BStr_InitConstString(key, "Author");
 * @endcode
 */
#define FSCRT_BStr_InitConstString(v, s)		(v).str = s, (v).len = sizeof(s) - 1;

#endif /* _FSCRT_DEF_STRUCTURE_BSTR_ */

/**
 * @brief	Helper function to initialize a byte string.
 *
 * @param[in]	bstr	Pointer to a byte string, it shall be a valid pointer to ::FSCRT_BSTR.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bstr</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to initialize a byte string variant.<br>
 *			It sets FSCRT_BSTR::str to a <b>NULL</b> pointer, and sets FSCRT_BSTR::len to 0.<br>
 *			Applications can initialize ::FSCRT_BSTR in other ways instead of calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_BStr_Init(FSCRT_BSTR* bstr);

/**
 * @brief	Helper function to clear a byte string.
 *
 * @param[in]	bstr	Pointer to a byte string, it shall be a valid pointer to ::FSCRT_BSTR.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bstr</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to clear string buffer after calling the function ::FSCRT_BStr_SetLength or ::FSCRT_BStr_Set.<br>
 *			It frees FSCRT_BSTR::str and sets it to <b>NULL</b>, and then sets FSCRT_BSTR::len to 0.<br>
 *			Applications can free ::FSCRT_BSTR by themselves instead of calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_BStr_Clear(FSCRT_BSTR* bstr);

/**
 * @brief	Helper function to set length of a byte string.
 *
 * @param[in]	bstr		Pointer to a byte string, it shall be a valid pointer to ::FSCRT_BSTR.
 * @param[in]	length		New length of byte string, in bytes.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bstr</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to reset the length of byte string.<br>
 *			It allocates string buffer if FSCRT_BSTR::str is <b>NULL</b> or reallocates if FSCRT_BSTR::str is not <b>NULL</b> and <br>
 *          FSCRT_BSTR::len is less than the parameter <i>length</i>, and then sets FSCRT_BSTR::len to the parameter <i>length</i>.<br>
 *			Setting 0 to length has the same action as function ::FSCRT_BStr_Clear.<br>
 *			Applications can reset a byte string instead of calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_BStr_SetLength(FSCRT_BSTR* bstr, FS_DWORD length);

/**
 * @brief	Helper function to set string data.
 *
 * @param[in]	bstr		Pointer to a byte string, it shall be a valid pointer to ::FSCRT_BSTR.
 * @param[in]	str			Pointer to a constant string buffer.
 * @param[in]	length		Length of the parameter <i>str</i>, in bytes. 
 *							If this parameter is -1, <i>str</i> is treated as a null-terminated string.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>bstr</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to set new string data.<br>
 *			It calls ::FSCRT_BStr_Clear if the parameter <i>str</i> is <b>NULL</b> or <i>length</i> is 0, or calls ::FSCRT_BStr_SetLength to prepare buffer and data.<br>
 *			Please note the difference between ::FSCRT_BStr_InitConstString and ::FSCRT_BStr_SetConstString: the first one has no private memory block, but the second one has private memory block.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_BStr_Set(FSCRT_BSTR* bstr, FS_LPCSTR str, FS_DWORD length);
/**
 * @brief	Macro to set constant string value.
 *
 * @note	This macro sets constant string value to a ::FSCRT_BSTR object direct.<br>
 *			Here are examples:<br>
 * @code
 *	FSCRT_BSTR str2;
 *	FSCRT_BStr_Init(&str2);
 *	FSCRT_BStr_SetConstString(&str2, "Third String Data");
 *	FSCRT_BStr_Clear(&str2);
 * @endcode
 */
#define	FSCRT_BStr_SetConstString(bstr, str)	FSCRT_BStr_Set(bstr, str, sizeof(str) - 1)
/**
 * @brief	Macro to copy string value.
 *
 * @note	This macro defines a copy operation between ::FSCRT_BSTR and the others.<br>
 *			Here are examples:<br>
 * @code
 *	FSCRT_BSTR str1;
 *	FSCRT_BStr_InitConstString(str1, "First String Data");
 *	FSCRT_BStr_InitConstString(str1, "Second String Data");
 *
 *	FSCRT_BSTR str2;
 *	FSCRT_BStr_Init(&str2);
 *	FSCRT_BStr_SetConstString(&str2, "Third String Data");
 *	FSCRT_BStr_Copy(&str2, &str1);
 *	FSCRT_BStr_Clear(&str2);
 * @endcode
 */
#define	FSCRT_BStr_Copy(dstStr, srcStr)			FSCRT_BStr_Set(dstStr, (srcStr)->str, (srcStr)->len)


#ifndef _FSCRT_DEF_STRUCTURE_ARRAY_
#define _FSCRT_DEF_STRUCTURE_ARRAY_

/**
 * @brief	Structure for array.
 */
typedef struct _FSCRT_ARRAY
{
	/** @brief	The data type. Please refer to macros definition <b>FSCRT_VT_XXX</b>.*/
	FS_INT32 dataType;
	/** @brief	The element count of the array.*/
	FS_DWORD count;
	/**
	 * @brief	The memory address of the first element, followed by the other elements, which are continuous in the memory.
	 *
	 * @note	The data buffer would be always allocated by function ::FSCRT_Memory_Alloc, and then caller should call function ::FSCRT_Array_Clear to free the buffer. 
	 */
	FS_LPVOID data;

}FSCRT_ARRAY;

#endif /* _FSCRT_DEF_STRUCTURE_ARRAY_ */

/**
 * @brief	Helper function to initialize array.
 *
 * @param[in]	array		Pointer to a array, it shall be a valid pointer to ::FSCRT_ARRAY.
 * @param[in]	dataType	The data type. Please refer to macros definition <b>FSCRT_VT_XXXX</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>array</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSCRT_Array_Init(FSCRT_ARRAY* array, FS_INT32 dataType);

/**
 * @brief	Helper function to release the array.
 *
 * @param[in]	array			Pointer to a array, it shall be a valid pointer to ::FSCRT_ARRAY.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>array</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This function would only release the array data buffer, and it won't release the data member of array. 
 *			For example, suppose that the data type is ::FSCRT_VT_BSTR, before calling this function, caller should call function ::FSCRT_BStr_Clear 
 *			to free the memory for each member of the array when they are not used any more.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSCRT_Array_Clear(FSCRT_ARRAY* array);

/*******************************************************************************/
/* File stream                                                                 */
/*                                                                             */
/* File access, read or write, stream I/O                                      */
/*******************************************************************************/
#ifndef _FSCRT_DEF_HANDLE_FILE_
#define _FSCRT_DEF_HANDLE_FILE_

/** @brief	Handle type of file objects. */
FSCRT_DEFINEHANDLE(FSCRT_FILE);

#endif /* _FSCRT_DEF_HANDLE_FILE_ */

#ifndef _FSCRT_DEF_STRUCTURE_FILESIZE_
#define _FSCRT_DEF_STRUCTURE_FILESIZE_

/**
 * @brief	Structure for large file size.
 *
 * @note	This structure supports 64-bit file size.<br>
 *			The current version of Foxit PDF SDK doesn't support large file access. In order to keep forward compatibility with future versions, some functions use this structure directly.<br>
 *			Not all platforms can support 64-bit integer or 64-bit file access.
 */
typedef struct _FSCRT_FILESIZE
{
	/** @brief	Low-order 32-bit unsigned size. */
	FS_DWORD 	loSize;
	/** @brief	High-order 32-bit unsigned size. */
	FS_DWORD 	hiSize;
} FSCRT_FILESIZE;

#endif /* _FSCRT_DEF_STRUCTURE_FILESIZE_ */

#ifndef _FSCRT_DEF_HANDLER_FILE_
#define _FSCRT_DEF_HANDLER_FILE_

/**
 * @brief	Structure for file reading or writing (I/O).
 *
 * @note	This is a handler and should be implemented by callers.<br>
 *			File stream contains basic file accessing methods for not only file reading mode but also file writing mode.<br>
 *			Users can determine whether to implement reading actions or writing actions based on application intentions.<br>
 *			Here, term ::FSCRT_FILEHANDLER is just a common symbol which represents any stream data I/O and is not limited to file access.
 *			For example, access data through internet by HTTP protocol.
 */
typedef struct _FSCRT_FILEHANDLER
{
	/**
	 * @brief	User-defined data.
	 * @note	Callers can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/**
	 * @brief	Callback function to release the current file stream object.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 *
	 * @return	None.
	 *
	 * @note	Function ::FSCRT_File_Release calls this function to release stream object.<br>
	 *			It's recommended that this function supports multiple-thread environments, it can be decided based on application intentions.
	 */
	void		(*Release)(FS_LPVOID clientData);

	/**
	 * @brief	Callback function to retrieve the current file stream size.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 *
	 * @return	32-bit integer size of file stream.
	 *
	 * @note	It's recommended that this function supports multiple-thread environments, it can be decided based on application intentions.
	 */
	FS_DWORD	(*GetSize)(FS_LPVOID clientData);

	/**
	 * @brief	Callback function to read data from the current file stream.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	offset		Offset position starts from the beginning of file stream. This parameter indicates reading position.
	 * @param[in]	buffer		Memory buffer to store data which are read from file stream. This parameter should not be <b>NULL</b>.
	 * @param[in]	size		Size of data which should be read from file stream, in bytes. The buffer indicated by the parameter <i>buffer</i> should be enough to store specified data.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_PARAM if the parameter <i>buffer</i> is <b>NULL</b>.<br>
	 *			::FSCRT_ERRCODE_FILE if the parameter <i>offset</i> exceeds current file size or cannot read the amount of data specified by parameter <i>size</i> or any file accessing error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	This function provides random file stream reading support and is called by Foxit PDF SDK internally.<br>
	 *			Implementer should avoid any exception when this function is called and ensure proper value returned.<br>
	 *			It's recommended that this function supports multiple-thread environments, this can be decided based on application intention.
	 */
	FS_RESULT	(*ReadBlock)(FS_LPVOID clientData, FS_DWORD offset, FS_LPVOID buffer, FS_DWORD size);

	/**
	 * @brief	Callback function to write data into the current file stream.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	offset		Offset position starts from the beginning of file stream. This parameter indicates writing position.
	 * @param[in]	buffer		Memory buffer contains data which is written into file stream. This parameter should not be <b>NULL</b>.
	 * @param[in]	size		Size of data which should be written into file stream, in bytes.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_PARAM if parameter <i>buffer</i> is a <b>NULL</b> pointer.<br>
	 *			::FSCRT_ERRCODE_FILE if any file accessing error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	This function provides random file stream writing support and is called by Foxit PDF SDK internally.<br>
	 *			Implementer should avoid any exception when this function is called and ensure proper value returned.<br>
	 *			It's recommended that this function supports multiple-thread environments, this can be decided based on application intention.
	 */
	FS_RESULT	(*WriteBlock)(FS_LPVOID clientData, FS_DWORD offset, FS_LPCVOID buffer, FS_DWORD size);

	/**
	 * @brief	Callback function to flush all internal accessing buffers.
	 *
	 * @details	For reading mode, this function will clear all cached buffers.<br>
	 *			For writing mode, this function writes all cached data into file stream.<br>
	 *			Sometimes, caller calls this function to make sure data is written into file stream.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_FILE if any file accessing error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	Implementer should avoid any exception when this function is called and ensure proper value is returned.<br>
	 *			It's recommended that this function supports multiple-thread environments, this can be decided based on application intention.
	 */
	FS_RESULT	(*Flush)(FS_LPVOID clientData);

	/**
	 * @brief	Callback function to change file size.
	 *
	 * @details	This function is called under writing mode usually. Implementer can determine whether to realize it based on application requests.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	size		New size of file stream, in bytes.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_FILE if any file accessing error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	Implementer should avoid any exception when this function is called and ensure proper value is returned.<br>
	 *			It's recommended that this function supports multiple-thread environments, this can be decided based on application intention.
	 */
	FS_RESULT	(*Truncate)(FS_LPVOID clientData, FS_DWORD size);

} FSCRT_FILEHANDLER;

#endif /* _FSCRT_DEF_HANDLER_FILE_ */

/**
 * @brief	Create a file object from file stream.
 *
 * @details	In order to provide uniform file accessing mechanism, Foxit PDF SDK doesn't use ::FSCRT_FILEHANDLER directly to access stream data.<br>
 *			<b>FSCRT_FILE</b> is used to represent a stream source and gives callers a normal way. The <b>FSCRT_FILE</b> object can be created from different manners.
 * 
 * @param[in]	fileStream		Pointer to a valid ::FSCRT_FILEHANDLER structure to create a file object.
 * @param[out]	file			Pointer to a <b>FSCRT_FILE</b> handle that receives the handle of file object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>fileStream</i> or parameter <i>file</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_HANDLER if any one callback functions in parameter <i>fileStream</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Foxit PDF SDK doesn't distinguish reading or writing mode explicitly, applications or implementers of ::FSCRT_FILEHANDLER structure can determine this by application intentions.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_File_Create(FSCRT_FILEHANDLER* fileStream, FSCRT_FILE* file);

#ifndef _FSCRT_DEF_HANDLE_LARGE_FILE_
#define _FSCRT_DEF_HANDLE_LARGE_FILE_

/**
 * @brief	Structure for file with large size for reading or writing (I/O).
 *
 * @note	This is a handler and should be implemented by callers.<br>
 *			File stream contains basic file accessing methods for not only file reading mode but also file writing mode.<br>
 *			Users can determine whether to implement reading actions or writing actions based on application intentions.<br>
 *			Here, term ::FSCRT_FILEHANDLER_L is just a common symbol which represents any stream data I/O and is not limited to file access.
 *			For example, access data through internet by HTTP protocol.
 */
 typedef struct _FSCRT_FILEHANDLER_L
 {
	 /**
	 * @brief	User-defined data.
	 * @note	Callers can use this field to track controls.
	 */
	 FS_LPVOID	clientData;

	 /**
	 * @brief	Callback function to release the current file stream object.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 *
	 * @return	None.
	 *
	 * @note	Function ::FSCRT_File_Release calls this function to release stream object.<br>
	 *			It's recommended that this function supports multiple-thread environments, it can be decided based on application intentions.
	 */
	 void	(*Release)(FS_LPVOID clientData);

	 /**
	 * @brief	Callback function to retrieve the current file stream size.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[out]	size		Pointer to structure ::FSCRT_FILESIZE that retrieves the stream size of current file.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_FILE if any file accessing error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	It's recommended that this function supports multiple-thread environments, it can be decided based on application intentions.
	 */
	 FS_RESULT	(*GetSize)(FS_LPVOID clientData, FSCRT_FILESIZE* size);

	 /**
	 * @brief	Callback function to read data from the current file stream.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	offset		Offset position starts from the beginning of file stream. This parameter indicates reading position.
	 * @param[in]	buffer		Memory buffer to store data which are read from file stream. This parameter should not be <b>NULL</b>.
	 * @param[in]	size		Size of data which should be read from large file stream, in bytes. The buffer indicated by the parameter <i>buffer</i> should be enough to store specified data.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_PARAM if the parameter <i>buffer</i> is <b>NULL</b>.<br>
	 *			::FSCRT_ERRCODE_FILE if the parameter <i>offset</i> exceeds current file size or cannot read the amount of data specified by parameter <i>size</i> or any file accessing error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	This function provides random file stream reading support and is called by Foxit PDF SDK internally.<br>
	 *			Implementer should avoid any exception when this function is called and ensure proper value returned.<br>
	 *			It's recommended that this function supports multiple-thread environments, this can be decided based on application intention.
	 */
	 FS_RESULT	(*ReadBlock)(FS_LPVOID clientData, const FSCRT_FILESIZE* offset, FS_LPVOID buffer, const FSCRT_FILESIZE* size);

	 /**
	 * @brief	Callback function to write data into the current large file stream.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	offset		Offset position starts from the beginning of large file stream. This parameter indicates writing position.
	 * @param[in]	buffer		Memory buffer contains data which is written into file stream. This parameter should not be <b>NULL</b>.
	 * @param[in]	size		Size of data which should be written into large file stream, in bytes.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_PARAM if parameter <i>buffer</i> is a <b>NULL</b> pointer.<br>
	 *			::FSCRT_ERRCODE_FILE if any file accessing error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	This function provides random file stream writing support and is called by Foxit PDF SDK internally.<br>
	 *			Implementer should avoid any exception when this function is called and ensure proper value returned.<br>
	 *			It's recommended that this function supports multiple-thread environments, this can be decided based on application intention.
	 */
	 FS_RESULT	(*WriteBlock)(FS_LPVOID clientData, const FSCRT_FILESIZE* offset, FS_LPCVOID buffer, const FSCRT_FILESIZE* size);
	
	 /**
	 * @brief	Callback function to flush all internal accessing buffers.
	 *
	 * @details	For reading mode, this function will clear all cached buffers.<br>
	 *			For writing mode, this function writes all cached data into file stream.<br>
	 *			Sometimes, caller calls this function to make sure data is written into file stream.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_FILE if any file accessing error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	Implementer should avoid any exception when this function is called and ensure proper value is returned.<br>
	 *			It's recommended that this function supports multiple-thread environments, this can be decided based on application intention.
	 */
	 FS_RESULT	(*Flush)(FS_LPVOID clientData);

	 /**
	 * @brief	Callback function to change file size.
	 *
	 * @details	This function is called with writing mode usually. Implementer can determine when to call it based on application requests.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	fileSize	New size of large file stream, in bytes.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_FILE if any file accessing error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	Implementer should avoid any exception when this function is called and ensure proper value is returned.<br>
	 *			It's recommended that this function supports multiple-thread environments, this can be decided based on application intention.
	 */
	 FS_RESULT	(*Truncate)(FS_LPVOID clientData, const FSCRT_FILESIZE* fileSize);

 } FSCRT_FILEHANDLER_L;

#endif /* _FSCRT_DEF_HANDLE_LARGE_FILE_ */

 /**
 * @brief	Create a <b>FSCRT_FILE</b> object from a large file, which the file size could be over 2GB.
 *
 * @details	In order to provide uniform file accessing mechanism, Foxit PDF SDK doesn't use ::FSCRT_FILEHANDLER_L directly to access stream data.<br>
 *			<b>FSCRT_FILE</b> is used to represent a stream source and gives callers a normal way. The <b>FSCRT_FILE</b> object can be created from many different manners.
 * 
 * @param[in]	fileStream		Pointer to a valid ::FSCRT_FILEHANDLER_L structure to create a large file object.
 * @param[out]	file			Pointer to a <b>FSCRT_FILE</b> handle that receives the handle of file object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>fileStream</i> or parameter <i>file</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_HANDLER if any callback functions in parameter <i>fileStream</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Foxit PDF SDK doesn't distinguish reading or writing mode explicitly, applications or implementers of ::FSCRT_FILEHANDLER_L structure can determine this by application intentions.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_File_Create_L(FSCRT_FILEHANDLER_L* fileStream, FSCRT_FILE* file);


/**
 * @brief	Create a cached file object from file stream.
 *
 * @details	In order to provide uniform file accessing mechanism, Foxit PDF SDK doesn't use ::FSCRT_FILEHANDLER directly to access stream data.<br>
 *			<b>FSCRT_FILE</b> is used to represent a stream source and gives callers a normal way.<b>FSCRT_FILE</b>object can be created from different manners.<br>
 *			In some environments, file accessing is slow. Using file cache can increase efficiency significantly. This function is designed for this purpose.<br>
 *			File cache consists of a set of chunks. A chunk is a memory block.<br>
 * 			A cached file is only for reading mode. Do not use it to write data into file object.
 * 
 * @param[in]	fileStream	Pointer to a valid ::FSCRT_FILEHANDLER structure to create a <b>FSCRT_FILE</b>object.
 * @param[in]	chunkSize	Chunk size, in bytes, parameter <i>chunkSize</i> should not be less than 4096 and not be greater than 65536.
 * @param[in]	chunkCount	The number of chunks used in file cache, parameter <i>chunkCount</i> should not less than 1 and not be greater than 256.
 * @param[in]	buffer		Pointer to cache buffer. If it's <b>NULL</b>, a new cache buffer will be allocated internally. If it's not <b>NULL</b>, buffer size should be not less than the amount value parameter <i>chunkSize</i> multiplies parameter <i>chunkCount</i>.
 * @param[out]	file		Pointer to a <b>FSCRT_FILE</b> handle that receives the handle of file object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>fileStream</i> or <i>file</i> is a <b>NULL</b> pointer or the values of parameter <i>chunkSize</i> and <i>chunkCount</i> exceed their ranges.<br>
 * 			::FSCRT_ERRCODE_HANDLER if any callback function in parameter <i>fileStream</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Foxit PDF SDK doesn't distinguish reading or writing mode explicitly, applications or implementer of ::FSCRT_FILEHANDLER can determine this by application intentions.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_File_CreateCacheFile(FSCRT_FILEHANDLER* fileStream, FS_DWORD chunkSize, FS_DWORD chunkCount, FS_LPVOID buffer, FSCRT_FILE* file);

/**
 * @brief	Create a memory-based file object.
 *
 * @param[in]	buffer	Pointer to a memory block to access data. It should be valid.
 * @param[in]	length	Size of buffer, in bytes.
 * @param[out]	file	Pointer to a <b>FSCRT_FILE</b> handle that receives the handle of file object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>buffer</i> or <i>file</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	The memory-based file is either for reading or writing purpose, do not write and read on the same memory-based file!
 *			The size of memory buffer is fixed:<br>
 *			<ul>
 *			<li>For reading mode, parameter <i>length</i> indicates the size of data stored in parameter <i>buffer</i>.</li>
 *			<li>For writing mode, parameter <i>length</i> is the maximum size of data can be written.</li>
 *			</ul>
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_File_CreateFromMemory(FS_LPVOID buffer, FS_DWORD length, FSCRT_FILE* file);

#ifndef _FSCRT_DEF_MACRO_FILEMODE_
#define _FSCRT_DEF_MACRO_FILEMODE_
/**
 * @name	Macro Definitions for File Mode
 */
/**@{*/

/** 
 * @brief	Write mode.
 *
 * @details	If the file doesn't exist, it will be created automatically.
 *			However, if the file exists, the content will be appended to the end of the file.
 */
#define FSCRT_FILEMODE_WRITE		0
/** @brief	Read-only mode. */
#define FSCRT_FILEMODE_READONLY		1
/** @brief	Clear existing contents, size of file is to be 0, for writing mode only. */
#define FSCRT_FILEMODE_TRUNCATE		2

/**@}*/
#endif /* _FSCRT_DEF_MACRO_FILEMODE_ */

/**
 * @brief	Create a file object from a specific file path.
 *
 * @param[in]	fileName		Pointer to a UTF-8 encoded string, it should be a valid pointer to ::FSCRT_BSTR that specifies a path of file.
 * @param[in]	fileModes		Indicate a file mode. It should be one of the following value:<br>
 *								<ul>
 *								<li>::FSCRT_FILEMODE_WRITE</li>
 *								<li>::FSCRT_FILEMODE_READONLY</li>
 *								<li>::FSCRT_FILEMODE_TRUNCATE</li>
 *								</ul>
 * @param[out]	file			Pointer to a <b>FSCRT_FILE</b> handle that receives a handle of file object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>fileName</i> or <i>file</i> or FSCRT_BSTR::str is <b>NULL</b> or FSCRT_BSTR::len is invalid.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 * 			::FSCRT_ERRCODE_FORMAT if it is not a UTF-8 byte string in the parameter <i>fileName</i>.<br>
 * 			::FSCRT_ERRCODE_ERROR if the function cannot create file object because of any other reasons. For exampke, a file is not existing.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Foxit PDF SDK doesn't distinguish reading from writing mode explicitly, it is determined by the parameter <i>fileModes</i>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_File_CreateFromFileName(const FSCRT_BSTR* fileName, FS_DWORD fileModes, FSCRT_FILE* file);

/**
 * @brief	Get the number of bytes of a file object.
 *
 * @param[in]	file		Handle to a <b>FSCRT_FILE</b> object which is a handle of file object.
 * @param[out]	fileSize	Pointer to a ::FSCRT_FILESIZE structure that receives a file size. In order to keep forward compatibilities, use 64-bits here.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>file</i> or <i>fileSize</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_File_GetSize(FSCRT_FILE file, FSCRT_FILESIZE* fileSize);

/**
 * @brief	Set reading range of file object, the following reading from file would be restricted in this range.
 *
 * @details	In some cases, such as opening a PDF wrapper file, this function is used for applications to change reading range of file.<br>
 *			This function works in reading mode rather than writing purpose.
 *
 * @param[in]	file		Handle to a <b>FSCRT_FILE</b> object which is a handle of file object.
 * @param[in]	offset		Pointer to a ::FSCRT_FILESIZE structure to set the starting position of file object in bytes. In order to keep forward compatibilities, use 64-bits here.
 * @param[in]	length		Pointer to a ::FSCRT_FILESIZE structure to set the new reading length of file object in bytes. In order to keep forward compatibilities, use 64-bits here.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>file</i> or <i>offset</i> or <i>length</i> is <b>NULL</b>, 
 *			or parameter <i>offset</i> is out of the file size range.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_File_SetRange(FSCRT_FILE file, const FSCRT_FILESIZE* offset, const FSCRT_FILESIZE* length);

/**
 * @brief	Clear the reading range of file object, the current reading position won't be affected.
 *
 * @details	If function ::FSCRT_File_SetRange is called to read the file content from the specific range, then you might  
 *			call ::FSCRT_File_ClearRange to clear the range, or the following reading from file would be restricted in the range.
 *
 * @param[in]	file		Handle to a <b>FSCRT_FILE</b> object which is a handle of file object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>file</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_File_ClearRange(FSCRT_FILE file);

/**
 * @brief	Read data from file object.
 *
 * @param[in]		file		Handle to a <b>FSCRT_FILE</b> object which is a handle of file object.
 * @param[in]		buffer		Pointer to a buffer which receives the specific data of file object.
 * @param[in]		size		Pointer to a ::FSCRT_FILESIZE structure to set the size of file object in bytes to be read. In order to keep forward compatibilities, use 64-bits here.
 * @param[out]		actualSize	Pointer to a ::FSCRT_FILESIZE structure to recieve the actual size read from file object in bytes. In order to keep forward compatibilities, use 64-bits here.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>file</i> or <i>buffer</i> or <i>size</i> or <i>actualSize</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_File_Read(FSCRT_FILE file, FS_LPVOID buffer, const FSCRT_FILESIZE* size, FSCRT_FILESIZE* actualSize);

/**
 * @brief	Write data to file object.
 *
 * @param[in]		file		Handle to a <b>FSCRT_FILE</b> object which is a handle of file object.
 * @param[in]		buffer	Pointer to a buffer to save data which will be written to file object.
 * @param[in]		size		Pointer to a ::FSCRT_FILESIZE structure to set the size of file object in bytes to be written. In order to keep forward compatibilities, use 64-bits here.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>file</i> or <i>buffer</i> or <i>size</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_File_Write(FSCRT_FILE file, FS_LPVOID buffer, const FSCRT_FILESIZE* size);

/**
 * @brief	Release a file object.
 *
 * @param[in]	file		Handle to a <b>FSCRT_FILE</b> object which is a handle of file object to release.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>file</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Don't use the parameter <i>file</i> object in case it's released.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_File_Release(FSCRT_FILE file);

/*******************************************************************************/
/* Library management, license controls, log file and memory management        */
/*******************************************************************************/
#ifndef _FSCRT_DEF_MACRO_LICENSETYPE_
#define _FSCRT_DEF_MACRO_LICENSETYPE_
/**
 * @name	Macro Definitions for License Types
 * @note	Foxit PDF SDK manages a license control mechanism to determine how to run for application purposes.<br>
 * 			  Applications should purchase Foxit PDF SDK license and apply unlock key and code before accessing functions.
 */
/**@{*/

/** 
 * @brief	Invalid license.
 * 
 * @details	This means applications don't call the function ::FSCRT_License_UnlockLibrary or license key/code is incorrect. 
 */
#define FSCRT_LICENSETYPE_INVALID			FSCRT_ERRCODE_INVALIDLICENSE
/** 
 * @brief	Authorized license.
 *
 * @details	This means applications can use Foxit PDF SDK normally.
 */
#define FSCRT_LICENSETYPE_AUTHORIZED		0
/** 
 * @brief	Evaluation license.
 * 
 * @details	This means applications are using an evaluation version of Foxit PDF SDK. 
 */
#define FSCRT_LICENSETYPE_EVALUATION		1
/** 
 * @brief	Expired license.
 * 
 * @details	If applications use Foxit PDF SDK in the expired condition, please contact Foxit Software Inc. to get a legal license. 
 */
#define FSCRT_LICENSETYPE_EXPIRED			2

/**@}*/
#endif /* _FSCRT_DEF_MACRO_LICENSETYPE_ */

#ifndef _FSCRT_DEF_HANDLER_MEMMGR_
#define _FSCRT_DEF_HANDLER_MEMMGR_

/**
 * @brief	Structure for memory management.
 * @note	This is a handler and should be implemented by applications.<br>
 *			Memory manager provides platform-based memory allocation and free controls.<br>
 *			Function ::FSCRT_Library_CreateMgr uses a memory manager to initialize Foxit PDF SDK manager.
 */
typedef struct _FSCRT_MEMMGRHANDLER
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Applications can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/**
	 * @brief	A callback function to allocate a memory block.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	size		The number of bytes for memory block. It can be 0.
	 *
	 * @return	The pointer to allocated memory block. <b>NULL</b> if fails.
	 *
	 * @note	Applications should avoid any exceptions when this function is called,
	 *			and should also ensure it supports multiple-thread environments.<br>
	 *			If the parameter <i>size</i> is 0, a minimum size of memory block should be returned.<br>
	 *			Function ::FSCRT_Memory_Alloc calls this function.
	 */
	FS_LPVOID	(*Alloc)(FS_LPVOID clientData, FS_DWORD size);

	/**
	 * @brief	A callback function to reallocate a memory block.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	ptr			Pointer to an existing memory block, or <b>NULL</b>.
	 * @param[in]	newSize		New size of a memory block, in bytes. It can be 0.
	 *
	 * @return	The pointer of reallocated memory block, or <b>NULL</b> if fails.
	 *
	 * @note	Applications should avoid any exceptions when this function is called,
	 *			and should also ensure it supports multiple-thread environments.<br>
	 *			If the parameter <i>ptr</i> is <b>NULL</b>, this function has the same action as function FSCRT_MEMMGRHANDLER::Alloc.<br>
	 *			If the parameter <i>newSize</i> is 0, this function returns a pointer of parameter <i>ptr</i> directly.<br>
	 *			Function ::FSCRT_Memory_Realloc calls this function.
	 */
	FS_LPVOID	(*Realloc)(FS_LPVOID clientData, FS_LPVOID ptr, FS_DWORD newSize);

	/**
	 * @brief	A callback function to free a memory block.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 * @param[in]	ptr			Pointer to an existing memory block to be freed.
	 *
	 * @return	None.
	 *
	 * @note	Applications should avoid any exceptions when this function is called,
	 *			and should also ensure it supports multiple-thread environments.<br>
	 *			Function ::FSCRT_Memory_Free calls this function.
	 */
	void		(*Free)(FS_LPVOID clientData, FS_LPVOID ptr);

} FSCRT_MEMMGRHANDLER;

#endif /* _FSCRT_DEF_HANDLER_MEMMGR_ */

/**
 * @brief	Create a Foxit PDF SDK manager.
 * 
 * @details	This is the first function to be called by applications. Applications should call this function to initialize Foxit PDF SDK library at first.<br>
 * 			It will cause unexpected errors to call other functions before this one.
 *
 * @param[in]	memory	Pointer to a pre-allocated memory buffer to initialize Foxit PDF SDK. It should be valid.
 * @param[in]	size	Buffer size specified by the parameter <i>memory</i>, in bytes. The parameter <i>size</i> should be at least 8MB.
 * @param[in]	memMgr	Pointer to a ::FSCRT_MEMMGRHANDLER structure to provide extensible memory management. The parameter <i>memMgr</i> may be <b>NULL</b> when no need to support extension.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_FINISHED if Foxit PDF SDK manager exists.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>memory</i> is <b>NULL</b>, or the parameter <i>size</i> is less than 8MB.<br>
 * 			::FSCRT_ERRCODE_ERROR if Foxit PDF SDK can't be initialized because of any other reasons.<br>
 *			::FSCRT_ERRCODE_HANDLER if one of the callback functions in the parameter <i>memMgr</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Call this function before others. Once this function is called, applications should not invoke the function ::FSCRT_Library_CreateDefaultMgr.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Library_CreateMgr(FS_LPVOID memory, FS_DWORD size, FSCRT_MEMMGRHANDLER* memMgr);

/**
 * @brief	Create a default Foxit PDF SDK manager by applications.
 *
 * @details	This is the first function to be called by applications. Applications should call this function to initialize Foxit PDF SDK library at first.<br>
 *			Calling this function to use a default memory allocation strategy.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_FINISHED if Foxit PDF SDK manager exists.<br>
 *			::FSCRT_ERRCODE_ERROR if Foxit PDF SDK can't be initialized because of any other reasons.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Call this function before others, Once this function is called, caller should not invoke the function ::FSCRT_Library_CreateMgr.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Library_CreateDefaultMgr();

/**
 * @brief	Get the current Foxit PDF SDK manager.
 * 
 * @details	This function is used under multiple-executive-module environments. 
 *			It is used to ensure the whole application use the same Foxit PDF SDK manager.
 *
 * @param[out]	sdkMgr	Pointer to a ::FS_LPVOID object that receives the current Foxit PDF SDK manager.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>sdkMgr</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Library_GetMgr(FS_LPVOID* sdkMgr);

/**
 * @brief	Set the current Foxit PDF SDK manager.
 *
 * @details	This function is used under multiple-executive-module environments. 
 *			It is used to ensure the whole application use the same Foxit PDF SDK manager.
 *			Current Foxit PDF SDK manager is often got by the function ::FSCRT_Library_GetMgr.
 * 
 * @param[in]	sdkMgr	Pointer to Foxit PDF SDK manager.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>sdkMgr</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Library_SetMgr(FS_LPVOID sdkMgr);

/**
 * @brief	Destroy the current Foxit PDF SDK manager.
 * 
 * @details	This function releases all internal resources and frees the current Foxit PDF SDK manager.
 *
 * @return	None.
 * 
 * @note	Call this function only in the executive module in which current Foxit PDF SDK manager is created 
 *			by the previous function ::FSCRT_Library_CreateMgr or ::FSCRT_Library_CreateDefaultMgr.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
void		FSCRT_Library_DestroyMgr();

/**
 * @brief	Get the used memory size of the fixed memory manager in Foxit PDF SDK. Only available when a library manager is created by the function ::FSCRT_Library_CreateMgr.
 *
 * @param[out]	memSize		Pointer to ::FS_DWORD object that receives the memory size of the fixed memory manager in Foxit PDF SDK.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>memSize</i> is <b>NULL</b> .<br>
 *			::FSCRT_ERRCODE_INVALIDMANAGER if the current Foxit PDF SDK manager is not initialized.<br>
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
FS_RESULT	FSCRT_Library_GetFixedMemSize(FS_DWORD* memSize);

/**
 * @brief	Unlock Foxit PDF SDK library using a license key and a code.
 * 
 * @details	Applications should call this function to unlock library.<br>
 * 			This function should be called after Foxit PDF SDK manager is created and a library is initialized successfully.<br>
 * 			Please purchase an authorized Foxit PDF SDK license.
 *
 * @param[in]	licenseKey	Pointer to a binary string (may not be a UTF-8 string here) that specifies license key value.
 * @param[in]	unlockCode	Pointer to a binary string (may not be a UTF-8 string here) that specifies license code value.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>licenseKey</i> or <i>unlockCode</i> is a <b>NULL</b> pointer, or their content is empty.<br>
 * 			::FSCRT_ERRCODE_FORMAT if content in the parameter <i>licenseKey</i> or <i>unlockCode</i> is invalid or inapplicable.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	To know which type of license is accepted, please call the function ::FSCRT_License_GetType.<br>
 * 			Make sure a license is authorized before using Foxit PDF SDK library.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_License_UnlockLibrary(const FSCRT_BSTR* licenseKey, const FSCRT_BSTR* unlockCode);

/**
 * @brief	Get the current license type.
 * 
 * @details	Applications should call the function ::FSCRT_License_UnlockLibrary to unlock a library.<br>
 * 			Using this function to determine which type of license can be accepted.<br>
 * 			Please purchase authorized Foxit PDF SDK licenses.
 *
 * @param[out]	type		Pointer to ::FS_INT32 object that receives the current license type. It should be one of the followings:<br>
 *							<ul>
 *							<li>::FSCRT_LICENSETYPE_INVALID</li>
 *							<li>::FSCRT_LICENSETYPE_AUTHORIZED</li>
 *							<li>::FSCRT_LICENSETYPE_EVALUATION</li>
 *							<li>::FSCRT_LICENSETYPE_EXPIRED</li>
 *							</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>type</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Make sure a license is authorized before using Foxit PDF SDK library.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_License_GetType(FS_INT32* type);

/**
 * @brief	Set a log file handle. Currently only support Windows 32-bit, and not support Windows 8.
 *
 * @param[in]	file	Handle to a <b>FSCRT_FILE</b> object which is a log file.
 * 						This can only be created by function ::FSCRT_File_Create and ::FSCRT_File_Create_L.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>file</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDMANAGER if Foxit PDF SDK manager is not initialized.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>file</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Library_SetLogFile(FSCRT_FILE file);

/**
 * @brief	Enable or disable javascript for PDF.
 *
 * @details	Javascript for PDF is enabled by default.
 *
 * @param[in]	isEnabled	A boolean value that indicate to enable(<b>TRUE</b>) or disable(<b>FALSE</b>) javascript.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_INVALIDMANAGER if Foxit PDF SDK manager is not initialized.<br>
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
FS_RESULT	FSCRT_Library_EnableJavaScript(FS_BOOL isEnabled);

/**
 * @brief	Allocate a memory block.
 *
 * @param[in]	size	number of bytes to be allocated.
 * @param[out]	ptr		Pointer to a ::FS_LPVOID object that receives the allocated memory block.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>ptr</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
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
FS_RESULT	FSCRT_Memory_Alloc(FS_DWORD size, FS_LPVOID* ptr);

/**
 * @brief	Reallocate a memory block.
 *
 * @param[in]	ptr		Pointer to a memory block to be reallocated.
 * @param[in]	newSize	New size of memory block in bytes.
 * @param[out]	newPtr	Pointer to a ::FS_LPVOID object that receives a new reallocated memory block.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>newPtr</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if invalid memory access.<br>
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
FS_RESULT	FSCRT_Memory_Realloc(FS_LPVOID ptr, FS_DWORD newSize, FS_LPVOID* newPtr);

/**
 * @brief	Free a memory block.
 *
 * @param[in]	ptr	Pointer to a memory block allocated by the previous functions ::FSCRT_Memory_Alloc or ::FSCRT_Memory_Realloc.
 *
 * @return	None.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
void		FSCRT_Memory_Free(FS_LPVOID ptr);

/**
 * @brief	Get the current Foxit PDF SDK version.
 * 
 * @param[out]	sdkVersion	Pointer to a UTF-8 encoded string that receives a version. It should be a valid pointer to ::FSCRT_BSTR.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>sdkVersion</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Library_GetVersion(FSCRT_BSTR* sdkVersion);

/*******************************************************************************/
/* Thread supports                                                             */
/*                                                                             */
/* Thread handler and finalization                                             */
/*******************************************************************************/
#ifndef _FSCRT_DEF_HANDLE_THREAD_
#define _FSCRT_DEF_HANDLE_THREAD_

/** @brief	Handle type to thread object. */
FSCRT_DEFINEHANDLE(FSCRT_THREAD);

#endif /* _FSCRT_DEF_HANDLE_THREAD_ */

#ifndef _FSCRT_DEF_HANDLER_THREAD_
#define _FSCRT_DEF_HANDLER_THREAD_

/**
 * @brief	A callback function definition for finalizing a thread.
 * 
 * @param[in]	thread	Pointer to a <b>FSCRT_THREAD</b> object which is the current thread handle.
 * 
 * @return	None.
 * 
 * @note	This callback function is used by the callback function FSCRT_THREADHANDLER::SetThreadFinalizeCallback.<br>
 * 			Threads are maintained by applications, and Foxit PDF SDK doesn't care how many threads are running in an application at one time.<br>
 * 			But Foxit PDF SDK needs to access thread associated data which are maintained by Foxit PDF SDK internally.<br>
 * 			Foxit PDF SDK will pass a callback function to FSCRT_THREADHANDLER::SetThreadFinalizeCallback to release thread associated data.
 */
typedef void (*FSCRT_CALLBACK_THREADFINALIZE)(FSCRT_THREAD thread);

/**
 * @brief	Structure for multiple-thread support.
 *
 * @note	This is a handler and it is implemented by applications.<br>
 * 			Foxit PDF SDK supports multiple-thread environments, and maintain some internal data.
 */
typedef struct _FSCRT_THREADHANDLER
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Applicaitons can use this field to track controls.
	 */
	FS_LPVOID		clientData;

	/**
	 * @brief	A callback function to retrieve the current thread.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 *
	 * @return	The pointer to the current thread. <b>NULL</b> if fails.
	 */
	FSCRT_THREAD	(*GetCurrentThread)(FS_LPVOID clientData);

	/**
	 * @brief	A callback function to pass a callback function ::FSCRT_CALLBACK_THREADFINALIZE to applications.
	 *
	 * @param[in]	clientData				Pointer to user-defined data.
	 * @param[in]	callbackThreadFinalize	Pointer to a callback function ::FSCRT_CALLBACK_THREADFINALIZE.
	 *
	 * @return	None.
	 * 
	 * @note	Applications should save the parameter <i>callbackThreadFinalize</i> and call it when the current thread finishes.<br>
	 * 			This function will be called once applications call the function ::FSCRT_Library_SetThreadHandler.
	 */
	void			(*SetThreadFinalizeCallback)(FS_LPVOID clientData, FSCRT_CALLBACK_THREADFINALIZE callbackThreadFinalize);

} FSCRT_THREADHANDLER;

#endif /* _FSCRT_DEF_HANDLER_THREAD_ */

/**
 * @brief	Set a thread handler into Foxit PDF SDK library.
 *
 * @param[in]	threadHandler		Pointer to a ::FSCRT_THREADHANDLER structure to support multiple-thread environments.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>threadHandler</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_HANDLER if any callback functions in the parameter <i>threadHandler</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Call this function when applications need multiple-thread environment.<br>
 * 			To single-thread application, no need to call this function.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Library_SetThreadHandler(FSCRT_THREADHANDLER* threadHandler);

/**
 * @brief	Set the upper limit of PDF library cache size.
 *
 * @param[in]	size	The upper limit of the cache, in MegaBytes, 0~4096. 100 is recommended.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the size is greater than 4096.
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Currently, only font and image cache would be managed by this API.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Library_SetCacheSize(FS_DWORD size);

/*******************************************************************************/
/* Common data structures                                                             */
/*                                                                             */
/* date & time, rectangle, matrix                                              */
/*******************************************************************************/
#ifndef _FSCRT_DEF_STRUCTURE_DATETIMEZONE_
#define _FSCRT_DEF_STRUCTURE_DATETIMEZONE_

/** @brief	Structure for date and time. */
typedef struct _FSCRT_DATETIMEZONE
{
	/** @brief	Year, a four-digit number, such as 2014. */
	FS_UINT16		year;
	/** @brief	Month, from 1 to 12. */
	FS_UINT16		month;
	/** @brief	Day of month, from 1 to 31. */
	FS_UINT16		day;
	/** @brief	Day of week, from 0 to 6. PDF standard doesn't support now, you can omit this field if it is not applicable. */
	FS_UINT16		dayOfWeek;
	/** @brief	Hour, from 0 to 23. */
	FS_UINT16		hour;
	/** @brief	Minute, from 0 to 59. */
	FS_UINT16		minute;
	/** @brief	Second, from 0 to 60. 60 for leap second. */
	FS_UINT16		second;
	/** @brief	Millisecond, from 0 to 999. PDF standard doesn't support now, you can omit this field if it is not applicable. */
	FS_UINT16		milliseconds;
	/** 
	 * @brief	Hour of time zone, from -12 to 12. 
	 * 
	 * @details	Positive value for the eastern time zone, and negative value for the western time zone. 
	 */
	FS_INT16		tzHour;
	/** @brief	Minute of time zone, from 0 to 59. */
	FS_UINT16		tzMinute;
} FSCRT_DATETIMEZONE;

#endif /* _FSCRT_DEF_STRUCTURE_DATETIMEZONE_ */

#ifndef _FSCRT_DEF_STRUCTURE_RECT_
#define _FSCRT_DEF_STRUCTURE_RECT_

/**
 * @brief	Structure for rectangle, in integer.
 *
 * @note	This structure is used for device coordinates commonly.
 */
typedef struct _FSCRT_RECT
{
	/** @brief	Left coordinate. */
	FS_INT32		left;
	/** @brief	Top coordinate. */
	FS_INT32		top;
	/** @brief	Right coordinate. */
	FS_INT32		right;
	/** @brief	Bottom coordinate. */
	FS_INT32		bottom;
} FSCRT_RECT;

#endif /* _FSCRT_DEF_STRUCTURE_RECT_ */

#ifndef _FSCRT_DEF_STRUCTURE_RECTF_
#define _FSCRT_DEF_STRUCTURE_RECTF_

/**
 * @brief	Structure for rectangle, in float.
 *
 * @note	This structure is used for document coordinates commonly.
 */
typedef struct _FSCRT_RECTF
{
	/** @brief	Left coordinate. */
	FS_FLOAT		left;
	/** @brief	Top coordinate. */
	FS_FLOAT		top;
	/** @brief	Right coordinate. */
	FS_FLOAT		right;
	/** @brief	Bottom coordinate. */
	FS_FLOAT		bottom;
} FSCRT_RECTF;

#endif /* _FSCRT_DEF_STRUCTURE_RECTF_ */

#ifndef _FSCRT_DEF_STRUCTURE_QUADPOINTSF_
#define _FSCRT_DEF_STRUCTURE_QUADPOINTSF_

/**
 * @brief	Structure for quad points, in float.
 *
 * @note	Helper structure to access quad points data.
 */
typedef struct _FSCRT_QUADPOINTSF
{
	/** @brief	X coordinate for the first point. */
	FS_FLOAT	x1;
	/** @brief	Y coordinate for the first point. */
	FS_FLOAT	y1;
	/** @brief	X coordinate for the second point. */
	FS_FLOAT	x2;
	/** @brief	Y coordinate for the second point. */
	FS_FLOAT	y2;
	/** @brief	X coordinate for the third point. */
	FS_FLOAT	x3;
	/** @brief	Y coordinate for the third point. */
	FS_FLOAT	y3;
	/** @brief	X coordinate for the fourth point. */
	FS_FLOAT	x4;
	/** @brief	Y coordinate for the fourth point. */
	FS_FLOAT	y4;
} FSCRT_QUADPOINTSF;

#endif /* _FSCRT_DEF_STRUCTURE_QUADPOINTSF_ */

#ifndef _FSCRT_DEF_STRUCTURE_MATRIX_
#define _FSCRT_DEF_STRUCTURE_MATRIX_

/**
 * @brief	Structure for 2D matrix.
 *
 * @note	Matrix is used for coordinates transformation.
 */
typedef struct _FSCRT_MATRIX
{
	/** @brief	Coefficient a. */
	FS_FLOAT	a;
	/** @brief	Coefficient b. */
	FS_FLOAT	b;
	/** @brief	Coefficient c. */
	FS_FLOAT	c;
	/** @brief	Coefficient d. */
	FS_FLOAT	d;
	/** @brief	Coefficient e. */
	FS_FLOAT	e;
	/** @brief	Coefficient f. */
	FS_FLOAT	f;
} FSCRT_MATRIX;

#endif /* _FSCRT_DEF_STRUCTURE_MATRIX_ */

/**
 * @brief	Helper function to determine whether one rectangle is adjacent to another in the horizontal or vertical direction.
 *
 * @param[in]	rect1					Pointer to a ::FSCRT_RECTF structure for the first rectangle.
 * @param[in]	rect2					Pointer to a ::FSCRT_RECTF structure for the second rectangle.
 * @param[in]	alignmentTolerance		Alignment tolerance to be allowed between two rectangles. Measured in coordinate units, and should be non-negative value.
 * @param[in]	distanceTolerance		Distance tolerance to be allowed between two rectangles. Measured in coordinate units, and should be non-negative value.
 * @param[in]	direction				Specify a direction to judge adjacent state between two rectangles:<br>
 *										<ul>
 *										<li>0 is horizontal</li>
 *										<li>1 is vertical.</li>
 *										</ul>
 * @param[out]	adjacent				Pointer to a ::FS_BOOL object that receives the adjacent state. 
 *										<b>TRUE</b> means the parameter <i>rect1</i> is adjacent to the parameter <i>rect2</i>, while <b>FALSE</b> means not.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>rect1</i> or <i>rect2</i> or <i>adjacent</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Rect_IsAdjacent(const FSCRT_RECTF* rect1, const FSCRT_RECTF* rect2,
								  FS_FLOAT alignmentTolerance, FS_FLOAT distanceTolerance, FS_DWORD direction,
								  FS_BOOL* adjacent);

/**
 * @brief	Translate a coordinate matrix.
 *
 * @param[in,out]	matrix		Pointer to a ::FSCRT_MATRIX structure.<br> 
 *								When this function is called, it is the source matrix.<br>
 *								When this function returns, it receives the translated matrix.
 * @param[in]		offsetX		X value by which to translate the parameter <i>matrix</i>. 
 * @param[in]		offsetY		Y value by which to translate the parameter <i>matrix</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>matrix</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Matrix_Translate(FSCRT_MATRIX* matrix, FS_FLOAT offsetX, FS_FLOAT offsetY);

/**
 * @brief	Scale a coordinate matrix.
 *
 * @param[in,out]	matrix		Pointer to a ::FSCRT_MATRIX structure.<br> 
 *								When this function is called, it is the source matrix.<br>
 *								When this function returns, it receives the scaled matrix.
 * @param[in]		scaleX		X-axis scale value. 
 * @param[in]		scaleY		Y-axis scale value.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>matrix</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Matrix_Scale(FSCRT_MATRIX* matrix, FS_FLOAT scaleX, FS_FLOAT scaleY);

/**
 * @brief	Rotate a coordinate matrix.
 *
 * @param[in,out]	matrix	Pointer to a ::FSCRT_MATRIX structure.<br> 
 *							When this function is called, it is the source matrix.<br>
 *							When this function returns, it receives the rotated matrix.
 * @param[in]		angle	Angle of rotation, in radian.<br>
 *  						For a coordinate in which Y-axis is downward, positive value means rotation in clockwise and negative value means rotation in counterclockwise.<br>
 * 							If Y-axis is upward, rotation direction is inverse.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>matrix</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Matrix_Rotate(FSCRT_MATRIX* matrix, FS_FLOAT angle);

/**
 * @brief	Make a shear transformation on a coordinate matrix.
 *
 * @param[in,out]	matrix	Pointer to a ::FSCRT_MATRIX structure.<br> 
 *							When this function is called, it is the source matrix.<br>
 *							When this function returns, it receives the sheared matrix.
 * @param[in]		alpha	X-axis shear angle, in radian.<br>
 *  						For a coordinate in which Y-axis is downward, positive value means a clockwise shear, and negative value means a counterclockwise shear.
 * 							If Y-axis is upward, shear direction is inverse.
 * @param[in]		beta	Y-axis shear angle, in radian.<br>
 *  						For a coordinate in which Y-axis is downward, positive value means a counterclockwise shear and negative value means a clockwise shear.
 * 							If Y-axis is upward, shear direction is inverse.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>matrix</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Matrix_Shear(FSCRT_MATRIX* matrix, FS_FLOAT alpha, FS_FLOAT beta);

/**
 * @brief	Get a reversed matrix.
 *
 * @param[in]	srcMatrix	Pointer to a ::FSCRT_MATRIX structure for source matrix.
 * @param[out]	dstMatrix	Pointer to a ::FSCRT_MATRIX structure that receives a reversed matrix from the parameter <i>srcMatrix</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>srcMatrix</i> or <i>dstMatrix</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_ERROR if the parameter <i>srcMatrix</i> is not invertible.<br>
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
FS_RESULT	FSCRT_Matrix_GetReverse(const FSCRT_MATRIX* srcMatrix, FSCRT_MATRIX* dstMatrix);

/**
 * @brief	Concatenate another matrix.
 *
 * @param[in,out]	dstMatrix	Pointer to a ::FSCRT_MATRIX structure.<br> 
 *								When this function is called, it is a matrix.<br>
 *								When this function returns, it receives the concatenated matrix.
 * @param[in]		srcMatrix	Pointer to a ::FSCRT_MATRIX structure for source matrix.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>dstMatrix</i> or <i>srcMatrix</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Matrix_Concat(FSCRT_MATRIX* dstMatrix, const FSCRT_MATRIX* srcMatrix);

/**
 * @brief	Transform an integer point by a matrix.
 *
 * @param[in]		matrix	Pointer to a ::FSCRT_MATRIX structure for a coordinate matrix.
 * @param[in,out]	x		Pointer to a ::FS_INT32 object.<br> 
 *							When this function is called, it means X coordinate value of point in integer<br>
 *							When this function returns, it's transformed by the parameter <i>matrix</i>.
 * @param[in,out]	y		Pointer to a ::FS_INT32 object.<br> 
 *							When this function is called, it means Y coordinate value of point in integer<br>
 *							When this function returns, it's transformed by the parameter <i>matrix</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>matrix</i> or <i>x</i> or <i>y</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Matrix_TransformPoint(const FSCRT_MATRIX* matrix, FS_INT32* x, FS_INT32* y);

/**
 * @brief	Transform a float point by a matrix.
 *
 * @param[in]		matrix	Pointer to a ::FSCRT_MATRIX structure for a coordinate matrix.
 * @param[in,out]	x		Pointer to a ::FS_FLOAT object.<br> 
 *							When this function is called, it means X coordinate value of point in float.<br>
 *							When this function returns, it's transformed by the parameter <i>matrix</i>.
 * @param[in,out]	y		Pointer to a ::FS_FLOAT object.<br> 
 *							When this function is called, it means Y coordinate value of point in float.<br>
 *							When this function returns, it's transformed by the parameter <i>matrix</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>matrix</i> or <i>x</i> or <i>y</i>  is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Matrix_TransformPointF(const FSCRT_MATRIX* matrix, FS_FLOAT* x, FS_FLOAT* y);

/**
 * @brief	Transform an integer rectangle by a matrix.
 *
 * @param[in]		matrix	Pointer to a ::FSCRT_MATRIX structure for a coordinate matrix.
 * @param[in,out]	rect	Pointer to a ::FSCRT_RECT structure.<br> 
 *							When this function is called, it means coordinate values of a rectangle in integer.<br>
 *							When this function returns, it's transformed by the parameter <i>matrix</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>matrix</i> or <i>rect</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Matrix_TransformRect(const FSCRT_MATRIX* matrix, FSCRT_RECT* rect);

/**
 * @brief	Transform a float rectangle by a matrix.
 *
 * @param[in]		matrix	Pointer to a ::FSCRT_MATRIX structure for a coordinate matrix.
 * @param[in,out]	rect	Pointer to a ::FSCRT_RECTF structure.<br> 
 *							When this function is called, it means coordinate value of a rectangle in float.<br>
 *							When this function returns, it's transformed by the parameter <i>matrix</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>matrix</i> or <i>rect</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSCRT_Matrix_TransformRectF(const FSCRT_MATRIX* matrix, FSCRT_RECTF* rect);

/*******************************************************************************/
/* Path Data                                                                   */
/*******************************************************************************/
#ifndef _FSCRT_DEF_HANDLE_PATHDATA_
#define _FSCRT_DEF_HANDLE_PATHDATA_

/** @brief	Handle type to a path data. */
FSCRT_DEFINEHANDLE(FSCRT_PATHDATA);

#endif /* _FSCRT_DEF_HANDLE_PATHDATA_ */

#ifndef _FSCRT_DEF_MACRO_POINTTYPE_
#define _FSCRT_DEF_MACRO_POINTTYPE_
/** 
 * @name	Macro Definitions for Path Point Types
 */
/**@{*/

/** 
 * @brief	Point type of Close Figure.
 *
 * @details	Specify that a figure is automatically closed after the corresponding line or curve is drawn. 
 *			The figure is closed by drawing a line from the line or curve endpoint to the point corresponding to the last ::FSCRT_POINTTYPE_MOVETO. 
 */
#define FSCRT_POINTTYPE_CLOSEFIGURE		1
/** 
 * @brief	Point type of Line To.
 *
 * @details	Specify that a line is to be drawn from the current position to this point, which becomes a new current position.
 */
#define FSCRT_POINTTYPE_LINETO			2
/** 
 * @brief	Point type of Bezier To.
 *
 * @details	Specifies that this point is a control point or ending point for a Bezier spline.
 */
#define FSCRT_POINTTYPE_BEZIERTO		4
/** 
* @brief	Point type of Move To.
*
* @details	Specify that this point starts a figure. This point becomes a new current position.
*/
#define FSCRT_POINTTYPE_MOVETO			6

/**@}*/
#endif /* _FSCRT_DEF_MACRO_POINTTYPE_ */

#ifndef _FSCRT_DEF_MACRO_FILLMODE_
#define _FSCRT_DEF_MACRO_FILLMODE_
/**
 * @name	Macro Definitions for Filling Mode Types
 */
/**@{*/

/** @brief	No fill color. */
#define FSCRT_FILLMODE_NONE				0
/** 
 * @brief	Alternate fill mode.
 *
 * @details	Represent a fill mode in which the system fills this area between odd-numbered and even-numbered polygon 
 *			sides on each scan line.
 */
#define FSCRT_FILLMODE_ALTERNATE		1
/** 
 * @brief	Winding fill mode.
 *
 * @details	Represent a fill mode in which the system uses a direction in which a figure is drawn to determine 
 *			whether to fill an area.
 */
#define FSCRT_FILLMODE_WINDING			2

/**@}*/
#endif /* _FSCRT_DEF_MACRO_FILLMODE_ */

/**
 * @brief	Create new path data.
 *
 * @param[out]	pathData		Pointer to a <b>FSCRT_PATHDATA</b> handle that receives an object of path data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_Create(FSCRT_PATHDATA* pathData);

/**
 * @brief	Clear all points of the given path data.
 *
 * @details	This function will free all memory allocated for the given path data. Applications can call the function ::FSCRT_PathData_AddPointsCount to increase memory.
 * 
 * @param[in]	pathData		Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if an error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_Clear(FSCRT_PATHDATA pathData);

/**
 * @brief	Release all related resources of the given path data.
 *
 * @param[in]	pathData		Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_Release(FSCRT_PATHDATA pathData);

/**
 * @brief	Get number of points of the given path data.
 *
 * @param[in]	pathData		Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 * @param[out]	count			Pointer to a ::FS_INT32 object that receives point count of the given path data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> or <i>count</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_CountPoints(FSCRT_PATHDATA pathData, FS_INT32* count);

/**
 *
 * @brief	Add a number of points to the given path data.
 *
 * @details	This function will reallocate more memory for the given number of points. Call the function ::FSCRT_PathData_Clear to free memory of all points.
 * 
 * @param[in]	pathData		Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 * @param[in]	count			Count of new points added to the given path data. It should not be negative.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b>, or the parameter <i>count</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	After call this function, you shall call the function ::FSCRT_PathData_SetPoint to set the points you add.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_AddPointsCount(FSCRT_PATHDATA pathData, FS_INT32 count);

/**
 * @brief	Get a specific point of the given path data.
 *
 * @param[in]	pathData		Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 * @param[in]	index			The index of the point.
 * @param[out]	x				Pointer to a ::FS_FLOAT object that receives the value of the X coordinate of the point.
 * @param[out]	y				Pointer to a ::FS_FLOAT object that receives the value of the Y coordinate of the point.
 * @param[out]	pointType		Pointer to a ::FS_INT32 object that receives path point types. It can be one or combination of the followings:<br> 
 *								<ul>
 *								<li>::FSCRT_POINTTYPE_CLOSEFIGURE</li>
 *								<li>::FSCRT_POINTTYPE_LINETO</li>
 *								<li>::FSCRT_POINTTYPE_BEZIERTO</li>
 *								<li>::FSCRT_POINTTYPE_MOVETO</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i>, <i>x</i>, <i>y</i> or <i>pointType</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of range.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	::FSCRT_POINTTYPE_LINETO, ::FSCRT_POINTTYPE_BEZIERTO and ::FSCRT_POINTTYPE_MOVETO can not be combined.
 *			Additionally, ::FSCRT_POINTTYPE_MOVETO and ::FSCRT_POINTTYPE_CLOSEFIGURE can not be combined as well.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_GetPoint(FSCRT_PATHDATA pathData, FS_INT32 index, FS_FLOAT* x, FS_FLOAT* y, FS_INT32* pointType);

/**
 * @brief	Set the specific point of the path data.
 *
 * @param[in]	pathData		Handle to a <b>FSCRT_PATHDATA</b> object which is the path data object.
 * @param[in]	index			The index of the point.
 * @param[in]	x				The value of the X coordinate of the point.
 * @param[in]	y				The value of the Y coordinate of the point.
 * @param[in]	pointType		The path point types. It can be one or combination of the followings:<br> 
 *								<ul>
 *								<li>::FSCRT_POINTTYPE_CLOSEFIGURE</li>
 *								<li>::FSCRT_POINTTYPE_LINETO</li>
 *								<li>::FSCRT_POINTTYPE_BEZIERTO</li>
 *								<li>::FSCRT_POINTTYPE_MOVETO</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b> or the parameter <i>pointType</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of range.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	::FSCRT_POINTTYPE_LINETO, ::FSCRT_POINTTYPE_BEZIERTO and ::FSCRT_POINTTYPE_MOVETO can not be combination. 
 *			Additionally, ::FSCRT_POINTTYPE_MOVETO and ::FSCRT_POINTTYPE_CLOSEFIGURE can not be combined as well.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_SetPoint(FSCRT_PATHDATA pathData, FS_INT32 index, FS_FLOAT x, FS_FLOAT y, FS_INT32 pointType);

/**
 * @brief	Remove the specific point of the given path data.
 *
 * @param[in]	pathData		Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 * @param[in]	index			The index of the given point.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of range.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_RemovePoint(FSCRT_PATHDATA pathData, FS_INT32 index);

/**
 * @brief	Add a point to start a figure. This point will become a new current position.
 *
 * @param[in]	pathData		Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 * @param[in]	x				The value of the X coordinate of the point.
 * @param[in]	y				The value of the Y coordinate of the point.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_MoveTo(FSCRT_PATHDATA pathData, FS_FLOAT x, FS_FLOAT y);

/**
 * @brief	Add a point to a given figure, and a line is to be drawn from the current position to this point, which then becomes a new current position.
 *
 * @param[in]	pathData	Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 * @param[in]	x			The value of the X coordinate of the point.
 * @param[in]	y			The value of the Y coordinate of the point.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_LineTo(FSCRT_PATHDATA pathData, FS_FLOAT x, FS_FLOAT y);

/**
 * @brief	Add Bezier points to a given path data.
 *
 * @param[in]	pathData	Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 * @param[in]	x1			The value of the X coordinate of the first control point.
 * @param[in]	y1			The value of the Y coordinate of the first control point.
 * @param[in]	x2			The value of the X coordinate of the second control point.
 * @param[in]	y2			The value of the Y coordinate of the second control point.
 * @param[in]	x3			The value of the X coordinate of the end point.
 * @param[in]	y3			The value of the Y coordinate of the end point.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Points and an ending point in the path constitutes a Bezier curve.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_CubicBezierTo(FSCRT_PATHDATA pathData, FS_FLOAT x1, FS_FLOAT y1, FS_FLOAT x2, FS_FLOAT y2, FS_FLOAT x3, FS_FLOAT y3);

/**
 * @brief	Add a rectangle figure to path data.
 *
 * @param[in]	pathData	Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 * @param[in]	rect		Pointer to a ::FSCRT_RECTF structure for a rectangle.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_AppendRect(FSCRT_PATHDATA pathData, const FSCRT_RECTF* rect);

/**
 * @brief	Add an ellipse figure to path data.
 *
 * @param[in]	pathData	Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 * @param[in]	rect		Pointer to a ::FSCRT_RECTF structure for a enclosing rectangle of an ellipse.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_AppendEllipse(FSCRT_PATHDATA pathData, const FSCRT_RECTF* rect);

/**
 * @brief	Close the last figure of path data.
 *
 * @param[in]	pathData	Handle to a <b>FSCRT_PATHDATA</b> object which is a path data object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if path data have no figures.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_CloseFigure(FSCRT_PATHDATA pathData);

/**
 * @brief	Transform all path points into path data with a given matrix.
 *
 * @param[in]	pathData	Handle to a <b>FSCRT_PATHDATA</b> object which is the path data object.
 * @param[in]	matrix		Pointer to a ::FSCRT_MATRIX structure for a coordinate matrix.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_PARAM if the parameter <i>pathData</i> or <i>matrix</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pathData</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_PathData_Transform(FSCRT_PATHDATA pathData, const FSCRT_MATRIX* matrix);

/*******************************************************************************/
/* Private Data                                                                */
/*******************************************************************************/
#ifndef _FSCRT_DEF_CALLBACK_FREEPRIVATEDATA_
#define _FSCRT_DEF_CALLBACK_FREEPRIVATEDATA_

/**
 * @brief	A callback function to free private data.
 * 
 * @param[in]	data	Pointer to private data to be freed.
 * 
 * @return	None.
 * 
 * @note	This callback is used as a paramter in the function ::FSCRT_Library_SetPrivateData. It will be called automatically to free private data in management.<br>
 * 			If there's no need to free private data, just pass <b>NULL</b> to the function ::FSCRT_Library_SetPrivateData.
 * 			When the function ::FSCRT_Library_RemovePrivateData is called to remove private data and the specified callback function here is not called, Foxit PDF SDK assumes applications could process.
 */
typedef void (*FSCRT_CALLBACK_FREEPRIVATEDATA)(FS_LPVOID data);

#endif /* _FSCRT_DEF_CALLBACK_FREEPRIVATEDATA_ */

/**
 * @brief	Set private data.
 * 
 * @param[in]	moduleID					Pointer to any module ID or identity code to distinguish private data. It shall not be <b>NULL</b>.
 * @param[in]	data						Pointer to any private data.
 * @param[in]	callbackFreePrivateData		Callback function address to free private data. Pass <b>NULL</b> if no need to free process.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>moduleID</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	Private data are a global feature in Foxit PDF SDK.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Library_SetPrivateData(FS_LPVOID moduleID, FS_LPVOID data, FSCRT_CALLBACK_FREEPRIVATEDATA callbackFreePrivateData);

/**
 * @brief	Get private data.
 * 
 * @param[in]	moduleID	Pointer to specify a module ID or identity code to distinguish private data. It shall not be <b>NULL</b>.
 * @param[out]	data		Pointer to a ::FS_LPVOID object that receives private data. It shall not be <b>NULL</b>.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>moduleID</i> or <i>data</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>moduleID</i> is not found.
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
FS_RESULT	FSCRT_Library_GetPrivateData(FS_LPVOID moduleID, FS_LPVOID* data);

/**
 * @brief	Remove private data.
 * 
 * @param[in]	moduleID	Pointer to specify a module ID or identity code to distinguish a private data. It shall not be <b>NULL</b>.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>moduleID</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>moduleID</i> is not found.
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	This function assumes applications free private data associated with the parameter <i>moduleID</i>,
 * 			so if applications specify a callback function to the function ::FSCRT_Library_SetPrivateData, it shall be omitted here.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Library_RemovePrivateData(FS_LPVOID moduleID);

/*******************************************************************************/
/* Common objects                                                              */
/*******************************************************************************/
#ifndef _FSCRT_DEF_HANDLE_DOCUMENT_
#define _FSCRT_DEF_HANDLE_DOCUMENT_

/** @brief	Handle type to a document. */
FSCRT_DEFINEHANDLE(FSCRT_DOCUMENT);

#endif /* _FSCRT_DEF_HANDLE_DOCUMENT_ */

#ifndef _FSCRT_DEF_HANDLE_PAGE_
#define _FSCRT_DEF_HANDLE_PAGE_

/** @brief	Handle type to a page. */
FSCRT_DEFINEHANDLE(FSCRT_PAGE);

#endif /* _FSCRT_DEF_HANDLE_PAGE_ */

#ifndef _FSCRT_DEF_DEFINEHANDLE_ANNOT_
#define _FSCRT_DEF_DEFINEHANDLE_ANNOT_

/** @brief	Handle type to an annot. */
FSCRT_DEFINEHANDLE(FSCRT_ANNOT);

#endif /* _FSCRT_DEF_DEFINEHANDLE_ANNOT_ */

#ifndef _FSCRT_DEF_MACRO_DOCUMENTTYPE_
#define _FSCRT_DEF_MACRO_DOCUMENTTYPE_
/**
 * @name	Macro Definitions for Document Types
 * @note	<b>FSCRT_DOCUMENT</b> is a common document type,  and a document object may be a different type, such as PDF document, ePub document.<br>
 *			Call function ::FSCRT_Doc_GetType to get a document type.
 */
/**@{*/

/** @brief	PDF document type. */
#define FSCRT_DOCUMENTTYPE_PDF			1
/** @brief	FDF document type. */
#define FSCRT_DOCUMENTTYPE_FDF			2

/**@}*/
#endif /* _FSCRT_DEF_MACRO_DOCUMENTTYPE_ */

/**
 * @brief	Get a document type.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a document object.
 * @param[out]	docType		Pointer to a ::FS_INT32 object that receives document type value. <br>
 *							Please refer to macro definitions <b>FSCRT_DOCUMENTTYPE_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>docType</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Doc_GetType(FSCRT_DOCUMENT document, FS_INT32* docType);

/**
 * @brief	Get a document handle related to a page.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a page object. A page is an element of a document.
 * @param[out]	document	Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives a handle of document object associated with the parameter <i>page</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>document</i> or <i>page</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *			    <li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Page_GetDocument(FSCRT_PAGE page, FSCRT_DOCUMENT* document);

/**
 * @brief	Get a page handle related to an annotation. Only support PDF annotation.
 *
 * @param[in]	annot		Handle to a <b>FSCRT_ANNOT</b> object which is an annotation object. An annotation is an element of a page.
 * @param[out]	page		Pointer to a <b>FSCRT_PAGE</b> handle that receives a handle of page associated with the parameter <i>annot</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>annot</i> or <i>page</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This function works when the "PDF Annotation" module is authorized.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>annot</i>: this handle is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Annot_GetPage(FSCRT_ANNOT annot, FSCRT_PAGE* page);

/*******************************************************************************/
/* Progressive controls                                                           */
/*******************************************************************************/
#ifndef _FSCRT_DEF_HANDLE_PROGRESS_
#define _FSCRT_DEF_HANDLE_PROGRESS_

/** @brief	Handle type to a progress. */
FSCRT_DEFINEHANDLE(FSCRT_PROGRESS);

#endif /* _FSCRT_DEF_HANDLE_PROGRESS_ */

#ifndef _FSCRT_DEF_HANDLER_PAUSE_
#define _FSCRT_DEF_HANDLER_PAUSE_

/**
 * @brief	Structure for pause control in progressive process.
 *
 * @note	This is a handler and is implemented by applications.<br>
 * 			if a process takes a long time, Foxit PDF SDK uses a progressive mechanism to release CPU control to applications.<br>
 *			The function ::FSCRT_Progress_Continue uses this handler to release the current CPU control.	
 */
typedef struct _FSCRT_PAUSEHANDLER
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Applications can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/**
	 * @brief	A callback function to indicates whether current running can be broken or not.
	 *
	 * @param[in]	clientData	Pointer to user-defined data.
	 *
	 * @return	<b>TRUE</b> means the current functions can be paused, or <b>FALSE</b> means not.
	 *
	 * @note	Usually, applictions can use a timer to determine how long the current function can run.
	 */
	FS_BOOL		(*NeedPauseNow)(FS_LPVOID clientData);

} FSCRT_PAUSEHANDLER;

#endif /* _FSCRT_DEF_HANDLER_PAUSE_ */

/**
 * @brief	Continue a progressive process.
 *
 * @param[in]	progress	Handle to a <b>FSCRT_PROGRESS</b> object which is a progressive object created by the <b>START</b> functions, such as ::FSPDF_RenderContext_StartPage.
 * @param[in]	pause		Pointer to a ::FSCRT_PAUSEHANDLER structure to determine break state.<br>
 * 							If it's <b>NULL</b> or FSCRT_PAUSEHANDLER::NeedPauseNow is <b>NULL</b>, this function will not return until it's finished or an error occurs.
 *
 * @return	::FSCRT_ERRCODE_FINISHED if the current process is finished successfully.<br>
 * 			::FSCRT_ERRCODE_TOBECONTINUED if the current process is paused, applications need to call this function again.<br>
 *			::FSCRT_ERRCODE_ROLLBACK if applications need to rollback.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>progress</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an memory exception raises.<br>
 * 			::FSCRT_ERRCODE_ERROR if an error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	A progress is a long-time process object, and it is splited with a ::FSCRT_PAUSEHANDLER structure.<br>
 * 			Foxit PDF SDK contains several different types of progressive processes. For example, the function ::FSPDF_Page_StartParse parses a PDF page, the function ::FSPDF_RenderContext_StartPage renders a PDF page, etc.
 * 			Different progressive processes implement this function in various ways, so it may return different error codes. Please refer to comments in <b>STRART</b> functions.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>For parsing page progress: 
 *					<ul>
 *					<li>This function is long-term recoverable.</li>
 *					<li><i>progress</i>: this handle is long-term recoverable.</li>
 *					</ul>
 *				</li>
 *				<li>For progress of importing page, saving document, rendering page, doing encryption, parsing reflow page, rendering reflow page: 
 *					<ul>
 *					<li>This function is long-term unrecoverable.</li>
 *					<li><i>progress</i>: this handle is long-term partially recoverable.</li>
 *					</ul>
 *				</li>
 *				<li>For progress of rendering annotation(s), rendering form control(s): 
 *					<ul>
 *					<li>This function is short-term.</li>
 *					<li><i>progress</i>: this handle is short-term.</li>
 *					</ul>
 *				</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Progress_Continue(FSCRT_PROGRESS progress, FSCRT_PAUSEHANDLER* pause);

/**
 * @brief	Get a percent of progressive process.
 *
 * @param[in]	progress		Handle to a <b>FSCRT_PROGRESS</b> object which is a progressive object created by the <b>START</b> functions, such as the function ::FSPDF_RenderContext_StartPage.
 * @param[out]	percent			Pointer to a ::FS_INT32 object that receives the current progressive percent.<br>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>progress</i> or <i>position</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fails to get percent for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Different progressive processes implement this function in various ways, so it may return different error codes.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>For parsing page progress: 
 *					<ul>
 *					<li>This function is long-term recoverable.</li>
 *					<li><i>progress</i>: this handle is long-term recoverable.</li>
 *					</ul>
 *				</li>
 *				<li>For progress of parsing reflow page, rendering reflow page: 
 *					<ul>
 *					<li>This function is long-term unrecoverable.</li>
 *					<li><i>progress</i>: this handle is long-term partially recoverable.</li>
 *					</ul>
 *				</li>
 *				<li>For progress of importing page, saving document, rendering page, doing encryption: 
 *					<ul>
 *					<li>This function is short-term.</li>
 *					<li><i>progress</i>: this handle is long-term partially recoverable.</li>
 *					</ul>
 *				</li>
 *				<li>For progress of rendering annotation(s), rendering form control(s): 
 *					<ul>
 *					<li>This function is short-term.</li>
 *					<li><i>progress</i>: this handle is short-term.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
FS_RESULT	FSCRT_Progress_GetPercent(FSCRT_PROGRESS progress, FS_INT32* percent);

/**
 * @brief	Release the current progressive process.
 *
 * @param[in]	progress		Handle to a <b>FSCRT_PROGRESS</b> object which is a progressive object created by <b>START</b> functions, such as the function ::FSPDF_RenderContext_StartPage.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>progress</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Different progressive processes implement this function in various ways, so it may return different error codes.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li>OOM property of <i>progress</i> depends on the actual kind of progress.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSCRT_Progress_Release(FSCRT_PROGRESS progress);

/**
 * @brief	Set property of current progressive process.
 *
 * @details	Currently, this function only support to set the property of "fileversion", and FSCRT_VAR::type shall be ::FSCRT_VT_INT32.
 *
 * @param[in]	progress		Handle to a <b>FSCRT_PROGRESS</b> object. It shall be valid.
 * @param[in]	property		Pointer to a ::FSCRT_BSTR structure or array that specifies the property information of a progress to be set.
 * @param[in]	values			Pointer to a ::FSCRT_VAR structure or array that specifies the value of a progress property. It shall match the parameter <i>property</i>.<br>
 * @param[in]	count			The count of properties to be set.<br>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>progress</i>, <i>property</i> or <i>values</i> is <b>NULL</b>, or value of <i>values</i> or <i>count</i> is invalid.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the current <i>progress</i> doesn't support this function.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the parameter <i>property</i> or <i>values</i> or <i>count</i> isn't supported.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Different progressive processes are implemented in various way, so it may return different error codes.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>For saving document progress: 
 *					<ul>
 *					<li>This function is long-term recoverable.</li>
 *					<li><i>progress</i>: this handle is long-term partially recoverable.</li>
 *					</ul>
 *				</li>
 *				<li>For other kind of progress: currently, not support this function.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Progress_SetProperty(FSCRT_PROGRESS progress, const FSCRT_BSTR* property, const FSCRT_VAR* values, FS_INT32 count);

/*******************************************************************************/
/* Font access                                                                 */
/*******************************************************************************/
#ifndef _FSCRT_DEF_HANDLE_FONT_
#define _FSCRT_DEF_HANDLE_FONT_



/** @brief	Handle type to a font. */
FSCRT_DEFINEHANDLE(FSCRT_FONT);

#endif /* _FSCRT_DEF_HANDLE_FONT_ */

#ifndef _FSCRT_DEF_MACRO_FONTSTYLE_
#define _FSCRT_DEF_MACRO_FONTSTYLE_
/**
 * @name	Macro Definitions for Font Flags.
 */
/**@{*/

/** @brief	Fixed pitch. */
#define FSCRT_FONTSTYLE_FIXEDPITCH		1
/** @brief	Serif. */
#define FSCRT_FONTSTYLE_SERIF			2
/** @brief	Symbolic. */
#define FSCRT_FONTSTYLE_SYMBOLIC		4
/** @brief	Script. */
#define FSCRT_FONTSTYLE_SCRIPT			8
/** @brief	Non-symbolic. */
#define FSCRT_FONTSTYLE_NONSYMBOLIC		32
/** @brief	Italic. */
#define FSCRT_FONTSTYLE_ITALIC			64
/** @brief	All cap. */
#define FSCRT_FONTSTYLE_ALLCAP			0x10000
/** @brief	Small cap. */
#define FSCRT_FONTSTYLE_SMALLCAP		0x20000
/** @brief	Force bold. */
#define FSCRT_FONTSTYLE_BOLD			0x40000

/**@}*/
#endif /* _FSCRT_DEF_MACRO_FONT_ */

#ifndef _FSCRT_DEF_MACRO_STDFONT_
#define _FSCRT_DEF_MACRO_STDFONT_
/**
 * @name	Macro Definitions for Standard Font ID
 */
/**@{*/

#define FSCRT_STDFONT_COURIER			0	/**< @brief	Courier. */
#define FSCRT_STDFONT_COURIER_B			1	/**< @brief	Bold. Courier-Bold. */
#define FSCRT_STDFONT_COURIER_BI		2	/**< @brief	Bold italic. Courier-BoldOblique. */
#define FSCRT_STDFONT_COURIER_I			3	/**< @brief	Italic. Courier-Oblique. */
#define FSCRT_STDFONT_HELVETICA			4	/**< @brief	Helvetica. */
#define FSCRT_STDFONT_HELVETICA_B		5	/**< @brief	Bold. Helvetica-Bold. */
#define FSCRT_STDFONT_HELVETICA_BI		6	/**< @brief	Bold italic. Helvetica-BoldOblique. */
#define FSCRT_STDFONT_HELVETICA_I		7	/**< @brief	Italic. Helvetica-Oblique. */
#define FSCRT_STDFONT_TIMES				8	/**< @brief	Times-Roman. */
#define FSCRT_STDFONT_TIMES_B			9	/**< @brief	Bold. Times-Bold. */
#define FSCRT_STDFONT_TIMES_BI			10	/**< @brief	Bold italic. Times-BoldItalic. */
#define FSCRT_STDFONT_TIMES_I			11	/**< @brief	Italic. Times-Italic. */
#define FSCRT_STDFONT_SYMBOL			12	/**< @brief	Symbol. */
#define FSCRT_STDFONT_ZAPFDINGBATS		13	/**< @brief	ZapfDingbats. */

/**@}*/
#endif /* _FSCRT_DEF_MACRO_STDFONT_ */

#ifndef _FSCRT_DEF_MACRO_CHARSET_
#define _FSCRT_DEF_MACRO_CHARSET_
/**
 * @name	Macro Definitions for Charsets
 * @note	Charsets are same as defined in Windows.
 */
/**@{*/

#define FSCRT_CHARSET_ANSI				0		/**< @brief	ANSI (United States, Western Europe). */
#define FSCRT_CHARSET_DEFAULT			1		/**< @brief	System default, for unknown or mapping purpose. */
#define FSCRT_CHARSET_SYMBOL			2		/**< @brief	Standard symbols. */
#define FSCRT_CHARSET_SHIFTJIS			128		/**< @brief	Japanese (Shift-JIS). */
#define FSCRT_CHARSET_HANGEUL			129		/**< @brief	Korean (Wansung). */
#define FSCRT_CHARSET_GB2312			134		/**< @brief	Simplified Chinese. */
#define FSCRT_CHARSET_CHINESEBIG5		136		/**< @brief	Traditional Chinese. */
#define FSCRT_CHARSET_THAI				222		/**< @brief	Thai. */
#define FSCRT_CHARSET_EASTEUROPE		238		/**< @brief	Eastern European. */
#define FSCRT_CHARSET_RUSSIAN			204		/**< @brief	Russian. */
#define FSCRT_CHARSET_GREEK				161		/**< @brief	Greek. */
#define FSCRT_CHARSET_TURKISH			162		/**< @brief	Turkish. */
#define FSCRT_CHARSET_HEBREW			177		/**< @brief	Hebrew. */
#define FSCRT_CHARSET_ARABIC			178		/**< @brief	Arabic. */
#define FSCRT_CHARSET_BALTIC			186		/**< @brief	Baltic. */

/**@}*/
#endif /* _FSCRT_DEF_MACRO_CHARSET_ */

#ifndef _FSCRT_DEF_HANDLER_FONTMAPPER_
#define _FSCRT_DEF_HANDLER_FONTMAPPER_

/**
 * @brief	Structure for font mapping.
 *
 * @note	This is a handler and it is implemented by applications. It is used to find a mapping font object for the given conditions.<br>
 */
typedef struct _FSCRT_FONTMAPPERHANDLER
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Applications can use this field to track controls.
	 */
	FS_LPVOID	clientData;
	
	/**
	 * @brief	Find a font for a particular PDF font.
	 *
	 * @param[in]	clientData		Pointer to user-supplied data.
	 * @param[in]	fontName		Pointer to a zero-terminated string for the given font name.
	 * @param[in]	fontStyles		Font Flags. Please refer to macro definitions of <b>FSCRT_FONTSTYLE_XXX</b> and this can be one or a combination of these macros.
	 * @param[in]	weight			Weight of a font. Range from 100 to 900. 400 is normal, 700 is bold.
	 * @param[in]	charset			Charset ID. Please refer to macro definitions of <b>FSCRT_CHARSET_XXX</b> and this shall be one of these macros.
	 * @param[out]	fontFile		Pointer to a <b>FSCRT_FILE</b> handle that receives a file object.
	 * @param[out]	faceIndex		Pointer to a ::FS_INT32 object that receives a zero-based index value for a font face,
	 * 								if the mapped font file is a "collection" (meaning a number of faces are stored in the same file).
	 * 								If the font file is not a collection, the index value shall be zero.
	 *
	 * @note	When implementing this callback function, user should pay attention to manage parameter <i>fontFile</i>:
	 *			<ul>
	 *			<li>User is strongly recommended to return the same <b>FSCRT_FILE</b> object if the same font is mapped in this callback fuction.</li>
	 *			<li>The <b>FSCRT_FILE</b> object should be kept valid in application level during the entire life cycle of Foxit PDF SDK, 
	 *				and should be released in application level before Foxit PDF SDK is destroyed.</li>
	 *			</ul>
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS means a substitution font has been specified.
	 *			Others means if a mapper can't be mapped to a font, or something is wrong.
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*MapFont)(FS_LPVOID clientData, FS_LPCSTR fontName,
						   FS_DWORD fontStyles, FS_INT32 weight, FS_INT32 charset,
						   FSCRT_FILE* fontFile, FS_INT32* faceIndex);
} FSCRT_FONTMAPPERHANDLER;

#endif /* _FSCRT_DEF_HANDLER_FONTMAPPER_ */

/**
 * @brief	Use a system font mapper (typically for Chinese/Japanese/Korean charsets).
 *
 * @details	This function is used for devices that come with one or more system fonts,
 *			and those fonts are in standard TrueType or Type1 format.
 *
 * @param[in]	fontMapperHandler	Pointer to a ::FSCRT_FONTMAPPERHANDLER structure.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>fontMapperHandler</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_HANDLER if any callback functions in the parameter <i>fontMapperHandler</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if a function can't set a font mapper handler for other reasons.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
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
FS_RESULT	FSCRT_Library_SetFontMapperHandler(FSCRT_FONTMAPPERHANDLER* fontMapperHandler);

/**
 * @brief	Add an additional font (typically a TrueType, Type1 or CFF font) to Foxit PDF SDK library from <b>FSCRT_FILE</b>.
 *
 * @details	This function can be called multiple times, each time to add a font to Foxit PDF SDK Library. 
 *			When calling the function ::FSCRT_Font_Create to create a font or display a document which has non-embedded fonts,
 *			Foxit PDF SDK Library will search a font from system fonts and also search all fonts added by this function.
 *
 * @param[in]	fontFile	Handle to a <b>FSCRT_FILE</b> object which is a font file to be added.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>fontFile</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to add an additional font for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>fontFile</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Library_AddFontFile(FSCRT_FILE fontFile);

/**
 * @brief	Load the installed local system fonts for Foxit PDF SDK.
 *
 * @details	This function is only useful for Linux, Windows 8.1 store app, WindowsPhone 8.1 and Windows 10 universal app.<br>
 *			And this function should be called after the library is initialized and before loading a PDF document.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to load system font map.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term not recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT		FSCRT_Library_LoadSystemFonts();

#ifndef _FSCRT_DEF_STRUCTURE_FONTFACE_
#define _FSCRT_DEF_STRUCTURE_FONTFACE_

/** @brief	Structure to get properties of a font face. */
typedef struct _FSCRT_FONTFACE
{
	/**
	 * @brief	The face name of font.
	 *
	 * @note	Applications should clear memory used by this field.
	 */
	FSCRT_BSTR		faceName;
	/** @brief	Judge whether a font is bold or not. */
	FS_BOOL			bold;
	/** @brief	Judge whether a font is italic or not. */
	FS_BOOL			italic;
} FSCRT_FONTFACE;

#endif /* _FSCRT_DEF_STRUCTURE_FONTFACE_ */

/**
 * @brief	Create a font with the given attributes.
 *
 * @param[in]	fontName		Pointer to a UTF-8 encoded string, it should be a valid pointer to ::FSCRT_BSTR that specifies a typeface name of a given font.
 * @param[in]	fontStyles		The font styles. Please refer to macro definitions of <b>FSCRT_FONTSTYLE_XXX</b> and this can be one or a combination of these macros.
 * @param[in]	weight			Original font weight. 0 means unspecified.
 * @param[in]	charset			The charset of the font. Please refer to macro definitions of <b>FSCRT_CHARSET_XXX</b> and this shall be one of these macros.
 * @param[out]	font			Pointer to a <b>FSCRT_FONT</b> handle that receives a new font object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>fontName</i> or <i>font</i> is <b>NULL</b> or other reasons.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to create a font object for other reasons, such as the private data of a font is <b>NULL</b> or unable to get an alternative font and so on.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Font_Create(const FSCRT_BSTR* fontName, FS_DWORD fontStyles, FS_INT32 weight, FS_INT32 charset, FSCRT_FONT* font);

/**
 * @brief	Create a standard font by a font ID.
 *
 * @param[in]	fontID			ID of standard font. Please refer to macro definitions of <b>FSCRT_STDFONT_XXX</b> and this should be one of these macros. 
 * @param[out]	font			Pointer to a <b>FSCRT_FONT</b> handle that receives a new font object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>font</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is invalid, fontID shall be at between 0 and 13.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to create font object for other reasons, such as the private data of a font is <b>NULL</b> and so on.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Font_CreateStandard(FS_INT32 fontID, FSCRT_FONT* font);

/**
 * @brief	Enum faces from a font file.
 *
 * @details	Commonly this function needs to be called twice:<br>
 *			For the first time, set the parameter <i>faces</i> to be <b>NULL</b> to get buffer size, 
 *			which will be returned by the parameter <i>count</i>.<br>
 *			Then use <i>count</i> to allocate <i>faces</i>.<br>
 *			For the second time, input <i>faces</i> with enough space and its <i>count</i>. 
 *			When this function returns successfully, <i>faces</i> will receive face information.<br>
 *			The size of <i>faces</i> shall not be less than buffer size, and the parameter <i>count</i> shall not be empty.
 *
 * @param[in]	fontFile		Handle to a <b>FSCRT_FILE</b> object.
 * @param[out]	faces			Pointer to a ::FSCRT_FONTFACE structure that receives faces of a font file, it can be <b>NULL</b> to get the parameter <i>count</i>.
 * @param[out]	count			Pointer to a ::FS_INT32 object that receives the count of faces in a given font file.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>fontFile</i> or <i>count</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_FILE if fail to access the parameter <i>fontFile</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to enumerate font faces for other reasons,such as count of faces in a font is -1.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>fontFile</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Font_EnumFaces(FSCRT_FILE fontFile, FSCRT_FONTFACE* faces, FS_INT32* count);

/**
 * @brief	Create a font from a font file.
 *
 * @param[in]	fontFile		Handle to a <b>FSCRT_FILE</b> object.
 * @param[in]	faceIndex		The zero-based face index, range from [0, <i>faceCount</i>). <i>faceCount</i> is returned by function ::FSCRT_Font_EnumFaces.
 * @param[in]	charset			The charset of the font. Please refer to macro definitions of <b>FSCRT_CHARSET_XXX</b> and this should be one of these macros.
 * @param[out]	font			Pointer to a <b>FSCRT_FONT</b> handle that receives a new font object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>fontFile</i>, <i>font</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>faceIndex</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to create a font object for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>fontFile</i>: this handle is long-term recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Font_CreateFromFile(FSCRT_FILE fontFile, FS_INT32 faceIndex, FS_INT32 charset, FSCRT_FONT* font);

/**
 * @brief	Release a font object.
 *
 * @param[in]	font			Handle to a <b>FSCRT_FONT</b> object created by the function ::FSCRT_Font_CreateStandard, ::FSCRT_Font_Create or ::FSCRT_Font_CreateFromFile.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>font</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Font_Release(FSCRT_FONT font);

/**
 * @brief	Retrieve a face name of a font and return a name in string.
 *
 * @param[in]	font			Handle to a <b>FSCRT_FONT</b> object created by the function ::FSCRT_Font_CreateStandard, ::FSCRT_Font_Create or ::FSCRT_Font_CreateFromFile.
 * @param[out]	fontName		Pointer to a UTF-8 encoded string that receives a font name, it shall be a valid pointer to ::FSCRT_BSTR.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>font</i> or <i>fontName</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get font name for any other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Font_GetName(FSCRT_FONT font, FSCRT_BSTR* fontName);

/**
 * @brief	Judge whether a font object is bold or not.
 *
 * @param[in]	font			Handle to a <b>FSCRT_FONT</b> object created by the function ::FSCRT_Font_CreateStandard, ::FSCRT_Font_Create or ::FSCRT_Font_CreateFromFile.
 * @param[out]	bold			Pointer to a ::FS_BOOL object receives font style, that indicates if a font is bold or not.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>font</i> or <i>bold</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to judge wheter a font is bold or not for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Font_IsBold(FSCRT_FONT font, FS_BOOL* bold);

/**
 * @brief	Judge whether a font object is italic or not.
 *
 * @param[in]	font			Handle to a <b>FSCRT_FONT</b> object created by the function ::FSCRT_Font_CreateStandard, ::FSCRT_Font_Create or ::FSCRT_Font_CreateFromFile.
 * @param[out]	italic			Pointer to a ::FS_BOOL object receives the font style, that indicates if a font is italic or not.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>font</i> or <i>italic</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to judge whether a font is italic or not for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Font_IsItalic(FSCRT_FONT font, FS_BOOL* italic);

/**
 * @brief	Get an ascent value of a font.
 *
 * @param[in]	font			Handle to a <b>FSCRT_FONT</b> object created by the function ::FSCRT_Font_CreateStandard, ::FSCRT_Font_Create or ::FSCRT_Font_CreateFromFile.
 * @param[out]	ascent			Pointer to a ::FS_INT32 object receives a font ascent value.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>font</i> or <i>ascent</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get an ascent value for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Font_GetAscent(FSCRT_FONT font, FS_INT32* ascent);

/**
 * @brief	Get a descent value of a font.
 *
 * @param[in]	font			Handle to a <b>FSCRT_FONT</b> object created by the function ::FSCRT_Font_CreateStandard, ::FSCRT_Font_Create or ::FSCRT_Font_CreateFromFile.
 * @param[out]	descent			Pointer to a ::FS_INT32 object receives a font descent value.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>font</i> or <i>descent</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get descent value for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Font_GetDescent(FSCRT_FONT font, FS_INT32* descent);

/**
 * @brief	Get a specific character bounding box of a font.
 *
 * @param[in]	font			Handle to a <b>FSCRT_FONT</b> object created by the function ::FSCRT_Font_CreateStandard, 
 *								::FSCRT_Font_Create or ::FSCRT_Font_CreateFromFile.
 * @param[in]	unicode			A character unicode value.
 * @param[out]	bbox			Pointer to a ::FSCRT_RECT object that receives a character bounding box.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>font</i> or <i>bbox</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get character bounding box for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT  FSCRT_Font_GetCharBBox(FSCRT_FONT font, FS_DWORD unicode, FSCRT_RECT* bbox);

/**
 * @brief	 Get a specific character width of a font.
 *
 * @param[in]	font			Handle to a <b>FSCRT_FONT</b> object created by function ::FSCRT_Font_CreateStandard, 
 *								::FSCRT_Font_Create or ::FSCRT_Font_CreateFromFile.
 * @param[in]	unicode			A character unicode value.
 * @param[out]	width			Pointer to a ::FS_FLOAT object that receives character width.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>font</i> or <i>width</i> is <b>NULL</b>.<br>
* 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to get character width for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>font</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT  FSCRT_Font_GetCharWidth(FSCRT_FONT font, FS_DWORD unicode, FS_FLOAT* width);

/*******************************************************************************/
/* Common definitions                                                          */
/*                                                                             */
/* Macros for search flags, ciphers                                            */
/*******************************************************************************/
#ifndef _FSCRT_DEF_MACRO_SEARCHFLAG_
#define _FSCRT_DEF_MACRO_SEARCHFLAG_
/**
 * @name	Macro Definitions for Search Flags 
 */
/**@{*/

/** @brief	Whether is it a matching case. */
#define FSCRT_SEARCHFLAG_MATCHCASE			1
/** @brief	Whether is it a matching whole word. */
#define FSCRT_SEARCHFLAG_MATCHWHOLEWORD		2
/** @brief	Whether matching consecutively (for example, "CC" will match twice in "CCC").*/
#define FSCRT_SEARCHFLAG_CONSECUTIVE		4

/**@}*/
#endif /* _FSCRT_DEF_MACRO_SEARCHFLAG_ */

#ifndef _FSCRT_DEF_MACRO_CIPHER_
#define _FSCRT_DEF_MACRO_CIPHER_
/**
 * @name	Macro Definitions for Encryption Algorithm.
 */
/**@{*/

/** @brief	Not use encryption algorithm. */
#define FSCRT_CIPHER_NONE		0
/** @brief	Use RC4 encryption algorithm, with the key length between 5-bytes and 16-bytes. */
#define FSCRT_CIPHER_RC4		1
/** @brief	Use AES encryption algorithm, with the key length be 16-bytes or 32-bytes. */
#define FSCRT_CIPHER_AES		2

/**@}*/
#endif /* _FSCRT_DEF_MACRO_CIPHER_ */

#ifndef _FSCRT_DEF_MACRO_OBJECTTYPE_
#define _FSCRT_DEF_MACRO_OBJECTTYPE_
/**
 * @name	Macro Definitions for Object Type 
 */
/**@{*/

/** @brief	Unknown type. */
#define FSCRT_OBJECTTYPE_UNKNOWN		0
/** @brief	Document type. */
#define FSCRT_OBJECTTYPE_DOCUMENT		1
/** @brief	Section type. */
#define FSCRT_OBJECTTYPE_SECTION		2
/** @brief	Page type. */
#define FSCRT_OBJECTTYPE_PAGE			3
/** @brief	Annotation type. */
#define FSCRT_OBJECTTYPE_ANNOT			4
/** @brief	Form type. */
#define FSCRT_OBJECTTYPE_FORM			5
/** @brief	Form field type. */
#define FSCRT_OBJECTTYPE_FORMFIELD		6
/** @brief	Form control type. */
#define FSCRT_OBJECTTYPE_FORMCONTROL	7
/** @brief	Signature type. */
#define FSCRT_OBJECTTYPE_SIGNATURE		8
/** @brief	Pressure sensitive ink type. */
#define	FSCRT_OBJECTTYPE_PSI			9

/**@}*/
#endif /* _FSCRT_DEF_MACRO_OBJECTTYPE_ */

#ifndef _FSCRT_DEF_MACRO_PAGEROTATION_
#define _FSCRT_DEF_MACRO_PAGEROTATION_
/**
 * @name 	Macro Definitions for Page Rotation
 */
/**@{*/

/** @brief	No rotation. */
#define	FSCRT_PAGEROTATION_0		0
/** @brief	Rotate 90 degrees in clockwise direction. */
#define	FSCRT_PAGEROTATION_90		1
/** @brief	Rotate 180 degrees in clockwise direction. */
#define	FSCRT_PAGEROTATION_180		2
/** @brief	Rotate 270 degrees in clockwise direction. */
#define	FSCRT_PAGEROTATION_270		3

/**@}*/
#endif /* _FSCRT_DEF_MACRO_PAGEROTATION_ */

#ifndef _FSCRT_DEF_MACRO_LANGUAGE_
#define _FSCRT_DEF_MACRO_LANGUAGE_
/**
 * @name	Macro Definitions for Language
 */
/**@{*/

/** @brief	Unknown language. */
#define	FSCRT_LANGUAGE_UNK		0
/** @brief	Chinese Simplified. */
#define	FSCRT_LANGUAGE_CHS		1
/** @brief	Chinese Traditional. */
#define	FSCRT_LANGUAGE_CHT		2
/** @brief	Danish. */
#define	FSCRT_LANGUAGE_DAN		3
/** @brief	German. */
#define	FSCRT_LANGUAGE_DEU		4
/** @brief	English. */
#define	FSCRT_LANGUAGE_ENU		5
/** @brief	Spanish. */
#define	FSCRT_LANGUAGE_ESP		6
/** @brief	French. */
#define	FSCRT_LANGUAGE_FRA		7
/** @brief	Italian. */
#define	FSCRT_LANGUAGE_ITA		8
/** @brief	Korean. */
#define	FSCRT_LANGUAGE_KOR		9
/** @brief	Japanese. */
#define	FSCRT_LANGUAGE_JPN		10
/** @brief	Dutch. */
#define	FSCRT_LANGUAGE_NLD		11
/** @brief	Norwegian. */
#define	FSCRT_LANGUAGE_NOR		12
/** @brief	Brazilian Portuguese. */
#define	FSCRT_LANGUAGE_PTB		13
/** @brief	Finnish. */
#define	FSCRT_LANGUAGE_SUO		14
/** @brief	Swedish. */
#define	FSCRT_LANGUAGE_SVE		15

/**@}*/
#endif /* _FSCRT_DEF_MACRO_LANGUAGE_ */

#ifndef _FSCRT_DEF_DEFINEHANDLE_ARCHIVE_
#define _FSCRT_DEF_DEFINEHANDLE_ARCHIVE_

/** @brief	Handle type to an archive. */
FSCRT_DEFINEHANDLE(FSCRT_ARCHIVE);

#endif /* _FSCRT_DEF_DEFINEHANDLE_ARCHIVE_ */

/**
 * @brief	Create an archive object for serializing and de-serializing.
 *
 * @param[out]	archive		Pointer to a <b>FSCRT_ARCHIVE</b> handle that receives a handle of file object.
 *							If there's any errors, it will be set <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>archive</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>archive</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Archive_Create(FSCRT_ARCHIVE* archive);

/**
 * @brief	Release an archive handle.
 *
 * @param[in]	archive		Handle to a <b>FSCRT_ARCHIVE</b> object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>archive</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if it fails for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>archive</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Archive_Release(FSCRT_ARCHIVE archive);

/**
 * @brief	Get data from an archive object.
 *
 * @param[in]	archive		Handle to a <b>FSCRT_ARCHIVE</b> object.
 * @param[out]	data		Pointer to a ::FSCRT_BSTR structure that receives memory data from an archive object.<br>
 *							It shall be released by function ::FSCRT_BStr_Clear.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>archive</i> or <i>data</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if it fails for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention   <b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>archive</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Archive_GetData(FSCRT_ARCHIVE archive, FSCRT_BSTR* data);
 
/**
 * @brief	Load data to an archive object.
 *
 * @param[in]	archive		Handle to a <b>FSCRT_ARCHIVE</b> object.
 * @param[in]	data		Pointer to a ::FSCRT_BSTR object which represents data to be loaded to an archive object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>archive</i> or <i>data</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if it fails for other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>archive</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Archive_LoadData(FSCRT_ARCHIVE archive, const FSCRT_BSTR* data);

#ifndef _FSCRT_DEF_HANDLE_POSITION_
#define _FSCRT_DEF_HANDLE_POSITION_
/** @brief	Handle type to position. */
FSCRT_DEFINEHANDLE(FSCRT_POSITION);
#endif /* _FSCRT_DEF_HANDLE_POSITION_ */

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FSBASE */

#endif /* _FSCRT_BASE_R_H_ */
