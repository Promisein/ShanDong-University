// student name:贺若桓
// id number:202100130222

#include <omp.h>
#include <openacc.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <iostream>
using namespace std;

// add your codes begin

// 获取数组中的最大值
int getMax(vector<int>& data) {
    int maxVal = data[0];
    for (int i = 1; i < data.size(); i++) {
        if (data[i] > maxVal) {
            maxVal = data[i];
        }
    }
    return maxVal;
}

// 基数排序的计数排序子函数
void countSort(vector<int>& data, int exp) {
    int n = data.size();
    vector<int> output(n);
    int count[10] = { 0 };

    // 计算每个桶中的元素个数
#pragma acc parallel loop present(data[0:n])
    for (int i = 0; i < n; i++) {
        count[(data[i] / exp) % 10]++;
    }

    // 计算位置索引
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 按照当前位数对数据进行排序
    for (int i = n - 1; i >= 0; i--) {
        output[count[(data[i] / exp) % 10] - 1] = data[i];
        count[(data[i] / exp) % 10]--;
    }

    // 复制临时数组到原数组
#pragma acc parallel loop present(data[0:n], output[0:n])
    for (int i = 0; i < n; i++) {
        data[i] = output[i];
    }
}

// 基数排序算法
void radixSort(vector<int>& data) {
    int maxVal = getMax(data);
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countSort(data, exp);
    }
}

// add your codes end

int main() {
    vector<int> data(SIZE);

    srand(SIZE);
    for (int i = 0; i < SIZE; i++) data[i] = rand() % (SIZE * 10);

    double t = omp_get_wtime();
    // add your codes begin
#pragma acc data copy(data[0:SIZE])
    {
        radixSort(data);
    }
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE - 1; i++) assert(data[i] <= data[i + 1]);

    return 0;
}
