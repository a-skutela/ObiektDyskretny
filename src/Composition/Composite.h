#pragma once

#include "Component.h"
#include <vector>
#include <memory>

class Composite : public Component
{
protected:
    std::vector<std::shared_ptr<Component>> components;

public:
    bool dodaj(std::shared_ptr<Component> component);

    bool usun(std::shared_ptr<Component> component);
};
