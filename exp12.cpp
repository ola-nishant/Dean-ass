#include <iostream>
#include <cmath>
using namespace std;

double evaluate(double coeff[], int n, double x)
{
    double val = coeff[n-1];
    for (int i = n-2; i >= 0; i--)
        val = val * x + coeff[i];
    return val;
}

double findRoot(double coeff[], int n, double a, double b)
{
    double c, fa, fb, fc;
    do {
        fa = evaluate(coeff, n, a);
        fb = evaluate(coeff, n, b);
        c = (a + b) / 2.0;
        fc = evaluate(coeff, n, c);
        if (fa * fc < 0)
            b = c;
        else if (fb * fc < 0)
            a = c;
        else
            break;
    } while (abs(b - a) > 0.5e-6);
    return c;
}

int main()
{
    int n;
    cout << "Enter the degree of the polynomial: ";
    cin >> n;
    double coeff[n];
    cout << "Enter the coefficients of the polynomial from highest to lowest degree: ";
    for (int i = n-1; i >= 0; i--)
        cin >> coeff[i];
    double a, b;
    cout << "Enter the interval [a, b] in which to search for the root: ";
    cin >> a >> b;
    double root = findRoot(coeff, n, a, b);
    cout << "Root = " << root << endl;
    return 0;
}
