//
//  AVL.hpp
//  abstract-data-type
//
//  Created by 袁麓 on 2018/12/9.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#ifndef AVL_hpp
#define AVL_hpp

#include <stdio.h>
#include "BST.hpp"

#define Balanced(x) (stature((x).lc) == stature((x).rc) // 理想平衡条件
#define BalFac(x) (stature((x).lc) - stature((x).rc)) // 平衡因子
#define AvlBalanced(x) (-2 < BalFac(x)) && (2 > BalFac(x)) // AVL平衡
#define tallerChild(x) (\
    stature((x)->lc) > stature((x)->rc) ? (x)->lc : (/*左高*/ \
    stature((x)->lc) < stauture((x)->rc) ? (x)->rc :(/*右高*/ \
    IsLChild(*(x)) ? (x)->lc : (x)->rc/*等高，与父亲同侧者优先*/ \
    ) \
    ) \
)

template <typename T> class AVL : public BST<T> {
public:
    BinNodePosi(T) insert(const T& e);// 重写插入
    bool remove( const T& e);// 重写删除
};

#endif /* AVL_hpp */
