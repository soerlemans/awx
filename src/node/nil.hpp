#ifndef NIL_HPP
#define NIL_HPP

#include "node_interface.hpp"


namespace nodes {
class Nil : public NodeInterface {
  private:
  public:
  virtual auto accept(NodeVisitor* t_visitor) -> void;

  virtual ~Nil() = default;
};
} // namespace nodes

#endif // NIL_HPP
