#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 100;
const int MAXM = 1005;

struct Edge 
{
    int from, to, weight, next;  //��㡢�յ㡢Ȩֵ����һ����index
} edges[MAXM];

int head[MAXN], inDegree[MAXN], outDegree[MAXN];   //ͷָ�����顢��ȡ�����
int early[MAXN], late[MAXN], Order[MAXN];          //������ɡ�������ɡ������ڵ�
int n, m, edgeCount;                               //N M ��ǰ��

//��ʼ������
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

//��������
void addEdge(int u, int v, int w)
{
    edges[edgeCount] = { u, v, w, head[u] };  //�����ߵ���㡢�յ㡢Ȩֵ��ָ�����һ����
    head[u] = edgeCount++;                    //���½ڵ� u ��top��ָ�����µı�
    inDegree[v]++;                            //���� v �����
}

//���������ж��Ƿ�������
bool topoSort()
{
    int queue[MAXN], front = 0, prev = 0;
    //���Ϊ 0 �Ľڵ����
    for (int i = 1; i <= n; i++)
    {
        if (inDegree[i] == 0)
        {
            queue[prev++] = i;
        }
    }
    int index = 0;
    //����
    while (front < prev)
    {
        int temp = queue[front++];
        Order[index++] = temp;
        for (int i = head[temp]; i != -1; i = edges[i].next)
        {
            int v = edges[i].to;     
            if (--inDegree[v] == 0)  // ������ȼ�Ϊ 0�������
            {
                queue[prev++] = v;
            }
        }
    }
    return index == n;               //����ʣ��ڵ������
}

//����������
void sumPath()
{
    //����ʱ��
    for (int i = 0; i < n; i++)
    {
        int u = Order[i];
        for (int j = head[u]; j != -1; j = edges[j].next)
        {
            int v = edges[j].to;
            early[v] = max(early[v], early[u] + edges[j].weight);//����earlt time
        }
    }
    //������ʱ��
    int time = 0;
    for (int i = 1; i <= n; i++)
    {
        time = max(time, early[i]);
    }
    //late��ʼ��
    for (int i = 1; i <= n; i++) 
    {
        late[i] = time;
    }
    //����ʱ��
    for (int i = n - 1; i >= 0; i--)
    {
        int u = Order[i];
        for (int j = head[u]; j != -1; j = edges[j].next)
        {
            int v = edges[j].to;
            late[u] = min(late[u], late[v] - edges[j].weight);  //����late time
        }
    }
    cout << time << endl; // ����ܹ���
    for (int u = 1; u <= n; u++) 
    {  
        for (int i = head[u]; i != -1; i = edges[i].next)
        {
            //u���г���
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