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
