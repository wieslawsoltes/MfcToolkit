// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <map>
#include <utility>
#include <initializer_list>

namespace util
{
    template <class K, class V>
    class CMapT
    {
    public:
        std::map<K, V> m_Map;
    public:
        CMapT() { }
        CMapT(std::initializer_list<std::pair<const K, V>> m) : m_Map(m) { }
        CMapT(const CMapT &other) : m_Map(other.m_Map) { }
        CMapT(CMapT&& other) : m_Map(std::move(other.m_Map)) { }
        CMapT& operator=(const CMapT& other)
        {
            m_Map = other.m_Map;
            return *this;
        }
        CMapT& operator=(CMapT&& other)
        {
            m_Map = std::move(other.m_Map);
            return *this;
        }
        ~CMapT() { }
    public:
        bool IsEmpty()
        {
            return m_Map.empty();
        }
        int Count()
        {
            return (int)m_Map.size();
        }
        void Set(K key, V& szValue)
        {
            m_Map[key] = szValue;
        }
        void Set(K key, V&& szValue)
        {
            m_Map[key] = szValue;
        }
        V& Get(K key)
        {
            return m_Map[key];
        }
        bool TryGet(K key, V& rValue)
        {
            if (m_Map.count(key) == 1)
            {
                rValue = m_Map[key];
                return true;
            }
            return false;
        }
        void Insert(K key, V& szValue)
        {
            m_Map[key] = szValue;
        }
        void Insert(K key, V&& szValue)
        {
            m_Map[key] = szValue;
        }
        void Remove(K key)
        {
            m_Map.erase(key);
        }
        void RemoveAll(void)
        {
            if (m_Map.size() > 0)
                m_Map.clear();
        }
        void Swap(K key1, K key2)
        {
            V value1;
            V value2;
            bool haveValue1 = this->TryGet(key1, value1);
            bool haveValue2 = this->TryGet(key2, value2);
            if (haveValue1 == false || haveValue2 == false)
                return;
            this->Set(key2, value1);
            this->Set(key1, value2);
        }
    };
}
