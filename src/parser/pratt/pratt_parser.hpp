#ifndef AWX_PARSER_PRATT_PRATT_PARSER_HPP
#define AWX_PARSER_PRATT_PRATT_PARSER_HPP

// STL Includes:
#include <unordered_map>
#include <utility>

// Includes:
#include "../../types.hpp"
#include "../parser.hpp"
#include "binding/maps.hpp"


namespace parser::pratt {
// Aliases:
//! Pratt parsers use precedence climbing, so we must pass an int parameter
using PrattFunc = std::function<node::NodePtr(token::TokenType)>;

// Classes:
class PrattParser : public Parser {
  private:
  // Note that these come from a submodule
  binding::PrefixMap m_prefix;
  binding::InfixMap m_infix;
  binding::PostfixMap m_postfix;

  public:
  PrattParser(token::TokenStream&& t_tokenstream);

  virtual auto newline_opt() -> void;

  virtual auto lvalue() -> node::NodePtr;

  // Helper methods:
  virtual auto grouping() -> node::NodePtr;
  virtual auto negation(const ParserFunc& t_expr) -> node::NodePtr;
  virtual auto literal() -> node::NodePtr;

  // Expression helpers:
  virtual auto arithmetic(node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> node::NodePtr;
  virtual auto logical(node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> node::NodePtr;

  virtual auto universal_expr(node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> node::NodePtr;

  // Print expressions:
  virtual auto non_unary_print_expr(int t_min_bp = 0) -> node::NodePtr;
  virtual auto unary_print_expr(int t_min_bp = 0) -> node::NodePtr;
  virtual auto print_expr(int t_min_bp = 0) -> node::NodePtr;

  // Expressions:
  virtual auto non_unary_expr() -> node::NodePtr;
  virtual auto unary_expr() -> node::NodePtr;
  virtual auto expr() -> node::NodePtr;

  virtual auto multiple_expr_list() -> node::NodeListPtr;
  virtual auto expr_list() -> node::NodeListPtr;

  virtual ~PrattParser() = default;
};
} // namespace parser::pratt

#endif // AWX_PARSER_PRATT_PRATT_PARSER_HPP
