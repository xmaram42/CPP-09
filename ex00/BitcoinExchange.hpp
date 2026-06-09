
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

class BitcoinExchange
{
private:
    std::map<std::string, double> _rates;

    bool isValidDate(const std::string& date) const;
    bool isLeapYear(int year) const;
    double searchDataSet(const std::string& date) const;


    
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void loadDatabase(const std::string &file);
    void takeFile(const std::string &file);
};

#endif