//
//  math.cpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/7/12.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#include <stdio.h>
#include "math.h"

int fibonacci(int k){
    if(k<=2) return 1;
    return fibonacci(k-1) + fibonacci(k-2);
}

Fib::Fib(int n){
    num = 1;
    nex = 1;
    if(n > 1){
        while(num < n){
            nex = num + nex;
            num = nex - num;
        }
    }
}
