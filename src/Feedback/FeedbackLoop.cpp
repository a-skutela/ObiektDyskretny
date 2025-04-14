#include "FeedbackLoop.h"
#include <iostream>

double FeedbackLoop::operator()(double setpoint, PIDRegulator& regulator, ARXModel& object)
{
    double error = setpoint - y_prev;
    double y = object.step(regulator.step(error));
    y_prev = y;
    return y;
}