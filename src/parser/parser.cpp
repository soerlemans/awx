#include "parser.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <tuple>

#include "../token/token_type.hpp"
#include "../token/token_type_helpers.hpp"


// Class definitions:
Parser::Parser(TokenStream t_token_stream): m_token_stream{t_token_stream}
{
}

// item             : action
//                  | pattern action
//                  | normal_pattern
//                  | Function NAME      '(' param_list_opt ')'
//                        newline_opt action
//                  | Function FUNC_NAME '(' param_list_opt ')'
//                        newline_opt action
//                  ;
auto Parser::item() -> NodePointer
{
}


// item_list        : /* empty */
//                  | item_list item terminator
//                  ;
auto Parser::item_list() -> NodePointer
{
}

// program          : item_list
//                  | item_list item
//                  ;
auto Parser::program() -> NodePointer
{
}

auto Parser::next_token() -> Token&
{
  return m_token_stream.next();
}

auto Parser::parse() -> Ast
{
  using namespace reserved;

  Ast ast;
  for(; !m_token_stream.eos(); m_token_stream.next()) {
    // Ast is pieced together from calling nested functions
    // That each return a NodePointer to eachother
    // ast.add(toplevel());
  }

  return ast;
}

Parser::~Parser()
{
}
