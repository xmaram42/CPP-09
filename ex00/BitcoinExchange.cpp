
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    _rates = other._rates;
}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if(this != &other)
    {
         _rates = other._rates;
    }
    return(*this);
}
BitcoinExchange::~BitcoinExchange()
{

}

void BitcoinExchange::loadDatabase(const std::string &file) // it will read data.cvs
{
    std::ifstream db(file.c_str());
    std::string line;


    if(!db.is_open())
    {
        std::cerr << "Error: could not open database ." << std::endl;
        return;
    }
    std::getline(db, line);

    //date = "2011-01-03"
    //rate = 0.3
    //_rates["2011-01-03"] = 0.3;


    while(std::getline(db, line))
    {
        size_t comma = line.find(','); 
        if(comma == std::string::npos)
            continue;
        std::string date = line.substr(0, comma);
        std::string ratestr = line.substr(comma + 1);

        std::stringstream ss(ratestr);
        double rate;
        ss >> rate;
        _rates[date] = rate;
    }
}

void BitcoinExchange::takeFile(const std::string &file)
{
    std::ifstream input(file.c_str());
    std::string line;
    if(!input.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    std::getline(input, line);
   while (std::getline(input, line))
    {
        size_t pipe = line.find(" | ");

        if (pipe == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = line.substr(0, pipe);
        std::string value_str = line.substr(pipe + 3);

        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::stringstream ss(value_str);
        double value;

        ss >> value;

        if (ss.fail())
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }

        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        double rate = searchDataSet(date);

        if (rate < 0)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::cout << date << " => " << value << " = " << value * rate << std::endl;
    }
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    int year;
    int month;
    int day;
    int maxDays;

    if (date.length() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }
    year = std::atoi(date.substr(0, 4).c_str());
    month = std::atoi(date.substr(5, 2).c_str());
    day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return false;

    if (day < 1)
        return false;

    if (month == 2)
    {
        if (isLeapYear(year))
            maxDays = 29;
        else
            maxDays = 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        maxDays = 30;
    else
        maxDays = 31;

    if (day > maxDays)
        return false;

    return true;
}

bool BitcoinExchange::isLeapYear(int year) const
{
    if(year % 400 == 0)
        return (true);
    if(year % 100 == 0)
        return(false);
    if(year % 4 == 0)
        return(true);
    return(false);
}

double BitcoinExchange::searchDataSet(const std::string& date) const
{
    std::map<std::string, double>::const_iterator iter;

    iter = _rates.lower_bound(date);

    if (iter != _rates.end() && iter->first == date)
        return iter->second;

    if (iter == _rates.begin())
        return -1;

    --iter;
    return iter->second;
}
