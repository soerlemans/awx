#ifndef SPECIAL_PATTERN_HPP
#define SPECIAL_PATTERN_HPP


#include "../node_interface.hpp"

#include "recipes.hpp"

namespace node::recipes {
enum class SpecialPatternOp { BEGIN, END };

class SpecialPattern : public NodeInterface {
  private:
  SpecialPatternOp m_op;

  public:
  SpecialPattern(SpecialPatternOp t_op);

  auto op() const -> SpecialPatternOp;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~SpecialPattern() override = default;
};
} // namespace node::recipes

#endif // SPECIAL_PATTERN_HPP
