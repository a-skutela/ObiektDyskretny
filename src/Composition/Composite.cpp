#include "Composite.h"
#include <algorithm>

bool Composite::dodaj(std::shared_ptr<Component> component)
{
    if (component != nullptr)
    {
        components.push_back(component);
        return true;
    }
    return false;
}

bool Composite::usun(std::shared_ptr<Component> component)
{
    auto position = std::find(components.begin(), components.end(), component);
    if (position != components.end())
    {
        components.erase(position);
        return true;
    }
    else
    {
        return false;
    }
}
