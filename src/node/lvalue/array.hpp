#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "lvalue.hpp"
#include "variable.hpp"

#include <vector>


namespace node::lvalue {
class Array : public Variable {
  private:
  NodePtr m_expr_list;

  public:
  Array(std::string t_name, NodePtr&& t_expr_list = nullptr);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Array() override = default;
};
} // namespace node::lvalue

#endif // ARRAY_HPP
