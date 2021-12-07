//
// Created by alex on 07.12.2021.
//

#ifndef CONVOLUTION_GENERATOR_H
#define CONVOLUTION_GENERATOR_H


#include <vector>
#include <cstdlib>

namespace generator {
    std::vector<int> generateVector(int n) {
        std::vector<int> r(n);
        for (int i = 0; i < n; i++) {
            r[i] = rand()%17 - 7;
        }
        return r;
    }

    std::vector<std::vector<int>> generateDoubleVector(int m, int n) {
        std::vector<std::vector<int>> r(m);
        for (int i = 0; i < m; i ++) {
            r[i] = generateVector(n);
        }
        return r;
    }
}

#endif //CONVOLUTION_GENERATOR_H
