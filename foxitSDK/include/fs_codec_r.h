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
 * @file	fs_codec_r.h
 * @brief	Header file for \ref FSBASE "Base" module of Foxit PDF SDK.
 * @details	This header file is a supplement for fs_base_r.h. It defines functions about coding conversion and digest algorithms.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. UTF-8 encoding and decoding. </li>
 *			<li>2. Base-4 encoding and decoding. </li>
 *			<li>3. Digest algorithms. </li>
 *			<li>4. Flate encoding and decoding. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> explicitly.
 */

#ifndef _FSCRT_CODEC_R_H_
#define _FSCRT_CODEC_R_H_

/** 
 * @defgroup	FSBASE Base
 * @brief		Base definitions for whole Foxit PDF SDK.<br>
 *				Definitions and functions in this module are included in fs_base_r.h and fs_codec_r.h.<br>
 *				Module: Base<br>
 *				License Identifier: Base/All<br>
 *				Available License Right: Unnecessary
 * @details		This module contains the following features:<br>
 *				<ul>
 *				<li>1. Basic definitions: involve definitions for basic types, error codes and variant types.</li>
 *				<li>2. Byte string:
 *					<ul>
 *					<li>a. In Foxit PDF SDK, a byte string is defined as a ::FSCRT_BSTR structure.
 *						   It is used as an inputting parameter or an outputting result.</li>
 *					<li>b. The related functions can be initialized, string data are cleared, or content is set.
 *						   ::FSCRT_BSTR should be UTF-8 format for common string data.
 *						   It can be used as binary string data in some functions.</li>
 *					<li>c. Note: The length rather than '/0' is used to judge whether FSCRT_BSTR is terminated.</li>
 *					</ul>
 *				</li>
 *				<li>3. UTF-8 conversion: convert strings between UTF-8 and UTF-16LE, UTF-16BE, UTF-32LE, UTF-32BE.</li>
 *				<li>4. Base-64: encode data into a Base-64 string or decode data from a Base-64 string.</li>
 *				<li>5. Digest: calculate digest by several algorithms: MD5, SHA1, SHA256, SHA384, SHA512.</li>
 *				<li>6. Flate: compress or decompress data by the flate or deflate algorithm.</li>
 *				<li>7. File access:
 *					<ul>
 *					<li>a. Create a file object from ::FSCRT_FILEHANDLER or directly from a file name, and retrieve file size.</li>
 *					<li>b. ::FSCRT_FILEHANDLER is an extension interface to support variant stream I/O.</li>
 *					<li>c. Note: Using ::FSCRT_FILEHANDLER needs to make sure thread safety if applications need to support multi-threaded environments.</li>
 *					</ul>
 *				</li>
 *				<li>8. Library management:
 *					<ul>
 *					<li>a. Initialize a library manager or destroy a library manager, unlock a library with the given license data, log file support and memory allocation.</li>
 *					<li>b. Any applications based on Foxit PDF SDK shall initialize Foxit PDF SDK first before calling other APIs.</li>
 *					<li>c. Note: A log file is provided for bugs investigated or performance analyzed. In most cases, it's not recommmended to set a log file.</li>
 *					</ul>
 *				</li>
 *				<li>9. Multi-thread:
 *					<ul>
 *					<li>a. Set an object of ::FSCRT_THREADHANDLER to Foxit PDF SDK to support multi-thread.</li>
 *					<li>b. Foxit PDF SDK maintains some context data for multi-thread. This increases stability.</li>
 *					</ul>
 *				</li>
 *				<li>10. Common data structures: 
 *					<ul>
 *					<li>a. Involve date, integer or float rectangle, quad points, matrix and path data.</li>
 *					<li>b. These features provide common supports on coordinates.</li>
 *					</ul>
 *				</li>
 *				<li>11. Private data: applications can set some private data into Foxit PDF SDK library.
 *						Private data can be shared between among executive modules.</li>
 *				<li>12. Common objects: documents, pages and annotations are three types of common objects.</li>
 *				<li>13. Progressive control: 
 *					<ul>
 *					<li>a. Progressive control is designed for those long-time-occupancy processes.</li>
 *					<li>b. Foxit PDF SDK contains some important features, such as saving PDF or encrypting PDF. It takes long time for these features to finish.
 *						   Progressive control can increase applicability. A progressive object which inherts from progressive control can have private properties.</li>
 *					</ul>
 *				</li>
 *				<li>14. Font access: 
 *					<ul>
 *					<li>a. Create font objects, retrieve font properties, or set font mappers to Foxit PDF SDK.</li>
 *					<li>b. Font is one of the most important resources and is used for text display.
 *						   Applications can create a new font or get an existing font in PDF.</li>
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
/* UTF-8                                                                       */
/*******************************************************************************/
/**
 * @brief	Get count of characters stored in a UTF-8 string.
 *
 * @param[in]	utf8Str		Pointer to a UTF-8 encoded string, it should be a valid pointer to ::FSCRT_BSTR.
 * @param[out]	count		Pointer to a ::FS_DWORD object that receives count of characters in parameter <i>utf8Str</i>. It should not be a <b>NULL</b> pointer.
 * @param[out]	pos			Pointer to a ::FS_DWORD object that receives index position of FSCRT_BSTR::str, in bytes, 
 *							indicating wrong byte position which is incompatible with UTF-8 format the in parameter <i>utf8Str</i>.<br>
 *							It's limited by the value of FSCRT_BSTR::len in the parameter <i>utf8Str</i>. Pass <b>NULL</b> to this parameter to ignore it.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>utf8Str</i> or <i>count</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_FORMAT if it is not a UTF-8 byte string in the parameter <i>utf8Str</i>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.<br>
 *			This function retrieves the real number of unicode characters stored in the parameter <i>utf8Str</i>.<br>
 *			If it contains any wrong bytes, the parameter <i>pos</i> is used to get an index and returns ::FSCRT_ERRCODE_FORMAT.<br>
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
FS_RESULT	FSCRT_UTF8_CountChars(const FSCRT_BSTR* utf8Str, FS_DWORD* count, FS_DWORD* pos);

/**
 * @brief	Convert a UTF-8 string to a UTF-16LE string.
 *
 * @param[in]		utf8Str		Pointer to a UTF-8 encoded string, it should be a valid pointer to ::FSCRT_BSTR.
 * @param[out]		buffer		Pointer to a buffer to receive a UTF-16LE string. It can be <b>NULL</b> when there isn't UTF-16LE string data.
 * @param[in,out]	length		Pointer to a ::FS_DWORD object receives the length of the given buffer.<br>
 *								When this function is called, it should be the size of parameter <i>buffer</i> in words (double bytes).<br>
 *								When this function returns, it contains the real number of UTF-16LE characters stored in the parameter <i>buffer</i>.<br>
 *								This parameter shall not be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>utf8Str</i> or <i>length</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_FORMAT if it isn't a UTF-8 byte string in the parameter <i>utf8Str</i>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.<br>
 *			UTF-16LE is a little-endian 16-bit Unicode format defined by Unicode Consortium.<br>
 *			Usually, this function is called twice: pass <b>NULL</b> to the parameter <i>buffer</i> first to retrieve buffer size,
 *			and call it again when the parameter <i>buffer</i> got from the first calling. The parameter <i>length</i> shall not be empty.<br>
 *			Return ::FSCRT_ERRCODE_FORMAT when it contains any incorrect bytes.<br>
 *			Applications can call the function ::FSCRT_UTF8_CountChars to check if there are any incorrect bytes.
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
FS_RESULT	FSCRT_UTF8_ToUTF16LE(const FSCRT_BSTR* utf8Str, FS_WORD* buffer, FS_DWORD* length);

/**
 * @brief	Convert a UTF-8 string to a UTF-16BE string.
 *
 * @param[in]		utf8Str		Pointer to a UTF-8 encoded string, it should be a valid pointer to ::FSCRT_BSTR.
 * @param[out]		buffer		Pointer to a buffer to receive UTF-16BE string. It can be <b>NULL</b> when there isn't UTF-16BE string data.
 * @param[in,out]	length		Pointer to a ::FS_DWORD object receives the length of buffer.<br>
 *								When this function is called, it should be the size of parameter the <i>buffer</i> in words (double bytes).<br>
 *								When this function returns, it contains the real number of UTF-16BE characters stored in the parameter <i>buffer</i>.<br>
 *								This parameter can't be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>utf8Str</i> or <i>length</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_FORMAT if it is not a UTF-8 byte string in the parameter <i>utf8Str</i>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding format defined by Unicode Consortium.<br>
 *			UTF-16BE is a big-endian 16-bit Unicode format defined by Unicode Consortium.<br>
 *			Usually, this function is called twice, pass <b>NULL</b> to the parameter <i>buffer</i> first to retrieve buffer size,<br>
 *			and call it again when the parameter <i>buffer</i> got from the first calling. The parameter <i>length</i> shall not be empty.<br>
 *			Return ::FSCRT_ERRCODE_FORMAT if there are incorrect byte formats.<br>
 *			Applications can call the function ::FSCRT_UTF8_CountChars to check if there are incorrect bytes.
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
FS_RESULT	FSCRT_UTF8_ToUTF16BE(const FSCRT_BSTR* utf8Str, FS_WORD* buffer, FS_DWORD* length);

/**
 * @brief	Convert a UTF-8 string to a UTF-32LE string.
 *
 * @param[in]		utf8Str		Pointer to a UTF-8 encoded string, it should be a valid pointer to ::FSCRT_BSTR.
 * @param[out]		buffer		Pointer to a buffer to receive UTF-32LE string. It can be <b>NULL</b> when there aren't UTF-32LE string data.
 * @param[in,out]	length		Pointer to a ::FS_DWORD object receives the length of buffer.<br>
 *								When this function is called, it should be the size of the parameter <i>buffer</i> in double words.<br>
 *								When this function returns, it contains the real number of UTF-32LE characters stored in the parameter <i>buffer</i>.<br>
 *								This parameter can't be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>utf8Str</i> or <i>length</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_FORMAT if it is not a UTF-8 byte string in the parameter <i>utf8Str</i>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding format defined by Unicode Consortium.<br>
 *			UTF-32LE is a little-endian 32-bit Unicode format defined by Unicode Consortium.<br>
 *			Usually, this function is called twice, pass <b>NULL</b> to the parameter <i>buffer</i> to retrieve buffer size,<br>
 *			and call it again when the parameter <i>buffer</i> got from the first calling. The parameter <i>length</i> shall not be empty.<br>
 *			Return ::FSCRT_ERRCODE_FORMAT when there are incorrect bytes.<br>
 *			Applications can call the function ::FSCRT_UTF8_CountChars to check if there are incorrect bytes.
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
FS_RESULT	FSCRT_UTF8_ToUTF32LE(const FSCRT_BSTR* utf8Str, FS_DWORD* buffer, FS_DWORD* length);

/**
 * @brief	Convert a UTF-8 string to a UTF-32BE string.
 *
 * @param[in]		utf8Str		Pointer to a UTF-8 encoded string, it shall be a valid pointer to ::FSCRT_BSTR.
 * @param[out]		buffer		Pointer to a buffer to receive UTF-32BE string. It can be <b>NULL</b> when there aren't UTF-32BE string data.
 * @param[in,out]	length		Pointer to a ::FS_DWORD object receives the length of buffer.<br>
 *								When this function is called, it shall be the size of the parameter <i>buffer</i> in double words.<br>
 *								When this function returns, it contains the real number of UTF-32BE characters stored in the parameter <i>buffer</i>.<br>
 *								This parameter shalln't be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>utf8Str</i> or <i>length</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_FORMAT if it isn't a UTF-8 byte string in the parameter <i>utf8Str</i>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding format defined by Unicode Consortium.<br>
 *			UTF-32BE is a big-endian 32-bit Unicode format defined by Unicode Consortium.<br>
 *			Usually, this function is called twice, pass <b>NULL</b> to the parameter <i>buffer</i> first to retrieve buffer size,<br>
 *			and call it again when the parameter <i>buffer</i> got from the first calling. The parameter <i>length</i> shalln't be empty.<br>
 *			Return ::FSCRT_ERRCODE_FORMAT if there are any incorrect bytes.<br>
 *			Applications can call the function ::FSCRT_UTF8_CountChars to check if there are incorrect bytes.
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
FS_RESULT	FSCRT_UTF8_ToUTF32BE(const FSCRT_BSTR* utf8Str, FS_DWORD* buffer, FS_DWORD* length);

/**
 * @brief	Encode a UTF-16LE string into a UTF-8 string.
 *
 * @param[out]	utf8Str		Pointer to a valid ::FSCRT_BSTR structure that receives a UTF-8 encoded string.
 * @param[in]	buffer		Pointer to a buffer which stores valid UTF-16LE string, it shalln't be <b>NULL</b>.
 * @param[in]	length		Length of UTF-16LE string in words (double bytes) stored in parameter <i>buffer</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>utf8Str</i> or <i>buffer</i> is a <b>NULL</b> pointer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.<br>
 *			UTF-16LE is a little-endian 16-bit Unicode format defined by Unicode Consortium.<br>
 *			This function will call the function ::FSCRT_Memory_Alloc or ::FSCRT_Memory_Realloc to allocate or reallocate memory to store UTF-8 string data in the parameter <i>utf8Str</i>.<br>
 *			It's necessary for applications to prepare buffer before calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. It may cause unexpected errors when the same object is handled by
 *				multiple threads. Applications shall maintain thread safety in this scenario.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_UTF8_FromUTF16LE(FSCRT_BSTR* utf8Str, const FS_WORD* buffer, FS_DWORD length);

/**
 * @brief	Convert a UTF-16BE string into a UTF-8 string.
 *
 * @param[out]	utf8Str		Pointer to a valid ::FSCRT_BSTR structure that receives a UTF-8 encoded string.
 * @param[in]	buffer		Pointer to a buffer which stores a valid UTF-16BE string, it shalln't be <b>NULL</b>.
 * @param[in]	length		Length of UTF-16BE string in words (double bytes) stored in the parameter <i>buffer</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>utf8Str</i> or <i>buffer</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding format defined by Unicode Consortium.<br>
 *			UTF-16BE is a big-endian 16-bit Unicode format defined by Unicode Consortium.<br>
 *			This function will call the function ::FSCRT_Memory_Alloc or ::FSCRT_Memory_Realloc to allocate or reallocate memory to store UTF-8 string data in the parameter <i>utf8Str</i>.<br>
 *			It's necessary for applications to prepare buffer before calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. It may cause unexpected errors when the same object is handled by
 *				multiple threads. Applications shall maintain thread safety in this scenario.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_UTF8_FromUTF16BE(FSCRT_BSTR* utf8Str, const FS_WORD* buffer, FS_DWORD length);

/**
 * @brief	Convert a UTF-32LE string into a UTF-8 string.
 *
 * @param[out]	utf8Str		Pointer to a valid ::FSCRT_BSTR structure that receives a UTF-8 encoded string.
 * @param[in]	buffer		Pointer to a buffer which stores a valid UTF-32LE string, it shall not be <b>NULL</b>.
 * @param[in]	length		Length of UTF-32LE string in words (double bytes) stored in the parameter <i>buffer</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>utf8Str</i> or <i>buffer</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding format defined by Unicode Consortium.<br>
 *			UTF-32LE is a little-endian 32-bit Unicode format defined by Unicode Consortium.<br>
 *			This function will call the function ::FSCRT_Memory_Alloc or ::FSCRT_Memory_Realloc to allocate or reallocate memory to store UTF-8 string data in the parameter <i>utf8Str</i>.<br>
 *			It's necessary for applications to prepare buffer before calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. It may cause unexpected errors when the same object is handled by
 *				multiple threads. Applications shall maintain thread safety in this scenario.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_UTF8_FromUTF32LE(FSCRT_BSTR* utf8Str, const FS_DWORD* buffer, FS_DWORD length);

/**
 * @brief	Convert a UTF-32BE string into a UTF-8 string.
 *
 * @param[out]	utf8Str		Pointer to a valid ::FSCRT_BSTR structure that receives a UTF-8 encoded string.
 * @param[in]	buffer		Pointer to a buffer which stores a valid UTF-32BE string, it cannot be <b>NULL</b>.
 * @param[in]	length		Length of UTF-32BE string in words (double bytes) is stored in the parameter <i>buffer</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>utf8Str</i> or <i>buffer</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	UTF-8 is a standard character encoding method defined by Unicode Consortium.<br>
 *			UTF-32BE is a big-endian 32-bit Unicode format defined by Unicode Consortium.<br>
 *			This function will call the function ::FSCRT_Memory_Alloc or ::FSCRT_Memory_Realloc to allocate or reallocate memory to store UTF-8 string data in the parameter <i>utf8Str</i>.<br>
 *			It's necessary for applications to prepare buffer before calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. It may cause unexpected errors when the same object is handled by
 *				multiple threads. Applications shall maintain thread safety in this scenario.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_UTF8_FromUTF32BE(FSCRT_BSTR* utf8Str, const FS_DWORD* buffer, FS_DWORD length);

/*******************************************************************************/
/* Base-64                                                                     */
/*******************************************************************************/
/**
 * @brief	Convert a BASE-64 string into a buffer.
 *
 * @param[in]		base64Str	Pointer to a valid ::FSCRT_BSTR structure which stores an original BASE-64 string.
 * @param[out]		buffer		Pointer to a buffer to receive decoded binary data. It can be <b>NULL</b> there aren't decoded data.
 * @param[in,out]	length		Pointer to a ::FS_DWORD object receives the length of buffer.<br>
 *								When this function is called, it should be the size of parameter <i>buffer</i> in bytes.<br>
 *								When this function returns, it contains the real length of data stored in the parameter <i>buffer</i>.<br>
 *								This parameter can't be <b>NULL</b>.
 * @param[out]		pos			Pointer to a ::FS_DWORD object that receives the index position of FSCRT_BSTR::str, in bytes, indicating wrong byte position which is incompatible with BASE-64 format in parameter <i>base64Str</i>.<br>
 *								It's limited by the value of FSCRT_BSTR::len in the parameter <i>base64Str</i>. Pass <b>NULL</b> to this parameter to ignore it.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>base64Str</i> or <i>length</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_FORMAT if it is not a BASE-64 byte string in the parameter <i>base64Str</i>.<br>
 *			::FSCRT_ERRCODE_BUFFEROVERFLOW if the parameter <i>length</i> is less than the required length when the parameter <i>buffer</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	BASE-64 is an industrial standard to encode any 3-byte binary data into 4 normal ASCII codes.<br>
 *			Usually, this function is called twice, pass <b>NULL</b> to the parameter <i>buffer</i> first to retrieve buffer size,
 *			and call it again when the parameter <i>buffer</i> got from the first calling. The parameter <i>length</i> shalln't be be empty.<br>
 *			Applications can call this function consecutively to decode a large amount of BASE-64 data. 
 *			Ensure FSCRT_BSTR::len can be divided by 4 (four BASE-64 ASCII codes) exactly in previous calls, 
 *			and pass all the remaining data in the last call, last equal signs ('=') will be omitted.<br>
 *			Return ::FSCRT_ERRCODE_FORMAT if the parameter <i>base64Str</i> contains incorrect format bytes and the error position is saved in the parameter <i>pos</i>.<br>
 *			It's necessary for applications to prepare buffer before calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. It may cause unexpected errors when the same object is handled by
 *				multiple threads. Applications shall maintain thread safety in this scenario.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Base64_DecodeToBuffer(const FSCRT_BSTR* base64Str, FS_LPVOID buffer, FS_DWORD* length, FS_DWORD* pos);

/**
 * @brief	Encode a buffer into a BASE-64 string.
 *
 * @param[out]	base64Str	Pointer to a valid ::FSCRT_BSTR structure that receives a BASE-64 encoded string.
 * @param[in]	buffer		Any binary data buffer, it shall not be <b>NULL</b>.
 * @param[in]	length		Length of parameter <i>buffer</i>, in bytes.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>base64Str</i> or <i>buffer</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	BASE-64 is an industrial standard to encode any 3-byte binary data into 4 normal ASCII codes.<br>
 *			One or two equal signs ('=') will be appended if the parameter <i>length</i> can not be divided by 3 (three bytes) exactly.<br>
 *			This function will call the function ::FSCRT_Memory_Alloc or ::FSCRT_Memory_Realloc to allocate or reallocate memory to store BASE-64 string data in the parameter <i>base64Str</i>.<br>
 *			It's necessary for applications to prepare buffer before calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. It may cause unexpected errors when the same object is handled by
 *				multiple threads. Applications shall maintain thread safety in this scenario.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Base64_EncodeFromBuffer(FSCRT_BSTR* base64Str, FS_LPCVOID buffer, FS_DWORD length);

/*******************************************************************************/
/* Digest algorithm                                                            */
/*******************************************************************************/
#ifndef _FSCRT_DEF_HANDLE_DIGEST_
#define _FSCRT_DEF_HANDLE_DIGEST_

/** @brief	Handle type to a DIGEST. */
FSCRT_DEFINEHANDLE(FSCRT_DIGEST);

#endif /* _FSCRT_DEF_HANDLE_DIGEST_ */

#ifndef _FSCRT_DEF_MACRO_DIGEST_
#define _FSCRT_DEF_MACRO_DIGEST_
/**
 * @name	Macro Definitions for Digest Algorithm Types
 */
/**@{*/

/** @brief	For MD5 algorithm that generates 128 bits digest. */
#define FSCRT_DIGEST_MD5		1
/** @brief	For SHA1 algorithm that generates 128 bits digest. */
#define FSCRT_DIGEST_SHA1		2
/** @brief	For SHA256 algorithm that generates 256 bits digest. */
#define FSCRT_DIGEST_SHA256		3
/** @brief	For SHA384 algorithm that generates 384 bits digest. */
#define FSCRT_DIGEST_SHA384		4
/** @brief	For SHA512 algorithm that generates 512 bits digest. */
#define FSCRT_DIGEST_SHA512		5

/**@}*/
#endif /* _FSCRT_DEF_MACRO_DIGEST_ */

/**
 * @brief	Setup a DIGEST context.
 *
 * @param[in]	digestType		The specified DIGEST algorithm type. Please refer to macro definitions <b>FSCRT_DIGEST_XXX</b> and this should be one of these macros.
 * @param[out]	digest			Pointer to a <b>FSCRT_DIGEST</b> handle that receives a new DIGEST object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>digest</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>digestType</i> is invalid, because <i>digestType</i> must be one of macro definitions <b>FSCRT_DIGEST_XXX</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or applications should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>digest</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSCRT_Digest_Start(FS_INT32 digestType, FSCRT_DIGEST* digest);

/**
 * @brief	Update the DIGEST with some new data. Function ::FSCRT_Digest_Start must be called before.
 *
 * @param[in]	digest		Handle to a <b>FSCRT_DIGEST</b> object returned by function ::FSCRT_Digest_Start.
 * @param[in]	buf			Pointer to the data buffer. The buffer will be replaced with encrypted/decrypted data.
 * @param[in]	size		number of bytes in the data buffer.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>digest</i> or <i>buf</i> is a <b>NULL</b> pointer. 
 *			Additionally, parameter <i>size</i> which is set improperly can be used to receive the error.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>digest</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */				
FS_RESULT	FSCRT_Digest_Update(FSCRT_DIGEST digest, FS_LPVOID buf, FS_DWORD size);

/**
 * @brief	Finish the process and output the digest.
 *
 * @param[in]	digest			Handle to a <b>FSCRT_DIGEST</b> object.
 * @param[out]	hash			Pointer to a ::FSCRT_BSTR structure that receives the hash value.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>digest</i> or <i>hash</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>digest</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */	
FS_RESULT	FSCRT_Digest_Finish(FSCRT_DIGEST digest, FSCRT_BSTR* hash);

/*******************************************************************************/
/* Flate compress or decompress                                                */
/*******************************************************************************/
/**
 * @brief	Compress data by using the flate algorithm.
 *
 * @param[in]	src		Pointer to a ::FSCRT_BSTR structure that specifies the input data.
 * @param[out]	dst		Pointer to a ::FSCRT_BSTR structure that receives the compressed data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>src</i> or <i>dst</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if internal memory meets exception.<br>
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
FS_RESULT	FSCRT_Flate_Compress(const FSCRT_BSTR* src, FSCRT_BSTR* dst);

/**
 * @brief	Decompress data by using the flate algorithm.
 *
 * @param[in]	src		Pointer to a ::FSCRT_BSTR structure that specifies the input data.
 * @param[out]	dst		Pointer to a ::FSCRT_BSTR structure that receives the decompressed data.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>src</i> or <i>dst</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if internal memory meets exception.<br>
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
FS_RESULT	FSCRT_Flate_Decompress(const FSCRT_BSTR* src, FSCRT_BSTR* dst);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FSBASE */

#endif /* _FSCRT_CODEC_R_H_ */
