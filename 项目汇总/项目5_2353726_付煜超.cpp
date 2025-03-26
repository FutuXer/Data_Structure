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

	// ��������
	void input(T data)
	{
		Node<T>* tmp = new Node<T>(data, nullptr);
		if (first == nullptr)
		{
			first = tmp;
			last = tmp;
			last->next = first;  // �γ�ѭ������
		}
		else 
		{
			last->next = tmp;
			last = tmp;
			last->next = first;  // �γ�ѭ������
		}
	}

	// ɾ�������������еĵ�һ��Ԫ��zysb
	T pop() 
	{
		if (first == nullptr)
		{
			return T();  // ����Ĭ��ֵ
		}

		Node<T>* temp = first;
		T value = first->value;
		if (first == last)
		{
			first = last = nullptr;  // ����ֻʣһ��Ԫ�أ�ɾ�����ÿ�
		}
		else
		{
			first = first->next;
			last->next = first;  // ����ѭ������
		}
		delete temp;
		return value;
	}
};

int main() 
{
	cout << "����һ�������������е�һ����N��N<=1000��Ϊ�˿��������������Nλ�˿͵ı�š�" << endl;

	int n, code;
	Link<int> Alist, Blist;

	cin >> n;  // �˿�����

	for (int i = 0; i < n; i++) 
	{
		cin >> code;
		if (code % 2 == 1) 
		{
			Alist.input(code);  // ��������Alist
		}
		else {
			Blist.input(code);  // ż������Blist
		}
	}

	// �������
	while (!Alist.empty() || !Blist.empty())
	{
		if (!Alist.empty()) {
			cout << Alist.pop() << " ";  // ���������Alist�еĵ�һ��Ԫ��
		}
		if (!Blist.empty()) {
			cout << Blist.pop() << " ";  // ���������Blist�еĵ�һ��Ԫ��
		}
	}

	return 0;
}
