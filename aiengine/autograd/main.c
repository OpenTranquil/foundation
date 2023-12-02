#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "grad.h"

// f = (ax + b)^2
// Z = ax
// Y = Z + b
// F = Y ^ 2

// fx' = FY'YZ'Zx'
// fx' = 2Y * 1 * a
// fx' = 2(ax +b) * 1 * a
// fx' = 2(ax+b)a

double fx(double x, double a, double b) {
    double val = pow((a * x + b), 2);
    return val;
}

double fdx(double x, double a, double b) {
    double grad = 2.0f * (a * x + b) * a;
    return grad;
}

int main(int argc, char *argv[]) {
    double av = 5.1f;
    double xv = 6.3f;
    double bv = 2.1f;
    printf("a:%f, b:%f, x:%f \n", av, bv, xv);
    double exp_val = fx(xv, av, bv);
    double exp_grad = fdx(xv, av, bv);
    printf("EXPECTED val:%f, grad:%f\n", exp_val, exp_grad);

    ComputeNode *x = Variable(xv, "x");
    ComputeNode *fx = Pow(Add(Mul(x, Param(av, "a")), Param(bv, "b")), Constant(2.0f));
    printf("ACTUAL2 val: %f, grad:%f\n", Forword(fx), Backword(x));
    return 0;
}