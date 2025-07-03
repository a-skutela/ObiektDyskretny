#pragma once

#include "SignalDecorator.h"
#include "../TriangleSignal.h"

/**
 * \author Adrian Skutela
 * \class AddTriangleDecorator
 * \brief Decorator that adds a triangular wave to an existing signal.
 */
class AddTriangleDecorator : public SignalDecorator
{
    TriangleSignal triangleSignal;

public:
    /**
     * \brief Constructs an AddTriangleDecorator instance.
     * \param decoratedObject The signal to be decorated.
     * \param amplitude The amplitude of the triangular wave.
     * \param period The period of the triangular wave.
     */
    AddTriangleDecorator(std::shared_ptr<Signal> decoratedObject, double amplitude, long period);

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
