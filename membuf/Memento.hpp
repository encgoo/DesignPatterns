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
#include "membuf.hpp"
#include <vector>

class Memento
{
    friend class membuf;
public:
    virtual ~Memento(){};
    
private:
    Memento(const std::string& str, size_t pos1, size_t pos2, membuf::OPERATION op);
    Memento(const std::string& str1, const std::string& str2, std::vector<int> skipList);
    std::string         m_str1;
    std::string         m_str2;
    size_t              m_pos1;
    size_t              m_pos2;
    membuf::OPERATION   m_op;
    std::vector<int>    m_skipList;
};
#endif /* Memento_hpp */
