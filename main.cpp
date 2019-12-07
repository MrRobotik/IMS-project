#include <iostream>
#include "Simulation.h"


int main(int argc, const char **argv)
{
    Simulation simulation(10000, 25, 0.9);
    simulation.run(50);
    simulation.stats();

    return 0;
}
