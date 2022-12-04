#ifndef PARSER_H
#define PARSER_H

#include "lexer.hpp"
#include "ast.hpp"


class Parser {
private:
  TokenStream m_tokenstream;

public:
  Parser(TokenStream t_tokenstream);

  // Helper
  auto identifier(const Token& t_token) -> void;
  auto keyword(const Token& t_token) -> void;
  auto numeric(const Token& t_token) -> void;
  auto string(const Token& t_token) -> void;
  auto symbol(const Token& t_token) -> void;

  auto parse() -> Ast;

  ~Parser();
};

#endif /* PARSER_H */

