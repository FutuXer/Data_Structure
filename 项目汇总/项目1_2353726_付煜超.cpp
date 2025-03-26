#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<iomanip>
#include<cstring>


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

struct Student
{
    Student* next;
	//指向下一个成员的指针
	int number;
	CharString name;
	CharString gender;
	int age;
	CharString job;
	//基本信息

	Student(int number,CharString name,CharString gender,int age,CharString job):number(number),name(name),gender(gender),age(age),job(job),next(nullptr){}
	//构造函数
};

class StudentList
{
private:
	Student* head;
public:
	StudentList():head(NULL){}
	//构造函数

	void addStudent(int number, CharString name, CharString gender, int age, CharString job)
	{
		Student* newStudent = new Student(number, name, gender, age, job);

		if (head == NULL) 
		{			
			head = newStudent;
		}
		else 
		{
			
			Student* current = head;
			while (current->next != NULL) 
			{
				current = current->next;
			}
			
			current->next = newStudent;
		}
	}

	void deleteStudent(int number)
	{
		Student* current = head->next;  // 假设head是一个哨兵节点，不包含实际学生数据
		Student* previous = head;       // 初始previous为头结点

		// 遍历链表查找要删除的学生
		while (current != nullptr && current->number != number)
		{
			previous = current;  // 更新previous为当前节点
			current = current->next;  // 继续遍历
		}

		// 如果没有找到学生
		if (current == nullptr)
		{
			cout << "考生信息未找到!" << endl;
			return;
		}

		// 删除节点
		previous->next = current->next;  // 跳过当前节点
		cout << "你要删除考生的信息是" << current->number << "     " << current->name << "     " << current->gender << "     " << current->age << "     " << current->job << endl;
		delete current;  // 释放内存
	}

	void queryStudent(int number)
	{
		Student* current = head;

		while (current != nullptr) 
		{
			if (current->number == number) 
			{
				cout << "考号     " << "姓名     " << "性别     " << "年龄     " << "报考类别      " << endl;
				cout << setw(4) << std::left << current->number << "     ";
				cout << setw(9) << std::left << current->name;
				cout << setw(4) << std::left << current->gender << "     ";
				cout << setw(4) << std::left << current->age << "     ";
				cout << setw(8) << std::left << current->job << endl;
				return;
			}
			current = current->next;
		}

		cout << "考生信息未找到!" << endl;
	}

	void printAllStudents() 
	{
		Student* current = head;
		current = current->next;

		cout << "考号     " << "姓名     " << "性别     " << "年龄     " << "报考类别      " << endl;
		while (current != NULL) 
		{
			cout << setw(4) << std::left << current->number << "     ";
			cout << setw(9) << std::left << current->name;
			cout << setw(4) << std::left << current->gender << "     ";
			cout << setw(4) << std::left << current->age << "     ";
			cout << setw(8) << std::left << current->job << endl;
			current = current->next;
		}
	}

	void modifyStudent(int number, CharString name, CharString gender, int age, CharString job)
	{
		Student* current = head;

		while (current != nullptr)
		{
			if (current->number == number)
			{
				current->name = name;
				current->gender = gender;
				current->age = age;
				current->job = job;
				cout << "修改后考生的信息是：" << current->number << "     " << current->name << "     " << current->gender << "     " << current->age << "     " << current->job << endl;
				return;
			}
			current = current->next;
		}

		cout << "考生信息未找到!" << endl;
	}

	void insertStudent(int number, CharString name, CharString gender, int age, CharString job, int expect)
	{
		Student* newStudent = new Student(number, name, gender, age, job);
	
		if (expect == 0)
		{
			newStudent->next = head;
			head = newStudent;
			return;
		}

		Student* current = head;
		int i;
		for (i = 0; i < expect - 1; i++)
		{
			if (current == NULL)
			{
				
				delete newStudent; 
				return;
			}
			current = current->next;
		}

		if (current != NULL) 
		{
			newStudent->next = current->next;
			current->next = newStudent;
		}
		else 
		{
			
			delete newStudent;
		}
	
	}

	~StudentList()
	{
		Student* current = head;
		while (current != nullptr)
		{
			Student* next = current->next;
			delete current;
			current = next;
		}
	}
};

int main()
{
	StudentList list;
	int rank;
	int times = 0;
	int number, age;
	CharString name, gender, job;
	CharString first("padishah");
	list.addStudent(-1, first, first, -1, first);

	cout << "首先请建立考生信息系统" << endl;
	cout << "请输入考生人数：";
	cin >> rank;
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	while (times < rank)
	{
		cin >> number >> name >> gender >> age >> job;
		list.addStudent(number, name, gender, age, job);
		times++;
	}
	times = 0;
	//录入基本信息

	list.printAllStudents();
	//打印信息列表

	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作" << endl;
	cout << endl;

	int act = 0;
	int insert_loc = 0;

	while (1)
	{
		cout << "请选择您要进行的操作：";
		cin >> act;
		if (act == 0)
		{
			break;
		}
		switch (act)
		{
		case 1:
			cout << "请选择你要插入考生的位置：";
			cin >> insert_loc;
			cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
			cin >> number >> name >> gender >> age >> job;
			list.insertStudent(number, name, gender, age, job, insert_loc);
			cout << endl;
			list.printAllStudents();
			break;
		case 2:
			cout << "请选择你要删除考生的考号：";
			cin >> insert_loc;
			list.deleteStudent(insert_loc);
			cout << endl;
			list.printAllStudents();
			break;
		case 3:
			cout << "请选择你要查询考生的考号：";
			cin >> insert_loc;
			list.queryStudent(insert_loc);
			cout << endl;
			break;
		case 4:
			cout << "请选择你要修改考生的考号：";
			cin >> insert_loc;
			cout << "请选择你要修改考生的信息：";
			cin >> insert_loc >> name >> gender >> age >> job;
			list.modifyStudent(insert_loc, name, gender, age, job);
			cout << endl;
			break;
		case 5:
			list.printAllStudents();
			break;
		default:
			break;
		}
	}

	return 0;
}
