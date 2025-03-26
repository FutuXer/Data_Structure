#include <iostream>
#include <iomanip>
using namespace std;

const int HEIGHT = 7;
const int WIDTH = 7;
const int DIRECTIONS = 4;
const char SYMBOLS[3] = { '#', '0', '$' };

struct Direction 
{
    int dx, dy; // dx为x方向偏移，dy为y方向偏移
};

Direction moves[DIRECTIONS] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} }; // 四个方向的移动

// 用于存储路径的数组，最多有HEIGHT * WIDTH个坐标
const int MAX_PATH_LENGTH = HEIGHT * WIDTH;
struct Path {
    int x[MAX_PATH_LENGTH];  // 存储路径的x坐标
    int y[MAX_PATH_LENGTH];  // 存储路径的y坐标
    int length = 0;  // 当前路径的长度
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

// 查找路径的递归函数
int findPath(int maze[][WIDTH], int visited[][WIDTH], int x, int y, int goal_x, int goal_y, Path& route)
{
    if (x == goal_x && y == goal_y)
    {
        route.add(x, y); // 加入终点
        return 1; // 成功到达目标
    }

    for (int i = 0; i < DIRECTIONS; i++)
    {
        int next_x = x + moves[i].dx;
        int next_y = y + moves[i].dy;

        if (next_x >= 0 && next_x < HEIGHT && next_y >= 0 && next_y < WIDTH && maze[next_x][next_y] == 1 && visited[next_x][next_y] == 1)
        {
            visited[next_x][next_y] = 0; // 标记为已探查
            if (findPath(maze, visited, next_x, next_y, goal_x, goal_y, route))
            {
                route.add(x, y); // 加入当前坐标
                return 1; // 找到路径
            }
            visited[next_x][next_y] = 1; // 回溯时恢复状态
        }
    }
    return 0; // 未找到路径
}

// 打印迷宫的函数
void printMaze(int maze[HEIGHT][WIDTH], Path& route)
{
    cout << "   "; // 为行号留出空间
    for (int j = 0; j < WIDTH; j++)
    {
        cout << setw(3) << j; // 列号占3个字符宽度
    }
    cout << endl;

    // 打印迷宫内容
    for (int i = 0; i < HEIGHT; i++)
    {
        cout << setw(3) << i; // 打印行号
        for (int j = 0; j < WIDTH; j++)
        {
            char symbol;
            if (maze[i][j] == 0)
                symbol = SYMBOLS[0]; // 墙壁
            else if (maze[i][j] == 1)
                symbol = SYMBOLS[1]; // 可通行路径
            else
                symbol = SYMBOLS[2]; // 路径

            cout << setw(3) << symbol; // 每个格子占3个字符宽度
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    cout << "迷宫地图:" << endl;
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

    int visited[HEIGHT][WIDTH]; // 访问标记
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            visited[i][j] = (maze[i][j] == 1) ? 1 : 0; // 初始化

    int start_x = 1, start_y = 1, goal_x = 5, goal_y = 5;
    Path route; // 存储路径

    visited[start_x][start_y] = 0; // 标记起点
    if (findPath(maze, visited, start_x, start_y, goal_x, goal_y, route))
    {
        for (int i = 0; i < route.length; ++i)
        {
            maze[route.x[i]][route.y[i]] = 2; // 标记路径
        }
        printMaze(maze, route);

        cout << "迷宫路径: ";
        for (int i = 0; i < route.length; ++i)
        {
            cout << "(" << route.x[i] << "," << route.y[i] << ") ";
        }
    }
    else
    {
        cout << "迷宫没有出路！" << endl;
    }
    return 0;
}





