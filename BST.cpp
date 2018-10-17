//
//  BST.cpp
//  abstract-data-type
//
//  Created by 袁麓 on 2018/10/15.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#include "BST.hpp"

template <typename T>
static BinNodePosi(T) & searchIn(BinNodePosi(T) &v, const T& e, BinNodePosi(T) &hot){
    if( !v || (e == v->data)) return v;
    hot = v;
    return searchIn(((e > v->data)? v->rc : v->lc), hot, e);
}

template <typename T> BinNodePosi(T) & BST<T>::search(const T& e){ return searchIn(this->_root, e, _hot = NULL);}


//插入节点
template <typename T> BinNodePosi(T) BST<T>::insert(const T &e){
    BinNodePosi(T) &x = search(e);
    if(x) return x;
    x = new binNode<T>(e, _hot);
    this->_size++;
    updateHeightAbove(x);
    return x;
}

//删除节点
template <typename T> BinNodePosi(T) 
