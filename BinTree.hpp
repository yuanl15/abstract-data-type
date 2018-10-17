//
//  BinTree.hpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/9/2.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#ifndef BinTree_hpp
#define BinTree_hpp

#include <stdio.h>
#include "binNode.hpp"

template <typename T> class BinTree{
protected:
    int _size;//规模
    BinNodePosi(T) _root;//根节点
    virtual int updateHeight(BinNodePosi(T) x);//更新节点x的高度
    void updateHeightAbove(BinNodePosi(T) x);//更新节点x及其祖先的高度
    virtual bool lt(BinNodePosi(T) const &a,BinNodePosi(T) const &b){return a->data < b->data;}//需重载的比较
public:
    BinTree():_size(0),_root(NULL){}
    ~BinTree(){if(_size > 0) remove (_root);}//析构函数
    int size() const {return _size;}
    bool empty() const {return !_root;}//判空
    BinNodePosi(T) root(){ return _root;}//返回树根
    BinNodePosi(T) insertAsRoot ( T const& e);//插入根节点
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x,T const& e);//e作为x的左孩子插入
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x,T const& e);//e作为x的右孩子插入
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x,BinTree<T>* &t);//t作为x的左子树插入
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x,BinTree<T>* &t);//t作为x的右子树插入
    int remove(BinNodePosi(T) x);//删除以x为根节点的子树
    BinTree<T>* secede(BinNodePosi(T) x);//将该节点从树中删除，并转换为一个独立子树
    template <typename VST>//操作器
    void travLevel(VST& visit){if(_root) _root->travLevel(visit);}//层次遍历
    template <typename VST>
    void travPre(VST& visit){if(_root) _root->travPre(visit);}//先序遍历，调用binNode中的遍历方法
    template <typename VST>
    void travIn(VST& visit){if(_root) _root->travIn(visit);}//中序遍历，调用binNode中的遍历方法
    template <typename VST>
    void travPost(VST& visit){if(_root) _root->travPost(visit);}//后序遍历，调用binNode中的遍历方法
    bool operator< (BinTree<T> const& t)//比较器
    { return _root && t._root && lt(_root,t._root);}
    bool operator == (BinTree<T> const& t)//判等器
    { return _root && t._root && (_root == t._root);}
};
#endif /* BinTree_hpp */
