//
//  StateController.hpp
//  membuf
//
//  Created by Yongjian Feng on 1/8/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

/*
    StateController
    ---------------
    This is the CareTaker of the memento design pattern
*/
#ifndef StateController_hpp
#define StateController_hpp

#include <stdio.h>
#include <list>

class Memento;
class StateController
{
public:
    StateController();
    virtual ~StateController();
    
    void storeMemento(Memento *pMemento);
    Memento *getPrevious();
    Memento *getNext();
private:
    std::list<Memento *>    m_listMemento;
    int                     m_curMemento;
};

#endif /* StateController_hpp */
