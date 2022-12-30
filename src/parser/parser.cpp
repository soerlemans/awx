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

auto Parser::newline_opt() -> NodePtr
{
}

auto Parser::simple_get() -> NodePtr
{
}

auto Parser::unary_input_function() -> NodePtr
{
}

auto Parser::non_unary_input_function() -> NodePtr
{
}

auto Parser::lvalue() -> NodePtr
{
}

auto Parser::non_unary_print_expr() -> NodePtr
{
}

auto Parser::unary_print_expr() -> NodePtr
{
}

auto Parser::print_expr() -> NodePtr
{
}

auto Parser::print_expr_list() -> NodePtr
{
}

auto Parser::print_expr_list_opt() -> NodePtr
{
}

auto Parser::non_unary_expr() -> NodePtr
{
}

auto Parser::unary_expr() -> NodePtr
{
}

auto Parser::expr() -> NodePtr
{
}

auto Parser::expr_opt() -> NodePtr
{
}

auto Parser::multiple_expr_list() -> NodePtr
{
}

auto Parser::expr_list() -> NodePtr
{
}

auto Parser::expr_list_opt() -> NodePtr
{
}

auto Parser::output_redirection() -> NodePtr
{
}

auto Parser::simple_print_statement() -> NodePtr
{
}

auto Parser::print_statement() -> NodePtr
{
}

auto Parser::simple_statement() -> NodePtr
{
}

auto Parser::simple_statement_opt() -> NodePtr
{
}

auto Parser::terminatable_statement() -> NodePtr
{
}

auto Parser::unterminated_statement() -> NodePtr
{
}

auto Parser::terminated_statement() -> NodePtr
{
}

auto Parser::unterminated_statement_list() -> NodePtr
{
}

auto Parser::terminated_statement_list() -> NodePtr
{
}

auto Parser::terminator() -> NodePtr
{
}

// action           : '{' newline_opt                             '}'
//                  | '{' newline_opt terminated_statement_list   '}'
//                  | '{' newline_opt unterminated_statement_list '}'
//                  ;
auto Parser::action() -> NodePtr
{
}

// special_pattern  : Begin
//                  | End
//                  ;
auto Parser::special_pattern() -> NodePtr
{
}

// normal_pattern   : expr
//                  | expr ',' newline_opt expr
//                  ;
auto Parser::normal_pattern() -> NodePtr
{
}

// pattern          : normal_pattern
//                  | special_pattern
//                  ;
auto Parser::pattern() -> NodePtr
{
}

// param_list       : NAME
//                  | param_list ',' NAME
//                  ;
auto Parser::param_list() -> NodePtr
{
}

// param_list_opt   : /* empty */
//                  | param_list
//                  ;
auto Parser::param_list_opt() -> NodePtr
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
auto Parser::item() -> NodePtr
{
}


// item_list        : /* empty */
//                  | item_list item terminator
//                  ;
auto Parser::item_list() -> NodePtr
{
}

// program          : item_list
//                  | item_list item
//                  ;
auto Parser::program() -> NodePtr
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
    // That each return a NodePtr to eachother
    // ast.add(toplevel());
  }

  return ast;
}

Parser::~Parser()
{
}
