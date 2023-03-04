#ifndef REGEX_HPP
#define REGEX_HPP

#include "literal.hpp"


namespace nodes::rvalue {
class Regex : public Literal<std::string> {
  public:
  Regex(std::string&& t_value);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Regex() override = default;
};
} // namespace nodes::rvalue

#endif // REGEX_HPP
