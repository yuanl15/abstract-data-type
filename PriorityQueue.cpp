//
//  PriorityQueue.cpp
//  abstract-data-type
//
//  Created by 袁麓 on 2019/8/31.
//  Copyright © 2019 袁麓. All rights reserved.
//

#include <stdio.h>
#include "PriorityQueue.h"

template <typename T> T PriorityQueueHeap<T>::top() {
    return this->_elem[0];
}

// 存入元素, 先插入后上滤
template <typename T> void PriorityQueueHeap<T>::push(T e) {
    this->insert(e);
    percolateUp(this->_size - 1);
}

// 删除元素， 先删除，取末尾元素至堆顶，再采用下滤
template <typename T> void PriorityQueueHeap<T>::pop() {
    this->_elem[0] = this->_elem[--this->_size];
    percolateDown(this->_size, 0);
}

// 上滤算法
template <typename T> int PriorityQueueHeap<T>::percolateUp(int pos) {
    while (pos > 0) {
        int parentIndex = Parent(pos);
        if (this->_elem[parentIndex] >= this->_elem[pos]) break;
        this->swap(this->_elem[parentIndex], this->_elem[pos]);
        pos = parentIndex;
    }
    return pos;
}

// 下滤算法
template <typename T> int PriorityQueueHeap<T>::percolateDown(int n, int i) {
    while (i < this->_size) {
        int leftIndex = LChild(i);
        leftIndex = InHeap(leftIndex, this->_size) ? leftIndex : i;
        int rightIndex = RChild(i);
        rightIndex = InHeap(rightIndex, this->_size) ? rightIndex : i;
        int maxIndex = this->_elem[i] >= this->_elem[leftIndex] ? i : leftIndex;
        maxIndex = this->_elem[maxIndex] >= this->_elem[rightIndex] ? maxIndex : rightIndex;
        if (maxIndex == i) break;
        else {
            this->swap(this->_elem[maxIndex], this->_elem[i]);
            i = maxIndex;
        }
    }
    return i;
}
