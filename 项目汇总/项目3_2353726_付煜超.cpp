#include <iostream>
#include <iomanip>
using namespace std;

const int HEIGHT = 7;
const int WIDTH = 7;
const int DIRECTIONS = 4;
const char SYMBOLS[3] = { '#', '0', '$' };

struct Direction 
{
    int dx, dy; // dxΪx����ƫ�ƣ�dyΪy����ƫ��
};

Direction moves[DIRECTIONS] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} }; // �ĸ�������ƶ�

// ���ڴ洢·�������飬�����HEIGHT * WIDTH������
const int MAX_PATH_LENGTH = HEIGHT * WIDTH;
struct Path {
    int x[MAX_PATH_LENGTH];  // �洢·����x����
    int y[MAX_PATH_LENGTH];  // �洢·����y����
    int length = 0;  // ��ǰ·���ĳ���
    void add(int cx, int cy) 
    {
        if (length < MAX_PATH_LENGTH) 
        {
            x[length] = cx;
            y[length] = cy;
            length++;
        }
    }
};

// ����·���ĵݹ麯��
int findPath(int maze[][WIDTH], int visited[][WIDTH], int x, int y, int goal_x, int goal_y, Path& route)
{
    if (x == goal_x && y == goal_y)
    {
        route.add(x, y); // �����յ�
        return 1; // �ɹ�����Ŀ��
    }

    for (int i = 0; i < DIRECTIONS; i++)
    {
        int next_x = x + moves[i].dx;
        int next_y = y + moves[i].dy;

        if (next_x >= 0 && next_x < HEIGHT && next_y >= 0 && next_y < WIDTH && maze[next_x][next_y] == 1 && visited[next_x][next_y] == 1)
        {
            visited[next_x][next_y] = 0; // ���Ϊ��̽��
            if (findPath(maze, visited, next_x, next_y, goal_x, goal_y, route))
            {
                route.add(x, y); // ���뵱ǰ����
                return 1; // �ҵ�·��
            }
            visited[next_x][next_y] = 1; // ����ʱ�ָ�״̬
        }
    }
    return 0; // δ�ҵ�·��
}

// ��ӡ�Թ��ĺ���
void printMaze(int maze[HEIGHT][WIDTH], Path& route)
{
    cout << "   "; // Ϊ�к������ռ�
    for (int j = 0; j < WIDTH; j++)
    {
        cout << setw(3) << j; // �к�ռ3���ַ����
    }
    cout << endl;

    // ��ӡ�Թ�����
    for (int i = 0; i < HEIGHT; i++)
    {
        cout << setw(3) << i; // ��ӡ�к�
        for (int j = 0; j < WIDTH; j++)
        {
            char symbol;
            if (maze[i][j] == 0)
                symbol = SYMBOLS[0]; // ǽ��
            else if (maze[i][j] == 1)
                symbol = SYMBOLS[1]; // ��ͨ��·��
            else
                symbol = SYMBOLS[2]; // ·��

            cout << setw(3) << symbol; // ÿ������ռ3���ַ����
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    cout << "�Թ���ͼ:" << endl;
    int maze[HEIGHT][WIDTH] =
    {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };

    int visited[HEIGHT][WIDTH]; // ���ʱ��
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            visited[i][j] = (maze[i][j] == 1) ? 1 : 0; // ��ʼ��

    int start_x = 1, start_y = 1, goal_x = 5, goal_y = 5;
    Path route; // �洢·��

    visited[start_x][start_y] = 0; // ������
    if (findPath(maze, visited, start_x, start_y, goal_x, goal_y, route))
    {
        for (int i = 0; i < route.length; ++i)
        {
            maze[route.x[i]][route.y[i]] = 2; // ���·��
        }
        printMaze(maze, route);

        cout << "�Թ�·��: ";
        for (int i = 0; i < route.length; ++i)
        {
            cout << "(" << route.x[i] << "," << route.y[i] << ") ";
        }
    }
    else
    {
        cout << "�Թ�û�г�·��" << endl;
    }
    return 0;
}





