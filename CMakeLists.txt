cmake_minimum_required(VERSION 2.4)
project(DoublePendulum)
set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(PROJECT_CODE
    src/color.cpp include/color.hpp
    src/doublePendulum.cpp include/doublePendulum.hpp
    src/image.cpp include/image.hpp
    src/pendulum.cpp include/pendulum.hpp
    include/initialConditions.hpp
    include/pendulumParams.hpp
    include/point.hpp
    src/main.cpp)

include_directories(include)

add_executable(app ${PROJECT_CODE})