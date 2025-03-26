#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
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

template<class T>
class MYSTACK
{
private:
	T data[100];   // �洢ջ������
	int topIndex;  // ջ������

public:
	MYSTACK() : topIndex(-1) {} // ���캯����ʼ��ջ��

	bool empty() const { return topIndex == -1; } // ���ջ�Ƿ�Ϊ��

	void push(const T& item)
	{
		if (topIndex < 99)
		{
			data[++topIndex] = item;
		}
		else {
			cerr << "Stack overflow" << endl;
		}
	}

	void pop()
	{
		if (!empty())
		{
			--topIndex;
		}
		else {
			cerr << "Stack underflow" << endl;
		}
	}

	T top() const
	{
		if (!empty())
		{
			return data[topIndex];
		}
		else
		{
			cerr << "Stack is empty" << endl;
			return T();  // ����Ĭ��ֵ
		}
	}

	int size() const {
		return topIndex + 1;
	}
};

template<class T>
struct FamilyMember
{
	T name;
	FamilyMember* lChild;
	FamilyMember* rChild;
	FamilyMember(FamilyMember* lChild = nullptr, FamilyMember* rChild = nullptr) :lChild(lChild), rChild(rChild) {}
};

template<class T>
class FamilyTree
{
private:
	FamilyMember<T>* root;
public:
	FamilyTree() { root = nullptr; }
	FamilyMember<T>* find(T name, FamilyMember<T>* p);                         //����name
	FamilyMember<T>* findParent(FamilyMember<T>* child, FamilyMember<T>* p);   //����child�ĸ��ڵ�
	void creatFamily(T name);                                                  //����������
	void addFamily(T name);                                                    //����A������name�ļ���
	void deleteChild(FamilyMember<T>* p);                                      //ɾ��p����Ӧ�����к���
	void changeName(T name);                                                   //����D���޸�����                                   
	void printChild(FamilyMember<T>* p);                                       //չʾp����Ӧ�����к���
	void addMember(T name);                                                    //����B����ӳ�Ա
	void releaseFamily(T name);                                                //����C�Ľ�ɢ�ֲ���ͥ

};

CharString getdata()
{
	CharString myString; 

	char input[100]; 
	cin.getline(input, 100); 

	myString.setString(input); 
	return myString; //���ض���
}

//����һ������
template<class T>
void FamilyTree<T>::creatFamily(T name)
{
	root = new FamilyMember<T>;
	root->name = name;
}

template<class T>
FamilyMember<T>* FamilyTree<T>::find(T name, FamilyMember<T>* p)
{
	if (p == nullptr)  //�����Ϊ�գ�ֱ�ӷ��� nullptr
		return nullptr;

	MYSTACK<FamilyMember<T>*> nodeStack; 
	nodeStack.push(p);  //�����ڵ�ѹ��ջ��

	while (!nodeStack.empty())  
	{
		FamilyMember<T>* current = nodeStack.top(); 
		nodeStack.pop();  

		//�����ǰ�ڵ�������봫���������ͬ�����ص�ǰ�ڵ�
		if (current->name == name)
		{
			return current;
		}

		//�Ƚ����ӽڵ�ѹ��ջ�У��ٽ����ӽڵ�ѹ��ջ��
		if (current->rChild != nullptr)
		{
			nodeStack.push(current->rChild);
		}
		if (current->lChild != nullptr)
		{
			nodeStack.push(current->lChild);
		}
	}

	return nullptr;
}
//Ѱ��ĳһ����ͥ��Ա

template<class T>
FamilyMember<T>* FamilyTree<T>::findParent(FamilyMember<T>* child, FamilyMember<T>* p)
{
	if (p == nullptr || child == nullptr)
	{
		return nullptr;
	}

	FamilyMember<T>* sibling = p->lChild;  
	FamilyMember<T>* result = nullptr;     

	//�����ֵ������ݹ�������������
	while (sibling != nullptr && sibling != child)
	{
		result = findParent(child, sibling);
		if (result != nullptr) 
		{
			return result;  //�ҵ����ڵ�
		}
		sibling = sibling->rChild;  //�������ֵ�
	}

	//����ҵ��ӽڵ㣬�򷵻ظ��ڵ�
	if (sibling != nullptr && sibling == child)
	{
		return p;  
	}
	else
	{
		return nullptr;  
	}
}

//��Ӽ��ף�ע��Ҫ������³�Ա���ֿ�
template<class T>
void FamilyTree<T>::addFamily(T name)
{
	int num;
	T C_name;
	FamilyMember<T>* p = FamilyTree<T>::find(name, root);
	FamilyMember<T>* q = p;
	if (p == nullptr)
	{
		cout << "���˲����ڣ�" << endl;
		return;
	}
	else
	{
		cout << "������";
		cout << name;
		cout << "�Ķ�Ů������";
		cin >> num;
		cout << "����������";
		cout << name;
		cout << "�Ķ�Ů��������";
		for (int i = 0; i < num; i++)
		{
			if (i == 0)
			{
				FamilyMember<T>* lchild = new FamilyMember<T>;
				p->lChild = lchild;
				cin >> C_name;
				lchild->name = C_name;
				q = lchild;
			}//��һ������
			else
			{
				FamilyMember<T>* rchild = new FamilyMember<T>;
				cin >> C_name;
				rchild->name = C_name;
				q->rChild = rchild;
				q = rchild;
			}//ʣ��ȫ�����ֵ�
		}
		cout << name;
		cout << "�ĵ�һ��������:";
		printChild(p);
		cout << endl;
	}
}

template<class T>
void FamilyTree<T>::addMember(T name)
{
	T newBaby;
	FamilyMember<T>* p = find(name, root);
	FamilyMember<T>* current = p;
    //������Ŀ�����ҵ�name�Ķ��ӣ�Ȼ��һֱ�����ҵ��ֵܵ�ĩ��
	if (p == nullptr)
	{
		cout << "û���������" << endl << endl;
		return;
	}
	cout << "������";
	cout << name;
	cout << "����ӵĶ��ӣ���Ů����������:";
	cin >> newBaby;
	if (current->lChild == nullptr)
	{
		FamilyMember<T>* q = new FamilyMember<T>;
		q->name = newBaby;
		current->lChild = q;
	}
	else
	{
		current = current->lChild;
		while (current->rChild != nullptr)
		{
			current = current->rChild;		
		}
		FamilyMember<T>* q = new FamilyMember<T>;
		q->name = newBaby;
		current->rChild = q;
	}
	cout << name;
	cout << "�ĵ�һ��������:";
	printChild(p);
	cout << endl;
}

template<class T>
void FamilyTree<T>::releaseFamily(T name)
{
	FamilyMember<T>* p = find(name, root);
	FamilyMember<T>* current = p;
	if (p == nullptr)
	{
		cout << "û���������" << endl << endl;
		return;
	}
	if (p == root)
	{
		cout << "����ɾ������" << endl << endl;
		return;
	}
	cout << "Ҫ��ɢ��ͥ�����ǣ�";
	cout << name;
	cout << endl;
	cout << name << "�ĵ�һ��������: ";
	printChild(p);

	FamilyMember<T>* parent = findParent(p, root);
	if (parent->lChild = p)//�ǳ���
	{
		parent->lChild = p->rChild;
	}
	else  //���ǳ���
	{
		FamilyMember<T>* sibling = parent->lChild;
		while (sibling->rChild != p)
		{
			sibling = sibling->rChild;
		}
		sibling->rChild = p->rChild;	
	}
	deleteChild(p);  //ɾ�����ӽڵ�
	delete p; 
	cout << endl;
}

template<class T>
void FamilyTree<T>::deleteChild(FamilyMember<T>* p)
{
	while (p->lChild)
	{ 
		FamilyMember<T>* temp = p->lChild; 
		p->lChild = temp->rChild; //ָ�����ӵ��Һ���
		delete temp;
	}
}

template<class T>
void FamilyTree<T>::changeName(T name)
{
	T newname, tmp;
	FamilyMember<T>* p = find(name, root);
	tmp = name;
	cout << "��������ĺ��������";
	cin >> newname;
	p->name = newname;
	cout << tmp;
	cout << "�Ѹ���Ϊ";
	cout << newname;
	cout << endl;
	cout << endl;
}

template<class T>
void FamilyTree<T>::printChild(FamilyMember<T>* p)
{
	FamilyMember<T>* current = p;
	if (p->lChild != nullptr)//���ӷǿ�
	{
		current = p->lChild;
		cout << current->name;
		cout << " ";
		while (current->rChild != nullptr)//�ұ�ʼ�����ֵܣ��ǿռ�����ӡ
		{
			current = current->rChild;
			cout << current->name;
			cout << " ";
		}
	}
	else
	{
		cout << "û����";
	}
	cout << endl;
}

void printMenu()
{
	cout << "**             ���׹���ϵͳ             **" << endl;
	cout << "==========================================" << endl;
	cout << "**          A --- ���Ƽ���              **" << endl;
	cout << "**          B --- ��Ӽ�ͥ��Ա          **" << endl;
	cout << "**          C --- ��ɢ�ֲ���ͥ          **" << endl;
	cout << "**          D --- ���ļ�ͥ��Ա����      **" << endl;
	cout << "**          E --- �˳�����              **" << endl;
	cout << "==========================================" << endl;
	cout << "���Ƚ���һ�����ף�" << endl;
}

int main()
{
	printMenu();
	FamilyTree<CharString>FamilyMap;
	cout << "���������ȵ�����:";
	CharString ancestor;
	cin >> ancestor;
	cout << "�˼��׵�������:";
	cout << ancestor;
	cout << endl << endl;
	FamilyMap.creatFamily(ancestor);

	char key;
	while (1)
	{
		cout << "��ѡ��Ҫִ�еĲ���:";
		cin.clear();
		cin >> key;
		if (key == 'E')
			break;
		else
		{
			switch (key)
			{
			case 'A':
			{
				cout << "������Ҫ������ͥ���˵�����:";
				CharString name1;
				cin >> name1;
				FamilyMap.addFamily(name1);
				break;
			}
			case 'B':
			{
				cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�����:";
				CharString name2;
				cin >> name2;
				FamilyMap.addMember(name2);
				break;
			}
			case 'C':
			{
				cout << "������Ҫɾ����ͥ���˵�����:";
				CharString name3;
				cin >> name3;
				FamilyMap.releaseFamily(name3);
				break;
			}
			case 'D':
			{
				cout << "������Ҫ�����������˵�Ŀǰ����:";
				CharString name4;
				cin >> name4;
				FamilyMap.changeName(name4);         //����D�ı�����
				break;
			}
			default:
			{
				cout << "�����������������" << endl;
				break;
			}
			}
		}
	}
	return 0;
}