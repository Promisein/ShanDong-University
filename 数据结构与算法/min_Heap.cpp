#include <iostream>
using namespace std;
template <class T>
class minHeap
{
public:
    minHeap(int theSize = 5);                //构造函数
    //~minHeap() { delete[] Heap; }        //析构函数
    //真的很神奇，一delete就出错！真的离谱！！！
    void initialHeap(T* theHeap, int n); //初始化函数
    void push(T& theElement);            //插入函数
    void pop();                          //删除函数
    void sort(T a[], int n);             //排序函数
    void output();                       //输出函数
    void outroot(); //输出根节点元素
    void changeLengthld(T*& a, int oldLength, int newlength) 
    {
        T* temp = new T[newlength];
        int number = min(oldLength, newlength);
        copy(a, a + number, temp);
        delete[]a;
        a = temp;
    }
    void sorted_initialHeap(T* theHeap, int n);
    void sorted_pop();
    void sorted_push(T& theElement);
private:
    T* Heap;         //堆数组
    int heapSize;    //堆的大小
    int arrayLength; //数组大小
};
template <class T>
minHeap<T>::minHeap(int theSize)
{
    heapSize = 0;
    arrayLength = theSize + 1;
    //Heap = new T[heapSize];
    Heap = new T[arrayLength];
}
template <class T>
void minHeap<T>::initialHeap(T* theHeap, int n)
{ //在数组theheap中建立小根堆
    delete[] Heap;
    Heap = theHeap;
    /*
    T* temp = new T[n + 1];
    copy(theHeap, theHeap + n + 1, temp);
    Heap = temp;
    */
    heapSize = n;
    //进行堆化
    for (int root = heapSize / 2; root >= 1; root--)
        //从最后一个有孩子的结点开始进行堆化
    {
        T rootElement = Heap[root];
        //为rootElement寻找合适的位置
        int child = root * 2;
        while (child <= heapSize)
        {
            //寻找较小的兄弟结点
            //if(Heap[child] > Heap[child + 1] && child < heapSize)
            if ( child < heapSize && Heap[child] > Heap[child + 1] )
            {
                child++;
            }
            if (rootElement <= Heap[child])
            {
                break;
            }
            else
            {
                Heap[child / 2] = Heap[child]; //将孩子结点与父亲结点进行交换
                child *= 2;
            }
        }
        Heap[child / 2] = rootElement;
    }
    //cout << Heap[1] << endl;
     //output();
}
template <class T>
void minHeap<T>::push(T& theElement)
{
    /*
    if (heapSize == arrayLength - 1)
    {
        T* temp = new T[arrayLength * 2];
        for (int i = 1; i <= arrayLength; i++)
        {
            temp[i] = Heap[i];
        }
        arrayLength *= 2;
        delete Heap;
        Heap = temp;
    }
    */
    if (heapSize == arrayLength - 1)
    {
        changeLengthld(Heap, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    int currentNode = ++heapSize;                                  // currentNOde为新叶子结点的位置
    while (currentNode != 1 && Heap[currentNode / 2] > theElement) //循环到其父亲结点小于theElement
    {
        Heap[currentNode] = Heap[currentNode / 2];
        currentNode /= 2;
        //从底部开始向上冒泡
    }
    Heap[currentNode] = theElement;
    //cout << Heap[1] << endl;
    //output();
}
template <class T>
void minHeap<T>::pop()
{
    if (heapSize == 0)
    {
        return;
    }
    Heap[1].~T(); //删除最小元素
    T lastElement = Heap[heapSize--];
    //从根开始，为最后一个结点寻找元素位置
    int currentNode = 1, child = 2;
    while (child <= heapSize)
    {
        if (child < heapSize && Heap[child] > Heap[child + 1])
        {
            child++;
        } //返回孩子结点较小的元素
        if (lastElement <= Heap[child])
        {
            break;
        }
        else
        {
            Heap[currentNode] = Heap[child];
            currentNode = child;
            child *= 2;
        }
    }
    Heap[currentNode] = lastElement;
    // cout << Heap[1] << endl;
}
template <class T>
void minHeap<T>::sort(T a[], int n)
{
    //initialHeap(a, n);
    for (int i = n; i >= 1; i--)
    {
        cout << Heap[1] << " ";
        pop();
    }
    cout << endl;
}
template <class T>
void minHeap<T>::output()
{
    for (int i = 1; i <= heapSize; i++)
    {
        cout << Heap[i] << " ";
    }
    cout << endl;
}
template <class T>
void minHeap<T>::outroot()
{
    cout << Heap[1] << endl;
}
int main()
{
    // cout << " minHeap is constructing!" << endl;
    /*
    int n;
    cin >> n;
    int *p = new int [n + 1];
    for(int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }
    for(int i = 1; i <= n; i++)
    {
        cout << p[i] << " ";
    }
    cout << endl;
    minHeap<int> h(n);
    h.initialHeap(p, n);
    minHeap<int> h1(5);
    for(int i = 1; i <= n; i++)
    {
        h1.push(p[i]);
    }
    */
    int n, m;
    cin >> n;
    int nn = n + 1;
    int* element = new int[n + 1];
    element[0] = 0;
    minHeap<int> h(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> element[i];
        h.push(element[i]);
    }
    //h.initialHeap(element, n); //初始化最小堆
    h.outroot();
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int chioce;
        cin >> chioce;
        if (chioce == 1)
        {
            int pushed_element;
            cin >> pushed_element;
            h.push(pushed_element);
            h.outroot();
        }
        if (chioce == 2)
        {
            h.pop();
            h.outroot();
        }
        if (chioce == 3)
        {
            int new_n;
            cin >> new_n;
            int* sort_elements = new int[new_n + 1];
            sort_elements[0] = 0;
            minHeap<int> h1(new_n);
            for (int i = 1; i <= new_n; i++)
            {
                cin >> sort_elements[i];
                h1.push(sort_elements[i]);
            }
           //h.sort(sort_elements, new_n);
            h1.sort(sort_elements, new_n);
            //delete[]sort_elements;
        }
    }
    //在initial中已经重复析构了
    //delete[] element;
    return 0;
}
/*
10
20 12 35 15 10 80 30 17 2 1
*/