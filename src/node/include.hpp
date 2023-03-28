#ifndef INCLUDE_HPP
#define INCLUDE_HPP

/*! This header is made to include the headers of all classes that inherit from
 * Node, this to
 */

// Top level:
#include "../node/list.hpp"
#include "../node/nil.hpp"
#include "../node/node_interface.hpp"
#include "../node/node.hpp"

// Control Statements:
#include "../node/control/break.hpp"
#include "../node/control/continue.hpp"
#include "../node/control/control.hpp"
#include "../node/control/exit.hpp"
#include "../node/control/for.hpp"
#include "../node/control/for_in.hpp"
#include "../node/control/if.hpp"
#include "../node/control/next.hpp"
#include "../node/control/return.hpp"
#include "../node/control/while.hpp"

// IO:
#include "../node/io/getline.hpp"
#include "../node/io/io.hpp"
#include "../node/io/print.hpp"
#include "../node/io/printf.hpp"
#include "../node/io/redirection.hpp"

// Rvalue:
#include "../node/rvalue/literal.hpp"
#include "../node/rvalue/regex.hpp"
#include "../node/rvalue/rvalue.hpp"

// Lvalue:
#include "../node/lvalue/array.hpp"
#include "../node/lvalue/field_reference.hpp"
#include "../node/lvalue/lvalue.hpp"
#include "../node/lvalue/variable.hpp"

// Function:
#include "../node/functions/function.hpp"
#include "../node/functions/function_call.hpp"
#include "../node/functions/functions.hpp"

// Recipe:
#include "../node/recipes/recipe.hpp"
#include "../node/recipes/recipes.hpp"
#include "../node/recipes/special_pattern.hpp"

// Operators:
#include "../node/operators/arithmetic.hpp"
#include "../node/operators/assignment.hpp"
#include "../node/operators/comparison.hpp"
#include "../node/operators/decrement.hpp"
#include "../node/operators/delete.hpp"
#include "../node/operators/grouping.hpp"
#include "../node/operators/increment.hpp"
#include "../node/operators/logical.hpp"
#include "../node/operators/match.hpp"
#include "../node/operators/membership.hpp"
#include "../node/operators/operators.hpp"
#include "../node/operators/string_concatenation.hpp"
#include "../node/operators/ternary.hpp"
#include "../node/operators/unary_prefix.hpp"

#endif // INCLUDE_HPP
