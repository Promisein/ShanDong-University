#include<iostream>
using namespace std;
template<class T>
class mySort
{public:
	mySort(int n);              //构造函数
	~mySort() {};               //析构函数
	void swap(T& a, T& b);       //交换函数
	void ranking_sort(T* a, T* r, int n);           //名次排序
	void selection_sort(T* a, int n);               //选择排序
	void insertion_sort(T* a, int n);               //插入排序
	void bubble_sort(T* a, int n);                  //冒泡交换排序
private:
	int n;                      //需要排序的数的个数
};
template<class T>
mySort<T>::mySort(int n)
{
	if (n >= 0)
	{
		this->n = n;
	}
	else
	{
		this->n = 0;
	}
}
template<class T>
void mySort<T>::swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}
template<class T>
//名次排序 
void mySort<T>::ranking_sort(T* a, T*r, int n)
{
	for (int i = 0; i < n; i++)
	{
		r[i] = 0;           
	}//初始化名次数组
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (a[i] >= a[j])
			{
				r[i]++;
			}
			else
			{
				r[j]++;
			}
		}
	}//计算名次，将名次存入名次数组
	T* mid = new T[n];             
	for (int i = 0; i < n; i++)
	{
		mid[r[i]] = a[i];          //利用辅助数组，按照对应r数组中的名次暂时存储到mid辅助数组中
	}
	for (int i = 0; i < n; i++)
	{
		a[i] = mid[i];            //利用辅助数组的值将a数组的值替换掉
	}
	delete[] mid;
}
template<class T>
//及时停止的选择排序
void mySort<T>::selection_sort(T* a, int n)
{
	bool judge = false;    //判断是否排序完整
	for (int i = n; i > 1 && !judge; i--)
	{
		int max = 0;       //最大数所在的坐标
		judge = true;
		for (int j = 1; j < i; j++)
		{
			if (a[j] >= a[max])
			{
				max = j;
			}
			else
			{
				judge = false;     //只要有一次执行，说明排序不对
			}
		}
		mySort<T>::swap(a[max], a[i - 1]);
	}
}
template<class T>
//插入排序
void mySort<T>::insertion_sort(T* a, int n)
{
	//将下标为1到n-1元素逐个插入到已经排序序列当中的位置
	for (int i = 1; i < n; i++)          
	{
		//从数组a的末尾向a[0]寻找比较元素，找到合适的位置插入a[i]
		int j = i;
		T temp = a[i];
		while (j > 0 && temp < a[j - 1])
		{
			a[j] = a[j - 1];              //元素逐个后移，找到插入位置即可插入对应的元素
			j--;
		}
		//位置找到，插入元素
		a[j] = temp;
	}
}
template<class T>
//冒泡交换排序
void mySort<T>::bubble_sort(T* a, int n)
{
	bool judge = false;            //检验是否发生交换，若发生交换及时停止排序
	for (int i = 0; i < n - 1; i++)
	{
		if (judge)
		{
			break;
		}
		judge = true;
		for (int j = 0; j < n - i - 1; j++)
		{
			if (a[j] < a[j + 1])
			{
				mySort<T>::swap(a[j], a[j + 1]);
				judge = false;
			}
		}
	}
}
int main()
{
	int n;
	cin >> n;
	mySort<int> s(n);           //定义mySort<int>类的对象，并且初始化数组大小
	int* array = new int[n] ();
	//int* rank = new int[n]();   //名次排序中的名次数组
	for (int i = 0; i < n; i++)
	{
		cin >> array[i];
	}
	//s.ranking_sort(array, rank, n);      //名次排序
	//s.selection_sort(array, n);          //选择排序
	//s.insertion_sort(array, n);          //插入排序
	s.bubble_sort(array, n);               // 冒泡排序
	for (int i = 0; i < n; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	delete [] array;
	//delete [] rank;
	return 0;
}