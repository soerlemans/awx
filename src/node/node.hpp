#ifndef NODES_HPP
#define NODES_HPP

// STL Includes:
#include <memory>
#include <stdexcept>

// Local Includes:
/*! Contains the forward declarations of all Node classes
 */
#include "control/control.hpp"
#include "functions/functions.hpp"
#include "io/io.hpp"
#include "lvalue/lvalue.hpp"
#include "operators/operators.hpp"
#include "recipes/recipes.hpp"
#include "rvalue/rvalue.hpp"


namespace node {
// Abstract base Node class
class NodeInterface;

// Specifies List of NodePtr's
class List;

// Most Node types inherit from Expression
class Expression;

// Empty Node that does nothing (intended for empty statements)
class Nil;

} // namespace node

// Aliases:
using NodePtr = std::shared_ptr<node::NodeInterface>;
using NodeListPtr = std::shared_ptr<node::List>;

#endif // NODES_HPP
