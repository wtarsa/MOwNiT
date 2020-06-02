#include <iostream>
#include <vector>
#include <cmath>

#include <complex>
#include <cstdio>

#define M_PI 3.14159265358979323846

std::vector<std::complex<double>> computeDFT(std::vector<std::complex<double>> x) {
    std::vector<std::complex<double>> X;
    std::complex<double> zero(0, 0);
    int N = x.size();
    X.resize(N, zero);


    for (int k = 0; k < N; k++) {
        for (int n = 0; n < N; n++) {
            std::complex<double> f(cos(2 * M_PI * k * n / N), -sin(2 * M_PI * k * n / N));
            X[k] += x[n] * f;
        }
    }

    return X;
}

std::vector<std::complex<double>> wikipediaExample() {
    std::vector<std::complex<double>> numbers;
    numbers.resize(4);
    numbers[0] = std::complex<double>(1, 0);
    numbers[1] = std::complex<double>(2, -1);
    numbers[2] = std::complex<double>(0, -1);
    numbers[3] = std::complex<double>(-1, 2);
    return numbers;
}

void printComplexVector(std::vector<std::complex<double>> x) {
    for (int i = 0; i < x.size(); i++) {
        if (x[i].real() != 0) std::cout << x[i].real();
        if (x[i].real() != 0 and x[i].imag() != 0) std::cout << " + ";
        if (x[i].imag() != 0) {
            std::cout << x[i].imag() << "i";
        }
        std::cout << std::endl;
    }
}

void FFT(std::complex<double> *X, int N) {
    if (N >= 2) {

        std::vector<std::complex<double>> copy;
        copy.resize(N / 2);
        for (int i = 0; i < N / 2; i++) {
            copy[i] = X[i * 2 + 1];
        }
        for (int i = 0; i < N / 2; i++) {
            X[i] = X[i * 2];
        }
        for (int i = 0; i < N / 2; i++) {
            X[i + N / 2] = copy[i];
        }

        FFT(X, N / 2);
        FFT(X + N / 2, N / 2);

        for (int k = 0; k < N / 2; k++) {
            std::complex<double> e = X[k];
            std::complex<double> o = X[k + N / 2];
            std::complex<double> w = std::complex<double>(cos(2. * M_PI * k / N), -sin(2. * M_PI * k / N));
            X[k] = e + w * o;
            X[k + N / 2] = e - w * o;
        }
    }
}

int main() {
    printComplexVector(computeDFT(wikipediaExample()));

    const int N = 4;
    std::complex<double> x[N];

    x[0] = std::complex<double>(1, 0);
    x[1] = std::complex<double>(2, -1);
    x[2] = std::complex<double>(0, -1);
    x[3] = std::complex<double>(-1, 2);

    FFT(x, N);
    std::cout << "FFT" << std::endl;

    for (int i = 0; i < N; i++) {
        std::cout << x[i].real() << " + " << x[i].imag() << "i" << std::endl;
    }
}
