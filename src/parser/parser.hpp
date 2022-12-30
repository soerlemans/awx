#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.hpp"

#include "ast.hpp"


// TOOD: Create constexpr functions for verifying the grammar
// Like is_rvalue or is_lvalue
class Parser
{
  private:
  TokenStream m_tokenstream;

  public:
  Parser(TokenStream t_tokenstream);

  // Non-terminals:
  virtual auto action() -> NodePtr;
  virtual auto special_pattern() -> NodePtr;
  virtual auto normal_pattern() -> NodePtr;
  virtual auto pattern() -> NodePtr;

  virtual auto param_list() -> NodePtr;
  virtual auto param_list_opt() -> NodePtr;

  virtual auto item() -> NodePtr;
  virtual auto item_list() -> NodePtr;

  virtual auto program() -> NodePtr;

  auto next_token() -> Token&;

  // The parse() method should be virtual cause in the future we may want to
  // have different dialects of AWX
  virtual auto parse() -> Ast;

  ~Parser();
};

#endif /* PARSER_H */
