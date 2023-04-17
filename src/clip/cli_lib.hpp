#pragma once

#include <vector>
#include <string>

namespace cli {

enum class Type {
	None,
	String,
};

struct Arg {
	std::string name;
	Type        type;
};

struct Cmd {
	std::string name;
	std::string val;
};

class Parser {
	std::vector<std::string> _argv;
	std::vector<Cmd*> _cmds;
	int pos;
public:
	Parser(int argc, const char** argv);
	~Parser();
	bool empty();
	Parser& add_arg(Arg arg);
	Cmd* next();
};

} // cli