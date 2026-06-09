#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
class RPN
{
    private:
        std::stack<int> _stack;

        bool isOperator(char c) const;
        int calculateResult(int left, int right, char op) const;

    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();

        void calculate(const std::string& math);

};
#endif