#include <string>
#include <vector>
#include <iostream>
#include <iostream>
#include <algorithm>

#include "../errors.hpp"
#include "Calculable.hpp"
#include "../syntax/Token.hpp"

class Num;

using namespace std;

class BigInt : public Calculable {
private:
	void ignoreLeadingZeros();
	BigInt digitMultiply(unsigned int digit) const;

	int digit(int index) const;

	std::vector<unsigned int> digits;
	bool sign;

	string Result;

public:
	BigInt();
	BigInt(std::string number);

	BigInt& operator=(const BigInt& rhs);

	bool operator>(const BigInt& rhs) const;
	bool operator<(const BigInt& rhs) const;
	bool operator==(const BigInt& rhs) const;

	friend std::ostream& operator<<(std::ostream& outStream, BigInt& bigint);

	BigInt operator+(const BigInt& rhs) const;
	BigInt operator-(const BigInt& rhs) const;
	BigInt operator*(const BigInt& rhs) const;
	BigInt operator/(const BigInt& rhs) const;
	BigInt operator%(const BigInt& rhs) const;

	std::string to_string() const;
	std::string addBigInt(const BigInt* rhs);
	std::string subBigInt(const BigInt* rhs);
	std::string mulBigInt(const BigInt* rhs);
	std::string divBigInt(const BigInt* rhs);

	BigInt abs() const;

	std::string result() const;
	Calculable* copy() const;
	Calculable* add(Calculable* other);
	Calculable* sub(Calculable* other);
	Calculable* mul(Calculable* other);
	Calculable* div(Calculable* other);
	Calculable* rtd(Calculable* other);
};
