#ifndef AWX_EXCEPTION_SYNTAX_ERROR_HPP
#define AWX_EXCEPTION_SYNTAX_ERROR_HPP

// STL Includes:
#include <filesystem>
#include <stdexcept>

// Includes:
#include "../container/file_position.hpp"


// Error classes intended for being thrown as exceptions
// When a mistake is made
class SyntaxError : public std::exception {
  protected:
  std::string m_error;
  container::FilePosition m_file_pos;

  public:
  SyntaxError(std::string_view t_msg,
              const container::FilePosition& t_file_pos);

  auto what() const noexcept -> const char* override;
};

#endif // AWX_EXCEPTION_SYNTAX_ERROR_HPP
