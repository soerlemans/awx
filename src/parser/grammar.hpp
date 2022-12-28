#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "../lexer/token_type.hpp"

// This file contains functions for verifying if a given token type adheres to a
// Certain class of tokens like literals, lvalues, rvalue, etc
namespace grammar {
constexpr auto is_literal(const TokenType& t_token_type) -> bool;
constexpr auto is_lvalue(const TokenType& t_token_type) -> bool;
constexpr auto is_rvalue(const TokenType& t_token_type) -> bool;
};     // namespace grammar

#endif // GRAMMAR_H
