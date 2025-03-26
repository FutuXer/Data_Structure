#include<iostream>

using namespace std;

struct Links
{
    Links* next;
    int number;
    Links(int number) :number(number), next(NULL) {}
};

class numlist
{
private:
    Links* head;
public:
    numlist() :head(NULL) {}
    Links* getHead() { return head; }

    // ������ֵ�����
    void addnum(int num);

    // �������
    void printList() const;

    // ��ȡ����Ĵ�С
    int size() const;
};

void numlist::addnum(int num)
{
    Links* newnum = new Links(num);
    if (head == NULL)
    {
        head = newnum;
    }
    else
    {
        Links* current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newnum;
    }
}

// ��������Ԫ��
void numlist::printList() const
{
    Links* current = head;
    while (current != NULL)
    {
        cout << current->number << " ";
        current = current->next;
    }
    cout << endl;
}

// ��ȡ����Ĵ�С
int numlist::size() const
{
    int count = 0;
    Links* current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

// ����������������ͬ��Ԫ�أ�������һ���µ�������
void search_num(numlist& list1, numlist& list2, numlist& result)
{
    Links* ptr1 = list1.getHead();
    Links* ptr2 = list2.getHead();

    // ���� list1 �е�ÿ��Ԫ��
    while (ptr1 != NULL)
    {
        ptr2 = list2.getHead();  // ÿ�����±��� list2
        // ���� list2 �е�ÿ��Ԫ��
        while (ptr2 != NULL)
        {
            if (ptr1->number == ptr2->number)
            {
                result.addnum(ptr2->number);  // ����ͬԪ����ӵ��������
                break;  // �ҵ�һ��ƥ��ģ������ڲ�ѭ��
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}

int main()
{
    numlist list1, list2, result;
    int num;

    cout << "�������һ�����ݣ���-1��Ϊ������" << endl;
    while (true)
    {
        cin >> num;
        if (num == -1)
        {
            break;
        }
        list1.addnum(num);
    }

    cout << "������ڶ������ݣ���-1��Ϊ������" << endl;
    while (true)
    {
        cin >> num;
        if (num == -1)
        {
            break;
        }
        list2.addnum(num);
    }

    search_num(list1, list2, result);  // ���ҽ��������浽���������

    cout << endl << "����Ľ���ǣ�" << endl;
    if (result.size() == 0)
    {
        cout << "NULL" << endl;
    }
    else
    {
        result.printList();  // ����������
    }

    return 0;
}
