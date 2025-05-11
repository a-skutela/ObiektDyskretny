
#include "TriangleSignal.h"
#include <stdexcept>

TriangleSignal::TriangleSignal(double amplitude, long period)
: amplitude(amplitude), period(period)
{
    counter = 0;
    midpoint = period / 2;
    ascending = true;

    if (period <= 0)
    {
        throw std::invalid_argument("Period must be a positive integer.");
    }
}

double TriangleSignal::generate()
{
    double y = 2 * counter / static_cast<double>(period) * amplitude;
    if (counter >= midpoint)
    {
        ascending = false;
    }
    else if (counter <= 0)
    {
        ascending = true;
    }

    if (ascending)
    {
        counter++;
    }
    else
    {
        counter--;
    }
    return y;
};