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
 * @file	fpdf_form_r.h
 * @brief	Header file for \ref FPDFFORM "PDF Form" module of Foxit PDF SDK.
 * @details	This header file defines PDF form supports.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Load PDF form and access form data. </li>
 *			<li>2. Get trigger actions of form field. </li>
 *			<li>3. Get properties of form field. </li>
 *			<li>4. Get form controls. </li>
 *			<li>5. Render form controls. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Form Add-on</b> explicitly.
 */

#ifndef _FSPDF_FORM_R_H_
#define _FSPDF_FORM_R_H_

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
/* Definitions for PDF form                                                    */
/*******************************************************************************/
#ifndef _FSPDF_DEF_HANDLE_FORM_
#define _FSPDF_DEF_HANDLE_FORM_

/** @brief	Handle type to PDF form. */
FSCRT_DEFINEHANDLE(FSPDF_FORM);

#endif /* _FSPDF_DEF_HANDLE_FORM_ */

#ifndef _FSPDF_DEF_HANDLE_FORMCONTROL_
#define _FSPDF_DEF_HANDLE_FORMCONTROL_

/** @brief	Handle type to PDF form control (widget). */
FSCRT_DEFINEHANDLE(FSPDF_FORMCONTROL);

#endif /* _FSPDF_DEF_HANDLE_FORMCONTROL_ */

#ifndef _FSPDF_DEF_MACRO_FORMFIELDTYPE_
#define _FSPDF_DEF_MACRO_FORMFIELDTYPE_
/**
 * @name	Macro Definitions for Form Field Types.
 */
/**@{*/

#define FSPDF_FORMFIELDTYPE_UNKNOWN			0	/**< @brief	Unknown type. */
#define FSPDF_FORMFIELDTYPE_PUSHBUTTON		1	/**< @brief	Push button type. */
#define FSPDF_FORMFIELDTYPE_CHECKBOX		2	/**< @brief	Check box type. */
#define FSPDF_FORMFIELDTYPE_RADIOBUTTON		3	/**< @brief	Radio button type. */
#define FSPDF_FORMFIELDTYPE_COMBOBOX		4	/**< @brief	Combo box type. */
#define FSPDF_FORMFIELDTYPE_LISTBOX			5	/**< @brief	List box type. */
#define FSPDF_FORMFIELDTYPE_TEXTFIELD		6	/**< @brief	single line or multi-line texts. */
#define FSPDF_FORMFIELDTYPE_UNSPECIFIED		FSPDF_FORMFIELDTYPE_UNKNOWN	/**< @brief	Unspecified type. */

/**@}*/
#endif /* _FSPDF_DEF_MACRO_FORMFIELDTYPE_ */

#ifndef _FSPDF_DEF_MACRO_FORMFIELDFLAG_
#define _FSPDF_DEF_MACRO_FORMFIELDFLAG_
/**
 * @name	Macro Definitions for Form Field Flags.
 */
/**@{*/

#define FSPDF_FORMFIELDFLAG_READONLY		0x001	/**< @brief	The field is read only and no editing is allowed. */
#define FSPDF_FORMFIELDFLAG_REQUIRED		0x002	/**< @brief	The field will be exported by a submit-form action. */
#define FSPDF_FORMFIELDFLAG_NOEXPORT		0x004	/**< @brief	The field must not be exported by a submit-form action. */

/**@}*/

/**
 * @name	Macro Definitions for Radio Button Field Flags.
 */
/**@{*/

/**
 * @brief	Unable to turn this radio button off
 *
 * @details	For radio button only: if set, one radio button has to be selected at any time;
 *			Otherwise, when the selected radio button is clicked, it will be turned off,
 *			(leaving no radio button selected at this time).
 */
#define FSPDF_FORMFIELDFLAG_BUTTON_NOTOGGLETOOF			0x100
/**
 * @brief	Put radio buttons with same value in unison
 *
 * @details	If set, radio buttons with same value in a field will be turned on or off 
 *			in unison (either all one, or all off). If cleared, all buttons are 
 *			mutually exclusive.
 */
#define FSPDF_FORMFIELDFLAG_BUTTON_RADIOSINUNISON		0x200

/**@}*/

/**
 * @name	Macro Definitions for Text Field Flags.
 */
/**@{*/

/** @brief	Multiple lines. */
#define FSPDF_FORMFIELDFLAG_TEXT_MULTILINE				0x100
/** @brief	This is a password field. Password shouldn't be displayed or exported. */
#define FSPDF_FORMFIELDFLAG_TEXT_PASSWORD				0x200
/**
 * @brief	Never show scroll bar.
 *
 * @details	Do not scroll (vertically for multiple-line fields, or horizontally for 
 *			single-line fields). If the field is full, no further text is accepted.
 */
#define FSPDF_FORMFIELDFLAG_TEXT_DONOTSCROLL			0x400
/**
 * @brief	Use combs.
 *
 * @details	If set, the field is automatically divided into as many equally spaced positions, 
 *			or combs, as the value of maximum length of a field's text, and the text is laid out into those combs.
 */
#define FSPDF_FORMFIELDFLAG_TEXT_COMB					0x800

/**@}*/

/**
 * @name	Macro Definitions for Combo Box Field Flags.
 */
/**@{*/

/**
 * @brief	Combo box style.
 *
 * @details	If set, the combo box includes an editable text control, otherwise, it's only a drop list.
 */
#define FSPDF_FORMFIELDFLAG_COMBO_EDIT				0x100

/**@}*/

/**
 * @name	Macro Definitions for List Box Field Flags.
 */
/**@{*/

/** @brief	If set, more than one items can be selected. */
#define FSPDF_FORMFIELDFLAG_CHOICE_MULTISELECT			0x100

/**@}*/
#endif /* _FSPDF_DEF_MACRO_FORMFIELDFLAG_ */

/*******************************************************************************/
/* Form                                                                        */
/*******************************************************************************/
/**
 * @brief	Check if the document has a Acro form.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document.
 * @param[out]	hasForm		Pointer to a ::FS_BOOL object that receives the result.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i>, or <i>hasForm</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to PDF form is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a type of PDF document.<br>
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
FS_RESULT	FSPDF_Doc_HasForm(FSCRT_DOCUMENT document, FS_BOOL* hasForm);

/**
 * @brief	Retrieve a form handle for a specific document.
 *
 * @param[in]	pdfDoc		Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document.
 * @param[out]	form		Pointer to a <b>FSPDF_FORM</b> handle that receives a form object.
 *
 * @note	If annotations have been loaded before this function is called, functions in \ref FPDFFORM "PDF Form" module can't work correctly.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pdfDoc</i>, or <i>form</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if current license is not authorized or access to PDF form is not allowed.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>pdfDoc</i> is not a type of PDF document.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if there is no form in the document.
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>pdfDoc</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_Load(FSCRT_DOCUMENT pdfDoc, FSPDF_FORM* form);

/**
 * @brief	Release a PDF interactive form object.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process the same object under multi-threaded environment.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_Release(FSPDF_FORM form);

/**
 * @brief	Retrieve a PDF document which owns the form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[out]	document		Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives a PDF document.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, or <i>document</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_GetDocument(FSPDF_FORM form, FSCRT_DOCUMENT* document);

/**
 * @brief	Get count of fields satisfying a name filter in a form.
 *
 * @note	 It will count all fields if parameter <i>filter</i> is <b>NULL</b>.
 *
 * @param[in]	form		Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	filter		Pointer to a string which partially matches with the name of fields. It can be <b>NULL</b>.
 * @param[out]	count		Pointer to a ::FS_INT32 object that receives the count of fields.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, or <i>count</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSPDF_Form_CountFields(FSPDF_FORM form, const FSCRT_BSTR* filter, FS_INT32* count);

/**
 * @brief	Search and retrieve the name and type of a field satisfying a name filter in a form.
 *
 * @details	It will get a form field from all fields with specific index if <i>filter</i> is <b>NULL</b>.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	filter			Pointer to a ::FSCRT_BSTR structure which partially matches the name of fields. It can be <b>NULL</b>.
 *								For example, text1 will match text1.0, text1.2.0, etc. but text1 will not match test10 or test11.1..
 * @param[in]	index			A ::FS_INT32 to specify which field to retrieve information in the filtered results.
 * @param[out]	fieldName		Pointer to a ::FSCRT_BSTR structure that receives the name of the result field.
 * @param[out]	fieldType		Pointer to a ::FS_INT32 object that receives the type of the result field.<br>
 *								Please refer to macro definitions <b>FSPDF_FORMFIELDTYPE_XXX</b> and this should be one of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>fieldType</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if parameter <i>index</i> is out of range.<br>
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
FS_RESULT	FSPDF_Form_GetField(FSPDF_FORM form, const FSCRT_BSTR* filter, FS_INT32 index, FSCRT_BSTR* fieldName, FS_INT32* fieldType);

/**
 * @brief	Search for form control at a specific position in a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	page			Handle to a <b>FSPDF_PAGE</b> object which is a PDF page.
 * @param[in]	x				A ::FS_FLOAT which is the x position in PDF page coordinate.
 * @param[in]	y				A ::FS_FLOAT which is the y position in PDF page coordinate.
 * @param[in]	tolerance		A ::FS_FLOAT which specifies the tolerance of the search.
 * @param[in]	typeFilter		A ::FS_INT32 to specify which type of form control to search.<br>
 *								Please refer to macro definitions <b>FSPDF_FORMFIELDTYPE_XXX</b> and this should be one of these macros.
 *								If it is ::FSPDF_FORMFIELDTYPE_UNSPECIFIED, the first form control at the specific position in a page will be retrieved.
 * @param[out]	formControl		Pointer to a <b>FSPDF_FORMCONTROL</b> handle that receives a form control when the search is successful.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>page</i> or <i>formControl</i>, is <b>NULL</b>, or <i>typeFilter</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page or <i>form</i> and <i>page</i> are in different documents.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if annotations in parameter <i>page</i> are not loaded.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no form control is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>formControl</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_GetControlAtPos(FSPDF_FORM form, FSCRT_PAGE page, FS_FLOAT x, FS_FLOAT y, FS_FLOAT tolerance, 
									   FS_INT32 typeFilter, FSPDF_FORMCONTROL* formControl);

/**
 * @brief	Search for form control which locates at a specific device position in a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	page			Handle to a <b>FSPDF_PAGE</b> object which is a PDF page object.
 * @param[in]	matrix			Pointer to a ::FSCRT_MATRIX structure that specifies the transform matrix returned by function ::FSPDF_Page_GetMatrix.
 * @param[in]	x				A ::FS_FLOAT which specifies the x-coordinate in device for the search position.
 * @param[in]	y				A ::FS_FLOAT which specifies the y-coordinate in device for the search position.
 * @param[in]	tolerance		A ::FS_FLOAT which specifies the offset tolerance of the search.
 * @param[in]	typeFilter		A ::FS_INT32 to specify which type of form control to search.
 *								Please refer to macro definitions <b>FSPDF_FORMFIELDTYPE_XXX</b> and this should be one of these macros.
 *								If it is ::FSPDF_FORMFIELDTYPE_UNSPECIFIED, the first form control at the specific position in a page will be retrieved.
 * @param[out]	formControl		Pointer to a <b>FSPDF_FORMCONTROL</b> handle that receives the handle to the control when the search is successful.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>page</i>, <i>matrix</i>, or <i>formControl</i> is <b>NULL</b>, or <i>typeFilter</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page or <i>form</i> and <i>page</i> are different document objects.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if annotations in parameter <i>page</i> are not loaded.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no form control is found.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>formControl</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Form_GetControlAtDevicePos(FSPDF_FORM form, FSCRT_PAGE page, const FSCRT_MATRIX* matrix, 
											 FS_INT32 x, FS_INT32 y, FS_FLOAT tolerance, 
											 FS_INT32 typeFilter, FSPDF_FORMCONTROL* formControl);

/**
 * @brief	Retrieve a default appearance of form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[out]	defAppearance	Pointer to a ::FSPDF_DEFAULTAPPEARANCE structure that receives the default appearance.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, or <i>defAppearance</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSPDF_Form_GetDefaultAppearance(FSPDF_FORM form, FSPDF_DEFAULTAPPEARANCE* defAppearance);

/**
 * @brief	Retrieve alignment property of a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[out]	alignment		Pointer to a ::FS_INT32 object to receive the alignment property. It should be one of the following: <br>
 *								<ul>
 *								<li>::FSPDF_ALIGNMENT_LEFT</li>
 *								<li>::FSPDF_ALIGNMENT_CENTER</li>
 *								<li>::FSPDF_ALIGNMENT_RIGHT</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, or <i>alignment</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSPDF_Form_GetAlignment(FSPDF_FORM form, FS_INT32* alignment);

/**
 * @brief	Retrieve a boolean value whether or not to construct appearance property of a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[out]	needConstruct	Pointer to a ::FS_BOOL object that specifies whether or not to construct appearances when load form controls. <b>TRUE</b> if need, <b>FALSE</b> if not.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, or <i>needConstruct</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSPDF_Form_NeedConstructAppearances(FSPDF_FORM form, FS_BOOL* needConstruct);

/**
 * @brief	Check if a name is valid for specified type of field in a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	newFieldName	Pointer to a new field name string, it should be a valid pointer to ::FSCRT_BSTR which represents the name to check.
 * @param[in]	fieldType		A ::FS_INT32 object which specifies a field type this name is intended for. 
 *								Please refer to macro definitions <b>FSPDF_FORMFIELDTYPE_XXX</b> and this should be one of these macros.
 * @param[out]	validate		Pointer to a ::FS_BOOL object that receives the result of the check.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>newFieldName</i>, or <i>validate</i> is <b>NULL</b>, <i>newFieldName</i> is empty, or <i>fieldType</i> is invalid.<br>
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
FS_RESULT	FSPDF_Form_ValidateFieldName(FSPDF_FORM form, const FSCRT_BSTR* newFieldName, FS_INT32 fieldType, FS_BOOL* validate);

/**
 * @brief	Get fields in a form in calculation order.
 *
 * @param[in]		form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[out]		fieldNames		Pointer to a ::FSCRT_BSTR structure which is an array to hold field names in order.
 * @param[in,out]	count			Pointer to a ::FS_DWORD object.
 *									When <i>fieldNames</i> is <b>NULL</b>, <i>count</i> will receive the actual field count in the calculation order.<br>
 *									When <i>fieldNames</i> is not <b>NULL</b>, <i>count</i> represents the length of <i>fieldNames</i> and has to
 *									be no less than the actual field count in calculation. It will also receive the actual field count.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, or <i>count</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_BUFFEROVERFLOW if parameter <i>fieldNames</i> is valid but <i>count</i> is smaller than required.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Commonly, this function is called twice. First, pass <b>NULL</b> to <i>fieldNames</i> to retrieve necessary array size,
 *			call it again when <i>fieldNames</i> contains enough space. <i>count</i> should never be empty.<br>
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
FS_RESULT	FSPDF_Form_GetFieldsInCalculationOrder(FSPDF_FORM form, FSCRT_BSTR* fieldNames, FS_DWORD* count);

/*******************************************************************************/
/* Form field trigger actions                                                  */
/*******************************************************************************/
/**
 * @brief	Retrieve count of actions associated with a field and a trigger type in a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	trigger			A ::FS_INT32 which represents a trigger type.It should be one of the following: <br>
 *								<ul>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_KS</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WF</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WV</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_FC</li>
 *								</ul>
 * @param[out]	count			Pointer to a ::FS_INT32 object that receives the action count.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>count</i> is <b>NULL</b>, or <i>fieldName</i> is empty, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
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
FS_RESULT	FSPDF_FormField_CountActions(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32 trigger, FS_INT32* count);

/**
 * @brief	Retrieve action associated with a field and a trigger type at a specified index in a form.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[in]	trigger			A ::FS_INT32 which represents a trigger type. It should be one of the following: <br>
 *								<ul>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_KS</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WF</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_WV</li>
 *								<li>::FSPDF_TRIGGER_FORMFIELD_FC</li>
 *								</ul>
 * @param[in]	index			A ::FS_INT32 which represents the index of the action.
 * @param[out]	actionData		Pointer to a ::FSPDF_ACTIONDATA structure that receives action data associated with the action.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>,or <i>actionData</i> is <b>NULL</b>, or <i>fieldName</i> is empty, or <i>trigger</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found, <i>index</i> is out of range or no action is found.<br>
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
FS_RESULT	FSPDF_FormField_GetAction(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32 trigger, FS_INT32 index, FSPDF_ACTIONDATA* actionData);

/*******************************************************************************/
/* Form field                                                                  */
/*******************************************************************************/
#ifndef _FSPDF_DEF_STRUCTURE_CHOICEOPTION_
#define _FSPDF_DEF_STRUCTURE_CHOICEOPTION_

/**
 * @brief	Structure for list box and combo box option only
 */
typedef struct _FSPDF_CHOICEOPTION
{
	/**
	 * @brief	List box or Combo box option value.
	 */
	FSCRT_BSTR		optionValue;
	/**
	 * @brief	List box or Combo box option Label.
	 */
	FSCRT_BSTR		optionLabel;
	/**
	 * @brief	True if the item is selected.
	 */
	FS_BOOL			selected;
	/**
	 * @brief	Default selection flag.
	 */
	FS_BOOL			defaultSelected;
} FSPDF_CHOICEOPTION;

#endif /* _FSPDF_DEF_STRUCTURE_CHOICEOPTION_ */

/**
 * @brief	Helper function to initialize options.
 *
 * @param[in]	options		Pointer to a ::FSPDF_CHOICEOPTION structure which is for list box and combo box.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>options</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to initialize options.<br>
 *			It sets FSPDF_CHOICEOPTION::optionValue and FSPDF_CHOICEOPTION::optionLabel empty, 
 *			and sets FSPDF_CHOICEOPTION::selected and FSPDF_CHOICEOPTION::defaultSelected <b>FALSE</b><br>.
 *			Application can initialize a ::FSPDF_CHOICEOPTION as another way instead of calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe, do not call it to process the same object between multi-threads, 
 *				or application should maintain thread safety when need process same objects under multi-threaded environment.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_ChoiceOption_Init(FSPDF_CHOICEOPTION* options);

/**
 * @brief	Helper function to clear options.
 *
 * @param[in]	options		Pointer to a ::FSPDF_CHOICEOPTION structure which is for list box and combo box,
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>options</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to clear options.<br>
 *			It frees FSPDF_CHOICEOPTION::optionValue and FSPDF_CHOICEOPTION::optionLabel and set them to be <b>NULL</b> pointer.<br>
 *			Application can free a ::FSPDF_CHOICEOPTION as another way instead of calling this function.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe, do not call it to process same objects between multi-threads, 
 *				or application should maintain thread safety when need process same objects under multi-threaded environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_ChoiceOption_Clear(FSPDF_CHOICEOPTION* options);

/**
 * @brief	Get alignment type of a field's text.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[out]	alignment		Pointer to a ::FS_INT32 object to save the alignment type of the field's text. It should be one of the following: <br>
 *								<ul>
 *								<li>::FSPDF_ALIGNMENT_LEFT</li>
 *								<li>::FSPDF_ALIGNMENT_CENTER</li>
 *								<li>::FSPDF_ALIGNMENT_RIGHT</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>alignment</i> is <b>NULL</b>, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
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
FS_RESULT	FSPDF_FormField_GetAlignment(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32* alignment);

/**
 * @brief	Get flags specifying various characteristics of the field.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[out]	flags			Pointer to a ::FS_DWORD to save the flags of the field. 
 *								Please refer to macro definitions <b>FSPDF_FORMFIELDFLAG_XXX</b> and this can be one or a combination of these macros.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>flags</i> is <b>NULL</b>, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
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
FS_RESULT	FSPDF_FormField_GetFlags(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_DWORD* flags);

/**
 * @brief	Get field type.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[out]	fieldType		Pointer to a ::FS_INT32 object to save the type of the field.
 *								Please refer to macro definitions <b>FSPDF_FORMFIELDTYPE_XXX</b> and this should be one of these macros. <br>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>fieldType</i> is <b>NULL</b>, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
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
FS_RESULT	FSPDF_FormField_GetType(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32* fieldType);

/**
 * @brief	Get default value of a field.
 *
 * @details	Applicable for all fields except PushButton fields.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[out]	value			Pointer to a ::FSCRT_BSTR structure that receives default value of the field.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>value</i> is <b>NULL</b>, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
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
FS_RESULT	FSPDF_FormField_GetDefaultValue(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FSCRT_BSTR* value);

/**
 * @brief	Get value of a field.
 *
 * @details	Applicable for all fields except PushButton fields.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[out]	value			Pointer to a ::FSCRT_BSTR structure that receives the value of the field.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>value</i> is <b>NULL</b>, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
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
FS_RESULT	FSPDF_FormField_GetValue(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FSCRT_BSTR* value);

/**
 * @brief	Get count of controls in a PDF page which belongs to specified fields.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object that is a PDF interactive form.
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object that is a PDF page object.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents name of a field. 
 *								If this is <b>NULL</b> or <i>fieldName->str</i> is NULL or <i>fieldName->len</i> is less than 1, it means to get all form controls count in the page.
 * @param[out]	count			Pointer to a ::FS_INT32 object that receives count of controls.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>page</i>, or <i>formControl</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page or <i>form</i> and <i>page</i> are different document objects.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if annotations in parameter <i>page</i> are not loaded.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 <br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_CountControls(FSPDF_FORM form, FSCRT_PAGE page, const FSCRT_BSTR* fieldName, FS_INT32* count);

/**
 * @brief	Get a form control which belongs to the specified fields.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page object.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents name of a field. 
 *								If this is <b>NULL</b> or <i>fieldName->str</i> is NULL or <i>fieldName->len</i> is less than 1, it means to get all form controls count in the page.
 * @param[in]	index			The zero-based index in the matched form controls.
 * @param[out]	formControl		Pointer to a <b>FSPDF_FORMCONTROL</b> handle that receives the form control handle.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>page</i>, or <i>formControl</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a PDF page or <i>form</i> and <i>page</i> are different document objects.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found, or <i>index</i> is out of range or no form control is found.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if annotations in parameter <i>page</i> are not loaded.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>form</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>formControl</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormField_GetControl(FSPDF_FORM form, FSCRT_PAGE page, const FSCRT_BSTR* fieldName, FS_INT32 index, FSPDF_FORMCONTROL* formControl);

/**
 * @brief	Get index of the form control which belongs to the specified fields.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	formControl		Handle to a <b>FSPDF_FORMCONTROL</b> object that is a form control.
 * @param[out]	index`			Pointer to a ::FS_INT32 object that receives zero-based index in the matched form controls.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>formControl</i>, or <i>index</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
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
FS_RESULT	FSPDF_FormField_GetControlIndex(FSPDF_FORM form, const FSPDF_FORMCONTROL formControl, FS_INT32* index);

/**
 * @brief	Get default appearance of specified fields.
 *
 * @param[in]	form				Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName			Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[out]	defAppearance		Pointer to a ::FSPDF_DEFAULTAPPEARANCE structure that receives the default appearance of the specified fields.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>defAppearance</i> is <b>NULL</b>, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
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
FS_RESULT	FSPDF_FormField_GetDefaultAppearance(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FSPDF_DEFAULTAPPEARANCE* defAppearance);

/**
 * @brief	Get alternate name to be used in place of actual field name.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[out]	alternateName	Pointer to a ::FSCRT_BSTR structure that receives alternate name.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>alternateName</i> is <b>NULL</b>, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
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
FS_RESULT	FSPDF_FormField_GetAlternateName(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FSCRT_BSTR* alternateName);

/**
 * @brief	Get mapping name to be used when exporting interactive form field data from the document.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[out]	mappingName		Pointer to a ::FSCRT_BSTR structure which receives mapping name.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>mappingName</i> is <b>NULL</b>, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
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
FS_RESULT	FSPDF_FormField_GetMappingName(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FSCRT_BSTR* mappingName);

/**
 * @brief	Get maximum length of the field's text, in characters.
 *
 * @details	Applicable for Text fields.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[out]	maxLen			Pointer to a ::FS_INT32 object that receives the maximum length of the field's text.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>maxLen</i> is <b>NULL</b>, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found.<br>
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
FS_RESULT	FSPDF_FormField_GetMaxLen(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32* maxLen);

/**
 * @brief	Get list box or combo box options.
 *
 * @details	Applicable for ListBox and ComboBox fields.
 *
 * @param[in]		form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]		fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[out]		options			Pointer to a ::FSPDF_CHOICEOPTION structure array.
 * @param[in,out]	count			Pointer to a ::FS_INT32 object that indicates the number of option array. When this function is called, <i>count</i> tells 
 *									the number of <i>option</i> array, and when this function returns, <i>count</i> is the option's count stored in <i>options</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i>, or <i>count</i> is <b>NULL</b>, or <i>fieldName</i> is empty, or both <i>options</i> and <i>count</i> are <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found, or no choice options are found.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>field</i> is not a type of list box or combo box.<br>
 * 			::FSCRT_ERRCODE_BUFFEROVERFLOW if parameter <i>options</i> is valid but <i>count</i> is smaller than required.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Commonly, this function is called twice. First, pass <b>NULL</b> to <i>options</i> to retrieve necessary count.<br>
 *			Call it again when <i>options</i> contains enough space. <i>count</i> should never be empty.<br>
 *			Caller should prepare enough space before calling this function.<br>
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
FS_RESULT	FSPDF_FormField_GetOptions(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FSPDF_CHOICEOPTION* options, FS_INT32* count);

/**
 * @brief	Get top index for scrollable list boxes.
 *
 * @details	Applicable for ListBox fields. Parameter <i>index</i> is the index of first item which is in visible scope of list box.
 *
 * @param[in]	form			Handle to a <b>FSPDF_FORM</b> object which is a PDF interactive form.
 * @param[in]	fieldName		Pointer to a ::FSCRT_BSTR structure which represents the name of a field.
 * @param[out]	index			Pointer to a ::FS_INT32 object that receives the index of the first visible item. 
 *								
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeds.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>form</i>, <i>fieldName</i> or <i>index</i> is a <b>NULL</b> pointer, or <i>fieldName</i> is empty.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no specified form field is found, or no top visible choice option is found.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>field</i> is not a type of list box or combo box.<br>
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
FS_RESULT	FSPDF_FormField_GetTopVisibleIndex(FSPDF_FORM form, const FSCRT_BSTR* fieldName, FS_INT32* index);

/*******************************************************************************/
/* Form control                                                                */
/*******************************************************************************/
/**
 * @brief	Get widget annotation from form control handle.
 *
 * @param[in]	formControl		Handle to a <b>FSPDF_FORMCONTROL</b> object which is a PDF form control.
 * @param[out]	widgetAnnot		Pointer to a <b>FSCRT_ANNOT</b> handle that receives widget annotation handle.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>formControl</i>, or <i>widgetAnnot</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>formControl</i>: this handle is short-term.</li>
 *				<li> <i>widgetAnnot</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_FormControl_GetWidgetAnnot(FSPDF_FORMCONTROL formControl, FSCRT_ANNOT* widgetAnnot);

/**
 * @brief	Get field name from form control handle.
 *
 * @param[in]	formControl		Handle to a <b>FSPDF_FORMCONTROL</b> object which is a PDF form control.
 * @param[out]	fieldName		Pointer to a ::FSCRT_BSTR structure that receives field name. It should not be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>formControl</i>, or <i>fieldName</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
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
FS_RESULT	FSPDF_FormControl_GetFieldName(FSPDF_FORMCONTROL formControl, FSCRT_BSTR* fieldName);

/**
 * @brief	Get option's export value.
 *
 * @details	Applicable for CheckBox and RadioButton fields
 *
 * @param[in]	formControl		Handle to a <b>FSPDF_FORMCONTROL</b> object which is a PDF form control.
 * @param[out]	exportValue		Pointer to a ::FSCRT_BSTR structure that receives the option's export value.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>formControl</i>, or <i>exportValue</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if no export value is found.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>formControl</i> is not a type of check box or radio button.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
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
FS_RESULT	FSPDF_FormControl_GetExportValue(FSPDF_FORMCONTROL formControl, FSCRT_BSTR* exportValue);

/**
 * @brief	Get check box or radio button's state.
 *
 * @details	Applicable for CheckBox and RadioButton fields.
 *
 * @param[in]	formControl		Handle to a <b>FSPDF_FORMCONTROL</b> object which is a PDF form control.
 * @param[out]	checked			Pointer to a ::FS_BOOL object that receives the check box or radio button's state.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>formControl</i>, or <i>checked</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSPDF_FormControl_IsChecked(FSPDF_FORMCONTROL formControl, FS_BOOL* checked);

/**
 * @brief	Get check box or radio button's default state.
 *
 * @details	Applicable for CheckBox and RadioButton fields.
 *
 * @param[in] formControl		Handle to a <b>FSPDF_FORMCONTROL</b> object which is a PDF form control.
 * @param[out] checked			Pointer to a ::FS_BOOL object that receives the check box or radio button's default state.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>formControl</i>, or <i>checked</i> is <b>NULL</b>.<br>
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
FS_RESULT	FSPDF_FormControl_IsDefaultChecked(FSPDF_FORMCONTROL formControl, FS_BOOL* checked);

/**
 * @brief	Start rendering a PDF form control in a renderer with a PDF rendering context.
 *
 * @details	It will spend a long time to render a form control with complex or large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass <i>renderProgress</i> to ::FSCRT_Progress_Continue to continue rendering in steps, and should call function ::FSCRT_Progress_Release to destroy <i>renderProgress</i> object if rendering process is over.
 *
 * @param[in]	pdfRenderContext	Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF rendering context, created by function ::FSPDF_RenderContext_Create.
 * @param[in]	renderer			Handle to a <b>FSCRT_RENDERER</b> object which represents a rendering engine, 
 *									createcd by function ::FSCRT_Renderer_CreateOnBitmap or platform-dependednt renderer creating functions.
 * @param[in]	formControls		Pointer to a <b>FSPDF_FORMCONTROL</b> array handle which is a PDF form control object.
 * @param[in]	count				A ::FS_INT32 object that is the number of element in the formControls array.
 * @param[out]	renderProgress		Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pdfRenderContext</i>, <i>renderer</i>, <i>formControls</i>, or <i>renderProgress</i> is <b>NULL</b>, or <i>count</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			::FSCRT_ERRCODE_ERROR if fails to render form control because of any other reasons.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	::FSPDF_RENDERCONTEXTFLAG_NOWIDGET will be ignored in this function if it has been set to parameter <i>pdfRenderContext</i>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				<li> <i>formControl</i>: this handle is short-term.</li>
 *				<li> <i>renderProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_StartFormControls(FSPDF_RENDERCONTEXT pdfRenderContext, FSCRT_RENDERER renderer, const FSPDF_FORMCONTROL* formControls, FS_INT32 count, FSCRT_PROGRESS* renderProgress);

/**
 * @brief	Start rendering a page's form controls in a renderer with a PDF rendering context.
 *
 * @details	It will take a long time to render all form controls in a page with complex or large contents, so Foxit PDF SDK uses a progressive process to do this.<br>
 * 			Caller should pass <i>renderProgress</i> to ::FSCRT_Progress_Continue to continue rendering in steps, and should call function ::FSCRT_Progress_Release to destroy <i>renderProgress</i> object if rendering process is over.
 *
 * @param[in]	pdfRenderContext	Handle to a <b>FSPDF_RENDERCONTEXT</b> object which is a PDF rendering context, created by function ::FSPDF_RenderContext_Create.
 * @param[in]	renderer			Handle to a <b>FSCRT_RENDERER</b> object which represents a rendering engine, 
 *									created by function ::FSCRT_Renderer_CreateOnBitmap or platform-dependednt renderer creating functions.
 * @param[in]	page				Handle to a <b>FSCRT_PAGE</b> object which is a PDF page.
 * @param[out]	renderProgress		Pointer to a <b>FSCRT_PROGRESS</b> handle that receives a handle of progressive process.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>pdfRenderContext</i>, <i>renderer</i>, <i>page</i>, or <i>renderProgress</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNKNOWNSTATE if page form controls are not loaded.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if function finds an unrecoverable error internally.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	::FSPDF_RENDERCONTEXTFLAG_NOWIDGET will be ignored in this function if it has been set to parameter <i>pdfRenderContext</i>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>pdfRenderContext</i>: this handle is long-term recoverable.</li>
 *				<li> <i>renderer</i>: this handle is long-term recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>renderProgress</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_RenderContext_StartPageFormControls(FSPDF_RENDERCONTEXT pdfRenderContext, FSCRT_RENDERER renderer, 
													  FSCRT_PAGE page, FSCRT_PROGRESS* renderProgress);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFFORM */

#endif /* _FSPDF_FORM_R_H_ */
