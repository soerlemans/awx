#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.hpp"

#include "ast.hpp"


class Parser {
private:
  std::size_t m_index;
  TokenStream m_tokenstream;

  bool m_toplevel;

public:
  Parser(TokenStream t_tokenstream);

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

