#include "errors.hpp"

void UnderliningError::underline(std::ostream& out) const {
  for (int i = 0; i < start_pos; i++) {
	out << ' ';
  }
  for (int i = start_pos; i < end_pos; i++) {
	char ch = '-';
	if (end_pos - start_pos > 1) {
	  if (i == start_pos) {
		ch = '\\';
	  }
	  else if (i == end_pos - 1) {
		ch = '/';
	  }
	}
	out << ch;
  }
}

std::ostream& operator<<(std::ostream& out, const UnderliningError& e) {
  //e.underline(out);
  out << "Error: " << e.message << "!" << std::endl;
  return out;
}


DivisionByZeroError::DivisionByZeroError() {
  this->message = "division by zero";
}


IncompatibleTypesError::IncompatibleTypesError() {
  this->message = "incompatible math types";
}


UnsupportedOperationError::UnsupportedOperationError() {
  this->message = "this math type doesn't support this operation";
}
