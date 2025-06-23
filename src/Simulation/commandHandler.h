#pragma once

#include <map>
#include <string>
#include "../ObjectSISO.h"
#include "Regulator/PIDRegulator.h"
#include "Feedback/FeedbackLoop.h"
#include "ARXModel/ARXModel.h"
#include "Composition/SerialComposite.h"
#include "Composition/ParallelComposite.h"

class CommandHandler 
{
    std::map<int, std::shared_ptr<Component>> components;
    std::shared_ptr<SerialComposite> defaultObject;

public:
    CommandHandler()
    {
        defaultObject = std::make_shared<SerialComposite>();
    }


};
