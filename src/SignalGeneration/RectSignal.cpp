
#include "RectSignal.h"
#include <stdexcept>

RectSignal::RectSignal(double amplitude, long period, double fillFactor)
: amplitude(amplitude), period(period), fillFactor(fillFactor)
{
    if (fillFactor < 0 || fillFactor > 1)
    {
        throw std::invalid_argument("Fill factor must be between 0 and 1.");
    }
    if (period <= 0)
    {
        throw std::invalid_argument("Period must be a positive integer.");
    }

    levelSwitch = period * fillFactor;
    counter = 0;
}

double RectSignal::generate()
{
    double y = counter < levelSwitch ? amplitude : 0;
    counter++;
    if (counter >= period)
    {
        counter = 0;
    }
    return y;
};