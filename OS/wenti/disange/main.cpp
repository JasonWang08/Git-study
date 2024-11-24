#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>  // 引入 chrono 库进行时间统计

long count_keyword_in_chunk(const std::string& chunk, const std::string& keyword) {
    long count = 0;
    size_t pos = 0;

    while ((pos = chunk.find(keyword, pos)) != std::string::npos) {
        count++;
        pos += keyword.length();
    }

    return count;
}

void thread_count_keyword(const std::string& chunk, const std::string& keyword, long& count) {
    count = count_keyword_in_chunk(chunk, keyword);
}

long count_keyword(const std::string& file_path, const std::string& keyword, int thread_count) {
    std::ifstream file(file_path);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    long total_count = 0;
    size_t chunk_size = content.size() / thread_count;
    std::vector<std::thread> threads;
    std::vector<long> counts(thread_count, 0);

    for (int i = 0; i < thread_count; i++) {
        size_t start = i * chunk_size;
        size_t end = (i == thread_count - 1) ? content.size() : (i + 1) * chunk_size;
        std::string chunk = content.substr(start, end - start);
        threads.emplace_back(thread_count_keyword, chunk, keyword, std::ref(counts[i]));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    for (long count : counts) {
        total_count += count;
    }

    return total_count;
}

int main() {
    std::string file_path;  // 用户输入的文件路径
    std::string keyword;     // 用户输入的关键词

    std::cout << "请输入要查找的文件路径: ";  // 提示用户输入文件路径
    std::getline(std::cin, file_path);  // 接收用户输入的文件路径

    std::cout << "请输入要查找的关键词: ";  // 提示用户输入关键词
    std::cin >> keyword;  // 接收用户输入的关键词

    const int thread_count = 4; // 定义要使用的线程数量

    // 开始计时
    auto start_time = std::chrono::high_resolution_clock::now();

    long total_count = count_keyword(file_path, keyword, thread_count);

    // 结束计时
    auto end_time = std::chrono::high_resolution_clock::now();

    // 计算耗时（以毫秒为单位）
    std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;

    // 输出结果
    std::cout << "关键字 '" << keyword << "' 出现的次数: " << total_count << std::endl;
    std::cout << "查找耗时: " << elapsed_time.count() << " ms" << std::endl;

    return 0;
}
