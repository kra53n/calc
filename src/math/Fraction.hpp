#pragma once

#include <string>
#include <cstdlib>
#include <algorithm>

#include "Num.hpp"
#include "Calculatable.hpp"
#include "../syntax/Token.hpp"

class Fraction : public Calculatable {
  struct _Data {
    int numerator;
    int denominator;
  };
  _Data data;
public:
  Fraction(std::string& text);
  ~Fraction();
  std::string result() const;

  void simplify();
  _Data get_data() const;
  Calculatable* add(Calculatable* other);
  Calculatable* sub(Calculatable* other);
  Calculatable* mul(Calculatable* other);
  Calculatable* div(Calculatable* other);
  Calculatable* rtd(Calculatable* other);
};
