#pragma once

/**
 * \author Adrian Skutela
 * \class ObjectSISO
 * \brief Represents an abstract object that produces a single output for a single input.
 */
class ObjectSISO
{
public:
    /**
     * \brief Calculates the output of the object for a given input.
     * \param input The input value.
     * \return The output value.
     */
    virtual double step(double input) = 0;

    /**
     * \brief Virtual destructor for the ObjectSISO class.
     */
    virtual ~ObjectSISO() = default;
};