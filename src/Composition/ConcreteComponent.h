#pragma once

#include "Component.h"

class ConcreteComponent : public Component
{
public:
    /**
     * \brief Does nothing
     * \param component is ignored
     * \return always returns false
     */
    bool dodaj(std::shared_ptr<Component> component) override;

    /**
     * \brief Does nothing
     * \param component is ignored
     * \return always returns false
     */
    bool usun(std::shared_ptr<Component> component) override;
};
