//
//  Memento.cpp
//  membuf
//
//  Created by Yongjian Feng on 1/8/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#include "Memento.hpp"
using namespace std;
Memento::Memento(const string& str, size_t pos1, size_t pos2, membuf::OPERATION op)
:m_str1(str), m_pos1(pos1), m_pos2(pos2), m_op(op)
{
    m_str2 = "";
    m_skipList.clear();
}

Memento::Memento(const string& str1, const string& str2, vector<int> skipList)
:m_str1(str1), m_str2(str2)
{
    m_pos1 = 0;
    m_pos2 = 0;
    m_op = membuf::REPLACE;
    m_skipList.clear();
    m_skipList = skipList;
}
