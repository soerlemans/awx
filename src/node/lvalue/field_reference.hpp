#ifndef FIELD_REFERENCE_HPP
#define FIELD_REFERENCE_HPP

#include "../node_interface.hpp"


namespace node::lvalue {
class FieldReference : public NodeInterface {
  private:
  NodePtr m_expr;

  public:
  FieldReference(NodePtr&& t_expr);

  auto expr() -> NodePtr&;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~FieldReference() override = default;
};
} // namespace node::lvalue

#endif // FIELD_REFERENCE_HPP
