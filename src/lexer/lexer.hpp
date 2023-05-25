#ifndef AWX_LEXER_LEXER_HPP
#define AWX_LEXER_LEXER_HPP

// STL Includes:
#include <string>
#include <string_view>
#include <tuple>

// Includes:
#include "../file_buffer.hpp"
#include "../token/reserved.hpp"
#include "../token/token.hpp"


namespace lexer {
class Lexer {
  private:
  FileBuffer& m_fb;
  token::TokenStream m_ts;

  // Token stream handling:
  // Create a token with its file_position
  template<typename... Args>
  auto create_token(Args&&... t_args) -> token::Token
  {
    return token::Token{std::forward<Args>(t_args)..., m_fb.file_position()};
  }

  // Error handling:
  auto syntax_error(std::string_view t_msg) const -> void;

  public:
  Lexer(FileBuffer& t_fb);

  // Name lexing:
  static auto is_keyword(std::string_view t_identifier) -> token::TokenType;
  static auto is_builtin_function(std::string_view t_identifier)
    -> token::TokenType;
  auto identifier() -> token::Token;

  // Integer literal lexing:
  auto is_hex_literal() -> bool;
  auto handle_hex() -> token::Token;
  auto handle_float(std::string_view t_str = "", bool t_dot = false)
    -> token::Token;
  auto handle_integer() -> token::Token;

  // Literal lexing:
  auto literal_numeric() -> token::Token;
  auto literal_string() -> token::Token;
  auto literal_regex() -> token::Token;

  // Symbol lexing:
  auto is_multi_symbol() -> token::TokenType;
  auto is_single_symbol() -> token::TokenType;
  auto symbol() -> token::Token;

  auto tokenize() -> token::TokenStream;

  virtual ~Lexer() = default;
};
} // namespace lexer

#endif // AWX_LEXER_LEXER_HPP
