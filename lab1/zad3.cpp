#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

float sum_forward(int n){
    float result = 0.0f;
    for(int i = 1; i <= n; i++){
        result += 1/(float)pow(2, i+1);
    }
    return result;
}

float sum_backward(int n){
    float result = 0.0f;
    for(int i = n; i > 0; i--){
        result += 1/(float)pow(2, i+1);
    }
    return result;
}

double sum_forward_double(int n){
    double result = 0.0;
    for(int i = 1; i <= n; i++){
        result += 1/pow(2, i+1);
    }
    return result;
}

double sum_backward_double(int n){
    double result = 0.0;
    for(int i = n; i > 0; i--){
        result += 1/pow(2, i+1);
    }
    return result;
}

void fill_vector_with_numbers(std::vector<double> &numbers){
    for(int i = 1; i <= 50; i++){
        numbers[i-1] = 1/pow(2, i+1);
    }
}

double kahan_sum(std::vector<double> &numbers){
    double sum = 0.0f;
    double err = 0.0f;
    for(double &number: numbers){
        double y = number - err;
        double tmp = sum + y;
        err = (tmp - sum) - y;
        sum = tmp;
    }
    return sum;
}

int main() {
    int n_values[] = {50, 100, 200, 500, 800};
    std::cout << std::fixed;
    for(int i = 0; i < 5; i++){
        std::cout << "n = " << n_values[i] << std::endl;
        std::cout << std::setprecision(8) << sum_forward(n_values[i]) << std::endl;
        std::cout << std::setprecision(8) << sum_backward(n_values[i]) << std::endl;
        std::cout << std::setprecision(16) << sum_forward_double(n_values[i]) << std::endl;
        std::cout << std::setprecision(16) << sum_backward_double(n_values[i]) << std::endl;
    }

    //3.4
    std::vector<double> numbers;
    numbers.resize(50);
    fill_vector_with_numbers(numbers);
    double sum_kahan = kahan_sum(numbers);
    std::cout << std::setprecision(16) << "Suma wyliczona algorytmem Kahana: " << sum_kahan << std::endl;
}
