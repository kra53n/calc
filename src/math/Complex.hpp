#include <string>
#include <iostream>

#include "../util.hpp"
#include "../errors.hpp"
#include "Fraction.hpp"
#include "Calculable.hpp"
#include "../syntax/Token.hpp"

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

    std::string result() const;
    Calculable* copy() const;
    Calculable* add(Calculable* other);
    Calculable* sub(Calculable* other);
    Calculable* mul(Calculable* other);
    Calculable* div(Calculable* other);
    Calculable* rtd(Calculable* other);
};
