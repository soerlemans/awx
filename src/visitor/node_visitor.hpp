#ifndef NODE_VISITOR_HPP
#define NODE_VISITOR_HPP

#include "../node/nodes.hpp"

#include "../node/control/control.hpp"
#include "../node/functions/functions.hpp"
#include "../node/recipes/recipes.hpp"

#include "../node/io/io.hpp"

#include "../node/lvalue/lvalue.hpp"
#include "../node/rvalue/rvalue.hpp"

#include "../node/operators/operators.hpp"


// Implementation of the Visitor design pattern for Nodes
// This creates a recursive dependency on the different kind of nodes
// So all nodes need to be forward declared in this header
class NodeVisitor {
  private:
  public:
  NodeVisitor() = default;

  virtual auto visit(nodes::control::If* t_if) -> void = 0;
  virtual auto visit(nodes::control::While* t_while) -> void = 0;
  virtual auto visit(nodes::control::For* t_for) -> void = 0;
  virtual auto visit(nodes::control::ForIn* t_for) -> void = 0;
  virtual auto visit(nodes::control::Return* t_return) -> void = 0;

  virtual auto visit(nodes::functions::Function* t_fn) -> void = 0;
  virtual auto visit(nodes::functions::FunctionCall* t_fn_call) -> void = 0;
  virtual auto visit(nodes::functions::BuiltinFunction* t_fn) -> void = 0;

  virtual auto visit(nodes::recipes::SpecialPattern* t_pattern) -> void = 0;
  virtual auto visit(nodes::recipes::Recipe* t_recipe) -> void = 0;

  virtual auto visit(nodes::io::Print* t_print) -> void = 0;
  virtual auto visit(nodes::io::Printf* t_printf) -> void = 0;
  virtual auto visit(nodes::io::Getline* t_getline) -> void = 0;
  virtual auto visit(nodes::io::Redirection* t_redirection) -> void = 0;

  virtual auto visit(nodes::lvalue::Array* t_array) -> void = 0;
  virtual auto visit(nodes::lvalue::FieldReference* t_fr) -> void = 0;
  virtual auto visit(nodes::lvalue::Variable* t_var) -> void = 0;

  virtual auto visit(nodes::rvalue::Float* t_float) -> void = 0;
  virtual auto visit(nodes::rvalue::Integer* t_int) -> void = 0;
  virtual auto visit(nodes::rvalue::String* t_str) -> void = 0;
  virtual auto visit(nodes::rvalue::Regex* t_regex) -> void = 0;

  virtual auto visit(nodes::operators::Arithmetic* t_arithmetic) -> void = 0;
  virtual auto visit(nodes::operators::Assignment* t_assignment) -> void = 0;
  virtual auto visit(nodes::operators::Comparison* t_comparison) -> void = 0;

  virtual auto visit(nodes::operators::Increment* t_increment) -> void = 0;
  virtual auto visit(nodes::operators::Decrement* t_decrement) -> void = 0;

  virtual auto visit(nodes::operators::Delete* t_delete) -> void = 0;
  virtual auto visit(nodes::operators::Match* t_match) -> void = 0;

  virtual auto visit(nodes::operators::Not* t_not) -> void = 0;
  virtual auto visit(nodes::operators::And* t_and) -> void = 0;
  virtual auto visit(nodes::operators::Or* t_or) -> void = 0;

  virtual auto visit(nodes::operators::StringConcatenation* t_conc) -> void = 0;
  virtual auto visit(nodes::operators::Ternary* t_ternary) -> void = 0;

  virtual auto visit(nodes::operators::UnaryPrefix* t_unary_prefix) -> void = 0;

  virtual auto visit(nodes::List* t_list) -> void = 0;
  virtual auto visit(nodes::Nil* t_nil) -> void = 0;

  virtual auto visit(nodes::Node* t_node) -> void;

  virtual ~NodeVisitor() = default;
};

#endif // NODE_VISITOR_HPP
