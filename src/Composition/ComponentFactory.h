#pragma once

#include <memory>
#include "Component.h"

/**
 * \class ComponentFactory
 * \brief Factory class for creating components of various types.
 * \author Adrian Skutela
 */
class ComponentFactory 
{
public:
    /**
     * \brief Creates a component of the specified type.
     * \param type The type of the component to create.
     * \return A shared pointer to the created component.
     */
    static std::shared_ptr<Component> createComponent(const std::string& type);
};
