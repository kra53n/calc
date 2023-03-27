#include "util.hpp"

// Greatest Common Divisor
int gcd(int num1, int num2) {
  // The binary GCD algorithm implementation
  num1 = abs(num1);
  num2 = abs(num2);
  int d = 1;
  while (num1 and num2) {
    if (num1 % 2 == 0 and num2 % 2 == 0) {
      d *= 2;
      num1 /= 2;
      num2 /= 2;
    }
    else if (num1 % 2 == 0 and num2 % 2) {
      num1 /= 2;
    }
    else if (num1 % 2 and num2 % 2 == 0) {
      num2 /= 2;
    }
    else if (num1 % 2 and num2 % 2) {
      if (num1 >= num2) {
        num1 -= num2;
      }
      else {
        num2 -= num1;
      }
    }
  }
  return d * std::max(num1, num2);
}
