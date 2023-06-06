cmake_minimum_required(VERSION 3.5)

project(FlappyBirdSFMLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

add_executable(FlappyBirdSFMLProject main.cpp)
file (COPY DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(FlappyBirdSFMLProject sfml-system sfml-window sfml-graphics sfml-audio)

install(TARGETS FlappyBirdSFMLProject
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
