#include "Num.hpp"

Num::Num(std::string text) {
  data = stoi(text);
}

std::string Num::result() const {
  return std::to_string(data);
}
