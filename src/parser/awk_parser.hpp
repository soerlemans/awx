#ifndef AWK_PARSER_H
#define AWK_PARSER_H

#include <functional>

#include "parser.hpp"


// TODO: Some day split the Parser into different components that can be
// Individually extended and changed as of now its all put together into the
// Same file

// Forward declarations:
class AwkParser;

// Aliases:
// Used for functions that need to have different parsing rules dependent on
// Context
using ParserFunc = std::function<NodePtr()>;

// Classes:
class AwkParser : public Parser {
  private:
  public:
  // Constructors:
  AwkParser(TokenStream t_tokenstream);

  // Parsing grammar/rule methods:
  virtual auto newline_opt() -> void;

  // Input rules:
  virtual auto simple_get() -> NodePtr;
  virtual auto unary_input_function() -> NodePtr;
  virtual auto non_unary_input_function() -> NodePtr;

  virtual auto lvalue() -> NodePtr;

  // Function expression handlers:
  virtual auto function() -> NodePtr;
  virtual auto function_call() -> NodePtr;

  // Binary expression handlers:
  // TODO: Maybe replace the switch cases in these functions with macros?
  // TODO: Implement shunting yard algorithm for binary_operators
  virtual auto ere(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr;
  virtual auto arithmetic(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr;
  virtual auto assignment(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr;
  virtual auto comparison(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr;
  virtual auto logical(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr;
  virtual auto ternary(NodePtr& t_lhs, const ParserFunc& t_rhs) -> NodePtr;
  virtual auto binary_operator(NodePtr& t_lhs, const ParserFunc& t_rhs)
    -> NodePtr;

  // Print rules:
  virtual auto non_unary_print_expr() -> NodePtr;
  virtual auto unary_print_expr() -> NodePtr;
  virtual auto print_expr() -> NodePtr;
  virtual auto print_expr_list() -> NodeListPtr;
  virtual auto print_expr_list_opt() -> NodeListPtr;

  // Expression rules:
  virtual auto non_unary_expr() -> NodePtr;
  virtual auto unary_expr() -> NodePtr;

  virtual auto expr() -> NodePtr;
  virtual auto expr_opt() -> NodePtr;

  virtual auto multiple_expr_list() -> NodeListPtr;
  virtual auto expr_list() -> NodePtr;
  virtual auto expr_list_opt() -> NodePtr;

  // IO rules:
  virtual auto output_redirection() -> NodePtr;
  virtual auto simple_print_statement() -> NodePtr;
  virtual auto print_statement() -> NodePtr;

  // Statement rules:
  virtual auto simple_statement() -> NodePtr;
  virtual auto simple_statement_opt() -> NodePtr;

  virtual auto terminatable_statement() -> NodePtr;
  virtual auto unterminated_statement() -> NodePtr;
  virtual auto terminated_statement() -> NodePtr;
  virtual auto unterminated_statement_list() -> NodePtr;
  virtual auto terminated_statement_list() -> NodePtr;

  virtual auto terminator() -> void;

  virtual auto action() -> NodePtr;

  // Patterns:
  virtual auto special_pattern() -> NodePtr;
  virtual auto normal_pattern() -> NodePtr;
  virtual auto pattern() -> NodePtr;

  virtual auto param_list() -> NodePtr;
  virtual auto param_list_opt() -> NodePtr;

  virtual auto item() -> NodePtr;
  virtual auto item_list() -> NodePtr;

  virtual auto program() -> NodePtr;

  virtual auto parse() -> Ast override;

  // Desstructors:
  virtual ~AwkParser();
};

#endif // AWK_PARSER_H
