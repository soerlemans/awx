#ifndef ENUM_H
#define ENUM_H

#include <type_traits>

#include "types.hpp"


// Converts an enumeration to its underlying type
template<typename T>
constexpr auto enum2underlying_type(const T t_value) -> std::underlying_type_t<T>
{
  return static_cast<std::underlying_type_t<T>>(t_value);
}

#endif // ENUM_H
