#ifndef FUNCTION_CALL_H
#define FUNCTION_CALL_H

#include <string>

#include "../list.hpp"
#include "../node.hpp"

#include "functions.hpp"


namespace nodes::functions {
class FunctionCall : public Node {
  private:
  std::string m_name;
  NodeListPtr m_args;

  public:
  FunctionCall(const std::string t_name, NodeListPtr&& t_args);

  virtual auto accept(NodeVisitor* t_visitor) -> void override;

  virtual ~FunctionCall();
};
} // namespace nodes::functions

#endif // FUNCTION_CALL_H