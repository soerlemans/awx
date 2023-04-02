#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

// Includes:
#include "../node.hpp"
#include <memory>


namespace node::functions {
// Forward Declarations
class Function;
class BuiltinFunction;

class FunctionCall;

// Aliases:
using NodeFuncPtr = std::shared_ptr<Function>;
} // namespace node::functions

#endif // FUNCTIONS_HPP
