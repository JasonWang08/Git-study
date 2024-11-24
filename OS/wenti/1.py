import time

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

# 统计执行时间
start_time = time.time()

# 文件路径和关键词
file_path = 'D:/OS/1.txt'
keyword = 'e'

# 统计关键词出现的次数
keyword_count = count_keyword_in_file(file_path, keyword)
print(f"单进程单线程: Keyword '{keyword}' appears {keyword_count} times in the file.")

# 输出耗时
print(f"Time taken: {time.time() - start_time} seconds.")
