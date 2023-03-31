#include "Complex.hpp"

Complex::Complex(int real, int img)
    : data{ real, img }
{
}

Complex::Complex(std::string& text)
{
    bool minuses[3] = { 0, 0, 0 };
    std::string nums[2];
    int num_pos = 0;

    if (text.length() and text[0] == '-') {
        minuses[1] = 1;
        if (text[1] == '-') {
            minuses[0] = 1;
        }
    }

    std::string num;
    for (char ch : text) {
        if (ch == '-') {
            if (num_pos == 0) {
                continue;
            }
            minuses[2] = 1;
        }
        else if (is_skip_char(ch)) {
            nums[num_pos++] = num;
            num = "";
        }
        else {
            num = num + ch;
        }
    }
    nums[num_pos] = num;

    if (num_pos > 0) {
        data.a = std::stoi(nums[0]) * (minuses[0] ^ minuses[1] ? -1 : 1);
        data.b = std::stoi(nums[1]) * (minuses[0] ^ minuses[2] ? -1 : 1);
    }
    else {
        data.a = 0;
        data.b = std::stoi(nums[0]) * (minuses[0] ^ minuses[1] ? -1 : 1);
    }
}

Complex::_Data Complex::add_complex(const _Data& a, const _Data& b)
{
    _Data d;
    d.a = a.a + b.a;
    d.b = a.b + b.b;
    return d;
}

Complex::_Data Complex::sub_complex(const _Data& a, const _Data& b)
{
    _Data d;
    d.a = a.a - b.a;
    d.b = a.b - b.b;
    return d;
}

Complex::_Data Complex::mul_complex(const _Data& a, const _Data& b)
{
    _Data d;
    d.a = a.a * b.a - a.b * b.b;
    d.b = a.a * b.b + a.b * b.a;
    return d;
}

Complex::_Data Complex::div_complex(const _Data& a, const _Data& b)
{
    _Data d;
    d.a = (a.a * b.a + a.b * b.b) / (a.a * a.a + a.b * a.b);
    d.b = (a.b * b.a - a.a * b.b) / (a.a * a.a + a.b * a.b);
    return d;
}

std::string Complex::result() const
{
    std::string ResultStr = std::to_string(data.a) + " " + std::to_string(data.b) + "i";;
    return ResultStr;   
}

Calculatable* Complex::add(Calculatable* other)
{
    data = add_complex(data, ((Complex*)other)->data);
    return this;
}

Calculatable* Complex::sub(Calculatable* other)
{
    data = sub_complex(data, ((Complex*)other)->data);
    return this;
}

Calculatable* Complex::mul(Calculatable* other)
{
    data = mul_complex(data, ((Complex*)other)->data);
    return this;
}

Calculatable* Complex::div(Calculatable* other)
{
    data = div_complex(data, ((Complex*)other)->data);
    return this;
}

Calculatable* Complex::rtd(Calculatable* other)
{
    return this;
}
