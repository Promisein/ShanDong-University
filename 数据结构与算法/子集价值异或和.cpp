#include<iostream>
using namespace std;
int XOR_sum = 0;   //异或和
int subset(int* binary, int* input, int index, int n)  //b为输入的数组,a为递归的二进制数，n为元素个数
{
	if (index == n)
	{
		int sum_value = 0;
		int count = 1;
		for (int i = 0; i < n; i++)
		{
			if (binary[i] == 1)
			{
				sum_value += count * input[i];          //每一个子集的价值
				count++;
			}
		}
		XOR_sum ^= sum_value;                  //异或和
	}
	else
	{
		binary[index] = 1;
		subset(binary, input, index + 1, n);
		binary[index] = 0;
		subset(binary, input, index + 1, n);
	}//递归函数求出所有子集
	return XOR_sum;
}
int main()
{
	int n;
	cin >> n;
	int binary[100];    //二进制数组的保存数组
	int input[20];       // 输入的数组
	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
	}
	cout << subset(binary, input, 0, n) << endl;
	return 0;
}
