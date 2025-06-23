#pragma once

#include "SignalDecorator.h"

/**
 * \author Adrian Skutela
 * \class ClampDecorator
 * \brief Decorator that clamps the amplitude of a signal to a specified range.
 */
class ClampDecorator : public SignalDecorator
{
    double minValue;
    double maxValue;

public:
    /**
     * \brief Constructs a ClampDecorator instance.
     * \param decoratedObject The signal to be decorated.
     * \param minValue The minimum allowed amplitude.
     * \param maxValue The maximum allowed amplitude.
     */
    ClampDecorator(std::shared_ptr<Signal> decoratedObject, double minValue, double maxValue);

    /**
     * \brief Generates a single sample of the decorated signal.
     * \return A sample value of the decorated signal, clamped to the specified range.
     */
    double generate() override;

    /**
     * \brief Retrieves the type of the decorator.
     * \return A string representing the type of the decorator.
     */
    std::string getType() const override;

    /**
     * \brief The type identifier for the ClampDecorator.
     */
    static const std::string type;

protected:
    /**
     * \brief Serializes the ClampDecorator-specific data to an output stream.
     * \param output The output stream to serialize to.
     */
    void serializeImpl(std::ostream& output) const override;

    /**
     * \brief Deserializes the ClampDecorator-specific data from an input stream.
     * \param input The input stream to deserialize from.
     */
    void deserializeImpl(std::istream& input) override;
};
