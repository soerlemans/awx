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
  LOG(LogLevel::INFO, "NEWLINE OPT");
  NodePtr node{nullptr};

  return node;
}

// simple_get       : GETLINE
//                  | GETLINE lvalue
//                  ;
auto Parser::simple_get() -> NodePtr
{
  LOG(LogLevel::INFO, "SIMPLE GET");
  NodePtr node{nullptr};

  return node;
}

// unary_input_function : unary_expr '|' simple_get
//                  ;
auto Parser::unary_input_function() -> NodePtr
{
  LOG(LogLevel::INFO, "UNARY_INPUT_FUNCTION");
  NodePtr node{nullptr};

  return node;
}

// non_unary_input_function : simple_get
//                  | simple_get '<' expr
//                  | non_unary_expr '|' simple_get
//                  ;
auto Parser::non_unary_input_function() -> NodePtr
{
  LOG(LogLevel::INFO, "NON_UNARY_INPUT_FUNCTION");
  NodePtr node{nullptr};

  return node;
}

// lvalue           : NAME
//                  | NAME '[' expr_list ']'
//                  | '$' expr
//                  ;
auto Parser::lvalue() -> NodePtr
{
  LOG(LogLevel::INFO, "LVALUE");
  NodePtr node{nullptr};

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
  LOG(LogLevel::INFO, "NON UNARY PRINT EXPR");
  NodePtr node{nullptr};

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
  LOG(LogLevel::INFO, "UNARY PRINT EXPR");
  NodePtr node{nullptr};

  return node;
}

// print_expr       : unary_print_expr
//                  | non_unary_print_expr
//                  ;
auto Parser::print_expr() -> NodePtr
{
  LOG(LogLevel::INFO, "PRINT EXPR");
  NodePtr node{nullptr};

  return node;
}

// print_expr_list  : print_expr
//                  | print_expr_list ',' newline_opt print_expr
//                  ;
auto Parser::print_expr_list() -> NodePtr
{
  LOG(LogLevel::INFO, "PRINT EXPR LIST");
  NodePtr node{nullptr};

  return node;
}

// print_expr_list_opt : /* empty */
//                  | print_expr_list
//                  ;
auto Parser::print_expr_list_opt() -> NodePtr
{
  LOG(LogLevel::INFO, "PRINT EXPR LIST OPT");
  NodePtr node{nullptr};

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
  LOG(LogLevel::INFO, "NON UNARY EXPR");
  NodePtr node{nullptr};

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
  LOG(LogLevel::INFO, "UNARY EXPR");
  NodePtr node{nullptr};

  return node;
}

// expr             : unary_expr
//                  | non_unary_expr
//                  ;
auto Parser::expr() -> NodePtr
{
  LOG(LogLevel::INFO, "EXPR");
  NodePtr node{nullptr};

  return node;
}

// expr_opt         : /* empty */
//                  | expr
//                  ;
auto Parser::expr_opt() -> NodePtr
{
  LOG(LogLevel::INFO, "EXPR OPT");
  NodePtr node{nullptr};

  return node;
}

// multiple_expr_list : expr ',' newline_opt expr
//                  | multiple_expr_list ',' newline_opt expr
//                  ;
auto Parser::multiple_expr_list() -> NodePtr
{
  LOG(LogLevel::INFO, "MULTIPLE EXPR LIST");
  NodePtr node{nullptr};

  return node;
}

// expr_list        : expr
//                  | multiple_expr_list
//                  ;
auto Parser::expr_list() -> NodePtr
{
  LOG(LogLevel::INFO, "EXPR LIST");
  NodePtr node{nullptr};

  return node;
}

// expr_list_opt    : /* empty */
//                  | expr_list
//                  ;
auto Parser::expr_list_opt() -> NodePtr
{
  LOG(LogLevel::INFO, "EXPR LIST OPT");
  NodePtr node{nullptr};

  return node;
}

// output_redirection : '>'    expr
//                  | APPEND expr
//                  | '|'    expr
//                  ;
auto Parser::output_redirection() -> NodePtr
{
  LOG(LogLevel::INFO, "OUTPUT REDIRECTION");
  NodePtr node{nullptr};

  return node;
}

// simple_print_statement : Print  print_expr_list_opt
//                  | Print  '(' multiple_expr_list ')'
//                  | Printf print_expr_list
//                  | Printf '(' multiple_expr_list ')'
//                  ;
auto Parser::simple_print_statement() -> NodePtr
{
  LOG(LogLevel::INFO, "SIMPLE PRINT STATEMENT");
  NodePtr node{nullptr};

  return node;
}

// print_statement  : simple_print_statement
//                  | simple_print_statement output_redirection
//                  ;
auto Parser::print_statement() -> NodePtr
{
  LOG(LogLevel::INFO, "PRINT STATEMENT");
  NodePtr node{nullptr};

  return node;
}

// simple_statement : Delete NAME '[' expr_list ']'
//                  | expr
//                  | print_statement
//                  ;
auto Parser::simple_statement() -> NodePtr
{
  LOG(LogLevel::INFO, "SIMPLE STATEMENT");
  NodePtr node{nullptr};

  return node;
}

// simple_statement_opt : /* empty */
//                  | simple_statement
//                  ;
auto Parser::simple_statement_opt() -> NodePtr
{
  LOG(LogLevel::INFO, "SIMPLE STATEMENT OPT");
  NodePtr node{nullptr};

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
  LOG(LogLevel::INFO, "TERMINATABLE STATEMENT");
  NodePtr node{nullptr};

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
  LOG(LogLevel::INFO, "UNTERMINATED STATEMENT");
  NodePtr node{nullptr};

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
  LOG(LogLevel::INFO, "TERMINATED STATEMENT");
  NodePtr node{nullptr};

  return node;
}

// unterminated_statement_list : unterminated_statement
//                  | terminated_statement_list unterminated_statement
//                  ;
auto Parser::unterminated_statement_list() -> NodePtr
{
  LOG(LogLevel::INFO, "UNTERMINATED STATEMENT LIST");
  NodePtr node{nullptr};

  return node;
}

// terminated_statement_list : terminated_statement
//                  | terminated_statement_list terminated_statement
//                  ;
auto Parser::terminated_statement_list() -> NodePtr
{
  LOG(LogLevel::INFO, "TERMINATED STATEMENT LIST");
  NodePtr node{nullptr};

  return node;
}

// terminator       : terminator NEWLINE
//                  |            ';'
//                  |            NEWLINE
//                  ;
auto Parser::terminator() -> NodePtr
{
  LOG(LogLevel::INFO, "TERMINATOR");
  NodePtr node{nullptr};


  return node;
}

// action           : '{' newline_opt                             '}'
//                  | '{' newline_opt terminated_statement_list   '}'
//                  | '{' newline_opt unterminated_statement_list '}'
//                  ;
auto Parser::action() -> NodePtr
{
  LOG(LogLevel::INFO, "ACTION");
  NodePtr node{nullptr};

  // TODO: Figure a way out to cleanly compare these two
  const auto accolade_open{next_token()};

  if(auto newline_opt_ptr{newline_opt()}; newline_opt_ptr) {
    if(auto terminated_ptr{terminated_statement_list()}; terminated_ptr) {
    } else if(auto unterminated_ptr{unterminated_statement_list()};
              unterminated_ptr) {
    } else {
      // TODO:: Error handling
    }
  } else {
    // TODO: ERROR HANDLING
  }

  const auto accolade_close{next_token()};

  return node;
}

// special_pattern  : Begin
//                  | End
//                  ;
auto Parser::special_pattern() -> NodePtr
{
  LOG(LogLevel::INFO, "SPECIAL PATTERN");
  NodePtr node{nullptr};

  return node;
}

// normal_pattern   : expr
//                  | expr ',' newline_opt expr
//                  ;
auto Parser::normal_pattern() -> NodePtr
{
  LOG(LogLevel::INFO, "NORMAL PATTERN");
  NodePtr node{nullptr};

  return node;
}

// pattern          : normal_pattern
//                  | special_pattern
//                  ;
auto Parser::pattern() -> NodePtr
{
  LOG(LogLevel::INFO, "PATTERN");
  NodePtr node{nullptr};

  if(auto normal_pattern_ptr{normal_pattern()}; normal_pattern_ptr) {
    node = std::move(normal_pattern_ptr);
  } else if(auto special_pattern_ptr{special_pattern()}; special_pattern_ptr) {
    node = std::move(special_pattern_ptr);
  }

  return node;
}

// param_list       : NAME
//                  | param_list ',' NAME
//                  ;
auto Parser::param_list() -> NodePtr
{
  LOG(LogLevel::INFO, "PARAM LIST");
  NodePtr node{nullptr};

  // const auto token{next_token()};

  return node;
}

// param_list_opt   : /* empty */
//                  | param_list
//                  ;
auto Parser::param_list_opt() -> NodePtr
{
  LOG(LogLevel::INFO, "PARAM LIST OPT");
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
  LOG(LogLevel::INFO, "ITEM");
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
  LOG(LogLevel::INFO, "ITEM LIST");
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
  LOG(LogLevel::INFO, "PROGRAM");
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

auto Parser::eos() -> bool
{
  return m_tokenstream.eos();
}

auto Parser::parse() -> Ast
{
  using namespace reserved;

  PRINT("=== PARSING ===");

  Ast ast;
  for(; !eos(); next_token()) {
    // Ast is pieced together from calling nested functions
    // That each return a NodePtr to eachother
    // ast.add(toplevel());
  }

  program();

  PRINT();
  return ast;
}

Parser::~Parser()
{
}
