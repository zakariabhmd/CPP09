#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include <sstream>
# include <map>
# include <stdexcept>
#include <iterator>
# include <list>

class BitcoinExchange
{

	public:

		BitcoinExchange();
		BitcoinExchange( BitcoinExchange const & __unused src );
		~BitcoinExchange();
		void start( std::string &name , std::map<std::string , double> &dataBase);
		BitcoinExchange &		operator=( BitcoinExchange const & __unused rhs );
		std::map<std::string, double>	getData();

	private:
		void	_openFile(const std::string fileName, std::map<std::string , double> &dataBase);
		bool	_checkDate(const std::string &date);
		bool	_checkValue(const double &value);
		bool	_checkValue(const std::string &value);


};

std::ostream &			operator<<( std::ostream & o, BitcoinExchange const & i );
std::list<std::string> ftSplit(const std::string &str, char delimiter);
void printDatabase(const std::map<std::string, double>& database) ;
#endif
