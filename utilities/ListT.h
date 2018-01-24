// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <vector>

namespace util
{
    template <class T>
    class CListT
    {
    public:
        std::vector<T> m_Items;
    public:
        bool IsEmpty()
        {
            return m_Items.empty();
        }
        int Count()
        {
            return (int)m_Items.size();
        }
        void Set(T& item, int idx)
        {
            m_Items[idx] = item;
        }
        void Set(T&& item, int idx)
        {
            m_Items[idx] = item;
        }
        T& Get(int idx)
        {
            return m_Items[idx];
        }
        void Insert(T& item)
        {
            m_Items.emplace_back(item);
        }
        void Insert(T&& item)
        {
            m_Items.emplace_back(item);
        }
        void InsertBefore(T& item, int nIndex)
        {
            auto it = m_Items.begin() + nIndex;
            m_Items.insert(it, item);
        }
        void InsertBefore(T&& item, int nIndex)
        {
            auto it = m_Items.begin() + nIndex;
            m_Items.insert(it, item);
        }
        void InsertAfter(T& item, int nIndex)
        {
            auto it = m_Items.begin() + nIndex;
            m_Items.insert(it+1, item);
        }
        void InsertAfter(T&& item, int nIndex)
        {
            auto it = m_Items.begin() + nIndex;
            m_Items.insert(it + 1, item);
        }
        void Remove(int nIndex)
        {
            auto it = m_Items.begin() + nIndex;
            m_Items.erase(it);
        }
        void RemoveAll(void)
        {
            if (m_Items.size() != 0)
                m_Items.clear();
        }
        void Swap(int idx1, int idx2)
        {
            T item1 = this->Get(idx1);
            T item2 = this->Get(idx2);
            if ((idx1 < 0) || (idx2 < 0) || (idx1 >= Count()) || (idx2 >= Count()))
                return;
            this->Set(item1, idx2);
            this->Set(item2, idx1);
        }
    };
}
