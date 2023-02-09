#ifndef GETLINE_H
#define GETLINE_H

#include "../node.hpp"

#include "io.hpp"


namespace nodes::io {
class Getline : public Node {
  private:
  NodePtr m_var;

  public:
  Getline(NodePtr&& t_var);

  auto var() -> NodePtr&;
  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  ~Getline() override = default;
};
} // namespace nodes::io

#endif // GETLINE_H
