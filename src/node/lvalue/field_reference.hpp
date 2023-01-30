#ifndef FIELD_REFERENCE_H
#define FIELD_REFERENCE_H

#include "../node.hpp"


namespace nodes::lvalue {
class FieldReference : public Node {
  private:
  NodePtr m_expr;

  public:
  FieldReference(NodePtr&& t_expr);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~FieldReference();
};
} // namespace nodes::lvalue

#endif // FIELD_REFERENCE_H
