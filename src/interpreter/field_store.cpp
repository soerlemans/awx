#include "field_store.hpp"

// STL Includes:
#include <regex>


using namespace interpreter;

auto FieldStore::set(const std::string& t_fs, const std::string& t_str) -> void
{
  std::regex field_separator{t_fs, std::regex::extended};
  std::sregex_token_iterator iter{t_str.begin(), t_str.end(), field_separator,
                                  -1};
  std::sregex_token_iterator end;

  m_record = t_str;
  m_fields.assign(iter, end);
}

//! Returns the whole record
auto FieldStore::get() -> std::string
{
  return m_record;
}

//! Returns a specific field reference
auto FieldStore::get(const std::size_t t_index) -> std::string
{
  std::string str{"\n"};

  if(t_index < m_fields.size()) {
    str = m_fields[t_index];
  }

  return str;
}
