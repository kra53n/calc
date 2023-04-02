#include "Num.hpp"
#include "BigInt.hpp"

BigInt::BigInt() {
    digits.push_back(0);
    sign = true;
    token_name = Token::TokenName::BigInt;
}

BigInt::BigInt(std::string number) {
    int didits_pos = isdigit(number.at(0)) ? 0 : 1;
    sign = number.at(0) == '-' ? 0 : 1;

    for (unsigned int i = didits_pos; i < number.length(); i++)
        digits.push_back(number.at(i) - '0');

    ignoreLeadingZeros();
    token_name = Token::TokenName::BigInt;
}

void BigInt::ignoreLeadingZeros() {
    while (digits.size() > 1 && digits.at(0) == 0)
        digits.erase(digits.begin(), digits.begin() + 1);
}

std::string BigInt::to_string() const {
    std::string str;
    if (!sign)
        str += "-";
    for (unsigned int i = 0; i < digits.size(); i++)
        str += std::to_string(digits.at(i));
    return str;
}

BigInt& BigInt::operator=(const BigInt& rhs) {
    if (this == &rhs)
        return *this;
    sign = rhs.sign;
    digits = rhs.digits;
    return *this;
}

bool BigInt::operator>(const BigInt& rhs) const {
    if (sign == true && rhs.sign == false)
        return true;
    if (sign == false && rhs.sign == true)
        return false;

    if (digits.size() > rhs.digits.size())
        return sign;
    if (digits.size() < rhs.digits.size())
        return !sign;

    for (size_t i = 0; i < digits.size(); i++) {
        if (digits.at(i) > rhs.digits.at(i))
            return sign;
        if (digits.at(i) < rhs.digits.at(i))
            return !sign;
    }

    return false;
}

bool BigInt::operator<(const BigInt& rhs) const {
    return false == (*this == rhs) && false == (*this > rhs);
}

bool BigInt::operator==(const BigInt& rhs) const {
    return (sign == rhs.sign && digits == rhs.digits);
}

BigInt BigInt::abs() const {
    BigInt a(*this);
    a.sign = true;
    return a;
}

BigInt BigInt::operator+(const BigInt& rhs) const {
    BigInt sum;
    if (digits.at(0) == 0 && rhs.digits.at(0) == 0)
        return sum;
    if (sign == rhs.sign) {
        sum.digits.clear();
        sum.sign = sign;
        unsigned int carry = 0;
        int index1 = digits.size() - 1;
        int index2 = rhs.digits.size() - 1;
        while (index1 >= 0 || index2 >= 0) {
            auto digitsum = this->digit(index1) + rhs.digit(index2) + carry;

            carry = digitsum / 10;
            digitsum %= 10;

            sum.digits.push_back(digitsum);
            index1--;
            index2--;
        }
        if (carry != 0)
            sum.digits.push_back(carry);
        std::reverse(sum.digits.begin(), sum.digits.end());
    }
    else {
        if (this->abs() > rhs.abs()) {
            sum = this->abs() - rhs.abs();
            sum.sign = sign;
        }
        else {
            sum = rhs.abs() - this->abs();
            sum.sign = rhs.sign;
        }
    }
    return sum;
}

BigInt BigInt::operator-(const BigInt& rhs) const {
    BigInt difference;
    if ((digits.at(0) == 0 && rhs.digits.at(0) == 0))
        return difference;
    if (sign == rhs.sign) { 
        if (this->abs() > rhs.abs() || this->abs() == rhs.abs()) { 
            difference.digits.clear();
            int index1 = digits.size() - 1;
            int index2 = rhs.digits.size() - 1;
            int borrow = 0;
            difference.sign = sign;
            while (index1 >= 0 || index2 >= 0) {
                auto digitdiff = this->digit(index1) - rhs.digit(index2) - borrow;

                if (digitdiff < 0) {
                    borrow = 1;
                    digitdiff += 10;
                }
                else borrow = 0;

                difference.digits.push_back(digitdiff);
                index1--;
                index2--;
            }
            std::reverse(difference.digits.begin(), difference.digits.end());
            difference.ignoreLeadingZeros();
        }
        else { 
            difference = (rhs - (*this));
            difference.sign = !difference.sign;
        }
    }
    else {
        difference = this->abs() + rhs.abs();
        difference.sign = sign;
    }
    return difference;
}

BigInt BigInt::operator/(const BigInt& rhs) const {
    BigInt buffer;
    BigInt result;
    BigInt rhsAbs = rhs.abs();
    result.digits.clear();
    buffer.digits.clear();

    for (size_t i = 0; i < digits.size(); ++i) {
        buffer.digits.push_back(digits[i]);
        buffer.ignoreLeadingZeros();
        if (buffer < rhsAbs) {
            result.digits.push_back(0);
            continue;
        }
        int count;
        for (count = 0; buffer > rhsAbs || buffer == rhsAbs; ++count) {
            buffer = buffer - rhsAbs;
        }
        result.digits.push_back(count);
    }
    result.ignoreLeadingZeros();

    result.sign = true;
    if (sign != rhs.sign && result.digits[0] != 0)
        result.sign = false;

    return result;
}

BigInt BigInt::digitMultiply(unsigned int digit) const {
    BigInt result;
    result.digits.clear();
    result.sign = true;
    unsigned int carry = 0;
    for (int i = digits.size() - 1; i >= 0; i--) {
        unsigned int digitproduct = digits.at(i) * digit + carry;
        if (digitproduct > 9) {
            carry = digitproduct / 10;
            digitproduct %= 10;
        }
        else
            carry = 0;

        result.digits.push_back(digitproduct);
    }
    if (carry != 0)
        result.digits.push_back(carry);

    std::reverse(result.digits.begin(), result.digits.end());
    return result;
}

BigInt BigInt::operator*(const BigInt& rhs) const {
    BigInt product;
    BigInt psum;
    unsigned int zeros_to_insert = 0;
    for (int i = rhs.digits.size() - 1; i >= 0; i--) {
        unsigned int digit = rhs.digits.at(i);
        product = this->digitMultiply(digit);
        product.digits.insert(product.digits.end(), zeros_to_insert++, 0);
        psum = psum + product;
    }
    if (sign != rhs.sign)
        psum.sign = false;
    return psum;
}

BigInt BigInt::operator%(const BigInt& rhs) const {
    BigInt result;
    BigInt divResult = *this / rhs;

    result = *this - divResult * rhs;
    return result;
}

std::ostream& operator<<(std::ostream& ost, BigInt& bigint) {
    ost << bigint.to_string();
    return ost;
}

int BigInt::digit(int index) const {
    return index >= 0 ? digits[index] : 0;
}

std::string BigInt::addBigInt(const BigInt* rhs)
{
    BigInt a = (*this + (*rhs));
    return a.to_string();
}

std::string BigInt::subBigInt(const BigInt* rhs)
{
    BigInt a = (*this - (*rhs));
    return a.to_string();
}

std::string BigInt::mulBigInt(const BigInt* rhs)
{
    BigInt a = (*this * (*rhs));
    return a.to_string();
}

std::string BigInt::divBigInt(const BigInt* rhs)
{
    Result = (*this / (*rhs)).to_string();
    return Result;
}

std::string BigInt::result() const
{
    return Result;
}

Calculatable* BigInt::add(Calculatable* other)
{
    switch (other->get_token_name()) {
    case Token::TokenName::BigInt: {
        Result = addBigInt((BigInt*)other);
    } break;
    case Token::TokenName::Num: {
        BigInt* tmp = new BigInt(std::to_string(((Num*)other)->get_data()));
        Result = addBigInt(tmp);
        delete tmp;
    } break;
    default:
        throw IncompatibleTypesError();
    }
    return this;
}

Calculatable* BigInt::sub(Calculatable* other)
{
    switch (other->get_token_name()) {
    case Token::TokenName::BigInt: {
        Result = subBigInt((BigInt*)other);
    } break;
    case Token::TokenName::Num: {
        BigInt* tmp = new BigInt(std::to_string(((Num*)other)->get_data()));
        Result = subBigInt(tmp);
        delete tmp;
    } break;
    default:
        throw IncompatibleTypesError();
    }
    return this;
}

Calculatable* BigInt::mul(Calculatable* other)
{
    switch (other->get_token_name()) {
    case Token::TokenName::BigInt: {
        Result = mulBigInt((BigInt*)other);
    } break;
    case Token::TokenName::Num: {
        BigInt* tmp = new BigInt(std::to_string(((Num*)other)->get_data()));
        Result = mulBigInt(tmp);
        delete tmp;
    } break;
    default:
        throw IncompatibleTypesError();
    }
    return this;
}

Calculatable* BigInt::div(Calculatable* other)
{
    switch (other->get_token_name()) {
    case Token::TokenName::BigInt: {
        Result = divBigInt((BigInt*)other);
    } break;
    case Token::TokenName::Num: {
        BigInt* tmp = new BigInt(other->result());
        Result = divBigInt(tmp);
        delete tmp;
    } break;
    default:
        throw IncompatibleTypesError();
    }
    return this;
}

Calculatable* BigInt::rtd(Calculatable* other)
{
    throw UnsupportedOperationError();
}