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
  virtual auto special_pattern() -> NodePointer;
  virtual auto normal_pattern() -> NodePointer;
  virtual auto pattern() -> NodePointer;

  virtual auto param_list() -> NodePointer;
  virtual auto param_list_opt() -> NodePointer;

  virtual auto item() -> NodePointer;
  virtual auto item_list() -> NodePointer;

  virtual auto program() -> NodePointer;

  auto next_token() -> Token&;

  // The parse() method should be virtual cause in the future we may want to
  // have different dialects of AWX
  virtual auto parse() -> Ast;

  ~Parser();
};

#endif /* PARSER_H */
