#include "RPN.hpp"

RPN::RPN()
{
}
RPN::RPN(const RPN &other)
{
    _stack = other._stack;
}
RPN &RPN::operator=(const RPN &other)
{
    if(this != &other)
        _stack = other._stack;
    return *this;
}
RPN::~RPN()
{

}

void RPN::calculate(const std::string& math)
{
    std::stringstream ss(math);
    std::string token;

     while (ss >> token)
    {
        if (token.length() != 1)
        {
            std::cerr << "Error" << std::endl;
            return;
        }

        char c = token[0];

        if (std::isdigit(c))
            _stack.push(c - '0');
        else if (isOperator(c))
        {
            if (_stack.size() < 2)
            {
                std::cerr << "Error" << std::endl;
                return;
            }

            int right = _stack.top();
            _stack.pop();

            int left = _stack.top();
            _stack.pop();

            if (c == '/' && right == 0)
            {
                std::cerr << "Error" << std::endl;
                return;
            }
            int result = calculateResult(left, right, c);
            _stack.push(result);
        }
        else
        {
            std::cerr << "Error" << std::endl;
            return;
        }
    }
    if (_stack.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        return;
    }
    std::cout << _stack.top() << std::endl;
}
bool RPN::isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::calculateResult(int left, int right, char op) const
{
    if (op == '+')
        return (left + right);
    if (op == '-')
        return (left - right);
    if (op == '*')
        return (left * right);
    if (op == '/')
        return (left / right);
    return 0;
}