#ifndef TOKEN_TYPE_HELPERS_H
#define TOKEN_TYPE_HELPERS_H

#include "token_type.hpp"

// Functions intended for figuring out to what kind of class/property a token
// Type specifier belongs, example is a token type a numerical or valid for
// Usage as rvalue? Or could it produce a boolean result?
namespace tokentype
{
// Functions declarations:
constexpr auto is_int(const TokenType t_token_type) -> bool;
constexpr auto is_numeric(const TokenType t_token_type) -> bool;

constexpr auto is_literal(const TokenType t_token_type) -> bool;
constexpr auto is_lvalue(const TokenType t_token_type) -> bool;
constexpr auto is_rvalue(const TokenType t_token_type) -> bool;

constexpr auto is_control_statement(const TokenType t_token_type) -> bool;

constexpr auto is_logical_junction(const TokenType t_token_type) -> bool;
constexpr auto is_comparison_operator(const TokenType t_token_type) -> bool;

// Function definitions:
constexpr auto is_int(const TokenType t_token_type) -> bool
{
  bool result{false};

  switch(t_token_type) {
    case TokenType::HEX:
    case TokenType::INTEGER:
      result = true;
      break;

    default:
      break;
  }

  return result;
}

constexpr auto is_numeric(const TokenType t_token_type) -> bool
{
  bool result{false};

  if(is_int(t_token_type) || t_token_type == TokenType::FLOAT)
    result = true;

  return result;
}

constexpr auto is_literal(const TokenType t_token_type) -> bool
{
  bool result{false};

  switch(t_token_type) {
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

constexpr auto is_lvalue(const TokenType t_token_type) -> bool
{
  bool result{false};

  if(t_token_type == TokenType::IDENTIFIER)
    result = true;

  return result;
}

constexpr auto is_rvalue(const TokenType t_token_type) -> bool
{
  bool result{false};

  if(is_literal(t_token_type) || is_lvalue(t_token_type))
    result = true;

  return result;
}

constexpr auto is_control_statement(const TokenType t_token_type) -> bool
{
  bool result{false};

  switch(t_token_type) {
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

constexpr auto is_logical_junction(const TokenType t_token_type) -> bool
{
  bool result{false};

  switch(t_token_type) {
    case TokenType::AND:
    case TokenType::OR:
      result = true;
      break;

    default:
      break;
  }

  return result;
}

constexpr auto is_comparison_operator(const TokenType t_token_type) -> bool
{
  bool result{false};

  switch(t_token_type) {
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
