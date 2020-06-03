#include <iostream>
#include <vector>
#include <cmath>

#include <complex>
#include <cstdio>
#include <random>
#include <chrono>

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

void DFTandFFTtest(int seed, int n){
    srand(seed);
    std::vector<std::complex<double>> X;
    std::complex<double> X2[n];
    for(int i = 0; i < n; i++){
        auto c = std::complex<double>(1+rand()%100, 1+rand()%100);
        X.push_back(c);
        X2[i] = c;
    }

    std::cout << "wielkość zbioru: " << n << std::endl;
    auto start = std::chrono::steady_clock::now();
    computeDFT(X);
    auto end = std::chrono::steady_clock::now();
    std::cout << "DFT: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " μs" << std::endl;

    start = std::chrono::steady_clock::now();
    FFT(X2, n);
    end = std::chrono::steady_clock::now();
    std::cout << "FFT: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " μs" << std::endl;
}

void tempData(){
    std::complex<double> X[128] =
            {9.946629, 9.896628, 9.926628, 9.956628, 10.036628, 10.066628, 10.626628, 11.846628, 13.766628, 15.996628,
             18.396627, 20.746628, 22.416628, 23.506628, 23.716629, 23.936628, 23.596628, 22.826628, 22.13663, 21.056627,
             19.226627, 17.696629, 16.866629, 16.156628, 15.686628, 15.286628, 14.916628, 14.586628, 14.306628, 14.066628,
             14.326628, 15.166628, 16.88663, 20.296629, 23.286629, 25.716629, 27.396627, 28.586628, 29.286629, 29.63663,
             29.356628, 28.616629, 27.246628, 25.13663, 22.13663, 19.456629, 17.486628, 16.216629, 15.666628, 15.306628,
             14.876628, 14.486629, 14.206628, 13.936628, 14.446629, 16.856628, 19.246628, 21.446629, 23.536629, 25.506628,
             26.706629, 27.526628, 28.096628, 28.596628, 28.776628, 28.366629, 27.336628, 25.916628, 24.326628, 22.586628,
             21.376629, 20.306627, 19.426628, 19.486628, 19.196629, 18.516628, 18.316628, 18.176628, 18.346628, 18.856628,
             19.63663, 21.38663, 23.016628, 24.716629, 26.846628, 27.516628, 28.166628, 28.436628, 26.006628, 25.626629,
             25.13663, 24.806627, 23.906628, 22.286629, 20.986628, 20.086628, 19.356628, 19.096628, 19.076628, 19.146627,
             18.956629, 18.666628, 18.846628, 19.656628, 20.976627, 21.426628, 23.446629, 24.086628, 24.026628, 23.806627,
             23.396627, 23.006628, 22.706629, 22.336628, 21.846628, 20.816628, 19.696629, 18.326628, 17.226627, 16.026628,
             16.106628,15.336628,14.736629,13.986629,12.426628,11.506628,11.556628,11.586628};

    int n = 128;
    double seconds = 3600.0;
    double sampleRate = n / seconds;
    double freqResolution = sampleRate / n;
    std::complex<double> x[n];               

    FFT(X, n);

//    for (int i = 0; i < n; i++) {
//        std::cout << abs(X[i]) << std::endl;
//    }
//
    for (int i = 0; i < n; i++) {
        std::cout << i * freqResolution << std::endl;
    }

}


int main() {
//    printComplexVector(computeDFT(wikipediaExample()));
//
//    const int N = 4;
//    std::complex<double> x[N];
//
//    x[0] = std::complex<double>(1, 0);
//    x[1] = std::complex<double>(2, -1);
//    x[2] = std::complex<double>(0, -1);
//    x[3] = std::complex<double>(-1, 2);
//
//    FFT(x, N);
//    std::cout << "FFT" << std::endl;
//
//    for (int i = 0; i < N; i++) {
//        std::cout << x[i].real() << " + " << x[i].imag() << "i" << std::endl;
//    }
//    DFTandFFTtest(768, 32);
//    DFTandFFTtest(65, 64);
//    DFTandFFTtest(536, 128);
//    DFTandFFTtest(23, 256);
//    DFTandFFTtest(665, 512);
//    DFTandFFTtest(5, 1024);
//    DFTandFFTtest(45, 2048);
//    DFTandFFTtest(879, 4096);
//    DFTandFFTtest(38, 8192);
//    DFTandFFTtest(365, 16384);


    tempData();
}
