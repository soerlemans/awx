#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.hpp"

#include "ast.hpp"


// TOOD: Create constexpr functions for verifying the grammar
// Like is_rvalue or is_lvalue
class Parser {
  private:
  TokenStream m_token_stream;

  public:
  Parser(TokenStream t_token_stream);

  // Helpers:
  virtual auto function() -> NodePointer;

  virtual auto identifier() -> NodePointer;
  virtual auto literal() -> NodePointer;

  virtual auto condition() -> NodePointer;

  // Body contains execution body and actual statements
  virtual auto body() -> NodePointer;

  virtual auto toplevel() -> NodePointer;

  // The parse() method should be virtual cause in the future we may want to
  // have different dialects of AWX
  virtual auto parse() -> Ast;

  ~Parser();
};

#endif /* PARSER_H */
