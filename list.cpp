//
//  list.cpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/7/14.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#include "list.hpp"
#include <stdlib.h>
template<typename T> void list<T>::init(){//列表初始化，在创建列表对象时统一调用
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;//记录规模
}

//构造函数，复制列表
template<typename T> list<T>::list(list<T> const &L){
    init();
    int len = L.size();
    if(len > 0){
        ListNode<T>* p = L.first();//获取首节点
        while(len-- > 0){
            
        }
        
    }
}

//构造函数，复制节点p开始列表n个元素
template<typename T> list<T>::list(ListNode<T>* p,int n){ copyNode(p,n); }

//构造函数，复制列表第r个元素开始共n个
template<typename T> list<T>::list(list<T> const &L,int r,int n){copyNodes(L[r],n);}

//重载寻秩运算符
template<typename T>
T& list<T>::operator[](Rank r)const{
    ListNode<T>* p = first();
    while(r-- > 0)
        p = p->succ;
    return p->data;
}

//无序查找
template<typename T> ListNode<T>* list<T>::find(T const &e,int n,ListNode<T>* p)const{
    while(n-- > 0){
        if((p=p->pred)->data == e)
            return p;
        else
            p = p->succ;
    }
    return NULL;
}

//插入
template <typename T> ListNode<T>* list<T>::insertAsFirst(const T &e){
    _size++;
    return header->insertAsSucc(e);
}

template<typename T> ListNode<T>* list<T>::insertAsLast(const T &e){
    _size++;
    return trailer->insertAsPred(e);
}

template<typename T> ListNode<T>* list<T>::insertA(ListNode<T>* p,T const& e){
    _size++;
    return p->insertAsSuccc(e);
}

template<typename T> ListNode<T>* list<T>::insertB(ListNode<T>* p,T const& e){
    _size++;
    return p->insertAsPred(e);
}

//复制
template<typename T> void list<T>::copyNodes(ListNode<T>* p,int n){
    init();//创建头尾哨兵
    while(n--){
        insertAsLast(p->data);
        p = p->succ;
    }
}

//删除
template<typename T> T list<T>::remove(ListNode<T>* p){
    T temp = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return temp;
}

//析构函数
template<typename T> list<T>::~list(){
    clear();
    delete header;
    delete trailer;
}

//清空
template<typename T> int list<T>::clear(){
    int oldSize = _size;
    while(_size > 0)remove(header->succ);
    return oldSize;
}

//无序去重
template<typename T> int list<T>::deduplicate(){
    if(_size < 2) return 0;
    int oldSize = _size;
    ListNode<T>* p = header;
    Rank r = 0;
    while(trailer != (p = p->succ)){
        ListNode<T>* q = find(p->data,r,p);
        q?remove(q):r++;
    }
    return oldSize - _size;
}

//遍历
template<typename T> void list<T>::traverse(void (*visit)(T&)){
    for(ListNode<T>* p = header->succ;p!=trailer;p=p->succ)visit(p->data);
}

template<typename T> template<typename VST> void list<T>::traverse(VST& visit){
    for(ListNode<T>* p=header->succ;p!=trailer;p=p->succ)
        visit(p->data);
}

template<typename T> int list<T>::uniquify(){
    int oldSize = _size;
    if(_size < 2) return 0;
    ListNode<T>* p = first();
    ListNode<T>* q;
    while(trailer != (q = p->succ)){
        if(q->data == p->data) remove(q);
        else p = q;
    }
    return oldSize - _size;
}

template<typename T> ListNode<T>* list<T>::search(T const& e,int n,ListNode<T>* p)const{
    while(n-- >= 0)
        if(((p=p->pred)->data) <= e) break;
    return p;
}

template<typename T> void list<T>::sort(ListNode<T>* p,int n){
    switch(rand() % 3){
        case 1: insertionSort(p,n);break;
        case 2: selectionSort(p,n);break;
        default: mergeSort(p, n);break;
    }
}

template<typename T> void list<T>::insertionSort(ListNode<T> * &p, int n){
    for(int r=0;r<n;r++){
        insertA(search(p->data,r,p),p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template<typename T> void list<T>::selectionSort(ListNode<T> * &p, int n){
    ListNode<T>* head = p->pred;
    ListNode<T>* tail = p;
    for(int i=0;i<n;i++)tail = tail->succ;
    while(1<n){
        ListNode<T>* max = selectMax(head->succ,n);
        insertB(tail,remove(max));
        tail = tail->pred;
        n--;
    }
}

template<typename T> ListNode<T>* list<T>::selectMax(ListNode<T>* p,int n){
    ListNode<T>* max = p;
    for(ListNode<T>* cur = p;1<n;n--)
        if(!lt((cur=cur->succ)->data,max->data))
            max = cur;
    return max;
}

template<typename T> void list<T>::merge(ListNode<T>* &p, int n, list<T> &L, ListNode<T> *q, int m){
    ListNode<T>* pp = p->pred;
    while(0<m)
        if((0<n) && (p->data <= q->data)){
            if(q == (p=p->succ)) break;
            n--;
        }
        else{
            insertB(p,L.remove((q = q->succ)->pred));
            m--;
        }
    p = pp->succ;
}

template<typename T> void list<T>::mergeSort(ListNode<T>* &p, int n){
    if(n<2) return;
    int m= n >> 1;
    ListNode<T>* q = p;
    for(int i=0;i<m;i++)q = q->succ;
    mergeSort(p,m);
    mergeSort(q,n-m);
    merge(p,m,*this,q,n-m);
}
