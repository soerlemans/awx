#ifndef AWX_INTERPRETER_FIELD_STORE_HPP
#define AWX_INTERPRETER_FIELD_STORE_HPP

// STL Includes:
#include <string>
#include <string_view>
#include <vector>


namespace interpreter {
class FieldStore {
  private:
  // Contains the entire record
  std::string m_record;

  // Contains the found fields (based on the field separator)
  std::vector<std::string> m_fields;

  public:
  FieldStore() = default;

  auto set(const std::string& t_fs, std::string t_record) -> void;
  auto get(std::size_t t_index = 0) -> std::string;

  virtual ~FieldStore() = default;
};
} // namespace interpreter

#endif // AWX_INTERPRETER_FIELD_STORE_HPP
