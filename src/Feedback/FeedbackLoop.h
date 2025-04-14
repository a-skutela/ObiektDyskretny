#pragma once
#include <memory>
#include "../Regulator/PIDRegulator.h"
#include "../ARXModel/ARXModel.h"

class FeedbackLoop 
{
    double y_prev;
public:
    double operator()(double w, PIDRegulator& regulator, ARXModel& object);
};