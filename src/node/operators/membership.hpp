#ifndef MEMBERSHIP_HPP
#define MEMBERSHIP_HPP

#include "operators.hpp"
#include "unary_operator.hpp"


namespace node::operators {
class Membership : public UnaryOperator {
  private:
  std::string m_name;

  public:
  Membership(NodePtr&& t_lhs, std::string&& t_name);

  auto name() const -> std::string_view;
  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Membership() override = default;
};
} // namespace node::operators

#endif // MEMBERSHIP_HPP
