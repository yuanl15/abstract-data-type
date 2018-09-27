//
//  math.h
//  HelloWorld
//
//  Created by 袁麓 on 2018/7/12.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#ifndef math_h
#define math_h

int fibonacci(int k);//递归法实现获取fibonacci数列第n项
class Fib{
public:
    Fib(int n);//获得不小于n的fibonacci数
    int get(){return num;}//获取当前斐波拉契项
    int prev(){num = nex - num;nex = nex - num;return num;}//获取上一斐波拉契项
    int next(){nex = num + nex;num = nex - num;return num;}//获取下一斐波拉契项
private:
    int num;//当前斐波拉契项
    int nex;//下一项
};
#endif /* math_h */
