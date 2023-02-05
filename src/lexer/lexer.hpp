#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <string_view>
#include <tuple>

#include "../file_buffer.hpp"

#include "../token/reserved.hpp"
#include "../token/token_stream.hpp"


// Aliases:
// using TokenStream = std::vector<Token>;

class Lexer {
  private:
  FileBuffer& m_filebuffer;
  TokenStream m_tokenstream;

  // Token stream handling:
  // Create a token with its file_position
  template<typename... Args>
  auto create_token(Args&&... t_args) -> Token
  {
    static_assert(sizeof...(Args) <= 2,
                  "create_token(), does not accept more than two args.");

	auto file_pos{m_filebuffer.file_position()};

	// lineno are zero indexed
	// If we want it to print the correct line numbers we have to increment them
	file_pos.m_lineno++;

    return Token{std::forward<Args>(t_args)..., file_pos};
  }

  // Add token to token stream
  auto add_token(const Token& t_token) -> void;
  auto add_token(Token&& t_token) -> void;

  // Error handling:
  auto syntax_error(std::string_view t_msg) const -> void;

  public:
  Lexer() = delete;
  Lexer(FileBuffer& t_filebuffer);

  // Lexer functions:
  auto is_keyword(std::string_view t_identifier) -> TokenType;
  auto is_builtin_function(std::string_view t_identifier) -> TokenType;
  auto identifier() -> Token;

  auto is_hex_literal() -> bool;
  auto handle_hex() -> Token;
  auto handle_float(std::string_view t_str = "", bool t_dot = false) -> Token;
  auto handle_integer() -> Token;

  auto literal_numeric() -> Token;
  auto literal_string() -> Token;
  auto literal_regex() -> Token;

  auto is_multi_symbol() -> TokenType;
  auto is_single_symbol() -> TokenType;
  auto symbol() -> Token;

  auto next_char() const -> char;
  auto eol() const -> bool;

  auto tokenize() -> TokenStream;

  virtual ~Lexer();
};


#endif // TOKENIZER_H
