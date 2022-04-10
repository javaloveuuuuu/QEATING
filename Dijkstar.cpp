/* 
  @ Dijkstra�㷨(�gԴ���·��) 
*/  
#include<iostream>  
#include<cstdio>  
#include<cstdlib>  
#define MAXV 100  
#define LIMITLESS 9999    //����Ϊ�����,Ĭ��Ϊ�ڵ�䲻������ϵ  
using namespace std;  
typedef struct  
{  
   char info; //����������Ϣ  
}VertexType;  
  
typedef struct MGraph  
{  
    int v;     //������  
    int e;    //����  
    int edges[MAXV][MAXV];//�ڽӾ�����������  
    VertexType vexs[MAXV]; //������Ϣ  
}MGraph;  
  
void creat(MGraph *G)  
{  
    int i, j, k, w;  
    int start, end;  
    printf("�����붥�����ͱ���:\n");  
    scanf("%d%d", &(G->v), &(G->e));  
    getchar();  
    printf("�����붥����Ϣ:\n");  
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
    printf("����ͼ�Ķ���ߵ��±�ֵ������Ȩֵ:\n");  
    for (k = 0; k<G->e; k++)  
    {  
        scanf("%d%d%d", &start, &end, &w);  
        G->edges[start][end] = w;  
    }  
}  
  
void print(MGraph *G)  
{  
    int i, j;  
    printf("������:%d,����:%d\n", G->v, G->e);  
    printf("%d���������Ϣ��\n", G->v);  
    for (i = 0; i<G->v; i++)  
    {  
        printf("%5c",G->vexs[i].info);  
    }  
    printf("\n����������������:\n");  
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
  
void Ppath(MGraph *g,int path[], int i, int v) //ǰ��ݹ����·���ϵĶ���,��������������յ��·��ֵ  
{  
    int k;  
    k = path[i];  
    if (k == v)   //���м�ڵ�,�˳�  
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
            printf("��%c��%c�����·������Ϊ:%d\t·��Ϊ:", g->vexs[v], g->vexs[i], dist[i]);  
            printf("%c",g->vexs[v]);     //���·���ϵ����  
            Ppath(g,path, i, v);  //���·���ϵ��м��  
            printf("%c\n",g->vexs[i]); //���·���ϵ��յ�  
        }  
        else  
        {  
            printf("��%c��%c������·��\n", g->vexs[v], g->vexs[i]);  
        }  
    }  
}  
  
void Dijkstra(MGraph *g, int v)  
{  
    int mindis, i, j, u;  
    int s[MAXV];     //��ʾ��������Ƿ�������·����(0��ʾδ����,1��ʾ�Ѽ���)  
    int dist[MAXV]; //��ʾ��ʼ�㵽�˶���ľ���  
    int path[MAXV];//��ʾ�˵����һ������һ������  
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
        mindis = LIMITLESS;         //mindis����С���ȳ�ֵ  
        for (j = 0; j < g->v; j++) //ѡȡ����s���Ҿ�����С����Ķ���u  
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
