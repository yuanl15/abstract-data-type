//
//  BinTree.cpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/9/2.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#include "BinTree.hpp"
#include "queue.hpp"

template <typename T> int BinTree<T>::updateHeight ( BinNodePosi(T) x){//更新高度
    return x -> height = 1 + max ( stature(x -> lc),stature(x->rc));
}

template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x){//更新高度
    while(x){
        updateHeight(x);
        x = x->parent;
    }
}

//将e当作根节点插入空的二叉树
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e){
    _size = 1;
    return _root = new binNode<T>(e);
}

//e插入为x的左孩子
template<typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, const T &e){
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

//插入为x的右孩子
template<typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, const T &e){
    _size ++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template <typename T>//二叉树子树接入
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x,BinTree<T>* &S){
    if((x->lc = S->root)) x->lc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->root = NULL;
    S->_size = 0;
    release(S);//解除S指针对于原先指向内存的控制
    S = NULL;
    return x;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x,BinTree<T>* &S){
    if((x->rc = S->root)) x->rc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->root = NULL;
    S->_size = 0;
    release(S);
    S = NULL;
    return x;
}

template <typename T>//删除二叉树中位置x处的节点及其后代
int BinTree<T>::remove(BinNodePosi(T) x){
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}

template <typename T>//声明内部函数（静态函数），其意义在于起作用域为文件内部
static int removeAt(BinNodePosi(T) x){
    if(!x) return 0;
    int n = 1+ removeAt(x->lc) + removeAt(x->rc);//递归释放左右子树
    release(x->data);
    release(x);
    return n;
}

//子树分离
template <typename T>
BinTree<T>* BinTree<T>::secede(binNode<T> *x){
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);//更新原树中所有祖先的高度
    BinTree<T>* S = new BinTree<T>;
    S->_root = NULL;
    S->_size = x->size();
    _size -= S->_size;
    return S;
}

//先序遍历
template <typename T,typename VST>//元素类型、操作器
void travPre_R(BinNodePosi(T) x,VST& visit){
    if(!x) return ;
    visit(x->data);
    travPre_R(x->lc);
    travPre_R(x->rc);
}

//中序遍历
template <typename T,typename VST>//元素类型、操作器
void travIn_R(BinNodePosi(T) x,VST& visit){
    if(!x) return ;
    travPre_R(x->lc);
    visit(x->data);
    travPre_R(x->rc);
}

//后序遍历
template <typename T,typename VST>//元素类型、操作器
void travPost_R(BinNodePosi(T) x,VST& visit){
    if(!x) return ;
    travPre_R(x->lc);
    travPre_R(x->rc);
    visit(x->data);
}


