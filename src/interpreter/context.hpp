#ifndef CONTEXT_HPP
#define CONTEXT_HPP

namespace interpreter {
// Aliases:
using Any = std::variant<double, std::string>;

// Structs:
struct Context {
  // Sometimes we need the name of a variable or function
  std::string m_name;
  Any m_result;
};
} // namespace interpreter

#endif // CONTEXT_HPP
