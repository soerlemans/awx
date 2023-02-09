#ifndef ARRAY_H
#define ARRAY_H

#include "lvalue.hpp"
#include "variable.hpp"

#include <vector>


namespace nodes::lvalue {
class Array : public Variable {
  private:
  NodePtr m_expr_list;

  public:
  Array(std::string t_name, NodePtr&& t_expr_list = nullptr);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  ~Array() override = default;
};
} // namespace nodes::lvalue

#endif // ARRAY_H
