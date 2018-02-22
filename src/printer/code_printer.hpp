#ifndef NMODL_CODE_PRINTER_HPP
#define NMODL_CODE_PRINTER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

/**
 * \class CodePrinter
 * \brief Helper class for printing C/C++ code
 *
 * This class provides common functionality required by code generation
 * visitor to print C/C++/Cuda code.
 */

class CodePrinter {
  private:
    std::ofstream ofs;
    std::streambuf* sbuf = nullptr;
    std::shared_ptr<std::ostream> result;
    size_t indent_level = 0;
    const int NUM_SPACES = 4;

  public:
    CodePrinter() : result(new std::ostream(std::cout.rdbuf())) {
    }
    CodePrinter(std::stringstream& stream) : result(new std::ostream(stream.rdbuf())) {
    }
    CodePrinter(const std::string& filename);

    ~CodePrinter() {
        ofs.close();
    }

    /// print whitespaces for indentation
    void add_indent();

    /// start of new block scope (i.e. start with "{")
    /// and increases indentation level
    void start_block();

    void start_block(std::string&&);

    void add_text(const std::string&);

    void add_line(const std::string&);

    void add_newline(int n = 1);

    void increase_indent() {
        indent_level++;
    }

    void decrease_indent() {
        indent_level--;
    }

    /// end of current block scope (i.e. end with "}")
    /// and decreases indentation level
    void end_block();

    int indent_spaces() {
        return NUM_SPACES * indent_level;
    }
};

#endif