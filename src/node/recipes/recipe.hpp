#ifndef AWX_NODE_RECIPES_RECIPE_HPP
#define AWX_NODE_RECIPES_RECIPE_HPP

// Includes:
#include "../list.hpp"
#include "../node_interface.hpp"

// Local Includes:
#include "recipes.hpp"


namespace node::recipes {
class Recipe : public NodeInterface {
  private:
  NodePtr m_condition;

  // FIXME: Should be NodeListPtr
  NodePtr m_body;

  public:
  Recipe(NodePtr&& t_condition, NodePtr&& t_body);

  auto condition() -> NodePtr&;
  auto body() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Recipe() override = default;
};
} // namespace node::recipes

#endif // AWX_NODE_RECIPES_RECIPE_HPP
