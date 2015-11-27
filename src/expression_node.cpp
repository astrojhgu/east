#include <expression_node.hpp>


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
  
  std::ostream& operator<<(std::ostream& os,const expression_node& n)
  {
    std::string s=n.get_symbol();

    if(n.get_num_of_parents()!=0)
      {
	os<<"("<<s;
	
	for(int i=0;i<n.get_num_of_parents();++i)
	  {
	    os<<", "<<n.get_parent(i);
	  }
	os<<")";
      }
    else
      {
	os<<n.get_symbol();
      }
    return os;
  }
  
}
