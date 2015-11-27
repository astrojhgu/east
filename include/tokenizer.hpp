#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <list>
#include <regex>
#include <vector>
#include <operator_info.hpp>
#include <expression_node.hpp>
#include <memory>

namespace east
{
  enum class token_type
  {
    NUMBER,
      VARIABLE,
      OPERATOR,
    BINARY,
      UNARY,
      FUNCTION,
      LBRAKET,
      RBRAKET,
      COMMA,
      END
      };
  
  class token_pattern
  {
  public:
    std::regex pattern;
    token_type type;
  public:
    token_pattern(const std::string& p,const token_type t);
  };

  class token
  {
  public:
    std::string symbol;
    token_type type;
  public:
    token(const std::string& s,const token_type& t);
    static const token END;
    static const token LBRAKET;
    static const token RBRAKET;
    
  public:
    bool operator==(const token& rhs)const;
    bool is_value()const;
    bool is_operator()const;
    bool is_binary()const;
    bool is_unary()const;
    bool is_function()const;
    bool is_variable()const;
    bool is_number()const;
    bool is_operand()const;
    bool is_comma()const;

    std::string to_string()const;

    operator_info get_operator()const;
    std::shared_ptr<expression_node> get_operand()const;    
  };
  
  class tokenizer
  {
  private:
    std::list<token_pattern> token_patterns;
    std::string trim(const std::string& str);
    
  private:
    void add_pattern(const std::string& p,const token_type t);
  public:
    tokenizer();
    
  public:
    std::vector<token> tokenize(const std::string& input);
    
    
  };
}

#endif
