#ifndef PARSER_HPP
#define PARSER_HPP

#include "../lexer/lexer.hpp"

#include "ast.hpp"

/*! Abstract parser class provides utilities that a parser would need to
 * implement
 */
class Parser {
  private:
  TokenStream m_tokenstream;

  protected:
  // These are m_tokenstream helper methods:
  auto eos() -> bool;
  auto error(std::string_view t_msg) -> void;

  auto check(TokenType t_tokentype) -> bool;
  auto next() -> Token&;
  auto next_if(TokenType t_tokentype) -> bool;
  auto prev() -> Token&;
  auto expect(TokenType t_tokentype, std::string_view t_msg) -> Token&;
  auto get_token() -> Token;

  public:
  Parser(TokenStream&& t_tokenstream);

  // The parse() method should be virtual cause in the future we may want to
  // have different dialects of AWX
  virtual auto parse() -> Ast = 0;

  // Destructor:
  virtual ~Parser() = default;
};

#endif /* PARSER_H */
