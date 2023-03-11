#pragma once

#include "Base.hpp"

class Num : public Base {
  int data;
public:
  Num(std::string text);
  ~Num();
  std::string result();
}
