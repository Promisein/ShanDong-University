#include<iostream>
using namespace std;
template<class T>
//定义结点类
struct chainNode
{
	//数据成员
	T element;
	chainNode<T>* next;

	//solutions
	chainNode() {}     //默认构造函数
	chainNode(const T& element)
	{
		this->element = element;
	}//构造函数
	chainNode<T>(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};
template<class T>
//定义链表类
class chain
{
public:
	chain(int initialCapacity = 10);
	chain(const chain<T>& theList);
	~chain();

	void erase(int theIndex);                     //删除指定元素
	void insert(int theIndex, const T& element);  //指定位置插入元素
	int search(const T& theElement);              //搜索链表中是否有指定元素
	void reserve();                               //原地逆置链表
	int mysum();                                  //异或和
	void output();                                //输出链表
	chainNode<T>* get_firstNode() { return this->firstNode; }    //获得链表的头结点
	void mysort(chainNode<T>* firstNode);         //链表排序函数(头结点和元素个数)
	void chain_join(chain<T>& Node1, chain<T>& Node2);       //要连接的两个链表的头结点
	class iterator        //定义迭代器类（前驱迭代器）
	{
	public:
		//构造函数
		iterator(chainNode<T>* theNode = NULL)
		{
			node = theNode;
		}
		//迭代器加法操作
		iterator& operator ++()     //前加
		{
			node = node->next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			node = node->next;
			return old;
		}
		//解引用操作符
		T& operator *()const { return node->element; }
		T* operator ->()const { return &node->element; }
		//相等检验
		bool operator !=(const iterator right) const { return node != right.node; }
		bool operator ==(const iterator right) const { return node == right.node; }
	protected:
		chainNode<T>* node;
	};
	iterator begin() { return iterator(this->firstNode); }      //迭代器类型函数begin()
	iterator end() { return iterator(NULL); }  //迭代器类型函数end()
private:
	chainNode<T>* firstNode;   //链表的头指针
	int listSize;              //链表的元素个数
	//void checkIndex(int theIndex) const;

};
template<class T>
chain<T>::chain(int initialCapacity)      //构造函数
{
	firstNode = NULL;
	listSize = 0;
}
template<class T>
chain<T>::chain(const chain<T>& theList)       //复制构造函数(原链表的对象要复制 theList 链表)
{
	//链表为空
	if (listSize == 0)
	{
		firstNode = NULL;
		return;
	}
	//链表不为空
	this->firstNode = new chainNode<T>((theList.firstNode)->element);        //头结点new出一个用theList.firstNode->element初始化
	chainNode<T>* sourceNode = (theList.firstNode)->next;
	chainNode <T>* targetNode = firstNode;                                    //复制链表theList的头结点
	//for(; sourceNode != NULL; sourceNode = sourceNode->next)
	while (sourceNode != NULL)
	{
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;
}
template<class T>
chain<T>::~chain()   //析构函数，删除链表的所有结点
{
	//重复清除链表的首结点，直到链表为空
	while (firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}
template<class T>
void chain<T>::erase(int theIndex)   //删除指定索引的元素
{
	chainNode<T>* deleteNode;    //deleteNode指要删除的结点
	//删除首结点
	if (theIndex == 0)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		//用指针p指向要删除的结点的前结点
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		deleteNode = p->next;
		p->next = deleteNode->next;  //p->next=p->next->next;
	}
	listSize--;
	delete deleteNode;
}
template<class T>
void chain<T>::insert(int theIndex, const T& theElement)    //插入元素theElement并将其索引为theIndex
{
	if (theIndex == 0)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else
	{
		//用指针p指向要新结点的前结点
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		p->next = new chainNode<T>(theElement, p->next);     //新结点的next指针指向原来前结点的下一个结点
	}
	listSize++;
}
template<class T>
int chain<T>::search(const T& theElement)   //查询元素，并输出其首次索引，不存在则返回-1
{
	//用currentNode记录当前结点
	chainNode<T>* currentNode = firstNode;   //初始结点
	int currentIndex = 0;      //当前结点的索引
	while (currentNode != NULL && currentNode->element != theElement)
	{
		currentNode = currentNode->next;
		currentIndex++;
	}
	if (currentNode == NULL)
	{
		return -1;
	}
	else
	{
		return currentIndex;
	}
}
template<class T>
void chain<T>::reserve()            //翻转链表
{
	if (firstNode->next == NULL || firstNode == NULL)
	{
		//头结点为空或者只有一个结点，即firstNode->next = NUll
		return;
	}
	chainNode<T>* frontNode = firstNode;   //前沿结点,初始指向第一个结点
	chainNode<T>* lastNode = NULL;               //末尾结点
	chainNode<T>* midNode = firstNode;     //中间结点，初始指向第一个结点
	/*
	chainNode<T>* endNode = firstNode;           //最后结点
	while (endNode != NULL)
	{
		endNode = endNode->next;
	}
	firstNode->next = endNode;
	*/
	//首结点到末尾
	/*
	for (int i = 0; i < listSize; i++)
	{
		frontNode = frontNode->next;
		midNode->next = lastNode;
		lastNode = midNode;
		midNode = frontNode;
	}
	firstNode->next = lastNode;
	*/   //程序有bug，以索引为临界条件，循环会异常退出
	//最后遍历完frontNode = NULL;   midNode = NULL; lastNode值向原链表的最后一位;
	//（优化代码）
	while (midNode != NULL)
	{
		frontNode = frontNode->next;
		midNode->next = lastNode;
		lastNode = midNode;
		midNode = frontNode;
	}
	firstNode = lastNode;
}
template<class T>
int chain<T>::mysum()
{
	int sum = 0;
	int index = 0;
	for (iterator beginning = begin(); beginning != end(); beginning++)
	{
		//cout << index << "\t" << *beginning << "\t" << a << endl;
		sum = sum + (index ^ (*beginning));             //一定一定要加上括号！！！！
		index++;
	}
	return sum;
}
template<class T>
void chain<T>::output()     //输出链表元素
{
	for (iterator iter = begin(); iter != end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
}
template<class T>
void chain<T>::mysort(chainNode<T>* firstNode)          //链表排序函数(头结点)
{
	//bool judge = false;                              //判断排序是否完整
	for (iterator iter1 = begin(); iter1 != end(); iter1++)
	{
		//if (judge) { break; }
		//judge = true;
		for (iterator iter2 = begin(); iter2 != end(); iter2++)
		{
			if (*iter2 > *iter1)
			{
				T temp = *iter1;
				*iter1 = *iter2;
				*iter2 = temp;
				//judge = false;
			}
		}
	}
}
template<class T>
void chain<T>::chain_join(chain<T>& List1, chain<T>& List2)
{
	iterator iter1 = List1.begin();
	for (iter1; iter1 != List1.end(); iter1++)
	{
		List2.insert(0, *iter1);
	}
	//List2.output();
	List2.mysort(List2.get_firstNode());
	//List2.output();
	cout << List2.mysum();
}

int main()
{
	int N, M;
	cin >> N >> M;
	chain<int> list1, list2;
	int input_element;
	for (int i = 0; i < N; i++)
	{
		cin >> input_element;
		list1.insert(i, input_element);
	}//构建链表1
	for (int i = 0; i < M; i++)
	{
		cin >> input_element;
		list2.insert(i, input_element);
	}//构建链表2

	//list1.output();
	//list2.output();
	list1.mysort(list1.get_firstNode());
	list2.mysort(list1.get_firstNode());
	//list1.output();
	//list2.output();
	cout << list1.mysum() << endl;
	cout << list2.mysum() << endl;
	if (N == 0)    // 链表1为空
	{
		cout << list2.mysum() << endl;
	}
	if (M == 0)   //链表2为空
	{
		cout << list1.mysum() << endl;
	}
	if ((M != 0) && (N != 0))   //链表都不为空
	{
		list2.chain_join(list1, list2);
	}
	return 0;
}