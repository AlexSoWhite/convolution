//
// Created by alex on 06.12.2021.
//

#ifndef CONVOLUTION_METHODS_H
#define CONVOLUTION_METHODS_H


#include <utility>
#include <vector>
#include <exception>
#include <string>
#include <functional>
#include "Presenter.h"
#include <cmath>
#include <algorithm>

namespace convolution {

    enum system {
        PHYSICAL,
        ALGEBRAICAL
    };

    template<typename T>
    void reverse(std::vector<T> & vec) {
        for (int i = 0; i < vec.size()/2; i++) {
            std::swap(vec[i], vec[vec.size()-1-i]);
        }
    }

    uint getIndex(uint _size, int _i) {
        if (_i >= 0) {
            return _i;
        } else {
            return _size + _i;
        }
    }

    std::vector<int> solveLinearConvolution(
        const std::vector<int>& x,
        const std::vector<int>& h
    ) {
        if ((x.empty()) && (h.empty())) {
            return {};
        }

        std::vector<int> a;
        std::vector<int> b;
        if (x.size() < h.size()) {
            a = x;
            b = h;
        } else {
            a = h;
            b = x;
        }

        std::vector<int> y(a.size() + b.size() - 1, 0);
        for (size_t k = 0; k < a.size(); k++) {
            for (size_t l = 0; l < b.size(); l++) {
                y[l + k] += a[k] * b[l];
            }
        }
        return y;
    }

    std::vector<int> solveCircularConvolution(
        const std::vector<int>& x,
        const std::vector<int>& h
    ) {
        std::vector<int> y(x.size(), 0);
        for (size_t i = 0; i < x.size(); i++) {
            for (size_t k = 0; k < x.size(); k++) {
                y[i] += x[k] * h[(i-k)%x.size()];
            }
        }
        return y;
    }

    std::vector<std::vector<int>> solveTwoDimensionalCircularConvolution(
        const std::vector<std::vector<int>>& x,
        const std::vector<std::vector<int>>& h,
        system s
    ) {
        uint M = x.size();
        uint N = x[0].size();
        std::vector<std::vector<int>> y(M, std::vector<int>(N, 0));
        for (int m = 0; m < M; m++) {
            for (int n = 0; n < N; n++) {
                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        y[m][n] += x[i][j] * h[getIndex(h.size(), m-i)][getIndex(h[0].size(),n-j)];
                    }
                }
            }
        }
        if (s == PHYSICAL) {
            reverse(y);
        }
        return y;
    }

    std::vector<std::vector<int>> solveTwoDimensionalLinearConvolution(
            const std::vector<std::vector<int>>& x,
            const std::vector<std::vector<int>>& h,
            system s
    ) {
        uint M = x.size() + h.size() - 1;
        uint N = x[0].size() + h[0].size() - 1;
        std::vector<std::vector<int>> _x(M, std::vector<int>(N, 0));
        std::vector<std::vector<int>> _h(M, std::vector<int>(N, 0));

        for(int i = 0; i < x.size(); i++) {
            for (int j = 0; j < x[0].size(); j ++) {
                _x[i][j] = x[i][j];
            }
        }

        for(int i = 0; i < h.size(); i++) {
            for (int j = 0; j < h[0].size(); j ++) {
                _h[i][j] = h[i][j];
            }
        }

        if (s == PHYSICAL) {
            reverse(_x);
            reverse(_h);
        }

        std::cout << "after filling with zeros: " <<std::endl;
        std::cout << "{x(i,j)} = " << std::endl;
        Presenter::outputTwoDimensionalVector(_x);
        std::cout<<std::endl;
        std::cout << "{h(i,j)} = " << std::endl;
        Presenter::outputTwoDimensionalVector(_h);
        std::cout<<std::endl;

        std::vector<std::vector<int>> y(M, std::vector<int>(N,0));
        y = solveTwoDimensionalCircularConvolution(
                _x,
                _h,
                s
        );
        reverse(y);

        return y;
    }

    using namespace std;

    template<typename T>
    vector<double> dph(const vector<T> & input) {
        uint sz = input.size();
        vector<double> result;
        result.reserve(sz);
        for (uint k = 0; k < sz; k++) {
            double locsum = 0;
            for (uint i = 0; i < sz; i++) {
                locsum += (
                        cos(2*M_PI*i*k/sz)+
                        sin(2*M_PI*i*k/sz)
                ) * (input.at(i));
            }
            result.emplace_back(locsum);
        }
        return result;
    }

    template<typename T>
    vector<double> interpolate(const std::vector<T> & x, int m) {
        auto H = dph(x);
        std::cout << "1. {H(I)} = ";
        Presenter::outputVector(H);
        uint N = x.size() * m;
        std::vector<double> Hn(N);
        Hn[0] = H[0] * m;
        for (int i = 1; i <= H.size()/2; i++) {
            if (i < H.size()/2 || H.size()%2 != 0) {
                Hn[i] = H[i] * m;
                Hn[N-i] = H[H.size()-i] * m;
            } else {
                Hn[i] = H[i] * m / 2;
                Hn[N-i] = H[H.size()-i] * m /2;
            }
        }
        std::cout << "2. {Hn(i)} = ";
        Presenter::outputVector(Hn);
        auto hn = dph(Hn);
        for_each(hn.begin(), hn.end(), [N](double& a){ a = a / N;});
        std::cout<< "3. {hn(i)} = ";
        return hn;
    }

    template<typename T>
    vector<double> thin(const std::vector<T> & x, int m) {
        auto H = dph(x);
        std::cout << "1. {H(I)} = ";
        Presenter::outputVector(H);
        uint N = x.size() / m;
        std::vector<double> Hn(N);
        Hn[0] = H[0] / m;
        for (int i = 1; i <= Hn.size()/2; i++) {
            if (i < Hn.size()/2 || Hn.size()%2 != 0) {
                Hn[i] = H[i] / m;
                Hn[N-i] = H[H.size()-i] / m;
            } else {
                Hn[i] = (H[i] + H[H.size()-i] ) / m;
            }
        }
        std::cout << "2. {Hn(i)} = ";
        Presenter::outputVector(Hn);
        auto hn = dph(Hn);
        for_each(hn.begin(), hn.end(), [N](double& a){ a = a / N;});
        std::cout<< "3. {hn(i)} = ";
        return hn;
    }

}


#endif //CONVOLUTION_METHODS_H
