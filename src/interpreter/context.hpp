#ifndef AWX_INTERPRETER_CONTEXT_HPP
#define AWX_INTERPRETER_CONTEXT_HPP

// STL Includes:
#include <map>
#include <string>
#include <variant>

// Local Includes:
#include "any.hpp"


namespace interpreter {
//! Context stores the result of the last expression
struct Context {
  // Sometimes we need the name of a variable or function
  std::string m_identifier;
  Any m_result;
};
} // namespace interpreter

#endif // AWX_INTERPRETER_CONTEXT_HPP
