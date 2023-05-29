#ifndef AWX_NODE_IO_REDIRECTION_HPP
#define AWX_NODE_IO_REDIRECTION_HPP

#include "../node_interface.hpp"

#include "io.hpp"


namespace node::io {
enum class RedirectionOp { READ, TRUNC, APPEND, PIPE };

class Redirection : public NodeInterface {
  private:
  RedirectionOp m_op;
  NodePtr m_left;
  NodePtr m_right;

  public:
  Redirection(RedirectionOp t_op, NodePtr&& t_left, NodePtr&& t_right);

  auto left() -> NodePtr&;
  auto right() -> NodePtr&;
  auto op() const -> RedirectionOp;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Redirection() override = default;
};
} // namespace node::io

#endif // AWX_NODE_IO_REDIRECTION_HPP
