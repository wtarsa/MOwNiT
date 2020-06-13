#include <iostream>
#include <cmath>

#define SIGMA 10
#define RHO 28
#define BETA 2.6666
#define DELTA 0.01

int ITERATIONS = 2300;

struct point3{
    double x;
    double y;
    double z;
};

point3 old;

double dxdt(double x, double y){
    return SIGMA * (y - x);
}

double dydt(double x, double y, double z){
    return x * (RHO - z) - y;
}

double dzdt(double x, double y, double z){
    return x * y - BETA * z;
}

void eulerMethod(double x, double y, double z){
    for(int i = 0; i < ITERATIONS; i++){
        double xt = x + DELTA * dxdt(x, y);
        double yt = y + DELTA * dydt(x, y, z);
        double zt = z + DELTA * dzdt(x, y, z);
//        std::cout << x << std::endl;
//        std::cout << y << std::endl;
        std::cout << z << std::endl;

        x = xt;
        y = yt;
        z = zt;
    }
}

void eulerMethodBackward(double x, double y, double z){
    for(int i = 0; i < ITERATIONS; i++){
        double xt = x + DELTA * dxdt(x, y);
        double yt = y + DELTA * dydt(xt, y, z);
        double zt = z + DELTA * dzdt(xt, yt, z);
        x = xt;
        y = yt;
        z = zt;
//        std::cout << x << std::endl;
//        std::cout << y << std::endl;
        std::cout << z << std::endl;
    }
}

//rk4

double f1(point3 p, point3 pn){
    return SIGMA * (p.y  + pn.y * DELTA / 2 - (p.x + pn.x * DELTA / 2));
}

double f2(point3 p, point3 pn){
    return -1 * (p.x + pn.x * DELTA / 2) * (p.z + pn.z * DELTA / 2) + RHO * (p.x + pn.x * DELTA / 2) - (p.y + pn.y * DELTA / 2);
}

double f3(point3 p, point3 pn){
    return (p.x + pn.x * DELTA / 2) * (p.y + pn.y * DELTA / 2) - BETA * (p.z + pn.z * DELTA / 2);
}

point3 getK1(){
    point3 result;
    point3 zero;
    zero.x = zero.y = zero.z = 0;
    result.x = f1(old, zero);
    result.y = f2(old, zero);
    result.z = f3(old, zero);
    return result;
}

point3 getKn(point3 p){
    point3 result;
    result.x = f1(old, p);
    result.y = f2(old, p);
    result.z = f3(old, p);
    return result;
}

point3 getNextPoint(point3 startPoint){
    old = startPoint;

    point3 k1 = getK1();
    point3 k2 = getKn(k1);
    point3 k3 = getKn(k2);
    point3 k4 = getKn(k3);

    point3 nextPoint;
    nextPoint.x = old.x + (k1.x + 2 * k2.x + 2 * k3.x + k4.x) * DELTA / 6;
    nextPoint.y = old.y + (k1.y + 2 * k2.y + 2 * k3.y + k4.y) * DELTA / 6;
    nextPoint.z = old.z + (k1.z + 2 * k2.z + 2 * k3.z + k4.z) * DELTA / 6;

    return nextPoint;
}

void rk4(point3 startPoint){
    for(int i = 0; i < ITERATIONS; i++){
        point3 nextPoint = getNextPoint(startPoint);
        std::cout << nextPoint.x << std::endl;
        std::cout << nextPoint.y << std::endl;
        std::cout << nextPoint.z << std::endl;
        startPoint = nextPoint;
    }
}


//rk2

point3 getNextPointRK2(point3 startPoint){
    old = startPoint;

    point3 k1 = getK1();
    point3 k2 = getKn(k1);

    point3 nextPoint;
    nextPoint.x = old.x + (k1.x + 2 * k2.x) * DELTA / 6;
    nextPoint.y = old.y + (k1.y + 2 * k2.y) * DELTA / 6;
    nextPoint.z = old.z + (k1.z + 2 * k2.z) * DELTA / 6;
    return nextPoint;
}


void rk2(point3 startPoint){
    for(int i = 0; i < ITERATIONS; i++){
        point3 nextPoint = getNextPointRK2(startPoint);
        std::cout << nextPoint.x << std::endl;
        std::cout << nextPoint.y << std::endl;
        std::cout << nextPoint.z << std::endl;
        startPoint = nextPoint;
    }
}

//ostatnie
double dydx(double x, double y){
    return y * sin(x) + sin(x) * cos(x);
}

double func(double x){
    return exp(-cos(x)) - cos(x) + 1;
}

void euler(double x0, double xk, double y, double h){
    double tmp;
    while(x0 < xk){
        tmp = y;
        y = y + h * dydx(x0, y);
        x0 = x0 + h;
    }
    std::cout << y << std::endl;
}

//ostatnie rk

double newValue(point3 p, double h){
    return dydx(old.x, old.y) + (dydx(p.x, p.y) * h / 2);
}

point3 iterate(point3 startPoint, double h){
    old = startPoint;
    point3 zero;
    zero.x = zero.y = zero.z = 0;

    point3 nextPoint;
    point3 k1;
    point3 k2;
    k1.x = k2.x = old.x + h;
    k1.y = newValue(zero, h);
    k2.y = newValue(k1, h);

    nextPoint.x = k1.x;
    nextPoint.y = old.y + (k1.y + 2 * k2.y) * DELTA / 6;
    return nextPoint;
}

point3 solveEquation(point3 startPoint, double h, double xk){
    while(startPoint.x < xk){
        point3 next = iterate(startPoint, h);
        startPoint = next;
    }
    return startPoint;
}

int main() {
//    eulerMethodBackward(0.1, 0, 0);
//    point3 start;
//    start.x = 0.1;
//    start.y = start.z = 0;
//    rk4(start);
//    rk2(start);

    for (int i = 1; i <= 5; i++) {
        double h = 0.025 / i;
        std::cout << "h: " << h << std::endl;
        double x0 = 0;
        double y0 = func(x0);
        point3 start;
        start.x = x0;
        start.y = y0;
        double xk = 0.1;
        std::cout << "euler ";
        euler(x0, xk, y0, h);
        std::cout << "rk " << solveEquation(start, h, xk).y << std::endl;
        std::cout << func(xk) << std::endl;
    }
}

