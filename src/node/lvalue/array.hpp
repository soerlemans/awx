#ifndef ARRAY_H
#define ARRAY_H

#include "variable.hpp"

#include <vector>

class Array : public Variable {
private:
public:
  Array(const std::string t_name);

  virtual auto accept(NodeVisitor t_visitor) -> void override;
  virtual auto print() const -> void override;

  virtual ~Array();
};

#endif // ARRAY_H
