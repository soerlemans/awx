#ifndef PRINT_H
#define PRINT_H

#include "../list.hpp"
#include "../node.hpp"

#include "io.hpp"


// TODO: Merge Print and Printf into one?
namespace nodes::io {
class Print : public Node {
  private:
  NodeListPtr m_params;

  public:
  Print(NodeListPtr&& t_params);

  virtual auto params() -> NodeListPtr&;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Print() override = default;
};
} // namespace nodes::io

#endif // PRINT_H
