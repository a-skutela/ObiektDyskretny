#include "Simulator.h"
#include "../Composition/SerialComposite.h"
#include "../Composition/ParallelComposite.h"
#include "../Composition/FeedbackComposite.h"
#include "../SignalGeneration/SinSignal.h"
#include "../SignalGeneration/Decorators/AddSinDecorator.h"
#include "../SignalGeneration/Decorators/ClampDecorator.h"
#include "../SignalGeneration/Decorators/AddRectDecorator.h"
#include "../Regulator/PIDRegulator.h"

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
        std::cout << "Enter command (import, export, simulate, list, edit, details, exit): ";
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
        else if (command == "example2")
        {
            example2();
        }
        else if (command == "list")
        {
            list();
        }
        else if (command == "details")
        {
            details();
        }
        else if (command == "edit")
        {
            edit();
        }
        else
        {
            std::cout << "Unknown command: " << command << std::endl;
            std::cin.clear();
            std::cin.ignore();
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
        std::cout << "Number of steps must be an integer!" << std::endl;
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

        std::cout << "setpoint: " << signalValue << "   output: " << output << std::endl;
    }
}

void Simulator::importModel()
{
    components = std::vector<std::shared_ptr<Component>>();
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
        topComponent->deserialize(file, components);
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
    components = std::vector<std::shared_ptr<Component>>{pid, multBy0p2, arx, parallelComp, multBy0p2, feedbackLoop};

    std::shared_ptr<ConstantSignal> signal = std::make_shared<ConstantSignal>(0.0);
    std::shared_ptr<AddRectDecorator> rectDecorator = std::make_shared<AddRectDecorator>(signal, 10.0, 100, 0.5);
    std::shared_ptr<ClampDecorator> clampDecorator = std::make_shared<ClampDecorator>(rectDecorator, 0.0, 2.0);
    std::shared_ptr<AddConstantDecorator> originalSignal = std::make_shared<AddConstantDecorator>(clampDecorator, 0.0);

    this->topComponent = originalModel;
    this->signal = originalSignal;
}

void Simulator::example2()
{
    std::shared_ptr<Component> pid = std::make_shared<PIDRegulator>(0.5, 10.0, 0.2);
    std::shared_ptr<Component> arx = std::make_shared<ARXModel>(std::vector<double>{ -0.4 }, std::vector<double>{ 0.6 }, 2, 0);
    std::shared_ptr<Composite> feedbackLoop = std::make_shared<FeedbackComposite>();
    std::shared_ptr<SerialComposite> originalModel = std::make_shared<SerialComposite>();
    feedbackLoop->dodaj(pid);
    feedbackLoop->dodaj(arx);
    originalModel->dodaj(feedbackLoop);
    components = std::vector<std::shared_ptr<Component>>{pid, arx, feedbackLoop};

    std::shared_ptr<ConstantSignal> signal = std::make_shared<ConstantSignal>(0.0);
    std::shared_ptr<AddRectDecorator> rectDecorator = std::make_shared<AddRectDecorator>(signal, 2.0, 100, 0.5);
    std::shared_ptr<AddConstantDecorator> originalSignal = std::make_shared<AddConstantDecorator>(rectDecorator, 0.0);

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

void Simulator::list()
{
    for (size_t i = 0; i < components.size(); i++)
    {
        std::cout << i << ") " << components[i]->getType() << std::endl;
    }
}

void Simulator::edit()
{
    int index = 0;
    std::cin >> index;

    if (!std::cin.good())
    {
        std::cout << "Index must be an integer!" << std::endl;
        return;
    }

    if (index >= components.size())
    {
        std::cout << "Index out of range" << std::endl;
        return;
    }

    auto component = components[index];

    if (component->getType() == PIDRegulator::type)
    {
        auto pid = std::dynamic_pointer_cast<PIDRegulator>(component);
        double k;
        double Ti;
        double Td;

        std::cin >> k >> Ti >> Td;

        if (!std::cin.good())
        {
            std::cout << "IUnknown Error!" << std::endl;
            return;
        }

        pid->setK(k);
        pid->setTi(Ti);
        pid->setTd(Td);
    }
    else if (component->getType() == ARXModel::type)
    {
        auto arx = std::dynamic_pointer_cast<ARXModel>(component);
        int orderA;
        int orderB;
        std::vector<double> A;
        std::vector<double> B;
        int k;

        std::cout << "Podaj liczbe wspolczynnikow A" << std::endl;
        std::cin >> orderA;

        A = std::vector<double>(orderA);
        std::cout << "Podaj wspolczynniki A (od 0) oddzielone spacja" << std::endl;

        for (int i = 0; i < orderA; i++)
        {
            std::cin >> A[i];
        }
        
        std::cout << "Podaj liczbe wspolczynnikow B" << std::endl;
        std::cin >> orderB;

        B = std::vector<double>(orderB);
        std::cout << "Podaj wspolczynniki B (od 0) oddzielone spacja" << std::endl;

        for (int i = 0; i < orderB; i++)
        {
            std::cin >> B[i];
        }
        
        std::cout << "Podaj k" << std::endl;
        std::cin >> k;

        if (!std::cin.good())
        {
            std::cout << "Unknown Error!" << std::endl;
            return;
        }

        arx->setA(A);
        arx->setB(B);
        arx->setK(k);
    }
    else
    {
        std::cout << "Component " << component->getType() << " is not editable" << std::endl;
    }
}

void Simulator::details()
{
    int index = 0;
    std::cin >> index;

    if (!std::cin.good())
    {
        std::cout << "Index must be an integer!" << std::endl;
        return;
    }

    if (index >= components.size())
    {
        std::cout << "Index out of range" << std::endl;
        return;
    }

    components[index]->print(std::cout);
}