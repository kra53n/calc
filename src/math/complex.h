# include <iostream>
# include <stdlib.h>
# include <conio.h>;

using namespace std;

struct complex {
   int a, b;
};

class Complex {
    complex num;
public:
    Complex(int x = 0, int y = 0)
    {
        num.a = x;
        num.b = y;
    }
    Complex operator +(const Complex& c);
    Complex operator *(const Complex& c);
    Complex operator -(const Complex& c);
    Complex operator /(const Complex& c);
    bool operator ==(const Complex& c);
    void Print();
    Complex Read();
};