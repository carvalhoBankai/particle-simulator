cmake_minimum_required(VERSION 3.20)

project(sfml-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS Graphics Window System REQUIRED)

add_executable(particle-simulator
    src/main.cpp
    src/render.cpp
    src/vec2.cpp
    src/particle.cpp
)

target_link_libraries(particle-simulator
    PRIVATE
        SFML::Graphics
)

target_include_directories(particle-simulator
    PRIVATE
        include
)