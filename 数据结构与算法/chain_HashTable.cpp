#include<iostream>
using namespace std;
template<class T>
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
class chain
{
public:
	chain(int initialCapacity = 10)
	{
		firstNode = NULL;
		listSize = 0;
	}         //构造函数
	~chain()
	{
		//重复清除链表的首结点，直到链表为空
		while (firstNode != NULL)
		{
			chainNode<T>* nextNode = firstNode->next;
			delete firstNode;
			firstNode = nextNode;
		}
	}                              //析构函数
	void erase(const T& theElement);                     //删除指定元素
	void insert(const T& theElement);  //指定位置插入元素
	void find(const T& theElement);              //搜索链表中是否有指定元素
private:
	chainNode<T>* firstNode;   //链表的头指针
	int listSize;              //链表的元素个数
};
template<class T>
void chain<T>::insert(const T& theElement)
{
	if (firstNode == NULL || firstNode->element > theElement)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
		listSize++;
		return;
	}
	chainNode<T>* currentNode = firstNode;
	while (currentNode->next != NULL
		&& currentNode->element < theElement
		&& currentNode->next->element < theElement)
	{
		currentNode = currentNode->next;
	}
	if (currentNode->element == theElement || (currentNode->next != NULL && currentNode->next->element == theElement))
	{
		cout << "Existed" << endl;
	}
	else
	{
		chainNode<T>* newNode = new chainNode<T>(theElement, currentNode->next);
		currentNode->next = newNode;
		listSize++;
	}
}
template<class T>
void chain<T>::erase(const T& theElement)
{
	if (firstNode == NULL)
	{
		cout << "Delete Failed" << endl;
		return;
	}
	chainNode<T>* deleteNode;
	if (theElement == firstNode->element)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		chainNode<T>* currentNode = firstNode;
		while (currentNode->next != NULL && currentNode->next->element != theElement)
		{
			currentNode = currentNode->next;
		}
		if (currentNode->next == NULL)             //遍历到了最后
		{
			cout << "Delete Failed" << endl;
			return;
		}
		deleteNode = currentNode->next;
		currentNode->next = currentNode->next->next;
	}
	listSize--;
	delete deleteNode;
	cout << listSize << endl;
}
template<class T>
void chain<T>::find(const T& theElement)
{
	chainNode<T>* currentNode = firstNode;
	while (currentNode != NULL && currentNode->element < theElement)
	{
		currentNode = currentNode->next;
	}
	if (currentNode != NULL && currentNode->element == theElement)
	{
		cout << listSize << endl;
	}
	else
	{
		cout << "Not Found" << endl;
	}

}
template<class K,class E>
class chain_HashTable
{
public:
	chain_HashTable(int theDivisor = 11);
	~chain_HashTable()
	{
		//error!!!!delete table;
		delete []table;
	}
	void insert(const K& theKey);    //插入函数
	void erase(const K& theKey);                     //删除函数
	void find(const K& theKey);
private:
	int divisor;    //除数
	chain<K>* table;     //链表数组
};
template<class K, class E>
chain_HashTable<K, E>::chain_HashTable(int theDivisor)
{
	divisor = theDivisor;
	table = new chain<K>[divisor];
}
template<class K, class E>
void chain_HashTable<K, E>::find(const K& theKey)
{
	int homeBucket = (int)theKey % divisor;
	table[homeBucket].find(theKey);
}
template<class K, class E>
void chain_HashTable<K, E>::insert(const K& theKey)
{
	int homeBucket = (int)theKey % divisor;
	table[homeBucket].insert(theKey);
}
template<class K, class E>
void chain_HashTable<K, E>::erase(const K& theKey)
{
	int homeBucket = (int)theKey % divisor;
	table[homeBucket].erase(theKey);
}
int main()
{
	int D, m;
	cin >> D >> m;
	chain_HashTable<int, int> t(D);
	for (int i = 0; i < m; i++)
	{
		int opt, x;
		cin >> opt >> x;
		switch (opt)
		{
		case 0:
			t.insert(x);
			break;
		case 1:
			t.find(x);
			break;
		case 2:
			t.erase(x);
			break;
		default:
			break;
		}
	}
	return 0;
}