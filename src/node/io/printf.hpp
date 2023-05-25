#ifndef AWX_NODE_IO_PRINTF_HPP
#define AWX_NODE_IO_PRINTF_HPP

// Includes:
#include "../list.hpp"
#include "../node_interface.hpp"

// Local Includes:
#include "io.hpp"


namespace node::io {
class Printf : public NodeInterface {
  private:
  NodePtr m_format;
  NodeListPtr m_params;

  public:
  Printf(NodePtr&& t_format, NodeListPtr&& t_params);

  virtual auto format() -> NodePtr&;
  virtual auto params() -> NodeListPtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Printf() override = default;
};
} // namespace node::io

#endif // AWX_NODE_IO_PRINTF_HPP
