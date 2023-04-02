#pragma once

#include <string>
#include <iostream>
#include "syntax/Token.hpp"

struct UnderliningError {
  int start_pos;
  int end_pos;
  std::string message;

  void underline(std::ostream& out) const;
  friend std::ostream& operator<<(std::ostream& out, const UnderliningError& e);
};

struct DivisionByZeroError : UnderliningError {
  DivisionByZeroError();
};

struct IncompatibleTypesError : UnderliningError {
  IncompatibleTypesError();
};

struct UnsupportedOperationError : UnderliningError {
  UnsupportedOperationError();
};
