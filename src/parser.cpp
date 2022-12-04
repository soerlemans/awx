#include "parser.hpp"
#include "tokentype.hpp"


Parser::Parser(TokenStream t_tokenstream)
  :m_tokenstream{t_tokenstream}
{}

auto Parser::parse() -> void
{
  using namespace reserved;
  for(const auto& token : m_tokenstream)
	{
	  switch(token.type())
		{
		// case g_function.tokentype():
		//   break;

		// case g_function.tokentype():
		//   break;
		default:
		  // Throw an error
		  break;
		}
	}
}

Parser::~Parser()
{}
