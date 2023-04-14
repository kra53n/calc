#include "Error.hpp"
#include "Interp.hpp"

namespace xml {

Interp::Interp(Tag* root) 
	: root(root)
{
}

void Interp::_process_errors() {
	if (root == nullptr) {
		throw Error("file without any tags");
	}
	if (root->name != "calc") {
		throw Error("file must begin with calc, " + root->name + " was given");
	}

	int size = root->tags.size();
	if (
		size != 2 or
		root->tags[0]->name != "vars" or
		root->tags[1]->name != "eval"
	) {
		throw Error("file must contain `types`, `eval` tags");
	}
}

Interp::Result Interp::interp() {
	_process_errors();
	Result res;
	for (Tag* tag : root->tags[0]->tags) {
		std::string s1 = tag->attrs[0].val;
		std::string s2 = tag->val->substr(0, tag->val->length());
		res.vars.insert({ s1, s2 });
	}
	res.eval = root->tags[1]->val->substr(0, root->tags[1]->val->length());
	delete_tag(root);
	root = nullptr;
	return res;
}

} // xml