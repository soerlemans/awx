#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.hpp"

#include "ast.hpp"


class Parser {
  private:
  TokenStream m_token_stream;

  public:
  Parser(TokenStream t_token_stream);

  // Helper
  auto function() -> NodePointer;

  auto toplevel() -> NodePointer;

  // The parse() method should be virtual cause in the future we may want to
  // have different dialects of AWX
  virtual auto parse() -> Ast;

  ~Parser();
};

#endif /* PARSER_H */
