#include "serialization.h"
#include "../ARXModel/ARXModel.h"
#include <iostream>
#include <random>

std::ostream& operator<<(std::ostream& output, const ARXModel& arxModel)
{
    output << arxModel.A << " " << arxModel.B << " " << arxModel.k << " " << arxModel.generator << " " << arxModel.distribution << " ";
    return output;
}

std::istream& operator>>(std::istream& input, ARXModel& arxModel)
{
    input >> arxModel.A >> arxModel.B >> arxModel.k >> arxModel.generator >> arxModel.distribution;
    return input;
}