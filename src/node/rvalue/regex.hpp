#ifndef AWX_NODE_RVALUE_REGEX_HPP
#define AWX_NODE_RVALUE_REGEX_HPP

#include "literal.hpp"


namespace node::rvalue {
class Regex : public Literal<std::string> {
  public:
  Regex(std::string&& t_value);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Regex() override = default;
};
} // namespace node::rvalue

#endif // AWX_NODE_RVALUE_REGEX_HPP
