#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <random>

#define M_PI 3.14159265358979323846

int points = 10000;

double f1(double x){
    return 1/(1+pow(x, 2));
}

double f2(double x){
    return pow(x, 2);
}

double f3(double x){
    return sqrt(pow(x, 3) + 1);
}

double f4(double x){
    return sqrt(pow(x, 4) + 1);
}

double f5(double x){
    return x*sqrt(x + 1);
}

double rectangle_rule(double p, double q, double func(double)){
    double interval = (q-p)/points;
    double result = 0.0;
    for(int i = 0; i < points; i++){
        result += func(p+interval*(i+1))*interval;
    }
    return result;
}

double trapezoidal_rule(double p, double q, double func(double)){
    double interval = (q-p)/points;
    double result = 0.0;
    for(int i = 0; i < points; i++){
        result += (func(p+interval*(i+1))+func(p+interval*i))*interval/2;
    }
    return result;
}

double simpson_rule(double p, double q, double func(double)){
    double interval = (q-p)/points;
    double result = 0.0;
    double st = 0.0;
    for(int i = 0; i < points; i++){
        double x = p + interval*(i+1);
        st += func(x - interval/2);
        if(i < points-1) result += func(x);
    }
    result = (interval/6) * (func(p) + func(q) + 2*result + 4*st);
    return result;
}

double monte_carlo_rule(double p, double q, double func(double)){
    double result = 0.0;
    std::default_random_engine gen;
    std::uniform_real_distribution<double> random{p, q};
    for(int i = 0; i < points; i++){
        double x = random(gen);
        result += func(x);
    }
    result /= points;
    result *= (q-p);
    return result;
}

double get_pi(int points_number){
    std::default_random_engine gen;
    std::uniform_real_distribution<double> random{-1.0, 1.0};
    int hits = 0;
    for(int i = 0; i < points_number; i++){
        double x = random(gen);
        double y = random(gen);
        if(x*x + y*y <= 1) { hits++; }
    }
    std::cout << (float(hits))/(points_number/4) << std::endl;
}

int main() {
    std::cout << std::fixed;
    double w1 = 0.32175;
//    std::cout << std::setprecision(5) << rectangle_rule(1, 2, f1)/w1 << std::endl;
//    std::cout << std::setprecision(5) << trapezoidal_rule(1, 2, f1)/w1 << std::endl;
//    std::cout << std::setprecision(5) << simpson_rule(1, 2, f1)/w1 << std::endl; // ok
    std::cout << std::setprecision(5) << monte_carlo_rule(1, 2, f1)/w1 << std::endl; // ok

    double w2 = 9;
//    std::cout << std::setprecision(5) << rectangle_rule(0, 3, f2)/w2 << std::endl;
//    std::cout << std::setprecision(5) << trapezoidal_rule(0, 3, f2)/w2 << std::endl;
//    std::cout << std::setprecision(5) << simpson_rule(0, 3, f2)/w2 << std::endl; //ok
    std::cout << std::setprecision(5) << monte_carlo_rule(0, 3, f2)/w2 << std::endl; //ok

    double w3 = 1.11145;
//    std::cout << std::setprecision(5) << rectangle_rule(0, 1, f3)/w3 << std::endl;
//    std::cout << std::setprecision(5) << trapezoidal_rule(0, 1, f3)/w3 << std::endl;
//    std::cout << std::setprecision(5) << simpson_rule(0, 1, f3)/w3 << std::endl; //ok
    std::cout << std::setprecision(5) << monte_carlo_rule(0, 1, f3)/w3 << std::endl; //ok

    double w4 = 1.08943;
//    std::cout << std::setprecision(5) << rectangle_rule(0, 1, f4)/w4 << std::endl;
//    std::cout << std::setprecision(5) << trapezoidal_rule(0, 1, f4)/w4 << std::endl;
//    std::cout << std::setprecision(5) << simpson_rule(0, 1, f4)/w4 << std::endl; //ok
    std::cout << std::setprecision(5) << monte_carlo_rule(0, 1, f4)/w4 << std::endl; //ok

    double w5 = 0.64379;
//    std::cout << std::setprecision(5) << rectangle_rule(0, 1, f5)/w5 << std::endl;
//    std::cout << std::setprecision(5) << trapezoidal_rule(0, 1, f5)/w5 << std::endl;
//    std::cout << std::setprecision(5) << simpson_rule(0, 1, f5)/w5 << std::endl; //ok
    std::cout << std::setprecision(5) << monte_carlo_rule(0, 1, f5)/w5 << std::endl; //ok

    /*for(int i = 100; i < 100000; i+= 100){
        get_pi(i);
    }*/

}
