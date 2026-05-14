cmake_minimum_required(VERSION 3.20)

project(GoofyGoober)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(SFML COMPONENTS Graphics Window System REQUIRED)

add_executable(GoofyGoober
    src/main.cpp
    src/QuestionManager.cpp
)

target_link_libraries(GoofyGoober
    SFML::Graphics
    SFML::Window
    SFML::System
)