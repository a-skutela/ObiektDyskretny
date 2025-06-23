#pragma once

#include <memory>
#include "../Signal.h"
#include "../SignalFactory.h"

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

    /**
     * \brief Serializes the decorator-specific data to an output stream.
     * \param output The output stream to serialize to.
     */
    virtual void serializeImpl(std::ostream& output) const = 0;

    /**
     * \brief Deserializes the decorator-specific data from an input stream.
     * \param input The input stream to deserialize from.
     */
    virtual void deserializeImpl(std::istream& input) = 0;

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

    /**
     * \brief Serializes the decorator and its decorated signal to an output stream.
     * \param output The output stream to serialize to.
     */
    void serialize(std::ostream& output) const override;

    /**
     * \brief Deserializes the decorator and its decorated signal from an input stream.
     * \param input The input stream to deserialize from.
     */
    void deserialize(std::istream& input) override;
};