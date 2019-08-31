//
//  PriorityQueue.h
//  abstract-data-type
//
//  Created by 袁麓 on 2019/2/24.
//  Copyright © 2019 袁麓. All rights reserved.
//

#ifndef PriorityQueue_h
#define PriorityQueue_h
#include "vector.h"
#define Parent(i) (((i) - 1) >> 1)
#define LChild(i) (((i) << 1) + 1)
#define RChild(i) (((i) + 1) << 1)
#define InHeap(i, n) (((i) >= 0) && ((i) < n))

template <typename T> class PriorityQueue {
    virtual void push(T) = 0;// 按优先级插入词条
    virtual T top() = 0;// 取出优先级最高的词条
    virtual void pop() = 0;// 删除优先级最高的词条
};

template <typename T> class PriorityQueueHeap : public vector<T>, public PriorityQueue<T> {
protected:
    int percolateDown(int n, int i);// 下滤
    int percolateUp(int i);// 上滤
    void heapify(int n);// Floyd建堆算法
public:
    PriorityQueueHeap() {}
    PriorityQueueHeap(T *A, int n) {
        this->copy(A, 0, n);
        heapify(n);
    }
    T top();
    void push(T e);
    void pop();
};

#endif /* PriorityQueue_h */
