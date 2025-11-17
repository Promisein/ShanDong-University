#include <iostream>
#include <vector>
using namespace std;
struct edge
{
    long w;  //边的权重
    long to; //边的终点
    edge()
    {
        w = 0;
        to = 0;
    }
    edge(int w1, int v1)
    {
        w = w1, to = v1;
    }
    bool operator<(const edge &a) const
    {
        return w < a.w;
    }
    bool operator<=(const edge &a) const
    {
        return w <= a.w;
    }
    bool operator>(const edge &a) const
    {
        return w > a.w;
    }
};

//接下来是最小堆的实现

template <class T>
void changeLength1D(T *&a, int oldLength, int newLength)
{
    T *temp = new T[newLength];
    int number = min(oldLength, newLength);
    copy(a, a + number, temp);
    delete[] a;
    a = temp;
}
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
    void initialize(T *, int);
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
    heap[1].~T();

    T lastElement = heap[heapSize--];
    int currentNode = 1,
        child = 2;
    while (child <= heapSize)
    {
        if (child < heapSize && heap[child] > heap[child + 1])
            child++;
        if (lastElement <= heap[child])
            break;

        heap[currentNode] = heap[child];
        currentNode = child;
        child *= 2;
    }
    heap[currentNode] = lastElement;
}
#define max 200005
class min_spanningTree
{
public:
    min_spanningTree(int new_n, int new_e); //构造函数
    void Prim();                            //最小生成树算法函数
    void output();                          //输出函数
private:
    vector<edge> edges[max]; //可用链表数组代替 ，建立200005个vector的容器
    bool *if_join;           //用来判断是否该点已经加入
    int n, e;                //顶点和边数
};

min_spanningTree::min_spanningTree(int new_n, int new_e)
{
    n = new_n;
    e = new_e;
    if_join = new bool[n + 1];
    for (int i = 0; i <= n; ++i)
    {
        if_join[i] = true; //用来判断是否该点已经加入
    }
}
void min_spanningTree::output()
{
    for (int i = 1; i <= n; i++)
    {
        cout << i << "->";
        for (vector<edge>::iterator iter = edges[i].begin(); iter != edges[i].end(); iter++)
        {
            cout << iter->to << " ";
        }
        cout << endl;
    }
}
void min_spanningTree::Prim()
{
    //初始化图
    for (int i = 1; i <= e; ++i)
    {

        long long v1, v2, w;
        cin >> v1 >> v2 >> w;
        edge e1, e2;
        e1.w = w, e2.w = w;
        e1.to = v2, e2.to = v1;

        //邻接数组来表示图
        edges[v1].push_back(e1);
        edges[v2].push_back(e2);
    }

    long long sum = 0; //最小生成树的权重之和

    //默认从顶点为1的开始算法
    long long s = edges[1].size(); //获取第一个数组的长度
    minHeap<edge> heap;
    if_join[1] = false;
    for (int i = 0; i < s; i++) //初始化相邻点
    {
        long long v = edges[1][i].to, w = edges[1][i].w;
        edge temp(w, v);
        heap.push(temp);
    }

    for (int i = 1; i <= n - 1; i++) //遍历所有的顶点
    {
        long long minweight, toVertex;
        while (if_join[heap.top().to] == false) //最小堆中会加入多余的边，判断是否该点是否已经加入
        {
            heap.pop(); //将最小堆中的最小路径，如果已经遍历则删除
        }

        minweight = heap.top().w; //获取最小权重值
        toVertex = heap.top().to; //获取最小权重的顶点
        heap.pop();

        sum += minweight;           //更新最小权重和的结果
        if_join[toVertex] = false;  //更新该边为已经加入的边
        s = edges[toVertex].size(); //获取下一步的顶点所链接的边数（顶点数）

        for (int j = 0; j < s; ++j) //遍历新加入的边的邻接点
        {
            
            long v = edges[toVertex][j].to;
            long long w = edges[toVertex][j].w;

            //把下一个顶点的边插入到最小堆中
            edge temp(w, v);
            heap.push(temp);
        }
    }
    cout << sum << endl;
}
int main()
{
    int n, e; //输入顶点数目和边的数目
    cin >> n >> e;
    min_spanningTree T(n, e);
    T.Prim();
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