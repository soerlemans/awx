#ifndef TOKEN_TYPE_HELPERS_H
#define TOKEN_TYPE_HELPERS_H

#include "token_type.hpp"

// TODO: All these functions can be templated with a simple macro
#define DEFINE_TOKEN_TYPE_HELPER(func, ...)              \
  constexpr auto func(const TokenType t_tokentype)->bool \
  {                                                      \
    bool result{false};                                  \
                                                         \
    switch(t_tokentype) {                                \
      default:                                           \
        break;                                           \
    }                                                    \
                                                         \
    return result;                                       \
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
constexpr auto is_int(const TokenType t_tokentype) -> bool
{
  bool result{false};

  switch(t_tokentype) {
    case TokenType::HEX:
    case TokenType::INTEGER:
      result = true;
      break;

    default:
      break;
  }

  return result;
}

constexpr auto is_numeric(const TokenType t_tokentype) -> bool
{
  bool result{false};

  if(is_int(t_tokentype) || t_tokentype == TokenType::FLOAT)
    result = true;

  return result;
}

constexpr auto is_literal(const TokenType t_tokentype) -> bool
{
  bool result{false};

  switch(t_tokentype) {
    case TokenType::INTEGER:
    case TokenType::HEX:
    case TokenType::FLOAT:
    case TokenType::STRING:
    case TokenType::REGEX:
      result = true;
      break;

    default:
      break;
  }

  return result;
}

constexpr auto is_lvalue(const TokenType t_tokentype) -> bool
{
  bool result{false};

  if(t_tokentype == TokenType::IDENTIFIER)
    result = true;

  return result;
}

constexpr auto is_rvalue(const TokenType t_tokentype) -> bool
{
  bool result{false};

  if(is_literal(t_tokentype) || is_lvalue(t_tokentype))
    result = true;

  return result;
}

constexpr auto is_terminator(const TokenType t_tokentype) -> bool
{
  bool result{false};

  switch(t_tokentype) {
    case TokenType::SEMICOLON:
    case TokenType::END_OF_LINE:
      result = true;
      break;

    default:
      break;
  }

  return result;
}

constexpr auto is_control_statement(const TokenType t_tokentype) -> bool
{
  bool result{false};

  switch(t_tokentype) {
    case TokenType::IF:
    case TokenType::ELSE:
    case TokenType::DO:
    case TokenType::WHILE:
    case TokenType::FOR:
      result = true;
      break;

    default:
      break;
  }

  return result;
}

constexpr auto is_logical_junction(const TokenType t_tokentype) -> bool
{
  bool result{false};

  switch(t_tokentype) {
    case TokenType::AND:
    case TokenType::OR:
      result = true;
      break;

    default:
      break;
  }

  return result;
}

constexpr auto is_comparison_operator(const TokenType t_tokentype) -> bool
{
  bool result{false};

  switch(t_tokentype) {
    case TokenType::LESS_THAN:
    case TokenType::LESS_THAN_EQUAL:

    case TokenType::EQUAL:
    case TokenType::NOT_EQUAL:

    case TokenType::GREATER_THAN:
    case TokenType::GREATER_THAN_EQUAL:
      result = true;
      break;

    default:
      break;
  }

  return result;
}
}; // namespace tokentype

#endif // TOKEN_TYPE_HELPERS_H
