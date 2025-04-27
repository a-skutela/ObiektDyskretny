#pragma once
#include <memory>
#include "../Regulator/PIDRegulator.h"
#include "../ARXModel/ARXModel.h"

/**
 * \author Adrian Skutela
 * \class FeedbackLoop
 * \brief Represents a feedback loop that connects a regulator and an object.
 */
class FeedbackLoop 
{
    double y_prev;
public:
    /**
     * \brief Executes the feedback loop for a given setpoint.
     * \param w The desired setpoint value.
     * \param regulator The PID regulator used in the feedback loop.
     * \param object The ARXModel object used in the feedback loop.
     * \return The output value of the feedback loop.
     */
    double operator()(double w, PIDRegulator& regulator, ARXModel& object);
};