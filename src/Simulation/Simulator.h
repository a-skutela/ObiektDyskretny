#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "../ObjectSISO.h"
#include "../Regulator/PIDRegulator.h"
#include "../Feedback/FeedbackLoop.h"
#include "../ARXModel/ARXModel.h"
#include "../Composition/SerialComposite.h"
#include "../Composition/ParallelComposite.h"
#include "../SignalGeneration/Signal.h"
#include "../SignalGeneration/ConstantSignal.h"
#include "../SignalGeneration/Decorators/AddConstantDecorator.h"

/**
 * \brief Simulator class for managing and simulating a model composed of various components.
 * \author Adrian Skutela
 */
class Simulator 
{
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<SerialComposite> topComponent;

    std::shared_ptr<AddConstantDecorator> signal;

    bool shouldExit = false;

    void importModel();

    void exportModel();

    void simulate();

    void list();

    void edit();

    void details();

    void example();

    void example2();

public:
    /**
     * \brief Constructs a new Simulator object.
     */
    Simulator();

    /**
     * \brief Runs the simulator, allowing user interaction for importing, exporting, and simulating models.
     */
    void run();
};
