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

    // 添加数字到链表
    void addnum(int num);

    // 输出链表
    void printList() const;

    // 获取链表的大小
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

// 输出链表的元素
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

// 获取链表的大小
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

// 查找两个链表中相同的元素，保存在一个新的链表中
void search_num(numlist& list1, numlist& list2, numlist& result)
{
    Links* ptr1 = list1.getHead();
    Links* ptr2 = list2.getHead();

    // 遍历 list1 中的每个元素
    while (ptr1 != NULL)
    {
        ptr2 = list2.getHead();  // 每次重新遍历 list2
        // 遍历 list2 中的每个元素
        while (ptr2 != NULL)
        {
            if (ptr1->number == ptr2->number)
            {
                result.addnum(ptr2->number);  // 将相同元素添加到结果链表
                break;  // 找到一个匹配的，跳出内层循环
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

    cout << "请输入第一组数据（以-1作为结束）" << endl;
    while (true)
    {
        cin >> num;
        if (num == -1)
        {
            break;
        }
        list1.addnum(num);
    }

    cout << "请输入第二组数据（以-1作为结束）" << endl;
    while (true)
    {
        cin >> num;
        if (num == -1)
        {
            break;
        }
        list2.addnum(num);
    }

    search_num(list1, list2, result);  // 查找交集并保存到结果链表中

    cout << endl << "输出的结果是：" << endl;
    if (result.size() == 0)
    {
        cout << "NULL" << endl;
    }
    else
    {
        result.printList();  // 输出交集结果
    }

    return 0;
}
