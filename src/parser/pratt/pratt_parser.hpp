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
// Classes:
class PrattParser : public Parser {
  private:
  // Note that these come from a submodule
  binding::PrefixMap m_prefix;
  binding::InfixMap m_infix;
  binding::PostfixMap m_postfix;

  public:
  PrattParser(token::TokenStream&& t_tokenstream);

  // Print expressions:
  virtual auto non_unary_print_expr(int t_min_bp = 0) -> node::NodePtr;
  virtual auto unary_print_expr(int t_min_bp = 0) -> node::NodePtr;
  virtual auto print_expr(int t_min_bp = 0) -> node::NodePtr;

  // Regular expressions:
  virtual auto non_unary_expr() -> node::NodePtr;
  virtual auto unary_expr() -> node::NodePtr;
  virtual auto expr() -> node::NodePtr;

  virtual ~PrattParser() = default;
};
} // namespace parser::pratt

#endif // AWX_PARSER_PRATT_PRATT_PARSER_HPP
