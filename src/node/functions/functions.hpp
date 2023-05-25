#ifndef AWX_NODE_FUNCTIONS_FUNCTIONS_HPP
#define AWX_NODE_FUNCTIONS_FUNCTIONS_HPP

// Includes:
#include "../node.hpp"
#include <memory>


namespace node::functions {
// Forward Declarations
class Function;

class FunctionCall;
class BuiltinFunctionCall;

// Aliases:
using NodeFuncPtr = std::shared_ptr<Function>;
} // namespace node::functions

#endif // AWX_NODE_FUNCTIONS_FUNCTIONS_HPP
