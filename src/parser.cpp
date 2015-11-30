#include <parser.hpp>
#include <iostream>
#include <east_exceptions.hpp>
namespace east
{

  parser::parser()
    :token_index(-1)
  {}

  const token& parser::next()const
    {
      if(token_index+1>=tokens.size())
	{
	  return token::END;
	}
      return tokens[1+token_index];
    }

  void parser::consume()
  {
    if(next()==token::END)
      {
	return;
      }
    ++token_index;
  }
  
  void parser::expect(const token& tok)
  {
    if(next()==tok)
      {
	consume();
      }
    else
      {
	throw unexpected_token(next().symbol.c_str());
      }
  }

  std::shared_ptr<expression_node> parser::parse(std::string input)
  {
    tokens=tkn.tokenize(input);
    token_index=-1;
    while(!operator_stack.empty())operator_stack.pop();
    while(!operand_stack.empty())operand_stack.pop();
    
    return Eparse();
  }
  
  std::shared_ptr<expression_node> parser::Eparse()
  {
    operator_stack.push(operator_info::SENTINEL);
    E();
    expect(token::END);
    return operand_stack.top();
  }
  
  void parser::E()
  {
    P();
    while(next().is_binary())
      {
	push_operator(next().get_operator());
	consume();
	P();
      }
    while(operator_stack.top().type!=operator_type::SENTINEL)
      {
	pop_operator();
      }
  }

  void parser::Q()
  {
    E();
    int n=1;
    while(next().is_comma())
      {
	consume();
	E();
	++n;
      }
    operator_stack.pop();
    pop_operator(n);
  }
  

  void parser::P()
  {
    if(next().is_operand())
      {
	operand_stack.push(next().get_operand());
	consume();
      }
    else if(next().type==token_type::LBRAKET)
      {
	consume();
	operator_stack.push(operator_info::SENTINEL);
	E();
	expect(token::RBRAKET);
	operator_stack.pop();
      }
    else if(next().is_unary())
      {
	push_operator(next().get_operator());
	consume();
	P();
      }
    else if(next().is_function())
      {
	push_operator(next().get_operator());
	consume();
	operator_stack.push(operator_info::SENTINEL);
	Q();
	expect(token::RBRAKET);
      }
    else
      {
	throw unexpected_token(next().symbol.c_str());
      }
  }
  
  void parser::pop_operator()
  {
    if(operator_stack.top().type==operator_type::BINARY)
      {
	auto t1=operand_stack.top();
	operand_stack.pop();
	auto t0=operand_stack.top();
	operand_stack.pop();
	auto new_node=std::make_shared<expression_node>(operator_stack.top());
	operator_stack.pop();
	new_node->parents.push_back(t0);
	new_node->parents.push_back(t1);
	operand_stack.push(new_node);
      }
    else
      {
	auto t0=operand_stack.top();
	operand_stack.pop();
	auto new_node=std::make_shared<expression_node>(operator_stack.top());
	operator_stack.pop();
	new_node->parents.push_back(t0);
	operand_stack.push(new_node);
      }
  }
  
  void parser::pop_operator(int n)
  {
    auto new_node=std::make_shared<expression_node>(operator_stack.top());
    operator_stack.pop();

    std::stack<std::shared_ptr<expression_node> > temp_stack;
    
    for(int i=0;i<n;++i)
      {
	temp_stack.push(operand_stack.top());
	operand_stack.pop();
      }
    while(!temp_stack.empty())
      {
	new_node->parents.push_back(temp_stack.top());
	temp_stack.pop();
      }
    operand_stack.push(new_node);
  }
  
  void parser::push_operator(const operator_info& op)
  {
    while(operator_stack.top().higher_than(op))
      {
	pop_operator();
      }
    operator_stack.push(op);
  }
};
