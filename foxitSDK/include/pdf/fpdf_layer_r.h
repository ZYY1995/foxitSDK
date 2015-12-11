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
 * @file	fpdf_layer_r.h
 * @brief	Header file for \ref FPDFPAGEOBJECTS "PDF Page Objects" module of Foxit PDF SDK.
 * @details	This header file defines PDF layer related functionalities.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. Create and release PDF layer context. </li>
 *			<li>2. Retrieve document and layer context type. </li>
 *			<li>3. Reset, copy and merge layer context. </li>
 *			<li>4. Get and set visibility of layer context. </li>
 *			<li>5. Enumerate all layers. </li>
 *			<li>6. Get properties of a layer. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> explicitly.
 */

#ifndef _FSPDF_LAYER_R_H_
#define _FSPDF_LAYER_R_H_

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

#ifndef _FSPDF_DEF_HANDLE_LAYER_
#define _FSPDF_DEF_HANDLE_LAYER_
/** @brief	Handle type to PDF layer. */
FSCRT_DEFINEHANDLE(FSPDF_LAYER);
#endif // _FSPDF_DEF_HANDLE_LAYER_

/*******************************************************************************/
/* PDF Layer Node for enumerate the layers.                                    */
/*******************************************************************************/
#ifndef _FSCRT_DEF_STRUCTURE_LAYERNODE_
#define _FSCRT_DEF_STRUCTURE_LAYERNODE_
/**
 * @brief	Structure for PDF layer nodes.
 * 
 * @note	This structure is an encapsulation of PDF Layers.
 *			Foxit PDF SDK provides functions <b>FSPDF_LayerNode_XXX</b> to initialize and clear it.<br>
 */
typedef struct _FSPDF_LAYERNODE
{
	/** @brief	Layer name or layer group name, a UTF-8 string object. */
	FSCRT_BSTR				name;
	/**
	 * @brief	Handle to a <b>FSPDF_LAYER</b> object.
	 *
	 * @note	If not <b>NULL</b> means a layer; otherwise, it's a layer group.
	 */
	FSPDF_LAYER				layer;
	/**
	 * @brief	Pointer to children.
	 *
	 * @note	A layer or layer group could have children.
	 */
	struct _FSPDF_LAYERNODE*		children;
	/**
	 * @brief	Count of children.
	 *
	 */
	FS_INT32				count;
} FSPDF_LAYERNODE;
#endif //_FSCRT_DEF_STRUCTURE_LAYERNODE_

/**
 * @brief	Helper function to initialize a PDF layer node.
 *
 * @param[in]	layers		Pointer to a ::FSPDF_LAYERNODE structure which will be initialized.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if a parameter <i>layers</i> or <i>bstr</i> of FSPDF_LAYERNODE::name is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to initialize a layer node variable.<br>
 *			It sets FSCRT_BSTR::str to <b>NULL</b>, FSCRT_BSTR::len to 0 of FSPDF_LAYERNODE::name,
 *			FSPDF_LAYERNODE::layer and FSPDF_LAYERNODE::children to <b>NULL</b> and FSPDF_LAYERNODE::count to 0.<br>
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves
 *				when accessing the same objects during multi-thread environments.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_LayerNode_Init(FSPDF_LAYERNODE* layers);

/**
 * @brief	Helper function to clear a PDF layer node.
 *
 * @param[in]	layers		Pointer to a ::FSPDF_LAYERNODE structure which will be cleared.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>layers</i> or <i>bstr</i> of FSPDF_LAYERNODE::name is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if it fails to clear a PDF layer node.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	This helper function is used to clear data in a ::FSPDF_LAYERNODE object when no need to use it any more.<br>
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Applications need to make sure thread safety by themselves
 *				when accessing the same objects during multi-thread environments.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_LayerNode_Clear(FSPDF_LAYERNODE* layers);

/**
 * @brief	Enum all PDF Layers.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It shall be valid.
 * @param[out]	layers		Pointer to a <b>FSPDF_LAYERNODE</b> handle that receives PDF Layers.<br>
 *							If there are any errors, it will be set <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>document</i> or <i>layers</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the parameter <i>document</i> is not a valid type of PDF document.<br>
 *			::FSCRT_ERRCODE_NOTFOUND if parameter <i>document</i> doesn't contain any optional content.<br> 
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for ASYNC documents.<br>
 *			::FSCRT_ERRCODE_ERROR if it fails to enumerate all PDF Layers.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Doc_EnumLayers(FSCRT_DOCUMENT document, FSPDF_LAYERNODE* layers);

/*******************************************************************************/
/* Access PDF Layer Properties                                                 */
/*******************************************************************************/
/**
 * @brief	Get the name of a PDF layer.
 *
 * @param[in]	layer		Handle to a <b>FSPDF_LAYER</b> object which is a PDF layer. It shall be valid.
 * @param[out]	name		Pointer to a ::FSCRT_BSTR structure that receives a layer name. It shall be a UTF-8 string.<br>
 *							If there are any errors, FSCRT_BSTR::str will be set <b>NULL</b>, 
 *							and FSCRT_BSTR::len will be set 0.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>layer</i> or <i>name</i>is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
 *			::FSCRT_ERRCODE_ERROR if it fails to get name of a PDF layer.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>layer</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Layer_GetName(FSPDF_LAYER layer, FSCRT_BSTR* name);

/**
 * @brief	Check whether a PDF layer is in a given page or not.
 *
 * @param[in]	page		Handle to a <b>FSPDF_PAGE</b> object which is a PDF page. It shall be valid
 * @param[in]	layer		Handle to a <b>FSPDF_LAYER</b> object which is a PDF layer. It shall be valid.
 * @param[out]	isInPage	Pointer to a ::FS_BOOL object that receives a boolean value which indicates whether a layer is in a given page or not: <br>
 *							<b>TRUE</b> means in the page, while <b>FALSE</b> means not. <br>
 *							If there are any errors, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>page</i>, <i>layer</i> or <i>isInPage</i>is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>page</i> is not a type of PDF page.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>page</i>: this handle is long-term recoverable.</li>
  *				<li> <i>layer</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Layer_IsInPage(FSCRT_PAGE page, FSPDF_LAYER layer, FS_BOOL* isInPage);

/**
 * @brief	Check whether a PDF layer has a specific intent.
 *
 * @param[in]	layer		Handle to a <b>FSPDF_LAYER</b> object which is a PDF layer. It shall be valid.
 * @param[in]	intent		Pointer to a ::FSCRT_BSTR structure that specifies the intent name. It shall be a UTF-8 string.<br>
 *							Currently, PDF defines two intent names:"View","Design".
 * @param[out]	hasIntent	Pointer to a ::FS_BOOL object that receives a boolean value which indicates whether a layer has a specific intent <br>
 *							<b>TRUE</b> means it has the intent, while <b>FALSE</b> means not. <br>
 *							If there are any errors, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>layer</i> or <i>intent</i> or <i>hasIntent</i> is <b>NULL</b>, or <i>intent</i> is empty.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>layer</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_Layer_HasIntent(FSPDF_LAYER layer,const FSCRT_BSTR* intent, FS_BOOL* hasIntent);

/*******************************************************************************/
/* Definition and Functions for PDF Layer Context                              */
/*******************************************************************************/
#ifndef _FSPDF_DEF_MACRO_LAYERUSAGETYPE_
#define _FSPDF_DEF_MACRO_LAYERUSAGETYPE_
/**
 * @name	Macro definitions of Layer Usage Types.
 */
/**@{*/
/** @brief Use for a viewer. */
#define	FSPDF_LAYERUSAGETYPE_VIEW		0 
/** @brief Use to represent a document designer's structural organization of artwork. */
#define	FSPDF_LAYERUSAGETYPE_DESIGN		1 
/** @brief Use for printing. */
#define	FSPDF_LAYERUSAGETYPE_PRINT		2 
/** @brief Use for exporting. */
#define	FSPDF_LAYERUSAGETYPE_EXPORT		3 
/**@}*/
#endif //_FSPDF_DEF_MACRO_LAYERUSAGETYPE_

/**
 * @brief	Create a PDF layer context with a given type.
 *
 * @param[in]	document	Handle to a <b>FSCRT_DOCUMENT</b> object which is a PDF document object. It should be valid.
 * @param[in]	usType		Pointer to a ::FS_INT32 object indicating usage type. <br>
 * 							It should be one of the followings: <br>
 * 							<ul>
 * 							<li>::FSPDF_LAYERUSAGETYPE_VIEW</li>
 * 							<li>::FSPDF_LAYERUSAGETYPE_DESIGN</li>
 * 							<li>::FSPDF_LAYERUSAGETYPE_PRINT</li>
 * 							<li>::FSPDF_LAYERUSAGETYPE_EXPORT</li>
 *							</ul>
 * @param[out]	context		Pointer to a <b>FSPDF_LAYERCONTEXT</b> handle that receives a PDF layer context.<br>
 *							If there are any errors, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM when parameter <i>document</i> or <i>context</i>is <b>NULL</b>, or <i>usType</i> is invalid.<br>
 * 			::FSCRT_ERRCODE_INVALIDTYPE if parameter <i>document</i> is not a valid type of PDF document.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or incorrect memory access.<br>
 *			::FSCRT_ERRCODE_DATANOTREADY if there are not available data for asynchronous documents.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	It's required to call the function::FSPDF_LayerContext_Release to release a context when it isn't used anymore.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>document</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_LayerContext_Create(FSCRT_DOCUMENT document, FS_INT32 usType, FSPDF_LAYERCONTEXT* context);

/**
 * @brief	Release a PDF layer context.
 *
 * @param[in]	context		Handle to a <b>FSPDF_LAYERCONTEXT</b> object which is a PDF layer context.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>context</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if the PDF document which is parameter <i>context</i> belongs to is invalid.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>context</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_LayerContext_Release(FSPDF_LAYERCONTEXT context);

/**
 * @brief	Retrieve a PDF document which owns a PDF layer context.
 *
 * @param[in]	context			Handle to a <b>FSPDF_LAYERCONTEXT</b> object which is a PDF layer context.
 * @param[out]	document		Pointer to a <b>FSCRT_DOCUMENT</b> handle that receives a PDF document.
 *								If there are any errors, it will be <b>NULL</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>context</i>, or <i>document</i> is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>context</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_LayerContext_GetDocument(FSPDF_LAYERCONTEXT context, FSCRT_DOCUMENT* document);

/**
 * @brief	Get usage type of a PDF layer context.
 *
 * @param[in]	context		Handle to a <b>FSPDF_LAYERCONTEXT</b> object which is a PDF layer context.
 * @param[out]	usType		Pointer to a ::FS_INT32 object that receives a usage type.<br>
 * 							It can be one of the followings: <br>
 * 							<ul>
 * 							<li>::FSPDF_LAYERUSAGETYPE_VIEW</li>
 * 							<li>::FSPDF_LAYERUSAGETYPE_DESIGN</li>
 * 							<li>::FSPDF_LAYERUSAGETYPE_PRINT</li>
 * 							<li>::FSPDF_LAYERUSAGETYPE_EXPORT</li>
 *							</ul>
 *							If there are any errors, it will be -1.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>context</i> or <i>usType</i>is <b>NULL</b>.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term recoverable.</li>
 *				<li> <i>context</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_LayerContext_GetUsageType(FSPDF_LAYERCONTEXT context, FS_INT32* usType);

/**
 * @brief	Reset a PDF layer context.
 *
 * @param[in]	context		Handle to a <b>FSPDF_LAYERCONTEXT</b> object which is a PDF layer context.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>context</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_ERROR if it fails to reset a PDF layer context.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>context</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_LayerContext_Reset(FSPDF_LAYERCONTEXT context);

/**
 * @brief	Copy a PDF layer context state from another PDF layer context. 
 *
 * @param[in]	destContext		Handle to a <b>FSPDF_LAYERCONTEXT</b> object which is the destination PDF layer context.
 * @param[in]	srcContext		Handle to a <b>FSPDF_LAYERCONTEXT</b> object which is the source PDF layer context.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>destContext</i> or <i>srcContext</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if it fails to copy the state of layer context.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	The function will not change the usage type of the destination PDF layer context.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>destContext</i>: this handle is long-term partially recoverable.</li>
  *				<li> <i>srcContext</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_LayerContext_CopyStates(FSPDF_LAYERCONTEXT destContext,  FSPDF_LAYERCONTEXT srcContext);

/**
 * @brief	Merge state from source PDF layer context to destination. 
 *
 * @param[in]	destContext		Handle to a <b>FSPDF_LAYERCONTEXT</b> object which is the destination PDF layer context.
 * @param[in]	srcContext		Handle to a <b>FSPDF_LAYERCONTEXT</b> object which is the source PDF layer context. 
 *								It should be a different usage type with parameter <i>destContext</i>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>destContext</i> or <i>srcContext</i> is <b>NULL</b>.<br>
 *			::FSCRT_ERRCODE_INVALIDTYPE if the usage type of parameter <i>srcContext</i> is the same as <i>destContext</i>'s.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @note	The function doesn't change the usage type of the destination PDF layer context, 
 *			and only <b>OFF</b> layers in context will be merged.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>destContext</i>: this handle is long-term partially recoverable.</li>
  *				<li> <i>srcContext</i>: this handle is long-term partially recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_LayerContext_MergeStates(FSPDF_LAYERCONTEXT destContext, FSPDF_LAYERCONTEXT srcContext);

/**
 * @brief	Check whether a PDF layer is visible or not.
 *
 * @param[in]	context		Handle to a <b>FSPDF_LAYERCONTEXT</b> object which is PDF layer context.
 * @param[in]	layer		Handle to a <b>FSPDF_LAYER</b> object which is a PDF layer. It shall be valid.
 * @param[out]	visible		Pointer to a ::FS_BOOL object that receives a boolean value which indicates whether a layer is visible or not: <br>
 *							<b>TRUE</b> means visible, or <b>FALSE</b> means not.<br>
 *							If there are any errors, it will be <b>FALSE</b>.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>context</i>, <i>layer</i> or <i>visible</i>is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>context</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>layer</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_LayerContext_IsVisible(FSPDF_LAYERCONTEXT context, FSPDF_LAYER layer, FS_BOOL* visible);

/**
 * @brief	Change the visibility state of a PDF layer.
 *
 * @param[in]	context		Handle to a <b>FSPDF_LAYERCONTEXT</b> object which is a PDF layer context.
 * @param[in]	layer		Handle to a <b>FSPDF_LAYER</b> object which is a PDF layer. It shall be valid.
 * @param[in]	visible		A ::FS_BOOL value which represents the visibility state of PDF layer:<br>
 *							<b>TRUE</b> means visible, while <b>FALSE</b> means not.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if a parameter <i>context</i> or <i>layer</i>is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if an unrecoverable error occurs.<br>
 *			::FSCRT_ERRCODE_ERROR if it fails to change PDF layer visibility state.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is thread safe.
 *				<b>OOM Information</b>:<br>
 *				OOM handling is only for mobile platforms, not for server or desktop.<br>
 *				<ul>
 *				<li>This function is long-term unrecoverable.</li>
 *				<li> <i>context</i>: this handle is long-term partially recoverable.</li>
 *				<li> <i>layer</i>: this handle is long-term recoverable.</li>
 *				</ul>
 *				Please refer to the document "Robust PDF Applications with Limited Memory" for more details.
 */
FS_RESULT	FSPDF_LayerContext_SetVisible(FSPDF_LAYERCONTEXT context, FSPDF_LAYER layer, FS_BOOL visible);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FPDLAYER */

#endif /* _FSPDF_LAYER_R_H_ */