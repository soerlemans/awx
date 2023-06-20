#ifndef AWX_PARSER_AWK_AWK_PARSER_HPP
#define AWX_PARSER_AWK_AWK_PARSER_HPP

// Local Includes:
#include "../parser.hpp"
#include "../pratt/pratt_parser.hpp"


namespace parser::awk {
// TODO: Some day split the Parser into different components that can be
// Individually extended and changed as of now its all put together into the
// Same file

// Classes:
//! Top down parser for POSIX AWK. Grammar can be found in awk.yy file.
class AwkParser : public pratt::PrattParser {
  public:
  // Constructors:
  AwkParser(token::TokenStream t_tokenstream);

  // Parsing grammar/rule methods:
  // Input rules:
  virtual auto simple_get() -> node::NodePtr;
  virtual auto unary_input_function() -> node::NodePtr;
  virtual auto non_unary_input_function() -> node::NodePtr;

  // Function expression handlers:
  virtual auto function() -> node::NodePtr;

  // TODO: Add Control statement helper function
  virtual auto loop(const ParserFunc& t_body) -> node::NodePtr;

  // Expression rules:
  virtual auto print_expr_list() -> node::NodeListPtr;
  virtual auto print_expr_list_opt() -> node::NodeListPtr;
  virtual auto expr_opt() -> node::NodePtr;

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
} // namespace parser::awk

#endif // AWX_PARSER_AWK_AWK_PARSER_HPP
