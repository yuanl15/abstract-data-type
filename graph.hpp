//
//  graph.hpp
//  HelloWorld
//
//  Created by 袁麓 on 2018/9/14.
//  Copyright © 2018年 袁麓. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <limits.h>
#include "stack.hpp"


typedef enum{ UNDISCOVERED, DISCOVERED, VISITED } VStatus;//顶点状态
typedef enum{ UNDETERMINED, TREE, CROSS,FORWARD, BACKWARD } EType;//边在遍历树中所属类型
template <typename Tv , typename Te>//顶点类型、边类型
class graph{
private:
    //所有顶点、边的辅助信息复位
    void reset(){
        for(int i=0;i<n;i++){
            status(i) = UNDISCOVERED;//状态标签
            dTime(i) = fTime(i) = -1;//时间标签
            parent(i) = -1;
            priority(i) = INT_MAX;//遍历树中父节点，优先级数
            for(int j=0;j<n;j++)//所有的边
                if(exists(i,j))
                    type(i,j) = UNDETERMINED;
        }
    }
    
    //连通域广度优先搜索算法
    void BFS(int , int& );
    
    //连通域广度优先算法
    void DFS(int , int& );
    
    //连通域给予DFS的双连通分量分解算法
    void BCC(int ,int& ,stack<int>&);
    
    //基于DFS的拓扑排序算法
    bool TSort(int ,int& ,stack<Tv>* );
    
    //优先级搜索框架
    template <typename PU>void PFS(int,PU);
    
public:
//顶点
    int n;//顶点总数
    virtual int insert(Tv const& ) = 0;//插入顶点返回编号
    virtual Tv remove (int ) = 0;//删除顶点及其关联边，返回该顶点信息
    virtual Tv& vertex(int ) = 0;//顶点v的数据（该顶点的确存在）
    virtual int inDegree(int ) = 0;//顶点v的出度
    virtual int firstNbr(int) = 0;//顶点v的首个邻接顶点
    virtual int nextNbr(int,int) = 0;//顶点v的（相对于顶点j的）下一邻接顶点
    virtual VStatus& status(int) = 0;//顶点v的状态
    virtual int& dTime(int) = 0;//顶点v的时间标签
    virtual int& fTime(int) = 0;//顶点v的时间标签fTime
    virtual int& parent(int) = 0;//顶点v在遍历树中的父亲
    virtual int& priority(int) = 0;//顶点v在遍历树中的优先级数
    
//边：这里约定无向边均转化为方向互逆的一对有向边，从而将无向图视为有向图的特例
    int e;//边总数
    virtual bool exists(int,int) = 0;//边v，u是否存在
    virtual void insert(Te const&, int, int, int) = 0;//在顶点v，u之间插入权重为w的边e
    virtual Te remove(int, int) = 0;//删除顶点v，u之间的边e，返回该边信息
    virtual EType& type(int, int) = 0;//边（v，u）的类型
    virtual Te& edge(int, int) = 0;//边（v，u）的数据
    virtual int& weight(int, int) = 0;//边（v，u）的权重
//算法
    void bfs(int);//广度优先搜索算法
    void dfs(int);//深度优先搜索算法
    void bcc(int);//基于DFS的双连通分量分解算法
    stack<Tv>* tSort(int);//基于DFS的拓扑排序算法
    void prim(int);//最小支撑树Prim算法
    void dijkstra(int);//最短路径Dijkstra算法
    template <typename PU>void pfs(int,PU);//优先级搜索框架
};
#endif /* graph_hpp */
