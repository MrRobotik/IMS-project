#ifndef SIMULATION_H
#define SIMULATION_H

#include "Plantation.h"
#include "RainforestPatch.h"


class Simulation
{
public:
    /**
     * @param deforest_limit
     * @param rotation_time plantages rotation time after which palms are cut down and replanted
     * @param wood_waste estimated percentage of wood that is used for energy,
     * paper or left to rot within first 15 years and thus its carbon is released back to atmosphere
     */
    Simulation(size_t deforest_limit, int rotation_time, double wood_waste);

    /**
     * Run the simulation.
     * @param duration simulation time in years
     */
    void run(size_t duration);

    /**
     * Get statistics.
     */
    void stats();

private:
    /// Exponential distribution of life expectancy of the extracted wood.
    std::exponential_distribution<double> wle_distr;

    /// Maximum deforested area.
    const size_t DEFOREST_LIMIT;

private:
    /// Accumulator for forest transformation emissions.
    double ft_emissions;

    /// Accumulator for processable wood waste emissions.
    double pww_emissions;

private:
    /// Waiting for enough deforested area.
    Plantation next_plantation;

    /// Already working plantations.
    std::vector<Plantation> plantations;

    /// AG processable wood biomass from deforestation.
    std::vector<Patch::ProcessableWood> proc_wood;

private:
    /**
     * Proceed timer for each processable wood sample
     * and efficiently remove those which timer decreased to zero.
     */
    void pw_timer_next();
};

#endif // SIMULATION_H
