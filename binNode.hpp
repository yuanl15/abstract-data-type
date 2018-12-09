//
//  binNode.hpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/8/19.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#ifndef binNode_hpp
#define binNode_hpp

#include <stdio.h>
#include <stdlib.h>
#define BinNodePosi(T) binNode<T>*  //节点位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度
/******************************************************************
 *binNode状态与性质的判断
 *****************************************************************/
#define IsRoot(x) (!(x).parent)
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) (HasLChild(x) || HasRChild(x))//至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))//有两个孩子
#define IsLeaf(x) (!HasChild(x))//叶节点判断
/******************************************************************
 *与binNode具有特定关系的节点及指针
 ******************************************************************/
#define sibling(p) /*兄弟*/\
(IsLChild(*(p) ) ? (p)->parent->rc:(p)->parent->lc)

#define uncle(x) /*叔叔*/\
(IsLChild( (x)->parent ) ? x->parent->parent->rc : x->parent->parent->lc )

#define FromParentTo(x) /*来自父亲的引用*/ \
(IsRoot(x) ? this->_root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))

typedef enum {RB_RED,RB_BLACK} RBColor;

template <typename T> struct binNode{
    T data;//数值
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc;
    int height;//高度
    int npl;//Null Path Length左式堆
    RBColor color;
    binNode():
        parent(NULL),lc(NULL),rc(NULL),height(0),npl(1),color(RB_RED){}
    binNode(T e,BinNodePosi(T) p = NULL,BinNodePosi(T) lc = NULL,BinNodePosi(T) rc = NULL,int h = 0,int l = 1,RBColor c = RB_RED):
    data(e),parent(p),lc(lc),rc(rc),height(h),npl(l),color(c){}
    
    //操作接口
    int size();//统计当前节点后代总数
    BinNodePosi(T) insertAsLC(T const& );//插入节点作为当前节点左子节点
    BinNodePosi(T) insertAsRC(T const& );//作为右子节点插入
    BinNodePosi(T) succ();//提取当前节点的直接后继
    template <typename VST> void travLevel (VST & );//子树层次遍历
    template <typename VST> void travPre (VST& );//子树先序遍历
    template <typename VST> void travIn(VST& );//子树中序遍历
    template <typename VST> void travPost(VST& );//子树后序遍历
    //比较器、判等器
    bool operator < (binNode const& bn){return data<bn.data;}
    bool operator == (binNode const& bn){return data == bn.data;}
};
#endif /* binNode_hpp */
