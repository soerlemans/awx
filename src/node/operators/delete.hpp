#ifndef DELETE_H
#define DELETE_H

#include "../node.hpp"
#include "operators.hpp"


namespace nodes::operators {
class Delete : public Node {
  private:
  NodePtr m_array;

  public:
  Delete(NodePtr&& t_array);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  ~Delete() override = default;
};
} // namespace nodes::operators

#endif // DELETE_H
