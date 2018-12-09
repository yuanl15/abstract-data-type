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
template <typename T> bool BST<T>::remove(const T& e){
    BinNodePosi(T) &x = search(e);
    if(!x) return false;
    removeAt(x, _hot);
    this->_size--;
    updateHeightAbove(_hot);
    return true;
}

//BST节点删除算法（全局静态模版类函数，适用于AVL、Splay、RedBlack等各种BST）
template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) &x, BinNodePosi(T) &hot){
    BinNodePosi(T) w = x;//实际被删除的节点，初值同x
    BinNodePosi(T) succ = NULL;
    if(!HasLChild(*x))
        succ = x = x->rc;
    else if (!HasRChild(*x))
        succ = x = x->l;
    else {
        w = w->succ();
        swap(x->data, w->data);
        BinNodePosi(T) u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc;
    }
    hot = w->parent;
    if (succ) succ->parent = hot;
        release(w->data);
        release(w);
        return succ;
}

