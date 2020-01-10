//
//  CommandCommon.hpp
//  membuf
//
//  Created by Yongjian Feng on 1/10/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#ifndef CommandCommon_hpp
#define CommandCommon_hpp

#include <stdio.h>
#include <string>
#include "Command.hpp"

/*
 Factorization of functions shared by concrete commands
 */
class CommandCommon : public Command
{
public:
    CommandCommon(){};
    virtual ~CommandCommon(){};
    virtual bool Insert(size_t pos, const std::string& in_str, membuf::CharBuf *pBuf);
    virtual std::string Erase(size_t pos, size_t len, membuf::CharBuf *pBuf);
    virtual bool Append(const std::string& in_str, membuf::CharBuf *pBuf);
    virtual std::string EraseTrailing(size_t len, membuf::CharBuf *pBuf);
};
#endif /* CommandCommon_hpp */
