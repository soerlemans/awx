#include "token.hpp"
#include "tokentype.hpp"


namespace tokentype {
auto is_int(const TokenType t_tokentype) -> bool
{
  switch(t_tokentype) {
      case TokenType::HEX:
        [[fallthrough]];

      case TokenType::INTEGER:
        return true;
        break;

      default:
        return false;
  }
}
}; // namespace tokentype
