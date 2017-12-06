// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <Windows.h>
#include <afx.h>

static const unsigned int nBomHeaderSize = 2;

static const unsigned char szUnicode[nBomHeaderSize] = { 0xFF, 0xFE };

class CMyFile : private CFile
{
private:
    static const UINT nOpenFlagsRead = modeRead | typeBinary;
    static const UINT nOpenFlagsWrite = modeCreate | modeRead | modeWrite | typeBinary;
private:
    CString _szFileName;
    bool _bOpen;
    bool _bWrite;
private:
    static const size_t nSizeOf_TCHAR = sizeof(TCHAR);
    static const size_t nSizeOf_wchar_t = sizeof(wchar_t);
    static const size_t nSizeOf_char = sizeof(char);
private:
    // Ansi buffer
    char BufferA;
    // Unicode buffer
    wchar_t BufferU;
private:
    // read & write modes
    // 0 -> src = Unicode, dst = Unicode
    // 1 -> src = Ansi, dst = Unicode
    // 2 -> src = Unicode, dst = Ansi
    // 3 -> src = Ansi, dst = Ansi
    int _nMode;
public:
    CMyFile()
    {
        this->_bOpen = false;
        this->_nMode = -1;
        this->_bWrite = false;
        this->_szFileName = _T("");
    }
    CMyFile(CString szFileName, bool bWrite)
    {
        if (szFileName.GetLength() <= 0)
            return;

        this->FOpen(szFileName, bWrite);
    }
    ~CMyFile()
    {
        try
        {
            if (this->_bOpen == true)
            {
                Close();

                this->_bOpen = false;
                this->_nMode = -1;
            }
        }
        catch (...)
        {

        }
    }
public:
#ifdef _UNICODE
    bool FSetMode(int nMode = 0)
    {
        if (nMode >= 0 && nMode <= 3)
        {
            this->_nMode = nMode;
            return true;
        }
        else
        {
            return false;
        }
    }
#else
    bool FSetMode(int nMode = 3)
    {
        if (nMode >= 0 && nMode <= 3)
        {
            this->_nMode = nMode;
            return true;
        }
        else
        {
            return false;
        }
    }
#endif
    int FMode()
    {
        return this->_nMode;
    }
    ULONGLONG FSize()
    {
        return this->GetLength();
    }
    ULONGLONG FPos()
    {
        return this->GetPosition();
    }
    bool FOpen(CString szFileName, bool bWrite)
    {
        if (this->_bOpen == true)
            return true;

        if (szFileName.GetLength() <= 0)
            return false;

        this->_bWrite = bWrite;
        this->_szFileName = szFileName;

        try
        {
            if (Open(this->_szFileName,
                this->_bWrite ? this->nOpenFlagsWrite : this->nOpenFlagsRead) == FALSE)
            {
                this->_bOpen = false;
                return false;
            }
            else
            {
                // auto-select read & write modes
                if (this->_nMode == -1)
                {
                    if (this->_bWrite == false)
                    {
                        // set read mode
                        bool bHaveBomHeader = false;
                        unsigned char szUnicodeHeader[nBomHeaderSize];

                        if (Read(szUnicodeHeader, nBomHeaderSize) != nBomHeaderSize)
                        {
                            Close();
                            this->_bOpen = false;
                            return false;
                        }

                        if ((szUnicodeHeader[0] != szUnicode[0]) || (szUnicodeHeader[1] != szUnicode[1]))
                            bHaveBomHeader = false;
                        else
                            bHaveBomHeader = true;

#ifdef _UNICODE
                        if (bHaveBomHeader == true)
                            this->_nMode = 0;
                        else
                            this->_nMode = 1;
#else
                        if (bHaveBomHeader == true)
                            this->_nMode = 2;
                        else
                            this->_nMode = 3;
#endif

                        // if input is Ansi than seek to the beginning of the file
                        if ((this->_nMode == 1) || (this->_nMode == 3))
                            Seek(0, begin);
                    }
                    else
                    {
                        // set write mode
#ifdef _UNICODE
                        this->_nMode = 0;
                        Write(szUnicode, nBomHeaderSize);
#else
                        this->_nMode = 3;
#endif
                    }
                }
                else
                {
                    // mode was selected by user
                    if (this->_bWrite == true)
                    {
                        switch (this->_nMode)
                        {
                            // dst = Unicode
                        case 0:
                        case 1:
                        {
                            Write(szUnicode, nBomHeaderSize);
                        }
                        break;
                        // dst = Ansi
                        case 2:
                        case 3:
                        {
                            // nothing to do
                        }
                        break;
                        }
                    }
                    else
                    {
                        switch (this->_nMode)
                        {
                            // src = Unicode
                        case 0:
                        case 2:
                        {
                            Seek(nBomHeaderSize, begin);
                        }
                        break;
                        // src = Ansi
                        case 1:
                        case 3:
                        {
                            Seek(0, begin);
                        }
                        break;
                        }
                    }
                }

                this->_bOpen = true;
                return true;
            }
        }
        catch (...)
        {
            return false;
        }
    }
    bool FClose()
    {
        if (this->_bOpen == false)
            return false;

        try
        {
            Close();
        }
        catch (...)
        {
            return false;
        }

        this->_bOpen = false;
        this->_nMode = -1;

        return true;
    }
    bool FRead(TCHAR &Buffer)
    {
        if (this->_bOpen == false)
            return false;

        if (this->_nMode == -1)
            return false;

        switch (this->_nMode)
        {
            // 0 -> src = Unicode, dst = Unicode
        case 0:
        {
            try
            {
                if (Read(&this->BufferU, this->nSizeOf_wchar_t) == 0)
                    return false;
            }
            catch (...)
            {
                return false;
            }

            Buffer = this->BufferU;
            return true;
        }
        break;
        // 1 -> src = Ansi, dst = Unicode
        case 1:
        {
            try
            {
                if (Read(&this->BufferA, this->nSizeOf_char) == 0)
                    return false;
            }
            catch (...)
            {
                return false;
            }

            _mbstowcsz(&this->BufferU, &this->BufferA, 1);
            Buffer = this->BufferU;
            return true;
        }
        break;
        // 2 -> src = Unicode, dst = Ansi
        case 2:
        {
            try
            {
                if (Read(&this->BufferU, this->nSizeOf_wchar_t) == 0)
                    return false;
            }
            catch (...)
            {
                return false;
            }

            _wcstombsz(&this->BufferA, &this->BufferU, 1);
            Buffer = this->BufferU;
            return true;
        }
        break;
        // 3 -> src = Ansi, dst = Ansi
        case 3:
        {
            try
            {
                if (Read(&this->BufferA, this->nSizeOf_char) == 0)
                    return false;
            }
            catch (...)
            {
                return false;
            }

            Buffer = this->BufferA;
            return true;
        }
        break;
        default:
        {
            return false;
        }
        break;
        }
    }
    bool FWrite(TCHAR &Buffer)
    {
        if (this->_bOpen == false)
            return false;

        if (this->_bWrite == false)
            return false;

        if (this->_nMode == -1)
            return false;

        switch (this->_nMode)
        {
            // 0 -> src = Unicode, dst = Unicode
        case 0:
        {
            try
            {
                this->BufferU = Buffer;
                Write(&this->BufferU, this->nSizeOf_wchar_t);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }
        break;
        // 1 -> src = Ansi, dst = Unicode
        case 1:
        {
            try
            {
                this->BufferA = Buffer;
                _mbstowcsz(&this->BufferU, &this->BufferA, 1);
                Write(&this->BufferU, this->nSizeOf_wchar_t);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }
        break;
        // 2 -> src = Unicode, dst = Ansi
        case 2:
        {
            try
            {
                this->BufferU = Buffer;
                _wcstombsz(&this->BufferA, &this->BufferU, 1);
                Write(&this->BufferA, this->nSizeOf_char);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }
        break;
        // 3 -> src = Ansi, dst = Ansi
        case 3:
        {
            try
            {
                this->BufferA = Buffer;
                Write(&this->BufferA, this->nSizeOf_char);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }
        break;
        default:
        {
            return false;
        }
        break;
        }

        return true;
    }
    UINT FReadString(TCHAR *Buffer, UINT nLength)
    {
        UINT _nRead = 0;

        if ((nLength == 0) || (Buffer == NULL))
            return false;

        if (this->_bOpen == false)
            return false;

        if (this->_nMode == -1)
            return false;

        for (UINT i = 0; i < nLength; i++)
        {
            if (FRead(Buffer[i]) == false)
                return _nRead;
            else
                _nRead++;
        }

        return _nRead;
    }
    bool FWriteString(TCHAR *Buffer, UINT nLength)
    {
        if ((nLength == 0) || (Buffer == NULL))
            return false;

        if (this->_bOpen == false)
            return false;

        if (this->_bWrite == false)
            return false;

        if (this->_nMode == -1)
            return false;

        for (unsigned int i = 0; i < nLength; i++)
        {
            if (FWrite(Buffer[i]) == false)
                return false;
        }

        return true;
    }
};
