#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cstring>
#define M_PI 3.14159265358979323846
struct point{
    double x;
    double y;
};

double function(double x){
    return exp(cos(x));
}

double derivative(double x){
    return -sin(x) * exp(cos(x));
}

std::vector<point> getValueInPoints(double function(double x), int pointsNumber, double p, double q){
    std::vector<point> values;
    double interval = (q-p)/(pointsNumber-1);
    for(int i = 0; i < pointsNumber; i++){
        point point;
        point.x = p+interval*i;
        point.y = function(point.x);
        values.push_back(point);
    }
    return values;
}

std::vector<point> getChebyshevPoints(double function(double), int n){
    std::vector<point> values;
    for(int k = n-1; k >= 0; k--){
        point p;
        p.x = 3*cos((M_PI * (2*k+1))/(2*(n)));
        p.y = function(p.x);
        values.push_back(p);
    }
    return values;
}

double interpolateLagrange(std::vector<point> values, double xi){
    int n = values.size();
    double result = 0;
    for(int i = 0; i < n; i++){
        double yi = values[i].y;
        for(int j = 0; j < n; j++){
            if(i != j){
                yi = yi*(xi - values[j].x)/(values[i].x - values[j].x);
            }
        }
        result += yi;
    }
    return result;
}

std::vector<point> interpolateLagrangeAllRange(int pointsNumber, int steps){
    std::vector<point> results;
    std::vector<point> values = getValueInPoints(function, pointsNumber, -3.0, 3.0);
    double interval = 6.0/(steps-1);
    for(int i = 0; i < steps; i++){
        point p;
        p.x = interval*i-3.0;
        p.y = interpolateLagrange(values, p.x);
        results.push_back(p);
    }
    return results;
}

std::vector<point> interpolateLagrangeUsingChebyshev(int pointsNumber, int steps){
    std::vector<point> results;
    std::vector<point> values = getChebyshevPoints(function, pointsNumber);
    double interval = 6.0/(steps-1);
    for(int i = 0; i < steps; i++){
        point p;
        p.x = interval*i-3.0;
        p.y = interpolateLagrange(values, p.x);
        results.push_back(p);
    }
    return results;
}

double lagrangeError(int n, bool chebyshev){
    double error = 0.0;
    double interval = 6.0/10000;
    std::vector<point> results;
    if(!chebyshev) {
        results = interpolateLagrangeAllRange(n, 10001);
    }
    else{
        results = interpolateLagrangeUsingChebyshev(n, 10001);
    }
    for(int i = 0; i < 10001; i++){
        error += std::abs(function(i*interval-3.0) - results[i].y);
    }
    return error;
}

double component(int n, double x, std::vector<point> values){
    double result = 1;
    for(int i = 0; i < n; i++){
        result = result * (x - values[i].x);
    }
    return result;
}

std::vector<std::vector<double>> dividedDifferenceTable(std::vector<point> values, int n){
    std::vector<std::vector<double>> result;
    std::vector<double> empty_vec;
    empty_vec.resize(n, -1.0);
    result.resize(n, empty_vec);

    for(int i = 0; i < n; i++){
        result[i][0] = values[i].y;
    }

    for(int i = 1; i < n; i++){
        for(int j = 0; j < n-i; j++){
            result[j][i] = 0.0;
            result[j][i] = (result[j][i-1] - result[j+1][i-1])/
                    (values[j].x - values[i+j].x);
        }
    }
    return result;
}


double interpolateNewton(std::vector<point> values, int n, double x){
    std::vector<std::vector<double>> y = dividedDifferenceTable(values, n);
    double sum = y[0][0];
    for(int i = 1; i < n; i++){
        sum = sum + (component(i, x, values) * y[0][i]);
    }
    return sum;
}

std::vector<point> interpolateNewtonAllRange(int pointsNumber){
    std::vector<point> results;
    std::vector<point> values = getValueInPoints(function, pointsNumber, -3.0, 3.0);
    double interval = 6.0/(10000);
    for(int i = 0; i < 10001; i++){
        point p;
        p.x = interval*i-3.0;
        p.y = interpolateNewton(values, pointsNumber, p.x);
        results.push_back(p);
    }
    return results;
}

std::vector<point> interpolateNewtonUsingChebyshev(int pointsNumber){
    std::vector<point> results;
    std::vector<point> values = getChebyshevPoints(function, pointsNumber);
    double interval = 6.0/(10000);
    for(int i = 0; i < 10001; i++){
        point p;
        p.x = interval*i-3.0;
        p.y = interpolateNewton(values, pointsNumber, p.x);
        results.push_back(p);
    }
    return results;
}

double newtonError(int n, bool chebyshev){
    double error = 0.0;
    double interval = 6.0/10000;
    std::vector<point> results;
    if(!chebyshev) {
        results = interpolateNewtonAllRange(n);
    }
    else{
        results = interpolateNewtonUsingChebyshev(n);
    }
    for(int i = 0; i < 10001; i++){
        error += std::abs(function(i*interval-3.0) - results[i].y);
    }
    return error;
}

std::vector<std::vector<double>> dividedDifferenceTableHermite(std::vector<point> values, int n){
    std::vector<std::vector<double>> result;
    std::vector<double> empty_vec;
    empty_vec.resize(2*n, -1.0);
    result.resize(2*n, empty_vec);

    std::vector<point> values2;

    for(int i = 0; i < n; i++){
        values2.push_back(values[i]);
        values2.push_back(values[i]);
    }

    for(int i = 0; i < 2*n; i++){
        result[i][0] = values2[i].y;
    }

    for(int i = 1; i < 2*n; i++){
        if(i%2 == 1){ // pochodna
            result[i][1] = derivative(values2[i].x);
        }
        else{
            result[i][1] = (result[i-1][0] - result[i][0])/
                           (values2[i-1].x - values2[i].x);
        }
    }

    for(int i = 2; i < 2*n-1; i++){
        for(int j = i; j < 2*n; j++){
            result[j][i] = 0.0;
            result[j][i] = (result[j][i-1] - result[j-1][i-1])/
                           (values2[j].x - values2[j-i].x);
        }
    }

    return result;
}

double componentHermite(int n, double x, std::vector<point> values){
    std::vector<point> values2;

    for(int i = 0; i < n; i++){
        values2.push_back(values[i]);
        values2.push_back(values[i]);
    }

    double result = 1;
    for(int i = 0; i < n; i++){
        result = result * (x - values2[i].x);
    }
    return result;
}

double interpolateHermite(std::vector<point> values, int n, double x){
    std::vector<point> values2;

    for(int i = 0; i < n; i++){
        values2.push_back(values[i]);
        values2.push_back(values[i]);
    }

    std::vector<std::vector<double>> y = dividedDifferenceTableHermite(values, n);
    double sum = y[0][0];
    for(int i = 1; i < 2*n; i++){
        sum = sum + (componentHermite(i, x, values2) * y[i][i]);
    }
    return sum;
}

std::vector<point> interpolateHermiteAllRange(int pointsNumber){
    std::vector<point> results;
    std::vector<point> values = getValueInPoints(function, pointsNumber, -3.0, 3.0);
    double interval = 6.0/(10000);
    for(int i = 0; i < 10001; i++){
        point p;
        p.x = interval*i-3.0;
        p.y = interpolateHermite(values, pointsNumber, p.x);
        results.push_back(p);
    }
    return results;
}

int main(int argc, char** argv) {
    if(argc > 1){
        if(strcmp(argv[1], "funcx") == 0){
            int number = atoi(argv[2]);
            std::vector<point> results = getValueInPoints(function, number, -3.0, 3.0);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.x << std::endl;
            }
        }

        if(strcmp(argv[1], "funcy") == 0){
            int number = atoi(argv[2]);
            std::vector<point> results = getValueInPoints(function, number, -3.0, 3.0);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.y << std::endl;
            }
        }
        else if(strcmp(argv[1], "lagx") == 0){
            int number = atoi(argv[2]);
            int steps = atoi(argv[3]);
            std::vector<point> results = interpolateLagrangeAllRange(number, steps);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.x << std::endl;
            }
        }
        else if(strcmp(argv[1], "lagy") == 0){
            int number = atoi(argv[2]);
            int steps = atoi(argv[3]);
            std::vector<point> results = interpolateLagrangeAllRange(number, steps);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.y << std::endl;
            }
        }
        else if(strcmp(argv[1], "lagcy") == 0){
            int number = atoi(argv[2]);
            int steps = atoi(argv[3]);
            std::vector<point> results = interpolateLagrangeUsingChebyshev(number, steps);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.y << std::endl;
            }
        }
        else if(strcmp(argv[1], "lagcx") == 0){
            int number = atoi(argv[2]);
            int steps = atoi(argv[3]);
            std::vector<point> results = interpolateLagrangeUsingChebyshev(number, steps);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.x << std::endl;
            }
        }
        else if(strcmp(argv[1], "errorlag") == 0){
            for(int i = 2; i < 100; i++) {
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << i << " : " << lagrangeError(i, false) << std::endl;
            }
        }
        else if(strcmp(argv[1], "errorlagc") == 0){
            for(int i = 2; i < 100; i++) {
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << i << " : " << lagrangeError(i, true) << std::endl;
            }
        }
        else if(strcmp(argv[1], "newy") == 0){
            int number = atoi(argv[2]);
            std::vector<point> results = interpolateNewtonAllRange(number);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.y << std::endl;
            }
        }
        else if(strcmp(argv[1], "newx") == 0){
            int number = atoi(argv[2]);
            std::vector<point> results = interpolateNewtonAllRange(number);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.x << std::endl;
            }
        }
        else if(strcmp(argv[1], "newcy") == 0){
            int number = atoi(argv[2]);
            std::vector<point> results = interpolateNewtonUsingChebyshev(number);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.y << std::endl;
            }
        }
        else if(strcmp(argv[1], "newcx") == 0){
            int number = atoi(argv[2]);
            std::vector<point> results = interpolateNewtonUsingChebyshev(number);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.x << std::endl;
            }
        }
        else if(strcmp(argv[1], "errornew") == 0){
            for(int i = 2; i < 100; i++) {
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << i << " : " << newtonError(i, false) << std::endl;
            }
        }
        else if(strcmp(argv[1], "errornewc") == 0){
            for(int i = 2; i < 100; i++) {
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << i << " : " << newtonError(i, true) << std::endl;
            }
        }
        else if(strcmp(argv[1], "hery") == 0){
            int number = atoi(argv[2]);
            std::vector<point> results = interpolateHermiteAllRange(number);
            int counter = 1;
            for(point result: results){
                std::cout << std::fixed;
                std::cout << counter++  << " " << std::setprecision(5) << result.y << std::endl;
            }
        }
        else if(strcmp(argv[1], "herx") == 0){
            int number = atoi(argv[2]);
            std::vector<point> results = interpolateHermiteAllRange(number);
            for(point result: results){
                std::cout << std::fixed;
                std::cout << std::setprecision(5) << result.x << std::endl;
            }
        }
    }
}
