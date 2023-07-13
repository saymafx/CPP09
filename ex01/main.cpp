#include <iostream>
#include <string>
#include <stack>

int main(int ac, char **av) {
    float   tmp;
    int     error = 0;
    char    *str = av[1];
    std::stack<float>    thestack;
    if (ac != 2) {
        std::cout << "Error: wrong argument count." << std::endl;
        return 0;
    }
    for (int i = 0; str[i]; i++) {
        if (str[i] == ' ')
            continue;
        else if (std::isdigit(str[i])) {
            thestack.push(std::atof(str + i));
        }
        else if (str[i] == '-') {
            tmp = thestack.top();
            thestack.pop();
            thestack.top() -= tmp;
        }
        else if (str[i] == '+') {
            tmp = thestack.top();
            thestack.pop();
            thestack.top() += tmp;
        }
        else if (str[i] == '*') {
            tmp = thestack.top();
            thestack.pop();
            thestack.top() *= tmp;
        }
        else if (str[i] == '/') {
            tmp = thestack.top();
            thestack.pop();
            thestack.top() /= tmp;
        }
        else {
            error++;
            break ;
        }
    }
    if (error == 1 || thestack.size() > 1)
        std::cout << "Error"  << std::endl;
    else
        std::cout << thestack.top() << std::endl;
    return 0;
}
