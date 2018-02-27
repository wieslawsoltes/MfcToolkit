// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#define _AFXDLL
#include <afxwin.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif

#include <string>
#include "LanguageContext.h"

namespace lang
{
    class CLanguageHelper
    {
    public:
        CLanguageContext * pContext;
    public:
        CLanguageHelper(CLanguageContext *pContext) : pContext(pContext)
        {
        }
    public:
        void SetColumnText(CListCtrl& listCtrl, int nCol, int nKey)
        {
            std::wstring rValue;
            if (this->pContext->LookupString(nKey, rValue))
            {
                LVCOLUMN lvCol;
                ::ZeroMemory((void *)&lvCol, sizeof(LVCOLUMN));

                lvCol.mask = LVCF_TEXT;
                listCtrl.GetColumn(nCol, &lvCol);

                lvCol.pszText = (LPTSTR)(LPCTSTR)rValue.c_str();
                listCtrl.SetColumn(nCol, &lvCol);
            }
        }
        void SetMenuPopupText(CMenu *hMenu, UINT nPosition, int nKey)
        {
            std::wstring rValue;
            if (this->pContext->LookupString(nKey, rValue))
            {
                hMenu->ModifyMenu(nPosition, MF_STRING | MF_BYPOSITION, nPosition, rValue.c_str());
            }
        }
        void SetMenuItemText(CMenu *hMenu, UINT nID, int nKey)
        {
            std::wstring rValue;
            if (this->pContext->LookupString(nKey, rValue))
            {
                UINT nState = hMenu->GetMenuState(nID, MF_BYCOMMAND);
                hMenu->ModifyMenu(nID, MF_BYCOMMAND, nID, rValue.c_str());
                if (nState & MF_CHECKED)
                    hMenu->CheckMenuItem(nID, MF_CHECKED | MF_BYCOMMAND);
                else
                    hMenu->CheckMenuItem(nID, MF_UNCHECKED | MF_BYCOMMAND);
            }
        }
        void SetWndText(CWnd *hWnd, int nKey)
        {
            std::wstring rValue;
            if (this->pContext->LookupString(nKey, rValue))
            {
                hWnd->SetWindowText(rValue.c_str());
            }
        }
        void SetItemText(CWnd *hWnd, UINT nID, int nKey)
        {
            std::wstring rValue;
            if (this->pContext->LookupString(nKey, rValue))
            {
                hWnd->GetDlgItem(nID)->SetWindowText(rValue.c_str());
            }
        }
    };
}
