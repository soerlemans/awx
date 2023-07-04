#ifndef AWX_INTERPRETER_STRINGIFY_HPP
#define AWX_INTERPRETER_STRINGIFY_HPP

// Local Includes:
#include "context.hpp"
#include "overload.hpp"


namespace interpreter {
auto stringify(const Any& t_any) -> std::string;
} // namespace interpreter

#endif // AWX_INTERPRETER_STRINGIFY_HPP
