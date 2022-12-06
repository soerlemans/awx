#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <list>
#include <type_traits>

#include "token.hpp"
#include "tokentype.hpp"


// Forward declarations:
class Expression;

// Concepts:
template<typename T>
concept ExpressionChild = std::is_base_of<Expression, T>::value;

// Aliases:
using ExpressionPointer = std::unique_ptr<Expression>;
using ExpressionList = std::list<std::unique_ptr<Expression>>;

class Expression {
protected:
  TokenType m_tokentype;
  ExpressionPointer m_left;

public:
  explicit Expression(TokenType t_tokentype);

  template<ExpressionChild T>
  explicit Expression(TokenType t_tokentype, T&& t_expr);

  explicit Expression(Token t_token);

  auto tokentype() -> TokenType;
  virtual auto left() -> Expression&;
  // virtual auto left(Expression& t_expr) -> void;

  virtual auto right() -> Expression& = 0;
  virtual auto list() -> ExpressionList = 0;

  virtual ~Expression();
};

#endif // EXPRESSION_H
