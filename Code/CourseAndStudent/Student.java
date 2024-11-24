public class Student {
    private String name;
    private int age;
    private String stunum;
    Student()
    {

    }
    Student(String Inputname,int Inputage,String InputStunum)
    {
        this.name=Inputname;
        this.age=Inputage;
        this.stunum=InputStunum;
    }
    public String GetStuName()
    {
        return name;
    }
    public String GetStuNum()
    {
        return stunum;
    }
    public int GetStuAge()
    {
        return age;
    }
}
