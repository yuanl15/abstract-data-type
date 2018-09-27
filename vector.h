//
//  vector.hpp
//  datastruct
//
//  Created by Yuan on 2018/6/11.
//

#ifndef vector_hpp
#define vector_hpp

#include <cstdio>
#include "algorithm"

typedef int Rank;//秩
#define DEFAULT_CAPACITY 3
template <typename T> class vector{//向量模板类
protected:
    Rank _size;int _capacity;T* _elem;//规模、容量、数据区
    void copy(T const* A,Rank lo,Rank hi);//复制数组区间A[lo,hi)
    void expand();//空间不足时扩容
    void shrink();//装填因子过小时压缩
    //bool bubble(Rank lo,Rank li);//扫描交换
    void bubbleSort(Rank lo,Rank hi);//起泡排序
    Rank max(Rank lo,Rank hi);//获取最大元素
    void selectionSort(Rank lo,Rank hi);//选择排序
    void merge(Rank lo,Rank hi);//归并算法
    void mergeSort(Rank lo,Rank hi);//归并排序算法
    Rank partition(Rank lo,Rank hi);//轴点构造算法
    void quickSort(Rank lo,Rank hi);//快速排序算法
    void heapSort(Rank lo,Rank hi);//堆排序算法
public:
    vector(int c = DEFAULT_CAPACITY,int s=0,T v=0){_elem = new T[_capacity=c];for(_size=0;_size<s;_elem[_size++]=v);}//容量、规模、初始值
    vector(T const* A,Rank n){copy(A,0,n);}//复制数组
    vector(vector<T> const& V){copy(V._elem,0,V._size);}//复制向量
    vector(vector<T> const& V,Rank lo,Rank hi){copy(V._elem,lo,hi);}//区间复制
    ~vector(){delete [] _elem;}
    Rank size(){return _size;}
    bool empty(){return !_size;}
    int disordered() const;
    Rank find(T const& e) const{return find(e,0,_size);}//无序查找
    Rank find(T const& e,Rank lo,Rank hi) const;
    Rank search(T const& e)const
    {return _size>0?-1:search(e,0,_size);}
    Rank search(T const& e,Rank lo,Rank hi);
    //可写访问接口
    T& operator[](Rank r)const;//重载下标操作符
    vector<T>& operator=(vector<T> const&);
    T erase(Rank r);//删除单个元素
    int erase(Rank lo,Rank hi);//删除区间元素
    Rank insert(Rank r,T const& e);
    Rank insert(T const& e){return insert(_size,e);}
    void sort(Rank lo,Rank hi);
    void sort(){sort(0,_size);}
    void unsort(Rank lo,Rank hi);//乱序
    void unsort(){unsort(0,_size);}
    int deduplicate();//无序去重
    int uniquify();//有序去重
    //遍历
    void traverse(void (*)(T&));//函数指针
    template <typename VST> void traverse(VST&);
    void swap(T &a,T &b){
        T temp = a;
        a = b;
        b = a;
    }
};


#endif /* vector_hpp */
