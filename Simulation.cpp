#include "Simulation.h"
#include <assert.h>


Simulation::Simulation(int rotation_time, double wood_waste) :
    ft_emissions(0.), pww_emissions(0.)
{
    assert(rotation_time >= 0 && rotation_time <= 25);
    assert(wood_waste >= 0.0 && wood_waste <= 1.0);

    Plantation::ROTATION_TIME = rotation_time;

    // Distribution function equals wood_waste at 15 years.
    double lambda = -log(1. - wood_waste)/15.;
    wle_distr = std::exponential_distribution<double>(lambda);

    // FIXME: randomize PLANTATION size from mean and stddev
    next_plantation = Plantation(50);
}


void Simulation::run(size_t duration)
{
    auto &rg = RandomGenerator::get();

    for (size_t t = 0; t < duration; t++)
    {
        // Simulate next year for each plantation.
        for (auto &pl : plantations) {
            pl.proceed();
        }

        // Simulate next year for the processable wood biomass.
        pw_timer_next();

        // FIXME: randomize DEFORESTED AREA per year
        size_t deforested_area = 10;

        for (size_t i = 0; i < deforested_area; i++)
        {
            // Generate rainforest patch to be transformed.
            RainforestPatch forest_patch;

            // Simulate fate of processable wood.
            Patch::ProcessableWood wood;
            wood.biomass = forest_patch.get_wood(RainforestPatch::LITTER_RATIO);
            wood.life_expectancy = int(std::round(wle_distr(rg)));

            if (wood.life_expectancy == 0) {
                pww_emissions += wood.biomass;
            }
            else {
                proc_wood.push_back(wood);
            }

            // Generate new plantation patch.
            PlantationPatch plantation_patch;

            // Add carbon from litter burn/rot and SOC looses to accumulator.
            double litter = forest_patch.get_litter(RainforestPatch::LITTER_RATIO);
            double soc_diff = forest_patch.get_soc() - plantation_patch.get_soc();
            ft_emissions += litter + soc_diff;

            next_plantation.add_patch(plantation_patch);
            if (next_plantation.is_ready())
            {
                // Begin the rotation cycle.
                plantations.push_back(std::move(next_plantation));
                next_plantation = Plantation(50);
            }
        }
    }
}


void Simulation::pw_timer_next()
{
    size_t release_cnt = 0;
    for (auto it = proc_wood.begin(); it != proc_wood.end(); it++)
    {
        if (-- it->life_expectancy == 0)
        {
            // Release carbon back to the atmosphere.
            pww_emissions += it->biomass;

            // Just swap with the back so we don't have to copy all the items in the way.
            std::swap(*it, proc_wood.back());
            release_cnt++;
        }
    }
    // Shrink.
    proc_wood.resize(proc_wood.size() - release_cnt);
}
