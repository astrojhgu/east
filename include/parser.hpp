#ifndef PARSER_HPP
#define PARSER_HPP
#include <string>
#include <vector>
#include <memory>
#include <stack>
#include <tokenizer.hpp>
namespace east
{
  class parser
  {
  private:
    int token_index;
    tokenizer tkn;
    std::vector<token> tokens;

    std::stack<operator_info> operator_stack;
    std::stack<std::shared_ptr<expression_node> > operand_stack;

  public:
    parser();

  public:
    const token& next()const;
    void consume();
    void expect(const token& tok);
    std::shared_ptr<expression_node> parse(std::string input);
    std::shared_ptr<expression_node> Eparse();
    void E();
    void P();
    void Q();
    void pop_operator();
    void pop_operator(int n);
    void push_operator(const operator_info& op);
  };
  
}

#endif
