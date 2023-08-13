#ifndef AWX_INTERPRETER_ANY_HPP
#define AWX_INTERPRETER_ANY_HPP

// STL Includes:
#include <concepts>
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
using Variant = std::variant<double, std::string>;

// Structs:
// struct ArrayType : public std::map<Any, Any> {
//   using std::map<Any, Any>::map;
// };

class Any : public Variant {
  public:
  // Import constructors
  using Variant::Variant;

  auto str() const -> std::string;
  auto num() const -> double;
};

} // namespace interpreter

#endif // AWX_INTERPRETER_ANY_HPP
