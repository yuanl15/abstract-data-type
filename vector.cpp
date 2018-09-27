//
//  vector.cpp
//  datastruct
//
//  Created by Yuan on 2018/6/11.
//

#include "vector.h"
#include <cstdlib>
#include "math.h"

template <typename T>
void vector<T>::copy(T const* A,Rank lo,Rank hi){
    _elem = new T[_capacity = 2*(hi-lo)];
    _size = 0;
    while(lo < hi)
        _elem[_size++] = A[lo++];
}

template <typename T> vector<T>& vector<T>::operator= (vector<T> const& v){//重载
    if(_elem) delete[] _elem;
    copy(v._elem,0,v._size);//整体复制
    return *this;
}

template <typename T> void vector<T>::expand(){
    if(_size < _capacity)
        return;
    if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for(int i=0;i<_size;i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template <typename T> void vector<T>::shrink(){
    if(_capacity < DEFAULT_CAPACITY<<1) return;
    if(_size<<2 < _capacity) return;
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for(int i=0;i<_size;i++) _elem[i] = oldElem[i];
    delete[] oldElem;
}

//重载向量操作符
template <typename T> T& vector<T>::operator[](Rank r)const{return _elem[r];}

template <typename T> void vector<T>::unsort(Rank lo, Rank hi){
    T* V = _elem + lo;
    for(int i=hi-lo;i>0;i--)
        swap(V[i],V[rand()%i]);
}

//顺序查找
template <typename T>
Rank vector<T>::find(T const& e,Rank lo,Rank hi)const{
    while((lo<hi--) && (_elem[hi]!=e));
    return hi;
}

//插入
template<typename T>
Rank vector<T>::insert(Rank r,T const& e){
    expand();
    for(int i=_size;i>r;i--)_elem[i] = _elem[i-1];
    _elem[r] = e;
    _size++;
    return r;
}

//区间删除
template<typename T>
int vector<T>::erase(Rank lo,Rank hi){
    if(lo==hi)return 0;
    while(hi<_size)_elem[lo++] = _elem[hi++];
    _size = hi;
    shrink();
    return hi-lo;
}

template<typename T>
T vector<T>::erase(Rank r){
    T temp = _elem[r];
    erase(r,r+1);
    return temp;
}

//唯一化
template<typename T> int vector<T>::deduplicate(){
    int oldSize = _size;
    Rank i = 1;
    while(i<_size)
        (find(_elem[i],0,i)<0)?i++:erase(i);
    return oldSize - _size;
}

//遍历
template <typename T>void vector<T>::traverse (void(*visit)(T&)){
    for(int i=0;i<_size;i++)visit(_elem[i]);
}

template<typename T> template<typename VST>
void vector<T>::traverse (VST& visit){for(int i=0;i<_size;i++)visit(_elem[i]);}
//for example
//函数指针
template<typename T> void increase(T& e){e++;}
//函数对象
template<typename T> struct Increase{
    void operator() (T& e){e++;}
};
template<typename T> void increase(vector<T> &V){
    V.traverse(Increase<T>() );
}

//有序性判别
template <typename T> int vector<T>::disordered() const{
    int n = 0;//计数器
    for(int i=1;i<_size;i++)
        if(_elem[i-1] > _elem[i])
            n++;
    return n;
}

//有序向量唯一化
template <typename T> int vector<T>::uniquify(){
    int i=0,j=0;
    while(++j<_size){
        if(_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    }
    _size = ++i;
    shrink();
    return j - i;
}

//有序向量查找
template <typename T> Rank vector<T>::search(T const& e,Rank lo,Rank hi){
    return (rand() % 2)?binSearch(_elem,e,lo,hi):fibSearch(_elem,e,lo,hi);
}

//binary search
template <typename T> static Rank binarySearch(T* A,T const& e,Rank lo,Rank hi){
    while(lo < hi){
        Rank mi = (lo + hi) >> 1;
        if(A[mi] < A[hi])
            hi = mi;
        else if(A[mi] > A[lo])
            lo = mi;
        else
            return mi;
    }
    return -1;
}

//fibonacci search
template <typename T> static Rank fibSearch(T* A,T const& e,Rank lo,Rank hi){
    Fib fib(hi-lo);
    while(lo < hi){
        while(hi-lo < fib.get()) fib.prev();
        Rank mi = lo + fib.get() - 1;
        if(e < A[mi]) hi = mi;
        else if(e > A[mi]) lo = mi + 1;
        else
            return mi;
    }
}

//sort algorithm:bubble sort,selectiong sort,merge sort,heap sort,quick sort
template <typename T> void vector<T>::sort(Rank lo,Rank hi){
    switch(rand() % 5){
        case 0:quickSort(lo,hi);break;
        case 1:bubbleSort(lo,hi);break;
        case 2:selectionSort(lo,hi);break;
        case 3:mergeSort(lo,hi);break;
        case 4:heapSort(lo,hi);break;
        default:break;
    }
}
//冒泡排序
template<typename T> void vector<T>::bubbleSort(Rank lo, Rank hi){
    for(int i = hi - 1;i > lo;i--){
        for(int j = lo;j < i;j++){
            if(_elem[j] > _elem[j+1]) swap(_elem[j],_elem[j+1]);
        }
    }
}
//归并排序
template <typename T> void vector<T>::mergeSort(Rank lo, Rank hi){
    if(hi - lo < 2) return;
    int mi = (lo + hi) / 2;
    mergeSort(lo,mi);
    mergeSort(mi, hi);
    T* A = _elem + lo;
    T* B = new T[mi - lo];
    T* C = _elem + mi;
    for(int i=0,j=0,k=0;(j < mi - lo) || (k < hi - mi);){
        if((j < mi - lo) && ((k >= hi - mi) || (B[j] <= C[k]))) A[i++] = B[j++];
        if((k < hi - mi) && ((j >= mi - lo) || (B[j] > C[k]))) A[i++] = C[k++];
    }
    delete[] B;
}
