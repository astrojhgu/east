#include <east_exceptions.hpp>

namespace east
{
  unexpected_token::unexpected_token(const char* symbol)
    :std::logic_error(symbol)
  {}

  not_operator::not_operator(const char* symbol)
    :std::logic_error(symbol)
  {}

  not_operand::not_operand(const char* symbol)
    :std::logic_error(symbol)
  {}

  not_matched::not_matched()
    :std::logic_error("not matched")
  {}
};
