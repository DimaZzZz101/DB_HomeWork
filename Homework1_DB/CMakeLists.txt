cmake_minimum_required(VERSION 3.17)
project(Homework1_DB)

set(CMAKE_CXX_STANDARD 17)

add_executable(Homework1_DB main.cpp sources/BasicStorage.cpp include/BasicStorage.hpp sources/DB.cpp include/DB.hpp sources/ClothesStorage.cpp include/ClothesStorage.hpp sources/ShoesStorage.cpp include/ShoesStorage.hpp)