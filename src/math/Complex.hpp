#include <string>
#include <iostream>

#include "../util.hpp"
#include "Fraction.hpp"
#include "Calculable.hpp"
#include "../syntax/Token.hpp"
#include "Num.hpp"

class Num;
using namespace std;

class Complex : public Calculable {
    struct _Data {
        int a, b;
    };
    _Data data;
public:
    Complex(int real = 0, int img = 0);
    Complex(std::string& text);

    _Data add_complex(const _Data& a, const _Data& b);
    _Data sub_complex(const _Data& a, const _Data& b);
    _Data mul_complex(const _Data& a, const _Data& b);
    _Data div_complex(const _Data& a, const _Data& b);
    _Data add_num(int a, const _Data& b);
    _Data sub_num(int a, const _Data& b);
    _Data mul_num(int a, const _Data& b);
    _Data div_num(int a, const _Data& b);

    Calculable* copy() const;
    Calculable* add(Calculable* other);
    Calculable* sub(Calculable* other);
    Calculable* mul(Calculable* other);
    Calculable* div(Calculable* other);
    Calculable* rtd(Calculable* other);
    std::string result() const;
};
