#ifndef STRINGIFY_HPP
#define STRINGIFY_HPP

// Local Includes:
#include "context.hpp"
#include "overload.hpp"


namespace interpreter {
auto stringify(const Any& t_any) -> std::string;
} // namespace interpreter

#endif // STRINGIFY_HPP
