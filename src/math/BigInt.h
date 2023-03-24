#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <exception>
#include <iostream>

using namespace std;

class BigInt {
public:
	BigInt();
	BigInt(std::string number);
	BigInt(long long number);
	BigInt(const BigInt& rhs);

	BigInt& operator=(const BigInt& rhs);

	bool operator>(const BigInt& rhs) const;
	bool operator<(const BigInt& rhs) const;
	bool operator==(const BigInt& rhs) const;

	friend std::istream& operator>>(std::istream& inStream, BigInt& bigint);
	friend std::ostream& operator<<(std::ostream& outStream, BigInt& bigint);

	const BigInt operator+(const BigInt& rhs) const;
	const BigInt operator-(const BigInt& rhs) const;
	const BigInt operator*(const BigInt& rhs) const;
	const BigInt operator/(const BigInt& rhs) const;
	const BigInt operator%(const BigInt& rhs) const;

	std::string to_string() const;

	BigInt abs() const;
private:
	void ignoreLeadingZeros();
	BigInt digitMultiply(unsigned int digit) const;

	int digit(int index) const;

	std::vector<unsigned int> digits;
	bool sign;
};
