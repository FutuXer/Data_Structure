#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
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

template<class T>
class MYSTACK
{
private:
	T data[100];   // 存储栈的数组
	int topIndex;  // 栈顶索引

public:
	MYSTACK() : topIndex(-1) {} // 构造函数初始化栈顶

	bool empty() const { return topIndex == -1; } // 检查栈是否为空

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
			return T();  // 返回默认值
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
	FamilyMember<T>* find(T name, FamilyMember<T>* p);                         //查找name
	FamilyMember<T>* findParent(FamilyMember<T>* child, FamilyMember<T>* p);   //查找child的父节点
	void creatFamily(T name);                                                  //创建二叉树
	void addFamily(T name);                                                    //功能A的完善name的家谱
	void deleteChild(FamilyMember<T>* p);                                      //删除p结点对应的所有孩子
	void changeName(T name);                                                   //功能D的修改姓名                                   
	void printChild(FamilyMember<T>* p);                                       //展示p结点对应的所有孩子
	void addMember(T name);                                                    //功能B的添加成员
	void releaseFamily(T name);                                                //功能C的解散局部家庭

};

CharString getdata()
{
	CharString myString; 

	char input[100]; 
	cin.getline(input, 100); 

	myString.setString(input); 
	return myString; //返回对象
}

//创建一个仙人
template<class T>
void FamilyTree<T>::creatFamily(T name)
{
	root = new FamilyMember<T>;
	root->name = name;
}

template<class T>
FamilyMember<T>* FamilyTree<T>::find(T name, FamilyMember<T>* p)
{
	if (p == nullptr)  //如果树为空，直接返回 nullptr
		return nullptr;

	MYSTACK<FamilyMember<T>*> nodeStack; 
	nodeStack.push(p);  //将根节点压入栈中

	while (!nodeStack.empty())  
	{
		FamilyMember<T>* current = nodeStack.top(); 
		nodeStack.pop();  

		//如果当前节点的名字与传入的名字相同，返回当前节点
		if (current->name == name)
		{
			return current;
		}

		//先将右子节点压入栈中，再将左子节点压入栈中
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
//寻找某一个家庭成员

template<class T>
FamilyMember<T>* FamilyTree<T>::findParent(FamilyMember<T>* child, FamilyMember<T>* p)
{
	if (p == nullptr || child == nullptr)
	{
		return nullptr;
	}

	FamilyMember<T>* sibling = p->lChild;  
	FamilyMember<T>* result = nullptr;     

	//遍历兄弟链，递归在子树中搜索
	while (sibling != nullptr && sibling != child)
	{
		result = findParent(child, sibling);
		if (result != nullptr) 
		{
			return result;  //找到父节点
		}
		sibling = sibling->rChild;  //访问右兄弟
	}

	//如果找到子节点，则返回父节点
	if (sibling != nullptr && sibling == child)
	{
		return p;  
	}
	else
	{
		return nullptr;  
	}
}

//添加家谱，注意要与添加新成员区分开
template<class T>
void FamilyTree<T>::addFamily(T name)
{
	int num;
	T C_name;
	FamilyMember<T>* p = FamilyTree<T>::find(name, root);
	FamilyMember<T>* q = p;
	if (p == nullptr)
	{
		cout << "该人不存在！" << endl;
		return;
	}
	else
	{
		cout << "请输入";
		cout << name;
		cout << "的儿女人数：";
		cin >> num;
		cout << "请依次输入";
		cout << name;
		cout << "的儿女的姓名：";
		for (int i = 0; i < num; i++)
		{
			if (i == 0)
			{
				FamilyMember<T>* lchild = new FamilyMember<T>;
				p->lChild = lchild;
				cin >> C_name;
				lchild->name = C_name;
				q = lchild;
			}//第一个左孩子
			else
			{
				FamilyMember<T>* rchild = new FamilyMember<T>;
				cin >> C_name;
				rchild->name = C_name;
				q->rChild = rchild;
				q = rchild;
			}//剩下全是右兄弟
		}
		cout << name;
		cout << "的第一代子孙是:";
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
    //下来的目标是找到name的儿子，然后一直向右找到兄弟的末端
	if (p == nullptr)
	{
		cout << "没有这个人捏" << endl << endl;
		return;
	}
	cout << "请输入";
	cout << name;
	cout << "新添加的儿子（或女儿）的姓名:";
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
	cout << "的第一代子孙是:";
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
		cout << "没有这个人捏" << endl << endl;
		return;
	}
	if (p == root)
	{
		cout << "不能删除祖宗" << endl << endl;
		return;
	}
	cout << "要解散家庭的人是：";
	cout << name;
	cout << endl;
	cout << name << "的第一代子孙是: ";
	printChild(p);

	FamilyMember<T>* parent = findParent(p, root);
	if (parent->lChild = p)//是长子
	{
		parent->lChild = p->rChild;
	}
	else  //不是长子
	{
		FamilyMember<T>* sibling = parent->lChild;
		while (sibling->rChild != p)
		{
			sibling = sibling->rChild;
		}
		sibling->rChild = p->rChild;	
	}
	deleteChild(p);  //删除孩子节点
	delete p; 
	cout << endl;
}

template<class T>
void FamilyTree<T>::deleteChild(FamilyMember<T>* p)
{
	while (p->lChild)
	{ 
		FamilyMember<T>* temp = p->lChild; 
		p->lChild = temp->rChild; //指向左孩子的右孩子
		delete temp;
	}
}

template<class T>
void FamilyTree<T>::changeName(T name)
{
	T newname, tmp;
	FamilyMember<T>* p = find(name, root);
	tmp = name;
	cout << "请输入更改后的姓名：";
	cin >> newname;
	p->name = newname;
	cout << tmp;
	cout << "已更名为";
	cout << newname;
	cout << endl;
	cout << endl;
}

template<class T>
void FamilyTree<T>::printChild(FamilyMember<T>* p)
{
	FamilyMember<T>* current = p;
	if (p->lChild != nullptr)//左孩子非空
	{
		current = p->lChild;
		cout << current->name;
		cout << " ";
		while (current->rChild != nullptr)//右边始终是兄弟，非空继续打印
		{
			current = current->rChild;
			cout << current->name;
			cout << " ";
		}
	}
	else
	{
		cout << "没孩子";
	}
	cout << endl;
}

void printMenu()
{
	cout << "**             家谱管理系统             **" << endl;
	cout << "==========================================" << endl;
	cout << "**          A --- 完善家谱              **" << endl;
	cout << "**          B --- 添加家庭成员          **" << endl;
	cout << "**          C --- 解散局部家庭          **" << endl;
	cout << "**          D --- 更改家庭成员姓名      **" << endl;
	cout << "**          E --- 退出程序              **" << endl;
	cout << "==========================================" << endl;
	cout << "首先建立一个家谱！" << endl;
}

int main()
{
	printMenu();
	FamilyTree<CharString>FamilyMap;
	cout << "请输入祖先的名字:";
	CharString ancestor;
	cin >> ancestor;
	cout << "此家谱的祖先是:";
	cout << ancestor;
	cout << endl << endl;
	FamilyMap.creatFamily(ancestor);

	char key;
	while (1)
	{
		cout << "请选择要执行的操作:";
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
				cout << "请输入要建立家庭的人的姓名:";
				CharString name1;
				cin >> name1;
				FamilyMap.addFamily(name1);
				break;
			}
			case 'B':
			{
				cout << "请输入要添加儿子（或女儿）的人的姓名:";
				CharString name2;
				cin >> name2;
				FamilyMap.addMember(name2);
				break;
			}
			case 'C':
			{
				cout << "请输入要删除家庭的人的姓名:";
				CharString name3;
				cin >> name3;
				FamilyMap.releaseFamily(name3);
				break;
			}
			case 'D':
			{
				cout << "请输入要更改姓名的人的目前姓名:";
				CharString name4;
				cin >> name4;
				FamilyMap.changeName(name4);         //功能D改变姓名
				break;
			}
			default:
			{
				cout << "输入错误，请重新输入" << endl;
				break;
			}
			}
		}
	}
	return 0;
}