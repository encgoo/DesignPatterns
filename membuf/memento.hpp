//
//  memento.hpp
//  membuf
//
//  Created by yongjian feng on 1/8/20.
//  Copyright © 2020 Yongjian Feng. All rights reserved.
//

#ifndef memento_hpp
#define memento_hpp

#include <stdio.h>
#include "membuf.hpp"
/*
   class memento
   -------------
   Memento design pattern
*/

class Memento
{
public:
    friend class membuf;
    
    virtual ~Memento();
    membuf get_originator();
    
private:
    // private constructor
    // can be called by "friend" membuf only
    Memento(membuf mem_buf);
    membuf m_membuf;
};
#endif /* memento_hpp */




