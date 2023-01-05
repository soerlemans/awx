#ifndef DELETE_H
#define DELETE_H

#include "../node.hpp"
#include "operators.hpp"


class operators::Delete : public Node {
  private:
  NodePtr m_array;

  public:
  Delete(NodePtr&& t_array);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Delete();
};

#endif // DELETE_H
