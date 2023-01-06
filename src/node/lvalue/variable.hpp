#ifndef VARIABLE_H
#define VARIABLE_H

#include "../node.hpp"

class Variable : public Node {
  private:
  std::string m_name;

  public:
  Variable(const std::string t_name);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Variable();
};

#endif // VARIABLE_H
