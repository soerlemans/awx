#ifndef REDIRECTION_HPP
#define REDIRECTION_HPP

#include "../node_interface.hpp"

#include "io.hpp"


namespace nodes::io {
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

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Redirection() override = default;
};
} // namespace nodes::io

#endif // REDIRECTION_HPP
