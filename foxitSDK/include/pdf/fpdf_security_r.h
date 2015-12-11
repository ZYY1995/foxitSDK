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
 * @file	fpdf_security_r.h
 * @brief	Header file for \ref FPDFSECURITY "PDF Security" module of Foxit PDF SDK.
 * @details	This header file defines some security supports to PDF, mainly about "reading" methods.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Register and unregister five kinds of PDF decryption security handler to Foxit PDF SDK. </li>
 *			<li>2. Check password type of password encryption PDF. </li>
 *			<li>3. Password decryption of PDF. </li>
 *			<li>4. Certificate decryption of PDF. </li>
 *			<li>5. Custom decryption of PDF. </li>
 *			<li>6. Foxit DRM decryption of PDF. </li>
 *			<li>7. Extended encryption parameters dictionary support. </li>
 *			<li>8. RMS decryption of PDF, supporting Microsoft RMS. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Security Add-on</b> explicitly.
 */

#ifndef _FSPDF_SECURITY_R_H_
#define _FSPDF_SECURITY_R_H_

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
/* Base definitions for Security Module                                         */
/*                                                                              */
/* Data structure                                                               */
/********************************************************************************/
#ifndef _FSPDF_DEF_HANDLER_SECURITY_
#define _FSPDF_DEF_HANDLER_SECURITY_

/**
 * @brief	Structure for custom security handler. 
 *
 * @note	This structure holds a number of interfaces for customized security handlers.<br>
 *			Implementation of this interface is required to customize security handling. 
 *			Function ::FSPDF_Security_RegisterHandler should be called to register this handler to the Foxit PDF SDK.
 */
typedef struct _FSPDF_SECURITYHANDLER
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Caller can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/**
	 * @brief	Foxit PDF SDK calls this interface to initialize context handle of a custom handler.
	 *
	 * @param[in]	clientData		Pointer to the user-supplied data.
	 * @param[in]	file			Handle to a <b>FSCRT_FILE</b> object.<br>
	 *								To open a PDF document and decrypt contents, it's the source file object.<br>
	 *								To write a PDF document and encrypt contents, it's the destination file object.
	 * @param[in]	filter			Pointer to a ::FSCRT_BSTR structure to specify filter value.
	 * @param[in]	subFilter		Pointer to a ::FSCRT_BSTR structure to specify sub filter value.
     * @param[in]	encryptInfo		Pointer to a ::FSCRT_BSTR structure to specify encryption info data. <br>
     *								For Microsoft RMS, this should be publish license, which is Encoded Publishing License issued from server to the Content publisher.<br>
	 * @param[out]	context			A pointer specifies a context handle. Return <b>NULL</b> if fails.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*CreateContext)(FS_LPVOID clientData, FSCRT_FILE file, 
								 const FSCRT_BSTR* filter, const FSCRT_BSTR* subFilter, const FSCRT_BSTR* encryptInfo, FS_LPVOID* context);

	/**
	 * @brief	Foxit PDF SDK calls this interface to release context handle of a custom handler.
	 *
	 * @param[in]	clientData		Pointer to the user-supplied data.
	 * @param[in]	context			Pointer to context handle which is created by callback function FSPDF_SECURITYHANDLER::CreateContext.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*ReleaseContext)(FS_LPVOID clientData, FS_LPVOID context);

	/**
	 * @brief	Get permissions of user for context.
	 *
	 * @param[in]	clientData		Pointer to the user-supplied data.
	 * @param[in]	context			Pointer to context handle which is created by callback function FSPDF_SECURITYHANDLER::CreateContext.
	 * @param[in]	userPermission	Original permission settings of the document.
	 *								Please refer to macro definitions <b>FSPDF_PERMISSION_XXX</b> and this should be one or a combination of these macros.
	 * @param[out]	newPermission	A combination of permission flags. 
	 *								Please refer to macro definitions <b>FSPDF_PERMISSION_XXX</b> and this should be one or a combination of these macros.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetUserPermissions)(FS_LPVOID clientData, FS_LPVOID context, FS_DWORD userPermission, FS_DWORD* newPermission);

	/**
	 * @brief	Get identity type: owner or user. 
	 *
	 * @param[in]	clientData		Pointer to the user-supplied data.
	 * @param[in]	context			Pointer to context handle which is created by callback function FSPDF_SECURITYHANDLER::CreateContext.
	 * @param[out]	isOwner			<b>TRUE</b> if decryption of the current PDF document is done by the owner, or <b>FALSE</b> decryption is done by the user.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*IsOwner)(FS_LPVOID clientData, FS_LPVOID context, FS_BOOL* isOwner);

	/**
	 * @brief	Get cipher information including encryption algorithm and key. 
	 *
	 * @details	Foxit PDF SDK will call the function twice:
	 *			first time to get the length of the buffer, and second time to obtain the key content.
	 *			So implementation of this interface should be prepared to deal with this situation.<br>
	 *
	 * @param[in]		clientData		Pointer to the user-supplied data.
	 * @param[in]		context			Pointer to context handle which is created by callback function FSPDF_SECURITYHANDLER::CreateContext.
	 * @param[out]		cipher			Pointer to an integer that receives cipher identifier. It should be one of the followings:<br>
	 *									<ul>
	 *									<li>::FSCRT_CIPHER_RC4</li>
	 *									<li>::FSCRT_CIPHER_AES</li>
	 *									</ul>
	 * @param[out]		keyBuf			Pointer to a buffer to receive encryption key. 
	 *									If it is <b>NULL</b>, parameter <i>keyLen</i> should not be <b>NULL</b> and will be used to receive the required length of key buffer.
	 * @param[in,out]	keyLen			Pointer to a ::FS_DWORD object that receives the length (number of bytes) of key buffer, and it should not be <b>NULL</b>.
	 *									To ::FSCRT_CIPHER_RC4 cipher, this parameter is between 5 and 16.
	 *									To ::FSCRT_CIPHER_AES cipher, this parameter can be 16 or 32.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 * @note	If standard encryption and decryption is used,
	 *			callback function FSPDF_SECURITYHANDLER::GetCipherInfo must be set.
	 */
	FS_RESULT	(*GetCipherInfo)(FS_LPVOID clientData, FS_LPVOID context, FS_INT32* cipher, FS_LPVOID keyBuf, FS_DWORD* keyLen);

	/**
	 * @brief	Get the estimation size of decrypted data for a source data block.
	 *
	 * @details	If application doesn't want to do the estimation, parameter <i>decryptedSize</i> can always be set to 0 when this function returns.
	 *
	 * @param[in]	clientData		Pointer to the user-supplied data.
	 * @param[in]	context			Pointer to context handle which is created by callback function FSPDF_SECURITYHANDLER::CreateContext.
	 * @param[in]	dataSize		Size of source data which is an encrypted data block.
	 * @param[out]	decryptedSize	Estimation size of decrypted data.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetDecryptedSize)(FS_LPVOID clientData, FS_LPVOID context, FS_DWORD dataSize, FS_DWORD* decryptedSize);

	/**
	 * @brief	Start a decryptor context, for decrypting a data stream.
	 * 
	 * @param[in]	clientData		Pointer to the user-supplied data.
	 * @param[in]	context			Pointer to context handle which is created by callback function FSPDF_SECURITYHANDLER::CreateContext.
	 * @param[in]	objNum			PDF object number for the object we are decrypting.
	 * @param[in]	genNum			PDF version number for the object we are decrypting.
	 * @param[out]	decryptor		Implementation should return a pointer to internal structure of the started decryptor context.<br>
	 *								Return <b>NULL</b> for failure
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*StartDecryptor)(FS_LPVOID clientData, FS_LPVOID context, FS_INT32 objNum, FS_INT32 genNum, FS_LPVOID* decryptor);

	/**
	 * @brief	Decrypted data to the decryptor.
	 *
	 * @details	For each encrypted data buffer, Foxit PDF SDK will call this function twice:
	 *			first time to get the length of the decrypted data buffer, and second time to obtain the decrypted buffer.<br>
	 *			So implementation of this interface should be prepared to deal with this situation.
	 *
	 * @param[in]		clientData		Pointer to the user-supplied data.
	 * @param[in]		decryptor		Pointer to internal structure of the started decryptor context.
	 * @param[in]		encDataBuf		Pointer to a source (encrypted) data.
	 * @param[in]		encDataLen		Length (number of bytes) of the source data.
	 * @param[out]		decDataBuf		Pointer to a buffer which contains decrypted data.
	 *									If it is <b>NULL</b>, parameter <i>decDataLen</i> should not be <b>NULL</b> 
	 *									and will be used to receive the required length of decrypted data buffer.
	 * @param[in,out]	decDataLen		Pointer to a ::FS_DWORD object.that receives 
	 *									length (number of bytes) of the decrypted data, and it should not be <b>NULL</b>.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*DecryptData)(FS_LPVOID clientData, FS_LPVOID decryptor, 
							   FS_LPCVOID encDataBuf, FS_DWORD encDataLen, 
							   FS_LPVOID decDataBuf, FS_DWORD* decDataLen);

	/**
	 * @brief	Release internal structure of the started decryptor context.
	 *
	 * @details	This callback function is used to release the inernal handler structure, used as parameter <i>decryptor</i>.
	 *			If there's any left-over data, it should be returned in this callback function.
	 *			For the left-over data, Foxit PDF SDK will call this function twice:
	 *			first time to receive the required length of the left-over data buffer, and second time to receive the left-over data buffer.<br>
	 *			So implementation of this interface should be prepared to deal with this situation.
	 * 
	 * @param[in]		clientData		Pointer to the user-supplied data.
	 * @param[in]		decryptor		Pointer to internal structure of the created filter.
	 * @param[out]		decDataBuf		Pointer to a buffer which contains decrypted data.
	 * @param[in,out]	decDataLen		Pointer to a ::FS_DWORD object that receives 
	 *									length (number of bytes) of the decrypted data in parameter <i>decDataBuf</i>.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*FinishDecryptor)(FS_LPVOID clientData, FS_LPVOID decryptor, FS_LPVOID decDataBuf, FS_DWORD* decDataLen);

	/**
	 * @brief	Get the size of encrypted data for a source data block.
	 *
	 * @details	This callback function is always called before callback function FSPDF_SECURITYHANDLER::EncryptData is used.
	 *
	 * @param[in]	clientData		Pointer to the user-supplied data.
	 * @param[in]	context			Pointer to context handle which is created by callback function FSPDF_SECURITYHANDLER::CreateContext.
	 * @param[in]	objNum			PDF object number for the object we are encrypting.
	 * @param[in]	genNum			PDF generation number for the object we are encrypting.
	 * @param[in]	srcBuf			Pointer to a source data block.
	 * @param[in]	srcLen			The size in bytes of the source data.
	 * @param[out]	encryptedSize	Size of encrypted data. It should be equal to or be larger than the final encrypted data block.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetEncryptedSize)(FS_LPVOID clientData, FS_LPVOID context, 
									FS_INT32 objNum, FS_INT32 genNum, 
									FS_LPCVOID srcBuf, FS_DWORD srcLen, FS_DWORD* encryptedSize);

	/**
	 * @brief	Encrypt data.
	 *
	 * @details	Final encrypted data block should be output in parameter <i>dstBuf</i>.
	 *
	 * @param[in]		clientData		Pointer to the user-supplied data.
	 * @param[in]		context			Pointer to context handle which is created by callback function FSPDF_SECURITYHANDLER::CreateContext.
	 * @param[in]		objNum			PDF object number for the object being encrypted.
	 * @param[in]		genNum			PDF generation number for the object being encrypted.
	 * @param[in]		srcBuf			Pointer to a source data block.
	 * @param[in]		srcLen			The size in bytes of the source data.
	 * @param[out]		dstBuf			Pointer to a buffer that receives the encrypted data. It's should not be a <b>NULL</b> pointer. 
	 *									It should be allocated according to the size returned by callback function FSPDF_SECURITYHANDLER::GetEncryptedSize.
	 * @param[in,out]	dstLen			Pointer to a ::FS_DWORD object that receives the size in bytes of the encrypted data.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*EncryptData)(FS_LPVOID clientData, FS_LPVOID context, FS_INT32 objNum, FS_INT32 genNum, 
							   FS_LPCVOID srcBuf, FS_DWORD srcLen, FS_LPVOID dstBuf, FS_DWORD* dstLen);

} FSPDF_SECURITYHANDLER;

#endif /* _FSPDF_DEF_HANDLER_SECURITY_ */

#ifndef _FSCRT_DEF_HANDLER_SECURITY_CERT_
#define _FSCRT_DEF_HANDLER_SECURITY_CERT_

/**
 * @brief	Structure for certificate security handler. 
 *
 * @note	This is a handler and is implemented by caller.<br>
 * 			When host application wants to use certificate to do decryption, this handler should be implemented and 
 *			function ::FSPDF_Security_SetCertificateHandler should be called to set this handler to Foxit PDF SDK.
 */
typedef struct _FSPDF_SECURITYHANDLER_CERT
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Caller can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/**
	 * @brief	Get decryption key.
	 *
	 * @details	Foxit PDF SDK will call this function twice:
	 *			first to get the length of the source seed buffer, and second to obtain the source seed buffer.
	 *
	 * @param[in]		clientData		Pointer to user-defined data.
	 * @param[in]		envelopeBuf		Pointer to a buffer which is a certificate envelope.
	 * @param[in]		envelopeLen		Length of certificate envelope buffer, in bytes.
	 * @param[out]		keyBuf			Pointer to a buffer.<br>
	 *									If it's <b>NULL</b>, necessary size of seed buffer will be set to parameter <i>keyLen</i> as a result.<br>
	 *									If it's not <b>NULL</b>, it will receive the source seed buffer block.
	 * @param[in,out]	keyLen			Pointer to a ::FS_DWORD object.<br>
	 *									When this function is called, it means size of parameter <i>keyBuf</i> if <i>keyBuf</i> is not <b>NULL</b>.
	 *									When this function returns, it receives size of source seed buffer in bytes.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetDecryptionKey)(FS_LPVOID clientData, FS_LPCVOID envelopeBuf, FS_DWORD envelopeLen, FS_LPVOID keyBuf, FS_DWORD* keyLen);

}FSPDF_SECURITYHANDLER_CERT;

#endif /* _FSCRT_DEF_HANDLER_SECURITY_CERT_ */

#ifndef _FSCRT_DEF_HANDLER_SECURITY_FDRM_
#define _FSCRT_DEF_HANDLER_SECURITY_FDRM_

/**
 * @brief	Structure for Foxit DRM security handler. 
 *
 * @note	This is a handler and is implemented by caller.<br>
 * 			When host application wants to use Foxit DRM to decrypt, this handler should be implemented and
 *			function ::FSPDF_Security_SetFoxitDRMHandler should be called to set this handler to Foxit PDF SDK.
 */
typedef struct _FSPDF_SECURITYHANDLER_FDRM
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Caller can use this field to track controls.
	 */
	FS_LPVOID	clientData;

	/**
	 * @brief	Get decryption parameters.
	 *
	 * @param[in]	clientData			Pointer to user-defined data.
	 * @param[in]	file				Handle to a <b>FSCRT_FILE</b> object which is a PDF file object to be opened or decrypted.
	 * @param[in]	subFilter			Pointer to a ::FSCRT_BSTR structure  which is the sub filter of encryption.
	 * @param[out]	isOwner				Pointer to a ::FS_BOOL object that indicates to open PDF file as owner or user: 
	 *									<b>TRUE</b> means owner, or <b>FALSE</b> means user.
	 * @param[out]	userPermissions		Pointer to a ::FS_DWORD object that receives user permissions.
	 *									Please refer to macro definitions <b>FSPDF_PERMISSION_XXX</b> and this should be one or a combination of these macros.
	 * @param[out]	cipher				Pointer to a ::FS_INT32 object that receives cipher type. It should be one of the followings:<br>
	 *									<ul>
	 *									<li>::FSCRT_CIPHER_RC4, <i>file</i> is encrypted by RC4 cipher.</li>
	 *									<li>::FSCRT_CIPHER_AES, <i>file</i> is encrypted by AES cipher.</li>
	 *									</ul>
	 * @param[out]	keyLen				Pointer to a ::FS_INT32 object that specifies the key length in bytes.
	 *									To ::FSCRT_CIPHER_RC4 cipher, this parameter is between 5 and 16.
	 *									To ::FSCRT_CIPHER_AES cipher, this parameter can be 16 or 32.
	 * @param[out]	fileID				Pointer to a ::FSCRT_BSTR structure that receives file identity code. This can be empty.
	 * @param[out]	initialKey			Pointer to a ::FSCRT_BSTR structure that receives initial key value. This can be empty, but recommended strongly.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*GetDecryptionParams)(FS_LPVOID clientData, FSCRT_FILE file, const FSCRT_BSTR* subFilter, 
								   FS_BOOL* isOwner, FS_DWORD* userPermissions, FS_INT32* cipher, FS_INT32* keyLen, 
								   FSCRT_BSTR* fileID, FSCRT_BSTR* initialKey);

}FSPDF_SECURITYHANDLER_FDRM;

#endif /* _FSCRT_DEF_HANDLER_SECURITY_FDRM_ */

/********************************************************************************/
/* Security handler                                                             */
/*                                                                              */
/* Security access for opening PDF files.                                       */
/********************************************************************************/
/**
 * @brief	Register a custom security handler to Foxit PDF SDK, enabling access to a PDF document which is protected by customized security handler.
 *
 * @details	This function is only used for custom encryption and decryption, and RMS encryption and decryption (Microsoft RMS).<br>
 *			If user wants to use custom or RMS security handler, this function must be called first before doing customer encryption or decryption.<br>
 *			Once no more custom or RMS encryption or decryption is needed, function ::FSPDF_Security_UnregisterHandler shoulde be called to unregister current customer security handler.
 *
 * @param[in]	filter					Pointer to ::FSCRT_BSTR structure that specifies security filter.<br>
 *										Specially:<br>
 *										For Microsoft RMS, this should be "MicrosoftIRMServices".
 * @param[in]	securityHandler			Pointer to a valid ::FSPDF_SECURITYHANDLER structure to register a security handler.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>filter</i>, or <i>securityHandler</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or custom security is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMANAGER if Foxit PDF SDK manager is not initialized.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_HANDLER if any callback function in parameter <i>securityHandler</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 * 			::FSCRT_ERRCODE_CONFLICT if parameter <i>filter</i> collides with an existing one.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the handler cannot be registered because of any other reason.<br>
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
FS_RESULT	FSPDF_Security_RegisterHandler(const FSCRT_BSTR* filter, FSPDF_SECURITYHANDLER* securityHandler);

/** 
 * @brief	Unregister a customer security handler to Foxit PDF SDK.
 *
 * @details	This function is only used for custom encryption and decryption.
 *
 * @param[in]	filter		Pointer to ::FSCRT_BSTR structure that specifies a security filter. 
 *							It should be registered by previous call to the function ::FSPDF_Security_RegisterHandler.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>filter</i> is <b>NULL</b>.<br>	
 *			::FSCRT_ERRCODE_INVALIDMANAGER if Foxit PDF SDK manager is not initialized.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if no parameter <i>filter</i> is found.<br>
 *			::FSCRT_ERRCODE_ERROR if the handler cannot be unregistered because of any other reason.<br>
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
FS_RESULT	FSPDF_Security_UnregisterHandler(const FSCRT_BSTR* filter);

/**
 * @brief	Set certificate security handler to Foxit PDF SDK.
 *
 * @details	This function is only used for certificate decryption.<br>
 *			Certificate handler provides a method to extract decryption key from envelope.
 *
 * @param[in]	certificateHandler		Pointer to a ::FSPDF_SECURITYHANDLER_CERT structure which is a certificate handler.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>certificateHandler</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or certificate security is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMANAGER if Foxit PDF SDK manager is not initialized.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_HANDLER if any callback function in parameter <i>certificateHandler</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSPDF_Security_SetCertificateHandler(FSPDF_SECURITYHANDLER_CERT* certificateHandler);

/**
 * @brief	Set Foxit DRM security handler to Foxit PDF SDK.
 *
 * @details	This function is only used for Foxit DRM decryption.<br>
 *			Foxit DRM handler provides a method to extract decryption parameters of Foxit DRM.
 *
 * @param[in]	foxitDRMHandler		Pointer to a ::FSPDF_SECURITYHANDLER_FDRM structure which is a Foxit DRM handler.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>foxitDRMHandler</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or Foxit DRM security is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDMANAGER if Foxit PDF SDK manager is not initialized.<br>
 *			::FSCRT_ERRCODE_INVALIDMODULE if PDF module is not initialized.<br>
 *			::FSCRT_ERRCODE_HANDLER if any callback function in parameter <i>foxitDRMHandler</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSPDF_Security_SetFoxitDRMHandler(FSPDF_SECURITYHANDLER_FDRM* foxitDRMHandler);

/**
 * @brief	Detect type of password.
 *
 * @details	This function is only used for standard password decryption.
 *
 * @param[in]	document			Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	password			Pointer to a ::FSCRT_BSTR structure that specifies the byte string password.
 * @param[out]	passwordType		Pointer to a ::FS_INT32 object that receives the password type.
 *									It should be one of the followings:<br>
 *									<ul>
 *									<li>::FSPDF_PASSWORDTYPE_INVALID</li>
 *									<li>::FSPDF_PASSWORDTYPE_NOPASSWORD</li>
 *									<li>::FSPDF_PASSWORDTYPE_USERPASSWORD</li>
 *									<li>::FSPDF_PASSWORDTYPE_OWNERPASSWORD</li>
 *									</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>password</i>, or <i>passwordType</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a type of PDF document.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if the password cannot be checked because of any other reason.<br>
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
FS_RESULT	FSPDF_Security_CheckPassword(FSCRT_DOCUMENT document, const FSCRT_BSTR* password, FS_INT32* passwordType);

/********************************************************************************/
/* Foxit DRM																	*/
/********************************************************************************/
/**
 * @brief	Verify encryption parameters in a PDF document.
 *
 * @details	Foxit DRM maintains a set of encryption parameters for application purpose.
 *			Encryption parameters are stored in PDF file and protected by verification algorithm.
 *			So application should call this function to verify the current PDF document. 
 *			If verification is failed, the document might be distorted.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[out]	verified	Pointer to a ::FS_BOOL object that receives verification result:<br>
 *							<b>TRUE</b> for success, or <b>FALSE</b> for failure.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i> or <i>verified</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or Foxit DRM security is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a type of PDF document, or <i>document</i> is not a Foxit DRM encrypted one.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if cannot verify document because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Do not use this function for a non-Foxit DRM encrypted file.<br>
 *			Call function ::FSPDF_Doc_GetEncryptionType to determine if a PDF document is encrypted by Foxit DRM.
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
FS_RESULT	FSPDF_Security_VerifyFoxitDRMEncryptionParams(FSCRT_DOCUMENT document, FS_BOOL* verified);

/**
 * @brief	Get string value of a key from encryption parameters used for Foxit DRM security.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object.
 * @param[in]	key			Pointer to a ::FSCRT_BSTR structure to the key string specified which is to get. Caller can define private key name.<br>
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
 * @param[out]	str			Pointer to a ::FSCRT_BSTR structure that receives the string data. 
 *							User should call function ::FSCRT_BStr_Clear to free the memory if necessary.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, <i>key</i>, or <i>str</i> is <b>NULL</b>, or <i>str</i> is an empty string object.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or Foxit DRM security is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a type of PDF document, or <i>document</i> is not a Foxit DRM encrypted one.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if string value cannot be obtained because of any other reason.<br>
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
FS_RESULT	FSPDF_Security_GetFoxitDRMEncryptionParamValue(FSCRT_DOCUMENT document, const FSCRT_BSTR* key, FSCRT_BSTR* str);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFSECURITY */

#endif /* _FSPDF_SECURITY_R_H_ */

