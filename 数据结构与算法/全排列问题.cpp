#include<iostream>
using namespace std;
int sum_value = 0;                   //位运算或的和
void swap(int& a, int& b)    //交换函数
{
    int c = a;
    a = b;
    b = c;
}
int arragement(int* a, int index, int n)    //递归全排列
{
    if (index == n)
    {
        int value = 0;                       //value为全排列的价值
        for (int i = 0; i < n; i++)
        {
            value += (i + 1) ^ a[i];
        }
        sum_value |= value;
    }
    else
    {
        for (int i = index; i < n; i++)
        {
            swap(a[index], a[i]);
            arragement(a, index + 1, n);          //递归部分
            swap(a[index], a[i]);
        }
    }
    return sum_value;
}
int main()
{
    int n;   // 输入的元素个数
    cin >> n;
    int a[10];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << arragement(a, 0, n) << endl;
    return 0;
}