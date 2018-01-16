// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <afxstr.h>
#include <afxtempl.h>
#include "tinyxml2\tinyxml2.h" // https://github.com/leethomason/tinyxml2
#include "utilities\UnicodeUtf8.h"
#include "utilities\Utf8String.h"

typedef tinyxml2::XMLNode XmlNode;
typedef tinyxml2::XMLElement XmlElement;
typedef tinyxml2::XMLDocument XmlDocumnent;

class XmlDoc
{
protected:
    XmlDocumnent & m_Document;
public:
    XmlDoc(XmlDocumnent &doc) : m_Document(doc)
    {
    }
    virtual ~XmlDoc()
    {
    }
public:
    static const char* GetRootName(XmlDocumnent &doc)
    {
        auto root = doc.RootElement();
        if (root != nullptr)
            return root->Name();
        return nullptr;
    }
public:
    static void Create(XmlDocumnent & doc)
    {
        doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
    }
    static bool Open(const CString szFileName, XmlDocumnent & doc)
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
    static bool Save(const CString szFileName, XmlDocumnent & doc)
    {
        CStdioFile fp;
        if (fp.Open(szFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText) == TRUE)
        {
            fputc(0xefU, fp.m_pStream);
            fputc(0xbbU, fp.m_pStream);
            fputc(0xbfU, fp.m_pStream);
            tinyxml2::XMLPrinter printer(fp.m_pStream);
            doc.Print(&printer);
            fp.Close();
            return true;
        }
        return false;
    }
public:
    const LPCTSTR m_True = _T("true");
    const LPCTSTR m_False = _T("false");
public:
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
public:
    void GetAttributeValue(const XmlElement *element, const char *name, CString *value)
    {
        const char *pszResult = element->Attribute(name);
        if (pszResult != nullptr)
        {
            (*value) = ToCString(pszResult);
        }
    }
    void GetAttributeValue(const XmlElement *element, const char *name, int *value)
    {
        const char *pszResult = element->Attribute(name);
        if (pszResult != nullptr)
        {
            (*value) = ToInt(pszResult);
        }
    }
    void GetAttributeValue(const XmlElement *element, const char *name, bool *value)
    {
        const char *pszResult = element->Attribute(name);
        if (pszResult != nullptr)
        {
            (*value) = ToBool(pszResult);
        }
    }
public:
    void SetAttributeValue(XmlElement *element, const char *name, const CString& value)
    {
        element->SetAttribute(name, CUtf8String(value).m_Result);
    }
    void SetAttributeValue(XmlElement *element, const char *name, const int &value)
    {
        element->SetAttribute(name, CUtf8String(ToCString(value)).m_Result);
    }
    void SetAttributeValue(XmlElement *element, const char *name, const bool &value)
    {
        element->SetAttribute(name, CUtf8String(ToCString(value)).m_Result);
    }
public:
    void GetChildValue(const XmlElement *parent, const char *name, CString *value)
    {
        auto element = parent->FirstChildElement(name);
        if (element != nullptr)
        {
            (*value) = ToCString(element->GetText());
        }
    }
    void GetChildValue(const XmlElement *parent, const char *name, int *value)
    {
        auto element = parent->FirstChildElement(name);
        if (element != nullptr)
        {
            (*value) = ToInt(element->GetText());
        }
    }
    void GetChildValue(const XmlElement *parent, const char *name, bool *value)
    {
        auto element = parent->FirstChildElement(name);
        if (element != nullptr)
        {
            (*value) = ToBool(element->GetText());
        }
    }
public:
    void SetChildValue(XmlElement *parent, const char *name, const CString& value)
    {
        auto element = m_Document.NewElement(name);
        element->LinkEndChild(m_Document.NewText(CUtf8String(value).m_Result));
        parent->LinkEndChild(element);
    }
    void SetChildValue(XmlElement *parent, const char *name, const int &value)
    {
        auto element = m_Document.NewElement(name);
        element->LinkEndChild(m_Document.NewText(CUtf8String(ToCString(value)).m_Result));
        parent->LinkEndChild(element);
    }
    void SetChildValue(XmlElement *parent, const char *name, const bool &value)
    {
        auto element = m_Document.NewElement(name);
        element->LinkEndChild(m_Document.NewText(CUtf8String(ToCString(value)).m_Result));
        parent->LinkEndChild(element);
    }
public:
    XmlElement * NewElement(const char *name)
    {
        return m_Document.NewElement(name);
    }
    XmlElement* FirstChildElement(const char *name)
    {
        return m_Document.FirstChildElement(name);
    }
    XmlNode* LinkEndChild(XmlNode* node)
    {
        return m_Document.LinkEndChild(node);
    }
public:
    void Create()
    {
        XmlDoc::Create(m_Document);
    }
    bool Open(const CString szFileName)
    {
        return XmlDoc::Open(szFileName, m_Document);
    }
    bool Save(const CString szFileName)
    {
        return XmlDoc::Save(szFileName, m_Document);
    }
};
