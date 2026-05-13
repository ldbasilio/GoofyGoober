cmake_minimum_required(VERSION 3.20)

project(GoofyGoober)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(GoofyGoober
    src/main.cpp
    src/QuestionManager.cpp
)