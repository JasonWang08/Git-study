public class Complex_Num_Compute {
    private ComplexNum num1;
    private ComplexNum num2;
    Complex_Num_Compute()
    {

    }
    Complex_Num_Compute(ComplexNum num1,ComplexNum num2)
    {
        this.num1=num1;
        this.num2=num2;
    }
    public ComplexNum Complex_Num_Add()
    {
        ComplexNum result=new ComplexNum();
        result.Real_part=num1.Real_part+num2.Real_part;
        result.Imag_part=num1.Imag_part+num2.Imag_part;
        return result;
    }
    public ComplexNum Complex_Num_Sub()
    {
        ComplexNum result=new ComplexNum();
        result.Real_part=num1.Real_part-num2.Real_part;
        result.Imag_part=num1.Imag_part-num2.Imag_part;
        return result;
    }
    public ComplexNum Complex_Num_Mul()
    {
        ComplexNum result=new ComplexNum();
        result.Real_part=num1.Real_part*num2.Real_part-num1.Imag_part*num2.Imag_part;
        result.Imag_part=num1.Real_part*num2.Imag_part+num1.Imag_part*num2.Real_part;
        return result;
    }
}
