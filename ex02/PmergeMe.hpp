#include <string>
#include <iostream>
#include <deque>
#include <vector>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <iterator>

class PmergeMe
{
	private:
		PmergeMe();
		std::vector<int>	_vector;

		std::vector<int>	_vector_sorted;
		std::deque<int>		_deque_sorted;

		int					_pairsize;
	public:
		PmergeMe(int ac, char **av);
		PmergeMe( PmergeMe const &src );
		~PmergeMe();

		PmergeMe	&operator=(PmergeMe const &rhs);

		clock_t	start;
		clock_t	vectortimer;
		clock_t	dequetimer;

		void	sort();
		void	sortVector();
		void	sortDeque(std::deque<int> deque, std::deque<int>::iterator begin, std::deque<int>::iterator end);

		void	makePair(std::pair<int, int> pairTab[], int *tmp);
		void	sortPair(std::pair<int, int> pairTab[], int amount);
		void	pushMaxToVec(std::pair<int, int> pairTab[]);
		void	pushMinToVec( std::pair<int, int> pairTab[], int *last);
		void	add_last(std::pair<int, int> pairTab[], int *last);
		bool	allpushed(std::pair<int, int> pairTab[]);

		std::vector<int> const	&getVector( void ) const;
		std::deque<int> const	&getDeque( void ) const;
};