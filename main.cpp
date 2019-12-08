#include <iostream>
#include "Simulation.h"


int main(int argc, const char **argv)
{
    Simulation simulation(10000, 25, 0.80, 0.95);
    simulation.run(100);
    return 0;
}
