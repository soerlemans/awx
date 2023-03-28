#ifndef PARSER_HPP
#define PARSER_HPP

// Includes:
#include "../lexer/lexer.hpp"
#include "../node/node.hpp"


/*! Abstract parser class provides utilities that a parser would need to
 * implement
 */
class Parser {
  private:
  token::TokenStream m_tokenstream;

  protected:
  // These are m_tokenstream helper methods:
  auto eos() -> bool;
  auto error(std::string_view t_msg) -> void;

  auto check(TokenType t_tokentype) -> bool;
  auto next() -> token::Token&;
  auto next_if(TokenType t_tokentype) -> bool;
  auto prev() -> token::Token&;
  auto expect(TokenType t_tokentype, std::string_view t_msg) -> token::Token&;
  auto get_token() -> token::Token;

  public:
  Parser(token::TokenStream&& t_tokenstream);

  // The parse() method should be virtual cause in the future we may want to
  // have different dialects of AWX
  virtual auto parse() -> node::NodePtr = 0;

  // Destructor:
  virtual ~Parser() = default;
};

#endif /* PARSER_H */
