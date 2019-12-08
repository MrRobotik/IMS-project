#include "Simulation.h"
#include <assert.h>
#include <iostream>


Simulation::Simulation(size_t deforest_per_year,
                       size_t deforest_limit,
                       size_t plantation_size,
                       unsigned rotation_time,
                       size_t replant_per_year,
                       double rainforest_wood_waste,
                       double palm_wood_waste)
    :
      DEFOREST_PER_YEAR(deforest_per_year),
      DEFOREST_LIMIT(deforest_limit),
      PLANTATION_SIZE(plantation_size)
{
    assert(rotation_time <= 25);
    assert(rainforest_wood_waste >= 0.0 && rainforest_wood_waste <= 1.0);

    // Plantations settings.
    Plantation::ROTATION_TIME = rotation_time;
    Plantation::REPLANT_PER_YEAR = replant_per_year;

    // Prepare wood waste distributions.
    {
        double lambda;

        lambda = -log(1. - rainforest_wood_waste)/10.;
        RainforestPatch::wle_distr = std::exponential_distribution<double>(lambda);

        lambda = -log(1. - palm_wood_waste)/10.;
        PlantationPatch::wle_distr = std::exponential_distribution<double>(lambda);
    }

    // First plantation waiting for enough deforested area.
    next_plantation = Plantation(PLANTATION_SIZE);
}


void Simulation::set_output(const char *file)
{
    if (file) {
        output.open(file, std::ios_base::out);
        output << "year, deforest_emission, woodwaste_emission, palms_harvest, palms_NEP, palms_C_stocks\n";
    }
}


void Simulation::run(size_t duration)
{
    for (; t < duration; t++) {
        this->nextstep();
        this->print_csvline();
    }

    this->print_stats();
}


inline void Simulation::nextstep()
{
    auto &rg = RandomGenerator::get();
    auto &wood_storage = WoodStorage::get();

    // Simulate each plantation.
    for (auto &pl : plantations) {
        pl.nextstep();
    }

    // Simulate wood.
    wood_storage.nextstep();

    // Deforestation limit has been reached.
    if (total_deforested_area == DEFOREST_LIMIT)
        return;

    size_t deforested_area = DEFOREST_PER_YEAR;
    total_deforested_area += deforested_area;

    // Clip.
    if (total_deforested_area > DEFOREST_LIMIT)
        total_deforested_area = DEFOREST_LIMIT;

    // Simulate deforestation.
    for (size_t i = 0; i < deforested_area; i++)
    {
        // Generate rainforest patch to be transformed.
        RainforestPatch forest_patch;

        // Simulate life of processible rainforest wood after being cut.
        WoodStorage::unit wood;
        wood.biomass = forest_patch.get_wood(RainforestPatch::LITTER_RATIO);
        wood.life_expectancy = std::round(RainforestPatch::wle_distr(rg));
        wood_storage.add(wood);

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
            next_plantation = Plantation(PLANTATION_SIZE);
        }
    }
}


inline void Simulation::print_csvline()
{
    if (! output.is_open())
        return;

    double total_harvest = 0.;
    double total_nep = 0.;
    double c_stocks = 0.;

    for (auto &pl : plantations)
    {
        total_harvest += pl.get_harvest();
        total_nep += pl.get_nep();

        for (auto patch : pl.get_patches()) {
            c_stocks += patch.get_wood(0.) + patch.get_litter(0.);
        }
    }

    output << (t+1) << ',';
    output << ft_emissions << ',';
    output << WoodStorage::get().get_emissions() << ',';
    output << total_harvest << ',';
    output << total_nep << ',';
    output << c_stocks << '\n';
}


inline void Simulation::print_stats()
{
    std::cout << "Emissions (Mg C)\n";
    std::cout << "deforestation:\t\t" << ft_emissions << '\n';
    std::cout << "wood waste:\t\t" << WoodStorage::get().get_emissions() << '\n';

    double total_harvest = 0.;
    double total_nep = 0.;
    double c_stocks = 0.;
    size_t patch_cnt = 0;

    for (auto &pl : plantations)
    {
        total_harvest += pl.get_harvest();
        total_nep += pl.get_nep();
        patch_cnt += pl.get_patches().size();

        for (auto patch : pl.get_patches()) {
            c_stocks += patch.get_wood(0.) + patch.get_litter(0.);
        }
    }

    std::cout << "Plantations (Mg C)\n";
    std::cout << "total NEP:\t\t" << total_nep << '\n';
    std::cout << "total harvest:\t\t" << total_harvest << '\n';
    std::cout << "total C-stocks:\t\t" << c_stocks << '\n';
    std::cout << "C-stocks per patch:\t" << c_stocks/double(patch_cnt) << '\n';
}
