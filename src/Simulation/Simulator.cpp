#include "Simulator.h"
#include "../Composition/SerialComposite.h"
#include "../Composition/ParallelComposite.h"
#include "../Composition/FeedbackComposite.h"
#include "../SignalGeneration/SinSignal.h"
#include "../SignalGeneration/Decorators/AddSinDecorator.h"
#include "../SignalGeneration/Decorators/ClampDecorator.h"
#include "../SignalGeneration/Decorators/AddRectDecorator.h"

Simulator::Simulator()
{
    topComponent = std::make_shared<SerialComposite>();
    signal = std::make_shared<AddConstantDecorator>(std::make_shared<ConstantSignal>(0.0), 0.0);
}

void Simulator::run()
{
    while(!shouldExit)
    {
        std::string command;
        std::cout << "Enter command (import, export, simulate, exit, example): ";
        std::cin >> command;

        if (command == "import")
        {
            importModel();
        }
        else if (command == "export")
        {
            exportModel();
        }
        else if (command == "simulate")
        {
            simulate();
        }
        else if (command == "exit")
        {
            shouldExit = true;
        }
        else if (command == "example")
        {
            example();
        }
        else
        {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
}

void Simulator::simulate()
{
    int steps = 0;
    if (std::cin.eof())
    {
        std::cout << "Number of steps expected";
        return;
    }
    std::cin >> steps;
    if (!std::cin.good())
    {
        std::cout << "Number of steps must be an intiger!" << std::endl;
        return;
    }

    if (steps <= 0)
    {
        std::cout << "Number of steps must be greater than 0!" << std::endl;
        return;
    }

    for (size_t i = 0; i < steps; ++i)
    {
        auto signalValue = signal->generate();
        auto output = topComponent->step(signalValue);

        std::cout << output << std::endl;
    }
}

void Simulator::importModel()
{
    std::string filename = "";

    if (std::cin.eof())
    {
        std::cout << "Filename expected";
        return;
    }

    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "File not found: " << filename << std::endl;
        return;
    }

    try 
    {
        topComponent->deserialize(file);
        signal->deserialize(file);
    } 
    catch (const std::exception& e) 
    {
        std::cout << "Error during import: " << e.what() << std::endl;
    }
}

constexpr auto pi = 3.14159265358979323846;

void Simulator::example()
{
    std::shared_ptr<Component> pid = std::make_shared<PIDRegulator>(0.5, 10.0, 0.2);
	std::shared_ptr<Component> multBy0p2 = std::make_shared<ARXModel>(std::vector<double>{0.0}, std::vector<double>{0.2}, 0, 0.0);
    std::shared_ptr<Composite> parallelComp = std::make_shared<ParallelComposite>();
    std::shared_ptr<Component> arx = std::make_shared<ARXModel>(std::vector<double>{ -0.4,0.2 }, std::vector<double>{ 0.6, 0.3 }, 2, 0);
    std::shared_ptr<Composite> feedbackLoop = std::make_shared<FeedbackComposite>();
    std::shared_ptr<SerialComposite> originalModel = std::make_shared<SerialComposite>();
    parallelComp->dodaj(multBy0p2);
    parallelComp->dodaj(multBy0p2);
    parallelComp->dodaj(multBy0p2);
    feedbackLoop->dodaj(pid);
    feedbackLoop->dodaj(arx);
    feedbackLoop->dodaj(parallelComp);
    originalModel->dodaj(feedbackLoop);

    std::shared_ptr<ConstantSignal> signal = std::make_shared<ConstantSignal>(0.0);
    std::shared_ptr<AddRectDecorator> rectDecorator = std::make_shared<AddRectDecorator>(signal, 10.0, 100, 0.5);
    std::shared_ptr<ClampDecorator> clampDecorator = std::make_shared<ClampDecorator>(rectDecorator, 0.0, 2.0);
    std::shared_ptr<AddConstantDecorator> originalSignal = std::make_shared<AddConstantDecorator>(clampDecorator, 0.0);

    this->topComponent = originalModel;
    this->signal = originalSignal;
}

void Simulator::exportModel()
{
    std::string filename = "";

    if (std::cin.eof())
    {
        std::cout << "Filename expected";
        return;
    }

    std::cin >> filename;

    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "File could not be opened: " << filename << std::endl;
        return;
    }

    try 
    {
        topComponent->serialize(file);
        signal->serialize(file);
    } 
    catch (const std::exception& e) 
    {
        std::cout << "Error during export: " << e.what() << std::endl;
        std::cout << "File might not contain valid data" << e.what() << std::endl;
    }
}