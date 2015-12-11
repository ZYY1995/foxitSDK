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
 * @file	fpdf_signature_w.h
 * @brief	Header file for \ref FPDFSIGNATURE "PDF Signature" module of Foxit PDF SDK.
 * @details	This header file provides access to PDF signature, mainly about "writing" methods.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Add, clear and remove signature field.</li>
 *			<li>2. Set the properties of the signature field.</li>
 *			<li>3. Sign the signature field.</li>
 *			</ul>
 *
 * @note	The Signature module only provides the third-party signature interface and requires the customers have their own signature implementation. 
 *          If you want to purchase Foxit PDF SDK license and use any functions of this module, please contact Foxit to enable this module explicitly.
 */

#ifndef _FSPDF_SIGNATURE_W_H_
#define _FSPDF_SIGNATURE_W_H_

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
 *					<li>d. For the signed signature, Foxit PDF SDK also can modify it. In order to keep signature valid, application should not modify a signed signature.</li>
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
/* PDF signature                                                               */
/*******************************************************************************/
/**
 * @brief	Add an unsigned signature field without appearance to a specific position in a PDF page.
 *
 * @param[in]		page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[in]		rect		Pointer to a ::FSCRT_RECTF structure to specify rectangle position of new signature in PDF page, in PDF page coordinate system.
 * @param[out]		sig			Pointer to a <b>FSPDF_SIGNATURE</b> handle to receive the newly added PDF signature.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>rect</i>, or <i>sig</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if a signature field with a blank appearance at the specified page cannot be added because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	After adding a signature successfully, call ::FSPDF_Signature_InitValue to initialize the new signature before using it.
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
FS_RESULT 	FSPDF_Signature_Add(FSCRT_PAGE page, const FSCRT_RECTF* rect, FSPDF_SIGNATURE* sig);

/**
 * @brief	Remove a signature.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if a signature field cannot be removed because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Remove the seal, and user still needs to call the Release interface to release the signature of Handle.
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
FS_RESULT 	FSPDF_Signature_Remove(FSPDF_SIGNATURE sig);

/*******************************************************************************/
/* Access signature properties                                                 */
/*******************************************************************************/
/**
 * @brief	Set annotation flags of a signature.
 *
 * @details	A signature field is also a widget annotation. So a signature can have annotation flags.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	flags		Annotation flags used to set to signature. 
 *							Please refer to macro definitions <b>FSPDF_ANNOTFLAG_XXX</b> and this can be one or a combination of these macros. 
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if annotation flags of the current signature cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Signature_SetFlags(FSPDF_SIGNATURE sig, FS_DWORD flags);

/**
 * @brief	Set the name of the preferred signature handler to use for signature.
 *
 * @details	Filter is the name of signature handler,and it will be used to validate this signature.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	filter		Pointer to a ::FSCRT_BSTR structure to indicate the name of the preferred signature handler to use.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>filter</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the name of the preferred signature handler to use cannot be set
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
FS_RESULT 	FSPDF_Signature_SetFilter(FSPDF_SIGNATURE sig, const FSCRT_BSTR* filter);

/**
 * @brief	Set sub filter of a signature.
 *
 * @details Sub filter is used to describe the encoding of signature value and key information in the signature dictionary.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	subFilter	Pointer to ::FSCRT_BSTR structure that specifies the name describing the encoding of the signature value
 *							and key information.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>subFilter</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the name that describes the encoding of the signature value and key information 
 *			in the signature dictionary cannot be set because of any other reason.<br>
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
FS_RESULT 	FSPDF_Signature_SetSubFilter(FSPDF_SIGNATURE sig, const FSCRT_BSTR* subFilter);

/**
 * @brief	Set signer name of a signature.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature.
 * @param[in]	signer		Pointer to a ::FSCRT_BSTR structure that specifies the signer name.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>signer</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the signer name cannot be set because of any other reason.<br>
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
FS_RESULT 	FSPDF_Signature_SetSigner(FSPDF_SIGNATURE sig, const FSCRT_BSTR* signer);

/**
 * @brief	Set the creation time of a signature(M entry in the dictionary).
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	dt			Pointer to a ::FSCRT_DATETIMEZONE structure that specifies the creation time of the signature.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>dt</i> is <b>NULL</b>, or parameter <i>dt</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the creation time of signer cannot be set because of any other reason.<br>
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
FS_RESULT 	FSPDF_Signature_SetDateTime(FSPDF_SIGNATURE sig, const FSCRT_DATETIMEZONE* dt);

/**
 * @brief	The CPU host name or physical location of the signing.
 *
 * @details	Location information of signer: the host, MAC address, or a specific physical address. For example "FZ".
 * 
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	location	Pointer to a ::FSCRT_BSTR structure that specifies the signing location. 
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>location</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the location of signer cannot be set because of any other reason.<br>
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
FS_RESULT 	FSPDF_Signature_SetLocation(FSPDF_SIGNATURE sig, const FSCRT_BSTR* location);

/**
 * @brief	Set signing reason of a signature.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	reason		Pointer to a ::FSCRT_BSTR structure that specifies the signing reason. 
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>reason</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the signing reason cannot be set because of any other reason.<br>
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
FS_RESULT 	FSPDF_Signature_SetReason(FSPDF_SIGNATURE sig, const FSCRT_BSTR* reason);

/**
 * @brief	Set contact information of a signature.
 *
 * @details	Contact information provides methods about how to contact to the signer. It may include mail, telephone etc.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	contactInfo	Pointer to a ::FSCRT_BSTR structure that specifies the contact information.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>contactInfo</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the contact information cannot be set because of any other reason.<br>
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
FS_RESULT 	FSPDF_Signature_SetContactInfo(FSPDF_SIGNATURE sig, const FSCRT_BSTR* contactInfo);

/**
 * @brief	Set distinguished name of signer in a signature dictionary.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	dn			Pointer to a ::FSCRT_BSTR structure that specifies the distinguished name of signer.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>dn</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the signer distinguished name cannot be set because of any other reason.<br>
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
FS_RESULT 	FSPDF_Signature_SetDistinguishedName(FSPDF_SIGNATURE sig, const FSCRT_BSTR* dn);

/**
 * @brief	Set the text content out of signature appearance.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	text		Pointer to a ::FSCRT_BSTR structure that specifies the text content.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>text</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the text to be showed on signature appearance cannot be set because of any other reason.<br>
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
FS_RESULT 	FSPDF_Signature_SetText(FSPDF_SIGNATURE sig, const FSCRT_BSTR* text);

/**
 * @brief	Set a bitmap to icon in signature display.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	bitmap		Handle to a <b>FSCRT_BITMAP</b> object which specifies the icon of signature for visual display.<br>
 *							This object cannot be released until funcion ::FSPDF_Signature_ResetAppearance has been called for this signature object.
 *							And application should call function ::FSCRT_Bitmap_Release to release this <b>FSCRT_BITMAP</b> object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>bitmap</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>bitmap</i> is FSCRT_BITMAPFORMAT_16BPP_RGB565 format,FSCRT_BITMAPFORMAT_32BPP_RGBA,FSCRT_BITMAPFORMAT_32BPP_RGBx and FSCRT_BITMAPFORMAT_24BPP_RGB.<br> 
 *			::FSCRT_ERRCODE_ERROR if fail to set a bitmap handle for signature visual displaying cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Signature_SetBitmap(FSPDF_SIGNATURE sig, FSCRT_BITMAP bitmap);

/**
 * @brief	Set an image to icon in signature display.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	image		Pointer to a <b>FSCRT_IMAGE</b> handle which specifies the icon of signature for visual display.<br>
 *							This object cannot be released until funcion ::FSPDF_Signature_ResetAppearance has been called for this signature object.
 *							And application should call function ::FSCRT_Image_Release to release this <b>FSCRT_IMAGE</b> object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>image</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if the image type out of the supported type defined by macro definitions <b>FSCRT_IMAGETYPE_XXXX</b>.<br> 
 *			::FSCRT_ERRCODE_ERROR if fail to set an image object for signature visual displaying cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Signature_SetImage(FSPDF_SIGNATURE sig, FSCRT_IMAGE image);

/**
 * @brief	Set signature appearance flags required for resetting appearance.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	apFlags		Signature appearance state.
 *							Please refer to macro definitions <b>FSPDF_SIGNATURE_APPEARANCE_XXX</b> 
 *							and this can be one or combination of these macros
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the signature appearance required display appearance cannot be set because of any other reason.<br>
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
FS_RESULT	FSPDF_Signature_SetAppearanceFlags(FSPDF_SIGNATURE sig, FS_DWORD apFlags);

/**
 * @brief	Set a certificate chain into a signature dictionary.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	certChain	Pointer to a ::FSCRT_BSTR structure of array to specify the cert chain.
 * @param[in]	certCount	Size of certificate chain array.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>certChain</i> is <b>NULL</b>, or <i>certCount</i> is less than or equal to 0.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the certificate signed by the chain cannot be set because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	When the signature sub filter is adbe.x509.rsa_sha1,users need to call this interface to set the cert chain into Foxit PDF SDK.
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
FS_RESULT	FSPDF_Signature_SetCertChain(FSPDF_SIGNATURE sig, const FSCRT_BSTR* certChain, FS_INT32 certCount);

/**
 * @brief	Clear signature data and its appearance.
 *	
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * 
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if signed data of a signature field cannot be cleared because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	The function is called to clear signed signature data and appearance.
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
FS_RESULT 	FSPDF_Signature_ClearData(FSPDF_SIGNATURE sig); 

/*******************************************************************************/
/* Sign                                                                        */
/*******************************************************************************/
/**
 * @brief	Set the default length of signature value.
 * 
 * @note	When initializing the signature field, the length of signature will be decided by the default setting, then it's value would be initialized.
 *			The default value of content length is 8196. User may call this function to change the default setting if necessary. If this function is called after
 *			::FSPDF_Signature_InitValue will cause some unexpected error.
 *
 * @param[in]	sig					Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	contentsLength		The length of the signature value, in bytes. It shouldn't be less than 8196, if it is, then SDK would set the length to 8196.
 *									It should be a even number.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
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
FS_RESULT	FSPDF_Signature_SetDefaultContentsLength(FSPDF_SIGNATURE sig, FS_DWORD contentsLength);

/**
 * @brief	Initialize a signature field.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if a signature field cannot be initiated because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This function should be used for a newly added signature returned by function ::FSPDF_Signature_Add returns successfully.
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
FS_RESULT 	FSPDF_Signature_InitValue(FSPDF_SIGNATURE sig);

/**
 * @brief	Sign a PDF document progressively by using a signature signing handler specyfied by its Filter and SubFilter.
 *
 * @details	It may spend a long time to sign a PDF document, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass <i>signProgress</i> to function ::FSCRT_Progress_Continue to continue verifying in steps, 
 *			and should call function ::FSCRT_Progress_Release to destroy <i>signProgress</i> object if verifying process is over.<br>
 * 
 * @param[in]	sig				Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 * @param[in]	savedFile		Handle to a <b>FSCRT_FILE</b> object.
 * @param[out]	signProgress	Pointer to a <b>FSCRT_PRGRESS</b> handle that receives the signing progressive progress handle.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>, or <i>savedFile</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if signing failed because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	The signature interface will trigger the callback to handler for custom signature processing, and save to <i>saveFile</i>.
 *			It's suggested that application do not set <b>true</b> to the entry <b>NeedAppearances</b> of the dictionary <b>AcroForm</b>,
 *			or some compatibility problems with other software will happen.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>sig</i>: this handle is short-term.</li>
 *				<li> <i>signProgress</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT 	FSPDF_Signature_StartSign(FSPDF_SIGNATURE sig, FSCRT_FILE savedFile, FSCRT_PROGRESS* signProgress);

/*******************************************************************************/
/* Reset appearance of signature                                               */
/*******************************************************************************/
/**
 * @brief	Reset the appearance of a signature field.
 *
 * @param[in]	sig			Handle to a <b>FSPDF_SIGNATURE</b> object returned by function ::FSPDF_Doc_GetSignature or ::FSPDF_Signature_Add.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or access to signature is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>sig</i>is a <b>NULL</b> pointer.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if appearance of a signature field cannot be reset appearance because of any other reason.<br>
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
FS_RESULT 	FSPDF_Signature_ResetAppearance(FSPDF_SIGNATURE sig);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFSIGNATURE */

#endif /* _FSPDF_SIGNATURE_W_H_ */

