#ifndef AWX_NODE_LVALUE_ARRAY_HPP
#define AWX_NODE_LVALUE_ARRAY_HPP

#include "lvalue.hpp"
#include "variable.hpp"

#include <vector>


namespace node::lvalue {
class Array : public Variable {
  private:
  NodePtr m_expr_list;

  public:
  Array(std::string t_name, NodePtr&& t_expr_list = nullptr);

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Array() override = default;
};
} // namespace node::lvalue

#endif // AWX_NODE_LVALUE_ARRAY_HPP
