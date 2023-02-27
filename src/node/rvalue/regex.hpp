#ifndef REGEX_H
#define REGEX_H

#include "literal.hpp"


namespace nodes::rvalue {
class Regex : public Literal<std::string> {
  public:
  Regex(std::string&& t_value);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Regex() override = default;
};
} // namespace nodes::rvalue

#endif // REGEX_H
