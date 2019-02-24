//
//  PriorityQueue.h
//  abstract-data-type
//
//  Created by 袁麓 on 2019/2/24.
//  Copyright © 2019 袁麓. All rights reserved.
//

#ifndef PriorityQueue_h
#define PriorityQueue_h

template <typename T> PriorityQueue {
    virtual void insert(T) = 0;// 按优先级插入词条
    virtual T getMax() = 0;// 取出优先级最高的词条
    virtual T delMax() = 0;// 删除优先级最高的词条
}


#endif /* PriorityQueue_h */
