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
#include "BufferCommands.hpp"

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
    fileout.write((const char *) &m_buf[0], m_buf.size());
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
        infile.read((char *) &m_buf[0], f_size);
    }
    return f_size;
}

membuf& membuf::insert(size_t pos, const std::string &in_str)
{
    return execute(new InsertCommand(pos, in_str));
}

membuf& membuf::append(const std::string &in_str)
{
    return execute(new AppendCommand(in_str));
}

membuf& membuf::erase(size_t pos, size_t len)
{
    return execute(new EraseCommand(pos, len));
}

membuf& membuf::erase_trailing(size_t len)
{
    return execute(new EraseTrailingCommand(len));
}

membuf& membuf::replace(const std::string &from_str, const std::string &to_str)
{
    return execute(new ReplaceCommand(from_str, to_str));
}

membuf& membuf::undo()
{
    Memento* prev = m_stateController.getPrevious();
    if (prev != NULL)
    {
        prev->getCommand()->Undo(&m_buf);
    }
    return *this;
}

membuf& membuf::redo()
{
    Memento* next = m_stateController.getNext();
    if (next != NULL)
    {
        next->getCommand()->Execute(&m_buf);
    }
    return *this;
}

// Utility Functions
string membuf::get_content() const
{
    string ret(m_buf.begin(), m_buf.end());
    return ret;
}

membuf& membuf::execute(Command *pCommand)
{
    Memento *pMemento = new Memento(pCommand);
    m_stateController.storeMemento(pMemento);
    pCommand->Execute(&m_buf);
    return *this;
}
