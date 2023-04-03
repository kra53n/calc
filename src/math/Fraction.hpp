#pragma once

#include <string>
#include <cstdlib>
#include <algorithm>

#include "Calculable.hpp"
#include "../util.hpp"
#include "../errors.hpp"
#include "../syntax/Token.hpp"

class Num;

class Fraction : public Calculable {
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
  Calculable* copy() const;

  void simplify();
  Calculable* post_treatment();

  _Data get_data() const;
  Calculable* add(Calculable* other);
  Calculable* sub(Calculable* other);
  Calculable* mul(Calculable* other);
  Calculable* div(Calculable* other);
  Calculable* rtd(Calculable* other);
};
