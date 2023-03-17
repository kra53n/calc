#include "complex.h"



Complex Complex::operator +(const Complex& c) 
{
    Complex d;
    d.num.a = num.a + c.num.a;
    d.num.b = num.b + c.num.b;
    return d;
}

Complex Complex::operator -(const Complex& c) {
    Complex y;
    y.num.a = num.a - c.num.a;
    y.num.b = num.b - c.num.b;
    return y;
}

Complex Complex::operator *(const Complex& c) {
    Complex t;
    t.num.a = num.a * c.num.a - num.b * c.num.b;
    t.num.b = num.a * c.num.b + num.b * c.num.a;
    return t;
}
Complex Complex::operator /(const Complex& c) {
    Complex t;
    t.num.a = (num.a * c.num.a + num.b * c.num.b) / (num.a * num.a + num.b * num.b);
    t.num.b = (num.b * c.num.a - num.a * c.num.b) / (num.a * num.a + num.b * num.b);
    return t;
}

bool Complex::operator ==(const Complex& c) {
    if ((num.a == c.num.a) && (num.b == c.num.b))
        return true;
    return false;
}

void Complex::Print() {
    if (num.b >= 0)
        cout << num.a << "+" << num.b << "i\n";
    else
        cout << num.a << num.b << "i\n";
}

Complex Complex::Read() {
    double x, y;
    cout << "Действительнвая часть: ";
    cin >> x;
    cout << "Мнимая часть:        : ";
    cin >> y;
    Complex A = Complex(x, y);
    return A;
}