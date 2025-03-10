#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange & __unused src )
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange &				BitcoinExchange::operator=( BitcoinExchange const & __unused rhs )
{
	return *this;
}

std::ostream &			operator<<( std::ostream & o, BitcoinExchange const & __unused i )
{
	return o;
}

void BitcoinExchange::_openFile(const std::string fileName, std::map<std::string , double> &  dataBase)
{
	std::map<std::string, double> input;
	std::ifstream file(fileName);
	if(!file.is_open())
		throw std::ios_base::failure("Failed To open file : " + fileName);
	std::string line;
	std::getline(file, line);
	while(std::getline(file, line))
	{
		try
		{
			std::list<std::string> tokens = ftSplit(line, '|');
			if (tokens.size() > 1)
			{
			std::list<std::string>::iterator it = tokens.begin();
			std::string date = *tokens.begin();
			std::advance(it, 1);
			std::string value = *it;
			_checkDate(date);
				double amount = std::stod(value.c_str());
 			if (_checkValue(value) && _checkValue(amount))
			{
				double price = std::stod(value.c_str());
				input[date] = price;
				if (dataBase.find(date) == dataBase.end())
				{
					std::map<std::string, double>::iterator itData = dataBase.lower_bound(date);
					if (itData != dataBase.begin())
					{
						itData--;
						std::cout << date << " => " << price << " = " << itData->second * price << std::endl;
					}
				}
				else
				{
					std::cout << "Somthing Went wrong Please check : " << fileName << std::endl;
				}

			}
		}
		else
			std::cerr << "bad input => " << *tokens.begin() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

	}

}

bool BitcoinExchange::_checkValue(const std::string &value)
{
	if (value.size() == 0)
	{
		std::cout << "Error8 : Invalid input, missing Value " << std::endl;
		return 0;
	}
	for (size_t i = 0; i < value.size(); i++)
	{
		if (value[i] == ' ' || value[i] == '+' || value[i] == '-' || value[i] == '.' || value[i] == ',')
			continue;
		if(!std::isdigit(value[i]))
		{
			std::cerr << "Error7 : Invalid date, is Not Digit" << std::endl;
			return 0;
		}
	}
	return 1;
}

bool BitcoinExchange::_checkValue(const double &value)
{
	if (value <= 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return 0;
	}
	else if (value >= 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return 0;
	}
	return 1;
}
bool BitcoinExchange::_checkDate(const std::string &date)
{
	if (date.size() == 0)
	{
		std::cout << " Error1 : Invalid input, missing Value " << std::endl;
		return 0;
	}
	if(date.size() != 11)
	{
		std::cerr << "Error2 : Invalid date size" << std::endl;
		return 0;
	}
	else if (date[4] != '-' || date[7] != '-' )
	{
		std::cerr << "Error3 : Invalid date" << std::endl;
		return 0;
	}
	for (size_t i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7 || date[i] == ' ')
			continue;
		if (!std::isdigit(date[i]))
		{
			std::cerr << "Error4 : Invalid date, is Not Digit" << std::endl;
			return 0;
		}
	}
	return 1;
}

std::list<std::string> ftSplit(const std::string &str, char delimiter)
{
	std::list<std::string> tokens;
	std::string token;
	std::istringstream ss(str);
	while(getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void BitcoinExchange::start(std::string &Name, std::map<std::string , double> &dataBase)
{
	this->_openFile(Name, dataBase);
}

std::map<std::string, double> BitcoinExchange::getData()
{
	std::map<std::string, double> dataBase;
	std::ifstream file("data.csv");
	if (!file.is_open())
		throw std::ios_base::failure("Failed To open file : data.csv");
	std::string line;
	std::getline(file, line);
	while(std::getline(file, line))
	{
		std::list<std::string> tokens = ftSplit(line, ',');
		if (tokens.size() > 1)
		{
			std::list<std::string>::iterator it = tokens.begin();
			std::string date = *tokens.begin();
			std::advance(it, 1);
			std::string value = *it;
			double price = std::stod(value.c_str());
			dataBase[date] = price;
		}
	}
	return dataBase;
}

void printDatabase(const std::map<std::string, double>& database) {
    std::cout << "Database Contents:" << std::endl;
    std::map<std::string, double>::const_iterator it;
    for (it = database.begin(); it != database.end(); ++it) {
        std::cout << "Date: " << it->first << ", Price: " << it->second << std::endl;
    }
}
