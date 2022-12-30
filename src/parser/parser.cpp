#include "parser.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <tuple>

#include "../token/token_type.hpp"
#include "../token/token_type_helpers.hpp"


// Class definitions:
Parser::Parser(TokenStream t_tokenstream): m_tokenstream{t_tokenstream}
{
}

// special_pattern  : Begin
//                  | End
//                  ;
auto Parser::special_pattern() -> NodePointer
{
}

// normal_pattern   : expr
//                  | expr ',' newline_opt expr
//                  ;
auto Parser::normal_pattern() -> NodePointer
{
}

// pattern          : normal_pattern
//                  | special_pattern
//                  ;
auto Parser::pattern() -> NodePointer
{
}

// param_list       : NAME
//                  | param_list ',' NAME
//                  ;
auto Parser::param_list() -> NodePointer
{
}

// param_list_opt   : /* empty */
//                  | param_list
//                  ;
auto Parser::param_list_opt() -> NodePointer
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
  return m_tokenstream.next();
}

auto Parser::parse() -> Ast
{
  using namespace reserved;

  Ast ast;
  for(; !m_tokenstream.eos(); m_tokenstream.next()) {
    // Ast is pieced together from calling nested functions
    // That each return a NodePointer to eachother
    // ast.add(toplevel());
  }

  return ast;
}

Parser::~Parser()
{
}
