#ifndef UNARY_PREFIX_HPP
#define UNARY_PREFIX_HPP

#include "../../token/token_type.hpp"

#include "operators.hpp"
#include "unary_operator.hpp"


namespace nodes::operators {
// Enums:
enum class UnaryPrefixOp { PLUS, MINUS };

// Classes:
class UnaryPrefix : public UnaryOperator {
  private:
  UnaryPrefixOp m_op;

  public:
  UnaryPrefix(UnaryPrefixOp t_op, NodePtr&& t_left);
  UnaryPrefix(TokenType t_tokentype, NodePtr&& t_left);

  virtual auto op() const -> UnaryPrefixOp;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~UnaryPrefix() override = default;
};
} // namespace nodes::operators

#endif // UNARY_PREFIX_HPP
