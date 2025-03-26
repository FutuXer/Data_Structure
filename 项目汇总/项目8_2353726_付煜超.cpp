#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class CharString {
private:
    char* str;         // �ַ�����
    size_t length;     // �ַ����ĳ���

public:
    // Ĭ�Ϲ��캯��
    CharString() : str(nullptr), length(0) {}

    // �������Ĺ��캯��
    CharString(const char* input) : str(nullptr), length(0)
    {
        setString(input);
    }

    // �������캯��
    CharString(const CharString& other) : str(nullptr), length(other.length) {
        if (other.str) {
            str = new char[length + 1]; // �����ڴ�
            std::strcpy(str, other.str); // ʹ�� strcpy �����ַ���
        }
    }

    // ��ֵ���������
    CharString& operator=(const CharString& other) {
        if (this != &other) { // ��ֹ���Ҹ�ֵ
            delete[] str; // �ͷŵ�ǰ�ڴ�
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

    // ��������
    ~CharString() {
        delete[] str; // �ͷŶ�̬������ڴ�
    }

    // �����ַ���
    void setString(const char* input) {
        if (input) { // �ȼ�� input �Ƿ�Ϊ nullptr
            delete[] str; // �ͷ�֮ǰ���ڴ�
            length = strlen(input); // ʹ�� strlen ���������ַ����ĳ���
            str = new char[length + 1]; // �����ڴ�
            strcpy(str, input); // �����ַ�
        }
        else {
            str = nullptr;
            length = 0; // ����Ϊ 0
        }
    }

    // ��ȡ�ַ���
    const char* getString() const {
        return str;
    }

    // ����ַ���
    void print() const {
        if (str != nullptr) {
            cout << str << endl; // ����ַ���
        }
        else {
            cout << "Empty string" << endl; // ������ַ��������
        }
    }

    // ��ȡ�ַ�������
    size_t getLength() const {
        return length;
    }

    // ���� == �����
    bool operator==(const CharString& other) const {
        if (length != other.length) {
            return false; // ���Ȳ���ȣ��ַ���һ�������
        }
        return strcmp(str, other.str) == 0; // ʹ�� strcmp �Ƚ��ַ���
    }

    // ��Ԫ���������� << �����
    friend ostream& operator<<(ostream& os, const CharString& charString) {
        if (charString.str != nullptr) {
            os << charString.str; // ����ַ���
        }
        else {
            os << "Empty string"; // ������ַ��������
        }
        return os;
    }

    // ��Ԫ���������� >> �����
    friend istream& operator>>(istream& is, CharString& charString) {
        char buffer[256]; // ��������������ʱ�洢�����ַ���
        is >> buffer; // ����������ȡ�ַ���
        charString.setString(buffer); // ���� CharString ������ַ���
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

//���鼯��������ʵ��
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

//�������ģ��ϵͳ
class MinSpanTree
{
private:
    CharString* vertices; //������������
    Edge* edges;          //��
    Edge* mstEdges;       //��С�������ı�
    int vertexCount;      //��������
    int edgeCount;        //������
    int mstCost;          //��С�������ܳɱ�

public:
    //�������������
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
        cout << "�����붥��ĸ�����";
        cin >> vertexCount;
        cout << "�������������������ƣ�" << endl;
        for (int i = 0; i < vertexCount; i++)
        {
            char name[50];
            cin >> name;
            vertices[i] = CharString(name);
        }
    }

    void addEdge() 
    {
        cout << "���������������ƺͱߵ�Ȩ�أ�����Ȩ��Ϊ0��������\n";
        while (true)
        {
            char u[50], v[50];
            int weight;
            cout << "�������������㼰�ߣ�";
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
                cout << "��Ч�Ķ������ƣ�" << endl;
            }
        }
    }

    void constructMST()
    {
        UnionFind uf(vertexCount);

        //��Ȩ�������
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
            cout << "��С�������ѹ�����ɣ�" << endl;
        }
        else
        {
            cout << "ͼ���ܲ���ͨ������ʧ�ܣ�" << endl;
        }
    }

    void displayMST()
    {
        cout << "��С�������ı����£�" << endl;
        for (int i = 0; i < vertexCount - 1; i++)
        {
            cout << vertices[mstEdges[i].u] << "-<" << mstEdges[i].weight << ">->" << vertices[mstEdges[i].v] << endl;
        }
        cout << "�����: " << mstCost << endl;
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
    cout << "**          �������ģ��ϵͳ          **" << endl;
    cout << "========================================" << endl;
    cout << "**         A --- ������������         **" << endl;
    cout << "**         B --- ��ӵ����ı�         **" << endl;
    cout << "**         C --- ������С������       **" << endl;
    cout << "**         D --- ��ʾ��С������       **" << endl;
    cout << "**         E --- �˳�����             **" << endl;
    cout << "========================================" << endl;
}

int main()
{
    MinSpanTree MST(100, 1000); 
    char choice;

    printMenu();
    while (true) 
    {
        cout << "��ѡ�����: ";
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
            cout << "�˳�����" << endl;
            break;
        }
        else
        {
            cout << "��Ч���룬������ѡ��" << endl;
        }
    }

    return 0;
}