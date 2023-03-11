#include "Num.hpp"

Num::Num(std::string text) {
  data = stoi(text);
}

std::string Num::result() {
  return std::to_string(data);
}
