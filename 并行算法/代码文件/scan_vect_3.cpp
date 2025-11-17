#include <omp.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <iostream>
using namespace std;

// int SIZE = 10000;
void MapReduceScan(vector<int> &data)
{
    int num = 2000;
    omp_set_num_threads(num);
    int block_size = data.size() / num;
    vector<int> map_sums(num, 0);
    vector<int> prefix_sums(num, 0);
    // map
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int start = tid * block_size;
        int end = (tid == num - 1) ? data.size() : start + block_size;
        int block_sum = 0;
        for (int i = start; i < end; i++)
        {
            block_sum += data[i];
        }
        map_sums[tid] = block_sum;
    }

    // reduce
    {
        for (int i = 1; i < prefix_sums.size(); i++)
        {
            prefix_sums[i] += prefix_sums[i - 1];
            prefix_sums[i] += map_sums[i - 1];
        }

        // for(auto i : prefix_sums) cout << i << endl;

        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            int start = tid * block_size;
            int end = (tid == num - 1) ? data.size() : start + block_size;
            for (int i = start + 1; i < end; i++)
            {
                data[i] += data[i - 1];
            }
            for (int i = start; i < end; i++)
            {
                data[i] += prefix_sums[tid];
            }
        }
        
    }
}
int main()
{
    vector<int> data(SIZE, 1);
    data[0] = 0;

    double t = omp_get_wtime();
    // add your codes begin
    MapReduceScan(data);
    // add your codes end
    t = omp_get_wtime() - t;
    printf("time %f %d\n", t, SIZE);

    for (int i = 0; i < SIZE; i++)
        assert(data[i] == i);
    cout << "success" << endl;
}
