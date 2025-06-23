#pragma once

#include "Composite.h"

/**
 * \class FeedbackComposite
 * \brief Represents a composite that applies feedback to its components.
 * \author Adrian Skutela
 */
class FeedbackComposite : public Composite
{
    double y_prev;

public:
    /**
     * \brief Processes the input signal through the feedback composite.
     * \param input The input signal to process.
     * \return The processed output signal.
     */
    double step(double input);

    static const std::string type;

    /**
     * \brief Gets the type of the composite.
     * \return A string representing the type of the composite.
     */
    std::string getType() const override;
};
