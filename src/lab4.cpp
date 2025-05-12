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

using namespace std;

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
    test_serialComposition();
    test_parallelComposition();
}
