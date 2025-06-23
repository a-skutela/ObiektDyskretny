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

void Composite::deserializeImpl(std::istream& input)
{
    size_t size;
    input >> size;

    components.clear();
    
    for (size_t i = 0; i < size; ++i)
    {
        std::string type;
        input >> type;

        if (input.fail())
        {
            throw std::runtime_error("Error reading component type from input stream.");
        }

        std::shared_ptr<Component> component = ComponentFactory::createComponent(type);

        if (component)
        {
            component->deserialize(input);
            components.push_back(component);
        }
        else
        {
            throw std::runtime_error("Unknown component type: " + type);
        }
    }
}

void Composite::serializeImpl(std::ostream& output) const
{
    output << components.size() << " ";
    for (const auto& component : components)
    {
        output << component->getType() << " ";
        component->serialize(output);
    }
}
