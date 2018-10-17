//
//  BST.hpp
//  abstract-data-type
//
//  Created by 袁麓 on 2018/10/15.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include "BinTree.hpp"

template <typename T> class BST : public BinTree<T>{//由BinTree派生BST
protected:
    BinNodePosi(T) _hot;//“命中”节点的父亲
    BinNodePosi(T) connect34(//按照“3+4”结构，联接3个节点及四棵子树
                             BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
                             BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
    BinNodePosi(T) rotateAt(BinNodePosi(T) x);//对x及其父亲、祖父做统一旋转调整
public:
    virtual BinNodePosi(T) & search(const T& e);//查找
    virtual BinNodePosi(T) insert(const T& e);//插入
    virtual bool remove(const T& e);//删除
};

#endif /* BST_hpp */
