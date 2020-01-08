//
//  state_controller.hpp
//  membuf
//
//  Created by yongjian feng on 1/8/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#ifndef state_controller_hpp
#define state_controller_hpp

/*
    StateController
    ---------------
    This is the CareTaker of the memento design pattern
 */
#include <stdio.h>
#include <list>

class Memento;

class StateController
{
public:
    StateController();
    virtual ~StateController();
    
    void save_memento(Memento *pMemento);
    
    Memento* get_pre_memento();
    
    Memento* get_next_memento();
private:
    std::list<Memento *>    m_listMemento;
    int                     m_curIndex;
};

#endif /* state_controller_hpp */
