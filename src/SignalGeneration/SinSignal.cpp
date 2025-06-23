#include <cmath>
#include "SinSignal.h"
#include <iostream>

SinSignal::SinSignal(double omega, double amplitude)
: amplitude(amplitude)
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

std::string SinSignal::getType() const
{
    return SinSignal::type;
}

void SinSignal::serialize(std::ostream& output) const
{
    output << " " << amplitude << " " << x1 << " " << x2 << " " << x1Factor << "\n";
}

void SinSignal::deserialize(std::istream& input)
{
    input >> amplitude >> x1 >> x2 >> x1Factor;
    if (input.fail())
    {
        throw std::runtime_error("Error reading SinSignal parameters from input stream.");
    }
}

std::string const SinSignal::type = "SinSignal";
