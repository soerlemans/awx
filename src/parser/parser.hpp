#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.hpp"

#include "ast.hpp"


class Parser {
private:
  TokenStream m_token_stream;

  // TODO: Checkout of this variable is needed
  bool m_toplevel;

public:
  Parser(TokenStream t_token_stream);

  // Helper
  auto identifier(const Token& t_token) -> bool;
  auto keyword(const Token& t_token) -> bool;
  auto numeric(const Token& t_token) -> bool;
  auto string(const Token& t_token) -> bool;
  auto symbol(const Token& t_token) -> bool;

  auto toplevel() -> bool;

  auto parse() -> Ast;

  ~Parser();
};

#endif /* PARSER_H */

