#ifndef DELETE_H
#define DELETE_H

#include "../node.hpp"
#include "operators.hpp"


namespace nodes::operators {
class operators::Delete : public Node {
  private:
  NodePtr m_array;

  public:
  Delete(NodePtr&& t_array);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Delete();
};
} // namespace nodes::operators

#endif // DELETE_H
