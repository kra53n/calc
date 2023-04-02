#pragma once

#include "Fraction.hpp"
#include "Calculatable.hpp"
#include "../errors.hpp"
#include "../syntax/Token.hpp"

class BigInt;
class Complex;

class Num : public Calculatable {
  int data;
public:
  Num(std::string& text);
  Num(int num);
  ~Num();
  std::string result() const;
  Calculatable* copy() const;

  int get_data() const;
  Calculatable* add(Calculatable* other);
  Calculatable* sub(Calculatable* other);
  Calculatable* mul(Calculatable* other);
  Calculatable* div(Calculatable* other);
  Calculatable* rtd(Calculatable* other);
};
