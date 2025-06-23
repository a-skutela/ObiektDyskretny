#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <memory>
#include <functional>
#include <sstream>
#include "Regulator/PIDRegulator.h"
#include "Feedback/FeedbackLoop.h"
#include "ARXModel/ARXModel.h"
#include "Composition/SerialComposite.h"
#include "Composition/ParallelComposite.h"
#include "Composition/FeedbackComposite.h"
#include "Simulation/Simulator.h"

#include "SignalGeneration/SinSignal.h"
#include "SignalGeneration/RectSignal.h"
#include "SignalGeneration/TriangleSignal.h"
#include "SignalGeneration/WhiteNoiseSignal.h"
#include "SignalGeneration/ConstantSignal.h"
#include "SignalGeneration/Decorators/AddSinDecorator.h"
#include "SignalGeneration/Decorators/AddRectDecorator.h"
#include "SignalGeneration/Decorators/AddTriangleDecorator.h"
#include "SignalGeneration/Decorators/AddWhiteNoiseDecorator.h"
#include "SignalGeneration/Decorators/AddConstantDecorator.h"
#include "SignalGeneration/Decorators/ClampDecorator.h"

using namespace std;

#define MAIN

#ifdef DEBUG

constexpr auto pi = 3.14159265358979323846;

void raportBleduSekwencji(std::vector<double>& spodz, std::vector<double>& fakt)
{
	constexpr size_t PREC = 3;
	std::cerr << std::fixed << std::setprecision(PREC);
	std::cerr << "  Spodziewany:\t";
	for (auto& el : spodz)
		std::cerr << el << ", ";
	std::cerr << "\n  Faktyczny:\t";
	for (auto& el : fakt)
		std::cerr << el << ", ";
	std::cerr << std::endl << std::endl;
}

bool porownanieSekwencji(std::vector<double>& spodz, std::vector<double>& fakt)
{
	constexpr double TOL = 1e-3;	// tolerancja dla porównań zmiennoprzecinkowych
	bool result = fakt.size() == spodz.size();
	for (int i = 0; result && i < fakt.size(); i++)
		result = std::fabs(fakt[i] - spodz[i]) < TOL;
	return result;
}

void test_SISO(std::shared_ptr<ObjectSISO> sut, std::shared_ptr<ObjectSISO> goldenModel, std::vector<double> inputs)
{
    std::vector<double> goldenModelOutputs;
    std::vector<double> sutOutputs;
    for (auto i : inputs)
    {
        double output = sut->step(i);
        sutOutputs.push_back(output);
        double goldenOutput = goldenModel->step(i);
        goldenModelOutputs.push_back(goldenOutput);
    }
   
    if (porownanieSekwencji(goldenModelOutputs, sutOutputs))
        std::cerr << "OK!\n";
    else
    {
        std::cerr << "FAIL!\n";
        raportBleduSekwencji(goldenModelOutputs, sutOutputs);
    }
}

void test_model_serdes()
{   
    std::cout << "Porownanie wynikow oryginalnego i zdeserializowanego modelu:\n";

    std::shared_ptr<Component> pid = std::make_shared<PIDRegulator>(0.5, 10.0, 0.2);
	std::shared_ptr<Component> multBy2 = std::make_shared<ARXModel>(std::vector<double>{0.0}, std::vector<double>{2.0}, 0, 0.0);
    std::shared_ptr<Composite> parallelComp = std::make_shared<ParallelComposite>();
    std::shared_ptr<Component> arx = std::make_shared<ARXModel>(std::vector<double>{ -0.4,0.2 }, std::vector<double>{ 0.6, 0.3 }, 2, 0);
    std::shared_ptr<Composite> feedbackLoop = std::make_shared<FeedbackComposite>();
    std::shared_ptr<SerialComposite> originalModel = std::make_shared<SerialComposite>();
    parallelComp->dodaj(multBy2);
    parallelComp->dodaj(multBy2);
    parallelComp->dodaj(multBy2);
    feedbackLoop->dodaj(pid);
    feedbackLoop->dodaj(arx);
    feedbackLoop->dodaj(parallelComp);
    originalModel->dodaj(feedbackLoop);

    std::stringstream ss;
    originalModel->serialize(ss);

    std::shared_ptr<SerialComposite> deserializedModel = std::make_shared<SerialComposite>();
    deserializedModel->deserialize(ss);

    test_SISO(originalModel, deserializedModel, std::vector<double>{0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0});
}

void test_signal_serdes()
{   
    std::cout << "Porownanie wynikow oryginalnego i zdeserializowanego generatora sygnalow:\n";

    std::shared_ptr<ConstantSignal> signal = std::make_shared<ConstantSignal>(0.0);
    std::shared_ptr<AddSinDecorator> sinDecorator = std::make_shared<AddSinDecorator>(signal, pi * 0.01, 0.8);
    std::shared_ptr<ClampDecorator> clampDecorator = std::make_shared<ClampDecorator>(sinDecorator, -0.5, 0.5);
    std::shared_ptr<AddConstantDecorator> originalSignal = std::make_shared<AddConstantDecorator>(clampDecorator, 0.0);

    std::stringstream ss;
    originalSignal->serialize(ss);

    std::shared_ptr<AddConstantDecorator> deserializedSignal = std::make_shared<AddConstantDecorator>(nullptr, 0.0);
    deserializedSignal->deserialize(ss);

    constexpr size_t nIter = 20;

    std::vector<double> originalOutputs(nIter);
    std::vector<double> deserializedOutputs(nIter);
    for (size_t i = 0; i < nIter; ++i)
    {
        originalOutputs[i] = originalSignal->generate();
        deserializedOutputs[i] = deserializedSignal->generate();
    }

    if (porownanieSekwencji(originalOutputs, deserializedOutputs))
        std::cout << "OK!\n";
    else
    {
        std::cout << "FAIL!\n";
        raportBleduSekwencji(originalOutputs, deserializedOutputs);
    }
}

void test_full()
{   
    std::cout << "Porownanie wynikow oryginalnej i zdeserializowanej symulacji:\n";

    std::shared_ptr<Component> pid = std::make_shared<PIDRegulator>(0.5, 10.0, 0.2);
	std::shared_ptr<Component> multBy2 = std::make_shared<ARXModel>(std::vector<double>{0.0}, std::vector<double>{2.0}, 0, 0.0);
    std::shared_ptr<Composite> parallelComp = std::make_shared<ParallelComposite>();
    std::shared_ptr<Component> arx = std::make_shared<ARXModel>(std::vector<double>{ -0.4,0.2 }, std::vector<double>{ 0.6, 0.3 }, 2, 0);
    std::shared_ptr<Composite> feedbackLoop = std::make_shared<FeedbackComposite>();
    std::shared_ptr<SerialComposite> originalModel = std::make_shared<SerialComposite>();
    parallelComp->dodaj(multBy2);
    parallelComp->dodaj(multBy2);
    parallelComp->dodaj(multBy2);
    feedbackLoop->dodaj(pid);
    feedbackLoop->dodaj(arx);
    feedbackLoop->dodaj(parallelComp);
    originalModel->dodaj(feedbackLoop);

    std::shared_ptr<ConstantSignal> signal = std::make_shared<ConstantSignal>(0.0);
    std::shared_ptr<AddSinDecorator> sinDecorator = std::make_shared<AddSinDecorator>(signal, pi * 0.01, 0.8);
    std::shared_ptr<ClampDecorator> clampDecorator = std::make_shared<ClampDecorator>(sinDecorator, -0.5, 0.5);
    std::shared_ptr<AddConstantDecorator> originalSignal = std::make_shared<AddConstantDecorator>(clampDecorator, 0.0);

    for (size_t i = 0; i < 5; ++i)
    {
        originalModel->step(originalSignal->generate());
    }

    std::stringstream ss;
    originalModel->serialize(ss);
    originalSignal->serialize(ss);

    std::shared_ptr<SerialComposite> deserializedModel = std::make_shared<SerialComposite>();
    deserializedModel->deserialize(ss);

    std::shared_ptr<AddConstantDecorator> deserializedSignal = std::make_shared<AddConstantDecorator>(nullptr, 0.0);
    deserializedSignal->deserialize(ss);
    

    constexpr size_t nIter = 10;
    
    std::vector<double> originalOutputs(nIter);
    std::vector<double> deserializedOutputs(nIter);
    for (size_t i = 0; i < nIter; ++i)
    {
        auto originalSignalValue = originalSignal->generate();
        originalOutputs[i] = originalModel->step(originalSignalValue);

        auto deserializedSignalValue = deserializedSignal->generate();
        deserializedOutputs[i] = deserializedModel->step(deserializedSignalValue);
    }

    if (porownanieSekwencji(originalOutputs, deserializedOutputs))
        std::cout << "OK!\n";
    else
    {
        std::cout << "FAIL!\n";
        raportBleduSekwencji(originalOutputs, deserializedOutputs);
    }
}

int main()
{
    test_model_serdes();
    test_signal_serdes();
    test_full();
}

#endif

#ifdef MAIN

int main()
{
	Simulator simulator;

    simulator.run();
}

#endif