#ifndef RECIPE_HPP
#define RECIPE_HPP

#include "../list.hpp"
#include "../node_interface.hpp"

#include "recipes.hpp"

namespace nodes::recipes {
class Recipe : public NodeInterface {
  private:
  NodePtr m_pattern;

  // FIXME: Should be NodeListPtr
  NodePtr m_body;

  public:
  Recipe(NodePtr&& t_pattern, NodePtr&& t_body);

  auto pattern() -> NodePtr&;
  auto body() -> NodePtr&;

  auto accept(NodeVisitor* t_visitor) -> void override;

  ~Recipe() override = default;
};
} // namespace nodes::recipes

#endif // RECIPE_HPP
