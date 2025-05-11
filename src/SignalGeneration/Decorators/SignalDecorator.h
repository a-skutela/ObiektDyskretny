
#pragma once

#include <memory>
#include "../Signal.h"

/**
 * \author Adrian Skutela
 * \class SignalDecorator
 * \brief Base class for signal decorators that modify or enhance signals.
 */
class SignalDecorator : public Signal
{
protected:
    /**
     * \brief The signal object to be decorated.
     */
    std::shared_ptr<Signal> decoratedObject;

public:
    /**
     * \brief Constructs a SignalDecorator instance.
     * \param decoratedObject The signal to be decorated.
     */
    SignalDecorator(std::shared_ptr<Signal> decoratedObject);

    /**
     * \brief Sets the decorated signal object.
     * \param decoratedObject The new signal to be decorated.
     */
    void setDecoratedObject(std::shared_ptr<Signal> decoratedObject);
};