#ifndef RETURN_EXCEPTION_HPP
#define RETURN_EXCEPTION_HPP

// STL Includes:
#include <optional>

// Local Includes:
#include "context.hpp"


namespace interpreter {
/*! For our Tree Walk Interpreter we implement return statements as an Exception
 * this is safer than using std::longjmp. We use a separate struct so it does
 * not get caught by other exception handlers.
 */
struct ReturnException {
};
} // namespace interpreter

#endif // RETURN_EXCEPTION_HPP
