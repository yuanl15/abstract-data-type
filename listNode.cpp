//
//  listNode.cpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/7/14.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#include "listNode.hpp"

template <typename T> ListNode<T>* ListNode<T>::insertAsPred(const T &e){
    ListNode<T>* p = new ListNode(e,pred,this);
    pred->succ = p;
    pred = p;
    return p;
}

template <typename T> ListNode<T>* ListNode<T>::insertAsSucc(const T &e){
    ListNode<T>* s = new ListNode<T>(e,this,succ);
    succ->pred = s;
    succ = s;
    return s;
}
