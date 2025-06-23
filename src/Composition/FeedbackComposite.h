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

    /**
     * \brief Serializes the composite to an output stream.
     * \param output The output stream to serialize to.
     */
    void serialize(std::ostream& output) const override;

    /**
     * \brief Deserializes the composite from an input stream.
     * \param input The input stream to deserialize from.
     */
    void deserialize(std::istream& input) override;
};
