#include "Cli.hpp"
#include "Tui.hpp"
#include "errors.hpp"

int main(int argc, char** argv) {
    if (argc > 1) {
        Cli(argc, argv);
    } else {
        Tui();
    }
}
