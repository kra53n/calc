#pragma once

#include <string>

#include "../syntax/Token.hpp"

class Calculatable {
public:
  virtual std::string result() const = 0;
  friend std::ostream& operator<<(std::ostream& out, const Calculatable& calculatable);

  virtual Calculatable* add(Calculatable& num) = 0;
};
