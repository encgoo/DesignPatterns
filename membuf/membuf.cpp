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
    // There is no easy way to revert this operation. Store the whole m_buf
    // as a string in Memento
    string content_to_store;
    copy(m_buf.begin(), m_buf.end(), back_inserter(content_to_store));
    
    Memento *pMemento = new Memento(content_to_store, from_str, to_str);
    m_stateController.storeMemento(pMemento);
    
    vector<unsigned char>::iterator find_itr = search(m_buf.begin(), m_buf.end(),
                                                      from_str.begin(), from_str.end());
    
    while (find_itr != m_buf.end())
    {
        copy(to_str.begin(), to_str.end(), find_itr);
        vector<unsigned char>::iterator start_ptr = find_itr;
        advance(start_ptr, 1);
        find_itr = search(start_ptr, m_buf.end(), from_str.begin(), from_str.end());
    }
    
    return *this;
}

string membuf::get_content() const
{
    string ret(m_buf.begin(), m_buf.end());
    return ret;
}
