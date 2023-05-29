#ifndef AWX_NODE_OPERATORS_DELETE_HPP
#define AWX_NODE_OPERATORS_DELETE_HPP

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

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Delete() override = default;
};
} // namespace node::operators

#endif // AWX_NODE_OPERATORS_DELETE_HPP
