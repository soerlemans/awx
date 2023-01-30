#ifndef VARIABLE_H
#define VARIABLE_H

#include "../node.hpp"

#include "lvalue.hpp"


namespace nodes::lvalue {
class Variable : public Node {
  private:
  std::string m_name;

  public:
  Variable(std::string t_name);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~Variable();
};
} // namespace nodes::lvalue

#endif // VARIABLE_H
