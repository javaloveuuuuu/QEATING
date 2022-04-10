/* 
  @ Dijkstra算法(単源最短路径) 
*/  
#include<iostream>  
#include<cstdio>  
#include<cstdlib>  
#define MAXV 100  
#define LIMITLESS 9999    //定义为无穷大,默认为节点间不存在联系  
using namespace std;  
typedef struct  
{  
   char info; //顶点其他信息  
}VertexType;  
  
typedef struct MGraph  
{  
    int v;     //顶点数  
    int e;    //边数  
    int edges[MAXV][MAXV];//邻接矩阵的数组表现  
    VertexType vexs[MAXV]; //顶点信息  
}MGraph;  
  
void creat(MGraph *G)  
{  
    int i, j, k, w;  
    int start, end;  
    printf("请输入顶点数和边数:\n");  
    scanf("%d%d", &(G->v), &(G->e));  
    getchar();  
    printf("请输入顶点信息:\n");  
    for (i = 0; i<G->v; i++)  
    {  
        scanf("%c", &(G->vexs[i].info));  
    }  
    for (i = 0; i<G->v; i++)  
    {  
        for (j = 0; j<G->v; j++)  
        {  
            G->edges[i][j] = LIMITLESS;  
        }  
    }  
    printf("输入图的顶点边的下标值和它的权值:\n");  
    for (k = 0; k<G->e; k++)  
    {  
        scanf("%d%d%d", &start, &end, &w);  
        G->edges[start][end] = w;  
    }  
}  
  
void print(MGraph *G)  
{  
    int i, j;  
    printf("顶点数:%d,边数:%d\n", G->v, G->e);  
    printf("%d个顶点的信息：\n", G->v);  
    for (i = 0; i<G->v; i++)  
    {  
        printf("%5c",G->vexs[i].info);  
    }  
    printf("\n各个顶点的连接情况:\n");  
    printf("\t");  
    for (i = 0; i<G->v; i++)  
    {  
        printf("[%d]\t", i);  
    }  
    printf("\n");  
    for (i = 0; i<G->v; i++)  
    {  
        printf("[%d]\t", i);  
        for (j = 0; j<G->v; j++)  
        {  
            if (G->edges[i][j] == LIMITLESS)  
            {  
                printf("oo\t");  
            }  
            else  
            {  
                printf("%d\t", G->edges[i][j]);  
            }  
        }  
        printf("\n");  
    }  
}  
  
void Ppath(MGraph *g,int path[], int i, int v) //前向递归查找路径上的顶点,但不包含起点与终点的路径值  
{  
    int k;  
    k = path[i];  
    if (k == v)   //无中间节点,退出  
    {  
        return;  
    }  
    Ppath(g,path, k, v);  
    printf("%c",g->vexs[k]);  
}  
  
void Dispath(MGraph *g,int dist[], int path[], int s[], int n, int v)  
{  
    int i;  
    for (i = 0; i < n; i++)  
    {  
        if (s[i] == 1)  
        {  
            printf("从%c到%c的最短路径长度为:%d\t路径为:", g->vexs[v], g->vexs[i], dist[i]);  
            printf("%c",g->vexs[v]);     //输出路径上的起点  
            Ppath(g,path, i, v);  //输出路径上的中间点  
            printf("%c\n",g->vexs[i]); //输出路径上的终点  
        }  
        else  
        {  
            printf("从%c到%c不存在路径\n", g->vexs[v], g->vexs[i]);  
        }  
    }  
}  
  
void Dijkstra(MGraph *g, int v)  
{  
    int mindis, i, j, u;  
    int s[MAXV];     //表示这个顶点是否存入最短路线中(0表示未加入,1表示已加入)  
    int dist[MAXV]; //表示起始点到此顶点的距离  
    int path[MAXV];//表示此点的上一步是哪一个顶点  
    for (i = 0; i < g->v; i++)  
    {  
        s[i] = 0;  
        dist[i] = g->edges[v][i];  
        if (g->edges[v][i] < LIMITLESS)  
        {  
            path[i] = v;  
        }  
        else  
        {  
            path[i] = -1;  
        }  
    }  
    s[v] = 1;  
    path[v] = 0;  
    for (i = 0; i < g->v; i++)  
    {  
        mindis = LIMITLESS;         //mindis置最小长度初值  
        for (j = 0; j < g->v; j++) //选取不在s中且具有最小距离的顶点u  
        {  
            if (s[j] == 0 && dist[j] <mindis)  
            {  
                mindis = dist[j];  
                u = j;  
            }  
        }  
        s[u] = 1;  
        for (j = 0; j < g->v; j++)  
        {  
            if (s[j] == 0)  
            {  
                if (g->edges[u][j] < LIMITLESS&&dist[u] + g->edges[u][j] < dist[j])  
                {  
                    dist[j] = dist[u] + g->edges[u][j];  
                    path[j] = u;  
                }  
            }  
        }  
    }  
    Dispath(g ,dist, path, s, g->v, v);  
}  
  
int main(void)  
{  
    MGraph *g;  
    g = (MGraph *)malloc(sizeof(MGraph));  
    creat(g);  
    print(g);  
    Dijkstra(g,0);  
    return 0;  
}  
