﻿// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#define WIN32_LEAN_AND_MEAN

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _AFX_ALL_WARNINGS
#define _AFX_PORTABLE
#define _FORCENAMELESSUNION
#define _AFX_NO_DAO_SUPPORT
#define _AFX_NO_DHTML_SUPPORT
#define _AFX_NO_OLEDB_SUPPORT
#define _AFX_NO_RICHEDIT_SUPPORT

#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS

#include <afxwin.h>
#include <afxext.h>
#include <afxdisp.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <string>

#include "..\..\controls\MyButton.h"
#include "..\..\controls\MyEdit.h"
#include "..\..\controls\MyProgressCtrl.h"

#include "..\..\utilities\Download.h"
#include "..\..\utilities\Thread.h"
