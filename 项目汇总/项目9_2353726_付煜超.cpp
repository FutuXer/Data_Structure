#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 100;
const int MAXM = 1005;

struct Edge 
{
    int from, to, weight, next;  //起点、终点、权值、下一条边index
} edges[MAXM];

int head[MAXN], inDegree[MAXN], outDegree[MAXN];   //头指针数组、入度、出度
int early[MAXN], late[MAXN], Order[MAXN];          //最早完成、最晚完成、排序后节点
int n, m, edgeCount;                               //N M 当前边

//初始化设置
void init() 
{
    edgeCount = 0; 
    for (int i = 1; i <= n; i++)
    {
        head[i] = -1;     
        inDegree[i] = 0;   
        early[i] = 0;     
        late[i] = 0;
    }
}

//添加有向边
void addEdge(int u, int v, int w)
{
    edges[edgeCount] = { u, v, w, head[u] };  //新增边的起点、终点、权值和指向的下一条边
    head[u] = edgeCount++;                    //更新节点 u 的top，指向最新的边
    inDegree[v]++;                            //更新 v 的入度
}

//拓扑排序判断是否有有向环
bool topoSort()
{
    int queue[MAXN], front = 0, prev = 0;
    //入度为 0 的节点入队
    for (int i = 1; i <= n; i++)
    {
        if (inDegree[i] == 0)
        {
            queue[prev++] = i;
        }
    }
    int index = 0;
    //其它
    while (front < prev)
    {
        int temp = queue[front++];
        Order[index++] = temp;
        for (int i = head[temp]; i != -1; i = edges[i].next)
        {
            int v = edges[i].to;     
            if (--inDegree[v] == 0)  // 若的入度减为 0，则入队
            {
                queue[prev++] = v;
            }
        }
    }
    return index == n;               //返回剩余节点的数量
}

//计算输出结果
void sumPath()
{
    //最早时间
    for (int i = 0; i < n; i++)
    {
        int u = Order[i];
        for (int j = head[u]; j != -1; j = edges[j].next)
        {
            int v = edges[j].to;
            early[v] = max(early[v], early[u] + edges[j].weight);//更新earlt time
        }
    }
    //计算总时间
    int time = 0;
    for (int i = 1; i <= n; i++)
    {
        time = max(time, early[i]);
    }
    //late初始化
    for (int i = 1; i <= n; i++) 
    {
        late[i] = time;
    }
    //最晚时间
    for (int i = n - 1; i >= 0; i--)
    {
        int u = Order[i];
        for (int j = head[u]; j != -1; j = edges[j].next)
        {
            int v = edges[j].to;
            late[u] = min(late[u], late[v] - edges[j].weight);  //更新late time
        }
    }
    cout << time << endl; // 输出总工期
    for (int u = 1; u <= n; u++) 
    {  
        for (int i = head[u]; i != -1; i = edges[i].next)
        {
            //u所有出边
            int v = edges[i].to;

            if (early[u] + edges[i].weight == early[v] && early[u] + edges[i].weight == late[v])
            {
                cout << u << "->" << v << endl;
            }
        }
    }
}


int main()
{
    cin >> n >> m;
    init();
    for (int i = 0; i < m; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;
        addEdge(u, v, t);
    }

    if (!topoSort())
    {
        cout << 0 << endl;
        return 0;
    }

    sumPath();
    return 0;
}