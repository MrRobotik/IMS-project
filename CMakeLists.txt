cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "-Wall")

set(
 SOURCES
 src/main.cpp
 src/Simulation.cpp
 src/RandomGenerator.cpp
 src/Patch.cpp
 src/RainforestPatch.cpp
 src/PlantationPatch.cpp
 src/Plantation.cpp
 src/WoodStorage.cpp
)

project(ims-simul)
add_executable(${PROJECT_NAME} ${SOURCES})


