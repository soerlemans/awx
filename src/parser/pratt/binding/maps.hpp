#ifndef AWX_PARSER_PRATT_BINDING_MAPS_HPP
#define AWX_PARSER_PRATT_BINDING_MAPS_HPP

// Local Includes:
#include "binding_map.hpp"


namespace parser::pratt::binding {
// BINDING_POWER(GROUPING, 25, 25);

// Classes:
//! This class is a map of prefix operator binding powers
class PrefixMap : BindingMap {
  public:
  PrefixMap()
  {

    // BINDING_POWER(FIELD_REFERENCE, 24, 24);
    // BINDING_POWER(PRE_CREMENT, 22, 22);
    // BINDING_POWER(UNARY_OP, 19, 19);
  }
};

//! This class is a map of prefix operator binding powers
class InfixMap : BindingMap {
  public:
  InfixMap()
  {
    // BINDING_POWER(EXPONENTATION, 21, 20);
    // BINDING_POWER(FACTOR, 17, 18);
    // BINDING_POWER(BINARY, 15, 16);
    // BINDING_POWER(STRING_CONCAT, 13, 14);
    // BINDING_POWER(COMPARISON, 12, 12);
    // BINDING_POWER(MATCH, 11, 11);
    // BINDING_POWER(ARRAY_MEMBERSHIP, 9, 10);
    // BINDING_POWER(AND, 7, 8);
    // BINDING_POWER(OR, 5, 6);
    // BINDING_POWER(CONDITIONAL, 4, 3);
    // BINDING_POWER(ASSIGNMENT, 2, 1);
  }
};

//! This class is a map of prefix operator binding powers
class PostfixMap : BindingMap {
  public:
  PostfixMap()
  {
    // BINDING_POWER(POST_CREMENT, 23, 23);
  }
};

} // namespace parser::pratt::binding

#endif // AWX_PARSER_PRATT_BINDING_MAPS_HPP
