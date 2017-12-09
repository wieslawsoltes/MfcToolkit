// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <afxstr.h>
#include <afxtempl.h>
#include "tinyxml2\tinyxml2.h" // https://github.com/leethomason/tinyxml2
#include "utilities\UnicodeUtf8.h"
#include "utilities\Utf8String.h"

typedef tinyxml2::XMLElement XmlElement;
typedef tinyxml2::XMLDocument XmlDocumnent;

class XmlBase
{
    XmlDocumnent doc;
public:
    const unsigned char TIXML_UTF_LEAD_0 = 0xefU;
    const unsigned char TIXML_UTF_LEAD_1 = 0xbbU;
    const unsigned char TIXML_UTF_LEAD_2 = 0xbfU;
    const char *m_Utf8DocumentDeclaration = "xml version=\"1.0\" encoding=\"UTF-8\"";
public:
    XmlBase()
    {
    }
    virtual ~XmlBase()
    {
    }
private:
    const LPCTSTR m_True = _T("true");
    const LPCTSTR m_False = _T("false");
protected:
#ifdef _UNICODE
    CString ToCString(const char *pszUtf8)
    {
        if (pszUtf8 == nullptr)
            return _T("");
        if (strlen(pszUtf8) == 0)
            return _T("");
        wchar_t *pszUnicode = MakeUnicodeString((unsigned char *)pszUtf8);
        CString szBuff = pszUnicode;
        free(pszUnicode);
        return szBuff;
    }
#else
    CString ToCString(const char *pszUtf8)
    {
        if (pszUtf8 == nullptr)
            return _T("");
        if (strlen(pszUtf8) == 0)
            return _T("");
        char *pszAnsi;
        Utf8Decode(pszUtf8, &pszAnsi);
        CString szBuff = pszAnsi;
        free(pszAnsi);
        return szBuff;
    }
#endif
    bool ToBool(const char *pszUtf8)
    {
        return ToCString(pszUtf8).CompareNoCase(m_True) == 0;
    }
    int ToInt(const char *pszUtf8)
    {
        return _tstoi(ToCString(pszUtf8));
    }
    CString ToCString(const int nValue)
    {
        CString rValue;
        rValue.Format(_T("%d\0"), nValue);
        return rValue;
    }
    CString ToCString(const bool bValue)
    {
        CString rValue;
        rValue.Format(_T("%s\0"), bValue ? m_True : m_False);
        return rValue;
    }
protected:
    void GetAttributeValue(XmlElement *element, const char *name, CString *value)
    {
        const char *pszResult = element->Attribute(name);
        if (pszResult != NULL)
        {
            (*value) = ToCString(pszResult);
        }
    }
    void GetAttributeValue(XmlElement *element, const char *name, int *value)
    {
        const char *pszResult = element->Attribute(name);
        if (pszResult != NULL)
        {
            (*value) = ToInt(pszResult);
        }
    }
    void GetAttributeValue(XmlElement *element, const char *name, bool *value)
    {
        const char *pszResult = element->Attribute(name);
        if (pszResult != NULL)
        {
            (*value) = ToBool(pszResult);
        }
    }
protected:
    void SetAttributeValue(XmlElement *element, const char *name, CString& value)
    {
        element->SetAttribute(name, CUtf8String(value).m_Result);
    }
    void SetAttributeValue(XmlElement *element, const char *name, int &value)
    {
        element->SetAttribute(name, CUtf8String(ToCString(value)).m_Result);
    }
    void SetAttributeValue(XmlElement *element, const char *name, bool &value)
    {
        element->SetAttribute(name, CUtf8String(ToCString(value)).m_Result);
    }
protected:
    void GetChildValue(XmlElement *parent, const char *name, CString *value)
    {
        auto element = parent->FirstChildElement(name);
        if (element != NULL)
        {
            (*value) = ToCString(element->GetText());
        }
    }
    void GetChildValue(XmlElement *parent, const char *name, int *value)
    {
        auto element = parent->FirstChildElement(name);
        if (element != NULL)
        {
            (*value) = ToInt(element->GetText());
        }
    }
    void GetChildValue(XmlElement *parent, const char *name, bool *value)
    {
        auto element = parent->FirstChildElement(name);
        if (element != NULL)
        {
            (*value) = ToBool(element->GetText());
        }
    }
protected:
    void SetChildValue(XmlElement *parent, const char *name, CString& value)
    {
        auto element = doc.NewElement(name);
        element->LinkEndChild(doc.NewText(CUtf8String(value).m_Result));
        parent->LinkEndChild(element);
    }
    void SetChildValue(XmlElement *parent, const char *name, int &value)
    {
        auto element = doc.NewElement(name);
        element->LinkEndChild(doc.NewText(CUtf8String(ToCString(value)).m_Result));
        parent->LinkEndChild(element);
    }
    void SetChildValue(XmlElement *parent, const char *name, bool &value)
    {
        auto element = doc.NewElement(name);
        element->LinkEndChild(doc.NewText(CUtf8String(ToCString(value)).m_Result));
        parent->LinkEndChild(element);
    }
public:
    void Create()
    {
        doc.LinkEndChild(doc.NewDeclaration(m_Utf8DocumentDeclaration));
    }
    bool Open(CString szFileName)
    {
        CStdioFile fp;
        if (fp.Open(szFileName, CFile::modeRead | CFile::typeBinary) == TRUE)
        {
            auto result = doc.LoadFile(fp.m_pStream);
            fp.Close();
            return result == tinyxml2::XMLError::XML_SUCCESS;
        }
        return false;
    }
    bool Save(CString szFileName)
    {
        CStdioFile fp;
        if (fp.Open(szFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText) == TRUE)
        {
            fputc(TIXML_UTF_LEAD_0, fp.m_pStream);
            fputc(TIXML_UTF_LEAD_1, fp.m_pStream);
            fputc(TIXML_UTF_LEAD_2, fp.m_pStream);
            tinyxml2::XMLPrinter printer(fp.m_pStream);
            doc.Print(&printer);
            fp.Close();
            return true;
        }
        return false;
    }
};
