#include "serialization.h"
#include "../ARXModel/ARXModel.h"

std::ostream& operator<<(std::ostream& output, const ARXModel& arxModel)
{
    output << arxModel.getType() << arxModel.A << " " << arxModel.B << " " << arxModel.k << " " << arxModel.generator << " " << arxModel.distribution << " ";
    return output;
}

std::istream& operator>>(std::istream& input, ARXModel& arxModel)
{
    std::string type;
    input >> type;
    
    if (type != ARXModel::type) {
        throw std::runtime_error("Expected type " + ARXModel::type + ", but got " + type);
    }

    input >> arxModel.A >> arxModel.B >> arxModel.k >> arxModel.generator >> arxModel.distribution;
    return input;
}
