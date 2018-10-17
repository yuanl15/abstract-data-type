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
    Tv data;//数据
    int inDegree;//出度
    int outDegree;//入读
    VStatus status;//状态
    int dTime, fTime;//时间标签
    int parent;//遍历树中父节点
    int priority;//遍历树中优先级数
    
    //构造函数
    vertex(Tv const& d = (Tv)0):
        data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),
        dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}//暂不考虑权重溢出
};

//边对象（未严格封装）
template <typename Te> struct edge{
    Te data;//数据
    int weight;//权重
    EType type;//类型
    edge(Te const& d,int w):data(d),weight(w),type(UNDETERMINED){}
};

/**
 * 基于邻接矩阵实现的图
 **/
template <typename Tv,typename Te> class GraphMatrix : public graph<Tv,Te>{
private:
    vector<vertex<Tv> > V;//顶点集（向量）
    vector<vector<edge<Te>* > > E;//边集（邻接矩阵）
public:
    GraphMatrix(){this->n = this->e = 0;}//构造
    ~GraphMatrix(){//析构
        for(int j = 0;j < this->n;j++)//所有动态创建的边记录
            for(int i = 0;i < this->e;i++)
                delete E[j][i];
    }
    
    //顶点基本操作：查询第i个顶点（0<=i<n)
    virtual Tv& vertexData(int i){return V[i].data;}//数据
    virtual int inDegree(int i){return V[i].inDegree;}//入度
    virtual int outDegree(int i){return V[i].outDegree;}//出度
    virtual int firstNbr(int i){return nextNbr(i,this->n);}//首个邻接顶点
    virtual int nextNbr(int i,int j){//相对于顶点j的下一个邻接顶点（该用邻接表可提高效率）
        while((j>-1) && (!this->exists(i,--j)));//逆向线性试探
        return j;
    }
    virtual VStatus status(int i){return V[i].status;}//状态
    virtual int& dTime(int i){return V[i].dTime;}//时间标签dTime
    virtual int& fTime(int i){return V[i].fTime;}//时间标间fTime
    virtual int& parent(int i) { return V[i].parent; }//遍历树中父亲
    virtual int& priority(int i) { return V[i].priority; }//遍历树中优先级
    
    //顶点的动态操作
    virtual int insert(Tv const& vertexVal){ //插入顶点，返回编号
        for( int j = 0; j < this->n; j++) E[j].insert(NULL);//每个顶点预留一条潜在的关联边
        this->n++;//顶点数自增
        E.insert( vector<edge<Te>*>(this->n, this->n, (edge<Te>*) NULL) );//新增顶点与其他顶点相连的边
        return V.insert( vertex<Tv>(vertexVal) );
    }
    
    virtual Tv remove(int i){//删除顶点及其关联边
        for( int j = 0; j < this->n; j++){//所有出边
            if( this->exsits(i,j) ){
                delete E[i][j];
                V[j].inDegree--;
            }
        }
        E.erase(i);//删除第i行
        Tv vBak = vertexData(i);
        V.erase(i);
        this->n--;
        for( int j = 0; j < this->n; j++){
            if( edge<Te> * e = E[j].erase(i) ){
                delete e;
                V[j].outDegree--;
            }
        }
        return vBak;
    }
    
    //边的确认操作
    virtual bool exists(int i,int j){
        return (i >= 0) && (i < this->n) && (j >= 0) && (j < this->n) && (NULL != E[i][j]);
    }
    
    //边的基本操作:查询顶点i与j之间的联边（0 <= i,j < n且exists(i,j)）
    virtual EType& type( int i, int j){ return E[i][j]->type; }//边（i，j）类型
    virtual Te& edgeData( int i, int j){ return E[i][j]->data; }//边（i，j）数据
    virtual int& weight(int i, int j){ return E[i][j]->weight; }//边（i，j）权重
    
    //边的动态操作
    virtual void insert(Te const& eg, int w, int i, int j){//插入权重为w的边e=（i，j）
        if( exists(i,j) ) return;
        E[i][j] = new edge<Te>(eg,w);
        this->e++;
        V[i].outDegree++;
        V[j].inDegree++;
    }
    virtual Te remove( int i, int j){
        Te eBak = edgeData(i,j);
        delete E[i][j];
        E[i][j] = NULL;
        this->e--;
        V[i].outDegree--;
        V[j].inDegree--;
        return eBak;
    }
};

template <typename Tv,typename Te>//广度优先搜索（全图）
void graph<Tv,Te>::bfs(int s){
    reset();
    int clock = 0;
    int v = s;
    do//逐一检查所有顶点
        if( UNDISCOVERED == status(v) )
            BFS(v, clock);
    while( s != ( v = ( v++ % n ) ) );//按序号检查
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
                status(u) = DISCOVERED;//遍历后改变邻居状态
                type(v, u) = TREE;
                parent(u) = v;//引入树边拓展支撑树
            }
            else{//若u已被发现，或者已访问完毕
                type(v, u) = CROSS;//将边归类于跨边
            }
        status(v) = VISITED;
    }
    
}

template<typename Tv,typename Te>//深度优先搜索（全图）
void graph<Tv, Te>::dfs(int s){
    reset();
    int clock = 0;
    int v = s;
    do//逐一检查
        if(UNDISCOVERED == status(v))
           DFS(v, clock);
    while(s == (v = (++v % n)));
}

template<typename Tv,typename Te>//深度优先搜索（单连通域）
void graph<Tv,Te>::DFS(int v, int& clock){
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u)){
        switch(status(u)){
            case UNDISCOVERED:
                type(v, u) = DISCOVERED;
                parent(u) = v;
                DFS(u, clock);
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                break;
            default:
                type(v, u) = (dTime(v) < dTime(u))? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
    fTime(v) = ++clock;
}

//基于DFS的拓扑排序算法
template <typename Tv, typename Te>
stack<Tv>* graph<Tv,Te>::tSort(int s){
    reset();
    int clock = 0;
    int  v = s;
    stack<Tv>* S = new stack<Tv>;
    do{
        if(UNDISCOVERED == status(v))
            if(!TSort(v, clock, S)){
                while(!S->empty()){
                    S->pop();
                    break;
                }
            }
    }
    while(s != (v = (++v % n)));
    return S;
}

template <typename Tv, typename Te>
bool graph<Tv, Te>::TSort(int v, int& clock, stack<Tv>* S){
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    for(int u = firstNbr(v); -1 < u; u= nextNbr(v, u))
        switch(status(u)){
            case UNDISCOVERED:
                parent(u) = v;
                type(v, u) = TREE;
                if(!TSort(u, clock, S))
                    return false;
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                return false;
            default:
                type(v, u) = (dTime(v) < dTime(u))? FORWARD : CROSS;
                break;
        }
    status(v) = VISITED;
    S->push( vertexData(v) );
    return true;
}

//优先级搜索（全图）
template <typename Tv, typename Te> template <typename PU>
void graph<Tv, Te>::pfs(int s, PU prioUpdater){
    reset();
    int v = s;
    do
        if(UNDISCOVERED == status(v))
            PFS(v, prioUpdater);
    while(s != (v = (++v % n)));
}

template <typename Tv, typename Te> template <typename PU>
void graph<Tv, Te>::PFS(int s, PU prioUpdater){
    priority(s) = 0;
    status(s) = VISITED;
    parent(s) = -1;
    while(1){
        for(int w = firstNbr(s); -1 < w; w = nextNbr(s, w))
            prioUpdater(this, s, w);
        for(int shortest = INT_MAX, w = 0; w < n; w++)
            if(UNDISCOVERED == status(w))
                if(shortest > priority(w)){
                    shortest = priority(w);
                    s = w;
                }
        if(VISITED == status(s)) break;
        status(s) = VISITED;
        type(parent(s), s) = TREE;
    }
}

//最短路径算法
template <typename Tv, typename Te> struct DijkstraPU{
    virtual void operator() (graph<Tv, Te>* g, int uk, int v){
        if( UNDISCOVERED == g->status(v))
            if(g->priority(v) > g->prority(uk) + g->weight(uk,v)){
                g->priority(v) = g->priority(uk) + g->weight(uk,v);
                g->parent(v) = uk;
            }
    }
};
