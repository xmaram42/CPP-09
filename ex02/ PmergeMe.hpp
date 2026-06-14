#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <sstream>
#include <cctype>
#include <climits>
#include <stdexcept>

class PmergeMe
{
private:
    std::vector<int> _vector;
    std::deque<int> _deque;

    bool parseInput(int ac, char **av);
    void printBefore() const;
    void printAfter(const std::vector<int>& sorted) const;

    std::vector<int> sortVector(std::vector<int> input);
    void insertSortedVector(std::vector<int>& chain, int value);

    std::deque<int> sortDeque(std::deque<int> input);
    void insertSortedDeque(std::deque<int>& chain, int value);

    std::deque<size_t> getJacobsthalOrderDeque(size_t size) const
    std::deque<size_t> getJacobsthalOrderVector(size_t size) const
public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    void run(int ac, char **av);
};

#endif