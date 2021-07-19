### 十大排序算法

#### 归并排序
> 原地归并: 先将`data`拷贝到`aux`辅助数组中，然后再将`aux`归并回`data`中
- 递归实现
  > 递归函数签名：`merge_sort_(vector<int> &aux, int lo, int hi);`
  > 
  > 归并函数签名：`merge_arr(vector<int> &aux, int lo, int mid, int hi)`
  
- 迭代实现
  - 两路归并：用二重循环实现，第一层循环控制归并数组的大小，第二层进行归并
  > Notes: 一个小细节，归并的时候取`i+2*sz-1`和`n-1`之间的较小值（处理数字大小为奇数的情况）`merge_arr(aux, i, i+sz-1, min(i+2*sz-1, n-1));`
#### 快速排序
#### 计数排序

#### 堆排序（基于优先队列实现）
> https://www.cnblogs.com/chengxiao/p/6129630.html
- C++调用示例: `CPP-API/prior_queue.cpp`
- 堆操作：
  - 下沉（sink）
  - 上浮（swim）

- 堆排序：
  - 构建堆：这一步的关键是找到第一个非叶子节点`i`，从`i->0`依次处理，使得以`i`为根的二叉树满足堆的定义，因此对每个节点的下沉操作需要一直进行，直到走到叶子节点为止。
  ```
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
  ```
  - 将堆顶元素与末尾元素进行交换 
