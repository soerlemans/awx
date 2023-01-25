#ifndef PIPE_H
#define PIPE_H

#include "../node.hpp"

#include "io.hpp"


namespace nodes::io {
class Pipe : public Node {
  private:
  NodePtr m_expr;
  NodePtr m_getline;

  public:
  Pipe(NodePtr&& t_expr, NodePtr&& t_getline);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Pipe();
};
}; // namespace nodes::io

#endif // PIPE_H
