#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <tuple>
#include <variant>

#include "filebuffer.hpp"
#include "token.hpp"

class Tokenizer {
private:
  FileBuffer m_filebuffer;

public:
  Tokenizer() = delete;
  Tokenizer(FileBuffer&& t_filebuffer);

  auto tokenize() -> void;

  virtual ~Tokenizer();
};

#endif // TOKENIZER_H
