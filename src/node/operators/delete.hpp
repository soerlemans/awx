#ifndef DELETE_HPP
#define DELETE_HPP

#include "../list.hpp"
#include "operators.hpp"

#include <string>


namespace node::operators {
class Delete : public NodeInterface {
  private:
  // TOOD: Figure out if std::string is enough or if we need the fileposition
  // Data
  std::string m_array;
  NodeListPtr m_expr_list;

  public:
  Delete(std::string&& t_array, NodeListPtr&& t_expr_list);

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Delete() override = default;
};
} // namespace node::operators

#endif // DELETE_HPP
