#ifndef LEXER_HPP
#define LEXER_HPP

// STL Includes:
#include <string>
#include <string_view>
#include <tuple>

// Includes:
#include "../file_stream.hpp"
#include "../token/reserved.hpp"
#include "../token/token.hpp"


namespace lexer {
class Lexer {
  private:
  FileStream& m_fs;
  token::TokenStream m_ts;

  // Token stream handling:
  // Create a token with its file_position
  template<typename... Args>
  auto create_token(Args&&... t_args) -> token::Token
  {
    // static_assert(sizeof...(Args) <= 2,
    //               "create_token(), does not accept more than two args.");

    // return token::Token{std::forward<Args>(t_args)...,
    // 										m_ts.file_position()};
  }

  // Error handling:
  auto syntax_error(std::string_view t_msg) const -> void;

  public:
  Lexer(FileStream& t_filestream);

  // Lexer functions:
  static auto is_keyword(std::string_view t_identifier) -> token::TokenType;
  static auto is_builtin_function(std::string_view t_identifier)
    -> token::TokenType;
  auto identifier() -> token::Token;

  auto is_hex_literal() -> bool;
  auto handle_hex() -> token::Token;
  auto handle_float(std::string_view t_str = "", bool t_dot = false)
    -> token::Token;
  auto handle_integer() -> token::Token;

  auto literal_numeric() -> token::Token;
  auto literal_string() -> token::Token;
  auto literal_regex() -> token::Token;

  auto is_multi_symbol() -> token::TokenType;
  auto is_single_symbol() -> token::TokenType;
  auto symbol() -> token::Token;

  auto next_char() const -> char;
  auto eol() const -> bool;

  auto tokenize() -> token::TokenStream;

  virtual ~Lexer() = default;
};
} // namespace lexer

#endif // LEXER_HPP
