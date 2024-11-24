#include <iostream>
#include <fstream>
#include <string>
#include <chrono>  // 引入 chrono 库来计时

long count_keyword(const std::string& file_path, const std::string& keyword) {
    std::ifstream file(file_path);
    std::string line;
    long count = 0;

    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << file_path << std::endl;
        return -1; // 返回 -1 表示文件打开失败
    }

    while (std::getline(file, line)) {
        size_t pos = line.find(keyword);
        while (pos != std::string::npos) {
            count++;
            pos = line.find(keyword, pos + keyword.length());
        }
    }

    return count;
}

int main() {
    std::string file_path;  // 用户输入的文件路径
    std::string keyword;    // 用户输入的关键词

    std::cout << "Please enter the file path to search: ";  // 提示用户输入文件路径
    std::getline(std::cin, file_path);  // 接收用户输入的文件路径

    std::cout << "Please enter the keyword to search for: ";  // 提示用户输入关键词
    std::cin >> keyword;  // 接收用户输入的关键词

    // 开始计时
    auto start_time = std::chrono::high_resolution_clock::now();
    
    long total_count = count_keyword(file_path, keyword);

    // 结束计时D
    auto end_time = std::chrono::high_resolution_clock::now();
    
    // 计算耗时（以毫秒为单位）
    std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;

    // 检查文件是否成功打开，如果成功则输出结果
    if (total_count != -1) {
        std::cout << "The keyword '" << keyword << "' appears " << total_count << " times." << std::endl;
        std::cout << "Time taken to search: " << elapsed_time.count() << " ms" << std::endl;  // 输出耗时
    }

    return 0;
}
