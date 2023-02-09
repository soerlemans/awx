#ifndef RECIPE_H
#define RECIPE_H

#include "../node.hpp"
#include "../list.hpp"

#include "recipes.hpp"

namespace nodes::recipes {
class Recipe : public Node {
  private:
  NodePtr m_pattern;

  // FIXME: Should be NodeListPtr
  NodePtr m_body;

  public:
  Recipe(NodePtr&& t_pattern, NodePtr&& t_body);

  auto pattern() -> NodePtr&;
  auto body() -> NodePtr&;

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  ~Recipe() override = default;
};
} // namespace nodes::recipes

#endif // RECIPE_H
