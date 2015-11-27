#ifndef OPERATOR_INFO_HPP
#define OPERATOR_INFO_HPP
#include <string>
#include <exception>
namespace east
{

  enum class operator_type
  {
    FUNCTION,BINARY,UNARY,LBRAKET,RBRAKET,SENTINEL
      };
  
  enum class operator_associativity
  {
    LEFT,RIGHT,NONE
      };
  
  class operator_info
  {
    public:
      std::string symbol;
      operator_type type;
      operator_associativity associativity;
      int precedence;
      static const operator_info SENTINEL;
    public:
      operator_info(const std::string& s,const operator_type& t,
		    const operator_associativity& a,int p);
      
    public:
      bool operator==(const operator_info& rhs)const;
      bool higher_than(const operator_info& rhs)const;
    };
}

#endif
