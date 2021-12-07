//
// Created by alex on 06.12.2021.
//

#ifndef CONVOLUTION_PRESENTER_H
#define CONVOLUTION_PRESENTER_H


#include <vector>
#include <iostream>

class Presenter {
public:
    template<typename T>
    static void outputVector(const std::vector<T>& _vec) {
        std::cout<<"[ ";
        for (auto _e: _vec) {
            std::cout<<_e<<" ";
        }
        std::cout<<"]"<<std::endl;
    }

    template<typename T>
    static void outputTwoDimensionalVector(const std::vector<std::vector<T>>& _vec) {
        for (const auto & _line: _vec) {
            outputVector(_line);
        }
        std::cout<<std::endl;
    }
};

#endif //CONVOLUTION_PRESENTER_H
