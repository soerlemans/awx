#ifndef NIL_H
#define NIL_H

#include "node.hpp"


namespace nodes {
class Nil : public Node {
  private:
  public:
  virtual auto accept(NodeVisitor* t_visitor) -> void;

  virtual ~Nil() = default;
};
} // namespace nodes

#endif // NIL_H
