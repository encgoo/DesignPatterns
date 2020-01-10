//
//  Memento.hpp
//  membuf
//
//  Created by Yongjian Feng on 1/8/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#ifndef Memento_hpp
#define Memento_hpp

#include <stdio.h>
#include <string>

#include <vector>

class Command;
class Memento
{
    // Only allow membuf to call the private constructor
    friend class membuf;
public:
    virtual ~Memento();
    Command *getCommand();
private:
    Memento(Command *pCommand)
    :m_pCommand(pCommand){};

    Command     *m_pCommand;
};
#endif /* Memento_hpp */
