#ifndef AWX_VISITOR_PRINT_VISITOR_HPP
#define AWX_VISITOR_PRINT_VISITOR_HPP

// STL Includes:
#include <iostream>

// Includes:
#include "../node/include.hpp"

// Local Includes:
#include "node_visitor.hpp"


namespace visitor {
/*! Visitor made for printing the AST Node per node
 * Has a unique overload for every print
 */
class PrintVisitor : public NodeVisitor {
  private:
  //! This class is made for pretty printing the AST
  class Printer {
    private:
    int& m_counter;

    public:
    Printer(int& t_counter): m_counter{t_counter}
    {
      m_counter++;
    }

    template<typename... Args>
    auto print_if(node::NodePtr& t_ptr, PrintVisitor* t_this, Args&&... t_args)
      -> void
    {
      if(t_ptr) {
        print(std::forward<Args>(t_args)...);
        t_ptr->accept(t_this);
      }
    }

    template<typename... Args>
    auto print(Args&&... t_args) -> void
    {
      // Construct the prefix
      std::cout << std::string(m_counter, ' ') << "-> ";

      // Print the arguments
      (std::cout << ... << t_args);

      // Create the indentation level denoter
      std::cout << " - (" << m_counter << ")\n";
    }

    ~Printer()
    {
      m_counter--;
    }
  };

  // Variables:
  int m_counter{0};

  public:
  PrintVisitor() = default;

  auto visit(node::control::If* t_if) -> void override;
  auto visit(node::control::While* t_while) -> void override;
  auto visit(node::control::For* t_for) -> void override;
  auto visit(node::control::ForIn* t_for) -> void override;
  auto visit(node::control::Return* t_return) -> void override;
  auto visit(node::control::Next* t_next) -> void override;

  auto visit(node::functions::Function* t_fn) -> void override;
  auto visit(node::functions::FunctionCall* t_fn_call) -> void override;
  auto visit(node::functions::BuiltinFunctionCall* t_fn) -> void override;

  auto visit(node::recipes::SpecialPattern* t_pattern) -> void override;
  auto visit(node::recipes::Recipe* t_recipe) -> void override;

  auto visit(node::io::Print* t_print) -> void override;
  auto visit(node::io::Printf* t_printf) -> void override;
  auto visit(node::io::Getline* t_getline) -> void override;
  auto visit(node::io::Redirection* t_redirection) -> void override;

  auto visit(node::lvalue::Array* t_array) -> void override;
  auto visit(node::lvalue::FieldReference* t_fr) -> void override;
  auto visit(node::lvalue::Variable* t_var) -> void override;

  auto visit(node::rvalue::Float* t_float) -> void override;
  auto visit(node::rvalue::Integer* t_int) -> void override;
  auto visit(node::rvalue::String* t_str) -> void override;
  auto visit(node::rvalue::Regex* t_regex) -> void override;

  auto visit(node::operators::Arithmetic* t_arithmetic) -> void override;
  auto visit(node::operators::Assignment* t_assignment) -> void override;
  auto visit(node::operators::Comparison* t_comparison) -> void override;

  auto visit(node::operators::Increment* t_increment) -> void override;
  auto visit(node::operators::Decrement* t_decrement) -> void override;

  auto visit(node::operators::Delete* t_delete) -> void override;
  auto visit(node::operators::Match* t_match) -> void override;

  auto visit(node::operators::Not* t_not) -> void override;
  auto visit(node::operators::And* t_and) -> void override;
  auto visit(node::operators::Or* t_or) -> void override;

  auto visit(node::operators::StringConcatenation* t_conc) -> void override;
  auto visit(node::operators::Grouping* t_grouping) -> void override;
  auto visit(node::operators::Ternary* t_ternary) -> void override;

  auto visit(node::operators::UnaryPrefix* t_unary_prefix) -> void override;

  auto visit(node::List* t_list) -> void override;
  auto visit(node::Nil* t_nil) -> void override;

  ~PrintVisitor() override = default;
};
} // namespace visitor

#endif // AWX_VISITOR_PRINT_VISITOR_HPP
