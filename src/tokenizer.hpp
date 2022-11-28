#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <tuple>
#include <variant>

#include "filebuffer.hpp"
#include "token.hpp"


using TokenStream = std::vector<Token>;

class Tokenizer {
private:
  FileBuffer& m_filebuffer;

  // Tokenizer functions:
  auto single_character() -> void;

  auto literal_numeric() -> void;
  auto literal_string() -> void;

  auto keyword() -> void;
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
