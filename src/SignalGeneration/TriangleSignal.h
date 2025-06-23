#pragma once

#include "Signal.h"

/**
 * \author Adrian Skutela
 * \class TriangleSignal
 * \brief Generates a triangle wave signal.
 */
class TriangleSignal : public Signal
{
    long period;
    double amplitude;
    
    long counter;
    long midpoint;
    bool ascending;
public:
    /**
     * \brief Constructs a TriangleSignal instance.
     * \param amplitude The amplitude of the triangle wave.
     * \param period The period of the triangle wave.
     */
    TriangleSignal(double amplitude, long period);

    /**
     * \brief Generates a single sample of the triangle wave.
     * \return A sample value of the triangle wave.
     */
    double generate() override;

    /**
     * \brief Retrieves the type of the signal.
     * \return A string representing the type of the signal.
     */
    std::string getType() const override;

    /**
     * \brief Serializes the triangle signal to an output stream.
     * \param output The output stream to serialize to.
     */
    void serialize(std::ostream& output) const override;

    /**
     * \brief Deserializes the triangle signal from an input stream.
     * \param input The input stream to deserialize from.
     */
    void deserialize(std::istream& input) override;

    static const std::string type;
};