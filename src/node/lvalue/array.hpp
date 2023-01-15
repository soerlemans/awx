#ifndef ARRAY_H
#define ARRAY_H

#include "lvalue.hpp"
#include "variable.hpp"

#include <vector>


namespace nodes::lvalue {
class Array : public Variable {
  private:
  public:
  Array(const std::string t_name);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Array();
};
}; // namespace nodes::lvalue

#endif // ARRAY_H
