#ifndef AWX_INTERPRETER_CONTEXT_HPP
#define AWX_INTERPRETER_CONTEXT_HPP

// STL Includes:
#include <map>
#include <string>
#include <variant>


namespace interpreter {
// Concepts:
template<typename T>
concept VariableLike = std::same_as < std::remove_cvref_t<T>,
double > || std::same_as<std::remove_cvref_t<T>, std::string>;

// Forward Declarations:
// struct ArrayType;

// Aliases:
// using Any = std::variant<double, std::string, ArrayType>;
// TODO: Rename Any to Var and have these be castable
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
