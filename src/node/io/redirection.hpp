#ifndef REDIRECTION_H
#define REDIRECTION_H

#include "../node.hpp"

#include "io.hpp"


namespace nodes::io {
enum class RedirectionOp { READ, TRUNC, APPEND, PIPE };

class Redirection : public Node {
  private:
  RedirectionOp m_op;
  NodePtr m_left;
  NodePtr m_right;

  public:
  Redirection(RedirectionOp t_op, NodePtr&& t_left, NodePtr&& t_right);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Redirection();
};
} // namespace nodes::io

#endif // REDIRECTION_H
