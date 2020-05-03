#include <iostream>
#include <vector>
#include <iomanip>

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



int main() {
    //układy równań
    std::vector<std::vector<double>> m1 = {{2, 1, 11},{5, 7, 13}};
    std::vector<std::vector<double>> m2 = {{10, -1, 2, 0, 6},{-1, 11, -1, 3, 25},{2, -1, 10, -1, -11},{0, 3, -1, 8, 15}};
    std::vector<std::vector<double>> m3 = {{16, 3, 11},{7, -11, 13}};
    std::vector<std::vector<double>> m4 = {{4, -1, -1, 3},{-2, 6, 1, 9},{-1, 1, 7, -6}};
    std::vector<std::vector<double>> m5 = {{5, -1, 2, 12}, {3, 8, -2, -25}, {1, 1, 4, 6}};
    std::vector<std::vector<double>> m6 = {{20, 1, -2, 17}, {3, 20, -1, -18}, {2, -3, 20, 25}};
    std::vector<std::vector<double>> m7 = {{4, 1, 1, 2}, {1, 5, 2, -6}, {1, 2, 3, -4}};

    std::vector<double> x1 = jacobiMethod(m1, 25);
    showVector(x1);
    std::vector<double> x2 = jacobiMethod(m2, 25);
    showVector(x2);
    std::vector<double> x3 = jacobiMethod(m3, 25);
    showVector(x3);
    std::vector<double> x4 = jacobiMethod(m4, 25);
    showVector(x4);
    std::vector<double> x5 = jacobiMethod(m5, 25);
    showVector(x5);
    std::vector<double> x6 = jacobiMethod(m6, 25);
    showVector(x6);
    std::vector<double> x7 = jacobiMethod(m7, 25);
    showVector(x7);

}
