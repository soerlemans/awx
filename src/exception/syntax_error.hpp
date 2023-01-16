#ifndef SYNTAX_ERROR_H
#define SYNTAX_ERROR_H

#include <filesystem>
#include <stdexcept>


// Error classes intended for being thrown as exceptions
// When a mistake is made
class SyntaxError : public std::exception {
  protected:
  std::string m_error;
  std::string m_path;

  std::size_t m_lineno;
  std::string m_line;

  // TODO: Add support for showing which column number produces the error
  std::size_t m_columnno;

  public:
  SyntaxError(std::string t_msg, std::string t_path, std::size_t t_lineno,
              std::string t_line, std::size_t t_columnno);

  auto what() const noexcept -> const char*;
};

#endif // SYNTAX_ERROR_H
