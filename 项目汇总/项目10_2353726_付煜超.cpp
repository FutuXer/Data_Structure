#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;
#define DefaultSize 100000

template<class T>
struct Element
{
    T key;
    char otherdata;
    Element<T>& operator=(Element<T>& x)
    {
        key = x.key;
        otherdata = x.otherdata;
        return *this;
    }
    bool operator == (Element<T>& x)
    {
        return key == x.key;
    }
    bool operator <= (Element<T>& x)
    {
        return key <= x.key;
    }
    bool operator > (Element<T>& x)
    {
        return key > x.key;
    }
    bool operator < (Element<T>& x)
    {
        return key < x.key;
    }
};
template<class T>
struct dataList
{
    Element<T> *Vector;
    int maxSize;
    int currentSize;
    dataList(int sz = DefaultSize)
    {
        Vector = new Element<T>[sz];
        maxSize = sz;
        currentSize = 0;
    }
    //获取目前的长度
    int Length()
    {
        return currentSize;
    }
    //增加结点
    void addElement(T value) 
    {
        if (currentSize < maxSize)
        {
            Vector[currentSize++].key = value;
        }
    }
    //比较并交换结点
    void Swap(int x, int y)
    {
        Element<T>temp = Vector[x];
        Vector[x] = Vector[y];
        Vector[y] = temp;
    }
    //复制
    void copyFrom(const dataList<T>& other)
    {
        currentSize = other.currentSize;
        for (int i = 0; i < currentSize; i++)
        {
            Vector[i] = other.Vector[i];
        }
    }
};

//打印菜单
void printScreen()
{
    cout << "**          排序算法比较              **" << endl;
    cout << "========================================" << endl;
    cout << "**         1 --- 冒泡排序             **" << endl;
    cout << "**         2 --- 选择排序             **" << endl;
    cout << "**         3 --- 直接插入排序         **" << endl;
    cout << "**         4 --- 希尔排序             **" << endl;
    cout << "**         5 --- 快速排序             **" << endl;
    cout << "**         6 --- 堆排序               **" << endl;
    cout << "**         7 --- 归并排序             **" << endl;
    cout << "**         8 --- 基数排序             **" << endl;
    cout << "**         9 --- 退出程序             **" << endl;
    cout << "========================================" << endl;
    cout << endl;
}

//生成随机数并存储到 dataList 中
void getRandomNumbers(dataList<int>& numbers, int count) 
{
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < count; ++i)
    {
        numbers.addElement(rand() % 100000); 
    }
}

// 1.冒泡排序法
template <class T>
void BubbleSort(dataList<T> L)
{
    dataList<T> copy;
    copy.copyFrom(L);
    int n = copy.currentSize;
    int swapCount = 0;
    clock_t start = clock();
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (copy.Vector[j] > copy.Vector[j + 1]) 
            {
                copy.Swap(j, j + 1);
                swapCount++;
            }
        }
    }
    clock_t end = clock();
    cout << "冒泡排序所用时间:          " << end - start << endl;
    cout << "冒泡排序交换次数:          " << swapCount << endl;
}

// 2.选择排序法
template <class T>
void SelectionSort(dataList<T> L)
{
    dataList<T> copy;
    copy.copyFrom(L);
    int n = copy.currentSize;
    int swapCount = 0;
    clock_t start = clock();
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++) 
        {
            if (copy.Vector[j] < copy.Vector[min])
            {
                min = j;
            }
        }
        if (min != i) 
        {
            copy.Swap(i, min);
            swapCount++;
        }
    }
    clock_t end = clock();
    cout << "选择排序所用时间:          " << end - start << endl;
    cout << "选择排序交换次数:          " << swapCount << endl;
}

// 3.直接插入排序
template<class T>
void InsertSort(dataList<T>L, int left, int right)
{
    Element<T>temp;
    int i, j;
    int swapCount = 0;
    clock_t start = clock();
    for (i = left + 1; i <= right; i++)
    {
        if (L.Vector[i] < L.Vector[i - 1]) 
        {
            temp = L.Vector[i];
            j = i - 1;

            // 将 temp 插入到正确的位置
            while (j >= left && temp < L.Vector[j])
            {
                L.Vector[j + 1] = L.Vector[j]; // 元素后移
                j--;
            }
            L.Vector[j + 1] = temp; // 插入元素到正确位置
            swapCount++;
        }
    }
    clock_t end = clock();
    cout << "直接插入排序所用时间:      " << end - start << endl;
    cout << "直接插入排序交换次数:      " << swapCount << endl;
}

// 4.希尔排序
template<class T>
void ShellSort(dataList<T>L, int left, int right)
{
    dataList<T>copy = L;
    int i, j, gap = right - left + 1;
    int swapCount = 0;
    clock_t start = clock();
    Element<T>temp;
    do
    {
        gap = gap / 3 + 1;
        for (i = left + gap; i <= right; i++)
        {
            temp = copy.Vector[i];
            j = i - gap;
            do
            {
                copy.Vector[j + gap] = copy.Vector[j];
                swapCount++;   // 计入一次交换
                j = j - gap;
            } while (j >= left && temp < copy.Vector[j]);
        }
    } while (gap > 1);
    clock_t end = clock();
    cout << "希尔插入排序所用时间:      " << end - start << endl;
    cout << "希尔插入排序交换次数:      " << swapCount << endl;
}

// 5.快速排序
template<class T>
int Partition(dataList<T>L, int low, int high, int& swapCount)
{
    int pivotpos = low;
    Element<T>pivot = L.Vector[low];
    for (int i = low + 1; i <= high; i++)
    {
        if (L.Vector[i] < pivot)
        {
            pivotpos++; 
            if (pivotpos != i)
            {
                L.Swap(pivotpos, i);
                swapCount++;
            }
        }
    }
    L.Vector[low] = L.Vector[pivotpos];
    L.Vector[pivotpos] = pivot;

    return pivotpos;
}
template<class T>
void QuickSort(dataList<T>L, int left, int right, int& swapCount)
{
    dataList<T>copy = L;
    if (left < right)
    {
        int pivotpos = Partition(copy, left, right, swapCount);
        QuickSort(copy, left, pivotpos - 1, swapCount);
        QuickSort(copy, pivotpos + 1, right, swapCount);
    }
}
template<class T>
void QuicksortPrint(dataList<T>L, int left, int right)
{
    clock_t start = clock();
    int swapCount = 0;
    QuickSort(L, 0, L.currentSize, swapCount);
    clock_t end = clock();
    cout << "快速排序所用时间:          " << end - start << endl;
    cout << "快速排序交换次数:          " << swapCount << endl;
}

// 6.堆排序
template<class T>
void Heapify(dataList<T> L, int n, int i, int& swapCount)
{
    int largest = i;            //初始化最大元素为根节点
    int left = 2 * i + 1;       //左子
    int right = 2 * i + 2;      //右子

    //如果左子比根节点大
    if (left < n && L.Vector[left] > L.Vector[largest])
        largest = left;

    //如果右子比最大元素大
    if (right < n && L.Vector[right] > L.Vector[largest])
        largest = right;

    //最大不是根节点，交换
    if (largest != i)
    {
        L.Swap(i, largest);
        swapCount++;
        Heapify(L, n, largest, swapCount);  //调整子堆
    }
}
template<class T>
void HeapSort(dataList<T>copyL)
{
    int swapCount = 0;
    clock_t start = clock();
    //构建最大堆
    for (int i = copyL.currentSize / 2 - 1; i >= 0; i--)
        Heapify(copyL, copyL.currentSize, i, swapCount);

    for (int i = copyL.currentSize - 1; i > 0; i--)
    {
        //将当前根节点堆末尾元素交换
        copyL.Swap(0, i);
        swapCount++;

        //调整剩余
        Heapify(copyL, i, 0, swapCount);
    }

    clock_t end = clock();
    cout << "堆排序所用时间:            " << end - start << endl;
    cout << "堆排序交换次数:            " << swapCount << endl;
}

// 7.归并排序
template<class T>
void merge(dataList<T>L1, dataList<T>L2, int left, int mid, int right, int& swapCount)
{
    for (int i = left; i <= right; i++)
    {
        L2.Vector[i] = L1.Vector[i];
    }
    int s1 = left, s2 = mid + 1, t = left;//s1 s2是检测指针，t是存放指针
    while (s1 <= mid && s2 <= right)
    {
        swapCount++;
        if (L2.Vector[s1] <= L2.Vector[s2])
        {
            L2.Vector[t++] = L1.Vector[s1++];
        }
        else
        {
            L2.Vector[t++] = L1.Vector[s2++];
        }
    }
    while (s1<=mid)
    {
        L1.Vector[t++] = L2.Vector[s1++];
    }
    while (s2 <= mid)
    {
        L1.Vector[t++] = L2.Vector[s2++];
    }
}
template<class T>
void mergeSort(dataList<T> L, dataList<T> L2, int left, int right, int& swapCount)
{
    if (left >= right)
    {
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(L, L2, left, mid, swapCount);
    mergeSort(L, L2, mid + 1, right, swapCount);
    merge(L, L2, left, mid, right, swapCount);
    
}

// 8.基数排序
template<class T>
void RadixSort(dataList<T>& L)
{
    int min = L.Vector[0].key;
    int max = L.Vector[0].key;

    for (int i = 1; i < L.currentSize; i++)
    {
        if (L.Vector[i].key > max)
            max = L.Vector[i].key;
        if (L.Vector[i].key < min)
            min = L.Vector[i].key;
    }

    int offset = (min < 0) ? -min : 0;
    for (int i = 0; i < L.currentSize; i++)
        L.Vector[i].key += offset;

    int exp = 1;  //权重
    int* output = new int[L.currentSize];
    int* count = new int[10];

    while (maxVal / exp > 0)
    {
        //初始化
        for (int i = 0; i < 10; i++)
            count[i] = 0;

        //统计当前位数字出现的次数
        for (int i = 0; i < L.currentSize; i++)
        {
            int digit = (L.Vector[i].key / exp) % 10;
            count[digit]++;
        }

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        //排序
        for (int i = L.currentSize - 1; i >= 0; i--)
        {
            int digit = (L.Vector[i].key / exp) % 10;
            output[--count[digit]] = L.Vector[i].key;
        }

        //复制回原数组
        for (int i = 0; i < L.currentSize; i++)
            L.Vector[i].key = output[i];

        exp *= 10;  //下一位
    }

    for (int i = 0; i < L.currentSize; i++)
        L.Vector[i].key -= offset;

    delete[] output;
    delete[] count;
}

int main()
{
    printScreen();
    srand(static_cast<unsigned int>(time(0)));  
    int number;
    cout << "请输入要产生的随机数的个数: ";
    cin >> number;
    cout << endl;

    dataList<int> numbers(number);
    numbers.currentSize = number;
    for (int i = 0; i < number; ++i)
    {
        numbers.Vector[i].key = rand() % 100000; //生成0到99999之间的随机数
    }

    int key = 0;
    while (1)
    {
        cout << "请选择排序算法:            ";
        cin >> key;
        if (cin.fail())
        {
            cout << "输入无效，请重新选择排序算法。" << endl;
            cin.clear();                      
            cin.ignore(1024, '\n'); 
            continue;
        }
        if (key == 1)
        {
            dataList<int> bubbleNumbers = numbers;
            BubbleSort(bubbleNumbers);
            cout << endl;
        }
        else if (key == 2)
        {
            dataList<int> selectionNumbers = numbers;
            SelectionSort(selectionNumbers);
            cout << endl;
        }
        else if (key == 3)
        {
            dataList<int> copyL = numbers;
            InsertSort(copyL, 0, copyL.currentSize - 1);
            cout << endl;
        }
        else if (key == 4)
        {
            dataList<int> copyL = numbers;
            ShellSort(copyL, 0, copyL.currentSize - 1);
            cout << endl;
        }
        else if (key == 5)
        {
            dataList<int> copyL = numbers;
            QuicksortPrint(copyL, 0, copyL.currentSize - 1);
            cout << endl;
        }
        else if (key == 6)
        {
            dataList<int> copyL = numbers;
            HeapSort(copyL);
            cout << endl;
        }
        else if (key == 7)
        {
            clock_t start = clock();
            int swapCount = 0;

            dataList<int> copyL = numbers;
            dataList<int> L2(number);
            L2.currentSize = number;
            mergeSort(copyL, L2, 0, copyL.currentSize - 1, swapCount);
            clock_t end = clock();
            cout << "归并排序所用时间:          " << end - start << endl;
            cout << "归并排序比较次数:          " << swapCount << endl;
            cout << endl;
        }
        else if (key == 8)
        {
            dataList<int> radixNumbers = numbers;
            clock_t start = clock();
            RadixSort(radixNumbers);
            clock_t end = clock();
            cout << "基数排序所用时间:          " << end - start << endl;
            cout << endl;
        }
        else if (key == 9)
        {
            return 0;
        }
        else
        {
            cout << "无效的输入，请重新选择排序算法。" << endl;
            cin.clear();                      
            cin.ignore(1024, '\n');
            continue;
        }
    }
    return 0;
}
