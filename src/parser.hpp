#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.hpp"


class Parser {
private:
  TokenStream m_tokenstream;

public:
  Parser(TokenStream t_tokenstream);

  auto parse() -> void;

  ~Parser();
};

#endif /* PARSER_H */

