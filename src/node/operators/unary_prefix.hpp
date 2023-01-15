#ifndef UNARY_PREFIX_H
#define UNARY_PREFIX_H

#include "../../token/token_type.hpp"

#include "operators.hpp"
#include "unary_operator.hpp"

// Enums:
enum class UnaryPrefixOp { PLUS, MINUS };

// Classes:
namespace nodes::operators {
class UnaryPrefix : public UnaryOperator {
  private:
  UnaryPrefixOp m_op;

  public:
  UnaryPrefix(UnaryPrefixOp t_op, NodePtr t_left);

  virtual auto op() const -> UnaryPrefixOp;

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~UnaryPrefix();
};

// Exported Functions:
namespace unary_prefix {
// Convert TokenType enum to matching UnaryPrefixOp token
auto tokentype2enum(const TokenType t_tokentype) -> UnaryPrefixOp;
}; // namespace unary_prefix
}; // namespace nodes::operators

#endif // UNARY_PREFIX_H
