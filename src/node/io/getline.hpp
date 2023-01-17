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

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Getline();
};
}; // namespace nodes::io

#endif // GETLINE_H
