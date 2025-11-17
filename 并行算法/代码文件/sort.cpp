
#include <assert.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;


int thrd_num = 16;
int bitnum = 256;
// int bits[5] = {0, 10, 20, 30, 40};
int bits[12] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40};
// int bits[6] = {0, 8, 16, 24, 32, 40};
inline int get_bit(int x, int bit) { return (x >> bits[bit]) & (bitnum - 1); }

void rscan(int* data, int size) {
    if (size == 1) return;
    int twoSum[size / 2];
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 0; i < size / 2; i++) {
        twoSum[i] = data[i * 2] + data[2 * i + 1];
    }
    rscan(twoSum, size / 2);
#pragma omp parallel for num_threads(thrd_num)
    for (int i = 1; i < size; i += 2) {
        data[i] = twoSum[i / 2];
        if (i + 1 < size) {
            data[i + 1] = twoSum[(i + 1) / 2 - 1] + data[i + 1];
        }
    }
}

// 自定义 memset 函数
void my_memset(int* arr, int value, size_t size) {
#pragma omp parallel for num_threads(thrd_num)
    for (size_t i = 0; i < size; i++) {
        arr[i] = value;
    }
}

// 自定义 memcpy 函数
void my_memcpy(int* dest, const int* src, size_t size) {
#pragma omp parallel for num_threads(thrd_num)
    for (size_t i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

void bit_sort(vector<int>& data) {
    int cut = int(log2(10 * SIZE)) / 4 + 1;
    int cnt[bitnum];

    int* bucket = (int*)malloc(sizeof(int) * SIZE);
    for (int i = 0; i < cut; i++) {
        my_memset(cnt, 0, bitnum);

        for (int j = 0; j < data.size(); j++) {
            cnt[get_bit(data[j], i)]++;
        }

        rscan(&cnt[0], bitnum);

        for (int j = SIZE - 1; j >= 0; j--) {
            int bit = get_bit(data[j], i);
            bucket[cnt[bit] - 1] = data[j];
            cnt[bit]--;
        }
        my_memcpy(&data[0], bucket, SIZE);
    }
    free(bucket);
}

int main() {
    vector<int> data(SIZE);

    srand(SIZE);
    for (int i = 0; i < SIZE; i++) data[i] = rand() % (SIZE * 10);

    double t = omp_get_wtime();
    bit_sort(data);
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE - 1; i++) assert(data[i] <= data[i + 1]);
}
