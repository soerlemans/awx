#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <string_view>
#include <tuple>

#include "../file_buffer.hpp"

#include "reserved.hpp"
#include "token_stream.hpp"


// Aliases:
// using TokenStream = std::vector<Token>;

class Lexer {
private:
  FileBuffer& m_filebuffer;
  TokenStream m_tokenstream;

  // Token stream handling:
  auto add_token(Token&& t_token) -> void;

  // Error handling:
  auto syntax_error(std::string_view t_msg) const -> void;

public:
  Lexer() = delete;
  Lexer(FileBuffer& t_filebuffer);

  // Lexer functions:
  auto is_keyword(std::string_view t_identifier) -> TokenType;
  auto identifier() -> Token;

  auto is_hex_literal() -> bool;
  auto literal_numeric() -> Token;
  auto literal_string() -> Token;
  auto literal_regex() -> Token;

  auto is_multi_symbol() -> TokenType;
  auto is_single_symbol() -> TokenType;
  auto symbol() -> Token;

  auto tokenize() -> TokenStream;

  virtual ~Lexer();
};


#endif // TOKENIZER_H
