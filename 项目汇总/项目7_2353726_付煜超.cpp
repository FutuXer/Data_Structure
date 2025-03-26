#include <iostream>
using namespace std;

class Node
{
public:
    int value;
    Node* next;
    Node(int value) : value(value), next(nullptr) {}
};

class LinkedList 
{
public:
    Node* head;
    LinkedList() : head(nullptr) {}

    // 插入元素
    void insert(int value)
    {
        Node* newNode = new Node(value);
        if (!head || head->value >= value) 
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            Node* temp = head;
            while (temp->next && temp->next->value < value)
            {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // 弹出最小元素
    int pop()
    {
        if (!head) return -1;
        Node* temp = head;
        head = head->next;
        int val = temp->value;
        delete temp;
        return val;
    }

    // 获取链表大小
    bool empty()
    {
        return head == nullptr;
    }

    // 获取最小值
    int top() 
    {
        if (head) 
        {
            return head->value;
        }
        return -1; 

    }
};

int minCost(LinkedList& woodList)
{
    int sum = 0;
    while (!woodList.empty())
    {
        int a = woodList.pop();  // 弹出最小的木材
        if (woodList.empty()) break;  

        int b = woodList.pop();  // 弹出第二小的木材
        int cost = a + b;
        sum += cost;

        woodList.insert(cost);
    }
    return sum;  
}

int main()
{
    int len;
    int input;
    LinkedList woodList;

    cin >> len;

    for (int i = 0; i < len; i++) 
    {
        cin >> input;
        woodList.insert(input);  // 将每个木材长度插入链表
    }

    cout << minCost(woodList) << endl;
}

