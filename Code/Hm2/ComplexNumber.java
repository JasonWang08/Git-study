public class ComplexNumber {
    private double real;
    private double imaginary;

    // 构造函数
    public ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    // 加法运算
    public ComplexNumber add(ComplexNumber other) {
        return new ComplexNumber(this.real + other.real, this.imaginary + other.imaginary);
    }

    // 减法运算
    public ComplexNumber subtract(ComplexNumber other) {
        return new ComplexNumber(this.real - other.real, this.imaginary - other.imaginary);
    }

    // 乘法运算
    public ComplexNumber multiply(ComplexNumber other) {
        double realPart = this.real * other.real - this.imaginary * other.imaginary;
        double imaginaryPart = this.real * other.imaginary + this.imaginary * other.real;
        return new ComplexNumber(realPart, imaginaryPart);
    }

    // 除法运算
    public ComplexNumber divide(ComplexNumber other) {
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        double realPart = (this.real * other.real + this.imaginary * other.imaginary) / denominator;
        double imaginaryPart = (this.imaginary * other.real - this.real * other.imaginary) / denominator;
        return new ComplexNumber(realPart, imaginaryPart);
    }

    // 重写toString()方法
    @Override
    public String toString() {
        String result;
        if (imaginary == 0) {
            result = real + "";
            return result;
        } else if (imaginary < 0) {
            if (real != 0) {
                result = real + "" + imaginary + "j";
                return result;
            } else {
                result = imaginary + "j";
                return result;
            }
        } else {
            if (real != 0) {
                result = real + "+" + imaginary + "j";
                return result;
            } else {
                result = imaginary + "j";
                return result;
            }
        }
    }

    // 重写equals()方法
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof ComplexNumber)) {
            return false;
        }
        ComplexNumber other = (ComplexNumber) obj;
        return this.real == other.real && this.imaginary == other.imaginary;
    }
}
