#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<iomanip>
#include<cstring>


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

struct Student
{
    Student* next;
	//ָ����һ����Ա��ָ��
	int number;
	CharString name;
	CharString gender;
	int age;
	CharString job;
	//������Ϣ

	Student(int number,CharString name,CharString gender,int age,CharString job):number(number),name(name),gender(gender),age(age),job(job),next(nullptr){}
	//���캯��
};

class StudentList
{
private:
	Student* head;
public:
	StudentList():head(NULL){}
	//���캯��

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
		Student* current = head->next;  // ����head��һ���ڱ��ڵ㣬������ʵ��ѧ������
		Student* previous = head;       // ��ʼpreviousΪͷ���

		// �����������Ҫɾ����ѧ��
		while (current != nullptr && current->number != number)
		{
			previous = current;  // ����previousΪ��ǰ�ڵ�
			current = current->next;  // ��������
		}

		// ���û���ҵ�ѧ��
		if (current == nullptr)
		{
			cout << "������Ϣδ�ҵ�!" << endl;
			return;
		}

		// ɾ���ڵ�
		previous->next = current->next;  // ������ǰ�ڵ�
		cout << "��Ҫɾ����������Ϣ��" << current->number << "     " << current->name << "     " << current->gender << "     " << current->age << "     " << current->job << endl;
		delete current;  // �ͷ��ڴ�
	}

	void queryStudent(int number)
	{
		Student* current = head;

		while (current != nullptr) 
		{
			if (current->number == number) 
			{
				cout << "����     " << "����     " << "�Ա�     " << "����     " << "�������      " << endl;
				cout << setw(4) << std::left << current->number << "     ";
				cout << setw(9) << std::left << current->name;
				cout << setw(4) << std::left << current->gender << "     ";
				cout << setw(4) << std::left << current->age << "     ";
				cout << setw(8) << std::left << current->job << endl;
				return;
			}
			current = current->next;
		}

		cout << "������Ϣδ�ҵ�!" << endl;
	}

	void printAllStudents() 
	{
		Student* current = head;
		current = current->next;

		cout << "����     " << "����     " << "�Ա�     " << "����     " << "�������      " << endl;
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
				cout << "�޸ĺ�������Ϣ�ǣ�" << current->number << "     " << current->name << "     " << current->gender << "     " << current->age << "     " << current->job << endl;
				return;
			}
			current = current->next;
		}

		cout << "������Ϣδ�ҵ�!" << endl;
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

	cout << "�����뽨��������Ϣϵͳ" << endl;
	cout << "�����뿼��������";
	cin >> rank;
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	while (times < rank)
	{
		cin >> number >> name >> gender >> age >> job;
		list.addStudent(number, name, gender, age, job);
		times++;
	}
	times = 0;
	//¼�������Ϣ

	list.printAllStudents();
	//��ӡ��Ϣ�б�

	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������" << endl;
	cout << endl;

	int act = 0;
	int insert_loc = 0;

	while (1)
	{
		cout << "��ѡ����Ҫ���еĲ�����";
		cin >> act;
		if (act == 0)
		{
			break;
		}
		switch (act)
		{
		case 1:
			cout << "��ѡ����Ҫ���뿼����λ�ã�";
			cin >> insert_loc;
			cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
			cin >> number >> name >> gender >> age >> job;
			list.insertStudent(number, name, gender, age, job, insert_loc);
			cout << endl;
			list.printAllStudents();
			break;
		case 2:
			cout << "��ѡ����Ҫɾ�������Ŀ��ţ�";
			cin >> insert_loc;
			list.deleteStudent(insert_loc);
			cout << endl;
			list.printAllStudents();
			break;
		case 3:
			cout << "��ѡ����Ҫ��ѯ�����Ŀ��ţ�";
			cin >> insert_loc;
			list.queryStudent(insert_loc);
			cout << endl;
			break;
		case 4:
			cout << "��ѡ����Ҫ�޸Ŀ����Ŀ��ţ�";
			cin >> insert_loc;
			cout << "��ѡ����Ҫ�޸Ŀ�������Ϣ��";
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
