
#include <omp.h>
#include <openacc.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <iostream>

using namespace std;


// add your codes begin
#define NUM_THREAD 32
#define BITS_PER_PASS 8 
#define RADIX (1 << BITS_PER_PASS)
#define MASK (RADIX - 1)

void parallel_radix_sort(int *restrict data, int size) {
    int *restrict output = (int*) malloc(size * sizeof(int));
    int *restrict count = (int*) malloc(RADIX * sizeof(int));
    int *restrict prefix_sum = (int*) malloc(RADIX * sizeof(int));

    for (int shift = 0; shift < sizeof(int) * 8; shift += BITS_PER_PASS)
    {
        #pragma omp parallel for num_threads(NUM_THREAD)
        for (int i = 0; i < RADIX; i++) count[i] = 0;

        #pragma acc parallel loop gang num_workers(4) vector_length(128)
        for (int i = 0; i < size; i++)
        {
            int digit = (data[i] >> shift) & MASK;
           // #pragma acc atomic
            count[digit]++;
        }

        prefix_sum[0] = 0;
        #pragma acc parallel loop gang num_workers(4) vector_length(128)
        for (int i = 1; i < RADIX; i++)
        {
            prefix_sum[i] = prefix_sum[i - 1] + count[i - 1];
        }

        #pragma acc parallel loop gang num_workers(4) vector_length(128)
        for (int i = 0; i < size; i++)
        {
            int digit = (data[i] >> shift) & MASK;
            int pos = prefix_sum[digit]++;
            output[pos] = data[i];
        }
        
        #pragma acc parallel loop gang num_workers(4) vector_length(128)
        for (int i = 0; i < size; i++)
        {
            data[i] = output[i];
        }
    }

    free(output);
    free(count);
    free(prefix_sum);
}

// 串行基数排序
void serial_radix_sort(int *data, int size) {
    int *output = (int*) malloc(size * sizeof(int));
    int count[RADIX];

    for (int shift = 0; shift < sizeof(int) * 8; shift += BITS_PER_PASS) {
        for (int i = 0; i < RADIX; i++) count[i] = 0;

        for (int i = 0; i < size; i++) {
            int digit = (data[i] >> shift) & MASK;
            count[digit]++;
        }

        int prefix_sum = 0;
        for (int i = 0; i < RADIX; i++) {
            int temp = count[i];
            count[i] = prefix_sum;
            prefix_sum += temp;
        }

        for (int i = 0; i < size; i++) {
            int digit = (data[i] >> shift) & MASK;
            output[count[digit]++] = data[i];
        }

        for (int i = 0; i < size; i++) {
            data[i] = output[i];
        }
    }

    free(output);
}
// add your codes end

int main() {
    vector<int> data(SIZE);

    srand(SIZE);
    for (int i = 0; i < SIZE; i++) data[i] = rand() % (SIZE * 10);

    double t = omp_get_wtime();
    // add your codes begin
    if (SIZE <20000000) {
        // 使用串行基数排序
        serial_radix_sort(data.data(), SIZE);
    } else {
        // 使用并行基数排序
        int *data1 = (int*) malloc(SIZE * sizeof(int));

        #pragma omp parallel for num_threads(NUM_THREAD)
        for (int i = 0; i < SIZE; i++)
            data1[i] = data[i];

        #pragma acc data copy(data1[0:SIZE])
        {
           parallel_radix_sort(data1, SIZE);
        }

        #pragma omp parallel for num_threads(NUM_THREAD)
        for (int i = 0; i < SIZE; i++)
            data[i] = data1[i];

        free(data1);
    }
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE-1; i++) assert(data[i] <= data[i+1]);
}
