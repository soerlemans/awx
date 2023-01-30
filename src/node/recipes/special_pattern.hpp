#ifndef SPECIAL_PATTERN_H
#define SPECIAL_PATTERN_H


#include "../node.hpp"

#include "recipes.hpp"

namespace nodes::recipes {
enum class SpecialPatternOp { BEGIN, END };

class SpecialPattern : public Node {
  private:
  SpecialPatternOp m_op;

  public:
  SpecialPattern(SpecialPatternOp t_op);

  auto op() const -> SpecialPatternOp;

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~SpecialPattern();
};
} // namespace nodes::recipes

#endif // SPECIAL_PATTERN_H