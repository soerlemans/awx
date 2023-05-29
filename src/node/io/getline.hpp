#ifndef AWX_NODE_IO_GETLINE_HPP
#define AWX_NODE_IO_GETLINE_HPP

#include "../node_interface.hpp"

#include "io.hpp"


namespace node::io {
class Getline : public NodeInterface {
  private:
  NodePtr m_var;

  public:
  Getline(NodePtr&& t_var);

  auto var() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Getline() override = default;
};
} // namespace node::io

#endif // AWX_NODE_IO_GETLINE_HPP
