#pragma once

#include <memory>
#include "../ObjectSISO.h"

class Component : public ObjectSISO
{
public:
    virtual bool dodaj(std::shared_ptr<Component> component) = 0;

    virtual bool usun(std::shared_ptr<Component> component) = 0;
};
