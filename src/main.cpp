#include "lib.hpp"
#include "clip/clip_lib.hpp"

int main(int argc, const char** argv) {
  clip::Parser arg_parser(argc, argv);
  arg_parser
    .add_arg(clip::Arg{ "--xml", clip::Type::String });

  if (arg_parser.empty()) {
    repl();
  }
  for (clip::Cmd* cmd = arg_parser.next(); cmd; cmd = arg_parser.next()) {
    if (cmd->name == "--xml") {
      process_xml(cmd->val);
    }
  }
}
