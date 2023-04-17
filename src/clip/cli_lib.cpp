#include "cli_lib.hpp"

namespace cli {

Parser::Parser(int argc, const char** argv)
{
	pos = 0;
	if (argc < 1) {
		return;
	}
	for (int i = 1; i <= argc; i++) {
		_argv.push_back(argv[i]);
	}
}

Parser::~Parser()
{
}

bool Parser::empty()
{
	return pos >= _cmds.size();
}

Parser& Parser::add_arg(Arg arg)
{
	for (auto it = _argv.begin(); it != _argv.end(); it++)
	{
		if (arg.name != *it) {
			continue;
		}
		if (arg.type == Type::None) {
			_cmds.push_back(new Cmd{ arg.name, "" });
		}
		else if (arg.type == Type::String) {
			auto tmp = it;
			tmp++;
			if (tmp == _argv.end()) {
				continue;
			}
			_cmds.push_back(new Cmd{ arg.name, *tmp });
		}
	}
	return *this;
}

Cmd* Parser::next()
{
	return empty() ? nullptr : _cmds[pos];
}

} // cli
