import multiprocessing
import time

# 多进程单线程实现
def count_keyword_in_chunk(chunk, keyword):
    return chunk.count(keyword)

def count_keyword_in_file_multiprocessing(file_path, keyword):
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            text = file.read()

        # 将文本分割成多个块
        num_chunks = multiprocessing.cpu_count()  # 获取CPU核心数
        chunk_size = len(text) // num_chunks  # 每个块的大小
        chunks = [text[i:i + chunk_size] for i in range(0, len(text), chunk_size)]

        # 使用多进程来处理
        with multiprocessing.Pool(processes=num_chunks) as pool:
            results = pool.starmap(count_keyword_in_chunk, [(chunk, keyword) for chunk in chunks])

        return sum(results)
    
    except Exception as e:
        print(f"Error while reading file: {e}")
        return None

# 将主要执行代码移到这个函数中
def main():
    file_path = 'D:/OS/1.txt'
    keyword = 'e'

    # 记录开始时间
    start_time = time.time()

    # 调用多进程单线程统计关键词出现次数
    keyword_count = count_keyword_in_file_multiprocessing(file_path, keyword)

    # 记录结束时间
    end_time = time.time()

    # 输出结果和耗时
    print(f"多进程单线程: Keyword '{keyword}' appears {keyword_count} times in the file.")
    print(f"Time taken: {end_time  - start_time }seconds")

# 添加这个条件语句
if __name__ == '__main__':
    multiprocessing.freeze_support()  # 在 Windows 上需要这行
    main()
