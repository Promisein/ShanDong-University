#include <iostream>
using namespace std;
template <class T>
struct binaryTreeNode
{
    //数据成员
    T element;
    int left_number; //如果频繁的的递归计算左子树的大小，太浪费时间，
    //所以设置变量左子树的大小，
    //方便以后搜索索引时方便进行操作

    binaryTreeNode<T>* rightChild;
    binaryTreeNode<T>* leftChild;

    //成员函数
    //构造函数
    binaryTreeNode()
    {
        rightChild = leftChild = NULL;
    }
    //初始化元素
    binaryTreeNode(const T& theElement)
    {
        element = theElement;
        rightChild = leftChild = NULL;
        left_number = 0;
    }
    //全部初始化
    binaryTreeNode(binaryTreeNode<T>* theRightChild,
        binaryTreeNode<T>* theLeftChild,
        const T& theElement, int theLeft_number)
    {
        element = theElement;
        left_number = theLeft_number;
        rightChild = theRightChild;
        leftChild = theLeftChild;
    }
};
template <class T>
class Search_Tree
{
public:
    Search_Tree()
    {
        root = NULL;
        treesize = 0;
    }
    ~Search_Tree() {};
    void find(const T& theKey);   //查找
    void insert(const T& theKey); //插入
    void pop(const T& theKey);    //删除theKey
    void pop_rank(int theIndex);  //删除名次为theindex的元素
    void find_rank(int theIndex); //查找名次为theindex的元素
private:
    binaryTreeNode<T>* root; //搜索树的根节点
    int treesize;            //树的大小
};
template <class T>
void Search_Tree<T>::insert(const T& theKey)
{
    int sum = 0; //求比较元素的异或和
    binaryTreeNode<T>* p = root;
    binaryTreeNode<T>* pp = root; //用pp代表p的父亲结点
    while (p != NULL)
    { //检查元素p -> element
        pp = p;
        if (theKey > p->element) //插入元素大于当前结点的值，往右子树遍历
        {
            sum ^= p->element;
            p = p->rightChild;
        }
        else
        {
            if (theKey < p->element) //插入元素小于当前结点的值，往左子树遍历
            {
                sum ^= p->element;
                p = p->leftChild;
            }
            else
            {
                cout << 0 << endl; //已经 存在输出0
                return;
            }
        }
    }
    //为thekey建立一个新的结点与然后与pp连接
    binaryTreeNode<T>* newNode = new binaryTreeNode<T>(theKey);
    if (root != NULL)
    {
        if (theKey < pp->element)
        {
            pp->leftChild = newNode;
        }
        else
        {
            pp->rightChild = newNode;
        }
    }
    else //如果为空树
    {
        root = newNode;
    }
    treesize++;
    //对结点的左孩子进行更新的代码 code
    binaryTreeNode<T>* currentNode = root;
    while (currentNode->element != theKey)
    {
        if (currentNode->element < theKey)
        {
            currentNode = currentNode->rightChild;
        }
        else
        {
            if (currentNode->element > theKey)
            {
                currentNode->left_number++;
                currentNode = currentNode->leftChild;
            }
        }
    }
    cout << sum << endl;
}
template <class T>
void Search_Tree<T>::find(const T& theKey)
{
    int sum = 0; //求比较元素的异或和
    binaryTreeNode<T>* p = root;
    while (p != NULL && p->element != theKey)
    {
        if (theKey > p->element) //插入元素大于当前结点的值，往右子树遍历
        {
            sum ^= p->element;
            p = p->rightChild;
        }
        else
        {
            if (theKey < p->element) //插入元素小于当前结点的值，往左子树遍历
            {
                sum ^= p->element;
                p = p->leftChild;
            }
        }
    }
    if (p == NULL)
    {
        cout << 0 << endl; //未找到输出0
    }
    else
    {
        sum ^= p->element;
        cout << sum << endl;
    }
}
template <class T>
void Search_Tree<T>::pop(const T& theKey)
{
    int sum = 0;
    binaryTreeNode<T>* deleteNode = root;
    binaryTreeNode<T>* P_deleteNode = NULL; //要删除结点的双亲
    while (deleteNode != NULL && deleteNode->element != theKey)
    {
        P_deleteNode = deleteNode;
        if (theKey > deleteNode->element)
        {
            sum ^= deleteNode->element;
            deleteNode = deleteNode->rightChild;
        }
        else
        {
            if (theKey < deleteNode->element)
            {
                sum ^= deleteNode->element;
                deleteNode = deleteNode->leftChild;
            }
        }
    }
    if (deleteNode == NULL) //未找到删除的元素
    {
        cout << 0 << endl;
        return;
    }
    sum ^= deleteNode->element;
    //对结点的左孩子进行更新的代码 code
    binaryTreeNode<T>* currentNode = root;
    // current != NUll;
    while (currentNode->element != theKey)
    {
        if (currentNode->element < theKey)
        {
            currentNode = currentNode->rightChild;
        }
        else
        {
            if (currentNode->element > theKey)
            {
                currentNode->left_number--;
                currentNode = currentNode->leftChild;
            }
        }
    }

    //对二叉树进行重构
    //当deleteNode 有两个孩子结点
    if (deleteNode->leftChild != NULL && deleteNode->rightChild != NULL)
    {
        //在deleteNode的有孩子中寻找最小值
        binaryTreeNode<T>* minElement = deleteNode->rightChild;
        binaryTreeNode<T>* P_minElement = deleteNode; //最小值结点的父亲结点
        while (minElement->leftChild != NULL)
        {
            minElement->left_number--; //因为要移动右子树的最小值代替原来的结点
            P_minElement = minElement;
            minElement = minElement->leftChild;
        }

        //将minElement结点移动到 deleteNode,创建一个新的结点
        binaryTreeNode<T>* newNode = new binaryTreeNode<T>(deleteNode->rightChild, deleteNode->leftChild,
            minElement->element, deleteNode->left_number);
        if (P_deleteNode == NULL) //为根节点
        {
            root = newNode;
        }
        else
        { //判断是P_deleteNode的左子树还是右子树
            if (deleteNode == P_deleteNode->leftChild)
            {
                P_deleteNode->leftChild = newNode;
            }
            else
            {
                P_deleteNode->rightChild = newNode;
            }
        }

        //这里就看不懂了这个代买到底在干嘛
        if (P_minElement == deleteNode)   //将P_deleteNode指针移动到P_minElement处
        {
            //若要删除结点左子树的个数为一
            P_deleteNode = newNode;
        }
        else
        {
            P_deleteNode = P_minElement;
        }
        delete deleteNode;
        deleteNode = minElement;
    }

    //当deleteNode 最多有一个孩子结点
    binaryTreeNode<T>* c; //把要删除的子树存在c
    if (deleteNode->leftChild != NULL)
    {
        c = deleteNode->leftChild;
    }
    else
    {
        c = deleteNode->rightChild;
    }
    //删除deleteNode
    if (deleteNode == root)
    {
        root = c;
    }
    else
    {
        //判断deleteNode是父亲结点的左孩子还是右孩子
        if (deleteNode == P_deleteNode->leftChild)
        {
            P_deleteNode->leftChild = c;
        }
        else
        {
            P_deleteNode->rightChild = c;
        }
    }
    treesize--;
    delete deleteNode;
    cout << sum << endl;
}
template <class T>
void Search_Tree<T>::find_rank(int theIndex)
{
    binaryTreeNode<T>* currentNode = root;
    binaryTreeNode<T>* P_currentNode = NULL;
    while (currentNode != NULL && currentNode->left_number != theIndex)
    {
        if (theIndex > currentNode->left_number) //左子树的个数比索引小，索引要到右子树判断
        {
            theIndex = theIndex - (currentNode->left_number + 1);
            currentNode = currentNode->rightChild;
        }
        else
        {
            if (theIndex < currentNode->left_number) //左子树的个数比索引大，索引到左子树进行判断
            {
                currentNode = currentNode->leftChild;
            }
        }
    }
    //cout << currentNode->element << endl;
    //cout << currentNode->left_number << endl;
    if (currentNode)
    {
        find(currentNode->element);
    }
    
}
template <class T>
void Search_Tree<T>::pop_rank(int theIndex)
{
    binaryTreeNode<T>* currentNode = root;
    binaryTreeNode<T>* P_currentNode = NULL;
    while (currentNode != NULL && currentNode->left_number != theIndex)
    {
        if (theIndex > currentNode->left_number) //左子树的个数比索引小，索引要到右子树判断
        {
            theIndex = theIndex - (currentNode->left_number + 1);
            currentNode = currentNode->rightChild;
        }
        else
        {
            if (theIndex < currentNode->left_number) //左子树的个数比索引大，索引到左子树进行判断
            {
                currentNode = currentNode->leftChild;
            }
        }
    }
    if (currentNode)
    {
        pop(currentNode->element);
    }
}
int main()
{
    //cout << "binary search tree is constructing!" << endl;
    int m;
    cin >> m;
    int a, b;
    Search_Tree<int> st;
    for (int i = 0; i < m; i++)
    {
        cin >> a;
        if (a == 0)
        {
            cin >> b;
            st.insert(b);
        }
        if (a == 1)
        {
            cin >> b;
            st.find(b);
        }
        if (a == 2)
        {
            cin >> b;
            st.pop(b);
        }
        if (a == 3)
        {
            cin >> b;
            //因为索引为b的元素前面的元素个数为b-1
            st.find_rank(b - 1);
        }
        if (a == 4)
        {
            cin >> b;
            st.pop_rank(b - 1);
        }
    }
    return 0;
}