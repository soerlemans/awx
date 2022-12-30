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

// Parsing grammar functions:
// newline_opt      : /* empty */
//                  | newline_opt NEWLINE
//                  ;
auto Parser::newline_opt() -> NodePtr
{
}

// simple_get       : GETLINE
//                  | GETLINE lvalue
//                  ;
auto Parser::simple_get() -> NodePtr
{
}

// unary_input_function : unary_expr '|' simple_get
//                  ;
auto Parser::unary_input_function() -> NodePtr
{
}

// non_unary_input_function : simple_get
//                  | simple_get '<' expr
//                  | non_unary_expr '|' simple_get
//                  ;
auto Parser::non_unary_input_function() -> NodePtr
{
}

// lvalue           : NAME
//                  | NAME '[' expr_list ']'
//                  | '$' expr
//                  ;
auto Parser::lvalue() -> NodePtr
{
}

// non_unary_print_expr : '(' expr ')'
//                  | '!' print_expr
//                  | non_unary_print_expr '^'      print_expr
//                  | non_unary_print_expr '*'      print_expr
//                  | non_unary_print_expr '/'      print_expr
//                  | non_unary_print_expr '%'      print_expr
//                  | non_unary_print_expr '+'      print_expr
//                  | non_unary_print_expr '-'      print_expr
//                  | non_unary_print_expr          non_unary_print_expr
//                  | non_unary_print_expr '˜'      print_expr
//                  | non_unary_print_expr NO_MATCH print_expr
//                  | non_unary_print_expr In NAME
//                  | '(' multiple_expr_list ')' In NAME
//                  | non_unary_print_expr AND newline_opt print_expr
//                  | non_unary_print_expr OR  newline_opt print_expr
//                  | non_unary_print_expr '?' print_expr ':' print_expr
//                  | NUMBER
//                  | STRING
//                  | lvalue
//                  | ERE
//                  | lvalue INCR
//                  | lvalue DECR
//                  | INCR lvalue
//                  | DECR lvalue
//                  | lvalue POW_ASSIGN print_expr
//                  | lvalue MOD_ASSIGN print_expr
//                  | lvalue MUL_ASSIGN print_expr
//                  | lvalue DIV_ASSIGN print_expr
//                  | lvalue ADD_ASSIGN print_expr
//                  | lvalue SUB_ASSIGN print_expr
//                  | lvalue '=' print_expr
//                  | FUNC_NAME '(' expr_list_opt ')'
//                      /* no white space allowed before '(' */
//                  | BUILTIN_FUNC_NAME '(' expr_list_opt ')'
//                  | BUILTIN_FUNC_NAME
//                  ;
auto Parser::non_unary_print_expr() -> NodePtr
{
}

// unary_print_expr : '+' print_expr
//                  | '-' print_expr
//                  | unary_print_expr '^'      print_expr
//                  | unary_print_expr '*'      print_expr
//                  | unary_print_expr '/'      print_expr
//                  | unary_print_expr '%'      print_expr
//                  | unary_print_expr '+'      print_expr
//                  | unary_print_expr '-'      print_expr
//                  | unary_print_expr          non_unary_print_expr
//                  | unary_print_expr '˜'      print_expr
//                  | unary_print_expr NO_MATCH print_expr
//                  | unary_print_expr In NAME
//                  | unary_print_expr AND newline_opt print_expr
//                  | unary_print_expr OR  newline_opt print_expr
//                  | unary_print_expr '?' print_expr ':' print_expr
//                  ;
auto Parser::unary_print_expr() -> NodePtr
{
}

// print_expr       : unary_print_expr
//                  | non_unary_print_expr
//                  ;
auto Parser::print_expr() -> NodePtr
{
}

// print_expr_list  : print_expr
//                  | print_expr_list ',' newline_opt print_expr
//                  ;
auto Parser::print_expr_list() -> NodePtr
{
}

// print_expr_list_opt : /* empty */
//                  | print_expr_list
//                  ;
auto Parser::print_expr_list_opt() -> NodePtr
{
}

// non_unary_expr   : '(' expr ')'
//                  | '!' expr
//                  | non_unary_expr '^'      expr
//                  | non_unary_expr '*'      expr
//                  | non_unary_expr '/'      expr
//                  | non_unary_expr '%'      expr
//                  | non_unary_expr '+'      expr
//                  | non_unary_expr '-'      expr
//                  | non_unary_expr          non_unary_expr
//                  | non_unary_expr '<'      expr
//                  | non_unary_expr LE       expr
//                  | non_unary_expr NE       expr
//                  | non_unary_expr EQ       expr
//                  | non_unary_expr '>'      expr
//                  | non_unary_expr GE       expr
//                  | non_unary_expr '˜'      expr
//                  | non_unary_expr NO_MATCH expr
//                  | non_unary_expr In NAME
//                  | '(' multiple_expr_list ')' In NAME
//                  | non_unary_expr AND newline_opt expr
//                  | non_unary_expr OR  newline_opt expr
//                  | non_unary_expr '?' expr ':' expr
//                  | NUMBER
//                  | STRING
//                  | lvalue
//                  | ERE
//                  | lvalue INCR
//                  | lvalue DECR
//                  | INCR lvalue
//                  | DECR lvalue
//                  | lvalue POW_ASSIGN expr
//                  | lvalue MOD_ASSIGN expr
//                  | lvalue MUL_ASSIGN expr
//                  | lvalue DIV_ASSIGN expr
//                  | lvalue ADD_ASSIGN expr
//                  | lvalue SUB_ASSIGN expr
//                  | lvalue '=' expr
//                  | FUNC_NAME '(' expr_list_opt ')'
//                       /* no white space allowed before '(' */
//                  | BUILTIN_FUNC_NAME '(' expr_list_opt ')'
//                  | BUILTIN_FUNC_NAME
//                  | non_unary_input_function
//                  ;
auto Parser::non_unary_expr() -> NodePtr
{
}

// unary_expr       : '+' expr
//                  | '-' expr
//                  | unary_expr '^'      expr
//                  | unary_expr '*'      expr
//                  | unary_expr '/'      expr
//                  | unary_expr '%'      expr
//                  | unary_expr '+'      expr
//                  | unary_expr '-'      expr
//                  | unary_expr          non_unary_expr
//                  | unary_expr '<'      expr
//                  | unary_expr LE       expr
//                  | unary_expr NE       expr
//                  | unary_expr EQ       expr
//                  | unary_expr '>'      expr
//                  | unary_expr GE       expr
//                  | unary_expr '˜'      expr
//                  | unary_expr NO_MATCH expr
//                  | unary_expr In NAME
//                  | unary_expr AND newline_opt expr
//                  | unary_expr OR  newline_opt expr
//                  | unary_expr '?' expr ':' expr
//                  | unary_input_function
//                  ;
auto Parser::unary_expr() -> NodePtr
{
}

// expr             : unary_expr
//                  | non_unary_expr
//                  ;
auto Parser::expr() -> NodePtr
{
}

// expr_opt         : /* empty */
//                  | expr
//                  ;
auto Parser::expr_opt() -> NodePtr
{
}

// multiple_expr_list : expr ',' newline_opt expr
//                  | multiple_expr_list ',' newline_opt expr
//                  ;
auto Parser::multiple_expr_list() -> NodePtr
{
}

// expr_list        : expr
//                  | multiple_expr_list
//                  ;
auto Parser::expr_list() -> NodePtr
{
}

// expr_list_opt    : /* empty */
//                  | expr_list
//                  ;
auto Parser::expr_list_opt() -> NodePtr
{
}

// output_redirection : '>'    expr
//                  | APPEND expr
//                  | '|'    expr
//                  ;
auto Parser::output_redirection() -> NodePtr
{
}

// simple_print_statement : Print  print_expr_list_opt
//                  | Print  '(' multiple_expr_list ')'
//                  | Printf print_expr_list
//                  | Printf '(' multiple_expr_list ')'
//                  ;
auto Parser::simple_print_statement() -> NodePtr
{
}

// print_statement  : simple_print_statement
//                  | simple_print_statement output_redirection
//                  ;
auto Parser::print_statement() -> NodePtr
{
}

// simple_statement : Delete NAME '[' expr_list ']'
//                  | expr
//                  | print_statement
//                  ;
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
