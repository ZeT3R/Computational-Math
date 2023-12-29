//
// Created by Sergey on 08.11.2020.
//

#ifndef LAB2_FUNCCLASS_H
#define LAB2_FUNCCLASS_H
#include <cmath>

class Func{
private:


public:
    double a, b, c, d;

    static double N4Step(double &x, double a, double b, double c, double d);

    static int SolveP4De(double *&x, int b, int c, int d);

    static int SolveP3(double *&x,int a,int b,int c);

    static double SolveP4(double *&x, double a, double b, double c, double d);
};

#endif //LAB2_FUNCCLASS_H
