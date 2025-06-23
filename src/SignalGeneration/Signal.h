#pragma once

#include <istream>
#include <ostream>

/**
 * \author Adrian Skutela
 * \class Signal
 * \brief Abstract base class for signal generation.
 */
class Signal
{
public:
    /**
     * \brief Generates a single sample of the signal.
     * \return A sample value of the signal.
     */
    virtual double generate() = 0;

    /**
     * \brief Retrieves the type of the signal.
     * \return A string representing the type of the signal.
     */
    virtual std::string getType() const = 0;

    /**
     * \brief Serializes the signal to an output stream.
     * \param output The output stream to serialize to.
     */
    virtual void serialize(std::ostream& output) const = 0;

    /**
     * \brief Deserializes the signal from an input stream.
     * \param input The input stream to deserialize from.
     */
    virtual void deserialize(std::istream& input) = 0;

    /**
     * \brief Virtual destructor for the Signal class.
     */
    virtual ~Signal() = default;
};