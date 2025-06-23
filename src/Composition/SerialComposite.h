#pragma once

#include "Composite.h"

/**
 * \class SerialComposite
 * \brief Represents a composite that processes components in series.
 * \author Adrian Skutela
 */
class SerialComposite : public Composite
{
public:
    double step(double input);

    static const std::string type;

    /**
     * \brief Gets the type of the composite.
     * \return A string representing the type of the composite.
     */
    std::string getType() const override;
};
