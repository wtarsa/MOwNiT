#include <iostream>
#include <cmath>
#include <iomanip>

#define M_PI 3.14159265358979323846
#define NMAX 200

double epsilon = 2.22*10e-16;

bool doubleCompare(double a, double b, double tolerance) {
    return fabs(a - b) < tolerance;
}

double f1(double x) {
    return cos(x) * cosh(x) - 1;
}

double f2(double x) {
    if(doubleCompare(x, 0.0, epsilon)) return 0.0;
    return 1 / x - tan(x);
}

double f3(double x) {
    return pow(2, -x) + exp(x) + 2 * cos(x) - 6;
}

double derivF1(double x){
    return cos(x)*sinh(x) - sin(x)*cosh(x);
}

double derivF2(double x) {
    return -1 / pow(x, 2) - pow(1/cos(x), 2);
}

double derivF3(double x){
    return exp(x) - pow(2, -x)*log(2) - 2*sin(x);
}

double findSolution_bisection(double a, double b, double func(double), double tolerance, int &iterationCount) {
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

bool findSolution_Newton(double a, double func(double), double deriv(double),
        int &iterations, double tolerance, double &solution){
    for(int i = 0; i < iterations; i++){
        double y = func(a);
        double y_deriv = deriv(a);
        if(std::abs(y_deriv) < epsilon) break;
        solution = a - y/y_deriv;
        if(std::abs(solution - a) <= tolerance){
            iterations = i;
            return true;
        }
        a = solution;
    }
    return false;
}

bool findSolution_secant(double a, double b, double func(double), int &iterations, double &solution, double tolerance){
    for(int i = 0; i < iterations; i++){
        double c = b - func(b) * (b - a) / (func(b)-func(a));
        a = b;
        b = c;
        if(std::abs(b - a) <= tolerance){
            iterations = i;
            solution = c;
            return true;
        }
    }
    return false;
}

int main() {
    std::cout << "metoda bisekcji" << std::endl << std::endl;
    int iterationCount;
    std::cout << std::fixed;

    std::cout << "Błąd względny obliczeń 10^-7:" << std::endl;
    std::cout << "cos(x)*cosh(x) - 1" << std::endl;
    std::cout << std::setprecision(7) << "wynik: "
              << findSolution_bisection(3 * M_PI / 2, 2 * M_PI, f1, 1e-7, iterationCount)
              << ", liczba iteracji: " << iterationCount << std::endl;
    std::cout << "1/x - tan(x)" << std::endl;
    std::cout << std::setprecision(7) << "wynik: " << findSolution_bisection(0, M_PI / 2, f2, 1e-7, iterationCount)
              << ", liczba iteracji: " << iterationCount << std::endl;
    std::cout << "2^-x + e^x + 2*cos(x) - 6" << std::endl;
    std::cout << std::setprecision(7) << "wynik: " << findSolution_bisection(1, 3, f3, 1e-7, iterationCount)
              << ", liczba iteracji: "
              << iterationCount << std::endl << std::endl;

    std::cout << "Błąd względny obliczeń 10^-15:" << std::endl;
    std::cout << "cos(x)*cosh(x) - 1" << std::endl;
    std::cout << std::setprecision(15) << "wynik: "
              << findSolution_bisection(3 * M_PI / 2, 2 * M_PI, f1, 1e-15, iterationCount)
              << ", liczba iteracji: " << iterationCount << std::endl;
    std::cout << "1/x - tan(x)" << std::endl;
    std::cout << std::setprecision(15) << "wynik: " << findSolution_bisection(0, M_PI / 2, f2, 1e-15, iterationCount)
              << ", liczba iteracji: " << iterationCount << std::endl;
    std::cout << "2^-x + e^x + 2*cos(x) - 6" << std::endl;
    std::cout << std::setprecision(15) << "wynik: " << findSolution_bisection(1, 3, f3, 1e-15, iterationCount)
              << ", liczba iteracji: " << iterationCount << std::endl;

    //metoda Newtona
    std::cout << "metoda Newtona" << std::endl << std::endl;

    iterationCount = 20;
    double solution;
    std::cout << "Błąd względny obliczeń 10^-7:" << std::endl;
    if (findSolution_Newton(3 * M_PI / 2, f1, derivF1, iterationCount, 1e-7, solution)) {
        std::cout << "cos(x)*cosh(x) - 1" << std::endl;
        std::cout << std::setprecision(7) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl;
    }
    iterationCount = 20;
    if (findSolution_Newton(1, f2, derivF2, iterationCount, 1e-7, solution)) {
        std::cout << "1/x - tan(x)" << std::endl;
        std::cout << std::setprecision(7) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl;
    }
    iterationCount = 20;
    if (findSolution_Newton(1, f3, derivF3, iterationCount, 1e-7, solution)) {
        std::cout << "2^-x + e^x + 2*cos(x) - 6" << std::endl;
        std::cout << std::setprecision(7) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl << std::endl;
    }

    iterationCount = 20;
    std::cout << "Błąd względny obliczeń 10^-15:" << std::endl;
    if (findSolution_Newton(3 * M_PI / 2, f1, derivF1, iterationCount, 1e-15, solution)) {
        std::cout << "cos(x)*cosh(x) - 1" << std::endl;
        std::cout << std::setprecision(15) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl;
    }
    iterationCount = 20;
    if (findSolution_Newton(1, f2, derivF2, iterationCount, 1e-15, solution)) {
        std::cout << "1/x - tan(x)" << std::endl;
        std::cout << std::setprecision(15) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl;
    }
    iterationCount = 20;
    if (findSolution_Newton(1, f3, derivF3, iterationCount, 1e-15, solution)) {
        std::cout << "2^-x + e^x + 2*cos(x) - 6" << std::endl;
        std::cout << std::setprecision(15) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl << std::endl;
    }

    //metoda siecznych
    std::cout << "metoda siecznych" << std::endl << std::endl;

    std::cout << "Błąd względny obliczeń 10^-7:" << std::endl;
    iterationCount = 20;
    if (findSolution_secant(3 * M_PI / 2, 2 * M_PI, f1, iterationCount, solution, 1e-7)) {
        std::cout << "cos(x)*cosh(x) - 1" << std::endl;
        std::cout << std::setprecision(7) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl;
    }
    iterationCount = 20;
    if (findSolution_secant(1e-6, (M_PI / 2) - 1e-6, f2, iterationCount, solution, 1e-7)) {
        std::cout << "1/x - tan(x)" << std::endl;
        std::cout << std::setprecision(7) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl;
    }
    iterationCount = 20;
    if (findSolution_secant(1, 3, f3, iterationCount, solution, 1e-7)) {
        std::cout << "2^-x + e^x + 2*cos(x) - 6" << std::endl;
        std::cout << std::setprecision(7) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl << std::endl;
    }

    std::cout << "Błąd względny obliczeń 10^-15:" << std::endl;
    iterationCount = 20;
    if (findSolution_secant(3 * M_PI / 2, 2 * M_PI, f1, iterationCount, solution, 1e-15)) {
        std::cout << "cos(x)*cosh(x) - 1" << std::endl;
        std::cout << std::setprecision(15) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl;
    }
    iterationCount = 20;
    if (findSolution_secant(1e-6, (M_PI / 2) - 1e-6, f2, iterationCount, solution, 1e-15)) {
        std::cout << "1/x - tan(x)" << std::endl;
        std::cout << std::setprecision(15) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl;
    }
    iterationCount = 20;
    if (findSolution_secant(1, 3, f3, iterationCount, solution, 1e-15)) {
        std::cout << "2^-x + e^x + 2*cos(x) - 6" << std::endl;
        std::cout << std::setprecision(15) << "wynik: " << solution << ", liczba iteracji: " << iterationCount << std::endl;
    }
}