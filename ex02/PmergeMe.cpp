#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
}

PmergeMe::PmergeMe(const PmergeMe& copy) {
	*this = copy;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& copy) {
	this->data = copy.data;
	this->arr = copy.arr;
	this->Larr = copy.Larr;
	this->Ldata = copy.Ldata;
	return *this;
}
PmergeMe::~PmergeMe() {

}

static void	print(PmergeMe::vec2 arr) {
	for (size_t i = 0; i < arr.size(); i++) {
		for (size_t j = 0; j < arr[i].size(); j++) {
			std::cout << " " << arr[i][j];
		}
	}
	std::cout << std::endl;
}

static void check_dup(PmergeMe::vec1 vc){
	for(size_t i = 0; i < vc.size(); i++){
		for(size_t j = i + 1; j < vc.size(); j++){
			if(vc[i] == vc[j])
				throw std::invalid_argument("Error wrong argument");
		}
	}
}

static int check_aruments(std::string av){
	for (size_t i = 0; i < av.length(); i++){
		if (!isdigit(av[i]) && av[i] != ' ')
			return 0;
	}
	return 1;
}

static void check_errors(int ac, char **av, std::vector<int> &vec){
	for(int i = 1; i < ac; i++){
			if(check_aruments(av[i]) == 1){
				if(std::atoi(av[i]) >= 0 && std::atoi(av[i]) <= INT_MAX)
					vec.push_back(std::atoi(av[i]));
				else
					throw std::invalid_argument("Error wrong argument");
			}
			else
				throw std::invalid_argument("Error wrong argument");
	}

}

static	void mainfunc(PmergeMe::vec1 &vec, PmergeMe::vec2 &Secvec) {
	std::vector<int>::iterator it;
	for(it = vec.begin(); it != vec.end(); ++it){
		std::vector<int> tempvec;
		tempvec.push_back(*it);
		Secvec.push_back(tempvec);
	}
}

void	PmergeMe::launch(int ac, char **av) {
	clock_t start = clock();
	check_errors(ac, av, data);
	check_dup(data);
	mainfunc(data, arr);
	std::cout << "Before ";
	print(arr);
	sort();
	clock_t end = clock();
	std::cout << "After ";
	print(arr);
	std::cout << "Time to process a range of " << arr.size() << " elemens with std::vector : " << double(end - start) / CLOCKS_PER_SEC * 1000000 << " us\n";
}


static PmergeMe::vec1 swapvec(PmergeMe::vec1 vec1, PmergeMe::vec1 vec2){
	PmergeMe::vec1 vec;
	if (vec1.back() < vec2.back()){
		for (size_t i = 0; i < vec1.size(); i++){
			vec.push_back(vec1[i]);
		}
		for (size_t i = 0; i < vec2.size(); i++){
			vec.push_back(vec2[i]);
		}
	}
	else{
		for (size_t i = 0; i < vec2.size(); i++){
			vec.push_back(vec2[i]);
		}
		for (size_t i = 0; i < vec1.size(); i++){
			vec.push_back(vec1[i]);
		}
	}
	return vec;
}

PmergeMe::vec1 PmergeMe::merge() {
	vec1 tmp;
	vec2 newArr;

	if (arr.size() % 2 != 0)
	{
		tmp = arr.back();
		arr.pop_back();
	}
	for(size_t i = 0; i < arr.size(); i+=2){
		vec1 tmp1 = swapvec(arr[i], arr[i+1]);
		newArr.push_back(tmp1);
	}
	arr = newArr;
	return(tmp);
}

void PmergeMe::sort(){
	vec1 tmp;
	tmp = merge();
	if(arr.size() > 1){
		sort();
	}
	insert_(tmp);
}

static void spltvec(PmergeMe::vec2 &arr){
	PmergeMe::vec2 newarr;
	PmergeMe::vec1 tmp1;
	PmergeMe::vec1 tmp2;
	for(size_t i = 0; i < arr.size(); i++){
		for(size_t j = 0 ; j < (arr[i].size()); j++){
			if(j < arr[i].size() / 2)
				tmp1.push_back(arr[i][j]);
			else
				tmp2.push_back(arr[i][j]);
		}
		newarr.push_back(tmp1);
		newarr.push_back(tmp2);
		tmp1.clear();
		tmp2.clear();
	}
	arr = newarr;
}

static bool	compare(PmergeMe::vec1 v1, PmergeMe::vec1 v2){
	return (v1.back() < v2.back());
}
void update(PmergeMe::vec2::iterator& it, std::vector< std::pair<PmergeMe::vec2::iterator, PmergeMe::vec1> >& pend_pair){
	size_t i = 0;
    for (i = 0; i < pend_pair.size(); ++i) {
        if (pend_pair[i].first >= it)
            ++pend_pair[i].first;
    }
}

void PmergeMe::insert_(vec1 tmp){
	vec2 main;
	vec2 pend;

	std::vector< std::pair<vec2::iterator, vec1> > pend_pair;
	spltvec(arr);

	main.reserve(arr.size());
	main.push_back(arr[0]);
	main.push_back(arr[1]);

	vec2::iterator t;
	std::pair<vec2::iterator, vec1> tmp1;

	for(size_t i = 2; i < arr.size(); i += 2 ){
		t = main.insert(main.end(), arr[i+1]);
		tmp1.first = t;
		tmp1.second = arr[i];
		pend_pair.push_back(tmp1);
	}
	if (!tmp.empty()) {
		tmp1.first = main.end();
		tmp1.second = tmp;
		pend_pair.push_back(tmp1);
	}

	vec2::iterator it;
	for (size_t i = 0; i < pend_pair.size(); i++) {
		it = std::lower_bound(main.begin(), pend_pair[i].first, pend_pair[i].second, compare);
		main.insert(it, pend_pair[i].second);
		update(it, pend_pair);
	}
	arr = main;
}

static void check_dup_list(PmergeMe::list1 lst){

	for (PmergeMe::list1::iterator it1 = lst.begin(); it1 != lst.end(); ++it1) {
        for (PmergeMe::list1::iterator it2 = std::next(it1); it2 != lst.end(); ++it2) {
            if (*it1 == *it2)
                throw std::invalid_argument("Error wrong argument");
        }
    }
}
static int check_aruments_list(std::string av){
	for (size_t i = 0; i < av.length(); i++){
		if (!isdigit(av[i]) && av[i] != ' ')
			return 0;
	}
	return 1;
}

static void check_errors_list(int ac, char **av, std::list<int> &lst){
	for(int i = 1; i < ac; i++){
			if(check_aruments_list(av[i]) == 1){
				if(std::atoi(av[i]) >= 0 && std::atoi(av[i]) <= INT_MAX)
					lst.push_back(std::atoi(av[i]));
				else
					throw std::invalid_argument("Error wrong argument");
			}
			else
				throw std::invalid_argument("Error wrong argument");
	}


}
static	void mainfunc_list(PmergeMe::list1 &lst, PmergeMe::list2 &Seclst) {
	std::list<int>::iterator it;
	for(it = lst.begin(); it != lst.end(); ++it){
		std::list<int> tempvec;
		tempvec.push_back(*it);
		Seclst.push_back(tempvec);
	}
}
static PmergeMe::list1 swaplst(PmergeMe::list1 list1, PmergeMe::list1 list2){
	PmergeMe::list1 lst;
    if (list1.back() < list2.back()) {
        lst.insert(lst.end(), list1.begin(), list1.end());
        lst.insert(lst.end(), list2.begin(), list2.end());
    }
	else {
        lst.insert(lst.end(), list2.begin(), list2.end());
        lst.insert(lst.end(), list1.begin(), list1.end());
    }
    return lst;
}

PmergeMe::list1 PmergeMe::Lmerge() {
	list1 tmp;
	list2 newArr;

	if (Larr.size() % 2 != 0)
	{
		tmp = Larr.back();
		Larr.pop_back();
	}
	list2::iterator it = Larr.begin();
	while(it != Larr.end()){
		list1 tmp1 = swaplst(*it, *(std::next(it)));
		newArr.push_back(tmp1);
		std::advance(it, 2);
	}
	Larr = newArr;
	return(tmp);
}
static void spltlst(PmergeMe::list2 &arr){
	PmergeMe::list2 newlst;
	PmergeMe::list1 tmp1;
	PmergeMe::list1 tmp2;
	for(PmergeMe::list2::iterator it = arr.begin(); it != arr.end(); ++it){
		size_t midpoint = it->size() / 2;

		PmergeMe::list1::iterator it1 = it->begin();
		for(size_t j = 0 ; it1 != it->end(); j++, ++it1){
			if(j < midpoint)
				tmp1.push_back(*it1);
			else
				tmp2.push_back(*it1);
		}
		newlst.push_back(tmp1);
		newlst.push_back(tmp2);
		tmp1.clear();
		tmp2.clear();
	}
	arr = newlst;
}
static bool	lcompare(PmergeMe::list1 v1, PmergeMe::list1 v2){
	return (v1.back() < v2.back());
}

void PmergeMe::Linsert_(list1 tmp){
	list2 main;
	list2 pend;

	std::list< std::pair<list2::iterator, list1> > pend_pair;
	spltlst(Larr);

	main.push_back(*Larr.begin());
	main.push_back(*std::next(Larr.begin()));

	list2::iterator t;
	std::pair<list2::iterator, list1> tmp1;

	for(list2::iterator tt = std::next(Larr.begin(), 2); tt != Larr.end(); std::advance(tt ,2) ){
		t = main.insert(main.end(), *std::next(tt, 1));
		tmp1.first = t;
		tmp1.second = *tt;
		pend_pair.push_back(tmp1);

	}
	if (!tmp.empty()) {
		tmp1.first = main.end();
		tmp1.second = tmp;
		pend_pair.push_back(tmp1);
	}

	list2::iterator it;
	for (std::list<std::pair<list2::iterator, list1> >::iterator pendIt = pend_pair.begin(); pendIt != pend_pair.end(); ++pendIt) {
        it = std::lower_bound(main.begin(), pendIt->first , pendIt->second, lcompare);
        main.insert(it, pendIt->second);
    }
	Larr = main;
}

void PmergeMe::Lsort(){
	list1 tmp;
	tmp = Lmerge();
	if(Larr.size() > 1){
		Lsort();
	}
	Linsert_(tmp);
}

void	PmergeMe::Llaunch(int ac, char **av) {
	clock_t start = clock();
	check_errors_list(ac, av, Ldata);
	check_dup_list(Ldata);
	mainfunc_list(Ldata, Larr);
	Lsort();
	clock_t end = clock();
	std::cout << "Time to process a range of " << Larr.size() << " elemens with std::list : " << double(end - start) / CLOCKS_PER_SEC * 1000000 << " us\n";

}