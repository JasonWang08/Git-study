public class Course {
      //  private static int CourseSize;
        private Student[] studentarray=new Student[100];
        private static int studentnum;
        private static String Coursename;
        Course()
        {
            Coursename=" ";
         //   CourseSize=100;
            studentnum=0;
        }
        Course(String InputCourseName)
        {
            Coursename=InputCourseName;
           // CourseSize=InputCourseSize;
            studentnum=0;
        }
        public void AddStudent(String Inputname,int Inputage,String InputStunum) 
        {
            if(studentnum>100)
                System.out.print("There are no more places left! ");
            
            else
            {   
                Student newstudent=new Student(Inputname,Inputage,InputStunum);
                studentarray[studentnum]=newstudent;
                studentnum++;
            }
        }
        public void Getstuinfo()
        {
            for(int i=0;i<studentnum;i++)
            {
                System.out.print(studentarray[i].GetStuName()+" ");
                System.out.print(studentarray[i].GetStuNum()+" ");
                System.out.print(studentarray[i].GetStuAge()+" ");
                System.out.println();
            }
        }
        public static int Getstunum()
        {
            return studentnum;
        }
        public static String GetCourseName()
        {
            return Coursename;
        }
}
