cmake_minimum_required(VERSION 3.26)
project(finite_homologies)

set(CMAKE_CXX_STANDARD 20)

set(EIGEN_ROOT_DIR "/usr/local/include/eigen3/")

include_directories(
        ${EIGEN_ROOT_DIR}
)

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
        tests/test_poset.h
        chaincomplex.cpp
        chaincomplex.h
        tests/test_chaincomplex.cpp
        tests/test_chaincomplex.h
        tests/test_allsubsets.cpp
        tests/test_allsubsets.h)
