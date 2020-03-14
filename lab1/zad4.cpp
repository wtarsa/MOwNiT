#include <iostream>
#include <iomanip>

double find_machine_epsilon(double eps = 1.0){
    double previous = eps;
    while((eps + 1.0) != 1.0){
        previous = eps;
        eps = eps/2;
    }
    return previous;
}

int main() {
    std::cout << std::fixed;
    std::cout << std::setprecision(18) << find_machine_epsilon() << std::endl;
}
