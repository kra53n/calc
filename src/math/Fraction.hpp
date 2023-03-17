#pragma once

#include <string>
#include <cstdlib>
#include <algorithm>

#include "Calculatable.hpp"
#include "../syntax/Token.hpp"

class Num;

class Fraction : public Calculatable {
  struct _Data {
    int numerator;
    int denominator;
  };
  _Data data;
public:
  Fraction(std::string& text);
  Fraction(Num* num);
  ~Fraction();
  std::string result() const;

  _Data get_data() const;
  Calculatable* add(Calculatable* other);
  Calculatable* sub(Calculatable* other);
  Calculatable* mul(Calculatable* other);
  Calculatable* div(Calculatable* other);
  Calculatable* rtd(Calculatable* other);
};
