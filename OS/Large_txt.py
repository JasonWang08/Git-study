import random
import lorem

# 生成包含有意义文本的文件
def generate_meaningful_text_file(file_path, file_size_mb):
    file_size_bytes = file_size_mb * 1024 * 1024
    with open(file_path, 'w', encoding='utf-8') as f:
        while f.tell() < file_size_bytes:
            random_paragraph = lorem.paragraph() + '\n'
            f.write(random_paragraph)

# 示例用法
file_path = 'large_text_file_meaningful.txt'
generate_meaningful_text_file(file_path, file_size_mb=10)
print(f"文件已生成: {file_path}")