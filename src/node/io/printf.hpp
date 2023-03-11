#ifndef PRINTF_HPP
#define PRINTF_HPP

#include "../list.hpp"
#include "../node_interface.hpp"

#include "io.hpp"


namespace node::io {
class Printf : public NodeInterface {
  private:
  NodeListPtr m_params;

  public:
  Printf(NodeListPtr&& t_params);

  virtual auto params() -> NodeListPtr&;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Printf() override = default;
};
} // namespace node::io

#endif // PRINTF_HPP
