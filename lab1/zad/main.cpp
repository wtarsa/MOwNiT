#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>


float find_sum(std::vector<float> &numbers) {
    float result = 0.0f;
    for (float &number: numbers) {
        result += number;
    }
    return result;
}

float find_sum_recursively(std::vector<float> &numbers, int p, int q) {
    if (p == q) return numbers[p];
    if (abs(p - q) == 1) return numbers[p] + numbers[q];
    int pivot = (p + q) / 2;
    return find_sum_recursively(numbers, p, pivot) + find_sum_recursively(numbers, pivot + 1, q);
}

void fill_vector_with_numbers(std::vector<float> &numbers) {
    for (float &number : numbers) {
        number = 0.1634f;
    }
}

int main() {
    //1.1
    std::vector<float> numbers;
    numbers.resize(10000000);
    float sum = 0.0f;
    const float correct_sum = 1634000;
    fill_vector_with_numbers(numbers);
    auto start_sum = std::chrono::steady_clock::now();
    sum = find_sum(numbers);
    auto end_sum = std::chrono::steady_clock::now();

    //1.2
    std::cout << std::fixed;
    std::cout << "Najprostsza suma: " << std::setprecision(3) << sum << std::endl;
    std::cout << "Błąd bezwzględny: " << std::setprecision(3) << correct_sum - sum << std::endl;
    std::cout << "Błąd względny: " << std::setprecision(3) << (correct_sum - sum) * 100 / correct_sum << "%"
              << std::endl;

    //1.3
    std::vector<float> add_errors;
    sum = 0.0f;
    for (int i = 0; i < numbers.size(); i++) {
        sum += numbers[i];
        if (i % 25000 == 0) add_errors.push_back(std::abs(i * 0.1634 - sum));
    }

    /*  std::cout << add_errors.size() << std::endl;
      for(int i = 0; i < add_errors.size(); i++){
          std::cout << add_errors[i] << std::endl;
      }*/

    //1.4
    auto start_sum_rec = std::chrono::steady_clock::now();
    float sum_rec = find_sum_recursively(numbers, 0, 9999999);
    auto end_sum_rec = std::chrono::steady_clock::now();
    std::cout << "Suma wyznaczona rekurencyjnie: " << std::setprecision(3) << sum_rec << std::endl;

    //1.5
    std::cout << "Błąd bezwzględny: " << std::setprecision(3) << correct_sum - sum_rec << std::endl;
    std::cout << "Błąd względny: " << std::setprecision(8) << (correct_sum - sum_rec) * 100 / correct_sum << "%"
              << std::endl;

    //1.6
    std::cout << "Czas wyznaczenia sumy najprostszym sposobem : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_sum - start_sum).count()
              << " ms" << std::endl;
    std::cout << "Czas wyznaczenia sumy rekurencyjnie : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end_sum_rec - start_sum_rec).count()
              << " ms" << std::endl;

    for (float add_error : add_errors) {
        std::cout << add_error << std::endl;
    }
}