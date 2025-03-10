#include "PmergeMe.hpp"

int main(int ac, char **av){
	if (ac > 1){
		try{
			PmergeMe test;
			test.launch(ac, av);
			test.Llaunch(ac, av);
		}
		catch(std::exception &e){
			std::cout << e.what() << std::endl;
		}
	}
}