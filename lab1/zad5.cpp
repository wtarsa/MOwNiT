#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

float unstable_version(float x){
    return (sqrt(x+9) - 3);
}

float stable_version(float x){
    return x/(sqrt(x+9) + 3);
}

int main() {
    std::vector<float > arguments;
    std::vector<float > unstable_results;
    std::vector<float > stable_results;

    for(int i = 0; i < 101; i++){
        arguments.push_back(-0.00001 + i*0.0000002);
    }

    for(float &argument: arguments){
        unstable_results.push_back(unstable_version(argument));
    }

    for(float &argument: arguments){
        stable_results.push_back(stable_version(argument));
    }

    std::cout << std::fixed;
   
    /*for(float result: unstable_results){
        std::cout << std::setprecision(8) << result << std::endl;
    }*/

    for(float result: stable_results){
        std::cout << std::setprecision(8) << result << std::endl;
    }

}
