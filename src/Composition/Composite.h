#pragma once

#include "Component.h"
#include "ComponentFactory.h"
#include <vector>
#include <memory>

/**
 * \class Composite
 * \brief Represents a composite object that can contain multiple components.
 * \author Adrian Skutela
 */
class Composite : public Component
{
protected:
    std::vector<std::shared_ptr<Component>> components;

public:
    /**
     * \brief Adds a component to the composite.
     * \param component A shared pointer to the component to be added.
     * \return True if the component was added successfully, false otherwise.
     */
    bool dodaj(std::shared_ptr<Component> component);

    /**
     * \brief Removes a component from the composite.
     * \param component A shared pointer to the component to be removed.
     * \return True if the component was removed successfully, false otherwise.
     */
    bool usun(std::shared_ptr<Component> component);

    /**
     * \brief Serializes the component to an output stream.
     * \param output The output stream to serialize to.
     */
    virtual void serialize(std::ostream& output) const
    {
        output << getType() << " ";
        output << components.size() << " ";
        for (const auto& component : components)
        {
            component->serialize(output);
        }
    }

    /**
     * \brief Deserializes the component from an input stream.
     * \param input The input stream to deserialize from.
     */
    virtual void deserialize(std::istream& input)
    {
        size_t size;
        input >> size;

        components.clear();
        
        for (size_t i = 0; i < size; ++i)
        {
            std::string type;
            input >> type;
            std::shared_ptr<Component> component = ComponentFactory::createComponent(type);

            if (component)
            {
                components.push_back(component);
            }
            else
            {
                throw std::runtime_error("Unknown component type: " + type);
            }
        }
    }
};
