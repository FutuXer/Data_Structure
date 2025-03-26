#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class CharString {
private:
    char* str;         // 字符数组
    size_t length;     // 字符串的长度

public:
    // 默认构造函数
    CharString() : str(nullptr), length(0) {}

    // 带参数的构造函数
    CharString(const char* input) : str(nullptr), length(0)
    {
        setString(input);
    }

    // 拷贝构造函数
    CharString(const CharString& other) : str(nullptr), length(other.length) {
        if (other.str) {
            str = new char[length + 1]; // 分配内存
            std::strcpy(str, other.str); // 使用 strcpy 复制字符串
        }
    }

    // 赋值运算符重载
    CharString& operator=(const CharString& other) {
        if (this != &other) { // 防止自我赋值
            delete[] str; // 释放当前内存
            length = other.length;
            if (other.str) {
                str = new char[length + 1];
                strcpy(str, other.str);
            }
            else {
                str = nullptr;
            }
        }
        return *this;
    }

    // 析构函数
    ~CharString() {
        delete[] str; // 释放动态分配的内存
    }

    // 设置字符串
    void setString(const char* input) {
        if (input) { // 先检查 input 是否为 nullptr
            delete[] str; // 释放之前的内存
            length = strlen(input); // 使用 strlen 计算输入字符串的长度
            str = new char[length + 1]; // 分配内存
            strcpy(str, input); // 复制字符
        }
        else {
            str = nullptr;
            length = 0; // 设置为 0
        }
    }

    // 获取字符串
    const char* getString() const {
        return str;
    }

    // 输出字符串
    void print() const {
        if (str != nullptr) {
            cout << str << endl; // 输出字符串
        }
        else {
            cout << "Empty string" << endl; // 处理空字符串的情况
        }
    }

    // 获取字符串长度
    size_t getLength() const {
        return length;
    }

    // 重载 == 运算符
    bool operator==(const CharString& other) const {
        if (length != other.length) {
            return false; // 长度不相等，字符串一定不相等
        }
        return strcmp(str, other.str) == 0; // 使用 strcmp 比较字符串
    }

    // 友元函数：重载 << 运算符
    friend ostream& operator<<(ostream& os, const CharString& charString) {
        if (charString.str != nullptr) {
            os << charString.str; // 输出字符串
        }
        else {
            os << "Empty string"; // 处理空字符串的情况
        }
        return os;
    }

    // 友元函数：重载 >> 运算符
    friend istream& operator>>(istream& is, CharString& charString) {
        char buffer[256]; // 缓冲区，用于临时存储输入字符串
        is >> buffer; // 从输入流读取字符串
        charString.setString(buffer); // 设置 CharString 对象的字符串
        return is;
    }
};

struct Edge
{
    int u, v;      
    int weight;    
};

template<class T>
class Node 
{
public:
    T data;
    Node* next;

    Node(T data) : data(data), next(nullptr) {}
};

//并查集类用数组实现
class UnionFind 
{
private:
    int* parent;
    int* rank;
    int size;

public:
    UnionFind(int n) : size(n) 
    {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    ~UnionFind()
    {
        delete[] parent;
        delete[] rank;
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return false;

        if (rank[rootX] > rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else 
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

//电网造价模拟系统
class MinSpanTree
{
private:
    CharString* vertices; //顶点名称数组
    Edge* edges;          //边
    Edge* mstEdges;       //最小生成树的边
    int vertexCount;      //顶点数量
    int edgeCount;        //边数量
    int mstCost;          //最小生成树总成本

public:
    //构造和析构函数
    MinSpanTree(int maxVertices, int maxEdges)
    {
        vertices = new CharString[maxVertices];
        edges = new Edge[maxEdges];
        mstEdges = new Edge[maxVertices - 1];
        vertexCount = 0;
        edgeCount = 0;
        mstCost = 0;
    }
    ~MinSpanTree() 
    {
        delete[] vertices;
        delete[] edges;
        delete[] mstEdges;
    }

    void createVertices() 
    {
        cout << "请输入顶点的个数：";
        cin >> vertexCount;
        cout << "请依次输入各顶点的名称：" << endl;
        for (int i = 0; i < vertexCount; i++)
        {
            char name[50];
            cin >> name;
            vertices[i] = CharString(name);
        }
    }

    void addEdge() 
    {
        cout << "请输入两顶点名称和边的权重（输入权重为0结束）：\n";
        while (true)
        {
            char u[50], v[50];
            int weight;
            cout << "请输入两个顶点及边：";
            cin >> u >> v >> weight;
            if (weight == 0) break;

            int uIndex = findVertex(u);
            int vIndex = findVertex(v);
            if (uIndex != -1 && vIndex != -1)
            {
                edges[edgeCount++] = { uIndex, vIndex, weight };
            }
            else
            {
                cout << "无效的顶点名称！" << endl;
            }
        }
    }

    void constructMST()
    {
        UnionFind uf(vertexCount);

        //按权重排序边
        sortEdges();

        mstCost = 0;
        int mstEdgeCount = 0;

        for (int i = 0; i < edgeCount && mstEdgeCount < vertexCount - 1; i++)
        {
            if (uf.unionSets(edges[i].u, edges[i].v)) 
            {
                mstEdges[mstEdgeCount++] = edges[i];
                mstCost += edges[i].weight;
            }
        }

        if (mstEdgeCount == vertexCount - 1)
        {
            cout << "最小生成树已构造完成！" << endl;
        }
        else
        {
            cout << "图可能不连通，构造失败！" << endl;
        }
    }

    void displayMST()
    {
        cout << "最小生成树的边如下：" << endl;
        for (int i = 0; i < vertexCount - 1; i++)
        {
            cout << vertices[mstEdges[i].u] << "-<" << mstEdges[i].weight << ">->" << vertices[mstEdges[i].v] << endl;
        }
        cout << "总造价: " << mstCost << endl;
    }

private:
    int findVertex(const char* name) 
    {
        for (int i = 0; i < vertexCount; i++) 
        {
            if (vertices[i] == CharString(name)) 
            {
                return i;
            }
        }
        return -1;
    }

    void sortEdges() 
    {
        for (int i = 0; i < edgeCount - 1; i++) 
        {
            for (int j = 0; j < edgeCount - i - 1; j++) 
            {
                if (edges[j].weight > edges[j + 1].weight) 
                {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
    }
};

void printMenu() 
{
    cout << "**          电网造价模拟系统          **" << endl;
    cout << "========================================" << endl;
    cout << "**         A --- 创建电网顶点         **" << endl;
    cout << "**         B --- 添加电网的边         **" << endl;
    cout << "**         C --- 构造最小生成树       **" << endl;
    cout << "**         D --- 显示最小生成树       **" << endl;
    cout << "**         E --- 退出程序             **" << endl;
    cout << "========================================" << endl;
}

int main()
{
    MinSpanTree MST(100, 1000); 
    char choice;

    printMenu();
    while (true) 
    {
        cout << "请选择操作: ";
        cin >> choice;

        if (choice == 'A')
        {
            MST.createVertices();
            cout << endl;
        }
        else if (choice == 'B')
        {
            MST.addEdge();
            cout << endl;
        }
        else if (choice == 'C')
        {
            MST.constructMST();
            cout << endl;
        }
        else if (choice == 'D')
        {
            MST.displayMST();
            cout << endl;
        }
        else if (choice == 'E')
        {
            cout << "退出程序" << endl;
            break;
        }
        else
        {
            cout << "无效输入，请重新选择！" << endl;
        }
    }

    return 0;
}