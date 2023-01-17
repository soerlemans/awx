#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.hpp"

#include "ast.hpp"


// This is a recursive descent parser so each rule needs its own function
class Parser {
  private:
  TokenStream m_tokenstream;

  public:
  Parser(TokenStream&& t_tokenstream);

  // These are m_tokenstream helper methods:
  auto eos() -> bool;
  auto error(const std::string_view t_msg) -> void;

  auto check(const TokenType t_tokentype) -> bool;
  auto next() -> Token&;
  auto next_if(const TokenType t_tokentype) -> bool;
  auto prev() -> Token&;
  auto expect(const TokenType t_tokentype, const std::string t_msg) -> Token&;
  auto get_token() -> Token;

  // The parse() method should be virtual cause in the future we may want to
  // have different dialects of AWX
  virtual auto parse() -> Ast = 0;

  // Destructor:
  virtual ~Parser();
};

#endif /* PARSER_H */
