#include "pratt_parser.hpp"


using namespace parser;

// Macros:
#define BINDING_POWER(t_precedence, t_lbp, t_rbp) \
  case Precedence::t_precedence:                  \
    return BindingPower{t_lbp, t_rbp};

// Methods:
auto PrattParser::infix_binding_power(Precedence t_prec) const -> BindingPower
{
  switch(t_prec) {
    BINDING_POWER(GROUPING, 25, 25);
    BINDING_POWER(FIELD_REFERENCE, 24, 24);
    BINDING_POWER(POST_CREMENT, 23, 23);
    BINDING_POWER(PRE_CREMENT, 22, 22);
    BINDING_POWER(EXPONENTATION, 21, 20);
    BINDING_POWER(UNARY_OP, 19, 19);
    BINDING_POWER(FACTOR, 17, 18);
    BINDING_POWER(BINARY, 15, 16);
    BINDING_POWER(STRING_CONCAT, 13, 14);
    BINDING_POWER(COMPARISON, 12, 12);
    BINDING_POWER(MATCH, 11, 11);
    BINDING_POWER(ARRAY_MEMBERSHIP, 9, 10);
    BINDING_POWER(AND, 7, 8);
    BINDING_POWER(OR, 5, 6);
    BINDING_POWER(CONDITIONAL, 4, 3);
    BINDING_POWER(ASSIGNMENT, 2, 1);

    default:
      // TODO: Error handle
      break;
  }
}

auto PrattParser::infix_binding_power(const token::TokenType t_type) const
  -> BindingPower
{
  using namespace token;

  // Convert the TokenType to a Precedence
  infix_binding_power(tokentype2precedence(t_type));
}
