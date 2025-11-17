#include <iostream>
#include <queue>
using namespace std;
template <class T>
struct Edge_Node //定义边结点
{
    T vertex;           //该边的顶点位置
    T weight;           //边的权重
    Edge_Node<T>* next; //指向下一条边的指针
};

//邻接表  adjacency list
template <class T>
struct adj_List
{
    int element;             //存放顶点的第一个信息
    Edge_Node<T>* firstNode; //存放指向顶点 element的第一个顶点
};
template <class T>
class Graph
{
public:
    Graph(int n = 250);                    //构造函数
    ~Graph() {}                            //析构函数
    void insert(int v1, int v2, T weight); //插入函数，插入以v1，v2为顶点的边
    void erase(int v1, int v2);            //删除边
    bool ifRing();                         //判断是否有环
    void Prim();
    void Kruskal();
    void DFS(int i);
    void BFS(int i);
    void clear();
    int* getReach()
    {
        return this->reach;
    }
    int getmin();               //获取最小边结点
    int connected_components(); //寻找连通分量
    void output();              //输出函数
private:
    adj_List<T>* aList; //创建具有100010个结点的图（后期优化看能不能减少空间动态申请）
    int V_number;       //顶点数
    int E_number;       //边数
    int* reach;         // DFS来判断的状态
    bool judge = true;
};
template <class T>
Graph<T>::Graph(int n)
{
    V_number = n;
    E_number = 0;
    aList = new adj_List<T>[V_number];
    for (int i = 0; i < n; i++)
    {
        aList[i].element = i + 1;
        aList[i].firstNode = NULL;
    }
    reach = new int[V_number + 1];
    for (int i = 0; i <= n; i++)
    {
        reach[i] = 0;
    }
}
template <class T>
void Graph<T>::insert(int v1, int v2, T weight)
{
    Edge_Node<T>* edge1 = new Edge_Node<T>;
    edge1->vertex = v2;
    edge1->weight = weight;
    Edge_Node<T>* p = aList[v1 - 1].firstNode;
    Edge_Node<T>* pp = NULL;             // p的上一个边结点
    if (p == NULL || p->weight > weight) //当要插入的表头为空，或者头结点的元素值大于v2 - 1
    {
        edge1->next = aList[v1 - 1].firstNode;
        //如果p=null ，有效的只有执行这一步
        aList[v1 - 1].firstNode = edge1;
    } //从小到大插入边
    else
    {
        while (p != NULL && p->weight < weight) //当前仅当p不为空节点，而且p的边元素小与 v2 - 1，保证顺序
        {
            pp = p;
            p = p->next;
        }
        if (p == NULL) //最后循环到了链表的末尾
        {
            pp->next = edge1;
            edge1->next = NULL;
        }
        else //在中间退出循环
        {
            if (pp)
            {
                pp->next = edge1;
                edge1->next = p;
            }
        }
    }
    E_number++; //边数加一
}
template <class T>
void Graph<T>::erase(int v1, int v2)
{
    Edge_Node<T>* deleteNode = aList[v2 - 1].firstNode; //要删除的结点
    Edge_Node<T>* P_deleteNode = NULL;                  //要删除结点的上一个结点
    while (deleteNode != NULL && deleteNode->vertex != v1)
    { //寻找要删除边的一个结点
        P_deleteNode = deleteNode;
        deleteNode = deleteNode->next;
    }
    if (deleteNode == NULL)
    {
        cout << "删除失败！" << endl;
        return;
    }
    if (P_deleteNode != NULL) //判断删除的结点是否为头结点
    {
        P_deleteNode->next = deleteNode->next;
    }
    else
    {
        aList[v2 - 1].firstNode = deleteNode->next;
    }
    delete deleteNode;
    E_number--;
}
template <class T>
void Graph<T>::Prim()
{
}
template <class T>
void Graph<T>::Kruskal()
{
    int sum = 0;
    Graph<int> G2(V_number); //存储最小生成树
    int last_connected = G2.connected_components();
    int initial_connected = connected_components();
    while (initial_connected != G2.connected_components()) //当两个图的连通分量不相等是继续循环
    {
        int last_connected = G2.connected_components();
        int minEdge_v1 = this->getmin();                          //得到最小的边
        int minEdge_v2 = aList[minEdge_v1 - 1].firstNode->vertex; //获取最小边的结点
        int minweight = aList[minEdge_v1 - 1].firstNode->weight;
        sum += minweight;
        this->erase(minEdge_v1, minEdge_v2);
        this->erase(minEdge_v2, minEdge_v1);
        G2.insert(minEdge_v1, minEdge_v2, minweight);
        G2.insert(minEdge_v2, minEdge_v1, minweight);
        if (last_connected == G2.connected_components())
            //如果链接后的连通分量和连接前一样，那么说明，链接成的树中有环！
        {
            G2.erase(minEdge_v1, minEdge_v2);
            G2.erase(minEdge_v2, minEdge_v1);
            sum -= minweight;
        }
    }
    cout << sum << endl;
}
template <class T>
void Graph<T>::output()
{
    for (int i = 0; i < V_number; i++)
    {
        cout << aList[i].element;
        if (aList[i].firstNode != NULL)
        {
            Edge_Node<T>* p = aList[i].firstNode;
            while (p != NULL)
            {
                cout << " -> " << p->vertex;
                p = p->next;
            }
            cout << " -> NULL" << endl;
        }
        else
        {
            cout << " -> NULL" << endl;
        }
    }
}
template <class T>
void Graph<T>::DFS(int i)
{
    cout << "DFS" << endl;
    // 0 d代表为遍历
    // 1为遍历过
    //-1所链接的都遍历过
    reach[i] = 1;
    Edge_Node<T>* p = aList[i].firstNode;
    while (p != NULL)
    {
        if (reach[p->vertex] == 0)
        {
            DFS(p->vertex);
        }
        else
        {
            if (reach[p->vertex] == 1)
            {
                judge = false;
            }
        }
        p = p->next;
    }
    reach[i] = -1;
}
template <class T>
void Graph<T>::BFS(int n)
{
    queue<int> q; //广度优先搜索用队列实现
    q.push(n);
    reach[n] = -1;
    while (!q.empty())
    {
        int w = q.front() - 1;
        q.pop();
        for (Edge_Node<T>* p = aList[w].firstNode;
            p != NULL; p = p->next)
        {
            if (reach[p->vertex] == 0)
            {
                q.push(p->vertex);
                reach[p->vertex] = -1;
            }
        }
    }
}
template <class T>
bool Graph<T>::ifRing()
{
    if (!judge)
    {
        return true;
    }
    else
    {
        return false;
    }
}
template <class T>
void Graph<T>::clear()
{
    for (int i = 0; i <= V_number; i++)
    {
        reach[i] = 0;
    }
}
template <class T>
int Graph<T>::connected_components()
{
    int number = 0;
    //对每个点进行遍历，看是否到达
    for (int i = 1; i <= V_number; i++)
    {
        if (reach[i] == 0)
        {
            BFS(i);
            number++;
        }
    }
    clear();
    return number;
}
template <class T>
int Graph<T>::getmin()
{
    int minweight = aList[0].firstNode->weight;
    int min_v1 = aList[0].element;
    int i = 1;
    for (i; i < V_number; i++)
    {
        if (aList[i].firstNode != NULL)
        {
            if (aList[i].firstNode->weight < minweight)
            {
                minweight = aList[i].firstNode->weight;
                min_v1 = aList[i].element;
            }
        }
    }
    /*
    cout << minweight << endl;
    cout << min_v1 << " ";
    int mid = aList[min_v1 - 1].firstNode->vertex;
    cout << mid << endl;
    */
    return min_v1;
}
int main()
{
    int n, e;
    cin >> n >> e;
    Graph<int> G1(n);
    for (int i = 0; i < e; i++)
    {
        int v1, v2, weight;
        cin >> v1 >> v2 >> weight;
        G1.insert(v1, v2, weight);
        G1.insert(v2, v1, weight);
    }
    G1.Kruskal();
}
/*
7 9
1 6 10
1 2 28
2 7 14
2 3 16
6 5 25
7 5 24
7 4 18
3 4 12
5 4 22
*/