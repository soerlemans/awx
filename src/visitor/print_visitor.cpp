#include "print_visitor.hpp"


PrintVisitor::PrintVisitor(Ast& t_ast): m_ast{t_ast}
{
}

auto PrintVisitor::visit() -> void
{
  auto* current{m_ast.current()};

  // current->print(*this);
}

PrintVisitor::~PrintVisitor()
{
}
