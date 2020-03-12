#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

double unstable_version(double x){
    if(x==0.0) return 0.0;
    return (1-pow(cos(x), 2))/pow(x, 2);
}

double stable_version(double x){
    if(x==0.0) return 0.0;
    return pow(sin(x), 2)/pow(x, 2);
}

int main() {
    std::vector<double> arguments;
    std::vector<double> unstable_results;
    std::vector<double> stable_results;

    for(int i = 0; i < 100; i++){
        arguments.push_back(-0.01 + i*0.0002);
    }

    for(double &argument: arguments){
        unstable_results.push_back(unstable_version(argument));
    }

    for(double &argument: arguments){
        stable_results.push_back(stable_version(argument));
    }

    std::cout << std::fixed;

    /*for(double result: unstable_results){
        std::cout << std::setprecision(16) << result << std::endl;
    }*/

    for(double result: stable_results){
        std::cout << std::setprecision(16) << result << std::endl;
    }

}
