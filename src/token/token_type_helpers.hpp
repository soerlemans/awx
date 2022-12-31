#ifndef TOKEN_TYPE_HELPERS_H
#define TOKEN_TYPE_HELPERS_H

#include "token_type.hpp"


// TODO: All these functions can be templated with a simple macro
#define CASE_TOKEN_TYPE(tokentype) case TokenType::tokentype:

#define DEFINE_TOKEN_TYPE_HELPER(func, ...)              \
  constexpr auto func(const TokenType t_tokentype)->bool \
  {                                                      \
    switch(t_tokentype) {                                \
      __VA_ARGS__                                        \
      return true;                                       \
                                                         \
      default:                                           \
        break;                                           \
    }                                                    \
                                                         \
    return false;                                        \
  }

// Functions intended for figuring out to what kind of class/property a token
// Type specifier belongs, example is a token type a numerical or valid for
// Usage as rvalue? Or could it produce a boolean result?
namespace tokentype
{
// Functions declarations:
constexpr auto is_int(const TokenType t_tokentype) -> bool;
constexpr auto is_numeric(const TokenType t_tokentype) -> bool;

constexpr auto is_literal(const TokenType t_tokentype) -> bool;
constexpr auto is_lvalue(const TokenType t_tokentype) -> bool;
constexpr auto is_rvalue(const TokenType t_tokentype) -> bool;

constexpr auto is_terminator(const TokenType t_tokentype) -> bool;
constexpr auto is_control_statement(const TokenType t_tokentype) -> bool;

constexpr auto is_logical_junction(const TokenType t_tokentype) -> bool;
constexpr auto is_comparison_operator(const TokenType t_tokentype) -> bool;

// Function definitions:
// clang-format off
DEFINE_TOKEN_TYPE_HELPER(is_int,
						 CASE_TOKEN_TYPE(INTEGER)
						 CASE_TOKEN_TYPE(HEX));

constexpr auto is_numeric(const TokenType t_tokentype) -> bool
{
  return is_int(t_tokentype) || t_tokentype == TokenType::FLOAT;
}

DEFINE_TOKEN_TYPE_HELPER(is_literal,
                         CASE_TOKEN_TYPE(INTEGER)
						 CASE_TOKEN_TYPE(HEX)
                         CASE_TOKEN_TYPE(FLOAT)
						 CASE_TOKEN_TYPE(STRING)
                         CASE_TOKEN_TYPE(REGEX));

DEFINE_TOKEN_TYPE_HELPER(is_value,
						 CASE_TOKEN_TYPE(IDENTIFIER));

constexpr auto is_rvalue(const TokenType t_tokentype) -> bool
{
  return is_literal(t_tokentype) || is_lvalue(t_tokentype);
}

DEFINE_TOKEN_TYPE_HELPER(is_terminator,
						 CASE_TOKEN_TYPE(SEMICOLON)
						 CASE_TOKEN_TYPE(NEWLINE));

DEFINE_TOKEN_TYPE_HELPER(is_control_statement,
						 CASE_TOKEN_TYPE(IF)
						 CASE_TOKEN_TYPE(ELSE)
						 CASE_TOKEN_TYPE(DO)
						 CASE_TOKEN_TYPE(WHILE)
						 CASE_TOKEN_TYPE(FOR));

DEFINE_TOKEN_TYPE_HELPER(is_logical_junction,
						 CASE_TOKEN_TYPE(AND)
						 CASE_TOKEN_TYPE(OR));

DEFINE_TOKEN_TYPE_HELPER(is_comparison_operator,
						 CASE_TOKEN_TYPE(LESS_THAN)
						 CASE_TOKEN_TYPE(LESS_THAN_EQUAL)
						 CASE_TOKEN_TYPE(EQUAL)
						 CASE_TOKEN_TYPE(NOT_EQUAL)
						 CASE_TOKEN_TYPE(GREATER_THAN)
						 CASE_TOKEN_TYPE(GREATER_THAN_EQUAL));

// clang-format on
}; // namespace tokentype

#endif // TOKEN_TYPE_HELPERS_H
