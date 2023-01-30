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
  int m_counter;

  public:
  PrintVisitor();

  virtual auto visit(nodes::control::If* t_if) -> void override;

  virtual auto visit(nodes::functions::Function* t_fn) -> void override;
  virtual auto visit(nodes::functions::FunctionCall* t_fn_call)
    -> void override;
  virtual auto visit(nodes::functions::BuiltinFunction* t_fn) -> void override;

  virtual auto visit(nodes::recipes::SpecialPattern* t_pattern)
    -> void override;
  virtual auto visit(nodes::recipes::Recipe* t_recipe) -> void override;

  virtual auto visit(nodes::io::Print* t_print) -> void override;
  virtual auto visit(nodes::io::Printf* t_printf) -> void override;
  virtual auto visit(nodes::io::Getline* t_getline) -> void override;
  virtual auto visit(nodes::io::Redirection* t_redirection) -> void override;

  virtual auto visit(nodes::lvalue::Array* t_array) -> void override;
  virtual auto visit(nodes::lvalue::FieldReference* t_fr) -> void override;
  virtual auto visit(nodes::lvalue::Variable* t_var) -> void override;

  virtual auto visit(nodes::rvalue::Float* t_float) -> void override;
  virtual auto visit(nodes::rvalue::Integer* t_int) -> void override;
  virtual auto visit(nodes::rvalue::String* t_str) -> void override;

  virtual auto visit(nodes::operators::Arithmetic* t_arithmetic)
    -> void override;
  virtual auto visit(nodes::operators::Assignment* t_assignment)
    -> void override;
  virtual auto visit(nodes::operators::Comparison* t_comparison)
    -> void override;

  virtual auto visit(nodes::operators::Increment* t_increment) -> void override;
  virtual auto visit(nodes::operators::Decrement* t_decrement) -> void override;

  virtual auto visit(nodes::operators::Delete* t_delete) -> void override;
  virtual auto visit(nodes::operators::Ere* t_ere) -> void override;

  virtual auto visit(nodes::operators::Not* t_not) -> void override;
  virtual auto visit(nodes::operators::And* t_and) -> void override;
  virtual auto visit(nodes::operators::Or* t_or) -> void override;

  virtual auto visit(nodes::operators::StringConcatenation* t_conc)
    -> void override;
  virtual auto visit(nodes::operators::Ternary* t_ternary) -> void override;

  virtual auto visit(nodes::operators::UnaryPrefix* t_unary_prefix)
    -> void override;

  virtual auto visit(nodes::List* t_list) -> void override;

  virtual ~PrintVisitor();
};

#endif // PRINT_VISITOR_H
