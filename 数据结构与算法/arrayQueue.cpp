#include<iostream>
using namespace std;
template<class T>
class arrayQueue
{
public:
	arrayQueue(int intialSize = 10);             //构造函数
	~arrayQueue()
	{
		delete[] element;
	}
	void push(const T& theElement);               // 插入函数
	void pop();                                   //删除函数
	int Size()
	{
		return (queueSize + queueBack - queueFront) % queueSize;
	}
	T& frontELement()
	{
		return element[(queueFront + 1) % queueSize];
	}
	T& backElement()
	{
		return element[queueBack];
	}
	int getback()
	{
		return queueBack;
	}
	void output();    //输出函数
private:
	int queueFront = 0;     //循环队列的头
	int queueBack = 0;       //循环队列的尾
	int queueSize;            //队列的大小
	T* element;          //队列数组
};
template<class T>
arrayQueue<T>::arrayQueue(int initalSize)
{
	queueSize = initalSize;
	element = new T[queueSize];
}
template<class T>
void arrayQueue<T>::push(const T& theElement)
{
	if (queueFront == (queueBack + 1) % queueSize)
	{
		if (queueBack % queueSize < (queueFront + 1) % queueSize)
		{
			int front = (queueFront + 1) % queueSize;
			T* newElement = new T[queueSize * 2];
			copy(element + front, element + queueSize, newElement - (queueSize - front));    // 4 * 1 2 3    4 * 1 2 3 * * * * *    4 * * * * * * 1 2 3
			copy(element, element + queueBack + 1, newElement);
			delete[]element;
			queueSize *= 2;
			element = newElement;
		}
		else
		{
			T* newElement = new T[queueSize * 2];                                    // * 1 2 3 4    * 1 2 3 4 * * * * *
			for (int i = 0; i < queueSize; i++)
			{
				newElement[i] = element[i];
			}
			delete[] element;
			queueSize *= 2;
			element = newElement;
		}
	}
	queueBack = (queueBack + 1) % queueSize;
	element[queueBack] = theElement;
}
template<class T>
void arrayQueue<T>::pop()
{
	queueFront = (queueFront + 1) % queueSize;
	element[queueFront].~T();
}
template<class T>
void arrayQueue<T>::output()
{
	if (queueFront < queueBack)
	{
		for (int i = queueFront + 1; i <= queueBack; i++)
		{
			cout << element[i] << " ";
		}
		cout << endl;
	}
	if (queueFront > queueBack)
	{
		for (int i = queueFront + 1; i < queueSize; i++)
		{
			cout << element[i] << " ";
		}
		for (int i = 0; i < queueBack; i++)
		{
			cout << element[i] << " ";
		}
	}
	cout << endl;
}
int main()
{
		int n;   //卡片个数
		cin >> n;
		arrayQueue<int> q(n);
		for (int i = 0; i < n; i++)
		{
			q.push(i + 1);
		}
		while (q.Size() != 1)
		{
			q.pop();
			q.push(q.frontELement());
			q.pop();
			//q.output();
		}
		cout << q.backElement() << endl;
	return 0;
}