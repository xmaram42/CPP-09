#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <sstream>
#include <stdexcept>

class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;

        bool parseInput(int ac, char **av);
        bool isValidNumber(const std::string& str) const;

        
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void run(int argc, char **argv);



};
#endif