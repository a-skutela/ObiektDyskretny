#pragma once

#include <memory>
#include "Component.h"

class ComponentFactory 
{
public:
    static std::shared_ptr<Component> createComponent(const std::string& type);
};
