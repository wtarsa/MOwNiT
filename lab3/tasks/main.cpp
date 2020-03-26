#include <iostream>
#include <cmath>
#include <iomanip>

#define M_PI 3.14159265358979323846
#define NMAX 200

bool doubleCompare(double a, double b, double tolerance) {
    return fabs(a - b) < tolerance;
}

double f1(double x) {
    return cos(x) * cosh(x) - 1;
}

double f2(double x) {
    return 1 / x - tan(x);
}

double f3(double x) {
    return pow(2, -x) + exp(x) + 2 * cos(x) - 6;
}

double findSoultion_bisection(double a, double b, double func(double), double tolerance, int &iterationCount) {
    double c = (a + b) / 2;
    iterationCount = 0;
    while (!doubleCompare(func(c), 0, tolerance) && iterationCount < NMAX) {
        if (func(a) * func(c) < 0) b = c;
        else a = c;
        c = (a + b) / 2;
        iterationCount++;
    }
    return c;
}


int main() {
    std::cout << "metoda bisekcji" << std::endl << std::endl;
    int iterationCount;
    std::cout << std::fixed;

    std::cout << "Błąd względny obliczeń 10^-7:" << std::endl;
    std::cout << "cos(x)*cosh(x) - 1" << std::endl;
    std::cout << std::setprecision(7) << "wynik: " << findSoultion_bisection(3 * M_PI / 2, 2 * M_PI, f1, 1e-7, iterationCount)
              << ", liczba iteracji: " << iterationCount << std::endl;
    std::cout << "1/x - tan(x)" << std::endl;
    std::cout << std::setprecision(7) << "wynik: "  << findSoultion_bisection(0, M_PI / 2, f2, 1e-7, iterationCount)
              << ", liczba iteracji: " << iterationCount << std::endl;
    std::cout << "2^-x + e^x + 2*cos(x) - 6" << std::endl;
    std::cout << std::setprecision(7) << "wynik: "  << findSoultion_bisection(1, 3, f3, 1e-7, iterationCount) << ", liczba iteracji: "
              << iterationCount << std::endl << std::endl;

    std::cout << "Błąd względny obliczeń 10^-15:" << std::endl;
    std::cout << "cos(x)*cosh(x) - 1" << std::endl;
    std::cout << std::setprecision(15) << "wynik: "  << findSoultion_bisection(3 * M_PI / 2, 2 * M_PI, f1, 1e-15, iterationCount)
              << ", liczba iteracji: " << iterationCount << std::endl;
    std::cout << "1/x - tan(x)" << std::endl;
    std::cout << std::setprecision(15) << "wynik: "  << findSoultion_bisection(0, M_PI / 2, f2, 1e-15, iterationCount)
              << ", liczba iteracji: " << iterationCount << std::endl;
    std::cout << "2^-x + e^x + 2*cos(x) - 6" << std::endl;
    std::cout << std::setprecision(15) << "wynik: "  << findSoultion_bisection(1, 3, f3, 1e-15, iterationCount)
              << ", liczba iteracji: " << iterationCount << std::endl;

    //metoda
}
