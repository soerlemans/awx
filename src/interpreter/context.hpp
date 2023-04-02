#ifndef CONTEXT_HPP
#define CONTEXT_HPP

// STL Includes:
#include <map>

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

struct Context {
  // Sometimes we need the name of a variable or function
  std::string m_name;
  Any m_result;
};
} // namespace interpreter

#endif // CONTEXT_HPP
