#ifndef GETLINE_HPP
#define GETLINE_HPP

#include "../node_interface.hpp"

#include "io.hpp"


namespace node::io {
class Getline : public NodeInterface {
  private:
  NodePtr m_var;

  public:
  Getline(NodePtr&& t_var);

  auto var() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Getline() override = default;
};
} // namespace node::io

#endif // GETLINE_HPP
