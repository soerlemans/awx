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
  auto identifier() -> void;
  auto keyword() -> void;
  auto numeric() -> void;
  auto string() -> void;
  auto symbol() -> void;

  auto parse() -> void;

  ~Parser();
};

#endif /* PARSER_H */

