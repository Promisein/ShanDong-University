#include<iostream>
using namespace std;
int main()
{
	int sum = 0;
	int input;
	for (int i = 0; i < 11; i++)
	{
		cin >> input;
		int a = input ^ i;
		cout << i << '^' << input << " = "<< "\t " << a << endl;
		sum += input ^ i;
	}
	cout << sum << endl;
	return 0;
}
//6863 35084 44199 11427 53377 34937 14116 5000 49692 70281 73704
//398675
/*
10 10
6863 35084 11427 53377 34937 14116 5000 49692 70281 73704
4 6863
1 2 44199
5
4 21466
1 6 11483
5
4 34937
5
4 6863
1 10 
*/
