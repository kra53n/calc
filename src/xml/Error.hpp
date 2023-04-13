#pragma once

#include <iostream>

namespace xml {

struct Error {
	std::string message;

	Error(std::string message);
	friend std::ostream& operator<<(std::ostream& out, const Error& e);
};

} // xml