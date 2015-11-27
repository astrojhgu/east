#ifndef EXPRESSION_NODE_HPP
#define EXPRESSION_NODE_HPP
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <operator_info.hpp>

namespace east
{
  class parser;
  class expression_node
  {
  private:
    std::vector<std::shared_ptr<expression_node> > parents;
    const std::string symbol;
  public:
    expression_node(const std::string& sym);
    expression_node(const operator_info& op);

  public:
    int get_num_of_parents()const;    
    const expression_node& get_parent(int n)const;
    const std::string& get_symbol()const;
  public:
    friend class parser;
  };

  std::ostream& operator<<(std::ostream& os,const expression_node& n);
}


#endif
