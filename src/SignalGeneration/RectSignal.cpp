
#include "RectSignal.h"

RectSignal::RectSignal(double amplitude, long period, double fillFactor)
: amplitude(amplitude), period(period), fillFactor(fillFactor)
{
    counter = 0;
}

double RectSignal::generate(int n)
{
    double y = counter <= levelSwitch ? amplitude : 0;
    counter++;
    if (counter >= period)
    {
        counter = 0;
    }
};