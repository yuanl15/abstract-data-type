//
//  graph.cpp
//  HelloWorld
//  基于邻接矩阵实现的图
//  Created by 袁麓 on 2018/9/14.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#include "vector.h"
#include "graph.hpp"
#include "queue.hpp"

//顶点对象（未严格封装)
template <typename Tv> struct vertex{
    
};

//边对象（未严格封装）
template <typename Te> struct edge{
    
};

/**
 * 基于邻接矩阵实现的图
 **/
template <typename Tv,typename Te> class GraphMatrix : public graph<Tv,Te>{
private:
    vector<vertex<Tv> > V;//顶点集（向量）
    vector<vector<edge<Te>* > > E;//边集（邻接矩阵）
};

template <typename Tv,typename Te>//广度优先搜索（全图）
void graph<Tv,Te>::bfs(int s){
    
}

template <typename Tv,typename Te>//广度优先搜索（单连通域）
void graph<Tv,Te>::BFS(int v, int & clock){
    queue<int> Q;//引入辅助队列
    status(v) = DISCOVERED;
    Q.push(v);//初始化起点
    while(!Q.empty()){
        int w = Q.pop();
        dTime(w) = ++clock;
        for(int u = firstNbr(w);-1<u;u=nextNbr(w,u))//枚举w的所有邻居
            if(UNDISCOVERED == status(u)){
                status(u) = 
            }
        
    }
    
}
