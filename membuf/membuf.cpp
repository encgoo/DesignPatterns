//
//  membuf.cpp
//  membuf
//
//  Created by Yongjian Feng on 1/6/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#include "membuf.hpp"
#include <iostream>
#include <fstream>
#include "Memento.hpp"

using namespace std;

// constructor
membuf::membuf(string inbuf)
{
    copy(inbuf.begin(), inbuf.end(), back_inserter(m_buf));
}

size_t membuf::save_file(const std::string& filename) const
{
    size_t chars_written = 0;
    
    ofstream fileout(filename.c_str(), ios::out | ios::binary);
    fileout.write((const char*) &m_buf[0], m_buf.size());
    fileout.close();
    
    return chars_written;
}

size_t membuf::read_file(const std::string& filename)
{
    //@TODO: Verify the requirement
    // Not sure about the requirement here. If the m_buf
    // is not empty, shall we replace the content with
    // what we read from the file?
    
    ifstream infile(filename.c_str());
    size_t f_size = 0;
    if (!infile.eof() && !infile.fail())
    {
        // First figure out the file size
        infile.seekg(0, ios_base::end);
        f_size = infile.tellg();
        m_buf.resize(f_size);
        // make a copy
        infile.seekg(0, ios_base::beg);
        infile.read((char*) &m_buf[0], f_size);
    }
    return f_size;
}

membuf& membuf::insert(size_t pos, const std::string &in_str)
{
    Memento *pMemento = new Memento(in_str, pos, 0, membuf::INSERT);
    m_stateController.storeMemento(pMemento);
    
    vector<unsigned char>::iterator itr = m_buf.begin();
    advance(itr, pos);
    m_buf.insert(itr, in_str.begin(), in_str.end());
    
    return *this;
}

membuf& membuf::append(const std::string &in_str)
{
    Memento *pMemento = new Memento(in_str, 0, 0, membuf::APPEND);
    m_stateController.storeMemento(pMemento);
    
    vector<unsigned char>::iterator itr = m_buf.end();
    m_buf.insert(itr, in_str.begin(), in_str.end());
    
    return *this;
}

membuf& membuf::erase(size_t pos, size_t len)
{
    vector<unsigned char>::iterator start_itr = m_buf.begin();
    advance(start_itr, pos);
    vector<unsigned char>::iterator end_itr = m_buf.begin();
    advance(end_itr, pos + len);
    string content_to_store;
    copy(start_itr, end_itr, back_inserter(content_to_store));
    
    Memento *pMemento = new Memento(content_to_store, pos, len, membuf::ERASE);
    m_stateController.storeMemento(pMemento);
    
    m_buf.erase(start_itr, end_itr);
    return *this;
}

membuf& membuf::erase_trailing(size_t len)
{
    vector<unsigned char>::iterator start_itr = m_buf.begin();
    advance(start_itr, m_buf.size() - len);
    vector<unsigned char>::iterator end_itr = m_buf.end();

    string content_to_store;
    copy(start_itr, end_itr, back_inserter(content_to_store));
    
    Memento *pMemento = new Memento(content_to_store, len, 0, membuf::ERASE_TRAILING);
    m_stateController.storeMemento(pMemento);
    
    m_buf.erase(start_itr, end_itr);
    return *this;
}

membuf& membuf::replace(const std::string &from_str, const std::string &to_str)
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
    bool is_substring = search(to_str.begin(), to_str.end(),
                               from_str.begin(), from_str.end()) != to_str.end();
    
    vector<int> skipList;
    vector<unsigned char>::iterator search_start = m_buf.begin();
    vector<unsigned char>::iterator search_end = m_buf.end();
    vector<unsigned char>::iterator next_from = search(search_start, search_end, from_str.begin(), from_str.end());
    int cur_index = 0;
    while (next_from != m_buf.end())
    {
        int count = 0;
        if (!is_substring)
        {
            count = count_toString(search_start, next_from, to_str, cur_index, skipList);
        }
        cur_index += count;
        // first erase and then insert?
        m_buf.erase(next_from, next_from + from_str.size());
        m_buf.insert(next_from, to_str.begin(), to_str.end());
        cur_index ++;
        search_start = next_from + to_str.size();
        next_from = search(search_start, m_buf.end(), from_str.begin(), from_str.end());
    }
    
    Memento *pMemento = new Memento(from_str, to_str, skipList);
    m_stateController.storeMemento(pMemento);
    
    return *this;
}

string membuf::get_content() const
{
    string ret(m_buf.begin(), m_buf.end());
    return ret;
}

int membuf::count_toString(vector<unsigned char>::iterator search_start,
                           vector<unsigned char>::iterator search_end,
                           string str_to,
                           int cur_index,
                           vector<int>& skipList)
{
    int count = 0;
    vector<unsigned char>::iterator itr =
    search(search_start, search_end, str_to.begin(), str_to.end());
    while (itr != search_end)
    {
        skipList.push_back(cur_index + count);
        count ++;
        itr = search(itr + str_to.size(), search_end, str_to.begin(), str_to.end());
    }
    return count;
}

void membuf::undo_replace(const string& from_str, const string& to_str,
                          std::vector<int> skipList)
{
    int cur_index = 0;
    vector<unsigned char>::iterator search_start = m_buf.begin();
    vector<unsigned char>::iterator search_end = m_buf.end();
    
    vector<unsigned char>::iterator itr = search(search_start, search_end,
                                                 to_str.begin(), to_str.end());
    while (itr != m_buf.end())
    {
        // is cur_index in replace_lst?
        bool b_inlist = find(skipList.begin(), skipList.end(),
                             cur_index) != skipList.end();
        if (!b_inlist)
        {
            m_buf.erase(itr, itr + to_str.size());
            m_buf.insert(itr, from_str.begin(), from_str.end());
            search_start = itr + from_str.size();
        }
        else
        {
            search_start = itr + to_str.size();
        }
        cur_index ++;
        itr = search(search_start, m_buf.end(),
                     to_str.begin(), to_str.end());
    }
}

membuf& membuf::undo()
{
    Memento* prev = m_stateController.getPrevious();
    if (prev != NULL){
        
        switch(prev->m_op)
        {
            case REPLACE:
                undo_replace(prev->m_str1, prev->m_str2, prev->m_skipList);
                
        }
        
        
    }
    
    return *this;
}

membuf& membuf::redo()
{
    Memento* next = m_stateController.getNext();
    if (next != NULL)
    {
        switch(next->m_op)
        {
            case REPLACE:
                replace(next->m_str1, next->m_str2);
        }
    }
    return *this;
}
