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
 * @file	fpdf_form_w.h
 * @brief	Header file for \ref FPDFFORM "PDF Form" module of Foxit PDF SDK.
 * @details	This header file defines PDF form supports.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Export and import FDF files. </li>
 *			<li>2. Set trigger actions of form field. </li>
 *			<li>3. Set properties of form field. </li>
 *			<li>4. Set form controls. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Form Add-on</b> explicitly.
 */

#ifndef _FSPDF_FORM_W_H_
#define _FSPDF_FORM_W_H_

/**
 * @defgroup	FPDFFORM PDF Form
 * @brief		Definitions for access to PDF form.<br>
 *				Definitions and functions in this module are included in fpdf_form_r.h and fpdf_form_w.h.<br>
 *				Module: PDFForm<br>
 *				License Identifier: PDFForm/All<br>
 *				Available License Right: Reading/Writing<br>
 *				For License Right <b>Reading</b>, see fpdf_form_r.h.<br>
 *				For License Right <b>Writing</b>, see fpdf_form_w.h.<br>
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. PDF form:
 *					<ul>
 *					<li>a. Load PDF form, enumerate form fields for form controls, export or import FDF data, get or set properties of PDF form.</li>
 *					<li>b. PDF form is static form which consists of form field. Form fields contains one or more form controls.
 *						   In PDF reference, form control is called as widget, which is a type of annotation.
 *						   Form fields contain value data, and form controls provide appearances of form fields.
 *						   Form controls are used to provide interactions. </li>
 *					<li>c. Note: at present, Foxit PDF SDK provides only data-level access to PDF form.</li>
 *					<li>d. Reference: section 8.6 in PDF Reference 1.7 describes full information of PDF form.</li>
 *					</ul>
 *				</li>
 *				<li>2. Trigger actions:
 *					<ul>
 *					<li>a. Enumerate trigger actions of form field, modify or remove trigger actions.</li>
 *					<li>b. Note: Foxit PDF SDK doesn't contain functions to execute actions. In a viewer or reader, action should be executed by application.</li>
 *					<li>c. Reference: section 8.5.2 in PDF Reference 1.7 describes trigger actions,
 *						   and section 8.6.4 describes more trigger actions of form fields.</li>
 *					</ul>
 *				</li>
 *				<li>3. Form fields:
 *					<ul>
 *					<li>a. Get or set properties of form fields, and enumerate form controls to a form field.</li>
 *					<li>b. Different types of form fields consist of different properties.</li>
 *					<li>c. Reference: section 8.6.3 describes the properties of form fields.</li>
 *					</ul>
 *				</li>
 *				<li>4. Form controls:
 *					<ul>
 *					<li>a. Get or set export value, get or set checking state, and render form controls.</li>
 *					<li>b. Form controls can be accessed as widget annotations.
 *						   Caller can call functions defined in /ref FPDFANNOT "PDF Annotation" module to access common properties of form controls.</li>
 *					<li>c. Reference: section 8.4.5 describes the properties of widgets.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************/
/* Form                                                                        */
/*******************************************************************************/
/**
 * @brief	Create an arco form.
 *
 * @details	If a PDF document already has an arco form, this function will return the existed acro form object directly -- same as function ::FSPDF_Form_Load.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[out]	form		Pointer to a <b>FSPDF_FORM</b> handle that receives a form object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, or <i>form</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to PDF form is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a type of PDF document.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term recoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_CreateForm(FSCRT_DOCUMENT document, FSPDF_FORM* form);

/**
 * @brief	Export data in a form to a FDF document.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a FDF document object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>fdfDoc</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>fdfDoc</i> is not a type of FDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to PDF form is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>fdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_ExportToFDFDoc(FSPDF_FORM form, FSCRT_DOCUMENT fdfDoc);

/**
 * @brief	Import data in FDF document to fill a form.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a FDF document object.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>fdfDoc</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>fdfDoc</i> is not a type of FDF document.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to PDF form is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>fdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_ImportFromFDFDoc(FSPDF_FORM form, FSCRT_DOCUMENT fdfDoc);

/**
 * @brief	Export the form data to a XML file.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	xmlFile		Handle to a <b>FSCRT_FILE</b> object, to which form data is to be exported.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>xmlFile</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to PDF form is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to export a XML file because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term partially recoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>xmlFile</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_ExportToXML(FSPDF_FORM form, FSCRT_FILE xmlFile);

/**
 * @brief	Import the form data from a XML file.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	xmlFile		Handle to a <b>FSCRT_FILE</b> object, from which form data is to be imported.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>xmlFile</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to PDF form is not allowed.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if failing to import a XML file because of any other reason.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term partially recoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>xmlFile</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_ImportFromXML(FSPDF_FORM form, FSCRT_FILE xmlFile);

/**
 * @brief	Reset data in fields to their default value.
 *
 * @param[in]	form				Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldNames			Pointer to a ::FSCRT_BSTR structure array, whose elements are field names to include or exclude.
 * @param[in]	count				Array length of parameter <i>fieldNames</i>.
 * @param[in]	bInclude			A ::FS_BOOL that specifies whether to include the fields in the resetting. <b>TRUE</b> if include, <b>FALSE</b> if exclude.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	If parameter <i>fieldNames</i> is <b>NULL</b> or <i>count</i> is invalid. The function will reset whole form according to parameter <i>includeOrExclude</i> value.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_Reset(FSPDF_FORM form, const FSCRT_BSTR* fieldNames, FS_INT32 count, FS_BOOL bInclude);

/**
 * @brief	Set default appearance of a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	defAppearance	Pointer to a ::FSPDF_DEFAULTAPPEARANCE structure to update the default appearance.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>defAppearance</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_SetDefaultAppearance(FSPDF_FORM form, const FSPDF_DEFAULTAPPEARANCE* defAppearance);

/**
 * @brief	Set alignment property of a form, as a document-wide default value.
 *
 * @details	Alignment is a property of variable text. And it's only useful for text field and list box, 
 *			which may contain variable text as their content.<br>
 *			If a specific text field or list box has its own alignment value, the document-wide default one will be ignored; 
 *			otherwise, the document-wide default one will be used for the specific text field or list box.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	alignment		The new default alignment type of variable text. It should be one of the following: <br>
 *								<ul>
 *								<li>::FSPDF_ALIGNMENT_LEFT</li>
 *								<li>::FSPDF_ALIGNMENT_CENTER</li>
 *								<li>::FSPDF_ALIGNMENT_RIGHT</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_SetAlignment(FSPDF_FORM form, FS_INT32 alignment);

/**
 * @brief	Set a flag that specifies whether to construct appearances when loading form controls.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	needConstruct	A ::FS_BOOL that specifies whether to construct appearances when loading form controls. <b>TRUE</b> if need, <b>FALSE</b> if not.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_SetConstructAppearancesFlag(FSPDF_FORM form, FS_BOOL needConstruct);

/**
 * @brief	Rename a field to a new name.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure that specifies the field to rename.
 * @param[in]	newFieldName	Pointer to a ::FSCRT_BSTR structure that represents the name to check.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i> or <i>newFieldName</i> is a <b>NULL</b> pointer, or <i>fieldName</i> or <i>newFieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no parameter <i>fieldName</i> is found.<br>
 * 			::FSCRT_ERRCODE_CONFLICT if parameter <i>newFieldName</i> is same with an existing form field 
 *			and the type of existing form field is different from the one specified by <i>fieldName</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	It will change the field's index to rename a form field.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_RenameField(FSPDF_FORM form, const FSCRT_BSTR* fieldName, const FSCRT_BSTR* newFieldName);

/**
 * @brief	Set calculation order in a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldNames		Pointer to a ::FSCRT_BSTR structure which represents an array consisting of the field names to form a new calculation order.
 * @param[in]	count			The length of <i>fieldNames</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>fieldNames</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_SetFieldsInCalculationOrder(FSPDF_FORM form, const FSCRT_BSTR* fieldNames, FS_DWORD count);

/**
 * @brief	Add a form field to arco form, and also create a new form control with the field.
 *
 * @details	Application can use this function to add a form field to acro from, along with a new form control:
 *			<ul>
 *			<li>If the form field exists, a new form control will be created and set to the field.</li>
 *			<li>If the form field doesn't exist, the field will be created according to parameter <i>fieldName</i> and <i>fieldType</i> and added to acro form, 
 *				along with a newly created form control.</li>
 *			</ul>
 *			Whether a field exists or not will be judged with input parameter <i>fieldName</i> and <i>fieldType</i>.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a document object. It should be valid.
 * @param[in]	page		Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[in]	fieldName	Pointer to a ::FSCRT_BSTR structure which specifies the name of the form field which is to be added. It should be a UTF-8 string.
 * @param[in]	fieldType	A ::FS_INT32 object which specifies the type of the form field which is to be added. 
 *							Please refer to macro definitions <b>FSPDF_FORMFIELDTYPE_XXX</b> and this should be one of these macros 
 *							except ::FSPDF_FORMFIELDTYPE_UNKNOWN and ::FSPDF_FORMFIELDTYPE_UNSPECIFIED.
 * @param[in]	rect		Pointer to a ::FSCRT_RECTF structure which indicates the location to add a new form control for the form field, in PDF page coordinate system.
 * @param[out]	formControl	Pointer to a <b>FSPDF_FORMCONTROL</b> handle that receives the newly created form control handle. It will be <b>NULL</b> if there's any error.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to PDF form is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is <b>NULL</b>, <i>page</i> is <b>NULL</b>, <i>fieldName</i> is invalid, <i>rect</i> is invalid, or <i>formControl</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldType</i> is unsupported.<br>
 *			::FSCRT_ERRCODE_FORMAT if parameter <i>fieldName</i> is not in UTF-8 format.<br>
 *			::FSCRT_ERRCODE_UNKNOWNSTATE if annotations of parameter <i>page</i> haven't been loaded.<br>
 *			::FSCRT_ERRCODE_CONFLICT if there exists a field with same name but in different type.<br>
 *			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			::FSCRT_ERRCODE_ERROR if some other error happen.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>formControl</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_AddField(FSPDF_FORM form, FSCRT_PAGE page, const FSCRT_BSTR* fieldName, FS_INT32 fieldType, FSCRT_RECTF *rect, FSPDF_FORMCONTROL* formControl);

/**
 * @brief	Remove a form field from arco form. 
 *
 * @details	If the form field appears on more than one PDF page, all representations will be removed.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a document object. It should be valid.
 * @param[in]	fieldName	Pointer to a ::FSCRT_BSTR structure which specifies the name of form field which is to be removed. It should be a UTF-8 string.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to PDF form is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is <b>NULL</b>, or <i>fieldName</i> is invalid.<br>
 *			::FSCRT_ERRCODE_FORMAT if parameter <i>fieldName</i> is not in UTF-8 format.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if no field is found.<br>
 *			::FSCRT_ERRCODE_ERROR if some other error happen.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
* @note		After a form field has been removed, indexes of other form fields will be changed.
*
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_RemoveField(FSPDF_FORM form, const FSCRT_BSTR* fieldName);

/*******************************************************************************/
/* Form filler																   */
/*******************************************************************************/
#ifndef _FSPDF_DEF_HANDLE_FORMFILLER_
#define _FSPDF_DEF_HANDLE_FORMFILLER_

/** @brief	Handle type to PDF form filler. */
FSCRT_DEFINEHANDLE(FSPDF_FORMFILLER);

#endif /* _FSPDF_DEF_HANDLE_FORMFILLER_ */


#ifndef _FS_DEF_FORMINTERACTION_WINDOWLESSEXTENT_
#define _FS_DEF_FORMINTERACTION_WINDOWLESSEXTENT_

/** @brief	Structure for windowless form interaction information. */
typedef struct  _FPDF_FORMINTERACTION_WINDOWLESSEXTENT_
{    
     /** @brief	The size of the data structure. It must be set to <b>sizeof</b>(::FSPDF_FORMINTERACTION_WINDOWLESS). */
     FS_DWORD	lStructSize;
    
     /** @brief	The user-supplied data. */
     FS_LPVOID	clientData;
	/** 
	 * @brief	When user is taking the mouse to select texts on a form field, this callback function will keep 
	 *			returning the selected areas to the implementation.
	 *
	 * @details This CALLBACK function is useful for implementing special text selection effect. Implementation should
	 *			first record the returned rectangles, then draw them one by one in the painting period, and finally remove all 
	 *			the recorded rectangles when finish painting.
	 *
	 * @param[in] clientData	Pointer to user-defined data.
	 * @param[in] pageIndex		The page index which starts from 0.
	 * @param[in] pdfRect		Pointer to a <b>FSCRT_RECTF</b> structure, which specifies the page area in PDF page coordinate.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 *
	 */
	FS_RESULT	(*OutputSelectedRect)(FS_LPVOID clientData,FS_INT32 pageIndex, FSCRT_RECTF* pdfRect);

	/** 
	 * @brief	Set the Cursor shape.
	 *
	 * @param[in] clientData	Pointer to user-defined data.
	 * @param[in] nCursorType	Cursor type, please refer to macro definitions <b>FSCRT_CURSOR_XXX</b>.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*SetCursor)(FS_LPVOID clientData, FS_INT32 nCursorType);

	/** 
	 * @brief	This method installs a system timer. A time-out value is specified, 
	 *			and every time a time-out occurs, the system passes a message to
	 *			the TimerProc callback function. 
	 *
	 * @param[in] clientData	Pointer to user-defined data.
	 * @param[in] uElapse		Specifies the time-out value, in milliseconds.
	 * @param[in] lpTimerFunc	A pointer to the callback function-TimerCallback.
	 * @param[out] timeID		The timer identifier of the new timer if the function is successful.
	 *							An application passes this value to the KillTimer method to kill 
	 *							the timer. Nonzero if it is successful; otherwise, it is zero.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*SetTimer)(FS_LPVOID clientData, FS_INT32 uElapse, FSCRT_CALLBACK_TIMER lpTimerFunc, FS_INT32* timeID);

	/** 
	 * @brief	This method kills the timer event identified by nIDEvent, set by an earlier call to SetTimer. 
	 *
	 * @param[in] clientData	Pointer to user-defined data.
	 * @param[in] timerID		The timer ID returned by FSPDF_FORMINTERACTION_WINDOWLESS::SetTimer function.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*KillTimer)(FS_LPVOID clientData, FS_INT32 timerID);

	/** 
	* @brief	This method will be called when the focus is set to a form control.
	*
	* @param[in] clientData		Pointer to user-defined data.
	* @param[in] control		Handler to a <b>FSPDF_FORMCONTROL</b> object.
	* @param[in] filedValue		The value of form field associated with the control.
	*
	* @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
	*			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	*
	* @note Currently,only support text field and combobox field.
	* */
	FS_RESULT	(*GotFocusOnControl)(FS_LPVOID clientData, FSPDF_FORMCONTROL control, const FSCRT_BSTR* filedValue);

	/** 
	* @brief	This method will be called when the focus is lost from a form control.
	*
	* @param[in] clientData		Pointer to user-defined data.
	* @param[in] control		Handler to a <b>FSPDF_FORMCONTROL</b> object.
	* @param[in] filedValue		The value of form field associated with the control.
	*
	* @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
	*			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	*
	* @note Currently,only support text field and combobox field.
	* */
	FS_RESULT	(*LostFocusOnControl)(FS_LPVOID clientData, FSPDF_FORMCONTROL control, const FSCRT_BSTR* filedValue);
	
} FSPDF_FORMINTERACTION_WINDOWLESS;

#endif /* FPDF_FORMINTERACTION_WINDOWLESS */

/**
 * @brief	Begin the form filling.
 *
 * @note	::FSPDF_Doc_SetActionHandler should be called to set the action handler before starting the form filling, otherwise some action types like javascript could not perform well.
 *
 * @param[in] form			Handle to a <b>FSPDF_FORM</b> object which is a PDF form object.
 * @param[in] windowless	Pointer to a <b>FPDF_FORMINTERACTION_WINDOWLESS</b> structure which includes the callback functions for windowless form filling.
 * @param[out] filler		Pointer to a <b>FSPDF_FORMFILLER</b> handle to receive the form filler handle.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>filler</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormFiller_Begin(FSPDF_FORM form, FSPDF_FORMINTERACTION_WINDOWLESS* windowless, FSPDF_FORMFILLER* filler);

/**
 * @brief	Trigger the platform event for the windowless form filling.
 *
 * @param[in] filler		Handle to a <b>FSPDF_FORMFILLER</b> object which is a filler object. It should be valid.
 * @param[in] page			Handle to a valid <b>FSCRT_PAGE</b> object. 
 *							It could be NULL for some event type like <b>FSCRT_EVENT_KEYDOWN</b>,<b>FSCRT_EVENT_KEYUP</b>,<b>FSCRT_EVENT_CHAR</b>.	
 * @param[in] page2Device	Pointer to a ::FSCRT_MATRIX structure.<br>, which specifies the matrix transformation from page to device coordinate.
 *							It could be NULL for some event type like <b>FSCRT_EVENT_KEYDOWN</b>,<b>FSCRT_EVENT_KEYUP</b>,<b>FSCRT_EVENT_CHAR</b>.
 * @param[in] eventType		The type of the event. Please refer to macro definitions <b>FSCRT_EVENT_XXX</b> and this should be one of these macros.
 * @param[in] eventData		The event data, relative to parameter <i>eventType</i>. Please refer to macro definitions <b>FSCRT_NOTEDATA_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>filler</i> is a <b>NULL</b> pointer or <i>eventType</i> is invalid.
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>filler</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormFiller_TriggerWindowlessEvent(FSPDF_FORMFILLER filler, FSCRT_PAGE page, FSCRT_MATRIX* page2Device, FS_DWORD eventType, FS_LPVOID eventData);

/**
 * @brief	Set the highlight color for the form field.
 *
 * @param[in] filler		Handle to a <b>FSPDF_FORMFILLER</b> object which is a filler object. It should be valid.
 * @param[in] fieldType		The form field type, please refer to macro definitions <b>FSPDF_FORMFIELDTYPE_XXX</b>.
 * @param[in] color			The color value in ARGB format.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>filler</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormFiller_SetHighlightColor(FSPDF_FORMFILLER filler, FS_INT32 fieldType, FS_ARGB color);

/**
 * @brief	Whether to show the highlight of form field or not.
 *
 * @param[in] filler		Handle to a <b>FSPDF_FORMFILLER</b> object which is a filler object. It should be valid.
 * @param[in] show			Whether to highlight the form field or not.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>filler</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormFiller_ShowHighlight(FSPDF_FORMFILLER filler, FS_BOOL show);

/**
 * @brief	Finish the form filling.
 *
 * @param[in] filler		Handle to a <b>FSPDF_FORMFILLER</b> object which is a filler object. It should be valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>filler</i> is a <b>NULL</b> pointer, or <i>fieldType</i> is invalid.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>filler</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_FormFiller_End(FSPDF_FORMFILLER filler);

/*******************************************************************************/
/* Form field trigger actions                                                  */
/*******************************************************************************/
/**
 * @brief	Update an action associated with a field (except signature field) and a trigger type at a specified index in a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	trigger			A ::FS_INT32 which represents a trigger type. It should be one of the following: <br>
 *								<ul>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_KS</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WF</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WV</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_FC</li>
 *								</ul>
 * @param[in]	index			A ::FS_INT32 which represents the index of the action.
 * @param[in]	actionData		Pointer to a ::FSPDF_ACTIONDATA structure that is associated with the action.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i> or <i>actionData</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found, <i>index</i> is out of range or no action is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_SetAction(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32 trigger, FS_INT32 index, const FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Insert an action associated with a field (except signature field) and a trigger type at a specified index in a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	trigger			A ::FS_INT32 which represents a trigger type. It should be one of the following: <br>
 *								<ul>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_KS</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WF</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WV</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_FC</li>
 *								</ul>
 * @param[in]	index			A ::FS_INT32 which represents the index of the action. Range: 0 to (actioncount-1). <i>actioncount</i> is returned by function ::FSPDF_FormField_CountActions.<br>
 *								If it's out of the range, parameter <i>actionData</i> will be inserted to the last.
 * @param[in]	actionData		Pointer to a ::FSPDF_ACTIONDATA structure that receives the action data that associated with the action.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i> or <i>actionData</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found, <i>index</i> is out of range or no action is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_InsertAction(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32 trigger, FS_INT32 index, 
										 const FSPDF_ACTIONDATA* actionData);

/**
 * @brief	Remove an action associated with a field (except signature field) and a trigger type by index in a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	trigger			A ::FS_INT32 which represents a trigger type.It should be one of the following: <br>
 *								<ul>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_KS</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WF</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WV</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_FC</li>
 *								</ul>
 * @param[in]	index			A ::FS_INT32 which represents the index of the action.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>fieldName</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found, <i>index</i> is out of range or no action is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_RemoveAction(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32 trigger, FS_INT32 index);

/**
 * @brief	Remove all actions associated with a field (except signature field) and a trigger type in a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	trigger			A ::FS_INT32 which represents a trigger type. It should be one of the following: <br>
 *								<ul>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_KS</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WF</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WV</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_FC</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>fieldName</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found or there is no trigger action.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_RemoveAllActions(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32 trigger);

/**
 * @brief	Remove a form control from a form field. 
 *
 * @details	If the form field has only one control, the field itself will be removed at the same time.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a document object. It should be valid.
 * @param[in]	fieldName	Pointer to a ::FSCRT_BSTR structure which specify the name of the form field.
 * @param[in]	formControl	Handle to a <b>FSPDF_FORMCONTROL</b> object which is to be removed.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to PDF form is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is <b>NULL</b>, <i>fieldName</i> is invalid, or <i>formControl</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if no field or control is found.<br>
 *			::FSCRT_ERRCODE_FORMAT if parameter <i>fieldName</i> is not in UTF-8 format.<br>
 *			::FSCRT_ERRCODE_ERROR if some other error happen.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>formControl</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_RemoveControl(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FSPDF_FORMCONTROL formControl);

/**
 * @brief	Perform the form field javascript to validate whether the user input value is valid.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a document object. It should be valid.
 * @param[in]	fieldName	Pointer to a <b>FSCRT_BSTR</b> structure which specify the name of form field.
 * @param[in]	value		Pointer to a <b>FSCRT_BSTR</b> structure which specify the input value of form field.
 * @param[out]	isValid		Pointer to FS_BOOL to receive the value indicating whether the input value is valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is a <b>NULL</b> pointer, or <i>fieldName</i>,<i>isValid</i> is NULL.<br>
 *			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_ValidateValue(FSPDF_FORM form, const FSCRT_BSTR* fieldName, const FSCRT_BSTR* value, FS_BOOL* isValid);

/**
 * @brief	Perform the form field javascript to validate whether the input of key stroke is valid.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a document object. It should be valid.
 * @param[in]	fieldName	Pointer to a <b>FSCRT_BSTR</b> structure which specifies the name of form field.
 * @param[in]	value		Pointer to a <b>FSCRT_BSTR</b> structure which specifies the input value of form field.
 * @param[out]	isValid		Pointer to FS_BOOL to receive the value indicating whether the input value is valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is a <b>NULL</b> pointer, or <i>fieldName</i>,<i>isValid</i> is NULL.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_ValidateKeyStroke(FSPDF_FORM form, const FSCRT_BSTR* fieldName, const FSCRT_BSTR* value, FS_BOOL* isValid);

#ifndef _FSPDF_DEF_STRUCTURE_JAVASCRIPTEVENT_
#define _FSPDF_DEF_STRUCTURE_JAVASCRIPTEVENT_
/**
 * @brief	Structure for javascript event.
 */
typedef struct _FSPDF_JAVASCRIPTEVENT
{
	/** @brief	Value has different meanings for different field events such as KeyStroke,Validate,Format...[in/out] */
	FSCRT_BSTR		strValue;
	/** @brief	The string which will be part of a field's value. [in]*/
	FSCRT_BSTR		strChange;
	/** @brief	Indicate the  position of a field's value where the strChange start. [in]*/
	FS_INT32		nStart;
	/** @brief	Indicate the  position of a field's value where the strChange end. [in]*/
	FS_INT32		nEnd;
	/** @brief	Verifies the current keystroke event before the data is committed. [in] */
	FS_BOOL			bWillCommit;
	/** @brief	Used for validation. Indicates whether a particular event in the event chain should succeed. [in/out] */
	FS_BOOL			bRc;
} FSPDF_JAVASCRIPTEVENT;

#endif /* _FSPDF_DEF_STRUCTURE_JAVASCRIPTEVENT_ */

/**
 * @brief	Perform the form field javascript to validate whether the input of key stroke is valid.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a document object. It should be valid.
 * @param[in]	fieldName	Pointer to a <b>FSCRT_BSTR</b> structure which specifies the name of form field.
 * @param[in]	jsEvent		Pointer to a <b>FSPDF_JAVASCRIPTEVENT</b> structure which specifies the current event of form field.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if one of <i>form</i>,<i>fieldName</i> or <i>isValid</i> is <b>NULL</b>, 
 *			or the range specified by <i>jsEvent.nStart</i> and <i>jsEvent.nEnd</i> is invalid.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_ValidateKeyStrokeEvent(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FSPDF_JAVASCRIPTEVENT* jsEvent);

/**
 * @brief	Perform the form field javascript to calculate the values of form fields.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a document object. It should be valid.
 * @param[in]	fieldName	Pointer to a <b>FSCRT_BSTR</b> structure which specifies the name of form field.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is NULL.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_Calculate(FSPDF_FORM form, const FSCRT_BSTR* fieldName);

/**
 * @brief	Perform the form field javascript to format the values of form fields.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a document object. It should be valid.
 * @param[in]	fieldName	Pointer to a <b>FSCRT_BSTR</b> structure which specify the name of form field.
 * @param[out]	isFormated	Pointer to FS_BOOL to receive the value indicating whether the value is formated.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is a <b>NULL</b> pointer, or <i>fieldName</i>,<i>formated</i> is NULL.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_Format(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_BOOL* isFormated);

/*******************************************************************************/
/* Form field                                                                  */
/*******************************************************************************/
/**
 * @brief	Set alignment property of the field's text, only useful for text field and list box.
 *
 * @details	Alignment is a property of variable text. It can be set to any kind of form field, but only useful for text field and list box, 
 *			which may contain variable text as their content.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	alignment		The new alignment type of the field's variable text. It should be one of the following: <br>
 *								<ul>
 *								<li>::FSPDF_ALIGNMENT_LEFT</li>
 *								<li>::FSPDF_ALIGNMENT_CENTER</li>
 *								<li>::FSPDF_ALIGNMENT_RIGHT</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>fieldName</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_SetAlignment(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32 alignment);

/**
 * @brief	Set flags specifying various characteristics of the field (except signature field).
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	flags			The flags of the field. Please refer to macro definitions <b>FSPDF_FORMFIELDFLAG_XXX</b> 
 *								and this can be one or a combination of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>fieldName</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_SetFlags(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_DWORD flags);

/**
 * @brief	Set default value of the field (except signature field).
 *
 * @details	Applicable for all fields except PushButton fields.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	value			Pointer to a ::FSCRT_BSTR structure that sets the default value of the field.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i> or <i>value</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_SetDefaultValue(FSPDF_FORM form, const FSCRT_BSTR* fieldName, const FSCRT_BSTR* value);

/**
 * @brief	Set value of a field (except signature field).
 *
 * @details	Applicable for all fields except PushButton fields.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	value			Pointer to a ::FSCRT_BSTR structure which receives the value of the field.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i> or <i>value</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
* 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_SetValue(FSPDF_FORM form, const FSCRT_BSTR* fieldName, const FSCRT_BSTR* value);

/**
 * @brief	Set default appearance to the specified field (except signature field).
 *
 * @param[in]	form				Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName			Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	defAppearance		Pointer to a ::FSPDF_DEFAULTAPPEARANCE structure that receives the default appearance of the specified fields.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i> or <i>defAppearance</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Currently, FSPDF_DEFAULTAPPEARANCE::textMatrix will not have any effect (even if FSPDF_DEFAULTAPPEARANCE::flags contains ::FSPDF_DEFAULTAPPEARANCE_TEXTMATRIX ), 
 *			if the related widget annotation of specified field has "MK" dictionary.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_SetDefaultAppearance(FSPDF_FORM form, const FSCRT_BSTR* fieldName, const FSPDF_DEFAULTAPPEARANCE* defAppearance);

/**
 * @brief	Set alternate name to be used in place of the actual field (except signature field) name.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	alternateName	Pointer to a ::FSCRT_BSTR structure which specifies alternate name.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i> or <i>alternateName</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_SetAlternateName(FSPDF_FORM form, const FSCRT_BSTR* fieldName, const FSCRT_BSTR* alternateName);

/**
 * @brief	Set mapping name to be used when exporting interactive form field data from the document (except signature field).
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	mappingName		Pointer to a ::FSCRT_BSTR structure which specifies mapping name.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i> or <i>mappingName</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_SetMappingName(FSPDF_FORM form, const FSCRT_BSTR* fieldName, const FSCRT_BSTR* mappingName);

/**
 * @brief	Set maximum length of the field's text (except signature field), in characters.
 *
 * @details	Applicable for Text fields.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	maxLen			The maximum length of the field's text.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>fieldName</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
 *			::FSCRT_ERRCODE_UNSUPPORTED if parameter <i>fieldName</i> represents a signature field.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_SetMaxLen(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32 maxLen);

/**
 * @brief	Set list box or combo box options.
 *
 * @details	Applicable for ComboBox & ListBox fields
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	options			Pointer to a ::FSPDF_CHOICEOPTION structure that is an array.
 * @param[in]	count			The counts of input option.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i> or <i>options</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty, or <i>count</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>field</i> is not a type of list box or combo box.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if function fails to update the internal state.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_SetOptions(FSPDF_FORM form, const FSCRT_BSTR* fieldName, const FSPDF_CHOICEOPTION* options, FS_INT32 count);

/**
 * @brief	Set top index for scrollable list boxes.
 *
 * @details	Applicable for ListBox fields. Parameter <i>index</i> is the index of first item which is in visible scope of list box.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form. It should be valid.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	index			The first visible item's index to be set. 
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> or <i>fieldName</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found, or <i>index</i> is out of range or no top visible choice option is found.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>field</i> is not a type of list box.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_SetTopVisibleIndex(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32 index);

/*******************************************************************************/
/* Form control                                                                */
/*******************************************************************************/
/**
 * @brief	Set option's export value.
 *
 * @details	Applicable for CheckBox and RadioButton fields
 *
 * @param[in]	formControl		Handle to a <b>FSPDF_FORMCONTROL</b> object which is a PDF form control. It should be valid.
 * @param[in]	exportValue		Pointer to a ::FSCRT_BSTR structure that sets the option's export value.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>formControl</i> or <i>exportValue</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>formControl</i> is not a type of check box or radio button.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>formControl</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormControl_SetExportValue(FSPDF_FORMCONTROL formControl, const FSCRT_BSTR* exportValue);

/**
 * @brief	Set check box or radio button's state.
 *
 * @details	Applicable for CheckBox & RadioButton fields
 *
 * @param[in]	formControl		Handle to a <b>FSPDF_FORMCONTROL</b> object which is a PDF form control. It should be valid.
 * @param[in]	checked			A ::FS_BOOL object that is the check box or radio button's state.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>formControl</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>formControl</i> is not a type of check box or radio button.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>formControl</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormControl_SetChecked(FSPDF_FORMCONTROL formControl, FS_BOOL checked);

/**
 * @brief	Set check box or radio button's default state.
 *
 * @details	Applicable for CheckBox & RadioButton fields
 *
 * @param[in]	formControl		Handle to a <b>FSPDF_FORMCONTROL</b> object which is a PDF form control. It should be valid.
 * @param[in]	checked			A ::FS_BOOL object that is check box or radio button's default state.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>formControl</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>formControl</i> is not a type of check box or radio button.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>formControl</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormControl_SetDefaultChecked(FSPDF_FORMCONTROL formControl, FS_BOOL checked);

/**
 * @brief	Perform the form control javascript which is specified by the trigger.
 *
 * @param[in]	control		Handle to a <b>FSPDF_FORMCONTROL</b> object which is a form control object. It should be valid.
 * @param[in]	trigger		Type of the trigger event. Please refer to macro definitions <b>FSPDF_TRIGGER_ANNOT_XXX</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>control</i> is a <b>NULL</b> pointer, or <i>trigger</i> is invalid.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Parameter <i>trigger</i> should be one of preceding six macros of definitions <b>FSPDF_TRIGGER_ANNOT_XXX</b>. This function may fail with others.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>control</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormControl_DoJavaScriptAction(FSPDF_FORMCONTROL control, FS_INT32 trigger);

/**
 * @brief	Perform the form field javascript to validate whether the user input value is valid.
 *
 * @param[in]		form		Handle to a <b>FSPDF_FORM</b> object which is a document object. It should be valid.
 * @param[in]		fieldName	Pointer to a ::FSCRT_BSTR structure which specify the name of form field.
 * @param[in,out]	jsEvent		Pointer to a ::FSPDF_JAVASCRIPTEVENT structure which specify the params of this event. 
 *								For this event, the member <b>strValue</b> of structure ::FSPDF_JAVASCRIPTEVENT	should be valid.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is a <b>NULL</b> pointer, or <i>jsEvent</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_ValidateValueEvent(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FSPDF_JAVASCRIPTEVENT* jsEvent);

/**
 * @brief	Perform the form field javascript to format the values of form fields.
 *
 * @param[in]		form		Handle to a <b>FSPDF_FORM</b> object which is a document object. It should be valid.
 * @param[in]		fieldName	Pointer to a ::FSCRT_BSTR structure which specify the name of form field.
 * @param[in,out]	jsEvent		Pointer to a ::FSPDF_JAVASCRIPTEVENT structure which specify the params of this event. Only FSPDF_JAVASCRIPTEVENT::strValue is used for this event.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is a <b>NULL</b> pointer, or <i>jsEvent</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_FormatEvent(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FSPDF_JAVASCRIPTEVENT* jsEvent);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFFORM */

#endif /* _FSPDF_FORM_W_H_ */
