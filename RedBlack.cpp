//
//  RedBlack.cpp
//  abstract-data-type
//
//  Created by 袁麓 on 2018/12/16.
//  Copyright © 2018 袁麓. All rights reserved.
//

#include "RedBlack.hpp"

// 这里的高度均为黑高度
template <typename T> int RedBlack<T>::updateHeight(binNode<T> *x) {
    x->height = max(stature(x->lc), stature(x->rc));
    return IsBlack(x) ? x->height++ : x->height;
}

// 插入
template <typename T> BinNodePosi(T) RedBlack<T>::insert(const T &e) {
    BinNodePosi(T) &x = this->search(e);
    if (!x) return x;
    
    // 创建红节点x，以_hot为父，黑高度-1
    x = new binNode<T>(e, this->_hot, NULL, NULL, -1);
    solveDoubleRed(x);
    return x ? x : this->_hot->parent;
}

// 双红修正算法
template <typename T> void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x) {
    if (IsRoot(*x)) {
        this->_root->color = RB_BLACK;
    }
    // TODO
}
