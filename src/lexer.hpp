#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <string_view>
#include <tuple>
#include <variant>

#include "filebuffer.hpp"
#include "reserved.hpp"
#include "token.hpp"


// Aliases:
using TokenStream = std::vector<Token>;

class Lexer {
private:
  FileBuffer& m_filebuffer;
  TokenStream m_tokenstream;

  // TokenStream handling:
  auto add_token(const Token&& t_token) -> void;

  // Error handling:
  auto syntax_error(std::string_view t_msg) const -> void;

  // Lexer functions:
  auto check_hex() -> bool;
  auto literal_numeric() -> Token;
  auto literal_string() -> Token;

  auto is_keyword(std::string_view t_identifier) -> TokenType;
  auto identifier() -> Token;

  auto symbol() -> Token;

public:
  Lexer() = delete;
  Lexer(FileBuffer& t_filebuffer);

  auto tokenize() -> TokenStream;

  virtual ~Lexer();
};


#endif // TOKENIZER_H
