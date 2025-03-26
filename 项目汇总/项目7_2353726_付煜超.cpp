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

    // ����Ԫ��
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

    // ������СԪ��
    int pop()
    {
        if (!head) return -1;
        Node* temp = head;
        head = head->next;
        int val = temp->value;
        delete temp;
        return val;
    }

    // ��ȡ�����С
    bool empty()
    {
        return head == nullptr;
    }

    // ��ȡ��Сֵ
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
        int a = woodList.pop();  // ������С��ľ��
        if (woodList.empty()) break;  

        int b = woodList.pop();  // �����ڶ�С��ľ��
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
        woodList.insert(input);  // ��ÿ��ľ�ĳ��Ȳ�������
    }

    cout << minCost(woodList) << endl;
}

