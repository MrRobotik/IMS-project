cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "-Wall")

set(
 SOURCES
 main.cpp
 Simulation.cpp
 RandomGenerator.cpp
 RainforestPatch.cpp
 PlantationPatch.cpp
 Plantation.cpp
)

project(ims-simul)
add_executable(${PROJECT_NAME} ${SOURCES})


