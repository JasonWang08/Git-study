import mysql.connector
from faker import Faker
import random

# 数据库连接信息
db_config = {
    'host': '127.0.0.1',
    'user': 'root',  # 替换为你的MySQL用户名
    'password': '110119',  # 替换为你的MySQL密码
    'database': 'student',  # 替换为你的数据库名
}

fake = Faker()

# 生成学生数据
def generate_student_data(num_students):
    students = []
    for sno in range(20001, 20001 + num_students):  # 学号从 20001 开始
        sname = fake.name()[:20]  # 生成随机姓名并限制为20个字符
        sgender = random.choice(['男', '女'])  # 随机性别
        sbirth = fake.date_of_birth(minimum_age=18, maximum_age=22)  # 生成随机出生日期
        sdep = random.choice(['MA', 'PHY', 'CS'])  # 随机系别
        sdmajor = random.choice(['统计学', '材料物理', '计算机科学与技术', '数据科学与大数据技术'])  # 随机专业
        sage = 2023 - sbirth.year  # 根据出生年份计算年龄
        students.append((f'{sno:05}', sname, sgender, sbirth, sdep, sdmajor, sage))  # 确保 SNO 为 5 个字符
    return students


# 生成选课数据
def generate_sc_data(num_students, num_courses):
    sc_records = set()  # 使用集合避免重复记录
    # 确保每个学生随机选3门不重复的课程
    for sno in range(20001, 20001 + num_students):
        selected_courses = random.sample(range(1, num_courses + 1), 3)  # 每个学生随机选3门课程
        for cno in selected_courses:
            grade = random.choice([None] + list(range(60, 101)))  # 随机成绩
            semester = random.choice(['2021-1', '2021-2', '2022-1', '2022-2'])  # 随机学期
            teachingclass = f'{cno}-01'  # 假设教室编号为课程编号-01
            sc_records.add((f'{sno:05}', str(cno), grade, semester, teachingclass))  # 确保 SNO 为 5 个字符
    return list(sc_records)

def main():
    # 创建数据库连接
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()

    # 清空表数据
    cursor.execute("DELETE FROM SC;")
    cursor.execute("DELETE FROM Student;")
    cursor.execute("DELETE FROM Course;")

    # 生成学生数据并插入
    num_students = 100000
    students = generate_student_data(num_students)

    try:
        cursor.executemany('''
            INSERT INTO Student (SNO, SNAME, SGENDER, SBIRTH, SDEP, SDMAJOR, SAGE)
            VALUES (%s, %s, %s, %s, %s, %s, %s)
        ''', students)
        conn.commit()
        print(f'Inserted {len(students)} students successfully.')
    except mysql.connector.Error as err:
        print(f"Error: {err}")
    
    # 生成课程数据并插入（课程数量为 10）
    num_courses = 10
    courses = generate_course_data(num_courses)

    try:
        cursor.executemany('''
            INSERT INTO Course (CNO, CNAME, CREDIT, CPNO)
            VALUES (%s, %s, %s, %s)
        ''', courses)
        conn.commit()
        print(f'Inserted {len(courses)} courses successfully.')
    except mysql.connector.Error as err:
        print(f"Error: {err}")

    # 生成选课数据并插入
    sc_records = generate_sc_data(num_students, num_courses)

    try:
        cursor.executemany('''
            INSERT INTO SC (SNO, CNO, GRADE, SEMESTER, TEACHINGCLASS)
            VALUES (%s, %s, %s, %s, %s)
        ''', sc_records)
        conn.commit()
        print(f'Inserted {len(sc_records)} SC records successfully.')
    except mysql.connector.Error as err:
        print(f"Error: {err}")

    # 关闭连接
    cursor.close()
    conn.close()

if __name__ == "__main__":
    main()
