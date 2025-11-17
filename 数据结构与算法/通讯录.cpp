#include<iostream>
using namespace std;
class Student
{
public:
	~Student() {};
	void input_name(string &newname) { name = newname; }
	void input_phone(string &nphone) { telephone = nphone; }
	void input_grade(int &ngrade) { grade = ngrade; }
	void input_dorm(int &ndrom) { dorm = ndrom; }
	string get_name() { return name; }
	string get_phone() { return telephone; }
	int get_grade() { return grade; }
	int get_dorm() { return dorm; }
private:
	string name;        // 学生姓名
	string telephone;   //电话号码
	int grade = 0;          //班级
	int dorm = 0;           //宿舍号
};
template<class T>
void change_size(T*& a, int oldsize, int newsize)     //改变一个数组的长度
{
	if (newsize < 0)
	{
		throw "new size must be >=0";
	}
	T* temp = new T[newsize];          //新数组
	int number = min(oldsize, newsize);       //需要复制的元素个数
	copy(a, a + number, temp);            //copy(复制起点，复制终点，新的起点)
	delete[] a;                          //释放旧的空间
	a = temp;
}
class Linearlist:public Student
{
public:
	Linearlist(int n = 10);             //构造函数
	~Linearlist() { delete[] stu; }     //   析构函数，删除动态数组
	void insert(string& name, string& telephone, int& grade, int& dorm);      //插入函数
	void erase(string &name);           //删除函数
	void edit(string& name,int item);      //编辑函数，name为根据姓名,item为编辑项目
	bool search(string& name);           //查找函数，存在返回1，否则返回0
	int output(int& grade);               //输出一个班宿舍号的异或值
private:
	Student* stu;
	int size;          //数组大小
	int index;         //索引
};
Linearlist::Linearlist(int n)
{
	stu = new Student[n];         //初始化数组的大小为10
	size = n;               
	index = 0;
}
void Linearlist::insert(string& name, string& telephone, int& grade, int& dorm)
{
	if (index == size)
	{
		change_size(this->stu, this->size, size * 2);           //数组长度扩大到原来的两倍
		this->size = this->size * 2;
	}
	stu[index].input_name(name);
	stu[index].input_phone(telephone);
	stu[index].input_grade(grade);
	stu[index].input_dorm(dorm);
	index++;
}
void Linearlist::erase(string& name)
{
	int i = 0;
	for (i = 0; i < this->index && this->stu[i].get_name() != name; i++)
	{
		//遍历到要删除的元素对应的索引“i"
	}
	/*while (stu[i].get_name() != name && i < size)
	{
		i++;
	}*/
	copy(stu + i + 1, stu + index, stu + i); //copy(复制起点，复制终点，新的起点)
	stu[--index].~Student();       //调用析构函数
}
void Linearlist::edit(string& name, int item)
{
	int i = 0;
	for (i = 0; i < this->index && this->stu[i].get_name() != name; i++)
	{
		//遍历到要的姓名对应的索引“i"
	}
	//1.telephone
	//2.grade
	//3.drom
	if (item == 1)
	{
		string new_telephone;
		cin >> new_telephone;
		stu[i].input_phone(new_telephone);
	}
	if (item == 2)
	{
		int new_grade;
		cin >> new_grade;
		stu[i].input_grade(new_grade);
	}
	if (item == 3)
	{
		int new_drom;
		cin >> new_drom;
		stu[i].input_dorm(new_drom);
	}
}
bool Linearlist::search(string& name)
{
	int i = 0;
	for (i = 0; i < this->index && this->stu[i].get_name() != name; i++)
	{
		//遍历到要删除的元素对应的索引“i"
	}
	if (i >= index)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int Linearlist::output(int& grade)
{
	int sum = 0;
	for (int i = 0; i < index; i++)
	{
		if (stu[i].get_grade() == grade)
		{
			sum ^= stu[i].get_dorm();
		}
	}
	return sum;
}
int main()
{
	//0.插入    1.删除     2.编辑     3.查找    4.输出班级信息
	int n, mode;    // n为操作次数，mode为操作模式
	cin >> n;
	string name, telephone;
	int grade, dorm;
	Linearlist l;
	int* a = new int[n];     //输出格式：储存输出的数字的数组
	int index = 0;           //输出数组的索引
	for (int i = 0; i < n; i++)
	{
		cin >> mode;
		switch (mode)
		{
		case 0:
			cin >> name;
			cin >> telephone;
			cin >> grade;
			cin >> dorm;
			l.insert(name, telephone, grade, dorm);
			break;
		case 1:
			cin >> name;
			l.erase(name);
			break;
		case 2:
			int item;          //编辑项目： 1.telephone    2.grade     3.drom
			cin >> name;
			cin >> item;
			l.edit(name, item);
			break;
		case 3:
			cin >> name;
			a[index] = l.search(name);
			index++;
			break;
		case 4:
			cin >> grade;
			a[index] = l.output(grade);
			index++;
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < index; i++)
	{
		cout << a[i] << endl;
	}
	delete[] a;
	return 0;
}