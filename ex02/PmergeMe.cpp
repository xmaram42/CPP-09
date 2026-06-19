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

bool PmergeMe::parseInput(int ac, char **av)
{
    if (ac < 2)
        return false;
    int i = 1;
    while (i < ac)
    {
        std::string str = av[i];
        if (str.empty())
            return false;

        size_t j = 0;
        while (j < str.length())
        {
            if (!std::isdigit(str[j]))
                return false;
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
    return true;
}

void PmergeMe::run(int ac, char **av)
{
    std::vector<int> sortedVector;
    std::deque<int> sortedDeque;

    clock_t startVector;
    clock_t endVector;
    clock_t startDeque;
    clock_t endDeque;

    double vectorTime;
    double dequeTime;

    if (!parseInput(ac, av))
        throw std::runtime_error("Error");
    printBefore();
    startVector = clock();
    sortedVector = sortVector(_vector);
    endVector = clock();

    startDeque = clock();
    sortedDeque = sortDeque(_deque);
    endDeque = clock();

    if (sortedDeque.size() != sortedVector.size())
    throw std::runtime_error("Error");

    size_t k = 0;
    while (k < sortedVector.size())
    {
        if (sortedVector[k] != sortedDeque[k])
            throw std::runtime_error("Error");
        k++;
    }

    vectorTime = static_cast<double>(endVector - startVector) / CLOCKS_PER_SEC * 1000000;
    dequeTime = static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1000000;

    printAfter(sortedVector);

    std::cout << "Time to process a range of " << _vector.size()
              << " elements with std::vector : "
              << vectorTime << " us" << std::endl;

    std::cout << "Time to process a range of " << _deque.size()
              << " elements with std::deque : "
              << dequeTime << " us" << std::endl;
}


void PmergeMe::printBefore() const
{
    std::cout << "Before:";

    size_t i = 0;
    while (i < _vector.size())
    {
        std::cout << " " << _vector[i];
        i++;
    }
    std::cout << std::endl;
}

void PmergeMe::printAfter(const std::vector<int>& sorted) const
{
    std::cout << "After:";

    size_t i = 0;
    while (i < sorted.size())
    {
        std::cout << " " << sorted[i];
        i++;
    }

    std::cout << std::endl;
}
std::vector<int> PmergeMe::sortVector(std::vector<int> input)
{
    if (input.size() <= 1)
        return input;

    std::vector<int> chain;
    std::vector<int> pending;
    int leftover = 0;
    bool hasLeftover = false;
    size_t i = 0;

    while (i + 1 < input.size())
    {
        int first = input[i];
        int second = input[i + 1];

        if (first > second)
        {
            chain.push_back(first);
            pending.push_back(second);
        }
        else
        {
            chain.push_back(second);
            pending.push_back(first);
        }
        i = i + 2;
    }
    if (i < input.size())
    {
        leftover = input[i];
        hasLeftover = true;
    }
    chain = sortVector(chain);
    std::vector<size_t> order = getJacobsthalOrderVector(pending.size());
    i = 0;
    while (i < order.size())
    {
        insertSortedVector(chain, pending[order[i]]);
        i++;
    }
    if (hasLeftover)
        insertSortedVector(chain, leftover);
    return chain;
}
void PmergeMe::insertSortedVector(std::vector<int>& chain, int value)
{
    size_t left = 0;
    size_t right = chain.size();

    while (left < right)
    {
        size_t mid = left + (right - left) / 2;

        if (chain[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }

    chain.insert(chain.begin() + left, value);
}
std::deque<int> PmergeMe::sortDeque(std::deque<int> input)
{
    if (input.size() <= 1)
        return input;

    std::deque<int> chain;
    std::deque<int> pending;
    int leftover = 0;
    bool hasLeftover = false;
    size_t i = 0;

    while (i + 1 < input.size())
    {
        int first = input[i];
        int second = input[i + 1];

        if (first > second)
        {
            chain.push_back(first);
            pending.push_back(second);
        }
        else
        {
            chain.push_back(second);
            pending.push_back(first);
        }
        i = i + 2;
    }
    if (i < input.size())
    {
        leftover = input[i];
        hasLeftover = true;
    }
    chain = sortDeque(chain);
    std::deque<size_t> order = getJacobsthalOrderDeque(pending.size());
    i = 0;
    while (i < order.size())
    {
        insertSortedDeque(chain, pending[order[i]]);
        i++;
    }
    if (hasLeftover)
        insertSortedDeque(chain, leftover);
    return chain;
}

void PmergeMe::insertSortedDeque(std::deque<int>& chain, int value)
{
    size_t left = 0;
    size_t right = chain.size();

    while (left < right)
    {
        size_t mid = left + (right - left) / 2;

        if (chain[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    chain.insert(chain.begin() + left, value);
}

std::vector<size_t> PmergeMe::getJacobsthalOrderVector(size_t size) const
{
    std::vector<size_t> order;
    size_t prev;
    size_t curr;
    size_t next;
    size_t start;
    size_t end;

    if (size == 0)
        return order;
    order.push_back(0);

    prev = 1;
    curr = 3;
    while (order.size() < size)
    {
        start = prev + 1;
        end = curr;

        if (end > size)
            end = size;
        while (start <= end)
        {
            order.push_back(end - 1);
            if (end == start)
                break;
            end--;
        }
        next = curr + (2 * prev);
        prev = curr;
        curr = next;
    }
    return order;
}

std::deque<size_t> PmergeMe::getJacobsthalOrderDeque(size_t size) const
{
    std::deque<size_t> order;
    size_t prev;
    size_t curr;
    size_t next;
    size_t start;
    size_t end;

    if (size == 0)
        return order;
    order.push_back(0);
    prev = 1;
    curr = 3;
    while (order.size() < size)
    {
        start = prev + 1;
        end = curr;
        if (end > size)
            end = size;
        while (start <= end)
        {
            order.push_back(end - 1);
            if (end == start)
                break;
            end--;
        }
        next = curr + (2 * prev);
        prev = curr;
        curr = next;
    }
    return order;
}