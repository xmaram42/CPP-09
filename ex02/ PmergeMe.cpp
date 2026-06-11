#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    _vector = other._vector;
    _deque = other._deque;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::run(int ac, char **av)
{
    if (!parseInput(ac, av))
        throw std::runtime_error("Error");

    printBefore();
}

void PmergeMe::printBefore() const
{
    std::cout << "Before:";

    for (size_t i = 0; i < _vector.size(); i++)
        std::cout << " " << _vector[i];

    std::cout << std::endl;
}

bool PmergeMe::parseInput(int ac, char **av)
{
    if(ac < 2)
        return(false);

    int i = 1;
    while(i < ac)
    {
        std::string str = av[i];
        if (str.empty())
            return (false);

        size_t  j = 0;
        while(j < str.length())
        {
            if(!std::isdigit(str[j]))
                return(false);
            j++;
        }

        std::stringstream ss(str);
        long number;

        ss >> number;

        if (ss.fail())
            return false;

        if (number <= 0 || number > INT_MAX)
            return false;

        _vector.push_back(static_cast<int>(number));
        _deque.push_back(static_cast<int>(number));

        i++;
    }
    return(true);
}

