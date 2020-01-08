//
//  state_controller.cpp
//  membuf
//
//  Created by yongjian feng on 1/8/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#include "state_controller.hpp"

using namespace std;

StateController::StateController()
    :m_curIndex(-1)
{}

void StateController::save_memento(Memento *pMemento)
{
    if (m_curIndex != m_listMemento.size() - 1){
        // @TODO: Need to clarify requirement here.
        // If the current one is NOT the last one, how to save?
        // The logic below erase all the mementos behind
        // the current one first before pushing
        
        int tmp = m_listMemento.size() - 1;
        while (tmp > m_curIndex){
            Memento* pTmp = m_listMemento.back();
            m_listMemento.pop_back();
            delete pTmp;
            tmp--;
        }
    }
    
    m_listMemento.push_back(pMemento);
    m_curIndex ++;
}

Memento* StateController::get_pre_memento()
{
    if (m_curIndex < 0 || m_listMemento.size() == 0) {
        // Already the last one or list is empty
        return NULL;
    }
    m_curIndex--;
    
    return m_listMemento.;
}

