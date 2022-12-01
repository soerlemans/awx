#ifndef RESERVED_H
#define RESERVED_H

#include <string_view>

// TODO: If keywords ever need to be changed or reserved characters
// Change the namespaces into structs with a shared parent so different
// Syntaxes would be able to be dynamically swapped

// AWX reserved keywords and symbols
namespace reserved {

// Reserved shorthands of constexpr types
// Do not use outside of reserved namespace to avoid confusion
using r_ch = char;
using r_vw = std::string_view;

// Language reserved keywords
namespace keywords {
constexpr r_vw g_function{"function"};
constexpr r_vw g_if{"if"};
constexpr r_vw g_else{"else"};
constexpr r_vw g_do{"do"};
constexpr r_vw g_while{"while"};
constexpr r_vw g_for{"for"};
constexpr r_vw g_in{"in"};
}; // namespace keywords

// Language reserved symbols
namespace symbols {
// Braces
constexpr r_ch g_paren_open{'('};
constexpr r_ch g_paren_close{')'};
constexpr r_ch g_accolade_open{'{'};
constexpr r_ch g_accolade_close{'}'};
constexpr r_ch g_brace_open{'['};
constexpr r_ch g_brace_close{']'};

// String literal symbols
constexpr r_ch g_double_quote{'"'};

// Arithmetic operators
constexpr r_ch g_exponent{'^'};
constexpr r_ch g_plus{'+'};
constexpr r_ch g_minus{'-'};
constexpr r_ch g_multiplier{'*'};
constexpr r_ch g_divider{'/'};
constexpr r_ch g_modulus{'%'};

// Assignment variants of Arithmetic operators
// TODO: Rename or structure these better in the future?
constexpr r_vw g_exponent_assignment{"^="};
constexpr r_vw g_plus_assignment{"+="};
constexpr r_vw g_minus_assignment{"-="};
constexpr r_vw g_multiplier_assignment{"*="};
constexpr r_vw g_divider_assignment{"/="};
constexpr r_vw g_modulus_assignment{"%="};
constexpr r_ch g_assignment{'='};

// Regex operators
constexpr r_ch g_ere_match{'~'};
constexpr r_vw g_not_ere_match{"!~"};

// Logic operators
constexpr r_ch g_not{'!'};
constexpr r_ch g_less_than{'<'};
constexpr r_ch g_less_than_equal{'<'};

constexpr r_ch g_greater_than{'>'};
constexpr r_ch g_greater_than_equal{'>'};

// Control flow symbols
constexpr r_ch g_comma{','};
constexpr r_ch g_questionmark{'?'};
constexpr r_ch g_colon{':'};
constexpr r_ch g_semicolon{';'};

// Miscellaneous operators:
constexpr r_ch g_dollar_sign{'$'};
constexpr r_ch g_end_of_line{'\n'};
}; // namespace symbols
}; // namespace reserved

#endif // RESERVED_H
