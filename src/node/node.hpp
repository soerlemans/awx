#ifndef NODES_HPP
#define NODES_HPP

// STL Includes:
#include <memory>
#include <stdexcept>

// Local Includes:
// Forward declarations all Node classes:
#include "control/control.hpp"
#include "functions/functions.hpp"
#include "io/io.hpp"
#include "lvalue/lvalue.hpp"
#include "operators/operators.hpp"
#include "recipes/recipes.hpp"
#include "rvalue/rvalue.hpp"


namespace node {
// Forward Declarations:
class NodeInterface;
class List;       // List of NodePtr's
class Expression;
class Nil;        // Node that indicates nothing

// Aliases:
using NodePtr = std::shared_ptr<NodeInterface>;
using NodeListPtr = std::shared_ptr<List>;
} // namespace node

#endif // NODES_HPP
