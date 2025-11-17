#include<iostream>
#include<iomanip>
using namespace std;
template<class T>
class arraystack
{
public:
	arraystack(int initialCapocity = 10);   //构造函数，初始栈的大小为10
	~arraystack() { delete [] element; }       //析构函数
	void push(const T& theElement);               //往栈顶压入元素
	void pop();                             //栈的删除函数
	bool if_empty()
	{
		if (stackTop == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	T& top()
	{
		if (stackTop == -1)
		{
			exit(2);
		}
		return element[stackTop];
	}
private:
	int stackTop;       //当前栈顶
	int size = 10;     //栈的大小
	T* element;   // 元素数组
};
template<class T>
arraystack<T>::arraystack(int initialCapocity)
{
	size = initialCapocity;
	element = new T[size];
	stackTop = -1;
}
template<class T>
void arraystack<T>::push(const T& theElement)                 //向栈顶压入元素
{
	
	if (stackTop == size - 1)              //栈元素已满
	{
		
		T* newElement = new T[size*2];
		for (int i = 0; i < size; i++)
		{
			newElement[i] = element[i];
		}
		size = size * 2;
		delete element;
		element = newElement;
		
	}
	
	element[++stackTop] = theElement;
	//cout << "pushing! " << stackTop << " " <<element[stackTop] << endl;
}
template<class T>
void arraystack<T>::pop()
{
	if (stackTop == -1)
	{
		exit(1);	
	}
	element[stackTop--].~T();    //T的析构函数a
}
void calculate(arraystack<double>& array, arraystack<char>& c)
{
	if (c.top() == '(')
	{
		return;
	}
	double a, b;
	a = array.top();
	array.pop();
	b = array.top();
	array.pop();
	//将数字栈的两个数字弹出，并且用运算符栈的首个字符弹出，进行计算，并且将计算的结果重新压入数字栈中
	switch (c.top())     
	{
	case '+':
	{
		double sum = a + b;
		array.push((a+b));
		break;
	}
	case'-':
	{
		double subtraction = b - a;
		array.push(subtraction);
		break;
	}
	case'*':
	{
		double mul = a * b;
		array.push(mul);
		break;
	}
	case'/':
	{
		double division = b / a;
		array.push(division);
		break;
	}
	default:
		break;
	}
	c.pop();                              //运算符运算结束弹出栈
}
void compute(char* operate, int Length)      //将字符串拆解成数字和计算字符      
{
	//cout << "the equation is calculating!" << endl;
	bool minus = false;                        //判断是否为负数
	arraystack<double> a(Length);
	arraystack<char> c(Length);
	//cout << "here" << endl;
	for (int i = 0; i < Length; i++)
	{
		//cout << "index_here" << endl;
		if (operate[i] >= '0' && operate[i] <= '9')          //读到的为数字
		{
			double value = operate[i] - '0';
			while (operate[i + 1] >= '0' && operate[i + 1] <= '9')
			{
				value = 10 * value + (operate[i + 1] - '0');
				i++;
			}
			if (minus)
			{
				value = -value;
				minus = false;
			}
			a.push(value);
		}
		else              //读到的为字符
		{
			if ((i == 0 || operate[i - 1] == '(') && operate[i] == '-')  //负数开头或者括号内的复数的运算
			{
				minus = true;
				continue;
			}
			if (operate[i] == '-' || operate[i] == '+')
			{
				//cout << "char_here" << endl;
				if (c.if_empty() || c.top() == '(')
				{
					c.push(operate[i]);
				}
				else
				{
					calculate(a, c);            //遇到运算符就去运算
					if (!c.if_empty() && c.top() != '(')
					{
						calculate(a, c);        //继续运算若没碰到括号
					}
					c.push(operate[i]);
				}
			}
			if (operate[i] == '/' || operate[i] == '*')
			{
				if (c.if_empty() || c.top() == '(')
				{
					c.push(operate[i]);
				}
				else
				{
					if (c.top()=='+'||c.top()=='-')
					{
						c.push(operate[i]);                    //因为乘法运算级别高于加法，先把乘除压进栈
					}
					else
					{
						if (c.top() == '*' || c.top() == '/')
						{
							calculate(a, c);                      //如果是同级运算，即计算后压入
							c.push(operate[i]);
						}
					}
				}
			}
			if (operate[i] == '(')
			{
				c.push(operate[i]);           //左括号直接入栈
			}
			if (operate[i] == ')')                       //遇到右括号，对括号内进行运算直到运算到左括号
			{
				while (c.top() != '(')
				{
					calculate(a, c);
				}
				c.pop();                    //左括号出栈
			}
		}
		if (operate[i] == NULL)
		{
			break;
		}
	}
	for (; !c.if_empty();)
	{
		calculate(a, c);                            //计算剩余项
	}
	cout << setprecision(2) <<fixed<< a.top() << endl;
}
int main()
{
	//cout << "Stack is constucting!" << endl;
	int n;
    cin >> n;
	/*
	string operate;
	for (int i = 0; i < n; i++)
	{
		cin >> operate;
		int size = operate.size();
		//cout << size << endl;
		compute(operate, size);
	}
	*/
	for (int i = 0; i < n; i++)
	{
		char a[2000];
		cin >> a;
		compute(a, 2000);
	}
	
	return 0;
}