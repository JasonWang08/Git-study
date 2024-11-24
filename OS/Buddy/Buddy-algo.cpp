#include <vector>
#include <map>
#include <cmath>
#include <iostream>
using namespace std;

void initialize(int sz);
void allocate(int sz);
void reclaim(std::pair<int, int> range);
// Size of vector of pairs
int length=0;

// Global vector of pairs to store address ranges available in free list
vector<pair<int, int>> free_list[100000];//存储可用内存块

// Map used as hash map to store the starting address as key
// and size of allocated segment key as value
map<int, int> mp;//已分配的内存块

int main()
{
    initialize(128);
    allocate(32);
    allocate(7);
    allocate(2);
    allocate(64);
    allocate(56);
    //Reclaiming memory
    cout << "Reclaim memory:\n";
    reclaim({0, 31});      // 释放大小为 32 的块
    reclaim({64, 127});    // 释放大小为 64 的块
    allocate(32);
    allocate(56);

    return 0;
}
//每个索引 i 对应大小为2的i次方的内存块。
void initialize(int sz)
{
    // Maximum number of powers of 2 possible
    int n = static_cast<int>(ceil(log(sz) / log(2)));//2的7次方,n=7
    length = n + 1;
    for (int i = 0; i <= n; i++) free_list[i].clear();
    // Initially whole block of specified size is available
    free_list[n].emplace_back(0, sz - 1);//free_list[7] = [(0, 127)]
}

void allocate(int sz)
{
    // Calculate index in free list to search for block if available
    int n = static_cast<int>(ceil(log(sz) / log(2)));//5

    // Block available
    if (!free_list[n].empty())
    {
        pair<int, int> temp = free_list[n][0];

        // Remove block from free list
        free_list[n].erase(free_list[n].begin());
        cout << "Memory from " << temp.first
             << " to " << temp.second << " allocated" << "\n";
        // map starting address with size to make deallocating easy
        mp[temp.first] = temp.second - temp.first + 1;
    }
    else
    {
        int i;
        for (i = n + 1; i < length; i++)//找到符合要求的内存
        {
            // Find block size greater than request
            if (!free_list[i].empty()) break;
        }
        // If no such block is found i.e., no memory block available
        if (i == length)//没有找到可用内存
        {
            cout << "Sorry, failed to allocate memory \n";
        }
        // If found
        else
        {
            pair<int, int> temp;
            temp = free_list[i][0];

            // Remove first block to split it into halves
            free_list[i].erase(free_list[i].begin());
            i--;

            for (; i >= n; i--)
            {
                // Divide block into two halves----原内存分裂为两半
                pair<int, int> pair1, pair2;
                pair1 = make_pair(temp.first,
                                  temp.first + (temp.second - temp.first) / 2);
                pair2 = make_pair(temp.first + (temp.second - temp.first + 1) / 2,
                                  temp.second);
                free_list[i].push_back(pair1);

                // Push them in free list
                free_list[i].push_back(pair2);
                temp = free_list[i][0];

                // Remove first free block to further split
                free_list[i].erase(free_list[i].begin());
            }
            cout << "Memory from " << temp.first
                 << " to " << temp.second << " allocated" << "\n";
            mp[temp.first] = temp.second -
                             temp.first + 1;
        }
    }
}

void reclaim(std::pair<int, int> range) {
    int size = range.second - range.first + 1;
    int n = static_cast<int>(ceil(log(size) / log(2)));

    // 从 map 中删除记录，确保记录管理同步
    if (mp.find(range.first) == mp.end()) {
        cout << "Error: Block at " << range.first << " not found in allocated memory.\n";
        return;
    }
    mp.erase(range.first);//删除记录

    // 合并伙伴内存块逻辑
    while (true) {
        bool merged = false;
        int buddy_address = range.first ^ (1 << n);  // 计算伙伴块的起始地址

        // 查找伙伴块是否在 free_list 中
        for (auto it = free_list[n].begin(); it != free_list[n].end(); ++it) {
            if (it->first == buddy_address) {
                // 找到伙伴块，进行合并
                range = make_pair(min(range.first, it->first),
                                  max(range.second, it->second));
                free_list[n].erase(it);  // 从当前 free_list 中移除伙伴块
                merged = true;
                n++;  // 合并后块大小翻倍
                break;
            }
        }

        // 如果未找到可合并的伙伴，停止合并
        if (!merged) break;
    }

    // 将最终的块插入对应的 free_list
    free_list[n].push_back(range);//存在伙伴块，合并后加入更高一层的free_list,不存在则直接加入当前free_list.
    cout << "Memory from " << range.first << " to " << range.second << " reclaimed.\n";
}
