#pragma once

#include "Fraction.hpp"
#include "Calculable.hpp"
#include "../errors.hpp"
#include "../syntax/Token.hpp"

class BigInt;
class Complex;

class Num : public Calculable {
  int data;
public:
  Num(std::string& text);
  Num(int num);
  ~Num();
  std::string result() const;
  Calculable* copy() const;

  int get_data() const;
  Calculable* add(Calculable* other);
  Calculable* sub(Calculable* other);
  Calculable* mul(Calculable* other);
  Calculable* div(Calculable* other);
  Calculable* rtd(Calculable* other);
};
