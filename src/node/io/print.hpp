#ifndef PRINT_H
#define PRINT_H

#include "../node.hpp"

#include "io.hpp"


// TODO: Merge Print and Printf into one?
namespace nodes::io {
class Print : public Node {
  private:
  NodePtr m_expr;

  public:
  Print(NodePtr&& t_expr);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Print();
};
}; // namespace nodes::io

#endif // PRINT_H
