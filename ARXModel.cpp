#include "ARXModel.h"


ARXModel::ARXModel(std::vector<double> A, std::vector<double> B, unsigned int k, double stdDev)
{
    this->k = k;
    this->A = A;
    this->B = B;
    u = std::deque<double>(B.size() + k);
    y = std::deque<double>(A.size());
}

double ARXModel::Step(double input)
{
    u.push_front(input);
    
    double Bu = std::inner_product(B.begin(), B.end(), u.begin() + k, 0.0);
    double Ay = std::inner_product(A.begin() + 1, A.end(), y.begin(), 0.0);
    double y0 = Bu + Ay + Noise();

    y.push_front(y0);

    u.pop_back();
    y.pop_back();

    return y0;
}

double Noise()
{
    return 0.0;
}