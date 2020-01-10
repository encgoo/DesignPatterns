//
//  BufferCommands.hpp
//  membuf
//
//  Created by Yongjian Feng on 1/10/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#ifndef BufferCommands_hpp
#define BufferCommands_hpp

#include <stdio.h>
#include "CommandCommon.hpp"
#include <string>
#include <vector>
/*
 BufferCommands
 --------------
 Concrete commands for membuf
*/

class InsertCommand : public CommandCommon
{
public:
    InsertCommand(size_t pos, const std::string& in_str);
    virtual ~InsertCommand(){};
    virtual bool Execute(membuf::CharBuf *pBuf);
    virtual bool Undo(membuf::CharBuf *pBuf);
private:
    size_t      m_pos;
    std::string m_inStr;
};

class AppendCommand : public CommandCommon
{
public:
    AppendCommand(const std::string& in_str);
    virtual ~AppendCommand(){};
    virtual bool Execute(membuf::CharBuf *pBuf);
    virtual bool Undo(membuf::CharBuf *pBuf);
    
private:
    std::string m_inStr;
};

class EraseCommand : public CommandCommon
{
public:
    EraseCommand(size_t pos, size_t len);
    virtual ~EraseCommand(){};
    virtual bool Execute(membuf::CharBuf *pBuf);
    virtual bool Undo(membuf::CharBuf *pBuf);
private:
    size_t      m_pos;
    size_t      m_len;
    std::string m_erasedStr;
};

class EraseTrailingCommand : public CommandCommon
{
public:
    EraseTrailingCommand(size_t len);
    virtual ~EraseTrailingCommand(){};
    virtual bool Execute(membuf::CharBuf *pBuf);
    virtual bool Undo(membuf::CharBuf *pBuf);
private:
    size_t      m_len;
    std::string m_erasedStr;
};

class ReplaceCommand : public CommandCommon
{
public:
    ReplaceCommand(const std::string& from_str, const std::string& to_str);
    virtual ~ReplaceCommand(){};
    virtual bool Execute(membuf::CharBuf *pBuf);
    virtual bool Undo(membuf::CharBuf *pBuf);
private:
    int store_toString_pos(membuf::CharBuf::iterator search_start,
                            membuf::CharBuf::iterator search_end,
                            const std::string& str_to,
                            int cur_index);
    
    std::string         m_fromStr;
    std::string         m_toStr;
    std::vector<int>    m_skipList;
};


#endif /* BufferCommands_hpp */
