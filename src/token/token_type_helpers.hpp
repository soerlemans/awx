#ifndef AWX_TOKEN_TOKEN_TYPE_HELPERS_HPP
#define AWX_TOKEN_TOKEN_TYPE_HELPERS_HPP

#include "token_type.hpp"


namespace token {
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
namespace tokentype {
// Functions declarations:
[[nodiscard]] constexpr auto is_literal(TokenType t_tokentype) -> bool;
[[nodiscard]] constexpr auto is_terminator(TokenType t_tokentype) -> bool;
[[nodiscard]] constexpr auto is_unary_operator(TokenType t_tokentype) -> bool;
[[nodiscard]] constexpr auto is_identifier(TokenType t_tokentype)
  -> bool;

// Function definitions:
DEFINE_TOKEN_TYPE_HELPER(is_literal,
                         CASE_TOKEN_TYPE(INTEGER) CASE_TOKEN_TYPE(HEX)
                           CASE_TOKEN_TYPE(FLOAT) CASE_TOKEN_TYPE(STRING)
                             CASE_TOKEN_TYPE(REGEX));

DEFINE_TOKEN_TYPE_HELPER(is_value, CASE_TOKEN_TYPE(IDENTIFIER));

DEFINE_TOKEN_TYPE_HELPER(is_terminator,
                         CASE_TOKEN_TYPE(SEMICOLON) CASE_TOKEN_TYPE(NEWLINE));

DEFINE_TOKEN_TYPE_HELPER(is_unary_operator,
                         CASE_TOKEN_TYPE(PLUS) CASE_TOKEN_TYPE(MINUS));

// A regular identifier is a valid name for a function declaration
// As in 'function func()' is just as valid as 'function func ()'
DEFINE_TOKEN_TYPE_HELPER(is_identifier,
                         CASE_TOKEN_TYPE(IDENTIFIER)
                           CASE_TOKEN_TYPE(FUNCTION_IDENTIFIER));

}; // namespace tokentype
} // namespace token

#endif // AWX_TOKEN_TOKEN_TYPE_HELPERS_HPP
