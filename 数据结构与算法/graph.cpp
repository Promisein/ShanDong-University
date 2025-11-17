#include <iostream>
#include <queue>
using namespace std;
template <class T>
struct Edge_Node //定义边结点
{
    T vertex;           //该边的顶点位置
    Edge_Node<T>* next; //指向下一条边的指针
};

//邻接表  adjacency list
template <class T>
struct adj_List
{
    int element;             //存放顶点的第一个信息
    Edge_Node<T>* firstNode; //存放指向顶点 element的第一个顶点
};
#define max 100011
template <class T>
class Graph
{
public:
    Graph(int n = 250); //构造函数
    /*
    ~Graph()
    {
        delete []aList;
        delete []reach;
    }
    */
    void clear();
    void insert(int v1, int v2); //插入函数，插入以v1，v2为顶点的边
    void erase(int v1, int v2);  //删除函数，删除边
    void BFS(int n);             //广度优先搜索
    void DFS(int n);             //深度优先搜索
    void outBFS(int n);          //输出广度优先搜索字典序最小
    void outDFS(int n);          //输出深度优先搜索字典序最小
    void length_BFS(int n);      // BFS的长度
    void length_DFS(int n);      // DFS的长度
    void output();               //输出函数
    void connected_components(); //寻找连通分量
    void min_Path(int v1, int v2);

private:
    adj_List<T> aList[max]; //创建具有100010个结点的图（后期优化看能不能减少空间动态申请）
    int V_number;              //顶点数
    int E_number;              //边数
    bool* reach;               //标记数组，用来标记是否被遍历
    /*adj_List<T> *aList;*/
};
template <class T>
Graph<T>::Graph(int n)
{
    /*
    aList = new adj_List<T>[V_number];
    */
    V_number = n;
    E_number = 0;
    for (int i = 0; i < n; i++)
    {
        aList[i].element = i + 1;
        aList[i].firstNode = NULL;
    }
    reach = new bool[V_number + 1];
    for (int i = 0; i <= V_number; i++)
    {
        reach[i] = true;
    }
}
template <class T>
void Graph<T>::clear()
{
    for (int i = 0; i <= V_number; i++)
    {
        reach[i] = true;
    }
}
template <class T>
void Graph<T>::insert(int v1, int v2)
{
    Edge_Node<T>* edge1 = new Edge_Node<T>;
    edge1->vertex = v2;

    Edge_Node<T>* p = aList[v1 - 1].firstNode;
    Edge_Node<T>* pp = NULL;         // p的上一个边结点
    if (p == NULL || p->vertex > v2) //当要插入的表头为空，或者头结点的元素值大于v2 - 1
    {
        edge1->next = aList[v1 - 1].firstNode;
        //如果p=null ，有效的只有执行这一步
        aList[v1 - 1].firstNode = edge1;
    } //从小到大插入边
    else
    {
        while (p != NULL && p->vertex < v2) //当前仅当p不为空节点，而且p的边元素小与 v2 - 1，保证顺序
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
        cout << "warning: the edge that you want to delete dose not exist" << endl;
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
void Graph<T>::BFS(int n)
{
    queue<int> q; //广度优先搜索用队列实现
    q.push(n);
    reach[n] = false;
    while (!q.empty())
    {
        int w = q.front() - 1;
        q.pop();
        for (Edge_Node<T>* p = aList[w].firstNode;
            p != NULL; p = p->next)
        {
            if (reach[p->vertex])
            {
                q.push(p->vertex);
                reach[p->vertex] = false;
            }
        }
    }
}
template <class T>
void Graph<T>::DFS(int n)
{
    reach[n] = false;
    Edge_Node<T>* p = aList[n - 1].firstNode;
    while (p != NULL)
    {
        if (reach[p->vertex])
        {
            DFS(p->vertex);
        }
        else
        {
            p = p->next;
        }
    }
}
template <class T>
void Graph<T>::outBFS(int n) //以n为开始的顶点
{
    queue<int> q; //广度优先搜索用队列实现
    q.push(n);
    reach[n] = false;
    while (!q.empty())
    {
        int w = q.front() - 1;
        cout << aList[w].element << " ";

        q.pop();
        for (Edge_Node<T>* p = aList[w].firstNode;
            p != NULL; p = p->next)
        {
            if (reach[p->vertex])
            {
                q.push(p->vertex);
                reach[p->vertex] = false;
            }
        }
    }
    cout << endl;
}
template <class T>
void Graph<T>::outDFS(int n)
{
    cout << aList[n - 1].element << " ";
    reach[n] = false;
    Edge_Node<T>* p = aList[n - 1].firstNode;
    while (p != NULL)
    {
        if (reach[p->vertex])
        {
            outDFS(p->vertex);
        }
        else
        {
            p = p->next;
        }
    }
}
template <class T>
void Graph<T>::length_BFS(int n)
{
    int number = 0;
    clear();
    queue<int> q; //广度优先搜索用队列实现
    q.push(n);
    number++;
    reach[n] = false;
    while (!q.empty())
    {
        int w = q.front() - 1;
        q.pop();
        for (Edge_Node<T>* p = aList[w].firstNode;
            p != NULL; p = p->next)
        {
            if (reach[p->vertex])
            {
                q.push(p->vertex);
                number++;
                reach[p->vertex] = false;
            }
        }
    }
    cout << number << endl;
}
int DFS_number = 0; //记录DFS的路径长度
template <class T>
void Graph<T>::length_DFS(int n) //第二个参数是递归次数，即长度
{
    DFS_number++;
    reach[n] = false;
    Edge_Node<T>* p = aList[n - 1].firstNode;
    while (p != NULL)
    {
        if (reach[p->vertex])
        {
            length_DFS(p->vertex);
        }
        else
        {
            p = p->next;
        }
    }
}
template <class T>
void Graph<T>::connected_components()
{
    int number = 0;
    //对每个点进行遍历，看是否到达
    for (int i = 1; i <= V_number; i++)
    {
        if (reach[i] == true)
        {
            BFS(i);
            number++;
        }
    }
    cout << number << endl;
    clear(); //清除标记
    for (int i = 1; i <= V_number; i++)
    {
        if (reach[i] == true)
        { //由于用顺序链表存储邻接链表，所以直接输出第一个元素即可
            cout << i << " ";
            BFS(i);
        }
    }
    cout << endl;
}
template <class T>
void Graph<T>::min_Path(int v1, int v2)
{
    clear();
    queue<int> q;
    int num = V_number + 1;
    q.push(v1);
    reach[q.front()] = false;
    int *path= new int[num];
    for (int i = 0; i < num; i++)
    {
        path[i] = 0;
    }
    while (!q.empty())
    {
        int w = q.front() - 1;
        q.pop();
        Edge_Node<T>* p = aList[w].firstNode;
        while (p != NULL)
        {
            //如果没有被标记
            if (reach[p->vertex])
            {
                if (p->vertex == v2)
                {
                    cout << path[w + 1] + 1 << endl;
                    return;
                }
                path[p->vertex] = path[w + 1] + 1;

                q.push(p->vertex);
                reach[p->vertex] = false;
            }
            p = p->next;
        }

    }
    cout << -1 << endl;


    /*
    //利用广度优先搜索寻找最短路径
    int number = 0;
    queue<int> q;
    q.push(v1);
    reach[v1] = false;
    while (!q.empty())
    {
        int w = q.front() - 1;
        //cout << aList[w].element << " ";
        number++;
        q.pop();
        for (Edge_Node<T>* p = aList[w].firstNode; p != NULL; p = p->next)
        {
            if (reach[p->vertex])
            {
                if (p->vertex == v2)
                {
                    //cout << v2 << endl;
                    break;
                }
                q.push(p->vertex);
                reach[p->vertex] = false;
            }
        }
    }
    cout << number << endl;
    */
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
int main()
{
    //cout << "Graph is constructing!" << endl;
    int n, m, s, t;
    cin >> n; //点的个数
    cin >> m; //操作数
    cin >> s >> t;
    Graph<int> G(n);
    /*
    cout << "1.insert    2.erase     3.BFS   4.DFS    5.onnected_components     6. lBFS,LDFS" << endl;
    for (int i = 0; i < m; i++)
    {
        int d;
        cin >> d;
        if (d == 0)
        {
            int v1, v2;
            cin >> v1 >> v2;
            G.insert(v1, v2);
            G.insert(v2, v1);
            G.output();
            cout << endl;
        }
        if (d == 1)
        {
            int v1, v2;
            cin >> v1 >> v2;
            G.erase(v1, v2);
            G.erase(v2, v1);
            G.output();
            cout << endl;
        }
        if (d == 2)
        {
            G.clear();
            cout << "广度优先搜索！" << endl;
            int nn;
            cin >> nn;
            G.outBFS(nn);
            cout << endl;
        }
        if (d == 3)
        {
            G.clear();
            cout << "深度优先搜索！" << endl;
            int nn;
            cin >> nn;
            G.outDFS(nn);
            cout << endl;
            cout << endl;
        }
        if (d == 4)
        {
            G.clear();
            G.connected_components();
        }
        if (d == 5)
        {
            G.clear();
            int nn;
            cin >> nn;
            G.length_BFS(nn);
            G.clear();
            G.length_DFS(nn);
            cout << DFS_number << endl;
            DFS_number = 0;
        }
        if(d == 6)
        {
            G.output();
        }
        if (d == 7)
        {
            int v1, v2;
            cin >> v1 >> v2;
            G.min_Path(v1, v2);
        }
    }
    */
    for (int i = 0; i < m; i++)
    {
        int d;
        cin >> d;
        if (d == 0)
        {
            int v1, v2;
            cin >> v1 >> v2;
            G.insert(v1, v2);
            G.insert(v2, v1);
        }
        if (d == 1)
        {
            int v1, v2;
            cin >> v1 >> v2;
            G.erase(v1, v2);
            G.erase(v2, v1);
        }
    }
    G.clear();
    G.connected_components();
    G.clear();
    G.length_DFS(s);
    cout << DFS_number << endl;
    G.clear();
    G.outDFS(s);
    cout << endl;
    G.clear();
    G.length_BFS(t);
    G.clear();
    G.outBFS(t);
    G.clear();
    G.min_Path(s, t);
    
    return 0;
}
/*
10 100
0 1 3
0 1 2
0 1 4
0 2 5
0 3 5
0 3 6
0 3 4
0 4 6
0 4 7
0 5 8
0 6 8
0 7 8
0 7 9
0 8 10
0 9 10
*/