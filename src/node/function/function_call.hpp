#ifndef FUNCTION_CALL_H
#define FUNCTION_CALL_H

#include <string>

#include "../list.hpp"

#include "function.hpp"


namespace nodes::function {
class FunctionCall : public List {
  private:
  std::string m_function_name;

  public:
};
}; // namespace nodes::function

#endif // FUNCTION_CALL_H
