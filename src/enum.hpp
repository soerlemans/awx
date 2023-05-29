#ifndef AWX_ENUM_HPP
#define AWX_ENUM_HPP

#include <type_traits>

#include "types.hpp"


// Converts an enumeration to its underlying type
template<typename T>
constexpr auto enum2int(const T t_value) -> std::underlying_type_t<T>
{
  return static_cast<std::underlying_type_t<T>>(t_value);
}

#endif // AWX_ENUM_HPP
