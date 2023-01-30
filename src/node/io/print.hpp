#ifndef PRINT_H
#define PRINT_H

#include "../node.hpp"
#include "../list.hpp"

#include "io.hpp"


// TODO: Merge Print and Printf into one?
namespace nodes::io {
class Print : public Node {
  private:
  NodeListPtr m_params;

  public:
  Print(NodeListPtr&& t_params);

  virtual auto params() -> NodeListPtr&;

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Print();
};
} // namespace nodes::io

#endif // PRINT_H
