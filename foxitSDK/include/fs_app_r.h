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
 * @file	fs_app_r.h
 * @brief	Header file for \ref FSAPP "App" module of Foxit PDF SDK.
 * @details	This header file defines application related supports.<br>
 *			It contains:<br>
 *			<ul>
 *			<li>1. An application handler to expand functions of Foxit PDF SDK. </li>
 *			<li>2. Formfiller related macros. </li>
 *			</ul>
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please request for enabling <b>Standard module</b> explicitly.
 */

#ifndef _FSCRT_APP_R_H_
#define _FSCRT_APP_R_H_

/**
 * @defgroup	FSAPP App
 * @brief		Definitions for a application access of Foxit PDF SDK.<br>
 *				Definitions and functions in this module are included in fs_app_r.h.<br>
 *				Module: App<br>
 *				License Identifier: App/All<br>
 *				Available License Right: Unnecessary
 * @details		This module contains following features:<br>
 *				<ul>
 *				<li>1. Application handler:
 *					<ul>
 *					<li>a. ::FSCRT_APPHANDLER provides an extension mechanism between applications and Foxit PDF SDK.</li>
 *					<li>b. There might be some functions which should be implemented by applications but be used by Foxit PDF SDK internally,
 *						   and Foxit PDF SDK can also send some events to applications for some purpose.</li>
 *					<li>c. Note: currently only PSI defines one event and ejects it to FSCRT_APPHANDLER::OnEvent callback function.</li>
 *					</ul>
 *				</li>
 *				</ul>
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/* Note definitions - message & event                                         */
/*                                                                            */
/* Virtual key codes, note flags, note types, cursor types, note structure                  */
/******************************************************************************/
#ifndef _FSCRT_DEF_VKEY_
#define _FSCRT_DEF_VKEY_
/**
 * @name 	Macro Definitions for Virtual Key Codes
 */
/**@{*/

#define FSCRT_VKEY_UNKNOWN		0x00	/**< @brief	An unknown key. */
#define FSCRT_VKEY_BACK			0x08	/**< @brief	Backspace key. */
#define FSCRT_VKEY_TAB			0x09	/**< @brief	Tab key. */
#define FSCRT_VKEY_RETURN		0x0D	/**< @brief	Enter key. */
#define FSCRT_VKEY_SHIFT		0x10	/**< @brief	Shift key. */
#define FSCRT_VKEY_CONTROL		0x11	/**< @brief	Ctrl key. */
#define FSCRT_VKEY_MENU			0x12	/**< @brief	Menu key. */
#define FSCRT_VKEY_PAUSE		0x13	/**< @brief	Pause Break key. */
#define FSCRT_VKEY_ESCAPE		0x1B	/**< @brief	ESC key. */
#define FSCRT_VKEY_SPACE		0x20	/**< @brief	Space key. */
#define FSCRT_VKEY_PRIOR		0x21	/**< @brief	Page Up key. */
#define FSCRT_VKEY_NEXT			0x22	/**< @brief	Page Down key. */
#define FSCRT_VKEY_END			0x23	/**< @brief	End key. */
#define FSCRT_VKEY_HOME			0x24	/**< @brief	Home key. */
#define FSCRT_VKEY_LEFT			0x25	/**< @brief	Left arrow key. */
#define FSCRT_VKEY_UP			0x26	/**< @brief	Up arrow key. */
#define FSCRT_VKEY_RIGHT		0x27	/**< @brief	Right arrow key. */
#define FSCRT_VKEY_DOWN			0x28	/**< @brief	Down arrow key. */
#define FSCRT_VKEY_PRINT		0x2A	/**< @brief	Print key. */
#define FSCRT_VKEY_SNAPSHOT		0x2C	/**< @brief	Print Screen key. */
#define FSCRT_VKEY_INSERT		0x2D	/**< @brief	Insert key. */
#define FSCRT_VKEY_DELETE		0x2E	/**< @brief	Delete key. */
#define FSCRT_VKEY_HELP			0x2F	/**< @brief	Help key. */
#define FSCRT_VKEY_0			0x30	/**< @brief	0 key. */
#define FSCRT_VKEY_1			0x31	/**< @brief	1 key. */
#define FSCRT_VKEY_2			0x32	/**< @brief	2 key. */
#define FSCRT_VKEY_3			0x33	/**< @brief	3 key. */
#define FSCRT_VKEY_4			0x34	/**< @brief	4 key. */
#define FSCRT_VKEY_5			0x35	/**< @brief	5 key. */
#define FSCRT_VKEY_6			0x36	/**< @brief	6 key. */
#define FSCRT_VKEY_7			0x37	/**< @brief	7 key. */
#define FSCRT_VKEY_8			0x38	/**< @brief	8 key. */
#define FSCRT_VKEY_9			0x39	/**< @brief	9 key. */
#define FSCRT_VKEY_A			0x41	/**< @brief	A key. */
#define FSCRT_VKEY_B			0x42	/**< @brief	B key. */
#define FSCRT_VKEY_C			0x43	/**< @brief	C key. */
#define FSCRT_VKEY_D			0x44	/**< @brief	D key. */
#define FSCRT_VKEY_E			0x45	/**< @brief	E key. */
#define FSCRT_VKEY_F			0x46	/**< @brief	F key. */
#define FSCRT_VKEY_G			0x47	/**< @brief	G key. */
#define FSCRT_VKEY_H			0x48	/**< @brief	H key. */
#define FSCRT_VKEY_I			0x49	/**< @brief	I key. */
#define FSCRT_VKEY_J			0x4A	/**< @brief	J key. */
#define FSCRT_VKEY_K			0x4B	/**< @brief	K key. */
#define FSCRT_VKEY_L			0x4C	/**< @brief	L key. */
#define FSCRT_VKEY_M			0x4D	/**< @brief	M key. */
#define FSCRT_VKEY_N			0x4E	/**< @brief	N key. */
#define FSCRT_VKEY_O			0x4F	/**< @brief	O key. */
#define FSCRT_VKEY_P			0x50	/**< @brief	P key. */
#define FSCRT_VKEY_Q			0x51	/**< @brief	Q key. */
#define FSCRT_VKEY_R			0x52	/**< @brief	R key. */
#define FSCRT_VKEY_S			0x53	/**< @brief	S key. */
#define FSCRT_VKEY_T			0x54	/**< @brief	T key. */
#define FSCRT_VKEY_U			0x55	/**< @brief	U key. */
#define FSCRT_VKEY_V			0x56	/**< @brief	V key. */
#define FSCRT_VKEY_W			0x57	/**< @brief	W key. */
#define FSCRT_VKEY_X			0x58	/**< @brief	X key. */
#define FSCRT_VKEY_Y			0x59	/**< @brief	Y key. */
#define FSCRT_VKEY_Z			0x5A	/**< @brief	Z key. */
#define FSCRT_VKEY_NUMPAD0		0x60	/**< @brief	0 key in the numeric keypad. */
#define FSCRT_VKEY_NUMPAD1		0x61	/**< @brief	1 key in the numeric keypad. */
#define FSCRT_VKEY_NUMPAD2		0x62	/**< @brief	2 key in the numeric keypad. */
#define FSCRT_VKEY_NUMPAD3		0x63	/**< @brief	3 key in the numeric keypad. */
#define FSCRT_VKEY_NUMPAD4		0x64	/**< @brief	4 key in the numeric keypad. */
#define FSCRT_VKEY_NUMPAD5		0x65	/**< @brief	5 key in the numeric keypad. */
#define FSCRT_VKEY_NUMPAD6		0x66	/**< @brief	6 key in the numeric keypad. */
#define FSCRT_VKEY_NUMPAD7		0x67	/**< @brief	7 key in the numeric keypad. */
#define FSCRT_VKEY_NUMPAD8		0x68	/**< @brief	8 key in the numeric keypad. */
#define FSCRT_VKEY_NUMPAD9		0x69	/**< @brief	9 key in the numeric keypad. */
#define FSCRT_VKEY_MULTIPLY		0x6A	/**< @brief	Multiply key in the numeric keypad. */
#define FSCRT_VKEY_ADD			0x6B	/**< @brief	Plus key in the numeric keypad. */
#define FSCRT_VKEY_SEPARATOR	0x6C	/**< @brief	Enter key in the numeric keypad. */
#define FSCRT_VKEY_SUBTRACT		0x6D	/**< @brief	Minus key in the numeric keypad. */
#define FSCRT_VKEY_DECIMAL		0x6E	/**< @brief	Dot key in the numeric keypad. */
#define FSCRT_VKEY_DIVIDE		0x6F	/**< @brief	Slash key in the numeric keypad. */
#define FSCRT_VKEY_F1			0x70	/**< @brief	F1 key. */
#define FSCRT_VKEY_F2			0x71	/**< @brief	F2 key. */
#define FSCRT_VKEY_F3			0x72	/**< @brief	F3 key. */
#define FSCRT_VKEY_F4			0x73	/**< @brief	F4 key. */
#define FSCRT_VKEY_F5			0x74	/**< @brief	F5 key. */
#define FSCRT_VKEY_F6			0x75	/**< @brief	F6 key. */
#define FSCRT_VKEY_F7			0x76	/**< @brief	F7 key. */
#define FSCRT_VKEY_F8			0x77	/**< @brief	F8 key. */
#define FSCRT_VKEY_F9			0x78	/**< @brief	F9 key. */
#define FSCRT_VKEY_F10			0x79	/**< @brief	F10 key. */
#define FSCRT_VKEY_F11			0x7A	/**< @brief	F11 key. */
#define FSCRT_VKEY_F12			0x7B	/**< @brief	F12 key. */

/**@}*/

#endif /* _FSCRT_DEF_VKEY_ */

#ifndef _FSCRT_DEF_NOTEFLAG_
#define _FSCRT_DEF_NOTEFLAG_
/**
 * @name 	Macro Definitions for Key Flags
 */
/**@{*/

#define FSCRT_NOTEFLAG_SHIFTKEY				0x0001	/**< @brief	The flag of the event: the "Shift" key. */
#define FSCRT_NOTEFLAG_CONTROLKEY			0x0002	/**< @brief	The flag of the event: the "Ctrl" key. */
#define FSCRT_NOTEFLAG_ALTKEY				0x0004	/**< @brief	The flag of the event: the "Alt" key. */
#define FSCRT_NOTEFLAG_METAKEY				0x0008	/**< @brief	The flag of the event: meta key. */
#define FSCRT_NOTEFLAG_KEYPAD				0x0010	/**< @brief	The flag of the event: key pad. */
#define FSCRT_NOTEFLAG_AUTOREPEAT			0x0020	/**< @brief	The flag of the event: auto repeat. */
#define FSCRT_NOTEFLAG_LEFTBUTTONDOWN		0x0040	/**< @brief	The flag of the event: the left button of the mouse is down. */
#define FSCRT_NOTEFLAG_MIDDLEBUTTONDOWN		0x0080	/**< @brief	The flag of the event: the middle button of the mouse is down. */
#define FSCRT_NOTEFLAG_RIGHTBUTTONDOWN		0x0100	/**< @brief	The flag of the event: the right button of the mouse is down. */

/**@}*/
#endif /* _FSCRT_DEF_NOTEFLAG_ */

#ifndef _FSCRT_DEF_NOTETYPE_
#define _FSCRT_DEF_NOTETYPE_
/**
 * @name 	Macro Definitions for Note Type
 */
/**@{*/

#define FSCRT_NOTETYPE_KEYDOWN			1	/**< @brief	The key command event: key down. */
#define FSCRT_NOTETYPE_KEYUP			2	/**< @brief	The key command event: key up. */
#define FSCRT_NOTETYPE_CHAR				3	/**< @brief	The key command event: char. */
#define FSCRT_NOTETYPE_LBUTTONDOWN		4	/**< @brief	The mouse command event: the left button of the mouse is down. */
#define FSCRT_NOTETYPE_LBUTTONUP		5	/**< @brief	The mouse command event: the left button of the mouse is up. */
#define FSCRT_NOTETYPE_LBUTTONDBLCLK	6	/**< @brief	The mouse command event: the left button of the mouse is double clicked. */
#define FSCRT_NOTETYPE_RBUTTONDOWN		7	/**< @brief	The mouse command event: the right button of the mouse is down. */
#define FSCRT_NOTETYPE_RBUTTONUP		8	/**< @brief	The mouse command event: the right button of the mouse is up. */
#define FSCRT_NOTETYPE_RBUTTONDBLCLK	9	/**< @brief	The mouse command event: the right button of the mouse is double clicked. */
#define FSCRT_NOTETYPE_MBUTTONDOWN		10	/**< @brief	The mouse command event: the middle button of the mouse is down. */
#define FSCRT_NOTETYPE_MBUTTONUP		11	/**< @brief	The mouse command event: the middle button of the mouse is up. */
#define FSCRT_NOTETYPE_MBUTTONDBLCLK	12	/**< @brief	The mouse command event: the middle button of the mouse is double clicked. */
#define FSCRT_NOTETYPE_MOUSEMOVE		13	/**< @brief	The mouse command event: mouse move. */
#define FSCRT_NOTETYPE_MOUSEENTER		14	/**< @brief	The mouse command event: mouse enter. */
#define FSCRT_NOTETYPE_MOUSEHOVER		15	/**< @brief	The mouse command event: mouse hover. */
#define FSCRT_NOTETYPE_MOUSELEAVE		16	/**< @brief	The mouse command event: mouse leave. */
#define FSCRT_NOTETYPE_MOUSEWHEEL		17	/**< @brief	The mouse command event: mouse wheel. */
#define FSCRT_NOTETYPE_PAGEUP			18	/**< @brief	The page up event. */
#define FSCRT_NOTETYPE_PAGEDOWN			19	/**< @brief	The page down event. */
#define FSCRT_NOTETYPE_KILLFOCUS		20	/**< @brief	Force to kill the focus of a field. */

/**@}*/
#endif /* _FSCRT_DEF_NOTETYPE_*/

#ifndef _FSCRT_CURSOR_TYPE_
#define _FSCRT_CURSOR_TYPE_
/**
 * @name 	Macro Definitions for Cursor Type
 */
/**@{*/

#define FSCRT_CURSOR_ARROW	0	/**< @brief	Cursor Type: Arrow. */
#define FSCRT_CURSOR_NESW	1	/**< @brief	Cursor Type: NESW. */
#define FSCRT_CURSOR_NWSE	2	/**< @brief	Cursor Type: NWSE. */
#define FSCRT_CURSOR_VBEAM	3	/**< @brief	Cursor Type: Vertical Beam. */
#define FSCRT_CURSOR_HBEAM	4	/**< @brief	Cursor Type: Horizontal Beam. */
#define FSCRT_CURSOR_HAND	5	/**< @brief	Cursor Type: Hand. */

/**@}*/
#endif /* _FSCRT_CURSOR_TYPE_*/

#ifndef _FSCRT_DEF_NOTEDATA_KEY_
#define _FSCRT_DEF_NOTEDATA_KEY_

/**
 * @brief	Structure for note key
 * @note	This structure is used for passing key information of note.
 */
typedef struct _FSCRT_NOTEDATA_KEY
{
	/** @brief	Key flags. Please refer to macro definitions <b>FSCRT_NOTEFLAG_XXX</b> and this should be one of these macros. */
	FS_DWORD	flags;
	/** @brief	Key code. Please refer to macro definitions <b>FSCRT_VKEY_XXX</b> and this can be one or combination of these macros. */
	FS_DWORD	code;
} FSCRT_NOTEDATA_KEY;

#endif /* _FSCRT_DEF_NOTEDATA_KEY_ */

#ifndef _FSCRT_DEF_NOTEDATA_CHAR_
#define _FSCRT_DEF_NOTEDATA_CHAR_

/**
 * @brief	Structure for character code
 * @note	This structure is used for passing code information of note.
 */
typedef struct _FSCRT_NOTEDATA_CHAR
{
	/** @brief	Flags. Please refer to macro definitions <b>FSCRT_NOTEFLAG_XXX</b> and this should be one of these macros. */
	FS_DWORD	flags;
	/** @brief	Char code. It should be encoded as a UTF16-LE character code. */
	FS_DWORD	code;
} FSCRT_NOTEDATA_CHAR;

#endif /* _FSCRT_DEF_NOTEDATA_CHAR_ */

#ifndef _FSCRT_DEF_NOTEDATA_MOUSE_
#define _FSCRT_DEF_NOTEDATA_MOUSE_

/**
 * @brief	Structure for note mouse
 * @note	This structure is used for passing mouse information of note.
 */
typedef struct _FSCRT_NOTEDATA_MOUSE
{
	/**
	 * @brief	The note flags. Please refer to macro definitions <b>FSCRT_NOTEFLAG_XXX</b> and this should be one of these macros. 
	 */
	FS_DWORD	flags;	
	FS_FLOAT	x;		/**< @brief	Mouse position. */
	FS_FLOAT	y;		/**< @brief	Mouse position. */
	FS_FLOAT	deltaX;	/**< @brief	Mouse wheel. */
	FS_FLOAT	deltaY;	/**< @brief	Mouse wheel. */
} FSCRT_NOTEDATA_MOUSE;

#endif /* _FSCRT_DEF_NOTEDATA_MOUSE_ */


#ifndef _FSCRT_DEF_CALLBACK_TIMER_
#define _FSCRT_DEF_CALLBACK_TIMER_

/**
 * @brief	Declares a pointer type for the callback function for the FSPDF_FORMFILL_INFO::SetTimer method.
 *
 * @param[in] timer			Identifier of a timer.
 *
 * @return None.
 */
typedef void		(*FSCRT_CALLBACK_TIMER)(FS_INT32 timer);

#endif /* _FSCRT_DEF_CALLBACK_TIMER_ */


#ifndef _FSCRT_DEF_EVENT_
#define _FSCRT_DEF_EVENT_
/**
 * @name 	Macro definitions for Event Type
 */
/**@{*/

#define FSCRT_EVENT_KEYDOWN					FSCRT_NOTETYPE_KEYDOWN			/**< @brief	The key command event: key down. */
#define FSCRT_EVENT_KEYUP					FSCRT_NOTETYPE_KEYUP			/**< @brief	The key command event: key up. */
#define FSCRT_EVENT_CHAR					FSCRT_NOTETYPE_CHAR				/**< @brief	The key command event: char. */
#define FSCRT_EVENT_LBUTTONDOWN				FSCRT_NOTETYPE_LBUTTONDOWN		/**< @brief	The mouse command event: the left button of the mouse is down. */
#define FSCRT_EVENT_LBUTTONUP				FSCRT_NOTETYPE_LBUTTONUP		/**< @brief	The mouse command event: the left button of the mouse is up. */
#define FSCRT_EVENT_LBUTTONDBLCLK			FSCRT_NOTETYPE_LBUTTONDBLCLK	/**< @brief	The mouse command event: the left button of the mouse is double clicked. */
#define FSCRT_EVENT_RBUTTONDOWN				FSCRT_NOTETYPE_RBUTTONDOWN		/**< @brief	The mouse command event: the right button of the mouse is down. */
#define FSCRT_EVENT_RBUTTONUP				FSCRT_NOTETYPE_RBUTTONUP		/**< @brief	The mouse command event: the right button of the mouse is up. */
#define FSCRT_EVENT_RBUTTONDBLCLK			FSCRT_NOTETYPE_RBUTTONDBLCLK	/**< @brief	The mouse command event: the right button of the mouse is double clicked. */
#define FSCRT_EVENT_MBUTTONDOWN				FSCRT_NOTETYPE_MBUTTONDOWN		/**< @brief	The mouse command event: the middle button of the mouse is down. */
#define FSCRT_EVENT_MBUTTONUP				FSCRT_NOTETYPE_MBUTTONUP		/**< @brief	The mouse command event: the middle button of the mouse is up. */
#define FSCRT_EVENT_MBUTTONDBLCLK			FSCRT_NOTETYPE_MBUTTONDBLCLK	/**< @brief	The mouse command event: the middle button of the mouse is double clicked. */
#define FSCRT_EVENT_MOUSEMOVE				FSCRT_NOTETYPE_MOUSEMOVE		/**< @brief	The mouse command event: mouse move. */
#define FSCRT_EVENT_MOUSEENTER				FSCRT_NOTETYPE_MOUSEENTER		/**< @brief	The mouse command event: mouse enter. */
#define FSCRT_EVENT_MOUSEHOVER				FSCRT_NOTETYPE_MOUSEHOVER		/**< @brief	The mouse command event: mouse hover. */
#define FSCRT_EVENT_MOUSELEAVE				FSCRT_NOTETYPE_MOUSELEAVE		/**< @brief	The mouse command event: mouse leave. */
#define FSCRT_EVENT_MOUSEWHEEL				FSCRT_NOTETYPE_MOUSEWHEEL		/**< @brief	The mouse command event: mouse wheel. */
#define FSCRT_EVENT_PAGEUP					FSCRT_NOTETYPE_PAGEUP			/**< @brief	The page up event. */
#define FSCRT_EVENT_PAGEDOWN				FSCRT_NOTETYPE_PAGEDOWN			/**< @brief	The page down event. */
#define	FSCRT_EVENT_KILLFOCUS				FSCRT_NOTETYPE_KILLFOCUS		/**< @brief	Force to kill the focus of a field. */

/**@}*/
#endif /* _FSCRT_DEF_EVENT_ */

/******************************************************************************/
/* PSI event definition                                                       */
/******************************************************************************/
#ifndef _FSCRT_DEF_EVENT_PSI_
#define _FSCRT_DEF_EVENT_PSI_

/** @brief	The psi event of invalidating a rectangle pointer to the ::FSCRT_RECTF object. */
#define	FSCRT_EVENT_PSI_INVALIDATE			((FSCRT_OBJECTTYPE_PSI << 16) | 0)

#endif /* _FSCRT_DEF_EVENT_PSI_ */

/******************************************************************************/
/* Application definitions                                                    */
/*                                                                            */
/* Application handler                                                        */
/******************************************************************************/
#ifndef _FSCRT_DEF_APPHANDLER_
#define _FSCRT_DEF_APPHANDLER_

/**
 * @brief	Structure for a application handler.
 *
 * @note	This is a handler implemented by callers. It's used to expand functions of Foxit PDF SDK, or get events from Foxit PDF SDK.<br>
 *			It's specially designed for higher-level control in Foxit PDF SDK.
 */
typedef struct _FSCRT_APPHANDLER
{
	/**
	 * @brief	User-defined data.
	 *
	 * @note	Callers can use this field to track control.
	 */
	FS_LPVOID	clientData;

	/**
	 * @brief	Callback functions to expand functions of Foxit PDF SDK, unsupported now.
	 *
	 * @param[in]	clientData 		Pointer to user-defined data.
	 * @param[in]	document		Handle to a <b>FSCRT_DOCUMENT</b> object which is a document object.
	 * @param[in]	function		Function ID to expand functions of Foxit PDF SDK.
	 * @param[in]	parameters		Pointer to parameter list for functions. It could be <b>NULL</b> if count equals zero.
	 * @param[in]	count			Count of the parameter <i>parameters</i>, it could be zero if the expanded functions have no parameters.
	 * @param[out]	ret				Pointer to a ::FSCRT_VAR structure that receives the return value of function. It shall not be <b>NULL</b>.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_PARAM if the parameter <i>ret</i> is <b>NULL</b>.<br>
	 *			::FSCRT_ERRCODE_UNSUPPORTED if the expandeding function is not supported by applications.
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*CallFunction)(FS_LPVOID clientData, FSCRT_DOCUMENT document, FS_INT32 function, FSCRT_VAR* parameters, FS_INT32 count, FSCRT_VAR* ret);

	/**
	 * @brief	Callback functions to events from Foxit PDF SDK.
	 *
	 * @details	Data type of the parameter <i>senderObject</i> depends on the parameter <i>senderObjectType</i>, as follows:<br>
	 *			Format: object type - object data type
	 *			<ul>
	 *			<li>::FSCRT_OBJECTTYPE_PSI - <b>FSCRT_PSI</b></li>
	 *			</ul>
	 *
	 * @param[in]	clientData 			Pointer to user-defined data.
	 * @param[in]	senderObject		Pointer to a sender object, related to the parameter <i>senderObjectType</i>.
	 * @param[in]	senderObjectType	Object type of the parameter <i>senderObject</i>. Currently available value is ::FSCRT_OBJECTTYPE_PSI.
	 * @param[in]	eventType			The event type of parameter <i>eventData</i>. Currently available value is ::FSCRT_EVENT_PSI_INVALIDATE.
	 * @param[in]	eventData			The event data, related to the parameter <i>eventType</i>.
	 *
	 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
	 *			::FSCRT_ERRCODE_PARAM if the parameter <i>senderObject</i> or <i>eventData</i> is <b>NULL</b>.<br>
	 *			::FSCRT_ERRCODE_UNSUPPORTED if the expanding function is not supported by applications.
	 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
	 */
	FS_RESULT	(*OnEvent)(FS_LPVOID clientData, FS_LPVOID senderObject, FS_DWORD senderObjectType, FS_DWORD eventType, FS_LPVOID eventData);

	/**
	 * @brief	Callback functions indicate that Foxit PDF SDK is out of memory.
	 *
	 * @param[in]	clientData			Pointer to the user-defined data.
	 *
	 * @return	None.
	 *
	 * @note	This function is called when memory is insufficient.
	 *			Typically applications will get a return value ::FSCRT_ERRCODE_OUTOFMEMORY after this callback.
	 */
	void		(*OnOutOfMemory)(FS_LPVOID clientData);

	/**
	 * @brief	Callback functions to recover the previous operation when Foxit PDF SDK is out of memory.
	 *
	 * @details	Data type of the parameter <i>senderObject</i> depends on the parameter <i>senderObjectType</i>, as following:<br>
	 *			Format: object type - object data type
	 *			<ul>
	 *			<li>::FSCRT_OBJECTTYPE_DOCUMENT - <b>FSCRT_DOCUMENT</b></li>
	 *			</ul>
	 *
	 * @param[in]	clientData			Pointer to user-defined data.
	 * @param[in]	senderObject		Pointer to a sender object, related to the parameter <i>senderObjectType</i>. Valid values are mentioned in details part.
	 * @param[in]	senderObjectType	Object type of the parameter <i>senderObject</i>. Valid values are mentioned in details part.
	 *
	 * @return	None.
	 *
	 * @note	This function will be called when Foxit PDF SDK meets error but can't recover.
	 *			Typically applications will get a return value ::FSCRT_ERRCODE_UNRECOVERABLE after this callback.
	 */
	FS_RESULT		(*OnRecover)(FS_LPVOID clientData, FS_LPVOID senderObject, FS_DWORD senderObjectType);
} FSCRT_APPHANDLER;

#endif /* _FSCRT_DEF_APPHANDLER_ */

/**
 * @brief	Set a handler to Foxit PDF SDK library to support extension functions and events.
 *
 * @param[in]	appHandler			Pointer to a valid ::FSCRT_APPHANDLER structure to register a handler to library.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if the parameter <i>appHandler</i> is a <b>NULL</b> pointer.<br>
 * 			::FSCRT_ERRCODE_HANDLER if any callback function in the parameter <i>appHandler</i> is <b>NULL</b>.<br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or invalid memory access.<br>
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
FS_RESULT	FSCRT_Library_SetAppHandler(FSCRT_APPHANDLER* appHandler);

/**
 * @brief	Trigger the user operation for recovery from out of memory. Only used for OOM handling.
 *
 * @details	OOM handling is only for mobile platforms, not for server or desktop.<br>
 *			Functions in Foxit PDF SDK may return one of following values as a result: ::FSCRT_ERRCODE_MEMORYREBUILT, ::FSCRT_ERRCODE_UNRECOVERABLE, ::FSCRT_ERRCODE_ROLLBACK.<br>
 *			When receiving one of these value as a result, application should ensure to set a valid ::FSCRT_APPHANDLER object with FSCRT_APPHANDLER::OnRecover available by function ::FSCRT_Library_SetAppHandler 
 *			and call this function to do recovery.<br>
 *			For more details about handling OOM , please refer to the document "Robust PDF Applications with Limited Memory".<br>
 *			If this function returns one of result value mentioned above, it means the OOM situation cannot be recovered 
 *			and application doesn't need to call ::FSCRT_Library_OOMRecover or ::FSCRT_Library_TriggerRecover to try recovery again.<br>
 *			Data type of parameter <i>senderObject</i> depends on parameter <i>senderObjectType</i>, as following:<br>
 *			Format: object type - object data type
 *			<ul>
 *			<li>::FSCRT_OBJECTTYPE_DOCUMENT - <b>FSCRT_DOCUMENT</b>, representing PDF Document handle.</li>
 *			</ul> 
 *
 * @param[in]	senderObject		Pointer to a sender object, relative to parameter <i>senderObjectType</i>. Valid values are mentioned in details part.
 * @param[in]	senderObjectType	Object type of parameter <i>senderObject</i>. Valid values are mentioned in details part.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>senderObject</i> is a <b>NULL</b> pointer, or the parameter <i>senderObjectType</i> isn't equal with FSCRT_OBJECTTYPE_DOCUMENT. <br>
 * 			::FSCRT_ERRCODE_OUTOFMEMORY if there is not enough memory or if the memory access is wrong.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 */
FS_RESULT	FSCRT_Library_OOMRecover(FS_LPVOID senderObject, FS_DWORD senderObjectType);

/**
 * @brief	Trigger a recovery for handle of non-PDF module.  Only used for OOM handling.
 *
 * @details	OOM handling is only for mobile platforms, not for server or desktop.<br>
 *			When OOM occurs in modules which is independent of PDF module, application should call this function to recover handle related to these modules separately 
 *			if application wants to use handle of these modules to interact with PDF module.
 *			If this function returns ::FSCRT_ERRCODE_UNRECOVERABLE as a result, it means the OOM situation cannot be recovered 
 *			and application doesn't need to call ::FSCRT_Library_OOMRecover or ::FSCRT_Library_TriggerRecover to try recovery again.<br>
 *			Data type of parameter <i>senderObject</i> depends on parameter <i>senderObjectType</i>, as following:<br>
 *			Format: object type - object data type
 *			<ul>
 *			<li>::FSCRT_OBJECTTYPE_DOCUMENT - <b>FSCRT_DOCUMENT</b></li>
 *			<li>::FSCRT_OBJECTTYPE_PAGE - <b>FSCRT_PAGE</b></li>
 *			</ul>
 *
 * @param[in]	senderObject		Pointer to a sender object, relative to parameter <i>senderObjectType</i>. Valid values are mentioned in details part.
 * @param[in]	senderObjectType	Object type of parameter <i>senderObject</i>. Valid values are mentioned in details part.
 *
 * @return	::FSCRT_ERRCODE_SUCCESS for success.<br>
 *			::FSCRT_ERRCODE_PARAM if parameter <i>senderObject</i> is a <b>NULL</b> pointer or <i>senderObjectType</i> is not ::FSCRT_OBJECTTYPE_DOCUMENT or ::FSCRT_OBJECTTYPE_PAGE.<br>
 * 			::FSCRT_ERRCODE_UNRECOVERABLE if the function finds an unrecoverable error internally.<br>
 *			For more error codes, please refer to macro definitions <b>FSCRT_ERRCODE_XXX</b>.
 *
 * @attention	<b>Thread Safety</b>: this function is not thread safe. Do not call it to process same objects between multi-threads, 
 *				or the application should maintain thread safety when it needs to process same objects under multi-threaded environments.<br>
 */
FS_RESULT	FSCRT_Library_TriggerRecover(FS_LPVOID senderObject, FS_DWORD senderObjectType);

#ifdef __cplusplus
};
#endif

/**@}*/ /* group FSAPP */

#endif /* _FSCRT_APP_R_H_ */

