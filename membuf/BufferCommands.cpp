//
//  BufferCommands.cpp
//  membuf
//
//  Created by Yongjian Feng on 1/10/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#include "BufferCommands.hpp"
#include "membuf.hpp"
using namespace std;


/*
 InsertCommand
 -------------
 */

InsertCommand::InsertCommand(size_t pos, const string& in_str)
:m_pos(pos), m_inStr(in_str)
{
    
}

bool InsertCommand::Execute(membuf::CharBuf *pBuf)
{
    return Insert(m_pos, m_inStr, pBuf);
}

bool InsertCommand::Undo(membuf::CharBuf *pBuf)
{
    string removed = Erase(m_pos, m_inStr.size(), pBuf);
    return removed.size() > 0;
}

/*
 AppendCommand
 */
AppendCommand::AppendCommand(const string& in_str)
:m_inStr(in_str)
{
    
}

bool AppendCommand::Execute(membuf::CharBuf *pBuf)
{
    return Append(m_inStr, pBuf);
}

bool AppendCommand::Undo(membuf::CharBuf *pBuf)
{
    string removed = EraseTrailing(m_inStr.size(), pBuf);
    return removed.size() > 0;
}

/*
 EraseCommand
 */
EraseCommand::EraseCommand(size_t pos, size_t len)
:m_pos(pos), m_len(len)
{
    
}

bool EraseCommand::Execute(membuf::CharBuf *pBuf)
{
    m_erasedStr = Erase(m_pos, m_len, pBuf);
    return m_erasedStr.size() == m_len;
}

bool EraseCommand::Undo(membuf::CharBuf *pBuf)
{
    return Insert(m_pos, m_erasedStr, pBuf);
}

/*
 EraseTrailingCommand
 */

EraseTrailingCommand::EraseTrailingCommand(size_t len)
:m_len(len)
{
    
}

bool EraseTrailingCommand::Execute(membuf::CharBuf *pBuf)
{
    m_erasedStr = EraseTrailing(m_len, pBuf);
    return m_erasedStr.size() == m_len;
}

bool EraseTrailingCommand::Undo(membuf::CharBuf *pBuf)
{
    return Append(m_erasedStr, pBuf);
}

/*
 ReplaceCommand
 */
ReplaceCommand::ReplaceCommand(const string& from_str, const string& to_str)
:m_fromStr(from_str), m_toStr(to_str)
{
    m_skipList.clear();

}

int ReplaceCommand::store_toString_pos(membuf::CharBuf::iterator search_start,
                                        membuf::CharBuf::iterator search_end,
                                        const std::string& str_to,
                                        int cur_index)
{
    int count = 0;
    vector<unsigned char>::iterator itr =
    search(search_start, search_end, str_to.begin(), str_to.end());
    while (itr != search_end)
    {
        m_skipList.push_back(cur_index + count);
        count ++;
        itr = search(itr + str_to.size(), search_end, str_to.begin(), str_to.end());
    }
    return count;
}

bool ReplaceCommand::Execute(membuf::CharBuf *pBuf)
{
    // This is the tough one in this file. Need to store enough
    // information to do undo.
    //
    // The difficulty here is to handle something like this. Imagine:
    // Original string: "I think apple is better than orange"
    // Now replace "apple" with "orange". The end string becomes
    // "I think orange is better than orange".
    // To undo, we need to tell which "orange" was in the original string, and which
    // one came from the replace.
    //
    // The approach here is to count all the to_string in the original string, and
    // store the location in skipList. Later on, when undo, keep those unchanged.
    //
    
    // There is a special case. If the from_str is a substring of the to_str,
    // then we don't need to bother.
    bool is_substring = search(m_toStr.begin(), m_toStr.end(),
                               m_fromStr.begin(), m_fromStr.end()) != m_toStr.end();
    
    vector<int> skipList;
    vector<unsigned char>::iterator search_start = pBuf->begin();
    vector<unsigned char>::iterator search_end = pBuf->end();
    vector<unsigned char>::iterator next_from = search(search_start, search_end, m_fromStr.begin(), m_fromStr.end());
    int cur_index = 0;
    
    while (next_from != pBuf->end())
    {
        int count = 0;
        if (!is_substring)
        {
            count = store_toString_pos(search_start, next_from, m_toStr, cur_index);
        }
        cur_index += count;
        // first erase and then insert?
        size_t pos = next_from - pBuf->begin() + m_toStr.size();
        pBuf->erase(next_from, next_from + m_fromStr.size());
        pBuf->insert(next_from, m_toStr.begin(), m_toStr.end());
        cur_index ++;
        search_start = pBuf->begin();
        advance(search_start, pos);
        
        next_from = search(search_start, pBuf->end(), m_fromStr.begin(), m_fromStr.end());
    }
    return true;
}

bool ReplaceCommand::Undo(membuf::CharBuf *pBuf)
{
    int cur_index = 0;
    vector<unsigned char>::iterator search_start = pBuf->begin();
    vector<unsigned char>::iterator search_end = pBuf->end();
    
    vector<unsigned char>::iterator itr = search(search_start, search_end,
                                                 m_toStr.begin(), m_toStr.end());
    while (itr != pBuf->end())
    {
        // is cur_index in replace_lst?
        bool b_inlist = find(m_skipList.begin(), m_skipList.end(),
                             cur_index) != m_skipList.end();
        if (!b_inlist)
        {
            // replace it with original (from_str)
            pBuf->erase(itr, itr + m_toStr.size());
            pBuf->insert(itr, m_fromStr.begin(), m_fromStr.end());
            search_start = itr + m_fromStr.size();
        }
        else
        {
            search_start = itr + m_toStr.size();
        }
        cur_index ++;
        itr = search(search_start, pBuf->end(),
                     m_toStr.begin(), m_toStr.end());
    }
    return true;
}

