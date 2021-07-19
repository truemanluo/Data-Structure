#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class Sort
{
private:
    vector<int> data;

    int partition(int start, int end) {
        int pivot = start;
        int i = start, j = end;
        while (i < j) {
            while (i < j && data[j] >= data[pivot]) {
                --j;
            }
            while (i < j && data[i] <= data[pivot]) {
                ++i;
            }
            if (i >= j) break;
            swap(data[i], data[j]); // 此处交换完后不能++i,--j, 否则,比如[7, 8, 6, 4] --> [7, 4, 6, 8]的情况就会退出
        }
        swap(data[j], data[pivot]);
        return j;
    }

    void quick_sort_(int start, int end) {
        if (start >= end) return;
        int pivot = partition(start, end);
        quick_sort_(start, pivot-1);
        quick_sort_(pivot+1, end);
    }

    // 归并
    void merge_sort_(vector<int> &aux, int lo, int hi) {
        if (lo >= hi) return;
        int mid = lo + (hi - lo)/2;
        merge_sort_(aux, lo, mid);
        merge_sort_(aux, mid+1, hi);
        merge_arr(aux, lo, mid, hi); // 左右两半有序
    }

    void merge_arr(vector<int> &aux, int lo, int mid, int hi) {
        int left = lo, right = mid+1;
        for (int k = lo; k <= hi; ++k) {
            aux[k] = data[k];
        }
        for (int k = lo; k <= hi; ++k) {
            if (left > mid) {
                data[k] = aux[right++];
            }
            else if (right > hi) {
                data[k] = aux[left++];
            }
            else if (aux[left] < aux[right]) {
                data[k] = aux[left++];
            }
            else {
                data[k] = aux[right++];
            }
        }
        
    }

    // 堆的下沉(sink)
    void sink(int root, int length) {
        int tmp = data[root];
        // 看根节点与其子节点是否满足条件
        for (int i = 2*root+1; i < length; i = 2*i+1) {
            // 2*root+1是左节点，需要看右节点是否大于左节点
            if (i < length-1 && data[i+1] > data[i]) {
                ++i;
            }
            if (data[i] > tmp) {
                data[root] = data[i];
                root = i;
            }
            else {
                break;
            }
        }
        data[root] = tmp;
    }


public:
    Sort(int sz, int range);
    ~Sort() {};

    void print(string description) {
        cout << description << endl;
        for (int i = 0; i < data.size(); ++i) {
            cout << data[i];
            if (i == data.size()-1) continue;
            cout << ", ";
        }
        cout << endl;
    }


    // 冒泡排序
    void bubble_sort() {
        print("Before sort: ");
        for (int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < data.size()-i-1; ++j) {
                if (data[j] > data[j+1]) {
                    swap(data[j], data[j+1]);
                }
            }
        }
        print("After sort: ");
    }

    // 选择排序
    void selection_sort() {
        print("Before sort: ");
        for (int i = 0; i < data.size(); ++i) {
            int mindex = i;
            for (int j = i+1; j < data.size(); ++j) {
                if (data[j] < data[mindex]) {
                    mindex = j;
                }
            }
            swap(data[i], data[mindex]);
        }
        print("After sort: ");
    }

    // 插入排序
    void insertion_sort() {
        print("Before sort: ");
        for (int i = 1; i < data.size(); ++i) {
            int tmp = data[i];
            int j = i - 1;
            for (; j >= 0 && data[j] > tmp; --j) {
                data[j+1] = data[j];
            }
            data[j+1] = tmp;
        }
        print("After sort: ");
    }

    // 希尔排序
    void shell_sort() {
        int step = 1, n = data.size();
        while (step < n / 3) {
            step = step*3 + 1;
        }
        print("Before sort: ");
        while (step > 0) {
            for (int i = step; i < data.size(); ++i) {
                int tmp = data[i];
                int j = i - step;
                for (; j >= 0 && data[j] > tmp; --j) {
                    data[j+step] = data[j];
                }
                data[j+step] = tmp;
            }
            step /= 3;
        }
        print("After sort: ");
    }

    // 归并排序
    void merge_sort() {
        print("Before sort: ");
        // vector<int> data_copy = data;
        vector<int> aux(data.size()); // 临时数组
        int lo = 0, hi = data.size()-1;
        merge_sort_(aux, lo, hi);
        // std::sort(data_copy.begin(), data_copy.end());
        // cout << "sorted right? " << (data_copy == data) << endl;
        print("After sort: ");
    }

    void merge_sort_BU() { // 自底向上
        print("Before sort: ");
        int n = data.size();
        // vector<int> data_copy = data;
        vector<int> aux(data.size()); // 临时数组
        for (int sz = 1; sz < n; sz *= 2) {
            for (int i = 0; i < n - sz; i += 2*sz)
                merge_arr(aux, i, i+sz-1, min(i+2*sz-1, n-1));
        }
        print("After sort: ");
    }

    // 快速排序
    void quick_sort() {
        // print("Before sort: ");
        vector<int> data_copy = data;
        int start = 0, end = data.size() - 1;
        quick_sort_(start, end);
        std::sort(data_copy.begin(), data_copy.end());
        cout << "sorted right? " << (data_copy == data) << endl;
        // print("After sort: ");
    }

    // 堆排序
    void heap_sort() {
        print("Before sort: ");
        // vector<int> data_copy = data;

        int n = data.size();
        // 新建堆
        for (int i = n/2-1; i >= 0; --i) {
            sink(i, n);
        }

        // 调整堆
        for (int i = 0; i < n; ++i) {
            swap(data[0], data[n-i-1]);
            sink(0, n-i-1);
        }

        // std::sort(data_copy.begin(), data_copy.end());
        // cout << "sorted right? " << (data_copy == data) << endl;
        print("After sort: ");

    }

    // 计数排序
    void counting_sort() {
        print("Before sort: ");
        int max_len = *std::max_element(data.begin(), data.end()) + 1;
        vector<int> index(max_len, 0);
        // 统计每个数字出现的次数
        for (auto d : data) {
            ++index[d];
        }
        int start = 0;
        for (int i = 0; i < index.size(); ++i) {
            while (index[i] > 0)
            {
                data[start++] = i;
                --index[i]; 
            }
        }
        print("After sort: ");
    }

    // 桶排序

    // 基数排序


};

Sort::Sort(int sz, int range)
{
    for (int i = 0; i < sz; ++i) {
        data.push_back(rand()%range);
    }
}


int main(int argc, char *argv[])
{
    Sort st(std::stoi(argv[1]), std::stoi(argv[2]));
    st.heap_sort();
}


