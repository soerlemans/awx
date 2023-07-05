#include "field_store.hpp"

// STL Includes:
#include <regex>


// Using statements:
using namespace interpreter;

namespace {
auto trim(std::string& t_str) -> void
{
  const auto lambda{[&](const char t_char) {
    if(!t_str.empty() && t_str.back() == t_char) {
      t_str.pop_back();
    }
  }};

  // Trim newline and carriage return from end
  lambda('\n');
  lambda('\r');
}
} // namespace

//! Parse and set the field references according to the field separator
auto FieldStore::set(const std::string& t_fs, std::string t_record) -> void
{
  using Iter = std::sregex_token_iterator;

  trim(t_record);

  std::regex fs{t_fs, std::regex::extended};
  Iter iter{t_record.begin(), t_record.end(), fs, -1};
  Iter end;

  // Clear previous set fields
  m_fields.clear();

  // Construct fields
  m_fields.push_back(t_record);
  m_fields.insert(m_fields.end(), iter, end);
}

//! Returns a field reference
auto FieldStore::get(const std::size_t t_index) -> std::string
{
  std::string str;

  if(t_index < m_fields.size()) {
    str = m_fields[t_index];
  }

  return str;
}
