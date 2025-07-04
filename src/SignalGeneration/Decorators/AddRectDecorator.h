#pragma once

#include "SignalDecorator.h"
#include "../RectSignal.h"

/**
 * \author Adrian Skutela
 * \class AddRectDecorator
 * \brief Decorator that adds a rectangular wave to an existing signal.
 */
class AddRectDecorator : public SignalDecorator
{
    RectSignal rectSignal;

public:
    /**
     * \brief Constructs an AddRectDecorator instance.
     * \param decoratedObject The signal to be decorated.
     * \param amplitude The amplitude of the rectangular wave.
     * \param period The period of the rectangular wave.
     * \param fillFactor The fill factor of the rectangular wave.
     */
    AddRectDecorator(std::shared_ptr<Signal> decoratedObject, double amplitude, long period, double fillFactor);

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
