#pragma once

#include "SignalDecorator.h"
#include "../SinSignal.h"

/**
 * \author Adrian Skutela
 * \class AddSinDecorator
 * \brief Decorator that adds a sine wave to an existing signal.
 */
class AddSinDecorator : public SignalDecorator
{
    SinSignal sinSignal;
public:
    /**
     * \brief Constructs an AddSinDecorator instance.
     * \param decoratedObject The signal to be decorated.
     * \param omega The angular frequency of the sine wave.
     * \param amplitude The amplitude of the sine wave.
     */
    AddSinDecorator(std::shared_ptr<Signal> decoratedObject, double omega, double amplitude);

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
     * \brief A string representing the type of the signal.
     */
    static const std::string type;

protected:
    void serializeImpl(std::ostream& output) const override;
    void deserializeImpl(std::istream& input) override;
};