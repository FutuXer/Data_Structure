#include<iostream>
using namespace std;

template<class T> class Node 
{
public:
	Node(const T& value, Node<T>* next = nullptr) : value(value), next(next) {}
	Node(Node<T>* next = nullptr) : next(next) {}

	T value;
	Node<T>* next;
};

template<class T> class Link
{
public:
	Link() : first(nullptr), last(nullptr) {}

	Node<T>* first;
	Node<T>* last;

	bool empty()
	{
		return first == nullptr;
	}

	// 插入数据
	void input(T data)
	{
		Node<T>* tmp = new Node<T>(data, nullptr);
		if (first == nullptr)
		{
			first = tmp;
			last = tmp;
			last->next = first;  // 形成循环链表
		}
		else 
		{
			last->next = tmp;
			last = tmp;
			last->next = first;  // 形成循环链表
		}
	}

	// 删除并返回链表中的第一个元素zysb
	T pop() 
	{
		if (first == nullptr)
		{
			return T();  // 返回默认值
		}

		Node<T>* temp = first;
		T value = first->value;
		if (first == last)
		{
			first = last = nullptr;  // 链表只剩一个元素，删除后置空
		}
		else
		{
			first = first->next;
			last->next = first;  // 保持循环链表
		}
		delete temp;
		return value;
	}
};

int main() 
{
	cout << "输入一行正整数，其中第一数字N（N<=1000）为顾客总数，后面跟着N位顾客的编号。" << endl;

	int n, code;
	Link<int> Alist, Blist;

	cin >> n;  // 顾客总数

	for (int i = 0; i < n; i++) 
	{
		cin >> code;
		if (code % 2 == 1) 
		{
			Alist.input(code);  // 奇数加入Alist
		}
		else {
			Blist.input(code);  // 偶数加入Blist
		}
	}

	// 分类输出
	while (!Alist.empty() || !Blist.empty())
	{
		if (!Alist.empty()) {
			cout << Alist.pop() << " ";  // 弹出并输出Alist中的第一个元素
		}
		if (!Blist.empty()) {
			cout << Blist.pop() << " ";  // 弹出并输出Blist中的第一个元素
		}
	}

	return 0;
}
