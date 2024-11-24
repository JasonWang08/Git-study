#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>  // ���� chrono �����ʱ��ͳ��

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
    std::string file_path;  // �û�������ļ�·��
    std::string keyword;     // �û�����Ĺؼ���

    std::cout << "������Ҫ���ҵ��ļ�·��: ";  // ��ʾ�û������ļ�·��
    std::getline(std::cin, file_path);  // �����û�������ļ�·��

    std::cout << "������Ҫ���ҵĹؼ���: ";  // ��ʾ�û�����ؼ���
    std::cin >> keyword;  // �����û�����Ĺؼ���

    const int thread_count = 4; // ����Ҫʹ�õ��߳�����

    // ��ʼ��ʱ
    auto start_time = std::chrono::high_resolution_clock::now();

    long total_count = count_keyword(file_path, keyword, thread_count);

    // ������ʱ
    auto end_time = std::chrono::high_resolution_clock::now();

    // �����ʱ���Ժ���Ϊ��λ��
    std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;

    // ������
    std::cout << "�ؼ��� '" << keyword << "' ���ֵĴ���: " << total_count << std::endl;
    std::cout << "���Һ�ʱ: " << elapsed_time.count() << " ms" << std::endl;

    return 0;
}
