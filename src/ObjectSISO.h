#pragma once

/**
 * \author Adrian Skutela
 * \class ObjectSISO
 * \brief Represents an abstract object that produces single output for a single input.
 */
class ObjectSISO
{
public:
    virtual double step(double input) = 0;
    virtual ~ObjectSISO() = default;
};