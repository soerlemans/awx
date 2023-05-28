#ifndef AWX_PARSER_AWK_PARSER_HPP
#define AWX_PARSER_AWK_PARSER_HPP

// STL Includes:
#include <functional>

// Local Includes:
#include "parser.hpp"


namespace parser {
// TODO: Some day split the Parser into different components that can be
// Individually extended and changed as of now its all put together into the
// Same file

// Forward declarations:
class AwkParser;

// Aliases:
//! Used for functions that need to have different parsing rules dependent on
//! Context
using ParserFunc = std::function<node::NodePtr()>;

// Classes:
//! Top down parser for POSIX AWK. Grammar can be found in awk.yy file.
class AwkParser : public Parser {
  public:
  // Constructors:
  AwkParser(token::TokenStream t_tokenstream);

  // Parsing grammar/rule methods:
  virtual auto newline_opt() -> void;

  // Input rules:
  virtual auto simple_get() -> node::NodePtr;
  virtual auto unary_input_function() -> node::NodePtr;
  virtual auto non_unary_input_function() -> node::NodePtr;

  virtual auto lvalue() -> node::NodePtr;

  // Function expression handlers:
  virtual auto function() -> node::NodePtr;
  virtual auto function_call() -> node::NodePtr;

  // Common expressions:
  // TODO: Maybe replace the switch cases in these functions with macros?
  // TODO: Implement shunting yard algorithm for binary_operators
  virtual auto match(node::NodePtr& t_lhs, const ParserFunc& t_rhs)
    -> node::NodePtr;
  virtual auto arithmetic(node::NodePtr& t_lhs, const ParserFunc& t_rhs)
    -> node::NodePtr;
  virtual auto assignment(node::NodePtr& t_lhs, const ParserFunc& t_rhs)
    -> node::NodePtr;
  virtual auto comparison(node::NodePtr& t_lhs, const ParserFunc& t_rhs)
    -> node::NodePtr;
  virtual auto membership(node::NodePtr& t_lhs) -> node::NodePtr;
  virtual auto logical(node::NodePtr& t_lhs, const ParserFunc& t_rhs)
    -> node::NodePtr;
  virtual auto ternary(node::NodePtr& t_lhs, const ParserFunc& t_rhs)
    -> node::NodePtr;

  // Universal expressions are common expressions shared by other rules
  virtual auto universal_print_expr(node::NodePtr& t_lhs,
                                    const ParserFunc& t_rhs) -> node::NodePtr;
  virtual auto universal_expr(node::NodePtr& t_lhs, const ParserFunc& t_rhs)
    -> node::NodePtr;

  // Non unary helper rules:
  virtual auto grouping() -> node::NodePtr;
  virtual auto negation(const ParserFunc& t_expr)
    -> node::NodePtr; // negation == not, !
  virtual auto literal() -> node::NodePtr;
  virtual auto prefix_operator() -> node::NodePtr;
  virtual auto universal_lvalue(node::NodePtr& t_lhs, const ParserFunc& t_rhs)
    -> node::NodePtr;

  // Unary helper rules:
  virtual auto unary_prefix(const ParserFunc& t_rhs) -> node::NodePtr;

  // TODO: Add Control statement helper function
  virtual auto loop(const ParserFunc& t_body) -> node::NodePtr;

  // Print rules:
  virtual auto non_unary_print_expr() -> node::NodePtr;
  virtual auto unary_print_expr() -> node::NodePtr;
  virtual auto print_expr() -> node::NodePtr;
  virtual auto print_expr_list() -> node::NodeListPtr;
  virtual auto print_expr_list_opt() -> node::NodeListPtr;

  // Expression rules:
  virtual auto non_unary_expr() -> node::NodePtr;
  virtual auto unary_expr() -> node::NodePtr;

  virtual auto expr() -> node::NodePtr;
  virtual auto expr_opt() -> node::NodePtr;

  virtual auto multiple_expr_list() -> node::NodeListPtr;
  virtual auto expr_list() -> node::NodeListPtr;
  virtual auto expr_list_opt() -> node::NodeListPtr;

  // IO rules:
  virtual auto output_redirection(node::NodePtr& t_lhs) -> node::NodePtr;
  virtual auto simple_print_statement() -> node::NodePtr;
  virtual auto print_statement() -> node::NodePtr;

  // Statement rules:
  virtual auto simple_statement() -> node::NodePtr;
  virtual auto simple_statement_opt() -> node::NodePtr;

  virtual auto terminatable_statement() -> node::NodePtr;
  virtual auto unterminated_statement() -> node::NodePtr;
  virtual auto terminated_statement() -> node::NodePtr;

  virtual auto unterminated_statement_list() -> node::NodeListPtr;
  virtual auto terminated_statement_list() -> node::NodeListPtr;

  virtual auto terminator() -> void;

  virtual auto action() -> node::NodeListPtr;

  // Patterns:
  virtual auto special_pattern() -> node::NodePtr;
  virtual auto normal_pattern() -> node::NodeListPtr;
  virtual auto pattern() -> node::NodePtr;

  virtual auto param_list() -> node::NodeListPtr;
  virtual auto param_list_opt() -> node::NodeListPtr;

  virtual auto item() -> node::NodePtr;
  virtual auto item_list() -> node::NodeListPtr;

  virtual auto program() -> node::NodeListPtr;

  auto parse() -> node::NodePtr override;

  // Desstructors:
  ~AwkParser() override = default;
};
} // namespace parser

#endif // AWX_PARSER_AWK_PARSER_HPP
