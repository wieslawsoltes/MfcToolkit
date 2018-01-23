// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <afxstr.h>
#include <afxtempl.h>
#include <string>
#include "tinyxml2\tinyxml2.h" // https://github.com/leethomason/tinyxml2
#include "utilities\Utf8String.h"

namespace xml
{
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
        const std::wstring ToCString(const char *pszUtf8)
        {
            if (pszUtf8 == nullptr)
                return _T("");
            if (strlen(pszUtf8) == 0)
                return _T("");
            std::wstring szUnicode = util::CUtf8String::ToUnicode(pszUtf8);
            return szUnicode;
        }
        bool ToBool(const char *pszUtf8)
        {
            return _tcsicmp(ToCString(pszUtf8).c_str(), m_True) == 0;
        }
        int ToInt(const char *pszUtf8)
        {
            return _tstoi(ToCString(pszUtf8).c_str());
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
        bool GetAttributeValue(const XmlElement *element, const char *name, CString *value)
        {
            const char *pszResult = element->Attribute(name);
            if (pszResult != nullptr)
            {
                (*value) = ToCString(pszResult).c_str();
                return true;
            }
            return false;
        }
        bool GetAttributeValue(const XmlElement *element, const char *name, int *value)
        {
            const char *pszResult = element->Attribute(name);
            if (pszResult != nullptr)
            {
                (*value) = ToInt(pszResult);
                return true;
            }
            return false;
        }
        bool GetAttributeValue(const XmlElement *element, const char *name, bool *value)
        {
            const char *pszResult = element->Attribute(name);
            if (pszResult != nullptr)
            {
                (*value) = ToBool(pszResult);
                return true;
            }
            return false;
        }
    public:
        void SetAttributeValue(XmlElement *element, const char *name, const CString& value)
        {
            element->SetAttribute(name, util::CUtf8String::ToUtf8(value).c_str());
        }
        void SetAttributeValue(XmlElement *element, const char *name, const int &value)
        {
            element->SetAttribute(name, util::CUtf8String::ToUtf8(ToCString(value)).c_str());
        }
        void SetAttributeValue(XmlElement *element, const char *name, const bool &value)
        {
            element->SetAttribute(name, util::CUtf8String::ToUtf8(ToCString(value)).c_str());
        }
    public:
        bool GetChildValue(const XmlElement *parent, const char *name, CString *value)
        {
            auto element = parent->FirstChildElement(name);
            if (element != nullptr)
            {
                (*value) = ToCString(element->GetText()).c_str();
                return true;
            }
            return false;
        }
        bool GetChildValue(const XmlElement *parent, const char *name, int *value)
        {
            auto element = parent->FirstChildElement(name);
            if (element != nullptr)
            {
                (*value) = ToInt(element->GetText());
                return true;
            }
            return false;
        }
        bool GetChildValue(const XmlElement *parent, const char *name, bool *value)
        {
            auto element = parent->FirstChildElement(name);
            if (element != nullptr)
            {
                (*value) = ToBool(element->GetText());
                return true;
            }
            return false;
        }
    public:
        void SetChildValue(XmlElement *parent, const char *name, const CString& value)
        {
            auto element = m_Document.NewElement(name);
            element->LinkEndChild(m_Document.NewText(util::CUtf8String::ToUtf8(value).c_str()));
            parent->LinkEndChild(element);
        }
        void SetChildValue(XmlElement *parent, const char *name, const int &value)
        {
            auto element = m_Document.NewElement(name);
            element->LinkEndChild(m_Document.NewText(util::CUtf8String::ToUtf8(ToCString(value)).c_str()));
            parent->LinkEndChild(element);
        }
        void SetChildValue(XmlElement *parent, const char *name, const bool &value)
        {
            auto element = m_Document.NewElement(name);
            element->LinkEndChild(m_Document.NewText(util::CUtf8String::ToUtf8(ToCString(value)).c_str()));
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
}
