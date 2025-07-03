#pragma once

#include "Signal.h"

/**
 * \author Adrian Skutela
 * \class SinSignal
 * \brief Generates a sine wave signal.
 */
class SinSignal : public Signal
{
    double amplitude;
    double x1;
    double x2;
    double x1Factor;
    
public:
    SinSignal(double omega, double amplitude);
    
    double generate() override;

    /**
     * \brief Retrieves the type of the signal.
     * \return A string representing the type of the signal.
     */
    std::string getType() const override;

    /**
     * \brief Serializes the sine signal to an output stream.
     * \param output The output stream to serialize to.
     */
    void serialize(std::ostream& output) const override;

    /**
     * \brief Deserializes the sine signal from an input stream.
     * \param input The input stream to deserialize from.
     */
    void deserialize(std::istream& input) override;

    /**
     * \brief A string representing the type of the signal.
     */
    static const std::string type;
};
