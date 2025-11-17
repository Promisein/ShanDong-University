#include<iostream>
#include<utility>
using namespace std;
template<class K,class E>
class hashTable
{
public:
	hashTable(int theDivisor);         //构造函数
	~hashTable() { delete[]table; }    //析构函数
	void erase(const K& theKey);       //删除函数
	pair<const K, E>* find(const K& theKey);  //查找函数
	void insert(const pair<const K, E>& thePair);  //插入函数
	int get_dSize() { return dSize; }  //返回散列大小
 	int search(const K& theKey)const;  //查询函数
	void output();   //测试函数
private:
	pair<const K, E>** table;//散列表  
	//关于为什么要存指针，因为指针指向空值，能够表示桶为空，如果用数组存，如果默认了数组为0位空桶的话，那么theKey为0的就存不进去了
	int divisor;             //三列函数的除数
	int dSize;               //字典对数的个数
};
//构造函数
template<class K,class E>
hashTable<K, E>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;
	//初始化散列表，并且分配指针数组空间
	table = new pair<const K, E>*[divisor];
	for (int i = 0; i < divisor; i++)
	{
		table[i] = NULL;
	}
}
//查找函数，找见对应的桶
template<class K, class E>
int hashTable<K, E>::search(const K& theKey)const
{//
	int i = (int)theKey % divisor;      //起始的桶
	int j = i;                          //从起始桶开始
	//cout << j << i << endl;
	do
	{
		if (table[j] == NULL || table[j]->first == theKey)
		{
			return j;
		}
		else
		{
			j = (j + 1) % divisor;
			
		}
	} while (j!=i);                      //回到起始桶
	return j;                     //表示桶已满
}
template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey)
{
	int b = search(theKey);
	if (table[b] == NULL || table[b]->first != theKey)
	{
		cout << -1 << endl;
		return NULL;
	}
	else
	{
		cout << b << endl;
	}
	return 0;
}
template<class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
	int b = search(thePair.first);
	if (table[b] == NULL)
	{
		table[b] = new pair<const K, E>(thePair);
		dSize++;
		cout << b << endl;
	}
	else
	{
		if (table[b]->first == thePair.first)
		{
			table[b]->second = thePair.second;
			cout << b << endl;
		}
		else
		{
			cout << "Existed" << endl;
		}
	}
}
template<class K, class E>
void hashTable<K, E>::erase(const K& theKey)
{//有个简单暴力地方法就是把后面位置不对地删除掉，然后重新插了
	int b = search(theKey);
	if (table[b] == NULL || table[b]->first != theKey)
	{
		cout << "Not Found" << endl;
	}
	else
	{
		table[b] = NULL;    //删除对应的桶
		int initial_b = b;        //记录初始桶的位置, 作为循环的条件
		int exchange_b = b;  // 用来交换原来的桶
		int move_number = 0;      //记录移动的步数

		b = (b + 1) % divisor;    //从下一个桶开始遍历
		while (table[b] != NULL && b != initial_b)      //没有遇到空桶或者没有回到起始桶
		{
			int temp_initial_b= (int)table[b]->first % divisor;    //记录当前索引桶对应的起始桶
			if ((temp_initial_b <= exchange_b && temp_initial_b < b && b > exchange_b) ||          //当前桶到散列表末尾之间的范围内的移动
				(temp_initial_b <= exchange_b && temp_initial_b > b && exchange_b > b) ||      //当前桶到散列表末尾 -> 再从散列表的头开始移动
				(temp_initial_b > b && b > exchange_b)                                                //按顺序往前移动    
				)
			{
				table[exchange_b] = table[b];     //与起始桶交换
				exchange_b = b;
				move_number++;
			}
			
			b = (b + 1) % divisor;    //往前开始遍历
		}
		cout << move_number << endl;
		table[exchange_b] = NULL;
	}
}
template<class K, class E>
void hashTable<K, E>::output()
{
	/*
	for (int i = 0; i < this->divisor; i++)
	{
		if (table[i] == NULL)
		{
			cout << "theKey: NUll" << " " << "value: NUll" << endl;
		}
		else
		{
			cout << "theKey: " << table[i]->first 
				<< " value: " << table[i]->second 
				<< endl;
		}
	}
	*/
	cout << "bucket:\t";
	for (int i = 0; i < this->divisor; i++)
	{
		
		cout << i << "\t";
	}
	cout << endl;
	cout << "thekey:\t";
	for (int i = 0; i < this->divisor; i++)
	{
		
		if (table[i] == NULL)
		{
			cout << "*" << "\t";
		}
		else
		{
			cout << table[i]->first << "\t";
		}
	}
	cout << endl;
	cout << "themod:\t";
	for (int i = 0; i < this->divisor; i++)
	{
		
		if (table[i] == NULL)
		{
			cout << "*" << "\t";
		}
		else
		{
			cout << table[i]->first % divisor << "\t";
		}
	}
	cout << endl;
}
int main()
{
	int D, m;
	cin >> D >> m;
	hashTable<int, int> dic(D);
	int opt, x;          //操作模式,和对应元素操作
	for (int i = 0; i < m; i++)
	{
		cin >> opt;
		if (opt == 0)
		{
			cin >> x;
			pair<int, int>mypair(x, 520);
			dic.insert(mypair);
		}
		else
		{
			if (opt == 1)
			{
				cin >> x;
				pair<const int, int>* p = dic.find(x);
			}
			else
			{
				if (opt == 2)
				{
					cin >> x;
					dic.erase(x);
					//dic.output();
				}
				if (opt == 3)
				{
					dic.output();
				}
			}
		}
	}
	return 0;
}
/*
7 15
1 21
0 1
0 13
0 5
0 23
0 26
0 33
*/
/*
  1
  6
  5
  1->2
  5->6->0
  5->6->0->1->2->3
*/
/*
11 100
0 0
0 1
0 21
0 18
0 17
0 28
0 39
0 12
0 62
0 51
0 50
*/