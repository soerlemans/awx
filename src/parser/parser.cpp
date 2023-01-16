#include "parser.hpp"

#include <memory>
#include <sstream>
#include <stdexcept>
#include <utility>


// Class definitions:
Parser::Parser(TokenStream&& t_tokenstream)
  : m_tokenstream{std::forward<TokenStream>(t_tokenstream)}
{}

auto Parser::eos() -> bool
{
  return m_tokenstream.eos();
}

auto Parser::error(const std::string_view t_msg) -> void
{
  if(eos()) {
    // TODO: Make a function for this
    std::stringstream ss;
    ss << "EOS reached!\n";
    ss << " - ";
    ss << t_msg;

    throw std::runtime_error{ss.str()};
  }
}

auto Parser::check(const TokenType t_tokentype) -> bool
{
  error("Tried to check for token at EOS!");

  const auto token{m_tokenstream.token()};

  return token.type() == t_tokentype;
}

auto Parser::next() -> Token&
{
  error("Tried to move to next Token at EOS!");

  return m_tokenstream.next();
}

auto Parser::next_if(const TokenType t_tokentype) -> bool
{
  error("Tried to move to next if Token is equal to expected token at EOS!");

  // Only go to next token if we find the token we expect
  bool equal{check(t_tokentype)};
  if(equal)
    next();

  return equal;
}

auto Parser::prev() -> Token&
{
  return m_tokenstream.prev();
}

auto Parser::get_token() -> Token
{
  error("Tried to return get token at EOS!");

  return m_tokenstream.token();
}

auto Parser::expect(const TokenType t_tokentype, const std::string t_msg)
  -> Token&
{
  if(!check(t_tokentype)) {
    std::stringstream ss;
    ss << "Expected -> ";
    ss << t_msg;

    throw std::runtime_error{ss.str()};
  }

  return next();
}

Parser::~Parser()
{}
