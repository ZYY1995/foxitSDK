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
 * @file	fsdk.h
 * @brief	This header file includes all related header files in SDK.
 * @details	For application, just include this header file.
 *
 * @note	If you want to purchase Foxit PDF SDK license and use ANY features, please request for enabling modules explicitly.
 */

#ifndef _FSDK_H_
#define _FSDK_H_

#ifndef _FSCRT_BASE_R_H_
	#include "fs_base_r.h"
#endif
#ifndef _FSCRT_CODEC_R_H_
	#include "fs_codec_r.h"
#endif
#ifndef _FSCRT_APP_R_H_
	#include "fs_app_r.h"
#endif
#ifndef _FSCRT_IMAGE_R_H_
	#include "fs_image_r.h"
#endif
#ifndef _FSCRT_IMAGE_W_H_
	#include "fs_image_w.h"
#endif
#ifndef _FSCRT_RENDERER_R_H_
	#include "fs_renderer_r.h"
#endif
#if (defined(_WIN32) || defined(_WIN64))
	#if !defined(_INC_WINAPIFAMILY) || WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
		#ifndef _FSCRT_RENDERER_WINDOWS_R_H_
			#include "windows/fs_renderer_windows_r.h"
		#endif 
	#endif //!defined(_INC_WINAPIFAMILY) || WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#endif
#if defined(__APPLE__)
	#ifndef _FSCRT_RENDERER_APPLE_R_H_
		#include "apple/fs_renderer_apple_r.h"
	#endif
#endif
#ifndef _FSCRT_BARCODE_W_H_
	#include "fs_barcode_w.h"
#endif

#ifndef _FSPDF_H_
	#include "pdf/fpdf.h"
#endif

#ifndef _FSCRT_PSI_W_H_
	#include "fs_psi_w.h"
#endif

#endif /* _FSDK_H_ */
