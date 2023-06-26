#ifndef AWX_CONTAINER_TEXT_BUFFER_HPP
#define AWX_CONTAINER_TEXT_BUFFER_HPP

// STL Includes:
#include <string>
#include <vector>


namespace container {
class TextBuffer {
  protected:
  std::vector<std::string> m_buffer;

  // Keep track of current position in the filebuffer
  mutable std::size_t m_lineno, m_columnno;

  public:
  TextBuffer();

  auto add_line(std::string t_line) -> void;

  // Line movement
  auto next() const -> std::string;
  auto prev() const -> std::string;

  // Character movement
  auto forward() const -> char;
  auto backward() const -> char;

  auto line() const -> std::string;
  auto character() const -> char;

  auto size() const -> std::size_t;

  auto eol() const -> bool;
  auto eof() const -> bool;

  friend auto operator<<(std::ostream& t_os, const TextBuffer& t_tb)
    -> std::ostream&;

  virtual ~TextBuffer() = default;
};
} // namespace container

#endif // AWX_CONTAINER_TEXT_BUFFER_HPP
