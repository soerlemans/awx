#include "parser.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <tuple>

#include "../log.hpp"
#include "../token/token_type.hpp"
#include "../token/token_type_helpers.hpp"


// Class definitions:
Parser::Parser(TokenStream t_tokenstream): m_tokenstream{t_tokenstream}
{
}

// Parsing grammar methods:
// newline_opt      : /* empty */
//                  | newline_opt NEWLINE
//                  ;
auto Parser::newline_opt() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "NEWLINE OPT");
  return node;
}

// simple_get       : GETLINE
//                  | GETLINE lvalue
//                  ;
auto Parser::simple_get() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "SIMPLE GET");
  return node;
}

// unary_input_function : unary_expr '|' simple_get
//                  ;
auto Parser::unary_input_function() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "UNARY_INPUT_FUNCTION");
  return node;
}

// non_unary_input_function : simple_get
//                  | simple_get '<' expr
//                  | non_unary_expr '|' simple_get
//                  ;
auto Parser::non_unary_input_function() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "NON_UNARY_INPUT_FUNCTION");
  return node;
}

// lvalue           : NAME
//                  | NAME '[' expr_list ']'
//                  | '$' expr
//                  ;
auto Parser::lvalue() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "LVALUE");
  return node;
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
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "NON UNARY PRINT EXPR");
  return node;
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
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "UNARY PRINT EXPR");
  return node;
}

// print_expr       : unary_print_expr
//                  | non_unary_print_expr
//                  ;
auto Parser::print_expr() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "PRINT EXPR");
  return node;
}

// print_expr_list  : print_expr
//                  | print_expr_list ',' newline_opt print_expr
//                  ;
auto Parser::print_expr_list() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "PRINT EXPR LIST");
  return node;
}

// print_expr_list_opt : /* empty */
//                  | print_expr_list
//                  ;
auto Parser::print_expr_list_opt() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "PRINT EXPR LIST OPT");
  return node;
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
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "NON UNARY EXPR");
  return node;
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
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "UNARY EXPR");
  return node;
}

// expr             : unary_expr
//                  | non_unary_expr
//                  ;
auto Parser::expr() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "EXPR");
  return node;
}

// expr_opt         : /* empty */
//                  | expr
//                  ;
auto Parser::expr_opt() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "EXPR OPT");
  return node;
}

// multiple_expr_list : expr ',' newline_opt expr
//                  | multiple_expr_list ',' newline_opt expr
//                  ;
auto Parser::multiple_expr_list() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "MULTIPLE EXPR LIST");
  return node;
}

// expr_list        : expr
//                  | multiple_expr_list
//                  ;
auto Parser::expr_list() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "EXPR LIST");
  return node;
}

// expr_list_opt    : /* empty */
//                  | expr_list
//                  ;
auto Parser::expr_list_opt() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "EXPR LIST OPT");
  return node;
}

// output_redirection : '>'    expr
//                  | APPEND expr
//                  | '|'    expr
//                  ;
auto Parser::output_redirection() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "OUTPUT REDIRECTION");
  return node;
}

// simple_print_statement : Print  print_expr_list_opt
//                  | Print  '(' multiple_expr_list ')'
//                  | Printf print_expr_list
//                  | Printf '(' multiple_expr_list ')'
//                  ;
auto Parser::simple_print_statement() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "SIMPLE PRINT STATEMENT");
  return node;
}

// print_statement  : simple_print_statement
//                  | simple_print_statement output_redirection
//                  ;
auto Parser::print_statement() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "PRINT STATEMENT");
  return node;
}

// simple_statement : Delete NAME '[' expr_list ']'
//                  | expr
//                  | print_statement
//                  ;
auto Parser::simple_statement() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "SIMPLE STATEMENT");
  return node;
}

// simple_statement_opt : /* empty */
//                  | simple_statement
//                  ;
auto Parser::simple_statement_opt() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "SIMPLE STATEMENT OPT");
  return node;
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
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "TERMINATABLE STATEMENT");
  return node;
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
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "UNTERMINATED STATEMENT");
  return node;
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
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "TERMINATED STATEMENT");
  return node;
}

// unterminated_statement_list : unterminated_statement
//                  | terminated_statement_list unterminated_statement
//                  ;
auto Parser::unterminated_statement_list() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "UNTERMINATED STATEMENT LIST");
  return node;
}

// terminated_statement_list : terminated_statement
//                  | terminated_statement_list terminated_statement
//                  ;
auto Parser::terminated_statement_list() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "TERMINATED STATEMENT LIST");
  return node;
}

// terminator       : terminator NEWLINE
//                  |            ';'
//                  |            NEWLINE
//                  ;
auto Parser::terminator() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "TERMINATOR");
  return node;
}

// action           : '{' newline_opt                             '}'
//                  | '{' newline_opt terminated_statement_list   '}'
//                  | '{' newline_opt unterminated_statement_list '}'
//                  ;
auto Parser::action() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "ACTION");
  return node;
}

// special_pattern  : Begin
//                  | End
//                  ;
auto Parser::special_pattern() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "SPECIAL PATTERN");
  return node;
}

// normal_pattern   : expr
//                  | expr ',' newline_opt expr
//                  ;
auto Parser::normal_pattern() -> NodePtr
{
  NodePtr node{nullptr};

  LOG(LogLevel::INFO, "NORMAL PATTERN");
  return node;
}

// pattern          : normal_pattern
//                  | special_pattern
//                  ;
auto Parser::pattern() -> NodePtr
{
  NodePtr node{nullptr};

  if(auto normal_pattern_ptr{normal_pattern()}; normal_pattern_ptr) {
    node = std::move(normal_pattern_ptr);
  } else if(auto special_pattern_ptr{special_pattern()}; special_pattern_ptr) {
    node = std::move(special_pattern_ptr);
  }

  LOG(LogLevel::INFO, "PATTERN");
  return node;
}

// param_list       : NAME
//                  | param_list ',' NAME
//                  ;
auto Parser::param_list() -> NodePtr
{
  NodePtr node{nullptr};

  // const auto token{next_token()};

  LOG(LogLevel::INFO, "PARAM_LIST");
  return node;
}

// param_list_opt   : /* empty */
//                  | param_list
//                  ;
auto Parser::param_list_opt() -> NodePtr
{
  NodePtr node{nullptr};

  if(auto param_list_ptr{param_list()}; param_list_ptr) {
    node = std::move(param_list_ptr);
  }

  return node;
}

// item also covers what is the valid toplevel syntax:
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
  NodePtr node{nullptr};

  if(auto action_ptr{action()}; action_ptr) {
    node = std::move(action_ptr);
  } else if(auto pattern_ptr{pattern()}; pattern_ptr) {
    auto action_ptr{action()};

    // Resolve this?
    // How should we represent this in AST?
  } else if(auto normal_pattern_ptr{normal_pattern()}; normal_pattern_ptr) {
    node = std::move(normal_pattern_ptr);
  } else if(true) {
    // TODO: Implement function parsing for now ignore?
  }

  return node;
}


// item_list        : /* empty */
//                  | item_list item terminator
//                  ;
auto Parser::item_list() -> NodePtr
{
  NodePtr node{nullptr};

  // TODO Piece these together some way into an AST structure
  // item_list();
  item();
  terminator();

  return node;
}

// program          : item_list
//                  | item_list item
//                  ;
auto Parser::program() -> NodePtr
{
  NodePtr node{nullptr};

  // TODO Piece these together some way into an AST structure
  node = item_list();
  item();

  return node;
}

// Regular methods again:
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

  program();

  return ast;
}

Parser::~Parser()
{
}
