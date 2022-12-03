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

class Tokenizer {
private:
  FileBuffer& m_filebuffer;
  TokenStream m_tokenstream;

  // TokenStream handling:
  auto add_token(const Token&& t_token) -> void;

  // Error handling:
  auto syntax_error(std::string_view t_msg) const -> void;

  // Tokenizer functions:
  auto check_hex() -> bool;
  auto literal_numeric() -> void;
  auto literal_string() -> void;

  auto is_keyword(std::string_view t_identifier) -> TokenType;
  auto identifier() -> void;

  auto symbol() -> void;

public:
  Tokenizer() = delete;
  Tokenizer(FileBuffer& t_filebuffer);

  auto tokenize() -> TokenStream;

  virtual ~Tokenizer();
};


#endif // TOKENIZER_H
