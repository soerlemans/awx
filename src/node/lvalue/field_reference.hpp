#ifndef AWX_NODE_LVALUE_FIELD_REFERENCE_HPP
#define AWX_NODE_LVALUE_FIELD_REFERENCE_HPP

#include "../node_interface.hpp"


namespace node::lvalue {
class FieldReference : public NodeInterface {
  private:
  NodePtr m_expr;

  public:
  FieldReference(NodePtr&& t_expr);

  auto expr() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~FieldReference() override = default;
};
} // namespace node::lvalue

#endif // AWX_NODE_LVALUE_FIELD_REFERENCE_HPP
