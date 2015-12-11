/**
 * Copyright (C) 2003-2015, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It's not allowed to 
 * distribute any parts of Foxit PDF SDK to third party or public without permission unless an agreement 
 * is signed between Foxit Software Inc. and customers to explicitly grant customers to do that.
 *
 * @file	fpdf_markedcontent_r.h
 * @brief	Header file for \ref FPDFPAGEOBJECTS "PDF Page Objects" module of Foxit PDF SDK.
 * @details	This header file provides direct access to marked content of PDF page objects.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Get a marked content object from a given page object. </li>
 *			<li>2. Count items of marked content object.</li>
 *			<li>3. Get parameter information of a given marked content. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Edit Add-on</b> explicitly.
 */

#ifndef _FSPDF_MARKEDCONTENT_R_H_
#define _FSPDF_MARKEDCONTENT_R_H_

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

/*******************************************************************************/
/* PDF Marked Content	                                                       */
/*******************************************************************************/
#ifndef _FSPDF_DEF_HANDLE_MARKEDCONTENT_
#define _FSPDF_DEF_HANDLE_MARKEDCONTENT_

/** @brief	Handle type to PDF marked-content object. */
FSCRT_DEFINEHANDLE(FSPDF_MARKEDCONTENT);
#endif /* _FSPDF_DEF_HANDLE_MARKEDCONTENT_ */

#ifndef _FSPDF_DEF_MACRO_MARKEDCONTENT_PARAMTYPE_
#define _FSPDF_DEF_MACRO_MARKEDCONTENT_PARAMTYPE_
/**
 * @name	Macro Definitions for Marked Content Parameter Types.
 */
/**@{*/

/** @brief	None parameters. */
#define FSPDF_MARKEDCONTENT_PARAMTYPE_NONE				0
/** @brief	A dictionary is defined by named resource in the "Properties" sub-dictionary of the current resource dictionary. */
#define FSPDF_MARKEDCONTENT_PARAMTYPE_PROPERTIESDICT	1
/** @brief	A dictionary may be written inline in the content stream as a direct object. */
#define FSPDF_MARKEDCONTENT_PARAMTYPE_DIRECTDICT		2
/** 
 * @brief	(Reserved)A dictionary contains an MCID entry, which is an integer marked-content identifier
 *			that uniquely identifies marked-content sequence within its content stream. 
 *
 * @note	MCID is usually an entry of a dictionary object. So this macro definition may not be used; 
 *			instead, ::FSPDF_MARKEDCONTENT_PARAMTYPE_PROPERTIESDICT or ::FSPDF_MARKEDCONTENT_PARAMTYPE_DIRECTDICT is used.
 */
#define FSPDF_MARKEDCONTENT_PARAMTYPE_MCID				3

/**@}*/
#endif /* _FSPDF_DEF_MACRO_MARKEDCONTENT_PARAMTYPE_ */

/**
 * @brief	Get a marked content object from a page object.
 *
 * @details	This function is used to get a marked content object from a specific page object.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	pageObj			Handle to a <b>FSPDF_PAGEOBJECT</b> object which is a page object.
 * @param[out]	mc				Pointer to a <b>FSPDF_MARKEDCONTENT</b> handle that receives a marked content object.
 *								If there's any errors, this shall be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 * 			::FSCRT_ERRCODE_INVALIDLICENSE if the current license is not authorized or getting page objects is not allowed.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>pageObj</i> or <i>mc</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>page</i> is an invalid type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves 
 *				when accessing the same objects during multi-thread environments.<br>
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is short-term.</li>
 *				<li> <i>page</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>pageObj</i>: this handle is short-term.</li>
 *				<li> <i>mc</i>: this handle is short-term.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT FSPDF_PageObject_GetMarkedContent(FSCRT_PAGE page, FSPDF_PAGEOBJECT pageObj, FSPDF_MARKEDCONTENT* mc);

/**
 * @brief	Get the count of marked content items in the marked content sequence.
 *
 * @details	A marked content object may be nested one within another, and this function is used to get the count of marked content items 
 *			in the current marked content sequence.	
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	mc				Handle to a <b>FSPDF_MARKEDCONTENT</b> object which is a marked content object.
 * @param[out]	count			Pointer to a ::FS_INT32 object that receives count of marked content items.<br>
 *								If there are any errors, it shall be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>page</i>, <i>mc</i> or <i>count</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>page</i> is an invalid type.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT FSPDF_MarkedContent_CountItems(FSCRT_PAGE page, FSPDF_MARKEDCONTENT mc, FS_INT32* count);

/**
 * @brief	Get the tag name of a specific marked content item.
 *
 * @details	A marked content object may be nested one within another, and this function is used to get tag name of a specific marked content item 
 *			in the current marked content sequence.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	mc				Handle to a <b>FSPDF_MARKEDCONTENT</b> object which is a marked content object.
 * @param[in]	index			The index of the marked content item. Range: 0 to (itemcount-1). <i>itemcount</i> is returned by the function ::FSPDF_MarkedContent_CountItems.
 * @param[out]	tagName			Pointer to a ::FSCRT_BSTR structure (a UTF-8 string) that receives value of tag name.<br>
 *								If there are any errors, FSCRT_BSTR::str will be set empty if it's not <b>NULL</b>, 
 *								and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>page</i>, <i>mc</i> or <i>tagName</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>page</i> is an invalid type.<br>
 * 			::FSCRT_ERRCODE_NOTFOUND if the parameter <i>index</i> is out of range.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT FSPDF_MarkedContent_GetTagName (FSCRT_PAGE page, FSPDF_MARKEDCONTENT mc, FS_INT32 index, FSCRT_BSTR* tagName);

/**
 * @brief	Check whether a marked content object has a specified marked content item.
 *
 * @details	A marked content object may be nested one within another, and this function is used to check whether a marked content object has 
 *			a specified marked content item in the current marked content sequence.	
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	mc				Handle to a <b>FSPDF_MARKEDCONTENT</b> object which is a marked content object.
 * @param[in]	tagName			Pointer to a ::FSCRT_BSTR structure to specify value of the tag name. It should be a UTF-8 string.
 * @param[out]	bHas			Pointer to a ::FS_BOOL object that receives a boolean value which specifies whether there's a marked content item with the specific tag name.<br>
 *								If there are any errors, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>page</i>, <i>mc</i>, <i>tagName</i> or <i>bHas</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>page</i> is invalid type.<br>
 * 			::FSCRT_ERRCODE_FORMAT if it is not a UTF-8 byte string in the parameter <i>tagName</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT FSPDF_MarkedContent_HasTag(FSCRT_PAGE page, FSPDF_MARKEDCONTENT mc, const FSCRT_BSTR* tagName, FS_BOOL* bHas);

/**
 * @brief	Get a parameter type of a parameter value of a specific marked content item.
 *
 * @details	A marked content object may be nested one within another, and this function is used to get the parameter type and 
 *			its value of a specific marked content item in the current marked content sequence.
 *
 * @param[in]	page			Handle to a <b>FSCRT_PAGE</b> object which is a PDF page. It should be valid.
 * @param[in]	mc				Handle to a <b>FSPDF_MARKEDCONTENT</b> object which is a marked content object.
 * @param[in]	tagName			Pointer to a ::FSCRT_BSTR structure to specify value of the tag name. It should be a UTF-8 string.
 * @param[out]	paramType		Pointer to ::FS_INT32 object that receives a parameter type.<br>
 *								Please refer to macro definitions <b>FSPDF_MARKEDCONTENT_PARAMTYPE_XXX</b> and this should be one of these macros.<br>
 *								If there are any errors, it will be set -1.
 * @param[out]  param			Pointer to ::FS_LPVOID object that receives the parameter value.
 *								<ul>
 *								<li>If the parameter <i>paramType</i> is ::FSPDF_MARKEDCONTENT_PARAMTYPE_NONE, this value will be <b>NULL</b>.</li>
 *								<li>If the parameter <i>paramType</i> is ::FSPDF_MARKEDCONTENT_PARAMTYPE_PROPERTIESDICT or ::FSPDF_MARKEDCONTENT_PARAMTYPE_DIRECTDICT, 
 *									this value will be a <b>FSPDF_OBJECT</b> handle, which indicates a PDF dictionary.</li>
 *								<li>If the parameter <i>paramType</i> is ::FSPDF_MARKEDCONTENT_PARAMTYPE_MCID, this value willl be a ::FS_INT32 object 
 *									that receives the MCID value, which uniquely identifies a marked-content sequence within its content stream.<br>
 *									But for most cases, <i>paramType</i> for MCID will be ::FSPDF_MARKEDCONTENT_PARAMTYPE_PROPERTIESDICT or ::FSPDF_MARKEDCONTENT_PARAMTYPE_DIRECTDICT, 
 *									and this value will be a <b>FSPDF_OBJECT</b> handle, which indicates a PDF dictionary with entry MCID.</li>
 *								</ul>
 *								If there's any error, it will be set <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS if succeeded.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>page</i>, <i>mc</i>, <i>tagName</i>, <i>paramType</i> or <i>param</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>page</i> is invalid type.<br>
 * 			::FSCRT_ERRCODE_FORMAT if it is not a UTF-8 byte string in parameter <i>tagName</i>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
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
FS_RESULT FSPDF_MarkedContent_GetItemParam(FSCRT_PAGE page, FSPDF_MARKEDCONTENT mc, const FSCRT_BSTR* tagName, FS_INT32* paramType, FS_LPVOID* param);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDFPAGEOBJECTS */

#endif /* _FSPDF_MARKEDCONTENT_R_H_ */