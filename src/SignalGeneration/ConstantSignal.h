#pragma once

#include "Signal.h"

/**
 * \author Adrian Skutela
 * \class ConstantSignal
 * \brief Generates a constant signal with a fixed value.
 */
class ConstantSignal : public Signal
{
    double value;

public:
    /**
     * \brief Constructs a ConstantSignal instance.
     * \param value The constant value of the signal.
     */
    ConstantSignal(double value);

    /**
     * \brief Generates a single sample of the constant signal.
     * \return The constant value of the signal.
     */
    double generate() override;

    /**
     * \brief Returns the type of the signal.
     * \return The type of the signal as a string.
     */
    std::string getType() const override;

    /**
     * \brief Serializes the constant signal to an output stream.
     * \param output The output stream to serialize to.
     */
    void serialize(std::ostream& output) const override;

    /**
     * \brief Deserializes the constant signal from an input stream.
     * \param input The input stream to deserialize from.
     */
    void deserialize(std::istream& input) override;

    /**
     * \brief A constant signal with a value of 0.0.
     */
    static const ConstantSignal zero;

    /**
     * \brief A string representing the type of the signal.
     */
    static const std::string type;
};
