# include <iostream>
# include <stdlib.h>
# include <conio.h>;
#include "Calculatable.hpp"
#include "../syntax/Token.hpp"
#include "Fraction.hpp"
#include <string>


using namespace std;

struct complex {
   int a, b;
};

class Cx : public Calculatable {
  
public:
    complex num;
    complex Result;
    Cx(int x = 0, int y = 0)
    {
        num.a = x;
        num.b = y;
    }
   /* Complex operator +(const Complex& c);
    Complex operator *(const Complex& c);
    Complex operator -(const Complex& c);
    Complex operator /(const Complex& c);
    bool operator ==(const Complex& c);*/

    Calculatable* add(Calculatable* other);
    Calculatable* sub(Calculatable* other);
    Calculatable* mul(Calculatable* other);
    Calculatable* div(Calculatable* other);
    std::string result() const;


    //Cx SubCx(const Cx& a, const Cx& b);

    void Print();
    Cx Read();
};


