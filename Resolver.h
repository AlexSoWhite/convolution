//
// Created by alex on 07.12.2021.
//

#ifndef CONVOLUTION_RESOLVER_H
#define CONVOLUTION_RESOLVER_H

#include "Generator.h"
#include "Presenter.h"
#include "Methods.h"
#include <map>

enum tasks{
    LINEAR,
    CIRCULAR,
    DLINEAR,
    DCIRCULAR,
    INTERPOLATION,
    THINNING
};

void resolve(tasks task) {
    std::vector<int> x, h, y;
    std::vector<std::vector<int>> dx, dh, dy;
    char c;
    int n, m;
    switch (task) {
        case LINEAR:
        case CIRCULAR:
            n = rand()%3 + 3;
            x = generator::generateVector(n);
            h = generator::generateVector(task == LINEAR ? rand()%3 + 3 : n);
            std::cout<<"{x(i)} = ";
            Presenter::outputVector(x);
            std::cout<<std::endl;
            std::cout<<"{h(i)} = ";
            Presenter::outputVector(h);
            std::cout<<std::endl;
            std::cin >> c;
            y = task == LINEAR ? convolution::solveLinearConvolution(x,h) : convolution::solveCircularConvolution(x,h);
            std::cout<<"{y(n)} = ";
            Presenter::outputVector(y);
            std::cout<<std::endl;
            break;
        case DLINEAR:
        case DCIRCULAR:
            n = rand()%3 + 2, m = rand()%3 + 2;
            dx = generator::generateDoubleVector(m, n);
            dh = task == DLINEAR ? generator::generateDoubleVector(rand()%3+2,rand()%3+2) : generator::generateDoubleVector(m,n);
            std::cout<<"{x(i,j)} = "<<std::endl;
            Presenter::outputTwoDimensionalVector(dx);
            std::cout<<"{h(i,j)} = "<<std::endl;
            Presenter::outputTwoDimensionalVector(dh);
            std::cout<<std::endl;
            std::cout<<"coordinates system? (p/a) ";
            std::cin>>c;
            char d;
            std::cin>>d;
            if (c == 'p') {
                dy = task == DLINEAR? convolution::solveTwoDimensionalLinearConvolution(dx, dh, convolution::PHYSICAL)
                        : convolution::solveTwoDimensionalCircularConvolution(dx, dh, convolution::PHYSICAL);
            } else {
                dy = task == DLINEAR? convolution::solveTwoDimensionalLinearConvolution(dx, dh, convolution::ALGEBRAICAL)
                                    : convolution::solveTwoDimensionalCircularConvolution(dx, dh, convolution::ALGEBRAICAL);
            }
            std::cout<<"{y(m,n)} = "<<std::endl;
            Presenter::outputTwoDimensionalVector(dy);
            std::cout<<std::endl;
            break;
        case INTERPOLATION:
        case THINNING:
            std::map<int, int> sizesMap = {
                    {6,2},
                    {8,2},
                    {10,2},
                    {12,4}
            };
            std::vector<int> sizes = {6,8,10,12};
            int idx = rand()%sizes.size();
            x = generator::generateVector(task == INTERPOLATION ? rand()%4 + 3 : sizes.at(idx));
            //x = {1,2,7,4};
            //std::vector<double> _x = {0, 5, 2, 3, 1, 4, 5, 6};
            std::cout<<"{x(i)} = ";
            Presenter::outputVector(x);
            int m = task == INTERPOLATION ? rand()%2 + 2 : sizesMap.at(sizes.at(idx));
            std::cout<<"m = " << m << std::endl;
            std::cin>>c;
            Presenter::outputVector(task == INTERPOLATION ? convolution::interpolate(x, m) :
                                    convolution::thin(x, m));
            std::cout<<std::endl;
            break;
    }
}

#endif //CONVOLUTION_RESOLVER_H
