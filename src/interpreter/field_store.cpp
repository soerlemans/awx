#include "field_store.hpp"

// STL Includes:
#include <iostream>
#include <regex>


using namespace interpreter;

auto FieldStore::set(const std::string& t_fs, std::string t_record) -> void
{
  std::regex field_separator{t_fs, std::regex::extended};
  std::sregex_token_iterator iter{t_record.begin(), t_record.end(),
                                  field_separator, -1};
  std::sregex_token_iterator end;

  m_fields.clear();

  // FIXME: We do not account for carriage returns right now
  if(t_record.back() == '\n') {
    t_record.pop_back();
  }

  // Construct fields
  m_fields.push_back(t_record);
  m_fields.insert(m_fields.end(), iter, end);
}

// FIXME: Throw on empty fields
//! Returns a field reference
auto FieldStore::get(const std::size_t t_index) -> std::string
{
  std::string str;

  if(t_index < m_fields.size()) {
    str = m_fields[t_index];
  }

  return str;
}
