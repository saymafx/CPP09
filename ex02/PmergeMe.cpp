#include "PmergeMe.hpp"
#include <time.h>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int ac, char **av) {
	for (int i = 1; i <= ac - 1; i++) {
		_vector.push_back(atoi(av[i]));
		//_deque.push_back(atoi(av[i]));
	}
	_pairsize = (ac - 1) /2;
}

PmergeMe::~PmergeMe() {}

////////////////////////////////////////////////////////////////

void	PmergeMe::makePair(std::pair<int, int> pairTab[], int *tmp) {
	int	count = 0;
	std::vector<int>::iterator it_vec = _vector.begin();
	std::vector<int>::iterator next;

	while (it_vec != _vector.end()) {
		next = it_vec;
		next++;
		if (next == _vector.end()) {
			*tmp = *it_vec;
			break;
    	}
		pairTab[count].first = *it_vec;
		it_vec++;
		pairTab[count].second = *it_vec;
		it_vec++;
		count++;
	}
	return ;
}

void	PmergeMe::sortPair(std::pair<int, int> pairTab[], int amount) {
	int	tmp;

	for(int i = 0; i < amount; i++) {
		if (pairTab[i].first > pairTab[i].second) {
			tmp = pairTab[i].first;
			pairTab[i].first = pairTab[i].second;
			pairTab[i].second = tmp;
		}
	}
	return ;
}

bool	PmergeMe::allpushed(std::pair<int, int> pairTab[]) {
	for (int i = 0; i < _pairsize; i++) {
	
		if (pairTab[i].second >= 0) {
			return false;
		}
	}
	return true;
}

void	PmergeMe::pushMaxToVec( std::pair<int, int> pairTab[]) {
	int	tmp;

	if (allpushed(pairTab) == true)
		return ;
	tmp = pairTab[0].second;
	for (int i = 1; i < _pairsize; i++) {
		if (pairTab[i].second > tmp) {
			tmp = pairTab[i].second;
		}
	}
	for (int i = 0; i < _pairsize; i++) {
		if (tmp == pairTab[i].second) {
			pairTab[i].second = -1;;
			break ;
		}
	}
	_vector_sorted.insert(_vector_sorted.begin(), tmp);
	pushMaxToVec(pairTab);
	return ;
}

void	PmergeMe::pushMinToVec(std::pair<int, int> pairTab[], int *last) {
	int	tmp;

	tmp = pairTab[0].first;
	for (int i = 1; i < _pairsize; i++) {
		if (pairTab[i].first < tmp)
			tmp = pairTab[i].first;
	}
	for (int i = 0; i < _pairsize; i++) {
		if (tmp == pairTab[i].first) {
			if (*last >= 0 && tmp >= *last) {
				tmp = *last;
				*last = -10;
			}
			else
				pairTab[i].first = -1; 
			_vector_sorted.insert(_vector_sorted.begin(), tmp);
		}
	}
	return ;
}

void	PmergeMe::add_last(std::pair<int, int> pairTab[], int *last) {
	std::vector<int>::iterator	itr;
	int	i = 0;

	while (i < _pairsize) {
		if (pairTab[i].first > 0) {
			itr = std::lower_bound(_vector_sorted.begin(), _vector_sorted.end(), pairTab[i].first);
			_vector_sorted.insert(itr, pairTab[i].first);
		}
		i++;
	}
	if (*last >= 0) {
		itr = std::lower_bound(_vector_sorted.begin(), _vector_sorted.end(), *last);
		_vector_sorted.insert(itr, *last);
	}
	return ;
}

void	PmergeMe::sortVector() {
	std::pair<int, int>		pairs[_pairsize];
	int						last = -69;

	makePair(pairs, &last);
	sortPair(pairs, _pairsize);
	pushMaxToVec(pairs);
	// //print _vector_sorted
	// for (std::vector<int>::iterator it = _vector_sorted.begin(); it != _vector_sorted.end(); it++) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;
	pushMinToVec(pairs, &last);
	// //print _vector_sorted
	// for (std::vector<int>::iterator it = _vector_sorted.begin(); it != _vector_sorted.end(); it++) {
	// 	std::cout << *it << " ";
	// }
	// std::cout << std::endl;
	add_last(pairs, &last);

}

void	PmergeMe::sort(void) {
	std::vector<int>::iterator next;
	clock_t		start = std::clock();
	sortVector();
	clock_t		vectortimer = std::clock();

	std::cout << "\e[1;31mAfter\e[0m:	";
	for (std::vector<int>::iterator it = _vector_sorted.begin(); it != _vector_sorted.end(); it++) {
		next = it;	
		next++;
		if (next == _vector_sorted.end())
			std::cout << *it << std::endl;
		else
			std::cout << *it << " ";
	}
	long double	result = static_cast<long double>(vectortimer - start) / (CLOCKS_PER_SEC / 1000);
	std::cout << "Time to process a range of 5 elements with std::vector<int> : " << result << " us" << std::endl;

	start = std::clock();
	//sortDeque
	dequetimer = start - std::clock();

	return;
}