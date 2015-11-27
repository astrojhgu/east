#include <tokenizer.hpp>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <east_exceptions.hpp>
namespace east
{
  const token token::END({"END"},token_type::END);
  const token token::LBRAKET({"("},token_type::LBRAKET);
  const token token::RBRAKET({")"},token_type::RBRAKET);
  
  token::token(const std::string& s,const token_type& t)
    :symbol(s),type(t)
  {}
  
  bool token::operator==(const token& rhs)const
  {
    return symbol==rhs.symbol&&type==rhs.type;
  }

  bool token::is_value()const
  {
    return type==token_type::NUMBER||type==token_type::VARIABLE;
  }

  bool token::is_operator()const
  {
    return type==token_type::OPERATOR||
      type==token_type::BINARY||
      type==token_type::UNARY;
  }

  bool token::is_binary()const
  {
    return type==token_type::BINARY;
  }

  bool token::is_unary()const
  {
    return type==token_type::UNARY;
  }

  bool token::is_function()const
  {
    return type==token_type::FUNCTION;
  }

  bool token::is_variable()const
  {
    return type==token_type::VARIABLE;
  }

  bool token::is_number()const
  {
    return type==token_type::NUMBER;
  }

  bool token::is_operand()const
  {
    return is_number()||is_variable();
  }

  bool token::is_comma()const
  {
    return type==token_type::COMMA;
  }
    
  std::string token::to_string()const
  {
    std::string result;
    result+=symbol;
    result+=",";
    switch(type)
      {
      case token_type::NUMBER:
	result+="number";
	break;
      case token_type::VARIABLE:
	result+="variable";
	break;
      case token_type::OPERATOR:
	result+="operator";
	break;
      case token_type::BINARY:
	result+="binary";
	break;
      case token_type::UNARY:
	result+="unary";
	break;
      case token_type::FUNCTION:
	result+="function";
	break;
      case token_type::LBRAKET:
	result+="left braket";
	break;
      case token_type::RBRAKET:
	result+="right braket";
	break;
      case token_type::COMMA:
	result+="comma";
	break;
      case token_type::END:
	result+="end";
	break;
      }
    return result;
  }


  operator_info token::get_operator()const
  {
    if((!is_operator())&&(!is_function()))
      {
	throw not_operator(symbol.c_str());
      }
    if(symbol=="+"||
       symbol=="-")
      {
	if(is_unary())
	  {
	    return operator_info(symbol,operator_type::UNARY,operator_associativity::NONE,3);
	  }
	else
	  {
	    return operator_info(symbol,operator_type::BINARY,operator_associativity::LEFT,2);
	  }
      }
    else if(symbol=="*"||
	    symbol=="/")
      {
	return operator_info(symbol,operator_type::BINARY,operator_associativity::LEFT,4);
      }
    else if(symbol=="^")
      {
	return operator_info(symbol,operator_type::BINARY,operator_associativity::RIGHT,5);
      }
    else if(is_function())
      {
	return operator_info(symbol,operator_type::FUNCTION,operator_associativity::NONE,1);
      }
    else
      {
	throw std::logic_error("should never reach here");
	return operator_info("",operator_type::FUNCTION,operator_associativity::NONE,0);
      }
  }

  std::shared_ptr<expression_node> token::get_operand()const
  {
    if((!is_variable())&&(!is_number()))
      {
	std::string msg;
	throw not_operand(symbol.c_str());
      }
    return std::make_shared<expression_node>(symbol);
  }
  
  
  
  token_pattern::token_pattern(const std::string& p,const token_type t)
    :pattern(std::string("^(")+p+")"),type(t)
  {}

  tokenizer::tokenizer()
  {
    //add_pattern("sin\\(|cos\\(|tan\\(|exp\\(|log\\(|log10\\(|sqrt\\(",token_type::FUNCTION); // function
    add_pattern("[a-zA-Z][a-zA-Z0-9_]*\\s*\\(",token_type::FUNCTION); // function
    add_pattern("\\(",token_type::LBRAKET); // open bracket
    add_pattern("\\)",token_type::RBRAKET); // close bracket
    add_pattern("[+-]",token_type::OPERATOR); // plus or minus
    add_pattern("[*/]",token_type::OPERATOR); // mult or divide
    add_pattern("\\^",token_type::OPERATOR); // raised
    add_pattern("[0-9]+\\.?[0-9]*((E|e)(\\+|\\-)?[0-9]+)*",token_type::NUMBER); // integer number
    add_pattern("[a-zA-Z][a-zA-Z0-9_]*",token_type::VARIABLE); // variable
    add_pattern(",",token_type::COMMA); // variable
  }

  std::string tokenizer::trim(std::string const& str)
  {
    if(str.empty())
      return str;
    
    std::size_t firstScan = str.find_first_not_of(' ');
    std::size_t first     = firstScan == std::string::npos ? str.length() : firstScan;
    std::size_t last      = str.find_last_not_of(' ');
    return str.substr(first, last-first+1);
  }
  
  
  void tokenizer::add_pattern(const std::string& p,const token_type t)
  {
    token_patterns.push_back(token_pattern(p,t));
  }

  std::vector<token> tokenizer::tokenize(const std::string& _input)
  {
    std::vector<token> result;
    std::string input(trim(_input));
    while(input!="")
      {
	bool matched=false;
	
	for(auto& t:token_patterns)
	  {
	    std::smatch sm;
	    if(std::regex_search(input,sm,t.pattern))
	      {
		matched=true;
		//result.push_back(sm[0]);
		token tk(sm[0],t.type);
		if(t.type==token_type::OPERATOR)
		  {
		    if(result.empty()||
		       result.back().type==token_type::LBRAKET||
		       result.back().is_operator()||
		       result.back().is_function())
		      {
			tk.type=token_type::UNARY;
		      }
		    else
		      {
			tk.type=token_type::BINARY;
		      }
		  }
		else if(t.type==token_type::FUNCTION)
		  {
		    if(tk.symbol.back()=='(')
		      {
			tk.symbol.pop_back();
			tk.symbol=trim(tk.symbol);
		      }
		  }
		//std::cout<<(tk.type==token_type::NUMBER)<<" "<<tk.is_number()<<std::endl;
		result.push_back(tk);
		input=trim(std::regex_replace(input,t.pattern,""));
		break;
	      }
	    
	  }
	
	if(!matched)
	  {
	    throw not_matched();
	  }
      }
    return result;
  }

  
};
