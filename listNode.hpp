//
//  listNode.hpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/7/14.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#ifndef listNode_hpp
#define listNode_hpp

#include <stdio.h>
typedef int Rank;
template <typename T> struct ListNode{
    T data;//data
    ListNode<T>* pred;
    ListNode<T>* succ;
    ListNode(){}//header,trailer构造函数
    ListNode(T e,ListNode<T>* p = NULL,ListNode<T>* s = NULL):data(e),pred(p),succ(s){}//默认构造函数
    ListNode<T>* insertAsPred(T const& e);//当前节点前插入
    ListNode<T>* insertAsSucc(T const& e);//当前节点后插入
};
#endif /* listNode_hpp */
