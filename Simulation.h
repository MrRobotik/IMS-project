#ifndef SIMULATION_H
#define SIMULATION_H

#include "Plantation.h"
#include "RainforestPatch.h"
#include "ProcessableWood.h"


class Simulation
{
public:
    /**
     * Constructor.
     * Parameters *_wood_waste are estimated percentage of wood that is used for energy (charcoal),
     * paper, left to rot or burn within first 10 years and thus its carbon is released back into atmosphere.
     *
     * @param deforest_limit maximum area to deforest
     * @param rotation_time plantations rotation time after which palms are cut down and replanted
     * @param rainforest_wood_waste waste of wood from rainforest
     * @param palm_wood_waste waste of wood from palm plantation
     */
    Simulation(size_t deforest_limit, unsigned rotation_time,
               double rainforest_wood_waste, double palm_wood_waste);

    /**
     * Run the simulation.
     * @param duration simulation time in years
     */
    void run(size_t duration);

private:
    /// Exponential distribution of life expectancy of the processable wood.
    std::exponential_distribution<double> wle_distr;

    /// Maximum deforested area.
    const size_t DEFOREST_LIMIT;

private:
    /// Curent time position of the simulation (years).
    size_t t = 0;

    /// Accumulator for forest transformation emissions.
    double ft_emissions = 0.;

    /// Accumulator for processable wood waste emissions.
    double pww_emissions = 0.;

    /// Total area of deforested rainforest.
    size_t total_deforested_area = 0;

private:
    /// Waiting for enough deforested area.
    Plantation next_plantation;

    /// Active plantations.
    std::vector<Plantation> plantations;

    /// AG processable wood biomass.
    ProcessableWood wood_storage;

private:
    /**
     * Simulate the next simulation time step (year).
     */
    void nextstep();
};

#endif // SIMULATION_H
