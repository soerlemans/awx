#ifndef PRINTF_H
#define PRINTF_H

#include "../node.hpp"

#include "io.hpp"


namespace nodes::io {
class Printf : public Node {
  private:
  NodePtr m_expr;

  public:
  Printf(NodePtr&& t_expr);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Printf();
};
}; // namespace nodes::io

#endif // PRINTF_H
