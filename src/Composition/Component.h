#pragma once

#include <memory>
#include <istream>
#include <ostream>
#include <string>
#include "../ObjectSISO.h"

/**
 * \class Component
 * \brief Abstract base class for components in a composite structure.
 * \author Adrian Skutela
 */
class Component : public ObjectSISO
{
public:
    /**
     * \brief Adds a child component to the composite structure.
     * \param component The component to add.
     * \return True if the component was added successfully, false otherwise.
     */
    virtual bool dodaj(std::shared_ptr<Component> component) = 0;

    /**
     * \brief Removes a child component from the composite structure.
     * \param component The component to remove.
     * \return True if the component was removed successfully, false otherwise.
     */
    virtual bool usun(std::shared_ptr<Component> component) = 0;

    /**
     * \brief Serializes the component to an output stream.
     * \param output The output stream to serialize to.
     */
    virtual void serialize(std::ostream& output) const = 0;

    /**
     * \brief Deserializes the component from an input stream.
     * \param input The input stream to deserialize from.
     */
    virtual void deserialize(std::istream& input) = 0;

    /**
     * \brief Retrieves the type of the component as a string.
     * \return A string representing the type of the component.
     */
    virtual std::string getType() const = 0;
};
