#ifndef SYNTAX_ERROR_H
#define SYNTAX_ERROR_H

#include <filesystem>
#include <stdexcept>

#include "../file_position.hpp"


// Error classes intended for being thrown as exceptions
// When a mistake is made
class SyntaxError : public std::exception {
  protected:
  std::string m_error;
  FilePosition m_file_pos;

  public:
  SyntaxError(std::string t_msg, FilePosition t_file_pos);

  auto what() const noexcept -> const char*;
};

#endif // SYNTAX_ERROR_H
