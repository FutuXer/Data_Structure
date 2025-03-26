#include <iostream>
#include <cctype>
#include <cstdio>
#include <cstdlib>

using namespace std;

// 定义优先级
int priority(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    if (ch == '*' || ch == '/')
        return 2;
    return 0;
}

// 检查运算符
bool isOper(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// 自定义栈类
class MYSTACK
{
private:
    char data[100]; // 用于存储栈的数组
    int topIndex;   // 栈顶索引

public:
    MYSTACK() : topIndex(-1) {} // 构造函数初始化栈顶

    bool empty() const { return topIndex == -1; } // 检查栈是否为空

    void push(char ch)
    {
        if (topIndex < 99)
        {
            data[++topIndex] = ch;
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

    char top() const
    {
        if (!empty())
        {
            return data[topIndex];
        }
        else
        {
            cerr << "Stack is empty" << endl;
            return '\0';
        }
    }

    // 栈大小
    int size() const {
        return topIndex + 1;
    }
};

// 主转换函数
void Transform()
{
    MYSTACK Stack;
    char ch; // 当前字符
    char output[100]; //输出后缀表达式的数组
    int index = 0;

    while (true)
    {
        ch = getchar(); // 读取输入字符

        if (ch == '\n' || ch == EOF)
        {
            break;
        }

        if (isspace(ch))
        {
            continue; // 忽略空格
        }

        // 处理数字和字母（操作数）
        if (isalnum(ch))
        {
            output[index++] = ch;
            output[index++] = ' '; // 空格分隔符
            continue;
        }

        if (ch == '(')
        {
            Stack.push(ch); //左括号入栈
        }
        else if (ch == ')')
        {
            //右括号
            while (!Stack.empty() && Stack.top() != '(')
            {
                output[index++] = Stack.top();
                output[index++] = ' ';
                Stack.pop();
            }
            Stack.pop(); //左括号
        }
        else if (isOper(ch))
        {
            while (!Stack.empty() && priority(Stack.top()) >= priority(ch))
            {
                output[index++] = Stack.top();
                output[index++] = ' ';
                Stack.pop();
            }
            Stack.push(ch); //入栈
        }
    }

    //输出剩余运算符
    while (!Stack.empty())
    {
        output[index++] = Stack.top();
        output[index++] = ' ';
        Stack.pop();
    }

    // 输出结果
    if (index > 0)
    {
        output[index - 1] = '\0'; //去掉末尾空格
    }
    cout << output << endl;
}

int main()
{
    Transform();
    return 0;
}


