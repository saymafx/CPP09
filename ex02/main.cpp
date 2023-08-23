#include "PmergeMe.hpp"

int main(int ac, char **av) {
	if(ac < 2) {
		std::cout << "Error: not enough arguments!" << std::endl;
		return (0);
	}
	
	 for (int i = 1; i < ac; i++) {
        for(int j = 0; av[i][j] != '\0'; j++) {
            if (!isdigit(av[i][j])) {
                std::cout << "Error: Argument " << i << " is not a positive integer!" << std::endl;
                return 1;
            }
        }
		if (static_cast<unsigned  long long>(atoi(av[i])) > 2147483647) {
			std::cout << "Error: Argument " << i << " is bigger than an integer!" << std::endl;
			return 1;
		}
    }

	// std::vector<int>	vect;
	// std::deque<int>		deq;

	PmergeMe	sorter(ac, av);

	std::cout << "\e[1;31mBefore\e[0m:	";
	for (int i = 1; av[i]; i++) {

		if (!av[i + 1])
			std::cout << av[i] << std::endl;
		else
			std::cout << av[i] << " ";
	}
	
	sorter.sort();

	// clock_t		startVecTime = std::clock();


	// clock_t		endtVecTime = std::clock();
	// double		durationVector = static_cast<double>(startVecTime - endtVecTime) / CLOCKS_PER_SEC;
}