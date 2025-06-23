#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <memory>
#include <functional>
#include "Regulator/PIDRegulator.h"
#include "Feedback/FeedbackLoop.h"
#include "ARXModel/ARXModel.h"
#include "Composition/SerialComposite.h"
#include "Composition/ParallelComposite.h"

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

constexpr auto pi = 3.14159265358979323846;

void test_sinGeneration()
{
	std::cout << "###################" << std::endl;
	std::cout << "sin " << std::endl;
	std::cout << "###################" << std::endl;
	SinSignal sinSignal(pi * 0.125, 1.0);
    for (int i = 0; i < 20; i++)
    {
        std::cout << std::fixed << std::setprecision(2) << sinSignal.generate() << std::endl;
    }
	std::cout << std::endl;
}

void test_rectGeneration()
{
	std::cout << "###################" << std::endl;
	std::cout << "rect " << std::endl;
	std::cout << "###################" << std::endl;
	RectSignal signal(1.0, 10, 0.6);
    for (int i = 0; i < 20; i++)
    {
        std::cout << std::fixed << std::setprecision(2) << signal.generate() << std::endl;
    }
	std::cout << std::endl;
}

void test_triangleGeneration()
{
	std::cout << "###################" << std::endl;
	std::cout << "triangle " << std::endl;
	std::cout << "###################" << std::endl;
	TriangleSignal signal(1.0, 10);
	for (int i = 0; i < 20; i++)
	{
		std::cout << std::fixed << std::setprecision(2) << signal.generate() << std::endl;
	}
	std::cout << std::endl;
}

void test_whiteNoiseGeneration()
{
	std::cout << "###################" << std::endl;
	std::cout << "white noise " << std::endl;
	std::cout << "###################" << std::endl;
	WhiteNoiseSignal signal(1.0);
	for (int i = 0; i < 20; i++)
	{
		std::cout << std::fixed << std::setprecision(2) << signal.generate() << std::endl;
	}
	std::cout << std::endl;
}

void test_constantGeneration()
{
	std::cout << "###################" << std::endl;
	std::cout << "constant " << std::endl;
	std::cout << "###################" << std::endl;
	ConstantSignal signal(5.0);
	for (int i = 0; i < 20; i++)
	{
		std::cout << std::fixed << std::setprecision(2) << signal.generate() << std::endl;
	}
	std::cout << std::endl;
}

void test_decoration()
{
	std::cout << "###################" << std::endl;
	std::cout << "constant + rectangular + triangular + noise" << std::endl;
	std::cout << "###################" << std::endl;

    std::shared_ptr<ConstantSignal> signal = std::make_shared<ConstantSignal>(0.0);
    std::shared_ptr<AddRectDecorator> rectDecorator = std::make_shared<AddRectDecorator>(signal, 1.0, 20, 0.5);
    std::shared_ptr<AddTriangleDecorator> triangleDecorator = std::make_shared<AddTriangleDecorator>(rectDecorator, 1.0, 10);
    std::shared_ptr<AddWhiteNoiseDecorator> noiseDecorator = std::make_shared<AddWhiteNoiseDecorator>(triangleDecorator, 0.1);
    std::shared_ptr<AddConstantDecorator> constantDecorator = std::make_shared<AddConstantDecorator>(noiseDecorator, 5.0);

	for (int i = 0; i < 50; i++)
	{
		std::cout << std::fixed << std::setprecision(2) << constantDecorator->generate() << std::endl;
	}
	std::cout << std::endl;
}

void test_decoration2()
{
	std::cout << "###################" << std::endl;
	std::cout << "sin + clamp" << std::endl;
	std::cout << "###################" << std::endl;

    std::shared_ptr<ConstantSignal> signal = std::make_shared<ConstantSignal>(0.0);
    std::shared_ptr<AddSinDecorator> sinDecorator = std::make_shared<AddSinDecorator>(signal, pi * 0.05, 0.8);
    std::shared_ptr<ClampDecorator> clampDecorator = std::make_shared<ClampDecorator>(sinDecorator, -0.5, 0.5);

	for (int i = 0; i < 50; i++)
	{
		std::cout << std::fixed << std::setprecision(2) << clampDecorator->generate() << std::endl;
	}
	std::cout << std::endl;
}

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

void test_serialComposition()
{
	std::shared_ptr<Component> multBy2 = std::make_shared<ARXModel>(std::vector<double>{0.0}, std::vector<double>{2.0}, 0, 0.0);
    std::shared_ptr<Composite> serialComp = std::make_shared<SerialComposite>();
    serialComp->dodaj(multBy2);
    serialComp->dodaj(multBy2);
    serialComp->dodaj(multBy2);

    constexpr size_t LICZ_ITER = 30;
    std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu, 
    std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
    std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

    // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
    for (int i = 0; i < LICZ_ITER; i++)
    {
        sygWe[i] = i;
        spodzSygWy[i] = i * 8.0;
    }

    // Symulacja modelu:
    for (int i = 0; i < LICZ_ITER; i++)
        faktSygWy[i] = serialComp->step(sygWe[i]);

    // Walidacja poprawności i raport:
    if (porownanieSekwencji(spodzSygWy, faktSygWy))
        std::cerr << "OK!\n";
    else
    {
        std::cerr << "FAIL!\n";
        raportBleduSekwencji(spodzSygWy, faktSygWy);
    }
}

void test_parallelComposition()
{
	std::shared_ptr<Component> multBy2 = std::make_shared<ARXModel>(std::vector<double>{0.0}, std::vector<double>{2.0}, 0, 0.0);
    std::shared_ptr<Composite> serialComp = std::make_shared<ParallelComposite>();
    serialComp->dodaj(multBy2);
    serialComp->dodaj(multBy2);
    serialComp->dodaj(multBy2);

    constexpr size_t LICZ_ITER = 30;
    std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu, 
    std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
    std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

    // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
    for (int i = 0; i < LICZ_ITER; i++)
    {
        sygWe[i] = i;
        spodzSygWy[i] = i * 6.0;
    }

    // Symulacja modelu:
    for (int i = 0; i < LICZ_ITER; i++)
        faktSygWy[i] = serialComp->step(sygWe[i]);

    // Walidacja poprawności i raport:
    if (porownanieSekwencji(spodzSygWy, faktSygWy))
        std::cerr << "OK!\n";
    else
    {
        std::cerr << "FAIL!\n";
        raportBleduSekwencji(spodzSygWy, faktSygWy);
    }
}

void test_SISO(std::shared_ptr<ObjectSISO> sut, std::function<double(double)> goldenModel, std::vector<double> inputs)
{
    
}

int main()
{
	test_sinGeneration();
    test_rectGeneration();
	test_triangleGeneration();
	test_whiteNoiseGeneration();
	test_constantGeneration();
    test_decoration();
    test_decoration2();
    test_serialComposition();
    test_parallelComposition();
}
