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
 * @file	fpdf_signature_r.h
 * @brief	Header file for \ref FPDFSIGNATURE "PDF Signature" module of Foxit PDF SDK.
 * @details	This header file provides access to PDF signature, mainly about "reading" methods..<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Verify the signed PDF document.</li>
 *			<li>2. Get the properties of the signature field.</li>
 *			<li>3. Render the Signature on the render context. </li>
 *			</ul>
 *
 * @note	The Signature module only provides the third-party signature interface and requires the customers have their own signature implementation. 
 *			If you want to purchase Foxit PDF SDK license and use any functions of this module, please contact Foxit to enable this module explicitly.
 */

#ifndef _FSPDF_SIGNATURE_R_H_
#define _FSPDF_SIGNATURE_R_H_

/** 
 * @defgroup	FPDFSIGNATURE PDF Signature
 * @brief		Definitions for signature related operation.<br>
 *				Definitions and functions in this module are included in fpdf_signature_r.h and fpdf_signature_w.h.<br>
 *				Module: PDFSignature<br>
 *				License Identifier: PDFSignature/All<br>
 *				Available License Right: Reading/Writing.<br>
 *				For License Right <b>Reading</b>, see fpdf_signature_r.h.<br>
 *				For License Right <b>Writing</b>, see fpdf_signature_w.h.
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. Signature handler:
 *					<ul>
 *					<li>a. Register signature handler, and set an icon provider.</li>
 *					<li>b. Signature handler is used to sign a PDF document or verify a signature. 
 *						   It provides a common way to let application deal with the whole process according to their control purpose.
 *						   Signing a document and verifying a signature may spend a long time.</li>
 *					<li>c. Note: implementors should ensure thread safety to ::FSPDF_SIGNATUREHANDLER.</li>
 *					</ul>
 *				</li>
 *				<li>2. PDF signature:
 *					<ul>
 *					<li>a. Enumerate signatures in document level, add or remove a signature object.</li>
 *					<li>b. PDF Reference defines several types of signatures. Only document signature is supported in current Foxit PDF SDK.</li>
 *					<li>c. Reference: section 8.6.3 in PDF Reference 1.7 describes signature fields, and section 8.7 describes technologies of signature.</li>
 *					</ul>
 *				</li>
 *				<li>3. Signature properties:
 *					<ul>
 *					<li>a. Get or set properties of signature, access certificate chain or clear data of signature.</li>
 *					<li>b. In order to supplement requirements from customers, Foxit PDF SDK expands some new properties to signature.
 *						   They are DistinguishedName, Text, Bitmap, AppearanceFlags.</li>
 *					</ul>
 *				</li>
 *				<li>4. Verify:
 *					<ul>
 *					<li>a. Verify signature in a progressive process, get state of a signature and determine whether a signature is signed or not.</li>
 *					<li>b. Foxit PDF SDK will call callback functions defined in ::FSPDF_SIGNATUREHANDLER to verify signature.</li>
 *					</ul>
 *				</li>
 *				<li>5. Signature appearance: render a signature in PDF render context, or reset appearance of a signature.</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Base Definitions for Signature                                              */
/*                                                                             */
/* Handle definitions, macro definitions                                       */
/*******************************************************************************/
#ifndef _FSPDF_DEF_HANDLE_SIGNATURE_
#define _FSPDF_DEF_HANDLE_SIGNATURE_

/** @brief	Handle type to PDF signature. */
FSCRT_DEFINEHANDLE(FSPDF_SIGNATURE);

#endif /* _FSPDF_DEF_HANDLE_SIGNATURE_ */

#ifndef _FSPDF_DEF_MACRO_SIGNATURE_STATE_
#define _FSPDF_DEF_MACRO_SIGNATURE_STATE_
/**
 * @name	Macro definitions for PDF Signature State
 */
/**@{*/

/** @brief	Unknown signature. */
#define FSPDF_SIGNATURE_STATE_UNKNOWN		0
/** @brief	Unsigned signature. */
#define FSPDF_SIGNATURE_STATE_UNSIGNED		1
/** @brief	Valid signature. */
#define FSPDF_SIGNATURE_STATE_VALID			2
/** @brief	Invalid signature. */	
#define FSPDF_SIGNATURE_STATE_INVALID		3

/**@}*/
#endif /* _FSPDF_DEF_MACRO_SIGNATURE_STATE_ */

#ifndef _FSPDF_DEF_MACRO_SIGNATURE_APPEARANCE_
#define _FSPDF_DEF_MACRO_SIGNATURE_APPEARANCE_
/**
 * @name	Macro definitions for PDF Signature State
 */
/**@{*/

/** @brief	Show Foxit flag on signature appearance. */
#define FSPDF_SIGNATURE_APPEARANCE_FOXITFLAG		0x0001
/** @brief	Show label on description. */
#define FSPDF_SIGNATURE_APPEARANCE_LABEL			0x0002
/** @brief	Show reason on description. */
#define FSPDF_SIGNATURE_APPEARANCE_REASON			0x0004
/** @brief	Show date on description. */
#define FSPDF_SIGNATURE_APPEARANCE_DATE				0x0008
/** @brief	Show dn on description. */
#define FSPDF_SIGNATURE_APPEARANCE_DN				0x0010
/** @brief	Show location on description. */
#define FSPDF_SIGNATURE_APPEARANCE_LOCATION			0x0020
/** @brief	Show signer name on description. */
#define FSPDF_SIGNATURE_APPEARANCE_NAME				0x0040
/** @brief	Show image on signature appearance. */
#define FSPDF_SIGNATURE_APPEARANCE_IMAGE			0x0080
/** @brief	Show text on signature appearance. */
#define FSPDF_SIGNATURE_APPEARANCE_TEXT				0x0100

/**@}*/
#endif /* _FSPDF_DEF_MACRO_SIGNATURE_APPEARANCE_ */

#ifndef _FSPDF_DEF_MACRO_SIGNATURE_ICONFITMODE_
#define _FSPDF_DEF_MACRO_SIGNATURE_ICONFITMODE_
/**
 * @name	Macro definitions for PDF Signature State Icon Fit Mode
 */
/**@{*/

/** 
 * @brief	Icon fit mode: normal
 * 
 * @details Default size of icon is 32X32 and icon will displayed on the left-top corner of signature.
 */
#define FSPDF_SIGNATURE_ICONFITMODE_NORMAL		0
/** 
 * @brief	Icon fit mode: fit field
 *
 * @details This flag indicates to display the icon to fit the rectangle of signature. 
 */
#define FSPDF_SIGNATURE_ICONFITMODE_FITFIELD	1

/**@}*/
#endif /* _FSPDF_DEF_MACRO_SIGNATURE_ICONFITMODE_ */

#ifndef _FSPDF_DEF_HANDLER_SIGNATURE_
#define _FSPDF_DEF_HANDLER_SIGNATURE_
/**
 * @brief	Structure for Signature Handler.
 *
 * @note	This is a handler and is implemented by caller.<br>
 * 			When host application wants to do customize signing and verifying signature fields, this handler should be implemented and 
 *			function ::FSPDF_Signature_RegisterHandler should be called to register this handler to Foxit PDF SDK.
 */
typedef struct _FSPDF_SIGNATUREHANDLER
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Caller can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/**
	 * @brief	Foxit PDF SDK calls this interface to start a custom digest calculation.
	 *
	 * @param[in]	clientData		Pointer to the user-supplied data.
	 * @param[in]	sig				Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
	 * @param[in]	file			Handle to a <b>FSCRT_FILE</b> object.<br>
	 *								When signing a signature, it's the source file object to be signed.<br>
	 *								When verifying a signature field, it's the source file object to be verified.
	 * @param[in]	byteRangeArray	Pointer to a byte range array of the signed document(not the source document).<br>
	 *								Elements in this array always be in pairs of offset-size values in order of : offset,size,offset,size...
	 * @param[in]	sizeofArray		Count of elements in byte range array <i>byteRangeArray</i>.
	 * @param[out]	context			A pointer specifies a context handle. Return <b>NULL</b> if fails.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*StartCalcDigest)(FS_LPVOID clientData, FSPDF_SIGNATURE sig, FSCRT_FILE file, const FS_DWORD* byteRangeArray, FS_DWORD sizeofArray, FS_LPVOID* context);
	
	/**
	 * @brief	Foxit PDF SDK calls this interface to continue a custom digest calculation.
	 *
	 * @param[in]	clientData		Pointer to the user-supplied data.
	 * @param[in]	context			Pointer to context handle which is created by callback function FSPDF_SIGNATUREHANDLER::StartCalcDigest.
	 * @param[in]	pause			Pointer to a ::FSCRT_PAUSEHANDLER structure to determine break state.<br>
	 * 								If it's <b>NULL</b> or FSCRT_PAUSEHANDLER::NeedPauseNow is <b>NULL</b>, this function will not return until it's over or error occurs.
	 *
	 * @return	::FSCRT_ERRCODE_FINISHED for success.<br>
	 * 			::FSCRT_ERRCODE_TOBECONTINUED if the current process is paused, Foxit PDF SDK will call this function again.<br>
	 * 			::FSCRT_ERRCODE_ERROR if any internal running error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*ContinueCalcDigest)(FS_LPVOID clientData, FS_LPVOID context, FSCRT_PAUSEHANDLER* pause);
	
	/**
	 * @brief	Foxit PDF SDK calls this interface to finish the custom digest calculation and get the digest.
	 *
	 * @param[in]	clientData		Pointer to the user-supplied data.
	 * @param[in]	context			Pointer to context handle which is created by callback function FSPDF_SIGNATUREHANDLER::StartCalcDigest.
	 * @param[out]	digest			Pointer to a ::FSCRT_BSTR that receives the digest. A digest buffer is not required to be an UTF-8 string.<br>
	 * 								If it's <b>NULL</b> or FSCRT_PAUSEHANDLER::NeedPauseNow is <b>NULL</b>, this function will not return until it's over or error occurs.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 * 			::FSCRT_ERRCODE_ERROR if any internal running error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*FinishCalcDigest)(FS_LPVOID clientData, FS_LPVOID context, FSCRT_BSTR* digest);

	/**
	 * @brief	Foxit PDF SDK calls this interface to sign a document.
	 *
	 * @param[in]	clientData		Pointer to any type data which indicates user-defined data.
	 * @param[in]	context			Pointer to context handle which is created by callback function FSPDF_SIGNATUREHANDLER::StartCalcDigest.
	 * @param[in]	sig				Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
	 * @param[in]	digest			Pointer to a ::FSCRT_BSTR structure that indicates the digest of source file buffer to be signed.
	 * @param[out]	signedData		Pointer to a ::FSCRT_BSTR structure that receives the signed data. A signed buffer is not required to be an UTF-8 string.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 * 			::FSCRT_ERRCODE_ERROR if any internal running error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	Host application provides this callback method for custom sign mechanism. 
	 *			It is only called when function ::FSPDF_Signature_StartSign is invoked.
	 */
	FS_RESULT	(*Sign)(FS_LPVOID clientData, FS_LPVOID context, FSPDF_SIGNATURE sig, const FSCRT_BSTR* digest, FSCRT_BSTR* signedData);

	/**
	 * @brief	Verify a specified signature.
	 * 
	 * @param[in]	clientData		Pointer to any type data which indicates user-defined data.
	 * @param[in]	context			Pointer to context handle which is created by callback function FSPDF_SIGNATUREHANDLER::StartCalcDigest.
	 * @param[in]	sig				Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
	 * @param[in]	digest			Pointer to a ::FSCRT_BSTR structure that indicates the digest of source file buffer to be verified.
	 * @param[in]	signedData		Pointer to a ::FSCRT_BSTR structure which indicates the signed data. A signed data buffer is not required to be an UTF-8 string.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 * 			::FSCRT_ERRCODE_ERROR if any internal running error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	Host application provides this callback method for custom sign mechanism. 
	 *			It is only called when function ::FSPDF_Signature_StartVerify is invoked.
	 */
	FS_RESULT	(*Verify)(FS_LPVOID clientData, FS_LPVOID context, FSPDF_SIGNATURE sig, const FSCRT_BSTR* digest, const FSCRT_BSTR* signedData);

}FSPDF_SIGNATUREHANDLER;

#endif /* _FSPDF_DEF_HANDLER_SIGNATURE_ */

#ifndef _FSPDF_DEF_HANDLER_SIGNATUREICONPROVIDER_
#define _FSPDF_DEF_HANDLER_SIGNATUREICONPROVIDER_
/**
 * @brief	Structure for Signature Icon Provider Handler.
 *
 * @note	This is a handler and is implemented by caller.<br>
 * 			When host application wants to use customized icon according to signature state, this handler should be implement and 
 *			function ::FSPDF_Signature_SetIconProvider should be called to set this handler to Foxit PDF SDK.
 */
typedef struct _FSPDF_SIGNATUREICONPROVIDER
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Caller can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/**
	 * @brief	Callback function to retrieve the specific state icon of a signature.
	 * 
	 * @param[in]	clientData	Pointer to any type data which indicates user-defined data.
	 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
	 * @param[in]	nState		The state of signature.
	 *							Please refer to macro definitions <b>FSPDF_SIGNATURE_STATE_XXX</b> and this should be one of these macros.
	 * @param[out]	bitmap		Handle to a <b>FSCRT_BITMAP</b> object.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 * 			::FSCRT_ERRCODE_ERROR if any internal running error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	Host application provides this callback method for custom sign mechanism. 
	 *			This callback function will be triggered when Foxit PDF SDK is to display state icon of a signature 
	 *			if customized state icons are used.
	 */
	FS_RESULT	(*GetIcon)(FS_LPVOID clientData, FSPDF_SIGNATURE sig, FS_INT32 nState, FSCRT_BITMAP* bitmap);

	/**
	 * @brief	Callback function to receive the display mode of the specified state icon of a signature.
	 * 
	 * @param[in]	clientData	Pointer to any type data which indicates user-defined data.
	 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
	 * @param[in]	nState		The state of signature.
	 *							Please refer to macro definitions <b>FSPDF_SIGNATURE_STATE_XXX</b> and this should be one of these macros.
	 * @param[out]	fitMode		16-bit integer size of display mode.
	 *							Please refer to macro definitions <b>FSPDF_SIGNATURE_STATEICONFITMODE_XXX</b> and this should be one of these macros.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 * 			::FSCRT_ERRCODE_ERROR if any internal running error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	Host application provides this callback method for custom sign mechanism. 
	 *			This callback function will be triggered when Foxit PDF SDK displays state icon of a signature 
	 *			if customized state icons are used.
	 */
	FS_RESULT	(*GetIconFitMode)(FS_LPVOID clientData, FSPDF_SIGNATURE sig, FS_INT32 nState, FS_INT32* fitMode);

	/**
	 * @brief	Callback function to retrieve whether the signature specified state icon will be rotated after the page rotation.
	 * 
	 * @param[in]	clientData	Pointer to any type data which indicates user-defined data.
	 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
	 * @param[in]	nState		The state of signature.
	 *							Please refer to macro definitions <b>FSPDF_SIGNATURE_STATE_XXX</b> and this should be one of these macros.
	 * @param[out]	needRotate	<b>TRUE</b> means along with the rotation of the page otherwise <b>FALSE</b> means not with the rotating page.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 * 			::FSCRT_ERRCODE_ERROR if any internal running error occurs.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	Host application provides this callback method for custom sign mechanism. 
	 *			This callback function will be triggered when Foxit PDF SDK displays state icon of a signature 
	 *			if customized state icons are used.
	 */
	FS_RESULT	(*NeedRotate)(FS_LPVOID clientData, FSPDF_SIGNATURE sig, FS_INT32 nState, FS_BOOL* needRotate);

}FSPDF_SIGNATUREICONPROVIDER;

#endif /* _FSPDF_DEF_HANDLER_SIGNATUREICONPROVIDER_ */

/*******************************************************************************/
/* Signature handler                                                           */
/*******************************************************************************/
/**
 * @brief	A third-party handler registers their handler to Foxit PDF SDK, along with its filter and sub filter.
 *
 * @param[in]	filter		Pointer to a ::FSCRT_BSTR structure to indicate filter of a third-party handler. Filter is the name of handler.
 * @param[in]	subFilter	Pointer to a ::FSCRT_BSTR structure to indicate sub filter of a third-party handler. 
 *							Sub filter is to describe the encoding of signature value and key information in the signature dictionary.
 * @param[in]	sigHandler	Pointer to a ::FSPDF_SIGNATUREHANDLER structure. It is a handler of custom signature.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>filter</i>, or <i>sigHandler</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_HANDLER if any callback function in parameter <i>sigHandler</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the handler cannot be registered to Foxit PDF SDK because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If application wants to sign and verify signature, this function should be called first to register signature handler before signing and verifying.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Signature_RegisterHandler(const FSCRT_BSTR* filter, const FSCRT_BSTR* subFilter, FSPDF_SIGNATUREHANDLER* sigHandler);

/**
 * @brief	Set signature icon provider to Foxit PDF SDK.
 * 
 * @note	Signature icon provider provides methods to Foxit PDF SDK to extract state icon of signature and rendering mode of the icon 
 *			when displaying state icon of signature.
 *
 * @param[in]	iconProvider			Pointer to a ::FSPDF_SIGNATUREICONPROVIDER structure which is an custom signature icon provider handler.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_HANDLER if any callback function in parameter <i>iconProvider</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
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
FS_RESULT	FSPDF_Signature_SetIconProvider(FSPDF_SIGNATUREICONPROVIDER* iconProvider);

/*******************************************************************************/
/* PDF signature                                                               */
/*******************************************************************************/
/**
 * @brief	Get signature count in a PDF document.
 *
 * @param[in]	doc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[out]	count	Pointer to a ::FS_INT32 object that receives the count of total signatures in parameter <i>document</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>doc</i>, or <i>count</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>doc</i> is not a type of PDF document.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if signatures cannot be counted because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>doc</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Doc_CountSignatures(FSCRT_DOCUMENT doc, FS_INT32* count);

/**
 * @brief	Get a signature object.
 *
 * @param[in]	doc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	index	Index number starts from 0.
 * @param[out]	sig		Pointer to a <b>FSPDF_SIGNATURE</b> handle that receives the specific signature object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>doc</i>, or <i>sig</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>doc</i> is not a type of PDF document.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> exceeds the range of count of signature in <i>document</i>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the signature cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>doc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_GetSignature(FSCRT_DOCUMENT doc, FS_INT32 index, FSPDF_SIGNATURE* sig);

/**
 * @brief	Get a signature object by a specific position in PDF page.
 *
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[in]	x			Horizontal position in PDF page coordinate system.
 * @param[in]	y			Vertical position in PDF page coordinate system.
 * @param[in]	tolerance	Tolerance value for point, in PDF page coordinate system. Valid value: from 0.0f to 30.0f.
 * @param[out]	sig			Pointer to a <b>FSPDF_SIGNATURE</b> handle that receives the specific signature object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i> or <i>sig</i> is <b>NULL</b>, or <i>tolerance</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if there is no signature in the position.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if the signature cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Signature_GetAtPos(FSCRT_PAGE page, FS_FLOAT x, FS_FLOAT y, FS_FLOAT tolerance, FSPDF_SIGNATURE* sig);

/*******************************************************************************/
/* Access signature properties                                                 */
/*******************************************************************************/
/**
 * @brief	Retrieve the PDF document object related to a specific signature.
 *
 * @param[in]	sig		Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	doc		Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives a PDF document object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>doc</i>, or <i>sig</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>doc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Signature_GetDoc(FSPDF_SIGNATURE sig, FSCRT_DOCUMENT* doc);

/**
 * @brief	Get the index of a PDF page containing the specified signature.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	pageIndex	Pointer to a <b>FS_INT32</b> object that receives the index of a PDF page. Value -1 means error.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pageIndex</i>, or <i>sig</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if the page index cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_GetPageIndex(FSPDF_SIGNATURE sig, FS_INT32* pageIndex);

/**
 * @brief	Get annotation flags of a signature.
 *
 * @details	A signature field is also a widget annotation. So a signature can have annotation flags.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	flags		Pointer to a ::FS_DWORD object that receives the flags of signature.
 *							Please refer to macros <b>FSPDF_ANNOTFLAG_XXX</b> and this can be one or a combination of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i> or <i>flags</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if cannot get the current annotation flags of signature because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Signature_GetFlags(FSPDF_SIGNATURE sig, FS_DWORD* flags);

/**
 * @brief	Get the name of the preferred signature handler.
 *
 * @details	Filter is the name of signature handler,and it will be used to validate this signature.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	filter		Pointer to a ::FSCRT_BSTR structure that receives the name of the preferred signature handler to use.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>filter</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_ERROR if the name of the preferred signature handler to use cannot be obtained 
 *			when validating this signature because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_GetFilter(FSPDF_SIGNATURE sig, FSCRT_BSTR* filter);

/**
 * @brief	Get sub filter of a signature.
 *
 * @details Sub filter is used to describe the encoding of signature value and key information in the signature dictionary.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	subFilter	Pointer to a ::FSCRT_BSTR structure that receives a name that describes the encoding of the signature value 
 *							and key information.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>subFilter</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_ERROR if a name that describes the encoding of the signature value and key information 
 *			in the signature dictionary cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_GetSubFilter(FSPDF_SIGNATURE sig, FSCRT_BSTR* subFilter);

/**
 * @brief	Get signer name of a signature.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature.
 * @param[out]	signer		Pointer to a ::FSCRT_BSTR structure that receives signer name.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>signer</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_ERROR if the signer name cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_GetSigner(FSPDF_SIGNATURE sig, FSCRT_BSTR* signer);

/**
 * @brief	Get creation time of a signature(M entry in the dictionary).
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	dt			Pointer to a ::FSCRT_DATETIMEZONE structure that receives creation time.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>dt</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_ERROR if creation time cannot be obtained of signer because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_GetDateTime(FSPDF_SIGNATURE sig, FSCRT_DATETIMEZONE* dt);

/**
 * @brief	Get location information of signature owner(Location entry in the dictionary).
 *
 * @details	Location information of signer can be the host, MAC address, or a specific physical address. For example "FZ". 
 * 
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	location	Pointer to a ::FSCRT_BSTR structure that receives the signing location.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i> or <i>location</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_ERROR if location of signer cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_GetLocation(FSPDF_SIGNATURE sig, FSCRT_BSTR* location); 

/**
 * @brief	Get signing reason of a signature.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	reason		Pointer to a ::FSCRT_BSTR structure that receives the signing reason.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i> or <i>reason</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_ERROR if the signing reason cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_GetReason(FSPDF_SIGNATURE sig, FSCRT_BSTR* reason); 

/**
 * @brief	Get contact information of a signature.
 *
 * @details	Contact information provides methods about how to contact the signer. It can include mail, telephone etc.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	contactInfo	Pointer to a ::FSCRT_BSTR structure that receives the contact information.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i> or <i>contactInfo</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_ERROR if the contact information cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_GetContactInfo(FSPDF_SIGNATURE sig, FSCRT_BSTR* contactInfo);

/**
 * @brief	Get distinguished name of the signature owner.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	dn			Pointer to a ::FSCRT_BSTR structure that receives the distinguished name of signer.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i> or <i>dn</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_ERROR if the signer cannot be obtained distinguished name.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_GetDistinguishedName(FSPDF_SIGNATURE sig, FSCRT_BSTR* dn);

/**
 * @brief	Get the text content out of signature appearance.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	text		Pointer to a ::FSCRT_BSTR structure that receives the text content.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>text</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if the function can not be recovered.<br>
 *			::FSCRT_ERRCODE_ERROR if the text to be showed on signature appearance cannot be obtained.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_GetText(FSPDF_SIGNATURE sig, FSCRT_BSTR* text); 

/**
 * @brief	Get the icon bitmap in signature visual display.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	bitmap		Pointer to a <b>FSCRT_BITMAP</b> handle that receives the icon bitmap.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>bitmap</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the icon bitmap in signature visual display cannot be obtained.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				<li> <i>bitmap</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Signature_GetBitmap(FSPDF_SIGNATURE sig, FSCRT_BITMAP* bitmap);

/**
 * @brief	Get signature appearance flags.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	apFlags		Pointer to a ::FS_DWORD object receives the signature appearance state.
 *							Please refer to macro definitions <b>FSPDF_SIGNATURE_APPEARANCE_XXX</b> and this can be one or a combination of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i> or <i>apFlags</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if the signature appearance required display appearance cannot be obtained.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Signature_GetAppearanceFlags(FSPDF_SIGNATURE sig, FS_DWORD* apFlags);

/**
 * @brief	Count of certificates in the dictionary's certificate chain.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	certCount	Pointer to a ::FS_INT32 object that receives the count of certificates.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>certCount</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the number of certificate in the certificate chain cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	When sub filter of signature is adbe.x509.rsa_sha1, application needs to call this function to count certificates in certificate chain 
 *			and then call function ::FSPDF_Signature_GetCert to get verified public certificate before verifying signature.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Signature_CountCerts(FSPDF_SIGNATURE sig, FS_INT32* certCount);

/**
 * @brief	Get a signature certificate name from certificate chain.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	index		Index number of certificates which starts from 0.
 * @param[out]	signedCert	Pointer to a ::FSCRT_BSTR structure that receives the certificate.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>signedCert</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> exceeds the range of count of certificate in signature.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if a signature cert object in the chain cannot be obtained because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	When sub filter of signature is adbe.x509.rsa_sha1, application needs to call this function to get verified public certificate before verifying signature.
 *			The first certificate in certificate chain is the signing certificate, and it can be get to verify the signature.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Signature_GetCert(FSPDF_SIGNATURE sig, FS_INT32 index, FSCRT_BSTR* signedCert);

/*******************************************************************************/
/* Verify Signature                                                            */
/*******************************************************************************/
/**
 * @brief	Verify a signature progressively by using a signature signing handler specyfied by its Filter and SubFilter.
 *
 * @details	It may spend a long time to verify a signature, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass <i>verifyProgress</i> to ::FSCRT_Progress_Continue to continue verifying in steps, 
 *			and should call ::FSCRT_Progress_Release to destroy <i>verifyProgress</i> object if verifying process is over.<br>
 * 
 * @param[in]	sig				Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	verifyProgress	Pointer to a  <b>FSCRT_PROGRESS</b> handle that receives the progressive handle.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>verifyProgress</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if a signature field cannot be verified because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	The signature interface will trigger the callback custom authentication verification interface Handler.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				<li> <i>verifyProgress</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Signature_StartVerify(FSPDF_SIGNATURE sig, FSCRT_PROGRESS* verifyProgress);

/**
 * @brief	Get current state of a signature.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	state		Pointer to an integer value to receive current state of the signature .
 *							Please refer to macro definitions <b>FSPDF_SIGNATURE_STATE_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>state</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if the signature state cannot be obtained because of any reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Signature_GetState(FSPDF_SIGNATURE sig, FS_INT32* state);

/**
 * @brief	Determine whether a signature is signed or not.
 *	
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[out]	isSigned	Pointer to a ::FS_BOOL object that receives value indicatess if a signature is signed.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>isSigned</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the state that whether a signature field be signed cannot be determined because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_IsSigned(FSPDF_SIGNATURE sig, FS_BOOL* isSigned);

/*******************************************************************************/
/* Render Signature                                                            */
/*******************************************************************************/
/**
 * @brief	Render a signature on a render context.
 *
 * @param[in]	pdfRenderContext	Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a render context object.
 * @param[in]	renderer			Handle to a <b>FSCRT_RENDERER</b> object which is a renderer object.
 * @param[in]	sig					Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pdfRenderContext</i>, <i>renderer</i>, or <i>sig</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the state icon is FSCRT_BITMAPFORMAT_16BPP_RGB565 format.<br>
 *			::FSCRT_ERRCODE_ERROR if the signature failed to render because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 *				The Context flag FSPDF_RENDERCONTEXTFLAG_NOWIDGET and FSPDF_RENDERCONTEXTFLAG_NOSIGNATURE would be ignored.
 */
FS_RESULT	FSPDF_RenderContext_DrawSignature(FSPDF_RENDERCONTEXT pdfRenderContext, FSCRT_RENDERER renderer, FSPDF_SIGNATURE sig);

/**
 * @brief	Render all signatures of a page on render context.
 *
 * @details	This function can only render all normal appearance of signatures.<br>
 *			It will take a long time to render signatures with complex or large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass parameter <i>renderProgress</i> to function ::FSCRT_Progress_Continue to continue rendering in steps, 
 *			and should call function ::FSCRT_Progress_Release to destroy <i>renderProgress</i> object if rendering process is done.
 *
 * @param[in]	pdfRenderContext		Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF render context object.
 * @param[in]	renderer				Handle to a <b>FSCRT_RENDERER</b> object which is a renderer object.
 * @param[in]	page					Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[out]	renderProgress			Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pdfRenderContext</i>, <i>renderer</i>, <i>page</i>, or <i>renderProgress</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if page signatures are not loaded.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_ERROR if render signatures fails because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>renderProgress</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 *				The Context flag FSPDF_RENDERCONTEXTFLAG_NOWIDGET and FSPDF_RENDERCONTEXTFLAG_NOSIGNATURE would be ignored.
 */
FS_RESULT	FSPDF_RenderContext_StartPageSignatures(FSPDF_RENDERCONTEXT pdfRenderContext, FSCRT_RENDERER renderer, 
													FSCRT_PAGE page, FSCRT_PROGRESS* renderProgress);



#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFSIGNATURE */

#endif /* _FSPDF_SIGNATURE_R_H_ */

