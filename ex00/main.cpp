#include "BitcoinExchange.hpp"

int main(int  ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 0;
	}
	try
	{
		std::string data = "data.csv";
		std::string file = av[1];
		BitcoinExchange be;
		std::map<std::string, double> dataBase = be.getData();
		be.start(file, dataBase);

	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
