#ifndef AWX_NODE_RECIPES_RECIPE_HPP
#define AWX_NODE_RECIPES_RECIPE_HPP

#include "../list.hpp"
#include "../node_interface.hpp"

#include "recipes.hpp"

namespace node::recipes {
class Recipe : public NodeInterface {
  private:
  NodePtr m_pattern;

  // FIXME: Should be NodeListPtr
  NodePtr m_body;

  public:
  Recipe(NodePtr&& t_pattern, NodePtr&& t_body);

  auto pattern() -> NodePtr&;
  auto body() -> NodePtr&;

  auto accept(visitor::NodeVisitor* t_visitor) -> void override;

  ~Recipe() override = default;
};
} // namespace node::recipes

#endif // AWX_NODE_RECIPES_RECIPE_HPP
