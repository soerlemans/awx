#ifndef SPECIAL_PATTERN_HPP
#define SPECIAL_PATTERN_HPP


#include "../node.hpp"

#include "recipes.hpp"

namespace nodes::recipes {
enum class SpecialPatternOp { BEGIN, END };

class SpecialPattern : public NodeInterface {
  private:
  SpecialPatternOp m_op;

  public:
  SpecialPattern(SpecialPatternOp t_op);

  auto op() const -> SpecialPatternOp;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~SpecialPattern() override = default;
};
} // namespace nodes::recipes

#endif // SPECIAL_PATTERN_HPP
