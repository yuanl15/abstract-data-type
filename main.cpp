//
//  main.cpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/5/12.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#include <iostream>
#include "math.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Fib fibtest(6);
    std::cout<<fibtest.get()<<fibtest.prev()<<std::endl;
    return 0;
}
