//
//  binNode.cpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/8/19.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#include "binNode.hpp"
#include "queue.hpp"

template <typename T> BinNodePosi(T) binNode<T>::insertAsLC(T const& e){
    return lc = new binNode<T>(e,this);
}

template <typename T> BinNodePosi(T) binNode<T>::insertAsRC(T const& e){
    return rc = new binNode<T>(e,this);
}

template <typename T> template <typename VST>
void binNode<T>::travIn(VST& visit){
    switch(rand() % 5){
        case 1: travIn_I1(this,visit); break;
        case 2: travIn_I2(this,visit); break;
        case 3: travIn_I3(this,visit); break;
        case 4: travIn_I4(this,visit); break;
        case 5: travIn_R(this,visit); break;//递归版
    }
}

//层次遍历
template <typename T> template <typename VST>
void binNode<T>::travLevel(VST &visit){
    queue<BinNodePosi(T) > tree;
    if(this) tree.push(this);
    binNode<T>* temp;
    while(!tree.empty()){
        temp = tree.pop();
        if(HasLChild(*temp)) tree.push(temp->lc);
        if(HasRChild(*temp)) tree.push(temp->rc);
        visit(temp->data);
    }
}
