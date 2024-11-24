import time
import multiprocessing
import threading
from multiprocessing import freeze_support

# 单进程单线程实现
def count_keyword_in_file(file_path, keyword):
    count = 0
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            for line in file:
                count += line.count(keyword)
        return count
    except Exception as e:
        print(f"Error while reading file: {e}")
        return None


# 单进程多线程实现
def count_keyword_in_chunk_thread(chunk, keyword, result, index):
    result[index] = chunk.count(keyword)

def count_keyword_in_file_multithreading(file_path, keyword, num_threads):
    with open(file_path, 'r', encoding='utf-8') as file:
        text = file.read()

    # 将文本分成多个块
    chunk_size = len(text) // num_threads
    chunks = [text[i:i + chunk_size] for i in range(0, len(text), chunk_size)]
    
    # 结果存放列表
    result = [0] * num_threads
    threads = []

    # 创建多个线程处理不同的块
    for i in range(num_threads):
        thread = threading.Thread(target=count_keyword_in_chunk_thread, args=(chunks[i], keyword, result, i))
        threads.append(thread)
        thread.start()

    # 等待所有线程完成
    for thread in threads:
        thread.join()

    return sum(result)

# 测试不同线程数下的性能
def test_multithreading_with_different_threads(file_path, keyword):
    for num_threads in [1, 2, 4, 8, 16]:  # 可以根据需求调整线程数量
        start_time = time.time()
        keyword_count = count_keyword_in_file_multithreading(file_path, keyword, num_threads)
        print(f"{num_threads} threads: Keyword '{keyword}' appears {keyword_count} times in the file. Time taken: {time.time() - start_time} seconds.")




if __name__ == '__main__':
    freeze_support()
    
    # 文件路径和关键词
    file_path = 'D:/OS/1.txt'
    keyword = 'e'

    # 单进程单线程统计
    start_time = time.time()
    keyword_count = count_keyword_in_file(file_path, keyword)
    print(f"单进程单线程: Keyword '{keyword}' appears {keyword_count} times in the file.")
    print(f"Time taken: {time.time() - start_time} seconds.\n")

    # 测试不同线程数下的单进程多线程性能
    test_multithreading_with_different_threads(file_path, keyword)

