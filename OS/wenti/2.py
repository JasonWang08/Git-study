import multiprocessing
import time

def count_keyword_in_chunk(chunk, keyword):
    return chunk.count(keyword)

def count_keyword_in_file_multiprocessing(file_path, keyword):
    with open(file_path, 'r', encoding='utf-8') as file:
        text = file.read()

    # 将文本分割成多个块
    num_chunks = multiprocessing.cpu_count()
    chunk_size = len(text) // num_chunks
    chunks = [text[i:i + chunk_size] for i in range(0, len(text), chunk_size)]

    # 使用多进程来处理
    with multiprocessing.Pool(processes=num_chunks) as pool:
        results = pool.starmap(count_keyword_in_chunk, [(chunk, keyword) for chunk in chunks])

    return sum(results)

# 统计执行时间
start_time = time.time()

# 统计关键词出现的次数
keyword_count = count_keyword_in_file_multiprocessing(file_path, keyword)
print(f"多进程单线程: Keyword '{keyword}' appears {keyword_count} times in the file.")

# 输出耗时
print(f"Time taken: {time.time() - start_time} seconds.")
