
#include <cmath>
#include "SinSignal.h"

SinSignal::SinSignal(double omega, double amplitude)
: period(period), amplitude(amplitude)
{
    x2 = 0;
    x1 = amplitude * std::sin(omega);
    x1Factor = 2 * std::cos(omega);
}

double SinSignal::generate()
{
    double x = x1 * x1Factor - x2;
    double result = x2;
    x2 = x1;
    x1 = x;
    return result;
}