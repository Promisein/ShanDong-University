#include<iostream>
#include<queue>
using namespace std;
template<class T>
struct binaryTreeNode
{
	//数据成员
	T element;
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
	}
	//全部初始化
	binaryTreeNode(binaryTreeNode<T>* theRightChild,
		binaryTreeNode<T>* theLeftChild,
		const T& theElement)
	{
		element = theElement;
		rightChild = theRightChild;
		leftChild = theLeftChild;
	}
};
template<class T>
class linkedBinaryTree
{
public:
	linkedBinaryTree()
	{
		root = NULL;
		treeSize = 0;
	}
	//~linkedBinaryTree(){ erase();}
	void visit(binaryTreeNode<T>* t)
	{
		cout << t->element << " ";
	}
	int size() const { return treeSize; }          //返回结点数量
	binaryTreeNode<T>* getRoot() const { return this->root; }   //返回根节点
	binaryTreeNode<T>* NodeFinder(binaryTreeNode<T>* t, int n);  //获得序号为n的二叉树的结点（和层次遍历类似）
	void perOrder(binaryTreeNode<T>* t);           //前序遍历
	void inOrder(binaryTreeNode<T>* t);            //中序
	void postOrder(binaryTreeNode<T>* t);          //后续
	void levelOrder(binaryTreeNode<T>* t);         //层次遍历
	void construct_tree(int n);                    //按要求构造二叉树
	int  height(binaryTreeNode<T>* t);             //树的高度
	int  getNumber(binaryTreeNode<T>* t);          //获得当前子节点的个数（包括自己）
	void outNumber_Height(int n);                       //顺序输出子节点个数和树的高度
	void get_PostOrder(T* inOrder, T* preOrder, int length); //中序，前序，中序中需要读取长度
	
	//dongzi code
	binaryTreeNode<T>* bulidTree(int n, T *my_preOrder, T *my_inOrder);    //利用前序中序构造二叉树
	void exchange(binaryTreeNode<T>* currentNode);                         //交换一个结点的左右结点
	void solve(int n, T *my_preOrder, T *my_inOrder, T *outOurder);        //前序，后序，交换二叉树， 输出先序遍历
private:
	binaryTreeNode<T>* root;     //指向根节点的指针
	int treeSize;                //二叉树的结点个数
	T *levelArray;               //存顺序遍历的数组
};
template<class T>
binaryTreeNode<T>* linkedBinaryTree<T>::NodeFinder(binaryTreeNode<T>* t, int n)
{
	int count = 1;
	if(n == 1)
	{
		return root;
	}
	queue<binaryTreeNode<T>*> q;
	while(t != NULL)
	{
		if(t->element == n)
		{
			return t;
		}
		if(t->leftChild != NULL)
		{
			q.push(t->leftChild);
		}
		if(t->rightChild != NULL)
		{
			q.push(t->rightChild);
		}
		if(q.empty())
		{
			break;
		}
		t=q.front();
		q.pop();
	}
	return NULL;
}
template<class T>
void linkedBinaryTree<T>::perOrder(binaryTreeNode<T>* t)
{
	if(t != NULL)
	{
		visit(t);
		perOrder(t->leftChild);
		perOrder(t->rightChild);
	}
}
template<class T>
void linkedBinaryTree<T>::postOrder(binaryTreeNode<T>* t)
{
	if(t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		visit(t);
	}
}
template<class T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T>* t)
{
	if(t != NULL)
	{
		inOrder(t->leftChild);
		visit(t);
		inOrder(t->rightChild);
	}
}
template<class T>
void linkedBinaryTree<T>::levelOrder(binaryTreeNode<T>* t)
{
	queue<binaryTreeNode<T>*> q;
	while (t != NULL)
	{
		visit(t);
		if(t->leftChild != NULL)
		{
			q.push(t->leftChild);
		}
		if(t->rightChild != NULL)
		{
			q.push(t->rightChild);
		}
		if(q.empty())
		{
			break;
		}
		t=q.front();
		q.pop();
	}
	cout << endl;
}
template<class T>
int linkedBinaryTree<T>::height(binaryTreeNode<T>* t)
{
	if(t == NULL)
	{
		return 0;
	}
	int hl = height(t->leftChild);
	int hr = height(t->rightChild);
	if(hl > hr)
	{
		return ++hl;
	}
	else
	{
		return ++hr;
	}
}
template<class T>
void linkedBinaryTree<T>::construct_tree(int n)
{
	//利用层次遍历依次来构造树
	root = new binaryTreeNode<T> (1);
	
	for(int i = 1; i <= n; i++)
	{
		binaryTreeNode<T>* t = NodeFinder(root, i);
		int a, b;
		cin >> a >> b;
		if(a != -1)
		{
			t->leftChild = new binaryTreeNode<T> (a);
		}
		if(b != -1)
		{
			t->rightChild = new binaryTreeNode<T> (b);
		}
	}
}
template<class T>
int linkedBinaryTree<T>::getNumber(binaryTreeNode<T>* t)
{
	int number = 0;
	if(t != NULL)
	{
		number = getNumber(t->leftChild) + getNumber(t->rightChild) + 1;
	}
	return number;
}
template<class T>
void linkedBinaryTree<T>::outNumber_Height(int n)
{
	T number[n + 1];
	T h[n + 1];
	
	for(int i = 1; i <= n; i++)
	{
        binaryTreeNode<T>* t; 
		t = NodeFinder(root, i);
		number[i] = getNumber(t);
		h[i] = height(t); 
	}
	//代码优化之处在于，递归进行的nodefinder进行了一次，没有进行两次虽然下面三个循环时间复杂度都为O(n)
	//多递归一次就太浪费时间了。
	for(int i = 1; i <= n; i++)
	{
		cout << number[i] << " ";
	}
	cout << endl;
	for(int i = 1; i <= n; i++)
	{
		cout << h[i] << " ";
	}
	cout << endl;
	/*
	 binaryTreeNode<T>* t; 
	for(int i = 1; i <= n; i++)
	{
		t = NodeFinder(root, i);
		cout << getNumber(t) << " ";
	}
	cout << endl;
	for(int i = 1; i <= n; i++)
	{
		t = NodeFinder(root, i);
		cout << height(t) << " ";
	}
	cout << endl;
	*/
}
//question one
int main()
{
	int n;
	cin >> n;
	linkedBinaryTree<int> t;
	t.construct_tree(n);
	t.levelOrder(t.getRoot()); 
	t.outNumber_Height(n);          //这个函数时间超限了r
	return 0;
}
//question two
//using preOrder and inOrder to get pastOrder
template<class T>
void linkedBinaryTree<T>::get_PostOrder(T* inOrder, T* preOrder, int length) //中序，前序，中序中需要读取长度
{
	if(length == 0)
	{
		return;
	}
	binaryTreeNode<T>* currentNode = new binaryTreeNode<T>( *preOrder );
	int rootIndex = 0;     //根节点在中序中的坐标
	for( rootIndex; rootIndex < length; rootIndex++)
	{
		if(inOrder[rootIndex] == *preOrder)
		{
			break;
		}
	}//获取根节点的坐标，确定左子树和右子树

	//后序递归输出结果
	//先递归左子树，再递归右子树，输出当前的根节点
	get_PostOrder(inOrder, preOrder + 1, rootIndex);   //中序左边的递归
	get_PostOrder(inOrder + rootIndex + 1,preOrder + 1 + rootIndex, length - (rootIndex + 1));
	visit(currentNode);
}
template<class T>
binaryTreeNode<T>* linkedBinaryTree<T>::bulidTree(int n, T *my_preOrder, T *my_inOrder)
{
	if(my_preOrder == NULL, my_inOrder == NULL, n == 0)
	{
		return NULL;
	}
	//构造函数进行初始化(前序的第一个元素)
	binaryTreeNode<T>* currentRoot = new binaryTreeNode<T> (*my_preOrder);
	//cout << currentRoot->element << endl;
	if(n == 1 && *my_inOrder == *my_preOrder)
	{
		return currentRoot;  //只有一个结点，返回根节点
	}
	int left_number = 0;   //左子树的个数
	for( left_number; left_number < n; left_number++)
	{
		if(my_inOrder[left_number] == *my_preOrder)
		{
			break;
		}
	}//获取根节点的坐标，确定左子树和右子树

	if(left_number > 0)
	{
		currentRoot->leftChild = bulidTree(left_number, my_preOrder + 1, my_inOrder);
		//递归调用，即左子树的根为 my_preOrder + 1
	}
	if(n - (left_number + 1) > 0)  //为对应根节点右子树的个数
	{
		currentRoot->rightChild = bulidTree(n - (left_number + 1), my_preOrder + left_number + 1, my_inOrder + left_number + 1);
		//递归调用，在右子树中递归
	}   
	return currentRoot;
}
template<class T>
void linkedBinaryTree<T>::exchange(binaryTreeNode<T>* currentNode)
{
	if(currentNode == NULL)
	{
		return;
	}
	else
	{
		binaryTreeNode<T>* temp = currentNode->leftChild;
		currentNode->leftChild = currentNode->rightChild;
		currentNode->rightChild = temp;
		exchange(currentNode->leftChild);
		exchange(currentNode->rightChild);
		return;
	}
}
template<class T>
void linkedBinaryTree<T>::solve(int n, T *my_preOrder, T *my_inOrder, T *outOrder)
{
	root = bulidTree(n, my_preOrder, my_inOrder);  //构造二叉树
	cout << "交换前构架的二叉树：" << endl;
	postOrder(root);
	cout << endl;
	exchange(root);
	cout << "交换后的二叉树: " << endl;
	postOrder(root);
	cout << endl;
}
/*
int main()
{
	int *inorder = new int[10000];
	int *preorder = new int[10000];
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		cin >> preorder[i];
	}
	for(int i = 0; i < n; i++)
	{
		cin >> inorder[i];
	}
	int *outorder = NULL;
	linkedBinaryTree<int> t;
	//t.solve(n, preorder, inorder, outorder);
	t.get_PostOrder(inorder, preorder, n);
	delete [] inorder;
	delete [] preorder;
	return 0;
}
*/
