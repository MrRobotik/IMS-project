#include "Simulation.h"
#include <assert.h>
#include <iostream>


Simulation::Simulation(size_t deforest_limit, unsigned rotation_time, double wood_waste)
    :
      DEFOREST_LIMIT(deforest_limit)
{
    assert(rotation_time <= 25);
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
    for (; t < duration; t++) {
        this->nextstep();
    }
}


void Simulation::stats()
{
    std::cout << "FT emissions:\t" << ft_emissions << " Mg C\n";
    std::cout << "PWW emissions:\t" << pww_emissions << " Mg C\n";

    double total_harvest = 0.;
    double total_nep = 0.;
    double c_stocks = 0.;
    size_t patch_cnt = 0;

    for (auto &pl : plantations)
    {
        total_harvest += pl.get_harvest();
        total_nep += pl.get_nep();

        for (auto patch : pl.get_patches()) {
            c_stocks += patch.get_wood(0.) + patch.get_litter(0.);
            patch_cnt++;
        }
    }

    std::cout << "Total NEP:\t\t" << total_nep << " Mg C\n";
    std::cout << "Total harvest:\t" << total_harvest << " Mg C\n";
    std::cout << "C-stocks:\t\t" << c_stocks << "Mg C\n";
    std::cout << "C-stocks PP:\t" << c_stocks/double(patch_cnt) << "Mg C\n";
}


inline void Simulation::nextstep()
{
    auto &rg = RandomGenerator::get();

    // Simulate next year for each plantation.
    for (auto &pl : plantations) {
        pl.nextstep();
    }

    // Simulate next year for the processable wood biomass.
    pw_timer_next();

    // Deforestation limit has been reached.
    if (total_deforested_area >= DEFOREST_LIMIT)
        return;

    size_t deforested_area = 1000;
    total_deforested_area += deforested_area;

    for (size_t i = 0; i < deforested_area; i++)
    {
        // Generate rainforest patch to be transformed.
        RainforestPatch forest_patch;

        // Simulate life of processable wood after being cut.
        Patch::ProcessableWood wood;
        wood.biomass = forest_patch.get_wood(RainforestPatch::LITTER_RATIO);
        wood.life_expectancy = int(std::round(wle_distr(rg)));

        if (wood.life_expectancy == 0) {
            pww_emissions += wood.biomass;
        }
        else {
            wood_storage.push_back(wood);
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


inline void Simulation::pw_timer_next()
{
    size_t release_cnt = 0;
    for (auto it = wood_storage.begin(); it != wood_storage.end(); it++)
    {
        if (-- it->life_expectancy == 0)
        {
            // Release carbon back to the atmosphere.
            pww_emissions += it->biomass;

            // Just swap with the back so we don't have to copy extra items.
            std::swap(*it, wood_storage.back());
            release_cnt++;
        }
    }
    // Shrink.
    wood_storage.resize(wood_storage.size() - release_cnt);
}
