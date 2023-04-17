#include <string>
#include <iostream>

#include "../util.hpp"
#include "Fraction.hpp"
#include "Calculatable.hpp"
#include "../syntax/Token.hpp"
#include "Num.hpp"

class Num;
using namespace std;

class Complex : public Calculatable {
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



    Calculatable* add(Calculatable* other);
    Calculatable* sub(Calculatable* other);
    Calculatable* mul(Calculatable* other);
    Calculatable* div(Calculatable* other);
    Calculatable* rtd(Calculatable* other);
    std::string result() const;
};
