#ifndef FIELD_REFERENCE_H
#define FIELD_REFERENCE_H

#include "../node.hpp"


namespace nodes::lvalue {
class FieldReference : public Node {
  private:
  NodePtr m_expr;

  public:
  FieldReference(NodePtr&& t_expr);

  auto expr() -> NodePtr&;

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  ~FieldReference() override = default;
};
} // namespace nodes::lvalue

#endif // FIELD_REFERENCE_H
