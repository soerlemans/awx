#include "unary_prefix.hpp"

using namespace operators;


UnaryPrefix::UnaryPrefix(UnaryPrefixOp t_op, NodePtr t_left)
  : UnaryOperator{Precedence::UNARY_PREFIX, std::forward<NodePtr>(t_left)},
    m_op{t_op}
{}

auto UnaryPrefix::op() const -> UnaryPrefixOp
{
  return m_op;
}

auto UnaryPrefix::accept(NodeVisitor t_visitor) -> void
{}

auto UnaryPrefix::print() const -> void
{}

UnaryPrefix::~UnaryPrefix()
{}

// Exported functions:
auto unary_prefix::tokentype2enum(const TokenType t_tokentype) -> UnaryPrefixOp
{
  UnaryPrefixOp op;

  switch(t_tokentype) {
    case TokenType::PLUS:
      op = UnaryPrefixOp::PLUS;
      break;

    case TokenType::MINUS:
      op = UnaryPrefixOp::MINUS;
      break;

    default:
      // TODO: Error handling
      break;
  }

  return op;
}
