#ifndef LIST_H
#define LIST_H

#include <list>

#include "nodes.hpp"
#include "node.hpp"


// TODO: Inherit from std::list itself or shadow std::list functions
// This is a list in the sense of a list of expressions or similar
// Think a list of nodes separated by commas like function arguments
// Or function call separated nodes
class nodes::List : public nodes::Node
{
  private:
  std::list<NodePtr> m_list;

  public:
  List();
  List(List&& t_ast) = default;

  auto begin() -> std::list<NodePtr>::iterator;
  auto end() -> std::list<NodePtr>::iterator;

  auto add(NodePtr&& t_node) -> void;

  auto accept(NodeVisitor t_visitor) -> void override;
  auto print() const -> void override;
};

#endif // LIST_H
