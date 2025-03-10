#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <ctime>
#include <vector>
#include <list>


class PmergeMe {
	public:
		typedef std::vector<int>	vec1;
		typedef	std::vector< vec1 >	vec2;
		typedef std::list<int>	list1;
		typedef	std::list< list1 >	list2;

	private:
		vec1 data;
		vec2 arr;
		list1 Ldata;
		list2 Larr;
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& copy);
		~PmergeMe();

		void	launch(int ac, char **av);
		vec1	merge();
		void	sort();
		void 	insert_(vec1 tmp);

		void	Llaunch(int ac, char **av);
		list1	Lmerge();
		void	Lsort();
		void 	Linsert_(list1 tmp);
};

#endif