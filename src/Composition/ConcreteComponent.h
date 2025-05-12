#pragma once

#include "Component.h"

class ConcreteComponent : public Component
{
public:
    bool dodaj(std::shared_ptr<Component> component) override;

    bool usun(std::shared_ptr<Component> component) override;
};
