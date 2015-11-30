#include <expression_node.hpp>
#include <east_exceptions.hpp>
#include <regex>

namespace east
{
  expression_node::expression_node(const std::string& sym)
    :symbol(sym)
  {}
  
  
  expression_node::expression_node(const operator_info& op)
    :symbol(op.symbol)
  {}

  int expression_node::get_num_of_parents()const
  {
    return parents.size();
  }
  
  const expression_node& expression_node::get_parent(int n)const
  {
    return *(parents.at(n));
  }

  const std::string& expression_node::get_symbol()const
  {
    return symbol;
  }

  bool expression_node::operator<(const expression_node& rhs)const
    {
      if(symbol==rhs.symbol)
	{
	  return parents.size()<rhs.parents.size();
	}
      else
	{
	  return symbol<rhs.symbol;
	}
    }

  int expression_node::get_nparents()const
  {
    return parents.size();
  }

  std::string expression_node::get_kind()const
  {
    if(symbol=="+")
      {
	if(parents.size()==2)
	  {
	    return "add";
	  }
	else if(parents.size()==1)
	  {
	    return "pos";
	  }
	else
	  {
	    throw unknown_node(symbol.c_str());
	  }
      }
    else if(symbol=="-")
      {
	if(parents.size()==2)
	  {
	    return "sub";
	  }
	else if(parents.size()==1)
	  {
	    return "neg";
	  }
	else
	  {
	    throw unknown_node(symbol.c_str());
	  }
	
      }
    else if(symbol=="*")
      {
	if(parents.size()==2)
	  {
	    return "mul";
	  }
	else
	  {
	    throw unknown_node(symbol.c_str());
	  }	
      }
    else if(symbol=="/")
      {
	if(parents.size()==2)
	  {
	    return "div";
	  }
	else
	  {
	    throw unknown_node(symbol.c_str());
	  }
      }
    else if(symbol=="^")
      {
	if(parents.size()==2)
	  {
	    return "pow";
	  }
	else
	  {
	    throw unknown_node(symbol.c_str());
	  }
      }
    else if(parents.size()>0)
      {
	return "ftn";
      }
    else
      {
	std::regex regex_number("^([0-9]+\\.?[0-9]*((E|e)(\\+|\\-)?[0-9]+)*)");
	std::regex regex_variable("^([a-zA-Z][a-zA-Z0-9_]*)");
	if(std::regex_match(symbol,regex_number))
	  {
	    return "con";
	  }
	else if(std::regex_match(symbol,regex_variable))
	  {
	    return "var";
	  }
	else
	  {
	    throw unknown_node(symbol.c_str());
	  }
	return "unknown";	
      }
  }
  
  std::ostream& operator<<(std::ostream& os,const expression_node& n)
  {
    std::string s=n.get_symbol();

    if(n.get_num_of_parents()!=0)
      {
	os<<"("<<s<<":"<<n.get_kind();
	
	for(int i=0;i<n.get_num_of_parents();++i)
	  {
	    os<<", "<<n.get_parent(i);
	  }
	os<<")";
      }
    else
      {
	os<<"("<<n.get_symbol()<<":"<<n.get_kind()<<")";
      }
    return os;
  }
  
}
