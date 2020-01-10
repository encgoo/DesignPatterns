//
//  CommandCommon.cpp
//  membuf
//
//  Created by Yongjian Feng on 1/10/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#include "CommandCommon.hpp"

using namespace std;
bool CommandCommon::Insert(size_t pos, const std::string &in_str, membuf::CharBuf *pBuf)
{
    bool ret = false;
    if (pos < pBuf->size() - 1)
    {
        vector<unsigned char>::iterator itr = pBuf->begin();
        advance(itr, pos);
        pBuf->insert(itr, in_str.begin(), in_str.end());
        ret = true;
    }
    return ret;
}

string CommandCommon::Erase(size_t pos, size_t len, membuf::CharBuf *pBuf)
{
    string removed;
    if (pos >= 0 && pos + len < pBuf->size())
    {
        vector<unsigned char>::iterator start_itr = pBuf->begin();
        advance(start_itr, pos);
        vector<unsigned char>::iterator end_itr = pBuf->begin();
        advance(end_itr, pos + len);
        copy(start_itr, end_itr, back_inserter(removed));
        pBuf->erase(start_itr, end_itr);
    }
    return removed;
}

bool CommandCommon::Append(const string& in_str, membuf::CharBuf *pBuf)
{
    vector<unsigned char>::iterator itr = pBuf->end();
    pBuf->insert(itr, in_str.begin(), in_str.end());
    return true;
}

string CommandCommon::EraseTrailing(size_t len, membuf::CharBuf *pBuf)
{
    string removed;
    if (len < pBuf->size())
    {
        vector<unsigned char>::iterator start_itr = pBuf->begin();
        advance(start_itr, pBuf->size() - len);
        vector<unsigned char>::iterator end_itr = pBuf->end();
        copy(start_itr, end_itr, back_inserter(removed));
        pBuf->erase(start_itr, end_itr);
    }
    return removed;
}
