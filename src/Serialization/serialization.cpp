#include "serialization.h"
#include "../ARXModel/ARXModel.h"

std::ostream& operator<<(std::ostream& output, const ARXModel& arxModel)
{
    // output << arxModel.A << " " << arxModel.B << " " << arxModel.k << " " << arxModel.generator << " " << arxModel.distribution << " ";
    output << arxModel.A << " " << arxModel.B << " " << arxModel.k << " " << arxModel.u << " " << arxModel.y << " ";
    return output;
}

std::istream& operator>>(std::istream& input, ARXModel& arxModel)
{
    // input >> arxModel.A >> arxModel.B >> arxModel.k >> arxModel.generator >> arxModel.distribution;
    input >> arxModel.A >> arxModel.B >> arxModel.k >> arxModel.u >> arxModel.y;

    if (input.fail()) {
        throw std::runtime_error("Error while reading ARXModel from input stream.");
    }

    return input;
}
