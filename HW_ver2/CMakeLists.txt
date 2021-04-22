cmake_minimum_required(VERSION 3.17)
project(HW_ver2)

set(CMAKE_CXX_STANDARD 17)

add_executable(HW_ver2 main.cpp sources/BasicStorage.cpp include/BasicStorage.hpp sources/ShoesStorage.cpp include/ShoesStorage.hpp sources/ClothesStorage.cpp include/ClothesStorage.hpp sources/DB.cpp include/DB.hpp)