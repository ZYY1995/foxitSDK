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
 * @file	fpdf_security_w.h
 * @brief	Header file for \ref FPDFSECURITY "PDF Security" module of Foxit PDF SDK.
 * @details	This header file defines some security supports to PDF, mainly about "writing" methods.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Password encryption of PDF. </li>
 *			<li>2. Certificate encryption of PDF. </li>
 *			<li>3. Custom encryption of PDF. </li>
 *			<li>4. Foxit DRM encryption of PDF. </li>
 *			<li>5. Extended encryption parameters dictionary support. </li>
 *			<li>6. RMS encryption of PDF, supporting Microsoft RMS. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Security Add-on</b> explicitly.
 */

#ifndef _FSPDF_SECURITY_W_H_
#define _FSPDF_SECURITY_W_H_

/** 
 * @defgroup	FPDFSECURITY PDF Security
 * @brief		Definitions for pdf security related operation.<br>
 *				Definitions and functions in this module are included in fpdf_security_r.h and fpdf_security_w.h.<br>
 *				Module: PDFSecurity<br>
 *				License Identifier: PDFSecurity/All<br>
 *				Available License Right: Reading/Writing.<br>
 *				For License Right <b>Reading</b>, see fpdf_security_r.h.<br>
 *				For License Right <b>Writing</b>, see fpdf_security_w.h.<br>
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. Password security:
 *					<ul>
 *					<li>a. Encrypt a PDF file by standard password encryption algorithm.</li>
 *					<li>b. PDF reference defines a standard password encryption algorithm.
 *						   Function ::FSPDF_Security_StartPasswordEncryption is used to do password encryption, it provides a progressive process.
 *						   To open a password-encrypted PDF file, pass password as parameter directly when call function ::FSPDF_Doc_StartLoad or ::FSPDF_Doc_StartReLoad.</li>
 *					<li>c. </li>
 *					<li>d. Reference: section 3.5.2 in PDF Reference 1.7 describes standard password encryption.</li>
 *					</ul>
 *				</li>
 *				<li>2. Customized security:
 *					<ul>
 *					<li>a. Register or unregister a customized security handler, encrypt a PDF file by using customized encryption algorithm.</li>
 *					<li>b. Customized security handler is an extension according to PDF reference.
 *						   To encrypt a PDF file, call function ::FSPDF_Security_StartCustomEncryption in a progressive process.
 *						   To open customized encryption PDF files, user should call function ::FSPDF_Security_RegisterHandler
 *						   to register the corresponding security handler at first.</li>
 *					<li>c. Note: customized security is not a common solution, but it's very effective in most cases.
 *						   Implementors should ensure thread safety in ::FSPDF_SECURITYHANDLER. </li>
 *					<li>d. Reference: section 3.5 in PDF Reference 1.7 describes the definition of security handler.</li>
 *					</ul>
 *				</li>
 *				<li>3. Certificate security:
 *					<ul>
 *					<li>a. Set certificate security handler, encrypt a PDF file by using public-key technologies.</li>
 *					<li>b. Certificate security handler uses the industry standard Public Key Cryptographic Standard Number 7 (PKCS#7)
 *						   to encode recipient list, decryption key, and access permission information.
 *						   In PDF, use X.509 public key certificate to represent a recipient.</li>
 *					<li>c. Note: ::FSPDF_SECURITYHANDLER_CERT is used to open X.509 certificate and implementors should ensure thread safety.</li>
 *					<li>d. Reference: section 3.5.3 in PDF Reference 1.7 describes technologies on certificate security.</li>
 *					</ul>
 *				</li>
 *				<li>4. Foxit DRM:
 *					<ul>
 *					<li>a. Set Foxit DRM security handler, verify encryption parameters in Foxit DRM files, get or set parameter values, and encrypt a PDF file by Foxit DRM. </li>
 *					<li>b. Foxit DRM is a corporation-level standard security technologies. It provides more flexible security solutions.
 *						   To open a PDF file encrypted by Foxit DRM, call function ::FSPDF_Security_VerifyFoxitDRMEncryptionParams
 *						   to check whether the encryption parameters are valid or not.
 *						   Call function ::FSPDF_Security_StartFoxitDRMEncryption to encrypt a Foxit DRM PDF file in a progressive process.</li>
 *					</ul>
 *				</li>
 *				<li>5. RMS security:
 *					<ul>
 *					<li>a. Register or unregister a RMS security handler, encrypt a PDF file by using RMS encryption algorithm.</li>
 *					<li>b. RMS security handler is a special custom security handler, which is implemented by application, using AD RMS SDK.
 *						   Before doing RMS encryption or decryption, function ::FSPDF_Security_RegisterHandler should be called first
 *						   to register the corresponding security handler with specific filter.
 *						   To encrypt a PDF file, call function ::FSPDF_Security_StartRMSEncryption
 *						   in a progressive process.</li>
 *					<li>c. Note: RMS encryption and decryption algorithm is usually based on AD RMS SDK, which should be implemented by application.
 *						   Implementors should ensure thread safety in ::FSPDF_SECURITYHANDLER. </li>
 *					<li>d. Reference: section 3.5 in PDF Reference 1.7 describes the definition of security handler,
 *						   and relative specifications about Microsoft RMS.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************/
/* Encryption                                                                   */
/********************************************************************************/
/**
 * @brief	Start standard password encryption on a PDF document.
 *
 * @details	It will take a long time to encrypt a document with complex or large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 *			Caller should pass parameter <i>encryptProgress</i> to function ::FSCRT_Progress_Continue to continue encrypting in steps, 
 *			and should call function ::FSCRT_Progress_Release to destroy <i>encryptProgress</i> object if encrypting process is done.
 *			If caller wants to change the saved PDF file version, call function ::FSCRT_Progress_SetProperty to set <b>"fileversion"</b>.
 *
 * @param[in]	document			Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	userPermissions		Permission flags. Please refer to macro definitions <b>FSPDF_PERMISSION_XXX</b> and this should be one or a combination of these macros.
 * @param[in]	userPassword		Pointer to a ::FSCRT_BSTR structure that the user password, which could be set to <b>NULL</b>.
 * @param[in]	ownerPassword		Pointer to a ::FSCRT_BSTR structure that the owner password, which could be set to <b>NULL</b>.
 * @param[in]	cipher				The type of encryption algorithm. It should be one of the followings: <br>
 *									<ul>
 *									<li>::FSCRT_CIPHER_AES</li>
 *									<li>::FSCRT_CIPHER_RC4</li>
 *									</ul>
 * @param[in]	keyLen				Key length of parameter <i>cipher</i>, in bytes.<br>
 *									For ::FSCRT_CIPHER_AES, this can only be 16 or 32.<br>
 *									For ::FSCRT_CIPHER_RC4, this should be between 5 and 16.<br>
 * @param[in]	encryptMetadata		Whether to encrypt the metadata or not. <br>
 *									This must be <b>TRUE</b> if <i>cipher</i> is ::FSCRT_CIPHER_RC4 and <i>keyLen</i> is 5.
 * @param[in]	encryptedFile		Handle to a <b>FSCRT_FILE</b> object used to save encrypted PDF file.
 * @param[in]	flag				An integer value to specify saving mode. <br>
 *									Please refer to macro definitions <b>FSPDF_SAVEFLAG_XXX</b> and this should be one or a combination of these macros 
 *									except ::FSPDF_SAVEFLAG_REMOVESECURITY and ::FSPDF_SAVEFLAG_INCREMENTONLY.
 * @param[out]	encryptProgress		Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>encryptedFile</i>, or <i>encryptProgress</i> is <b>NULL</b>, 
 *			or parameter <i>flag</i> is invalid, or any other parameter is unexpected.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or standard password security is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a type of PDF document.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>cipher</i> is not applicable.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if document cannot be encrypted because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	Parameter <i>encryptedFile</i> should have <b>WRITE</b> callback functions implemented in structure ::FSCRT_FILEHANDLER.<br>
 *			If data cannot be written into parameter <i>encryptedFile</i>, ::FSCRT_ERRCODE_ERROR will return on calling function ::FSCRT_Progress_Continue during the next steps.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>encryptedFile</i>: this handle is long-term recoverable.</li>
 *				<li> <i>encryptProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Security_StartPasswordEncryption(FSCRT_DOCUMENT document, FS_DWORD userPermissions,
												   const FSCRT_BSTR* userPassword, const FSCRT_BSTR* ownerPassword, 
												   FS_INT32 cipher, FS_INT32 keyLen,
												   FS_BOOL encryptMetadata, FSCRT_FILE encryptedFile, FS_INT32 flag, FSCRT_PROGRESS* encryptProgress);

/**
 * @brief	Start custom PDF Encryption, and the PDF document will be protected by non-standard security handler.
 *
 * @details	It will take a long time to encrypt a document with complex or large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 *			Caller should pass parameter <i>encryptProgress</i> to function ::FSCRT_Progress_Continue to continue encrypting in steps, 
 *			call function ::FSCRT_Progress_Release to destroy <i>encryptProgress</i> object if encrypting process is done.
 *			If caller wants to change the saved PDF file version, call function ::FSCRT_Progress_SetProperty to set <b>"fileversion"</b>.
 *
 * @param[in]	document			Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	filter				Pointer to a ::FSCRT_BSTR structure to specify the filter of the custom security handler.
 * @param[in]	subFilter			Pointer to a ::FSCRT_BSTR structure to specify the subfilter of the custom security handler.
 * @param[in]	encryptInfo			Pointer to a ::FSCRT_BSTR structure to specify encryption information data.
 * @param[in]	securityHandler		Pointer to a ::FSPDF_SECURITYHANDLER structure which represents a custom security handler to update default appearance.
 * @param[in]	encryptMetadata		A boolean used to indicates whether to encrypt the meta data or not.
 * @param[in]	encryptedFile		Handle to a <b>FSCRT_FILE</b> object used to save encrypted PDF file.
 * @param[in]	flag				An integer value to specify saving mode. <br>
 *									Please refer to macro definitions <b>FSPDF_SAVEFLAG_XXX</b> and this should be one or a combination of these macros 
 *									except ::FSPDF_SAVEFLAG_REMOVESECURITY and ::FSPDF_SAVEFLAG_INCREMENTONLY.
 * @param[out]	encryptProgress		Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>filter</i>, <i>encryptedFile</i>, or <i>encryptProgress</i> is <b>NULL</b>, 
 *			or parameter <i>flag</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or custom security is not allowed.<br>
 *			::FSCRT_ERRCODE_HANDLER if parameter <i>securityHandler</i> is invalid
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a type of PDF document.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if document cannot be encrypted because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Parameter<i>encryptedFile</i> should have <b>WRITE</b> callback functions implemented in structure ::FSCRT_FILEHANDLER.<br>
 *			If data cannot be written into parameter <i>encryptedFile</i>, ::FSCRT_ERRCODE_ERROR will return on calling function ::FSCRT_Progress_Continue during the next steps.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>encryptedFile</i>: this handle is long-term recoverable.</li>
 *				<li> <i>encryptProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Security_StartCustomEncryption(FSCRT_DOCUMENT document,
												 const FSCRT_BSTR* filter, const FSCRT_BSTR* subFilter, const FSCRT_BSTR* encryptInfo, 
												 FSPDF_SECURITYHANDLER* securityHandler,
												 FS_BOOL encryptMetadata, FSCRT_FILE encryptedFile, FS_INT32 flag, FSCRT_PROGRESS* encryptProgress);

/**
 * @brief	Encrypt the PDF document by certificate. 
 *
 * @details	It will take a long time to encrypt a document with complex or large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 *			Caller should pass parameter <i>encryptProgress</i> to function ::FSCRT_Progress_Continue to continue encrypting in steps, 
 *			and should call function ::FSCRT_Progress_Release to destroy parameter <i>encryptProgress</i> object if encrypting process is over.
 *			If caller wants to change the saved PDF file version, call function ::FSCRT_Progress_SetProperty to set <b>"fileversion"</b>.
 *
 * @param[in]	document			Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	envelopes			Pointer to ::FSCRT_BSTR structure that specifies a certificate enveloper array.
 * @param[in]	count				The count of envelopes. This should be greater than zero.
 * @param[in]	cipher				Encryption algorithm. It should be one of the followings: <br>
 *									<ul>
 *									<li>::FSCRT_CIPHER_AES</li>
 *									<li>::FSCRT_CIPHER_RC4</li>
 *									</ul>
 * @param[in]	encryptKey			Pointer to ::FSCRT_BSTR structure that specifies the key information to be got after envelops calculate.
 *									For ::FSCRT_CIPHER_AES, length of parameter <i>encryptKey</i> can only be 16 or 32.
 *									For ::FSCRT_CIPHER_RC4, length of parameter <i>encryptKey</i> should be in the range from 5 to 16, including 5 and 16.
 * @param[in]	encryptMetadata		A boolean used to indicates whether to encrypt the meta data or not.
 * @param[in]	encryptedFile		Handle to a <b>FSCRT_FILE</b> object used to save encrypted PDF file.
 * @param[in]	flag				An integer value to specify saving mode. <br>
 *									Please refer to macro definitions <b>FSPDF_SAVEFLAG_XXX</b> and this should be one or a combination of these macros 
 *									except ::FSPDF_SAVEFLAG_REMOVESECURITY and ::FSPDF_SAVEFLAG_INCREMENTONLY.
 * @param[out]	encryptProgress		Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if any of five parameters <i>document</i>, <i>envelopes</i> , <i>encryptKey</i>, <i>encryptedFile</i>, and <i>encryptProgress</i> is <b>NULL</b>, 
 *			or parameter <i>count</i> is below 1 when parameter <i>envelopes</i> is valid, 
 *			or parameter <i>flag</i> is invalid, or any other parameter is unexpected.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or certificate security is not allowed.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a type of PDF document.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>cipher</i> is not applicable.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if document cannot be encrypted because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.	
 *
 * @note	Parameter<i>encryptedFile</i> should have <b>WRITE</b> callback functions implemented in structure ::FSCRT_FILEHANDLER.<br>
 *			If data cannot be written into parameter <i>encryptedFile</i>, ::FSCRT_ERRCODE_ERROR will return on calling function ::FSCRT_Progress_Continue during the next steps.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>encryptedFile</i>: this handle is long-term recoverable.</li>
 *				<li> <i>encryptProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Security_StartCertificateEncryption(FSCRT_DOCUMENT document, 
													  const FSCRT_BSTR* envelopes, FS_INT32 count, FS_INT32 cipher, const FSCRT_BSTR* encryptKey,
													  FS_BOOL encryptMetadata, FSCRT_FILE encryptedFile, FS_INT32 flag, FSCRT_PROGRESS* encryptProgress);

/**
 * @brief	Set string value of a key as encryption parameter for Foxit DRM encryption.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	key			Pointer to a ::FSCRT_BSTR structure to the key string specified which is to set. Caller can define private key name.<br>
 *							The following are pre-defined key names:<br>
 *							<ul>
 *							<li>Issuer: issuer name.</li>
 *							<li>Creator: creator of this file.</li>
 *							<li>FileID: file ID.</li>
 *							<li>FlowCode: flow code for application control.</li>
 *							<li>Order: order number.</li>
 *							<li>User: user name.</li>
 *							<li>ServiceURL: service URL for remote server.</li>
 *							<li>Vender: vender name.</li>
 *							</ul>
 * @param[in]	str			Pointer to a ::FSCRT_BSTR structure which is the key string value. 
 *							If <i>str</i> is <b>NULL</b>, <i>key</i> will be removed.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, or <i>key</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or Foxit DRM security is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a type of PDF document.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Security_SetFoxitDRMEncryptionParamValue(FSCRT_DOCUMENT document, const FSCRT_BSTR* key, const FSCRT_BSTR* str);

/** 
 * @brief	Start PDF document encryption by using Foxit DRM.
 *
 * @details	It will take a long time to encrypt a document with complex or large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 *			Caller should pass <i>encryptProgress</i> to function ::FSCRT_Progress_Continue to continue saving in steps, and should call function ::FSCRT_Progress_Release to destroy <i>encryptProgress</i> object if saving process is done.
 *			If caller wants to change the saved PDF file version, it can call function ::FSCRT_Progress_SetProperty to set <b>"fileversion"</b>.
 *
 * @param[in]	document			Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	subFilter			Pointer to a ::FSCRT_BSTR structure to specify a subfilter.
 * @param[in]	isOwner				A boolean used to indicate to encrypt PDF file as owner or user: <br>
 *									<b>TRUE</b> means owner, or <b>FALSE</b> means user.
 * @param[in]	userPermissions		User permission flags which is used to encrypt PDF document.
 *									Please refer to macro definitions <b>FSPDF_PERMISSION_XXX</b> and this should be one or a combination of these macros.
 * @param[in]	cipher				Encryption algorithm. It should be one of the followings: <br>
 *									<ul>
 *									<li>::FSCRT_CIPHER_AES</li>
 *									<li>::FSCRT_CIPHER_RC4</li>
 *									</ul>
 * @param[in]	keyLen				Length of encryption algorithm, in bytes.<br>
 *									For ::FSCRT_CIPHER_AES, this can be 16 or 32.<br>
 *									For ::FSCRT_CIPHER_RC4, this should be in the range from 5 to 16, including 5 and 16.
 * @param[in]	fileID				Pointer to a ::FSCRT_BSTR structure that specifies file identity code. This can be empty but its usage is highly recommended.
 * @param[in]	initialKey			Pointer to a ::FSCRT_BSTR structure which is an initial key data. This can be empty but its usage is highly recommended.
 * @param[in]	encryptMetadata		Indicates whether encrypt metadata or not.
 * @param[in]	encryptedFile		Handle to a <b>FSCRT_FILE</b> object used to save encrypted PDF file.
 * @param[in]	flag				An integer value to specify saving mode. <br>
 *									Please refer to macro definitions <b>FSPDF_SAVEFLAG_XXX</b> and this should be one or a combination of these macros 
 *									except ::FSPDF_SAVEFLAG_REMOVESECURITY and ::FSPDF_SAVEFLAG_INCREMENTONLY.
 * @param[out]	encryptProgress		Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>subFilter</i>, <i>encryptedFile</i>, or <i>encryptProgress</i> is <b>NULL</b>, 
 *			or parameter <i>cipher</i> or <i>flag</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or Foxit DRM security is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a type of PDF document.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>cipher</i> or <i>keyBytes</i> is not applicable.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if document cannot be encrypted because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 * 
 * @note	Parameter <i>encryptedFile</i> should have <b>WRITE</b> callback functions implemented in structure ::FSCRT_FILEHANDLER.<br>
 *			If data cannot be written into parameter <i>encryptedFile</i>, ::FSCRT_ERRCODE_ERROR will return on calling function ::FSCRT_Progress_Continue during the next steps.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>encryptedFile</i>: this handle is long-term recoverable.</li>
 *				<li> <i>encryptProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Security_StartFoxitDRMEncryption(FSCRT_DOCUMENT document, const FSCRT_BSTR* subFilter, FS_BOOL isOwner, FS_DWORD userPermissions,
												   FS_INT32 cipher, FS_INT32 keyLen, const FSCRT_BSTR* fileID, const FSCRT_BSTR* initialKey,
												   FS_BOOL encryptMetadata, FSCRT_FILE encryptedFile, FS_INT32 flag, FSCRT_PROGRESS* encryptProgress);

/**
 * @brief	Start PDF document encryption by using Microsoft RMS.
 *
 * @details	In order to do Microsoft RMS encryption and decryption, applictaion should implement a ::FSPDF_SECURITYHANDLER structure first,
 *			and call function ::FSPDF_Security_RegisterHandler to register this handler with specific filter "MicrosoftIRMServices".
 *			Then application can call this function to do Microsoft RMS encryption to a PDF file,
 *			or call function ::FSPDF_Doc_StartLoad to load a PDF file encrypted by Microsoft RMS.
 *			Application should remember to call function ::FSPDF_Security_UnregisterHandler when no need to use Microsoft RMS encryption and decryption.
 *
 * @param[in]	document			Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	publishLicense		Pointer to a ::FSCRT_BSTR structure that specifies Encoded Publishing License issued from server to the Content publisher.<br>
 *									This field contains the publishing license from Microsoft IRM services or a comparable IRM service.
 *									The original data of Publishing License should be compressed by Flate compression algorithm at first,
 *									and then encoded by Base-64 Encryption algorithm.
 * @param[in]	serverEulList		Pointer to a ::FSCRT_BSTR structure specifies a string array. <b>NULL</b> means no use.<br>
 *									In this array, 2 strings are in a pair, and each pair represents content of a dictionary object which is encoded Server EUL.<br>
 *									For each pair, the first string is ServerID, and the second one is ServerEUL.
 *									The original data of Server ID and Server EUL should be compressed by Flate compression algorithm at first,
 *									and then encoded by Base-64 Encryption algorithm.
 * @param[in]	listCount			Count of elements in array <i>serverEulList</i>. This should be multiply of 2.<br>
 *									This is useful only when if parameter <i>serverEulList</i> is valid.
 * @param[in]	irmVersion			Microsoft IRM version. Default: 1.
 * @param[in]	encryptMetadata		A boolean used to indicate whether to encrypt the meta data or not.
 * @param[in]	encryptedFile		Handle to a <b>FSCRT_FILE</b> object used to save encrypted PDF file.
 * @param[in]	flag				An integer value to specify saving mode. <br>
 *									Please refer to macro definitions <b>FSPDF_SAVEFLAG_XXX</b> and this should be one of these macros 
 *									except ::FSPDF_SAVEFLAG_REMOVESECURITY and ::FSPDF_SAVEFLAG_INCREMENTONLY.
 * @param[out]	encryptProgress		Handle to a <b>FSCRT_PROGRESS</b> object used to continue the encryption progress.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>encryptedFile</i>, or <i>encryptProgress</i> is <b>NULL</b>,
 *			or parameter <i>publishLicense</i> is <b>NULL</b> or empty,
 *			or parameter <i>listCount</i> is below 2 or not a multiply of 2 when parameter <i>serverEulList</i> is valid,
 *			or parameter <i>flag</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or Microsoft RMS security is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a type of PDF document.<br>
 *			::FSCRT_ERRCODE_UNKNOWNSECURITYHANDLER if valid security handler used for Microsoft RMS cannot be found.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if document cannot be encrypted because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>encryptedFile</i>: this handle is long-term recoverable.</li>
 *				<li> <i>encryptProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Security_StartRMSEncryption(FSCRT_DOCUMENT document,
                                              const FSCRT_BSTR* publishLicense, const FSCRT_BSTR* serverEulList, FS_INT32 listCount, FS_INT32 irmVersion,
                                              FS_BOOL encryptMetadata, FSCRT_FILE encryptedFile, FS_INT32 flag, FSCRT_PROGRESS* encryptProgress);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFSECURITY */

#endif /* _FSPDF_SECURITY_W_H_ */

