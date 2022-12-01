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

// Classes:
class Tokenizer {
  private:
  FileBuffer& m_filebuffer;
  TokenStream m_tokenstream;

  // Tokenizer functions:
  auto is_hex() -> bool;
  auto is_float() -> bool;

  auto literal_numeric() -> void;
  auto literal_string() -> void;

  auto is_keyword(std::string_view t_identifier) -> TokenType;
  auto identifier() -> void;

  auto operator_logical() -> void;
  auto operator_mutable() -> void;
  auto operator_() -> void; // TODO: Find a beter name for this than operator_

  public:
  Tokenizer() = delete;
  Tokenizer(FileBuffer& t_filebuffer);

  auto tokenize() -> TokenStream;
  virtual ~Tokenizer();
};


#endif // TOKENIZER_H
