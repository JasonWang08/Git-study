public class Coursetest {
    public static void main(String args[])
    {
        Course Mycourse=new Course("Data And Structures");
        Mycourse.AddStudent("王宇恒", 20, "2022302701");
        Mycourse.AddStudent("党子轩", 20, "2022302602");
        System.out.println(Course.GetCourseName());
        Mycourse.Getstuinfo();
        System.out.println(Course.Getstunum());
    }
}
