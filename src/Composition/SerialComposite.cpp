#include "SerialComposite.h"

double SerialComposite::step(double input)
{
    double y = input;
    for(auto component : components)
    {
        y = component->step(y);
    }
    return y;
}

std::string const SerialComposite::type = "SerialComposite";

std::string SerialComposite::getType() const
{
    return SerialComposite::type;
}
