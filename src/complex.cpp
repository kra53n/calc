#include "complex.h"

//Complex Complex::operator +(const Complex& c)
//{
//    Complex d;
//    d.num.a = num.a + c.num.a;
//    d.num.b = num.b + c.num.b;
//    return d;
//}
//
//Complex Complex::operator -(const Complex& c) {
//    Complex y;
//    y.num.a = num.a - c.num.a;
//    y.num.b = num.b - c.num.b;
//    return y;
//}
//
//Complex Complex::operator *(const Complex& c) {
//    Complex t;
//    t.num.a = num.a * c.num.a - num.b * c.num.b;
//    t.num.b = num.a * c.num.b + num.b * c.num.a;
//    return t;
//}
//Complex Complex::operator /(const Complex& c) {
//    Complex t;
//    t.num.a = (num.a * c.num.a + num.b * c.num.b) / (num.a * num.a + num.b * num.b);
//    t.num.b = (num.b * c.num.a - num.a * c.num.b) / (num.a * num.a + num.b * num.b);
//    return t;
//}
//
//bool Complex::operator ==(const Complex& c) {
//    if ((num.a == c.num.a) && (num.b == c.num.b))
//        return true;
//    return false;
//}

complex AddCx(const complex& a, const complex& b)
{
    complex d;
    d.a = a.a + b.a;
    d.b = a.b + b.b;
    return d;
}

//Cx AddCx(const Cx& a, const Cx& b)
//{
//    Cx d;
//    d.num.a = a.num.a + b.num.a;
//    d.num.b = a.num.b + b.num.b;
//    return d;
//}

complex SubCx(const complex& a, const complex& b)
{
    complex d;
    d.a = a.a - b.a;
    d.b = a.b - b.b;
    return d;
}

complex MulCx(const complex& a, const complex& b)
{
    complex d;
    d.a = a.a * b.a - a.b * b.b;
    d.b = a.a * b.b + a.b * b.a;
    return d;
}

complex DivCx(const complex& a, const complex& b)
{
    complex d;
    d.a = (a.a * b.a + a.b * b.b) / (a.a * a.a + a.b * a.b);
    d.b = (a.b * b.a - a.a * b.b) / (a.a * a.a + a.b * a.b);
    return d;
}


void Cx::Print() {
    if (num.b >= 0)
        cout << num.a << "+" << num.b << "i\n";
    else
        cout << num.a << num.b << "i\n";
}

//Cx Cx::Read() {
//    double x, y;
//    cout << "Действительнвая часть: ";
//    cin >> x;
//    cout << "Мнимая часть:        : ";
//    cin >> y;
//    Cx A = Cx(x, y);
//    return A;
//}

std::string Cx::result() const
{
    std::string ResultStr = std::to_string(Result.a) + " " + std::to_string(Result.b) + "i";;
    return ResultStr;   
}

Calculatable* Cx::add(Calculatable* other)
{
    Result = AddCx(num, ((Cx*)other)->num);
    return this;
}

Calculatable* Cx::sub(Calculatable* other)
{
    Result = SubCx(num, ((Cx*)other)->num);
    return this;
}

Calculatable* Cx::mul(Calculatable* other)
{
    Result = MulCx(num, ((Cx*)other)->num);
    return this;
}

Calculatable* Cx::div(Calculatable* other)
{
    Result = DivCx(num, ((Cx*)other)->num);
    return this;
}
