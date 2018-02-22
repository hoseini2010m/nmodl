#include "printer/code_printer.hpp"
#include "utils/string_utils.hpp"

CodePrinter::CodePrinter(const std::string& filename) {
    if (filename.empty()) {
        throw std::runtime_error("Empty filename for CodePrinter");
    }

    ofs.open(filename.c_str());

    if (ofs.fail()) {
        auto msg = "Error while opening file '" + filename + "' for CodePrinter";
        throw std::runtime_error(msg);
    }

    sbuf = ofs.rdbuf();
    result = std::make_shared<std::ostream>(sbuf);
}

void CodePrinter::start_block() {
    *result << "{";
    add_newline();
    indent_level++;
}

void CodePrinter::start_block(std::string&& text) {
    add_indent();
    *result << text << " {";
    add_newline();
    indent_level++;
}

void CodePrinter::add_indent() {
    *result << std::string(indent_level * NUM_SPACES, ' ');
}

void CodePrinter::add_text(const std::string& text) {
    *result << text;
}

void CodePrinter::add_line(const std::string& text) {
    add_indent();
    *result << text;
    add_newline();
}

void CodePrinter::add_newline(int n) {
    for (int i = 0; i < n; i++) {
        *result << std::endl;
    }
}

void CodePrinter::end_block() {
    indent_level--;
    add_indent();
    *result << "}";
}