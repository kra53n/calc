#include <iostream>
#include <String>
#include <vector>
#include <iomanip>

using namespace std;

class BigInt {
private:
    vector<int> chunks;
    int sign;
    static const int BASE = 2;
    static const int BASE10 = 100;

public:
    BigInt();
    BigInt(string str);
    BigInt _plus(BigInt& a);
    BigInt _minus(BigInt& a);
    void _normalizationSigns();
    void _normalizationChunks();
    void _resize(int newsize);
    int my_div(int num, int diver);
    int my_mod(int num, int diver);
    BigInt operator + (BigInt& num);
    BigInt operator - (BigInt& num);
    BigInt operator * (BigInt);
    BigInt operator / (BigInt num);
    bool operator>=(BigInt num);
    int getBASE();
    friend ostream& operator << (ostream& os, BigInt& num);
};