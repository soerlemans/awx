#ifndef AWX_INTERPRETER_CONTEXT_HPP
#define AWX_INTERPRETER_CONTEXT_HPP

// STL Includes:
#include <map>
#include <string>
#include <variant>


namespace interpreter {
// Forward Declarations:
// struct ArrayType;

// Aliases:
// using Any = std::variant<double, std::string, ArrayType>;
using Any = std::variant<double, std::string>;

// Structs:
// struct ArrayType : public std::map<Any, Any> {
//   using std::map<Any, Any>::map;
// };

//! Context stores the result of the last expression
struct Context {
  // Sometimes we need the name of a variable or function
  std::string m_name;
  Any m_result;
};
} // namespace interpreter

#endif // AWX_INTERPRETER_CONTEXT_HPP
