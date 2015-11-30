#ifndef EAST_EXCEPTIONS
#define EAST_EXCEPTIONS
#include <stdexcept>

namespace east
{
  class unexpected_token
    :public std::logic_error
  {
  public:
    unexpected_token(const char* symbol);
  };

  class not_operator
    :public std::logic_error
  {
  public:
    not_operator(const char* symbol);
  };

  class not_operand
    :public std::logic_error
  {
  public:
    not_operand(const char* symbol);
  };

  class not_matched
    :public std::logic_error
  {
  public:
    not_matched();
  };

  class unknown_node
    :public std::logic_error
  {
  public:
    unknown_node(const char* symbol);
  };

}

#endif
