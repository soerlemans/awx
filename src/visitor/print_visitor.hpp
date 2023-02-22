#ifndef PRINT_VISITOR_H
#define PRINT_VISITOR_H

#include "../debug/trace.hpp"
#include "node_visitor.hpp"


// Visitor made for printing the AST Node per node
// Has a unique overload for every print
class PrintVisitor : public NodeVisitor {
  private:
  // Classes:
  // This class is made for pretty printing the AST
  class Printer {
    private:
    int& m_counter;

    public:
    Printer(int& t_counter): m_counter{t_counter}
    {
      m_counter++;
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

  auto visit(nodes::control::If* t_if) -> void override;
  auto visit(nodes::control::While* t_while) -> void override;
  auto visit(nodes::control::For* t_for) -> void override;
  auto visit(nodes::control::ForIn* t_for) -> void override;
  auto visit(nodes::control::Return* t_return) -> void override;

  auto visit(nodes::functions::Function* t_fn) -> void override;
  auto visit(nodes::functions::FunctionCall* t_fn_call) -> void override;
  auto visit(nodes::functions::BuiltinFunction* t_fn) -> void override;

  auto visit(nodes::recipes::SpecialPattern* t_pattern) -> void override;
  auto visit(nodes::recipes::Recipe* t_recipe) -> void override;

  auto visit(nodes::io::Print* t_print) -> void override;
  auto visit(nodes::io::Printf* t_printf) -> void override;
  auto visit(nodes::io::Getline* t_getline) -> void override;
  auto visit(nodes::io::Redirection* t_redirection) -> void override;

  auto visit(nodes::lvalue::Array* t_array) -> void override;
  auto visit(nodes::lvalue::FieldReference* t_fr) -> void override;
  auto visit(nodes::lvalue::Variable* t_var) -> void override;

  auto visit(nodes::rvalue::Float* t_float) -> void override;
  auto visit(nodes::rvalue::Integer* t_int) -> void override;
  auto visit(nodes::rvalue::String* t_str) -> void override;

  auto visit(nodes::operators::Arithmetic* t_arithmetic) -> void override;
  auto visit(nodes::operators::Assignment* t_assignment) -> void override;
  auto visit(nodes::operators::Comparison* t_comparison) -> void override;

  auto visit(nodes::operators::Increment* t_increment) -> void override;
  auto visit(nodes::operators::Decrement* t_decrement) -> void override;

  auto visit(nodes::operators::Delete* t_delete) -> void override;
  auto visit(nodes::operators::Match* t_match) -> void override;

  auto visit(nodes::operators::Not* t_not) -> void override;
  auto visit(nodes::operators::And* t_and) -> void override;
  auto visit(nodes::operators::Or* t_or) -> void override;

  auto visit(nodes::operators::StringConcatenation* t_conc) -> void override;
  auto visit(nodes::operators::Ternary* t_ternary) -> void override;

  auto visit(nodes::operators::UnaryPrefix* t_unary_prefix) -> void override;

  auto visit(nodes::List* t_list) -> void override;

  ~PrintVisitor() override = default;
};

#endif // PRINT_VISITOR_H
