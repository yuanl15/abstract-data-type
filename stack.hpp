//
//  stack.hpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/7/16.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#ifndef stack_hpp
#define stack_hpp

#include <stdio.h>
#include "vector.h"

template<typename T> class stack:public vector<T>{
public:
    void push(T const &e){insert( this->size(),e );}
    T pop(){return erase(this->size() - 1);}
    T& top(){return (*this)[this->size()-1];}
};
#endif /* stack_hpp */
