#include "parser.hpp"

#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <tuple>

#include "../enum.hpp"
#include "../log.hpp"
#include "../token/token_type.hpp"
#include "../token/token_type_helpers.hpp"


// Class definitions:
Parser::Parser(TokenStream t_tokenstream): m_tokenstream{t_tokenstream}
{}

// Parsing grammar methods:
// This rule is made purely to discard any amount of newlines
// newline_opt      : /* empty */
//                  | newline_opt NEWLINE
//                  ;
auto Parser::newline_opt() -> void
{
  LOG(LogLevel::INFO, "NEWLINE OPT");

  for(; !eos(); next_token()) {
    const auto tokentype{m_tokenstream.token().type()};

    if(tokentype != TokenType::NEWLINE)
      break;
  }

  m_tokenstream.prev();
}

// simple_get       : GETLINE
//                  | GETLINE lvalue
//                  ;
auto Parser::simple_get() -> NodePtr
{
  LOG(LogLevel::INFO, "SIMPLE GET");
  NodePtr node{nullptr};

  // TODO: Implement GETLINE token

  // lvalue();
  return node;
}

// unary_input_function : unary_expr '|' simple_get
//                  ;
auto Parser::unary_input_function() -> NodePtr
{
  LOG(LogLevel::INFO, "UNARY_INPUT_FUNCTION");
  NodePtr node{nullptr};

  NodePtr lhs{unary_expr()};

  const auto token{next_token("|")};

  NodePtr rhs{simple_get()};

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

  const auto token{next_token("Identifier or a $")};
  switch(token.type()) {
    case TokenType::IDENTIFIER: {
      // We really dont expect these next_tokens to fail
      const auto brace_open{next_token()};

      // What do with expr_list???
      expr_list();

      const auto brace_close{next_token()};
      break;
    }

    case TokenType::DOLLAR_SIGN: {
      expr();
      break;
    }

    default:
      break;
  }

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

  const auto prefix{next_token("either a + or -")};
  if(prefix.type() == TokenType::PLUS || prefix.type() == TokenType::MINUS) {
    print_expr();
  } else {
    unary_print_expr();

    const auto op{next_token("expected operator")};

    print_expr();
  }

  return node;
}

// print_expr       : unary_print_expr
//                  | non_unary_print_expr
//                  ;
auto Parser::print_expr() -> NodePtr
{
  LOG(LogLevel::INFO, "PRINT EXPR");
  NodePtr node{nullptr};

  if(auto ptr{unary_print_expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{non_unary_print_expr()}; ptr) {
    node = std::move(ptr);
  }

  return node;
}

// print_expr_list  : print_expr
//                  | print_expr_list ',' newline_opt print_expr
//                  ;
auto Parser::print_expr_list() -> NodePtr
{
  LOG(LogLevel::INFO, "PRINT EXPR LIST");
  NodePtr node{nullptr};

  if(auto print_expr_ptr{print_expr()}; !print_expr_ptr)
    ; // Error handling

  const auto comma{next_token(",")};
  if(comma.type() != TokenType::COMMA) {
    m_tokenstream.prev();
  }

  newline_opt();
  print_expr();

  return node;
}

// print_expr_list_opt : /* empty */
//                  | print_expr_list
//                  ;
auto Parser::print_expr_list_opt() -> NodePtr
{
  LOG(LogLevel::INFO, "PRINT EXPR LIST OPT");
  NodePtr node{nullptr};

  print_expr_list();

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

  if(auto ptr{unary_expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{non_unary_expr()}; ptr) {
    node = std::move(ptr);
  } else {
    // TODO: Error handling
  }

  return node;
}

// expr_opt         : /* empty */
//                  | expr
//                  ;
auto Parser::expr_opt() -> NodePtr
{
  LOG(LogLevel::INFO, "EXPR OPT");
  NodePtr node{nullptr};

  if(auto ptr{expr()}; ptr) {
    node = std::move(ptr);
  }

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

  if(auto ptr{expr()}; ptr) {
    node = std::move(ptr);
  } else if(auto ptr{multiple_expr_list()}; ptr) {
    node = std::move(ptr);
  } else {
    // TODO: Error handling
  }

  return node;
}

// expr_list_opt    : /* empty */
//                  | expr_list
//                  ;
auto Parser::expr_list_opt() -> NodePtr
{
  LOG(LogLevel::INFO, "EXPR LIST OPT");
  NodePtr node{expr_list()};

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

  const auto token{next_token(">, >> or |")};

  switch(token.type()) {
    case TokenType::TRUNC:
      break;

    case TokenType::APPEND:
      break;

    case TokenType::PIPE:
      break;

    default:
      break;
  }

  // TODO: Pass this expr expression to the upper expressions
  expr();

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

  const auto print(next_token("Expected a print statement"));
  peek_token();
  next_token(")");


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

  const auto token{next_token(
    "Control statement token {if, while, for, ;, terminatable_statement}")};

  switch(token.type()) {
    case TokenType::IF: {
      const auto paren_open{next_token("(")};
      expr();
      const auto paren_close{next_token(")")};

      newline_opt();
      terminated_statement();

      if(!eos() && peek_token().type() == TokenType::ELSE) {
        newline_opt();
        terminated_statement();

        // TODO: Create Else node
      } else {
        // TODO: Create If node
      }
    }

    case TokenType::WHILE: {
      const auto paren_open{next_token("(")};
      expr();
      const auto paren_close{next_token(")")};
      newline_opt();
      terminated_statement();
    }

    case TokenType::FOR:
      break;

    case TokenType::SEMICOLON:
      newline_opt();
      break;

    default: {
      m_tokenstream.prev();

      terminatable_statement();
      const auto terminator_token{next_token("\\n or ;")};
      // TODO: Verify if is a is_terminator()
      newline_opt();
      break;
    }
  }

  return node;
}

// This rule is made to match atleast one unterminated statement
// Unterminated statements end on a -> \n
// unterminated_statement_list : unterminated_statement
//                  | terminated_statement_list unterminated_statement
//                  ;
auto Parser::unterminated_statement_list() -> NodePtr
{
  LOG(LogLevel::INFO, "UNTERMINATED STATEMENT LIST");
  NodePtr node{nullptr};


  if(auto unterminated_statement_ptr{unterminated_statement()};
     unterminated_statement_ptr) {
    // Add to NodeList

    while(!eos()) {
      auto ptr{unterminated_statement()};

      if(ptr) {
        // Add to NodeList
      } else {
        break;
      }
    }
  } else {
    // TODO: Error handling
    // EXCPECTED ATLEAST ONE...
  }

  return node;
}

// This rule is made to match atleast one terminated statement
// Terminated statements end on a -> ;
// terminated_statement_list : terminated_statement
//                  | terminated_statement_list terminated_statement
//                  ;
auto Parser::terminated_statement_list() -> NodePtr
{
  LOG(LogLevel::INFO, "TERMINATED STATEMENT LIST");
  NodePtr node{nullptr};

  if(auto terminated_statement_ptr{terminated_statement()};
     terminated_statement_ptr) {
    // Add to NodeList

    while(!eos()) {
      auto ptr{terminated_statement()};

      if(ptr) {
        // Add to NodeList
      } else {
        break;
      }
    }
  } else {
    // TODO: Error handling
    // EXCPECTED ATLEAST ONE...
  }

  return node;
}

// terminator       : terminator NEWLINE
//                  |            ';'
//                  |            NEWLINE
//                  ;
auto Parser::terminator() -> NodePtr
{
  LOG(LogLevel::INFO, "TERMINATOR IS NOT TESTED WARNING!!!!!");
  LOG(LogLevel::INFO, "TERMINATOR");
  NodePtr node{nullptr};

  for(; !eos(); next_token()) {
    const auto tokentype{m_tokenstream.token().type()};

    if(!tokentype::is_terminator(tokentype))
      break;
  }

  // if our last token was not a terminator go back to undo the lookahead
  m_tokenstream.prev();

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
  const auto accolade_open{next_token("}")};
  if(accolade_open.type() != TokenType::ACCOLADE_OPEN) {
    m_tokenstream.prev();
    return node;
  }

  newline_opt();

  if(auto terminated_ptr{terminated_statement_list()}; terminated_ptr) {
    // DO SOMETHING!
  } else if(auto unterminated_ptr{unterminated_statement_list()};
            unterminated_ptr) {
    // DO SOMETHING!
  } else {
    // TODO:: Error handling
  }

  const auto accolade_close{next_token("}")};
  if(accolade_close.type() != TokenType::ACCOLADE_CLOSE)
    ; // TODO: Error handling

  return node;
}

// special_pattern  : Begin
//                  | End
//                  ;
auto Parser::special_pattern() -> NodePtr
{
  LOG(LogLevel::INFO, "SPECIAL PATTERN");
  NodePtr node{nullptr};

  const auto token{next_token("BEGIN or END")};

  if(token.type() == TokenType::BEGIN) {
    LOG(LogLevel::DEBUG, "Found BEGIN!");

  } else if(token.type() == TokenType::END) {
    LOG(LogLevel::DEBUG, "Found END!");

  } else {
    m_tokenstream.prev();
  }

  return node;
}

// normal_pattern   : expr
//                  | expr ',' newline_opt expr
//                  ;
auto Parser::normal_pattern() -> NodePtr
{
  LOG(LogLevel::INFO, "NORMAL PATTERN");
  PRINT("{");
  NodePtr node{nullptr};

  if(auto expr_ptr{expr()}; expr_ptr) {
    const auto token{next_token(", or nothing")};
    if(token.type() == TokenType::COMMA) {
      newline_opt();
      expr();
    } else {
      m_tokenstream.prev();
    }
  }

  PRINT("}");

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

// param_list       : NAME_ptr
//                  | param_list ',' NAME_ptr
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

  if(auto ptr{action()}; ptr) {
    node = std::move(ptr);
  } else if(auto pattern_ptr{pattern()}; pattern_ptr) {
    auto action_ptr{action()};

    if(!action_ptr)
      throw 20; // TODO: Properly throw an error

    // Resolve this?
    // How should we represent this in AST?
  } else if(auto normal_pattern_ptr{normal_pattern()}; normal_pattern_ptr) {
    node = std::move(normal_pattern_ptr);
  } else if(true) {
    // TODO: Implement function parsing for now ignore?
  }

  return node;
}


// FIXME: This rule creates infinite recursion
// Possibly swap the order? This would seem to not affect the grammar
// item_list        : /* empty */
//                  | item_list item terminator
//                  ;
auto Parser::item_list() -> NodePtr
{
  LOG(LogLevel::INFO, "ITEM LIST");
  NodePtr node{nullptr};

  // TODO Piece these together some way into an AST structure
  if(auto item_ptr{item()}; item_ptr) {
    item_list();
    terminator();
  }

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

  if(auto item_ptr{item()}; item_ptr) {
    // item() is optional
  }

  return node;
}

// Regular methods again:
auto Parser::next_token(const std::string t_msg) -> Token&
{
  std::stringstream ss;
  ss << "Incomplete expression due to reaching EOS\n";
  ss << "Expected -> ";
  ss << t_msg;

  // TODO: Add a way for calls to next_token that are out of bounds to throw
  // A custom error message on what they expect either via overloading or
  if(eos())
    throw std::runtime_error{ss.str()};

  return m_tokenstream.next();
}

auto Parser::peek_token(const std::string t_msg) -> Token
{
  std::stringstream ss;
  ss << "Attempted to peek at EOS\n";
  ss << "Expected -> ";
  ss << t_msg;

  if(eos())
    throw std::runtime_error{ss.str()};

  const auto token{m_tokenstream.next()};

  m_tokenstream.prev();

  return token;
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

  program();

  PRINT();
  return ast;
}

Parser::~Parser()
{}
