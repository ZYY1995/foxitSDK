/**
 * Copyright (C) 2003-2015, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It's not allowed to 
 * distribute any parts of Foxit PDF SDK to third party or public without permission unless an agreement 
 * is signed between Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file	fpdf_markedcontent_w.h
 * @brief	Header file for \ref FPDFPAGEOBJECTS "PDF Page Objects" module of Foxit PDF SDK.
 * @details	This header file provides direct access to marked content of PDF page objects.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Add a marked content item to a PDF page object. </li>
 *			<li>2. Delete a specific marked content item with the PDF page object.</li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Edit Add-on</b> explicitly.
 */

#ifndef _FSPDF_MARKEDCONTENT_W_H_
#define _FSPDF_MARKEDCONTENT_W_H_

/**
 * @defgroup	FPDFPAGEOBJECTS PDF Page Objects
 * @brief		Definitions for access to PDF Page Objects, PDF Marked Content, and PDF Layers.<br>
 *				Definitions and functions in this module are included in fpdf_pageobjects_r.h, fpdf_pageobjects_w.h, fpdf_markedcontent_r.h, fpdf_markedcontent_w.h, fpdf_layer_r.h, and fpdf_layer_w.h.<br>
 *				Module: PDFPageObjects<br>
 *				License Identifier: PDFPageObjects/All<br>
 *				Available License Right: Reading/Writing<br>
 *				For License Right <b>Reading</b>, see fpdf_pageobjects_r.h, fpdf_markedcontent_r.h, and fpdf_layer_r.h.<br>
 *				For License Right <b>Writing</b>, see fpdf_pageobjects_w.h, fpdf_markedcontent_w.h, and fpdf_layer_w.h.
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. Page objects:
 *					<ul>
 *					<li>a. Enumerate page objects, get page objects by position, insert or remove page objects, and generate contents of page objects.</li>
 *					<li>b. Page content consists of page objects. Each page object contains its state information, data and instructions for rendering.
 *						   A form XObject is not only a page object, but also a container. A form XObject consists of a set of page objects or sub Form XObjects.</li>
 *					<li>c. Note: PDF page should be parsed before page objects can be accessed.</li>
 *					<li>d. Reference: Chapter 4 and 5 in PDF Reference 1.7 describe how page contents are expressed.</li>
 *					</ul>
 *				</li>
 *				<li>2. Page object: get type of a page object, clone a page object, and access properties or state data.</li>
 *				<li>3. Text object: get or set text state, access unicode string of a text object, and create a text object.</li>
 *				<li>4. Path object: get or set path data, access fill mode and stroke state, and create a path object.</li>
 *				<li>5. Image object: clone bitmap object associated to an image object, create an image object, and set image data.</li>
 *				<li>6. Form XObject object: get page objects associated to a Form XObject object, and create a Form XObject object.</li>
 *				<li>7. Clipping data:
 *					<ul>
 *					<li>a. Enumerate clipping path objects or clipping text objects, add or delete clipping path and text object,
 *						   and clear all clipping data.</li>
 *					<li>b. Each page object may have its own clipping data. In PDF, clipping data may be path objects or text objects.
 *						   Multiple clipping objects form intersections or union results.</li>
 *					</ul>
 *				</li>
 *				<li>8. PDF marked content:
 *					<ul>
 *					<li>a. Access to PDF page object's marked content, retrieve marked content object, add a new marked content item and delete a marked content item..</li>
 *					<li>b. Reference: Section 10.5 in PDF Reference 1.7 describes Marked Content of PDF Content Stream.</li>
 *					</ul>
 *				</li>
 *				<li>9. PDF Layer Context access: create and release PDF layer context, merge or copy state of PDF layer context objects. </li>
 *				<li>10. PDF Layer access:
 *					<ul>
 *					<li>a. Enumerate all layers of a PDF document , get name of a PDF layer, set and get visibility of a PDF layer. </li>
 *					<li>b. Note: If a PDF layer is invalid, it can't be viewed, designed, printed or exported.</li>
 *					</ul>
 *				</li>
 *				<li>11. Note: most functions in this module are not thread safe, caller should ensure not to call them
 *					   to process page objects in a same page across multi-threads or should maintain thread safety by application self.</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif 

/**
 * @brief	Add a new marked content item to the current marked content object.
 *
 * @details	A marked content object may be nested one within another, and this function is used to add a new marked content item 
 *			to the current marked content object associated with the current page object. <br>
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	mc				Handle to a <b>FSPDF_MARKEDCONTENT</b> object which is a marked content object.
 * @param[in]	tagName			Pointer to a ::FSCRT_BSTR structure to specify value of the tag name. It should be a UTF-8 string.
 * @param[in]	paramType		Pointer to ::FS_INT32 object that specifies a parameter type. 
 *								Please refer to macro definitions <b>FSPDF_MARKEDCONTENT_PARAMTYPE_XXX</b> and this should be one of these macros except ::FSPDF_MARKEDCONTENT_PARAMTYPE_MCID.<br>
 *								Also check comments of the parameter <i>param</i> and note part for more details.
 * @param[in]	param			Pointer to ::FS_LPVOID object that specifies a parameter value.
 *								<ul>
 *								<li>If the parameter <i>paramType</i> is ::FSPDF_MARKEDCONTENT_PARAMTYPE_NONE, this value should be <b>NULL</b>.</li>
 *								<li>If the parameter <i>paramType</i> is ::FSPDF_MARKEDCONTENT_PARAMTYPE_PROPERTIESDICT or ::FSPDF_MARKEDCONTENT_PARAMTYPE_DIRECTDICT, 
 *									this value will be a <b>FSPDF_OBJECT</b> handle, which indicates a PDF dictionary. <br>
 *									ATTENTION: when parameter <i>paramType</i> is ::FSPDF_MARKEDCONTENT_PARAMTYPE_DIRECTDICT and this dictionary object is newly created by function ::FSPDF_Object_CreateDict, 
 *									user needs to release this dictionary object by function ::FSPDF_Object_Release after calling current funtion, 
 *									if this dictionary object itself hasn't been or will not be inserted into any PDF document or other PDF objects.
 *								</li>
 *								<li>For setting MCID, the parameter <i>paramType</i> should be ::FSPDF_MARKEDCONTENT_PARAMTYPE_PROPERTIESDICT or ::FSPDF_MARKEDCONTENT_PARAMTYPE_DIRECTDICT, 
 *									and MCID should be an entry in the marked-content reference dictionary.</li>
 *								</ul>
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if 
 *			<ul>
 *			<li>the parameter <i>page</i>, <i>mc</i>, <i>tagName</i> is <b>NULL</b>;</li>
 *			<li>the parameter <i>paramType</i> is ::FSPDF_MARKEDCONTENT_PARAMTYPE_MCID or invalid.</li>
 *			<li>the parameter <i>param</i> is <b>NULL</b> when the parameter <i>paramType</i> is 
 *			::FSPDF_MARKEDCONTENT_PARAMTYPE_DIRECTDICT or ::FSPDF_MARKEDCONTENT_PARAMTYPE_PROPERTIESDICT.</li>
 *			</ul>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or adding marked content item is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>page</i> is an invalid type, 
 *			or if the parameter <i>param</i> is not a valid PDF dictionary type 
 *			when the parameter <i>paramType</i> is ::FSPDF_MARKEDCONTENT_PARAMTYPE_DIRECTDICT or ::FSPDF_MARKEDCONTENT_PARAMTYPE_PROPERTIESDICT.<br>
 * 			::FSCRT_ERRCODE_FORMAT if it is not a UTF-8 byte string in parameter <i>tagName</i>.<br>
 *			::FSCRT_ERRCODE_CONFLICT if the parameter <i>tagName</i> has already existing in items of the current marked content object.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to add a new marked content item for any other reasons.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	::FSPDF_MARKEDCONTENT_PARAMTYPE_MCID cannot be used in this method, since a MCID identifier should be an entry in a marked-content reference dictionary. 
 *			So when an application needs to set MCID, the parameter <i>paramType</i> should be either ::FSPDF_MARKEDCONTENT_PARAMTYPE_PROPERTIESDICT 
 *			or ::FSPDF_MARKEDCONTENT_PARAMTYPE_DIRECTDICT. This application shall set MCID value in its dictionary entry.<br>
 *			Marked content is a part of page object. So after adding an item to marked content, applications should call the function ::FSPDF_PageObjects_GenerateContents 
 *			before saving a page to a file or reloading a page, otherwise all changes on page objects will be lost.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>mc</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_MarkedContent_AddItem(FSCRT_PAGE page, FSPDF_MARKEDCONTENT mc, const FSCRT_BSTR* tagName, FS_INT32 paramType, FS_LPCVOID param);

/**
 * @brief	Delete a specific marked content item from the current marked content sequence.
 *
 * @details	A marked content object may be nested one within another, and this function is used to delete a specific marked content item from current marked content sequence.	
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	mc				Handle to a <b>FSPDF_MARKEDCONTENT</b> object which is a marked content object.
 * @param[in]	tagName			Pointer to a ::FSCRT_BSTR structure to specify value of the tag name. It should be a UTF-8 string.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>page</i>, <i>mc</i> or <i>tagName</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or deleting marked content item is not allowed.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>page</i> is invalid type.<br>
 * 			::FSCRT_ERRCODE_FORMAT if it is not a UTF-8 byte string in the parameter <i>tagName</i>.<br>
 *			::FSCRT_ERRCODE_ERROR if fail to delete a specific marked content item for any other reasons.<br> 
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	Marked content is a part of page objects. So after deleting an item from marked content, applications should call the function ::FSPDF_PageObjects_GenerateContents 
 *			before saving a page to a file or reloading a page, otherwise all changes on page objects will be lost.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>mc</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_MarkedContent_DeleteItem(FSCRT_PAGE page, FSPDF_MARKEDCONTENT mc, const FSCRT_BSTR* tagName);

#ifdef __cplusplus
}
#endif

/**@}*/ /* group FPDFPAGEOBJECTS */

#endif /* _FSPDF_MARKEDCONTENT_W_H_ */