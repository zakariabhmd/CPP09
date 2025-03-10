#include "RPN.hpp"

int main(int ac ,char **av){
	if(ac == 2){
		std::string str(av[1]);
		try{
			rpn(str);
		}
		catch(std::exception &e){
			std::cout << e.what() << std::endl;
		}
	}
}