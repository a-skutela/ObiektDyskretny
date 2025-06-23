#pragma once

#include <memory>
#include "signal.h"

class SignalFactory
{
public:
    /**
     * \brief Creates a signal based on the provided type.
     * \param type The type of the signal to create.
     * \return A shared pointer to the created signal, or nullptr if the type is not recognized.
     */
    static std::shared_ptr<Signal> createSignal(const std::string& type);
};
