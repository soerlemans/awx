#ifndef OPERATOR_PARSER_H
#define OPERATOR_PARSER_H

#include "parser.hpp"


class OperatorParser : public Parser {
  private:
  public:
  OperatorParser();

  // These are pure virtual since they are expected to be defined in derived
  // parsers
  virtual auto expr() -> NodePtr = 0;
  virtual auto newline_opt() -> void = 0;

  // These are general rules that probably wont change across different grammars
  virtual auto string_concatenation(NodePtr& t_lhs) -> NodePtr;
  virtual auto ere(NodePtr& t_lhs) -> NodePtr;
  virtual auto arithmetic(NodePtr& t_lhs) -> NodePtr;
  virtual auto comparison(NodePtr& t_lhs) -> NodePtr;
  virtual auto logical(NodePtr& t_lhs) -> NodePtr;
  virtual auto ternary(NodePtr& t_lhs) -> NodePtr;
  virtual auto binary_operator(NodePtr& t_lhs) -> NodePtr;

  virtual ~OperatorParser();
};

#endif // OPERATOR_PARSER_H
