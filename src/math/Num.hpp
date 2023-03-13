#pragma once

#include "Calculatable.hpp"

class Num : public Calculatable {
  int data;
public:
  Num(std::string text);
  ~Num();
  std::string result() const;
};
