#include <iostream>
using namespace std;
template <class T>
struct HoffmanTree_Node
{
    //数据成员
    T weight = 0; //权重
    HoffmanTree_Node* left = NULL;
    HoffmanTree_Node* right = NULL;

    //构造函数
    HoffmanTree_Node(){}
    HoffmanTree_Node(T w)
    {
        weight = w;
        left = right = NULL;
    }
    HoffmanTree_Node(T w, HoffmanTree_Node* l, HoffmanTree_Node* r)
    {
        weight = w;
        left = l;
        right = r;
    }
};

template <class T>
class Hoffman_Tree
{
private:
    HoffmanTree_Node<T>** Heap; //小根堆(寻找出权重中最小的两个值)
    int heapSize;

public:
    Hoffman_Tree(T* weight_character, int n);
    ~Hoffman_Tree() { delete[] Heap; };
    void initial();                                //对heap进行堆化
    void construct_Tree();                         //构造霍夫曼树
    HoffmanTree_Node<T>* top() { return Heap[1]; } //获得堆顶的元素
    void pop();
    void push(HoffmanTree_Node<T>* TreeNode);
    void output();
    void sum_Length(HoffmanTree_Node<T>* t, int n);
};

template <class T>
Hoffman_Tree<T>::Hoffman_Tree(T* weight_character, int n)
{
    heapSize = n;
    Heap = new HoffmanTree_Node<T> *[27];
    /*
    HoffmanTree_Node<T>* temp;
    for (int i = 1; i <= n; i++)
    {
        temp = new HoffmanTree_Node<T>(weight_character[i - 1]);
        push(temp);
    }
    */
    for (int i = 1; i <= n; i++)
    {
        Heap[i] = new HoffmanTree_Node<T>(weight_character[i - 1]);
    }
    
    for (int i = n + 1; i < 27; i++)
    {
        Heap[i] = new HoffmanTree_Node<T>;
    }
    
    //output();
} //将权重的值录入到heap中
//asdfghjklzxcvbnmqwertyuiopaaaaa
template <class T>
void Hoffman_Tree<T>::initial()
{
   
    //cout << heapSize << endl;
    for (int root = heapSize / 2; root >= 1; root--)
        //从最后一个有孩子的结点开始进行堆化
    {
        //cout << "debug!" << endl;
        HoffmanTree_Node<T>* rootElement = Heap[root];
        //为rootElement寻找合适的位置
        int child = root * 2;
        while (child <= heapSize)
        {
            
            //寻找较小的兄弟结点
            //if ((Heap[child]->weight > Heap[child + 1]->weight) && (child < heapSize))
            if ((child < heapSize) &&(Heap[child]->weight > Heap[child + 1]->weight))
            {
                child++;
            }
            /*
            if (child < heapSize)
            {
                if (Heap[child]->weight > Heap[child + 1]->weight)
                {
                    child++;
                }
            }
            */
            if (rootElement->weight <= Heap[child]->weight)
            {
                
                break;
            }
            /*
            else
            {
                cout << "here3" << endl;
                Heap[child / 2] = Heap[child]; //将孩子结点与父亲结点进行交换
                child *= 2;
            }
            */
            
            Heap[child / 2] = Heap[child]; //将孩子结点与父亲结点进行交换
            child *= 2;
        }
        Heap[child / 2] = rootElement;
    }
    //output();
}
template <class T>
void Hoffman_Tree<T>::push(HoffmanTree_Node<T>* TreeNode)
{
    int currentNode = ++heapSize;
    while (currentNode != 1 && Heap[currentNode / 2]->weight > TreeNode->weight)
    {
        Heap[currentNode] = Heap[currentNode / 2];
        currentNode /= 2;
    }
    Heap[currentNode] = TreeNode;
    // output();
}
template <class T>
void Hoffman_Tree<T>::pop()
{
    HoffmanTree_Node<T>* lastElement = Heap[heapSize--];
    int currentNode = 1, child = 2;
    while (child <= heapSize)
    {
        if (child < heapSize && Heap[child]->weight > Heap[child + 1]->weight)
        {
            child++;
        }
        if (lastElement->weight <= Heap[child]->weight)
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
    // output();
}
//利用最小堆进行排序，先选出最小的两个树结点，然后把它们的权重和作为他们的父亲结点
template <class T>
void Hoffman_Tree<T>::construct_Tree()
{
    //cout << heapSize << endl;
    HoffmanTree_Node<T>* x, * y, * z;
    if (heapSize == 1)
    {
        x = top();
        pop();
        z = new HoffmanTree_Node<T>(x->weight, x, NULL);
        push(z);
    }
    while (heapSize != 1)
        //在heap中只剩一个元素时停止循环
    {
        x = top();
        pop();
        y = top();
        pop();
        //取出最年轻的两颗树
        z = new HoffmanTree_Node<T>(x->weight + y->weight, x, y);
        //将x,y作为z的左右子树,构建霍夫曼树
        push(z);
    }
}
template <class T>
void Hoffman_Tree<T>::output()
{
    for (int i = 1; i <= heapSize; i++)
    {
        cout << Heap[i]->weight << " ";
    }
    cout << endl;
}
int sum = 0; //计算权重
template <class T>
void Hoffman_Tree<T>::sum_Length(HoffmanTree_Node<T>* t, int n)
{
    if (t != NULL)
    {
        if (t->left == NULL && t->right == NULL)
        {
            sum += n * t->weight;
        }
        sum_Length(t->left, n + 1);
        sum_Length(t->right, n + 1);
    }
}
int main()
{
    // cout << " Hoffman_Tree is constructing!" << endl;
    string str;
    cin >> str;

    //计算出每个英文字母的权重
    int* character = new int[26]; //用来表示26个英文字母
    for (int i = 0; i < 26; i++)
    {
        character[i] = 0;
    } //初始化
    for (int i = 0; i < str.length(); i++)
    {
        character[(int)str[i] - 97]++;
    }
    //遍历出字符的频率
    int not_null_number = 0; //来记录有多少个字符不等于零
    for (int i = 0; i < 26; i++)
    {
        if (character[i] != 0)
        {
            not_null_number++;
        }
    }
    //英文字母按照公认的默认顺序在数组中排列
    int* weight_character = new int[not_null_number];
    int j = 0;
    for (int i = 0; i < 26; i++)
    {
        if (character[i] != 0)
        {
            weight_character[j] = character[i];
            j++;
        }
    }
    /*
    for (int i = 0; i < not_null_number; i++)
    {
        cout << weight_character[i] << " ";
    }
    cout << endl;
    */
    //构建霍夫曼树
    Hoffman_Tree<int> h(weight_character, not_null_number);
    //h.output();
    h.initial(); //初始化为最小堆
    //h.output();
    h.construct_Tree();
    //h.sum_Length(h.top(), 0);
    h.sum_Length(h.top(), 0);
    cout << sum << endl;
    delete[] weight_character;
    delete[] character;
    return 0;
}
// aaaaaabbcccdddeeeefffffffff
//asdfghjklzxcvbnmqwertyuiopaaaaa
