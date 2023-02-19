#ifndef DELETE_H
#define DELETE_H

#include "../list.hpp"
#include "operators.hpp"

#include <string>


namespace nodes::operators {
class Delete : public Node {
  private:
  // TOOD: Figure out if std::string is enough or if we need the fileposition
  // Data
  std::string m_array;
  NodeListPtr m_expr_list;

  public:
  Delete(std::string&& t_array, NodeListPtr&& t_expr_list);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Delete() override = default;
};
} // namespace nodes::operators

#endif // DELETE_H
