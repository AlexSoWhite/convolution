cmake_minimum_required(VERSION 3.21)
project(convolution)

set(CMAKE_CXX_STANDARD 14)

add_executable(convolution main.cpp Methods.h Presenter.h Generator.h Resolver.h test.h)
