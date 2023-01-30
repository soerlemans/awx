#ifndef PRINTF_H
#define PRINTF_H

#include "../node.hpp"
#include "../list.hpp"

#include "io.hpp"


namespace nodes::io {
class Printf : public Node {
  private:
  NodeListPtr m_params;

  public:
  Printf(NodeListPtr&& t_params);

  virtual auto params() -> NodeListPtr&;

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Printf();
};
} // namespace nodes::io

#endif // PRINTF_H
