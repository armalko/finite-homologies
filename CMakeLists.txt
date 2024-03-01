cmake_minimum_required(VERSION 3.26)
project(finite_homologies)

set(CMAKE_CXX_STANDARD 20)

add_executable(finite_homologies main.cpp
        poset.cpp
        poset.h
        vertex.h
        edge.h
        matrix.cpp
        matrix.h
        scomplex.cpp
        scomplex.h
        tests/test_maxchains.cpp
        tests/test_maxchains.h
        tests/test_poset.cpp
        tests/test_poset.h)
