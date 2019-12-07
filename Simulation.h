#ifndef SIMULATION_H
#define SIMULATION_H

#include "Plantation.h"
#include "RainforestPatch.h"


class Simulation
{
public:
    /**
     * @param rotation_time plantages rotation time after which palms are cut down and replanted
     * @param wood_waste estimated percentage of wood that is used for energy,
     * paper or left to rot within first 15 years and thus its carbon is released back to atmosphere
     */
    Simulation(int rotation_time, double wood_waste);

    /**
     * Run the simulation.
     * @param duration simulation time in years
     */
    void run(size_t duration);

private:
    /// Lambda for exponential distribution of life expectancy of the extracted wood.
    double WLE;

private:
    /// Waiting for enough deforested area.
    Plantation next_plantation;

    /// Already working plantations.
    std::vector<Plantation> plantations;

    /// Above ground wood biomass extracted from deforestation.
    std::vector<Patch::ExtractedWood> wood;
};

#endif // SIMULATION_H
