#include "xml_Error.hpp"

namespace xml {

Error::Error(std::string message) 
	: message(message)
{
}

std::ostream& operator<<(std::ostream& out, const Error& e) {
	out << "XML Error: " << e.message << "!";
	return out;
}

} // xml