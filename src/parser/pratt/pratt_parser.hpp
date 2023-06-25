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
//! This type is used to get the right hand side of a binary expressions
using PrattFunc = std::function<node::NodePtr(token::TokenType)>;
//! This type takes the binding power
using BpFunc = std::function<node::NodePtr(int)>;
//! This type is used to parse extra infix operations of a universal method
using InfixFunc =
  std::function<node::NodePtr(node::NodePtr&, const PrattFunc&)>;

// Classes:
class PrattParser : public Parser {
  private:
  // Note that these come from a submodule
  binding::PrefixMap m_prefix;
  binding::InfixMap m_infix;
  binding::PostfixMap m_postfix;

  public:
  PrattParser(token::TokenStream&& t_tokenstream);

  // Expression terminals:
  virtual auto unary_prefix(const PrattFunc& t_fn) -> node::NodePtr;
  virtual auto grouping() -> node::NodePtr;
  virtual auto negation(const PrattFunc& t_expr) -> node::NodePtr;
  virtual auto literal() -> node::NodePtr;
  virtual auto lvalue() -> node::NodePtr;

  virtual auto postcrement(node::NodePtr& t_lhs) -> node::NodePtr;
  virtual auto precrement() -> node::NodePtr;

  virtual auto function_call() -> node::NodePtr;

  // Infix parsing:
  virtual auto arithmetic(node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> node::NodePtr;
  virtual auto match(node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> node::NodePtr;
  virtual auto membership(node::NodePtr& t_lhs) -> node::NodePtr;
  virtual auto logical(node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> node::NodePtr;
  virtual auto assignment(node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> node::NodePtr;
  virtual auto ternary(node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> node::NodePtr;
  virtual auto comparison(node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> node::NodePtr;
  virtual auto string_concat(node::NodePtr& t_lhs, const BpFunc& t_rhs,
                             int t_min_bp) -> node::NodePtr;

  virtual auto universal_infix(node::NodePtr& t_lhs, const PrattFunc& t_fn)
    -> node::NodePtr;

  // Universal expression parsers:
  virtual auto universal_non_unary_expr(const BpFunc& t_expr_fn,
                                        const InfixFunc& t_infix_fn,
                                        int t_min_bp = 0) -> node::NodePtr;
  virtual auto universal_unary_expr(const BpFunc& t_expr_fn,
                                    const InfixFunc& t_infix_fn,
                                    int t_min_bp = 0) -> node::NodePtr;

  // Grammar:
  virtual auto newline_opt() -> void = 0;

  virtual auto non_unary_input_function() -> node::NodePtr = 0;

  // Print expressions:
  virtual auto non_unary_print_expr(int t_min_bp = 0) -> node::NodePtr;
  virtual auto unary_print_expr(int t_min_bp = 0) -> node::NodePtr;
  virtual auto print_expr(int t_min_bp = 0) -> node::NodePtr;

  // Expressions:
  virtual auto non_unary_expr(int t_min_bp = 0) -> node::NodePtr;
  virtual auto unary_expr(int t_min_bp = 0) -> node::NodePtr;
  virtual auto expr(int t_min_bp = 0) -> node::NodePtr;

  virtual auto multiple_expr_list() -> node::NodeListPtr = 0;
  virtual auto expr_list() -> node::NodeListPtr = 0;
  virtual auto expr_list_opt() -> node::NodeListPtr = 0;

  virtual ~PrattParser() = default;
};
} // namespace parser::pratt

#endif // AWX_PARSER_PRATT_PRATT_PARSER_HPP
