#ifndef PRINTF_H
#define PRINTF_H

#include "../list.hpp"
#include "../node.hpp"

#include "io.hpp"


namespace nodes::io {
class Printf : public Node {
  private:
  NodeListPtr m_params;

  public:
  Printf(NodeListPtr&& t_params);

  virtual auto params() -> NodeListPtr&;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Printf() override = default;
};
} // namespace nodes::io

#endif // PRINTF_H
