#include "Num.hpp"

Num::Num(std::string text) {
  data = stoi(text);
}

std::string Num::result() const {
  return std::to_string(data);
}

int Num::get_data() const {
  return data;
}

Calculatable* Num::add(Calculatable& num) {
  num = *((Num*)(&num));
  this->data += num.get_data();
  return this;
}
