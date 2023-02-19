#ifndef MEMBERSHIP_H
#define MEMBERSHIP_H

#include "unary_operator.hpp"
#include "operators.hpp"


namespace nodes::operators {
class Membership : public UnaryOperator {
  private:
  std::string m_name;

  public:
  Membership(NodePtr&& t_lhs, const std::string& t_name);

  auto name() const -> std::string_view;
  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Membership() override = default;
};
} // namespace nodes::operators

#endif // MEMBERSHIP_H
