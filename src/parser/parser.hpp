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

  // Parsing rule functions:
  virtual auto newline_opt() -> NodePtr;
  virtual auto simple_get() -> NodePtr;

  virtual auto unary_input_function() -> NodePtr;
  virtual auto non_unary_input_function() -> NodePtr;

  virtual auto lvalue() -> NodePtr;
  virtual auto non_unary_print_expr() -> NodePtr;
  virtual auto unary_print_expr() -> NodePtr;

  virtual auto print_expr() -> NodePtr;
  virtual auto print_expr_list() -> NodePtr;
  virtual auto print_expr_list_opt() -> NodePtr;

  virtual auto non_unary_expr() -> NodePtr;
  virtual auto unary_expr() -> NodePtr;

  virtual auto expr() -> NodePtr;
  virtual auto expr_opt() -> NodePtr;

  virtual auto multiple_expr_list() -> NodePtr;
  virtual auto expr_list() -> NodePtr;
  virtual auto expr_list_opt() -> NodePtr;

  virtual auto output_redirection() -> NodePtr;
  virtual auto simple_print_statement() -> NodePtr;
  virtual auto print_statement() -> NodePtr;

  virtual auto simple_statement() -> NodePtr;
  virtual auto simple_statement_opt() -> NodePtr;

  virtual auto terminatable_statement() -> NodePtr;
  virtual auto unterminated_statement() -> NodePtr;
  virtual auto terminated_statement() -> NodePtr;
  virtual auto unterminated_statement_list() -> NodePtr;
  virtual auto terminated_statement_list() -> NodePtr;

  virtual auto terminator() -> NodePtr;

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
