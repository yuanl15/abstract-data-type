//
//  AVL.cpp
//  abstract-data-type
//
//  Created by 袁麓 on 2018/12/9.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#include "AVL.hpp"

template <typename T> BinNodePosi(T) AVL<T>::insert(const T& e) {
    BinNodePosi(T) & x = search(e);
    if (x) return x;
    BinNodePosi(T) xx = x = new binNode<T>(e, this->_hot);
    this->_size++;
    
    for (BinNodePosi(T) g = this->_hot; g; g = g->parent) {
        if ( !AvlBalanced(*g)) {
            FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
            break;
        }
        else updateHeight(g);
    }
    return xx;
}

template <typename T> bool AVL<T>::remove(const T& e) {
    BinNodePosi(T) &x = search(e);
    if (!x) return false;
    removeAt(x, this->_hot);
    this->_size--;
    for (BinNodePosi(T) g = this->_hot; g; g = g->parent) {
        if (!AvlBalanced(*g))
            g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
        updateHeight(g);
    }
    return true;
}

template <typename T> BinNodePosi(T) BST<T>::connect34(binNode<T> *a, binNode<T> *b, binNode<T> *c, binNode<T> *T0, binNode<T> *T1, binNode<T> *T2, binNode<T> *T3) {
    a->lc = T0; if (T0) T0->parent = a;
    a->rc = T1;if (T1) T1->parent = a; updateHeight(a);
    c->lc = T2;if (T2) T2->parent = c;
    c->rc = T3;if (T3) T3->parent = c;updateHeight(c);
    b->lc = a;a->parent = b;
    b->rc = c;c->parent = b;updateHeight(b);
    return b;
}

template <typename T> BinNodePosi(T) BST<T>::rotateAt(binNode<T> *v) {
    BinNodePosi(T) p = v->parent;
    BinNodePosi(T) g = p->parent;
    if (IsLChild(*p))
        if (IsLChild(*v)) {
            p->parent = g->parent;
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        }
        else {
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->rc, p->rc, g->rc);
        }
    else
        if (isRChild(*v)) {
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        } else {
            v->parent = g->parent;
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
}
