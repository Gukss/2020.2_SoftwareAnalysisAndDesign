#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEXS 50

int visited[MAX_VERTEXS];
int count = 1;
typedef struct _Node
{
    int data;
    struct Node* link;
}Node;

typedef struct _GraphType
{
    int n;
    struct Node* adj_list[MAX_VERTEXS];
}GraphType;

void Init(GraphType* G, int vertex)
{
    G->n = vertex;
    for (int i = 0; i < MAX_VERTEXS; i++)
    {
        G->adj_list[i] = NULL;
    }
}

void InsertEdge(GraphType* G, int u, int v)
{
    Node* vertex = (Node*)malloc(sizeof(Node));
    vertex->data = v;
    vertex->link = G->adj_list[u];
    G->adj_list[u] = vertex;
}

void Dfs(GraphType* G, int v)
{
    visited[v] = count;
    printf("%d -> ", v);
    for (Node* i = G->adj_list[v]; i; i = i->link)
    {
        if (!visited[i->data])
        {
            Dfs(G, i->data);
        }
    }
}

int Component(GraphType* G)
{
    for (int i = 0; i < G->n; i++)
    {
        if (!visited[i])
        {
            printf("%d번 : ", count);
            Dfs(G, i);
            count++;
            printf("\n\n");
        }
    }
    if (count - 1 == 1)
    {
        printf("연결되어 있습니다.\n");
    }
    else
    {
        printf("연결되어 있지 않습니다.\n");
        printf("컴포넌트 : %d개", count - 1);
    }
    return count - 1;
}

void main(void)
{
    GraphType* G = (GraphType*)malloc(sizeof(GraphType));
    int vertex = 4;
    int number;
    Init(G, vertex);
    /*InsertEdge(G, 0, 3);
    InsertEdge(G, 0, 4);
    InsertEdge(G, 3, 0);
    InsertEdge(G, 3, 4);
    InsertEdge(G, 4, 0);
    InsertEdge(G, 4, 3);
    InsertEdge(G, 4, 1);
    InsertEdge(G, 1, 4);
    InsertEdge(G, 2, 5);
    InsertEdge(G, 5, 2);*/
    //vertex값 바꾸고 실행하기
    InsertEdge(G, 0, 3);
    InsertEdge(G, 0, 1);
    InsertEdge(G, 2, 3);
    InsertEdge(G, 2, 1);
    InsertEdge(G, 1, 0);
    InsertEdge(G, 1, 2);
    InsertEdge(G, 3, 0);
    InsertEdge(G, 3, 2);
    Component(G);
}