//
//  Command.hpp
//  membuf
//
//  Created by Yongjian Feng on 1/10/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#ifndef Command_hpp
#define Command_hpp

#include <stdio.h>
#include <vector>
#include "membuf.hpp"
/*
    Command
    -------
    Base class for Command Design Pattern
 
*/
class membuf;

class Command
{
public:
    Command(){};
    virtual ~Command(){};
    
    virtual bool Execute(membuf::CharBuf *pBuf)=0;
    virtual bool Undo(membuf::CharBuf *pBuf)=0;
};

#endif /* Command_hpp */
