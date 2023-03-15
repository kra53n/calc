#pragma once

#include "Calculatable.hpp"
#include "../syntax/Token.hpp"

class Num : public Calculatable {
  int data;
public:
  Num(std::string& text);
  ~Num();
  std::string result() const;

  int get_data() const;
  Calculatable* add(Calculatable* other);
  Calculatable* sub(Calculatable* other);
  Calculatable* mul(Calculatable* other);
  Calculatable* div(Calculatable* other);
  Calculatable* rtd(Calculatable* other);
};
