//
//  queue.hpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/8/3.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#ifndef queue_hpp
#define queue_hpp

#include <stdio.h>
#include "list.hpp"

template <typename T> class queue:public list<T> {
    
public:
    void push(T e){insertAsLast(e);}
    T pop(){return remove( this->first() );}
    T& front(){return this->first()->data;}
};
#endif /* queue_hpp */
