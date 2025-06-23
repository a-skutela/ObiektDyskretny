#include "ConstantSignal.h"
#include <iostream>

ConstantSignal::ConstantSignal(double value)
: value(value)
{}

double ConstantSignal::generate()
{
    return value;
}

std::string ConstantSignal::getType() const
{
    return ConstantSignal::type;
}

void ConstantSignal::serialize(std::ostream& output) const
{
    output << " " << value << "\n";
}

void ConstantSignal::deserialize(std::istream& input)
{
    input >> value;
}

const ConstantSignal ConstantSignal::zero(0.0);

std::string const ConstantSignal::type = "ConstantSignal";
