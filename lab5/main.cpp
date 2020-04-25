#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include "aghMatrix.h"

#define M_PI 3.14159265358979323846

struct point{
    double x;
    double y;
};

std::vector<point> getValueInPoints(double function(double x), int pointsNumber){
    std::vector<point> values;
    double interval = 2*M_PI/(pointsNumber-1);
    for(int i = 0; i < pointsNumber; i++){
        point point;
        point.x = interval*i;
        point.y = function(point.x);
        values.push_back(point);
    }
    return values;
}

double f1(double x){
    return exp(cos(x));
}

double f2(double x){
    return exp(-x/M_PI) * sin(x);
}

double calculateSum(int power, std::vector<point> points){
    double result = 0.0;
    for(point p: points){
        result += pow(p.x, power);
    }
    return result;
}

double calculateSum(int power, std::vector<point> points, double func(double)){
    double result = 0.0;
    for(point p: points){
        result += pow(p.x, power)*func(p.x);
    }
    return result;
}

AGHMatrix<double> createMainMatrix(int m, std::vector<point> points, double func(double)){ // n = number of points, int m = number of functions
    std::vector<std::vector<double>> mat;
    std::vector<double> row;
    row.resize(m+2, 0);
    mat.resize(m+1, row);

    //first row
    for(int i = 0; i <= m; i++){
        mat[0][i] = calculateSum(i, points);
    }

    //remaining rows
    for(int i = 1; i <= m; i++){
        for(int j = 0; j <= m; j++){
            if(j != m) mat[i][j] = mat[i-1][j+1];
            else mat[i][j] = calculateSum(i+j, points);
        }
    }

    //last column (results)
    for(int i = 0; i <= m; i++){
        mat[i][m+1] = calculateSum(i, points, func);
    }

    AGHMatrix <double> result_matrix(mat);
    return result_matrix;
}

std::vector<point> beginApproximation(int n, int m, double func(double)){
    std::vector<point> points = getValueInPoints(func, n);
    AGHMatrix<double> mat = createMainMatrix(m, points, func);
    AGHMatrix<double> result = mat.gauss_elimination();
    std::vector<point> values;
    double interval = 14.0/(10000);
    for(int i = 0; i < 10001; i++){
        point point;
        point.x = interval*i-7;
        double y_val = 0.0;
        for(int j = 0; j < m+1; j++){
            y_val += result.matrix[j][0] * pow(point.x, j);
        }
        point.y = y_val;
        values.push_back(point);
    }
    return values;
}

double error(int n, int m, double func(double)){
    std::vector<point> points = getValueInPoints(func, n);
    AGHMatrix<double> mat = createMainMatrix(m, points, func);
    AGHMatrix<double> result = mat.gauss_elimination();
    double interval = 14.0/(10000);
    double result_value = 0.0;
    for(int i = 0; i < 10001; i++){
        double x = interval*i-7;
        double y = 0.0;
        for(int j = 0; j < m+1; j++){
            y += result.matrix[j][0] * pow(x, j);
        }
        y = std::abs(y - func(x));
        result_value += y;
    }
    return result_value;
}

//trigonometric
std::vector<point> getTrigonometricPoints(int L, double func(double)){
    std::vector<point> points;
    for(int i = 0; i < 2*L; i++){
        point p;
        p.x = i*M_PI/L;
        p.y = func(p.x);
        points.push_back(p);
    }
    return points;
}

double getAj(int L, int j, std::vector<point> points){
    double a = 0.0;
    for(int i = 0; i < 2*L; i++){
        a += points[i].y*cos(M_PI*i*j/L);
    }
    a /= L;
    return a;
}

double getBj(int L, int j, std::vector<point> points){
    double b = 0.0;
    for(int i = 0; i < 2*L; i++){
        b += points[i].y*sin(M_PI*i*j/L);
    }
    b /= L;
    return b;
}

double getFunctionValue(int L, double x, double func(double), int n){
    std::vector<point> points = getTrigonometricPoints(L, func);
    double result = getAj(L, 0, points)/2;
    for(int j = 1; j <= n; j++){
        result += getAj(L, j, points)*cos(j*x);
        result += getBj(L, j, points)*sin(j*x);
    }
    return result;
}

std::vector<point> beginApproximationTrigonometric(int n, int L, double func(double)){
    std::vector<point> values;
    double interval = 2*M_PI/(10000);
    for(int i = 0; i < 10001; i++){
        point point;
        point.x = interval*i;
        point.y = getFunctionValue(L, point.x, func, n);
        values.push_back(point);
    }
    return values;
}

double errorTr(int L, int n, double func(double)){
    double result = 0.0;
    double interval = 2*M_PI/(10000);
    for(int i = 0; i < 10001; i++){
        point point;
        point.x = interval*i;
        point.y = getFunctionValue(L, point.x, func, n);
        result += std::abs(point.y - func(point.x));
    }
    return result;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        if(strcmp(argv[1], "x") == 0){
            std::vector<point> results = getValueInPoints(f1, 10001);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.x << std::endl;
            }
        }
        if(strcmp(argv[1], "f1") == 0){
            std::vector<point> results = getValueInPoints(f1, 10001);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.y << std::endl;
            }
        }
        if(strcmp(argv[1], "f2") == 0){
            std::vector<point> results = getValueInPoints(f2, 10001);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.y << std::endl;
            }
        }
        if(strcmp(argv[1], "f1app") == 0){
            int n = atoi(argv[2]);
            int m = atoi(argv[3]);
            std::vector<point> results =  beginApproximation(n, m, f1);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.y << std::endl;
            }
        }
        if(strcmp(argv[1], "f2app") == 0){
            int n = atoi(argv[2]);
            int m = atoi(argv[3]);
            std::vector<point> results =  beginApproximation(n, m, f2);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.y << std::endl;
            }
        }
        if(strcmp(argv[1], "f2e") == 0){
            int m = atoi(argv[2]);
            for(int n = 6; n < 101; n++) {
                double result = error(n, m, f2);
                std::cout << n << ": " << std::setprecision(3) << result << std::endl;
            }
        }
        if(strcmp(argv[1], "f1e") == 0) {
            int m = atoi(argv[2]);
            for (int n = 6; n < 101; n++) {
                double result = error(n, m, f1);
                std::cout << n << ": " << std::setprecision(3) << result << std::endl;
            }
        }
        if(strcmp(argv[1], "f1at") == 0){
            int n = atoi(argv[2]);
            int L = atoi(argv[3]);
            std::vector<point> results = beginApproximationTrigonometric(n, L, f1);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.y << std::endl;
            }
        }
        if(strcmp(argv[1], "f2at") == 0){
            int n = atoi(argv[2]);
            int L = atoi(argv[3]);
            std::vector<point> results = beginApproximationTrigonometric(n, L, f2);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.y << std::endl;
            }
        }
        if(strcmp(argv[1], "f2et") == 0){
            int n = atoi(argv[2]);
            for(int L = n; L < 101; L++) {
                double result = errorTr(L, n, f2);
                std::cout << L << ": " << std::setprecision(3) << result << std::endl;
            }
        }
        if(strcmp(argv[1], "f1et") == 0) {
            int n = atoi(argv[2]);
            for (int L = n; L < 101; L++) {
                double result = errorTr(L, n, f1);
                std::cout << L << ": " << std::setprecision(3) << result << std::endl;
            }
        }
    }
}