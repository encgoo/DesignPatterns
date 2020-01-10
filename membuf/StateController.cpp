//
//  StateController.cpp
//  membuf
//
//  Created by Yongjian Feng on 1/8/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#include "StateController.hpp"

using namespace std;

StateController::StateController()
:m_curMemento(-1)
{}

StateController::~StateController()
{
    // Free memory
    for (Memento *pMem : m_listMemento)
    {
        delete pMem;
    }
    m_listMemento.clear();
}

void StateController::storeMemento(Memento *pMemento)
{
    if (m_curMemento != m_listMemento.size() - 1)
    {
        // @TODO Need to verify the requirement about this.
        // User has undo several times, and now he/she
        // wants to store.
        
        // Current logic is to remove whatever behind, then
        // store
        int tmp = m_listMemento.size() - 1;
        while (tmp > m_curMemento){
            Memento *pMem = m_listMemento.back();
            m_listMemento.pop_back();
            delete pMem;
        }
    }
    m_listMemento.push_back(pMemento);
    m_curMemento ++;
}

Memento *StateController::getPrevious()
{
    if (m_curMemento < 0)
    {
        // Already the first one or the list is empty
        return NULL;
    }
    
    list<Memento *>::iterator itr = m_listMemento.begin();
    std::advance(itr, m_curMemento--);
    return *itr;
}

Memento *StateController::getNext()
{
    if (m_curMemento > m_listMemento.size() - 1 || m_curMemento < -1)
    {
        // Already the last one.
        return NULL;
    }
    list<Memento *>::iterator itr = m_listMemento.begin();
    std::advance(itr, ++m_curMemento);
    return *itr;
}
