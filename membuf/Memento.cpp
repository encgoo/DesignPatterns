//
//  Memento.cpp
//  membuf
//
//  Created by Yongjian Feng on 1/10/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#include <stdio.h>
#include "Memento.hpp"
#include "Command.hpp"

Memento::~Memento()
{
    if (m_pCommand != NULL)
    {
        delete m_pCommand;
    }
    m_pCommand = NULL;
}

Command *Memento::getCommand()
{
    return m_pCommand;
}


