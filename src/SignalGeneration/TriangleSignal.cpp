
#include "TriangleSignal.h"

TriangleSignal::TriangleSignal(double amplitude, long period)
: amplitude(amplitude), period(period)
{
    counter = 0;
    midpoint = period / 2;
}

double TriangleSignal::generate(int n)
{
    double y = counter;
    if (counter <= midpoint)
    {
        counter++;
    }
    else
    {
        counter--;
    }
};