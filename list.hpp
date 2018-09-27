//
//  list.hpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/7/14.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#ifndef list_hpp
#define list_hpp

#include <stdio.h>
#include "listNode.hpp"

template <typename T> class list{
private:
    int _size;
    ListNode<T> header;
    ListNode<T> trailer;
    
protected:
    void init();//创建列表初始化
    int clear();//清楚所有节点
    void copyNodes(ListNode<T>* ,int );
    void merge(ListNode<T>* &p,int n,list<T> &L,ListNode<T>* q,int m);
    void mergeSort(ListNode<T>* &,int );//归并排序
    void selectionSort(ListNode<T>* &,int );//选择排序
    void insertionSort(ListNode<T>* &,int );//插入排序
public:
    list(){init();}
    list(list<T> const& L);//整体复制列表
    list(list<T> const& L,Rank r,int n);
    list(ListNode<T>* p,int n);
    ~list();
    Rank size() const{return _size;}
    bool empty() const{return _size <= 0;}
    T& operator[](Rank r)const;//重载，支持寻秩访问
    ListNode<T>* first()const{return header->succ;}//首节点位置
    ListNode<T>* last()const{return trailer->pred;}//末节点位置
    bool valid(ListNode<T>* p){return p && (p!=header) && (p!=trailer);}//判断位置p是否对外合法
    int disordered() const;//判断是否已排序
    ListNode<T>* find(T const& e)const{return find(e,_size,trailer);}//无序列表查找
    ListNode<T>* find(T const& e,int n,ListNode<T>* p)const;//无序区间查找
    ListNode<T>* search(T const& e)const{return search(e,_size,trailer);}
    ListNode<T>* search(T const& e,int n,ListNode<T>* p) const;
    ListNode<T>* selectMax(ListNode<T>* p,int n);//在p及其后n-1个节点中选出最大者
    ListNode<T>* selectMax(){return selectMax(header->succ,_size);}//在列表中选出最大值
    ListNode<T>* insertAsFirst(T const& e);//将e当作首节点插入
    ListNode<T>* insertAsLast(T const& e);//将e当作末节点插入
    ListNode<T>* insertA(ListNode<T>* p,T const& e);//将e当作p的后继插入
    ListNode<T>* insertB(ListNode<T>* p,T const& e);//将e当作p的前驱插入
    T remove(ListNode<T>* p);//删除合法位置p处的节点
    void sort(ListNode<T>* p,int n);//列表区间排序
    void sort(){sort(first(),_size);}
    int deduplicate();//无序去重
    int uniquify();//有序去重
    void reverse();//前后倒置
    void traverse(void (*) (T&));//遍历
    template<typename VST>void traverse(VST&);//函数对象实现的遍历
    
};
#endif /* list_hpp */
