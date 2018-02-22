#ifndef DIFFEQ_DRIVER_HPP
#define DIFFEQ_DRIVER_HPP

#include <string>

#include "parser/diffeq_context.hpp"


namespace diffeq {
    /**
     * \class Driver
     * \brief Class that binds all pieces together for parsing differential equations
     *
     * Driver class bind components required for lexing, parsing and ast
     * generation for differential equations.
     */

    /// flex generated scanner class (extends base lexer class of flex)
    class Lexer;

    /// parser class generated by bison
    class Parser;

    class Driver {
      private:
        std::string solve_equation(std::string& state,
                                   int order,
                                   std::string& rhs,
                                   std::string& method,
                                   bool& cnexp_possible,
                                   bool debug = false);

        /// parse given equation into lhs, rhs and find it's order and state variable
        void parse_equation(const std::string& equation,
                            std::string& state,
                            std::string& rhs,
                            int& order);

      public:
        Driver() = default;

        /// solve equation using provided method
        std::string solve(std::string equation, std::string method, bool debug = false);

        /// check if given equation can be solved using cnexp method
        bool cnexp_possible(std::string equation, std::string& solution);
    };

}  // namespace diffeq

#endif