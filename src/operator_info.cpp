#include <operator_info.hpp>
#include <exception>
#include <stdexcept>
#include <east_exceptions.hpp>

namespace east
{
  const operator_info operator_info::SENTINEL("SENTINEL",operator_type::SENTINEL,operator_associativity::NONE,0);

  
  operator_info::operator_info(const std::string& s,const operator_type& t,
		const operator_associativity& a,int p)
    :symbol(s),type(t),associativity(a),precedence(p)
  {
  }

  bool operator_info::operator==(const operator_info& rhs)const
  {
    return symbol==rhs.symbol&&
      type==rhs.type&&
      associativity==rhs.associativity&&
      precedence==rhs.precedence;
  }
  
  bool operator_info::higher_than(const operator_info& rhs)const
  {
    if(type==operator_type::BINARY &&
       rhs.type==operator_type::BINARY)
      {
	return precedence>rhs.precedence||
	  (precedence==rhs.precedence&&associativity==operator_associativity::LEFT);
      }
    else if (type==operator_type::UNARY&&
	     rhs.type==operator_type::BINARY)
      {
	return precedence>=rhs.precedence;
      }
    else if ((type==operator_type::UNARY||
	      type==operator_type::BINARY)&&
	     rhs.type==operator_type::UNARY)
      {
	return false;
      }
    else if (type==operator_type::SENTINEL &&
	     (rhs.type==operator_type::UNARY||
	      rhs.type==operator_type::BINARY))
      {
	return false;
      }
    else if ((type==operator_type::BINARY||
	      type==operator_type::UNARY)&&
	     rhs.type==operator_type::SENTINEL)
      {
	return true;
      }
    else if (type==operator_type::FUNCTION)
      {
	return true;
      }
    else if (rhs.type==operator_type::FUNCTION&&type!=operator_type::FUNCTION)
      {
	return false;
      }
    throw std::logic_error("should never reach here");
    return false;
  }
}
