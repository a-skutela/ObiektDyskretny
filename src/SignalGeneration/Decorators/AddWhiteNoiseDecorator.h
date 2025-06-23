#pragma once

#include "SignalDecorator.h"
#include "../WhiteNoiseSignal.h"

/**
 * \author Adrian Skutela
 * \class AddWhiteNoiseDecorator
 * \brief Decorator that adds white noise to an existing signal.
 */
class AddWhiteNoiseDecorator : public SignalDecorator
{
    WhiteNoiseSignal whiteNoiseSignal;

public:
    /**
     * \brief Constructs an AddWhiteNoiseDecorator instance.
     * \param decoratedObject The signal to be decorated.
     * \param amplitude The amplitude of the white noise.
     */
    AddWhiteNoiseDecorator(std::shared_ptr<Signal> decoratedObject, double amplitude);

    /**
     * \brief Generates a single sample of the decorated signal.
     * \return A sample value of the decorated signal.
     */
    double generate() override;

    /**
     * \brief Retrieves the type of the decorator.
     * \return A string representing the type of the decorator.
     */
    std::string getType() const override;

    /**
     * \brief The type identifier for the AddWhiteNoiseDecorator.
     */
    static const std::string type;

protected:
    /**
     * \brief Serializes the AddWhiteNoiseDecorator-specific data to an output stream.
     * \param output The output stream to serialize to.
     */
    void serializeImpl(std::ostream& output) const override;

    /**
     * \brief Deserializes the AddWhiteNoiseDecorator-specific data from an input stream.
     * \param input The input stream to deserialize from.
     */
    void deserializeImpl(std::istream& input) override;
};
