#include<iostream>
#include<vector>
using namespace std;
struct matrixTerm    // 定义矩阵类
{
	int row = 0;        //矩阵的行
	int col = 0;         //矩阵的列
	int value = 0;       //矩阵元素
	matrixTerm& operator = (matrixTerm& a)
	{
		row = a.row;
		col = a.col;
		value = a.value;
		return* this;
	}    // 重载函数方便后面赋值，简化代码
};
class sparse_matrix          //稀疏矩阵类
{
public:
	sparse_matrix& operator = (sparse_matrix &a);  //重载 = 方便后面的赋值操作
	void addElements(int &n);      //添加元素的函数  // n为元素个数
	void inputElements(int r, int c, int v);
	sparse_matrix(int r, int c);             //构造函数
	~sparse_matrix() { delete[] element; }   //析构函数
	void reset(int r, int c);                //重置函数
	void multiply(sparse_matrix& a);         //矩阵乘法
	void add(sparse_matrix& Q);              //矩阵加法
	void transpose();                        //转置函数
	void output();                           //输出函数
private:
	int rows = 0,
		cols = 0,
		Terms = 0;                            //矩阵非零元素个数
	matrixTerm* element;                       //  非0项表
};
sparse_matrix& sparse_matrix::operator=(sparse_matrix& a)                     //重载 = 方便后面的赋值操作
{
	rows = a.rows;
	cols = a.cols;
	Terms = a.Terms;
	for (int i = 0; i < a.Terms; i++)
	{
		element[i].value = a.element[i].value;
		element[i].col = a.element[i].col;
		element[i].row = a.element[i].row;

	}
	return *this;
}
void sparse_matrix::addElements(int &n)
{
	int theCol, theRow, theValue;
	for (int i = 0; i < n; i++)
	{
		cin >> theCol >> theRow >> theValue;
		element[i].col = theCol;
		element[i].row = theRow;
		element[i].value = theValue;
	}
	this->Terms = n;
}
void sparse_matrix::inputElements(int r, int c, int v)
{
	element[Terms].col = c;
	element[Terms].row = r;
	element[Terms].value = v;
	Terms++;
}
sparse_matrix::sparse_matrix(int r, int c)
{
	rows = r;
	cols = c;
	element = new matrixTerm[240000];
	//element = new matrixTerm[rows * cols];
}
void sparse_matrix::reset(int r, int c)
{
	rows = r;
	cols = c;
	Terms = 0;
	int index = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int input_element;
			cin >> input_element;
			if (input_element != 0)
			{
				element[index].row = i + 1;
				element[index].col = j + 1;
				element[index].value = input_element;
				index++;
				Terms++;
			}
		}
	}
}
void sparse_matrix::multiply(sparse_matrix& a)
{
	
	if (cols != a.rows)
	{
		*this = a;
		cout << -1 << endl;
		return;
	}
	else
	{
		sparse_matrix result(rows, a.cols);    ///储存乘法结果的矩阵
		result.Terms = 0;                         //设置初始结果矩阵的初始大小
		int result_index = 0;                     //用来标记结果矩阵的索引

		//与矩阵的转置求同存异，获得矩阵的每“行”的元素个数，以及每行第一个非0元素在element中的索引
		int* row_number = new int[rows + 1];  //储存各行非零元素的个数
		int* row_first = new int[rows + 1];   //每行第一个非0元素在element中的索引

		//初始化上面数组
		for (int i = 0; i <= rows; i++)
		{
			row_number[i] = 0;
		}
		for (int i = 0; i <= rows; i++)
		{
			row_first[i] = -1;          //如果第i行没有元素默认为-1；
		}
		
		//赋值上面数组
		for (int i = 0; i < Terms; i++)
		{
			row_number[element[i].row]++;
		}
		row_first[1] = 0;        //第一行的第一个元素所对应的第一个非0元素的索引必为0；
		for (int i = 2; i <= rows; i++)
		{
			row_first[i] = row_first[i - 1] + row_number[i - 1];
		}

		//储存累加结果的数组，数组大小为 a.cols + 1 ,应为行数不能为0
		int* sum = new int[a.cols + 1];
		for (int i = 0; i <= a.cols; i++)
		{
			sum[i] = 0;                      //初始化累加结果
		}
		
		//优化代码，减少每次遍历右边数组的次数
		// 记录右边矩阵每列的值
		int* right_colNumber = new int[a.cols + 1];        //储存a（右边矩阵）的每一列非零元素的值的个数
		for (int i = 0; i <= a.cols; i++)
		{
			right_colNumber[i] = 0;                         //初始化
		}
		for (int i = 0; i < a.Terms; i++)
		{
			right_colNumber[a.element[i].col]++;
		}

		int* right_colFirst = new int[a.cols + 1];          //储存a（右边矩阵）的每一列对应的索引
		for (int i = 0; i <= a.cols; i++)
		{
			right_colFirst[i] = 0;                         //初始化
		}
		right_colFirst[1] = 0;
		for (int i = 2; i <= a.cols; i++)
		{
			right_colFirst[i] = right_colFirst[i - 1] + right_colNumber[i - 1];
		}

		//开始乘法运算
		for (int i = 1; i <= rows; i++)          //遍历前面矩阵每一行
		{  
			if (row_first[i] != -1)             //当哪一行不为0是进行乘法
			{
				for (int k = 1; k <= row_number[i]; k++)    //遍历每一行不为0的元素
				{
					matrixTerm& rowElement = element[row_first[i]++];

					for (int j = right_colFirst[rowElement.col]; j < right_colFirst[rowElement.col] + right_colNumber[rowElement.col]; j++)              
					{//循环的精准定位——进准定位到所符合要求的元素，即 right_colFirst[rowElement.col] 到 right_colFirst[rowElement.col] + right_colNumber[rowElement.col];之间的元素的行的索引都是rowElement.col
						matrixTerm& colElement = a.element[j];
						sum[colElement.col] += rowElement.value * colElement.value;
					}
					/*
					for (int j =0; j < a.Terms; j++)                              //对于左边矩阵的每一行的元素，遍历一遍右边的矩阵 (这里导致运算超时了)，每次遍历一次矩阵太费时间
					{
						int mutiplyed_number = 0;
						matrixTerm& colElement = a.element[j];
						if (rowElement.row == i && rowElement.col == colElement.row)           //确定要做乘法的位置：确定在第i行，而且左边元素的列索引等于右边的行索引
						{
							sum[colElement.col] += rowElement.value * colElement.value;
							mutiplyed_number++; 
						}
						if (mutiplyed_number == right_colNumber[i])
						{
							break;
						}
					}
					*/
				}
				//得到了每一行累加的结果，接下来存入result中
				for (int k = 1; k <= a.cols; k++)
				{
					if (sum[k] != 0)          //累加的结果不等于0存入结果矩阵
					{
						result.element[result_index].row = i;            //左边矩阵的第i行
						result.element[result_index].col = k;             //右边矩阵所对应的第k列
						result.element[result_index].value = sum[k];
						result.Terms++;
						result_index++;
					}
				}
				//初始化累加数组
				for (int k = 1; k <= a.cols; k++)
				{
					sum[k] = 0;
				}
			}
		}
		*this = result;
	}
}
void sparse_matrix::add(sparse_matrix& Q)   //矩阵加法
{
	//检验合法性
	if (rows != Q.rows || cols != Q.cols)
	{
		*this = Q;                 //P + Q, P不合法，将Q赋值给P
		cout << -1 << endl;
		return;
	}
	//设置结果矩阵的特征
	sparse_matrix result(rows, cols);
	int result_size = 0;

	//定义迭代器(利用整形数据做简单的迭代器)   //后期代码完善的时候可以尝试用容器 : vector
	int it = 0;
	int iQ = 0;
	int itEnd = Terms;
	int iQEnd = Q.Terms;

	//遍历*this和Q，把相关的项相加
	while (it != itEnd && iQ != iQEnd)
	{ 
		//行主索引加上列数
		int tIndex = element[it].row * cols + element[it].col;
		int QIndex = Q.element[iQ].row * cols + Q.element[iQ].col;
		if (tIndex < QIndex)
		{
			//cout << "tIndex < QIndex" << endl;
			result.element[result_size++] = element[it];
			//cout << result.element[result_size - 1].row << " " << result.element[result_size - 1].col << " " << result.element[result_size - 1].value << endl;
			it++;
		}
		else
		{
			if (tIndex == QIndex)
			{//在同一位置
				if (element[it].value + Q.element[iQ].value != 0)
				{//当且仅当和不为0是插入
					//cout << "tIndex == QIndex" << endl;
					//cout << element[it].row << " " << element[it].row << " " << element[it].value << endl;
					matrixTerm myTerm;
					myTerm.col = element[it].col;
					myTerm.row = element[it].row;
					myTerm.value = element[it].value + Q.element[iQ].value;
					result.element[result_size++] = myTerm;
					//cout << result.element[result_size - 1].row << " " << result.element[result_size - 1].col << " " << result.element[result_size - 1].value << endl;
					/*
					result.element[result_size].col = element[it].col;
					result.element[result_size].row = element[it].row;
					result.element[result_size].value = element[it].value + Q.element[iQ].value;
					result_size++;
					*/
				}
				it++;
				iQ++;
			}
			else
			{
				//cout << "tIndex > QIndex" << endl;
				result.element[result_size++] = Q.element[iQ];
				//cout << result.element[result_size - 1].row << " " << result.element[result_size - 1].col << " " << result.element[result_size - 1].value << endl;
				iQ++;
			}
		}
	}
	//复制剩余项
	for (; it != itEnd; it++)
	{
		result.element[result_size++] = element[it];
		//cout << result.element[result_size - 1].row << " " << result.element[result_size - 1].col << " " << result.element[result_size - 1].value << endl;
	}
	for (; iQ != iQEnd; iQ++)
	{
		result.element[result_size++] = Q.element[iQ];
		//cout << result.element[result_size - 1].row << " " << result.element[result_size - 1].col << " " << result.element[result_size - 1].value << endl;
	}
	result.Terms = result_size;
	*this = result;
}
void sparse_matrix::transpose()
{
	sparse_matrix b(cols, rows);
	b.Terms = Terms;
	b.cols = rows;
	b.rows = cols;
	int* colSize = new int[cols + 1]; // 第i列的非0元素个数
	int* rowNext = new int[cols + 1]; // 第i行首个非0元素在b中的索引
	// 初始化
	for (int i = 1; i <= cols; i++)
	{
		colSize[i] = 0;
	}
	for (int i = 0; i < Terms; i++)
	{
		colSize[element[i].col]++;
	}
	/*
	for (int i = 1; i <= cols; i++)
	{
		cout << colSize[i] << " ";
	}
	cout << endl;
	*/
	// 寻找b中每一行的起始点
	rowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
	{
		rowNext[i] = rowNext[i - 1] + colSize[i - 1];
	}
	/*
	for (int i = 1; i <= cols; i++)
	{
		cout << rowNext[i] << " ";
	}
	cout << endl;
	*/
	// 实施从*this到b的转置复制
	for (int i = 0; i < Terms; i++)
	{
		int j = rowNext[element[i].col];
		rowNext[element[i].col]++;
		b.element[j].row = element[i].col;
		b.element[j].col = element[i].row;
		b.element[j].value = element[i].value;
	}
	//b.output();
	*this = b;                  //因为我没有重载“ = ”符号，复制的时候出错
}
void sparse_matrix::output()       // 输出函数
{
	int number = 0;
	cout << rows << " " << cols << endl;   //输出行数和列数
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (number < Terms  && element[number].row == i + 1 && element[number].col == j + 1)
			{
				cout << element[number].value << " ";
				number++;
			}
			else
			{
				cout << 0 << " ";
			}
		}
		cout << endl;
	}
}
int main()
{
	sparse_matrix x(0, 0);    //构造稀疏矩阵对象
	int w;             //操作数
	cin >> w;
	int decision;       //操作模式
	int row, col, t;   //行列，和矩阵中非0元素的个数
	for (int i = 0; i < w; i++)
	{
		cin >> decision;
		switch (decision)
		{
		case 1:
		{
			//reset matrix
			cin >> row >> col;
			x.reset(row, col);
			break;
		}
		case 2:
		{
			//multiply
			cin >> row >> col >> t;
			sparse_matrix mul(row, col);
			for (int i = 0; i < t; i++)
			{
				int r, c, v;
				cin >> r >> c >> v;
				mul.inputElements(r, c, v);
			}
			x.multiply(mul);
			//cout << " multiply matrix " << endl;
			break;
		}
		case 3:
		{
			//add
			cin >> row >> col >> t;
			//由于通过行列数和元素大小赋值，无法通过对象访问私有成员，所以还得来一个函数
			sparse_matrix add_matrix(row, col);   
			//add_matrix.addElements(t);
			for (int i = 0; i < t; i++)
			{
				int r, c, v;
				cin >> r >> c >> v;
				add_matrix.inputElements(r, c, v);
			}
			//add_matrix.output();
			x.add(add_matrix);
			break;
		}
		case 4:
		{
			x.output();
			break;
		}
		case 5:
			//transpose matrix
			x.transpose();
		default:
			break;
		}
	}
	return 0;
}
/*
7
1
3 4
1 0 0 2
0 3 0 4
5 0 0 6

3
3 4 6
1 2 1
1 4 2
2 1 3
2 3 4
3 1 5
3 3 6
*/