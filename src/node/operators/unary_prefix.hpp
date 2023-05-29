#ifndef AWX_NODE_OPERATORS_UNARY_PREFIX_HPP
#define AWX_NODE_OPERATORS_UNARY_PREFIX_HPP

#include "../../token/token_type.hpp"

#include "operators.hpp"
#include "unary_operator.hpp"


namespace node::operators {
// Enums:
enum class UnaryPrefixOp { PLUS, MINUS };

// Classes:
class UnaryPrefix : public UnaryOperator {
  private:
  UnaryPrefixOp m_op;

  public:
  UnaryPrefix(UnaryPrefixOp t_op, NodePtr&& t_left);
  UnaryPrefix(token::TokenType t_tokentype, NodePtr&& t_left);

  virtual auto op() const -> UnaryPrefixOp;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~UnaryPrefix() override = default;
};
} // namespace node::operators

#endif // AWX_NODE_OPERATORS_UNARY_PREFIX_HPP
