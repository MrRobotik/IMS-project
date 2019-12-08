#ifndef SIMULATION_H
#define SIMULATION_H

#include <fstream>

#include "Plantation.h"
#include "RainforestPatch.h"
#include "WoodStorage.h"


class Simulation
{
public:
    /**
     * Constructor.
     * Parameters *_wood_waste are estimated percentage of wood that is used for energy (charcoal),
     * paper, left to rot or burn within first 10 years and thus its carbon is released back into atmosphere.
     *
     * @param deforest_per_year area deforested per year
     * @param deforest_limit maximum area to deforest
     * @param plantation_size required deforested area for each plantation unit
     * @param rotation_time time after which palms are cut down and replanted
     * @param replant_per_year maximum replanted plantation area per year
     * @param rainforest_wood_waste waste of wood from rainforest
     * @param palm_wood_waste waste of wood from palm plantation
     */
    Simulation(size_t deforest_per_year,
               size_t deforest_limit,
               size_t plantation_size,
               unsigned rotation_time,
               size_t replant_per_year,
               double rainforest_wood_waste,
               double palm_wood_waste);

    /**
     * Set the CSV data output.
     * @param output file
     */
    void set_output(const char *file);

    /**
     * Run the simulation.
     * @param duration simulation time in years
     */
    void run(size_t duration);

private:
    /// Maximum deforested area.
    const size_t DEFOREST_LIMIT;

    /// Number of deforested hectars per year.
    const size_t DEFOREST_PER_YEAR;

    /// Required deforested area for each plantation unit.
    const size_t PLANTATION_SIZE;

private:
    /// Curent time position of the simulation (years).
    size_t t = 0;

    /// Accumulator for forest transformation emissions.
    double ft_emissions = 0.;

    /// Total area of deforested rainforest.
    size_t total_deforested_area = 0;

private:
    /// Waiting for enough deforested area.
    Plantation next_plantation;

    /// Active plantations.
    std::vector<Plantation> plantations;

private:
    /**
     * Simulate the next simulation time step (year).
     */
    void nextstep();

private:
    /**
     * Print next CSV line to output file.
     */
    void print_csvline();

    /**
     * Print total statistics of the simulation to stdout.
     */
    void print_stats();

private:
    std::fstream output;
};

#endif // SIMULATION_H
