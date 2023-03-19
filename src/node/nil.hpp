#ifndef NIL_HPP
#define NIL_HPP

#include "node_interface.hpp"


namespace node {
class Nil : public NodeInterface {
  private:
  public:
  virtual auto accept(visitor::NodeVisitor* t_visitor) -> void;

  virtual ~Nil() = default;
};
} // namespace node

#endif // NIL_HPP
