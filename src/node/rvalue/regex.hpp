#ifndef REGEX_HPP
#define REGEX_HPP

#include "literal.hpp"


namespace node::rvalue {
class Regex : public Literal<std::string> {
  public:
  Regex(std::string&& t_value);

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Regex() override = default;
};
} // namespace node::rvalue

#endif // REGEX_HPP
