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

// simple_statement_opt : /* empty */
//                  | simple_statement
//                  ;
auto Parser::simple_statement_opt() -> NodePtr
{
}

// terminatable_statement : simple_statement
//                  | Break
//                  | Continue
//                  | Next
//                  | Exit expr_opt
//                  | Return expr_opt
//                  | Do newline_opt terminated_statement While '(' expr ')'
//                  ;
auto Parser::terminatable_statement() -> NodePtr
{
}

// unterminated_statement : terminatable_statement
//                  | If '(' expr ')' newline_opt unterminated_statement
//                  | If '(' expr ')' newline_opt terminated_statement
//                       Else newline_opt unterminated_statement
//                  | While '(' expr ')' newline_opt unterminated_statement
//                  | For '(' simple_statement_opt ';'
//                   expr_opt ';' simple_statement_opt ')' newline_opt
//                       unterminated_statement
//                  | For '(' NAME In NAME ')' newline_opt
//                       unterminated_statement
//                  ;
auto Parser::unterminated_statement() -> NodePtr
{
}

// terminated_statement : action newline_opt
//                  | If '(' expr ')' newline_opt terminated_statement
//                  | If '(' expr ')' newline_opt terminated_statement
//                        Else newline_opt terminated_statement
//                  | While '(' expr ')' newline_opt terminated_statement
//                  | For '(' simple_statement_opt ';'
//                       expr_opt ';' simple_statement_opt ')' newline_opt
//                       terminated_statement
//                  | For '(' NAME In NAME ')' newline_opt
//                       terminated_statement
//                  | ';' newline_opt
//                  | terminatable_statement NEWLINE newline_opt
//                  | terminatable_statement ';'     newline_opt
//                  ;
auto Parser::terminated_statement() -> NodePtr
{
}

// unterminated_statement_list : unterminated_statement
//                  | terminated_statement_list unterminated_statement
//                  ;
auto Parser::unterminated_statement_list() -> NodePtr
{
}

// terminated_statement_list : terminated_statement
//                  | terminated_statement_list terminated_statement
//                  ;
auto Parser::terminated_statement_list() -> NodePtr
{
}

// terminator       : terminator NEWLINE
//                  |            ';'
//                  |            NEWLINE
//                  ;
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
  item_list();
  item();
  terminator();
}

// program          : item_list
//                  | item_list item
//                  ;
auto Parser::program() -> NodePtr
{
  item_list();
  item();
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
