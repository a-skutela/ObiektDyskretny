#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "Regulator/PIDRegulator.h"
#include "Feedback/FeedbackLoop.h"
#include "ARXModel/ARXModel.h"
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

int main()
{
	// test_sinGeneration();
    // test_rectGeneration();
	// test_triangleGeneration();
	// test_whiteNoiseGeneration();
	// test_constantGeneration();
    test_decoration();
    test_decoration2();
}
