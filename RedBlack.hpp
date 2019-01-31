//
//  RedBlack.hpp
//  abstract-data-type
//
//  Created by 袁麓 on 2018/12/16.
//  Copyright © 2018 袁麓. All rights reserved.
//

#ifndef RedBlack_hpp
#define RedBlack_hpp

#include <stdio.h>
#include "BST.hpp"

#define IsBlack(x) (!(x) || (RB_BLACK == (x)->color)) //是否为黑节点
#define IsRed(x) (!IsBlack(x)) //是否为红节点
#define BlackHeightUpdated(x) (/*红黑树高度更新条件*/ \
    (stature((x).lc) == stature((x).rc)) && \
    ((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1)) \
)

template <typename T> class RedBlack : public BST<T> {
protected:
    
    // 双红修正
    void solveDoubleRed(BinNodePosi(T) x);
    
    // 双黑修正
    void solveDoubleBlack(BinNodePosi(T) x);
    
    // 更新节点x的高度
    int updateHeight(BinNodePosi(T) x);
    
public:
    
    // 插入（重写）
    BinNodePosi(T) insert(const T& e);
    
    // 删除（重写）
    bool remove(const T& e);
    
};
#endif /* RedBlack_hpp */
