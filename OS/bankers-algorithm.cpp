#include <iostream>
#include <vector>
using namespace std;

class BankerAlgorithm {
private:
    int n;  // 进程数
    int m;  // 资源类型数
    vector<vector<int>> max;        // 最大需求矩阵
    vector<vector<int>> allocation; // 已分配矩阵
    vector<vector<int>> need;      // 需求矩阵
    vector<int> available;         // 可用资源向量
    vector<bool> finish;           // 完成状态向量

public:
    BankerAlgorithm(int numProcesses, int numResources) : 
        n(numProcesses), 
        m(numResources),
        max(n, vector<int>(m)),
        allocation(n, vector<int>(m)),
        need(n, vector<int>(m)),
        available(m),
        finish(n, false) {}

    // 初始化系统资源数据
    void initialize() {
        cout << "请输入每个进程的最大需求矩阵:" << endl;
        for(int i = 0; i < n; i++) {
            cout << "进程 P" << i << " 的最大需求:" << endl;
            for(int j = 0; j < m; j++) {
                cin >> max[i][j];
            }
        }

        cout << "请输入每个进程已分配的资源矩阵:" << endl;
        for(int i = 0; i < n; i++) {
            cout << "进程 P" << i << " 的已分配资源:" << endl;
            for(int j = 0; j < m; j++) {
                cin >> allocation[i][j];
                need[i][j] = max[i][j] - allocation[i][j];
            }
        }

        cout << "请输入可用资源向量:" << endl;
        for(int i = 0; i < m; i++) {
            cin >> available[i];
        }
    }

    // 检查是否安全
    bool isSafe() {
        vector<int> work = available; // 创建工作向量，初始化为可用资源
        fill(finish.begin(), finish.end(), false); // 初始化完成状态向量为 false
        vector<int> safeSeq; // 安全序列

        int count = 0; // 计数器，记录已完成的进程数
        while (count < n) { // 当未完成的进程数小于总进程数时
            bool found = false; // 标记是否找到可执行的进程
            for (int i = 0; i < n; i++) { // 遍历所有进程
                if (!finish[i]) { // 如果进程未完成
                    bool possible = true; // 假设该进程可以执行
                    for (int j = 0; j < m; j++) { // 检查该进程的需求
                        if (need[i][j] > work[j]) { // 如果需求超过可用资源
                            possible = false; // 该进程无法执行
                            break; // 跳出循环
                        }
                    }

                    if (possible) { // 如果该进程可以执行
                        for (int j = 0; j < m; j++) { // 更新工作向量
                            work[j] += allocation[i][j]; // 将已分配资源加到工作向量
                        }
                        finish[i] = true; // 标记该进程为完成
                        safeSeq.push_back(i); // 将进程加入安全序列
                        found = true; // 找到可执行的进程
                        count++; // 增加已完成进程计数
                    }
                }
            }

            if (!found) { // 如果没有找到可执行的进程
                cout << "系统不安全！" << endl; // 输出不安全信息
                return false; // 返回不安全
            }
        }

        cout << "系统安全！安全序列为: "; // 输出安全信息
        for (int i : safeSeq) { // 遍历安全序列
            cout << "P" << i << " "; // 输出安全序列中的进程
        }
        cout << endl; // 换行
        return true; // 返回安全
    }

    // 请求资源
    bool requestResource(int processId, vector<int>& request) {
        // 检查请求是否超过需求
        for (int i = 0; i < m; i++) {
            if (request[i] > need[processId][i]) {
                cout << "错误：请求超过最大需求！" << endl;
                return false;
            }
        }

        // 检查是否有足够的可用资源
        for (int i = 0; i < m; i++) {
            if (request[i] > available[i]) {
                cout << "错误：没有足够的可用资源！" << endl;
                return false;
            }
        }

        // 尝试分配资源
        for (int i = 0; i < m; i++) {
            available[i] -= request[i];
            allocation[processId][i] += request[i];
            need[processId][i] -= request[i];
        }

        // 检查是否安全
        if (isSafe()) {
            return true;
        } else {
            // 如果不安全，取消分配
            for (int i = 0; i < m; i++) {
                available[i] += request[i];
                allocation[processId][i] -= request[i];
                need[processId][i] += request[i];
            }
            return false;
        }
    }

    // 打印当前系统状态
    void printState() {
        cout << "\n当前系统状态：" << endl;
        cout << "进程  最大需求  已分配  需求" << endl;
        for (int i = 0; i < n; i++) {
            cout << "P" << i << "    ";
            for (int j = 0; j < m; j++) {
                cout << max[i][j] << " ";
            }
            cout << "    ";
            for (int j = 0; j < m; j++) {
                cout << allocation[i][j] << " ";
            }
            cout << "    ";
            for (int j = 0; j < m; j++) {
                cout << need[i][j] << " ";
            }
            cout << endl;
        }
        cout << "可用资源：";
        for (int i = 0; i < m; i++) {
            cout << available[i] << " ";
        }
        cout << endl;
    }
};

// 主函数示例
int main() {
    int n, m;
    cout << "请输入进程数量：";
    cin >> n;
    cout << "请输入资源类型数量：";
    cin >> m;

    BankerAlgorithm banker(n, m);
    banker.initialize();
    banker.printState();
    
    if (banker.isSafe()) {
        // 测试资源请求
        cout << "\n测试资源请求：" << endl;
        int processId;
        vector<int> request(m);
        
        cout << "请输入请求进程ID（0-" << n-1 << "）：";
        cin >> processId;
        cout << "请输入请求资源数量：" << endl;
        for (int i = 0; i < m; i++) {
            cin >> request[i];
        }
        
        if (banker.requestResource(processId, request)) {
            cout << "资源分配成功！" << endl;
            banker.printState();
        } else {
            cout << "资源分配失败！" << endl;
        }
    }

    return 0;
}
