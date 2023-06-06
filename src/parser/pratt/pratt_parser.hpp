#ifndef AWX_PARSER_PRATT_PRATT_PARSER_HPP
#define AWX_PARSER_PRATT_PRATT_PARSER_HPP

// STL Includes:
#include <unordered_map>
#include <utility>

// Includes:
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

  int m_min_bp;

  public:
  PrattParser(token::TokenStream&& t_tokenstream);

  //! Expression that uses binding power
  virtual auto expr() -> node::NodePtr;

  virtual ~PrattParser() = default;
};
} // namespace parser::pratt

#endif // AWX_PARSER_PRATT_PRATT_PARSER_HPP
