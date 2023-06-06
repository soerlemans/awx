#include "pratt_parser.hpp"


using namespace parser::pratt;

// Macros:
#define BINDING_POWER(t_precedence, t_lbp, t_rbp) \
  case Precedence::t_precedence:                  \
    return BindingPower{t_lbp, t_rbp};

// Methods:
PrattParser::PrattParser(token::TokenStream&& t_tokenstream)
  : Parser{std::move(t_tokenstream)}
{}


auto PrattParser::expr_bp() -> node::NodePtr
{}
