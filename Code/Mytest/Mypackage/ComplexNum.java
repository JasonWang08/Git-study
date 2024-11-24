package Mypackage;
public class ComplexNum {
    public int Real_part;
    public int Imag_part;
    private double Modulus;
    public    ComplexNum()
    {
        this(0,0);
    }
    public    ComplexNum(int Real_part,int Imag_part)
    {
        this.Real_part=Real_part;
        this.Imag_part=Imag_part;
    }
    public double GetModulus()
    {
        Modulus= Math.sqrt(Real_part*Real_part+Imag_part*Imag_part);
        return Modulus;
    }
    public String Tostring()
    {
        String result;
        if(Imag_part<0)
        {
            result=Real_part+""+Imag_part+"j";
        }
        else if(Imag_part==0)
        {
            result=Real_part+" ";
        }
        else
            result=Real_part+"+"+Imag_part+"j";
        return result;
    }
}
