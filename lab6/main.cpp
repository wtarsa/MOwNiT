#include <iostream>
#include <vector>
#include <iomanip>
#include <cfloat>

std::vector<std::vector<double>> getEmptyMatrix(int size){
    std::vector<double> row;
    row.resize(size+1, 0.0);
    std::vector<std::vector<double>> matrix;
    matrix.resize(size, row);
    return matrix;
}

std::vector<std::vector<double>> getLMatrix(std::vector<std::vector<double>> matrix){
    int size = matrix.size();
    std::vector<std::vector<double>> L = getEmptyMatrix(size);
    for(int i = 1; i < size; i++){
        for(int j = 0; j < i; j++){
            L[i][j] = matrix[i][j];
        }
    }
    return L;
}

std::vector<std::vector<double>> getUMatrix(std::vector<std::vector<double>> matrix){
    int size = matrix.size();
    std::vector<std::vector<double>> U = getEmptyMatrix(size);
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            U[i][j] = matrix[i][j];
        }
    }
    return U;
}

std::vector<std::vector<double>> getDMatrix(std::vector<std::vector<double>> matrix){
    int size = matrix.size();
    std::vector<std::vector<double>> D = getEmptyMatrix(size);
    for(int i = 0; i < size; i++){
        D[i][i] = matrix[i][i];

    }
    return D;
}

std::vector<std::vector<double>> matrixAddition(std::vector<std::vector<double>> m1, std::vector<std::vector<double>> m2){
    int size = m1.size();
    std::vector<std::vector<double>> result = getEmptyMatrix(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return result;
}

void showVector(std::vector<double> vec){
    std::cout << std::fixed;
    for(int i = 0; i < vec.size(); i++){
        std::cout << std::setprecision(4) << i << ": " << vec[i] << std::endl;
    }
}

std::vector<double> jacobiMethod(std::vector<std::vector<double>> matrix, int iterations){
    int size = matrix.size();
    std::vector<double> X;
    X.resize(size, 0.0);
    std::vector<double> tmp;
    tmp.resize(size, 0.0);
    std::vector<std::vector<double>> LU = matrixAddition(getLMatrix(matrix), getUMatrix(matrix));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                LU[i][j] = 0;
            } else {
                LU[i][j] = -(matrix[i][j] / matrix[i][i]);
            }
        }
    }

    for (int k = 0; k < iterations; k++) {
        for (int i = 0; i < size; i++) {
            tmp[i] = (1/matrix[i][i]) * matrix[i][size];
            for (int j = 0; j < size; j++) {
                tmp[i] += LU[i][j] * X[j];
            }
        }
        for (int i = 0; i < size; i++) {
            X[i] = tmp[i];
        }
    }
    return X;
}

std::vector<double> gaussSeidelMethod(std::vector<std::vector<double>> matrix, int iterations){
    int size = matrix.size();
    std::vector<double> X;
    X.resize(size, 0.0);
    std::vector<double> tmp;
    tmp.resize(size, 0.0);
    std::vector<std::vector<double>> LU = matrixAddition(getLMatrix(matrix), getUMatrix(matrix));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                LU[i][j] = 0;
            } else {
                LU[i][j] = -(matrix[i][j] / matrix[i][i]);
            }
        }
    }

    for (int k = 0; k < iterations; k++) {
        for (int i = 0; i < size; i++) {
            tmp[i] = (1 / matrix[i][i]) * matrix[i][size];
            for (int j = 0; j < size; j++) {
                if(j < i){
                    tmp[i] += LU[i][j] * tmp[j];
                } else if(j > i){
                    tmp[i] += LU[i][j] * X[j];
                }
            }
        }
        for (int i = 0; i < size; i++) {
            X[i] = tmp[i];
        }
    }
    return X;
}

std::vector<double> SORMethod(std::vector<std::vector<double>> matrix, int iterations, double w){
    int size = matrix.size();
    std::vector<double> X;
    X.resize(size, 0.0);
    std::vector<double> tmp;
    tmp.resize(size, 0.0);
    std::vector<std::vector<double>> LU = matrixAddition(getLMatrix(matrix), getUMatrix(matrix));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                LU[i][j] = 0;
            } else {
                LU[i][j] = -(matrix[i][j] / matrix[i][i]);
            }
        }
    }

    for (int k = 0; k < iterations; k++) {
        for (int i = 0; i < size; i++) {
            tmp[i] = (1 / matrix[i][i]) * matrix[i][size];
            for (int j = 0; j < size; j++) {
                if(j < i){
                    tmp[i] += LU[i][j] * tmp[j];
                } else if(j > i){
                    tmp[i] += LU[i][j] * X[j];
                }
            }
        }
        for (int i = 0; i < size; i++) {
            X[i] = w*tmp[i] + (1-w)*X[i];
        }
    }
    return X;
}

double findRelaxationFactor(std::vector<std::vector<double>> matrix, std::vector<double> X){
    double error = DBL_MAX;
    double relaxationFactor = -1.0;
    double interval = 0.01;
    int iterations = 0;
    for(int k = 1; k < 25; k++) {
        for (int i = 0; i < 200; i++) {
            double tmp_w = i * interval;
            double tmp_error = 0.0;
            std::vector<double> results = SORMethod(matrix, k, tmp_w);
            for (int j = 0; j < results.size(); j++) {
                tmp_error += std::abs(X[j] - results[j]);
            }
            if (tmp_error < error) {
                iterations = k;
                error = tmp_error;
                relaxationFactor = tmp_w;
            }
        }
    }
    printf("Liczba iteracji: %d\n", iterations);
    return relaxationFactor;
}

double findError(std::vector<std::vector<double>> matrix, std::vector<double> solutions, int iterations){
    //std::vector<double> X = jacobiMethod(matrix, iterations);
    //std::vector<double> X = gaussSeidelMethod(matrix, iterations);
    std::vector<double> X = SORMethod(matrix, iterations, 0.98);

    double error = 0.0;
    for(int i = 0; i < X.size(); i++){
        error += std::abs(solutions[i]-X[i]);
    }
    return error;
}

int main() {
    //układy równań
    std::vector<std::vector<double>> m1 = {{2, 1, 11},{5, 7, 13}};
    std::vector<std::vector<double>> m2 = {{10, -1, 2, 0, 6},{-1, 11, -1, 3, 25},{2, -1, 10, -1, -11},{0, 3, -1, 8, 15}};
    std::vector<std::vector<double>> m3 = {{16, 3, 11},{7, -11, 13}};
    std::vector<std::vector<double>> m4 = {{4, -1, -1, 3},{-2, 6, 1, 9},{-1, 1, 7, -6}};
    std::vector<std::vector<double>> m5 = {{5, -1, 2, 12}, {3, 8, -2, -25}, {1, 1, 4, 6}};
    std::vector<std::vector<double>> m6 = {{20, 1, -2, 17}, {3, 20, -1, -18}, {2, -3, 20, 25}};
    std::vector<std::vector<double>> m7 = {{4, 1, 1, 2}, {1, 5, 2, -6}, {1, 2, 3, -4}};

    std::vector<double> s1 = {7.11111111, -3.22222222};
    std::vector<double> s2 = {1, 2, -1, 1};
    std::vector<double> s3 = {0.81218274, -0.66497462};
    std::vector<double> s4 = {1, 2, -1};
    std::vector<double> s5 = {1, -3, 2};
    std::vector<double> s6 = {1, -1, 1};
    std::vector<double> s7 = {1, -1, -1};
//    //jacobi
//    std::vector<double> x1 = jacobiMethod(m1, 25);
//    showVector(x1);
//    std::vector<double> x2 = jacobiMethod(m2, 25);
//    showVector(x2);
//    std::vector<double> x3 = jacobiMethod(m3, 25);
//    showVector(x3);
//    std::vector<double> x4 = jacobiMethod(m4, 25);
//    showVector(x4);
//    std::vector<double> x5 = jacobiMethod(m5, 25);
//    showVector(x5);
//    std::vector<double> x6 = jacobiMethod(m6, 25);
//    showVector(x6);
//    std::vector<double> x7 = jacobiMethod(m7, 27);
//    showVector(x7);

//    //gauss-seidel
//    std::vector<double> x8 = gaussSeidelMethod(m1, 25);
//    showVector(x8);
//    std::vector<double> x9 = gaussSeidelMethod(m2, 25);
//    showVector(x9);
//    std::vector<double> x10 = gaussSeidelMethod(m3, 25);
//    showVector(x10);
//    std::vector<double> x11 = gaussSeidelMethod(m4, 25);
//    showVector(x11);
//    std::vector<double> x12 = gaussSeidelMethod(m5, 25);
//    showVector(x12);
//    std::vector<double> x13 = gaussSeidelMethod(m6, 25);
//    showVector(x13);
//    std::vector<double> x14 = gaussSeidelMethod(m7, 25);
//    showVector(x14);
//
//    double w1 = findRelaxationFactor(m1, s1);
//    std::cout << w1 << std::endl;
//    std::vector<double> x15 = SORMethod(m1, 25, w1);
//    showVector(x15);
//    double w2 = findRelaxationFactor(m2, s2);
//    std::cout << w2 << std::endl;
//    std::vector<double> x16 = SORMethod(m2, 25, w2);
//    showVector(x16);
//    double w3 = findRelaxationFactor(m3, s3);
//    std::cout << w3 << std::endl;
//    std::vector<double> x17 = SORMethod(m3, 25, w3);
//    showVector(x17);
//    double w4 = findRelaxationFactor(m4, s4);
//    std::cout << w4 << std::endl;
//    std::vector<double> x18 = SORMethod(m4, 25, w4);
//    showVector(x18);
//    double w5 = findRelaxationFactor(m5, s5);
//    std::cout << w5 << std::endl;
//    std::vector<double> x19 = SORMethod(m5, 25, w5);
//    showVector(x19);
//    double w6 = findRelaxationFactor(m6, s6);
//    std::cout << w6 << std::endl;
//    std::vector<double> x20 = SORMethod(m6, 25, w6);
//    showVector(x20);
//    double w7 = findRelaxationFactor(m7, s7);
//    std::cout << w7 << std::endl;
//    std::vector<double> x21 = SORMethod(m7, 25, w7);
//    showVector(x21);

    for(int i = 4; i <= 30; i++){
        std::cout << findError(m3, s3, i) << std::endl;
    }
}
