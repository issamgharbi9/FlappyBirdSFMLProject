cmake_minimum_required(VERSION 3.5)

project(FlappyBirdSFMLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FlappyBirdSFMLProject main.cpp)

install(TARGETS FlappyBirdSFMLProject
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
