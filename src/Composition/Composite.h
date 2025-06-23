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
    /**
     * \brief A vector of shared pointers to components contained in the composite.
     */
    std::vector<std::shared_ptr<Component>> components;

    /**
     * \brief Serializes the component to an output stream.
     * \param output The output stream to serialize to.
     */
    virtual void serializeImpl(std::ostream& output) const;

    /**
     * \brief Deserializes the component from an input stream.
     * \param input The input stream to deserialize from.
     */
    virtual void deserializeImpl(std::istream& input, std::vector<std::shared_ptr<Component>>& gComponents);

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

    void print(std::ostream& output) const override;
};
