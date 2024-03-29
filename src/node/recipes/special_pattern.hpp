#ifndef AWX_NODE_RECIPES_SPECIAL_PATTERN_HPP
#define AWX_NODE_RECIPES_SPECIAL_PATTERN_HPP


// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "recipes.hpp"


namespace node::recipes {
enum class SpecialPatternOp { BEGIN, END };

class SpecialPattern : public NodeInterface {
  private:
  SpecialPatternOp m_op;

  public:
  SpecialPattern(SpecialPatternOp t_op);

  auto op() const -> SpecialPatternOp;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~SpecialPattern() override = default;
};
} // namespace node::recipes

#endif // AWX_NODE_RECIPES_SPECIAL_PATTERN_HPP
