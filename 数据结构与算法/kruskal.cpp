#include <iostream>
using namespace std;
template <class T>
class minHeap
{
public:
    minHeap(int initialCapacity = 10);
    ~minHeap() { delete[] heap; }
    bool empty() const { return heapSize == 0; }
    int size() const
    {
        return heapSize;
    }
    const T top()
    {
        return heap[1];
    }
    void pop();
    void push(const T &);
    void initialize(T *theHeap, int n);
    void changeLength1D(T *&arr, int oldLength, int newLength)
    {
        T *temp = new T[newLength];
        int number = min(oldLength, newLength);
        copy(arr, arr + number, temp);
        delete[] arr;
        arr = temp;
    }
    void deactivateArray()
    {
        heap = NULL;
        arrayLength = heapSize = 0;
    }

private:
    int heapSize;
    int arrayLength;
    T *heap;
};
template <class T>
minHeap<T>::minHeap(int initialCapacity)
{
    arrayLength = initialCapacity + 1;
    heap = new T[arrayLength];
    heapSize = 0;
}
template <class T>
void minHeap<T>::initialize(T *theHeap, int theSize)
{
    // 在数组theHeap[1:theSize]中建立小根堆
    delete[] heap;
    heap = theHeap;
    heapSize = theSize;
    // 堆化
    for (int root = heapSize / 2; root >= 1; root--)
    {
        T rootElement = heap[root]; // 从叶节点的根开始
        int child = 2 * root;       // 叶子
        while (child <= heapSize)
        { // 选择较小的孩子
            if (child < heapSize && heap[child] > heap[child + 1])
                child++;
            if (rootElement <= heap[child]) // 根小于孩子则不用换
                break;
            heap[child / 2] = heap[child]; // 根于孩子进行交换
            child *= 2;
        }
        heap[child / 2] = rootElement;
    }
}
template <class T>
void minHeap<T>::push(const T &theElement)
{

    if (heapSize == arrayLength - 1)
    {
        changeLength1D(heap, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] > theElement)
    {
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;
    }

    heap[currentNode] = theElement;
}
template <class T>
void minHeap<T>::pop()
{
    if (heapSize == 0)
    {
        return;
    }
    heap[1].~T(); //删除最小元素
    T lastElement = heap[heapSize--];
    //从根开始，为最后一个结点寻找元素位置
    int currentNode = 1, child = 2;
    while (child <= heapSize)
    {
        if (child < heapSize && heap[child] > heap[child + 1])
        {
            child++;
        } //返回孩子结点较小的元素
        if (lastElement <= heap[child])
        {
            break;
        }
        else
        {
            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }
    }
    heap[currentNode] = lastElement;
}

template <class T>
struct Edge
{
    //结构体成员
    int x = 0;
    int y = 0;
    T weight = 0;

    //构造函数
    Edge() {}
    Edge(int ni, int nj, T nw) : x(ni), y(nj), weight(nw) {}

    //重载大于小于号
    bool operator<(Edge &a)
    {
        return weight < a.weight;
    }
    bool operator<=(Edge &a)
    {
        return weight <= a.weight;
    }
    bool operator>=(Edge &a)
    {
        return weight >= a.weight;
    }
    bool operator>(Edge &a)
    {
        return weight > a.weight;
    }
    Edge &operator=(Edge &a)
    {
        x = a.x;
        y = a.y;
        weight = a.weight;
        return *this;
    }
};

template <class T>
class min_spanningTree
{
public:
    min_spanningTree(int ne, int n); //边数，顶点数
    void Kruskal();
    void quick_sort(int begin, int end); //快速排序
    void heap_sort();                    //堆排序

    //并查集的两个函数
    int find(int x);         //判断是否为环的辅助函数
    void join(int x, int y); //将y的祖父结点指向x的祖父结点

    void output(); //输出函数
private:
    Edge<T> *graph;  //原来的图
    int *pre;        //存储所有结点的父节点
    int n;           //顶点的个数
    int edge_number; //边的个数
};
template <class T>
min_spanningTree<T>::min_spanningTree(int ne, int n)
{
    edge_number = ne;
    graph = new Edge<T>[edge_number + 1];
    pre = new int[n + 1];
    for (int i = 1; i <= n; i++)
    {
        pre[i] = i;
    }
    this->n = n;
}
template <class T>
void min_spanningTree<T>::heap_sort()
{
    minHeap<Edge<T>> heap(1);
    heap.initialize(this->graph, edge_number);
    // output();
}
template <class T>
void min_spanningTree<T>::quick_sort(int begin, int end)
{
    if (begin > end)
        return;
    Edge<T> tmp = graph[begin];
    int i = begin;
    int j = end;
    while (i < j)
    {
        //找到比tmp大的第一个数字的下标
        while (graph[j] >= tmp && j > i)
        {
            j--;
        }
        //找到比tmp小的第一个数字的下标
        while (graph[i] <= tmp && j > i)
        {
            i++;
        }
        if (j > i)
        { // i 与 j的元素交换位置
            Edge<T> mid = graph[i];
            graph[i] = graph[j];
            graph[j] = mid;
        }
    }
    //中间的元素与开头的元素交换位置
    graph[begin] = graph[i];
    graph[i] = tmp;
    quick_sort(begin, i - 1);
    quick_sort(i + 1, end);
}
template <class T>
void min_spanningTree<T>::output()
{
    cout << endl;
    for (int i = 1; i <= edge_number; i++)
    {
        cout << graph[i].x << " " << graph[i].y << " " << graph[i].weight << endl;
    }
}

template <class T>
int min_spanningTree<T>::find(int x)
{
    int root = x;
    while (root != pre[root])
    {
        root = pre[root]; //找到根
    }

    //压缩路径 所有的子节点都指向根
    //这里是吧所有的结点都指向最终的根节点，不用一直父亲结点判断完成后，又一次进行判断
    while (x != root)
    {
        int temp = pre[x];
        pre[x] = root;
        x = temp;
    }
    return root;
}
template <class T>
void min_spanningTree<T>::join(int x, int y)
{

    pre[find(y)] = find(x);
}
template <class T>
void min_spanningTree<T>::Kruskal()
{
    //初始化权重图
    for (int i = 1; i <= edge_number; i++)
    {
        int x, y, weight;
        cin >> x >> y >> weight;
        graph[i].x = x;
        graph[i].y = y;
        graph[i].weight = weight;
    }

    //排序
    quick_sort(1, edge_number);
    // heap_sort();
    //利用并查集判断是否有环判断是否生成环
    /*
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        ifring[i] = i + 1;
    }
    int i = 0;
    while (count < n && i < edge_number - 1)
    {
        int temp1 = ifring[graph[i].x - 1] ;
        int temp2 = ifring[graph[i].y - 1] ;
        if (temp1 != temp2)
        {
            subscript[count++] = i;
            for (int j = 0; j < n; j++)
            {
                if (ifring[j] == temp2)
                {
                    ifring[j] = temp1;
                }
            }

        }
        i++;
    }
    */
    /*
    int sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += graph[subscript[i]].weight;
        //cout << graph[subscript[i]].x << " " << graph[subscript[i]].y << " " << graph[subscript[i]].weight << endl;
    }
    cout << sum << endl;
    */
    int count = 0;                         //记录已连接边的数目
    long long sum = 0;                     //记录权重和（使用int就溢出了）
    for (int i = 1; i <= edge_number; i++) //遍历所有的边
    {
        if (count == n - 1)
        { //当已经链接的边的个数等于顶点数减一时，说明已经成为最小生成树
            break;
        }
        if (find(graph[i].x) != find(graph[i].y))
        {
            join(graph[i].x, graph[i].y);
            sum += graph[i].weight;
            count++;
        }
    }
    cout << sum << endl;
}

int main()
{
    int n, e; //顶点个数和边的个数
    cin >> n >> e;
    min_spanningTree<int> m(e, n);
    m.Kruskal();
    return 0;
}
/*
7 9
6 1 10
1 2 28
2 7 14
2 3 16
6 5 25
7 5 24
7 4 18
3 4 12
5 4 22
*/