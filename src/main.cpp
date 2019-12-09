#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>

#include "Simulation.h"

#define HELP \
"Simulation of rainforest tranformation to oil palm plantations.\n" \
"Usage: ims-simul -f <config-file> -d <duration-in-years> [-o <CSV-output-file>]\n\n" \
"Order of params in the config-file:\n" \
"1. size of the discrete area unit (hectars)\n" \
"2. deforestation rate (discrete area units per year)\n" \
"3. deforestation limit (discrete area units)\n" \
"4. palm plant. unit size (discrete area units)\n" \
"5. palm plant. rotation cycle (years)\n" \
"6. palm plant. replanting limit (discrete area units per year)\n" \
"7. wood waste from rainforest (ratio between 0.0 and 1.0)\n" \
"8. wood waste from palm plant (ratio between 0.0 and 1.0)"


int main(int argc, char **argv)
{
    const char *params = nullptr;
    const char *output = nullptr;
    size_t duration = 0;

    while (true)
    {
        switch (getopt(argc, argv, "f:d:o:"))
        {
        case 'f':
            params = optarg;
            continue;
        case 'd':
            duration = std::strtoull(optarg, nullptr, 10);
            continue;
        case 'o':
            output = optarg;
            continue;
        case '?':
            std::cout << HELP << std::endl;
            return 1;
        default:;
        }
        break;
    }

    if (! params || ! duration) {
        std::cout << HELP << std::endl;
        return 1;
    }

    double discrete_area;
    size_t deforest_per_year;
    size_t deforest_limit;
    size_t plantation_size;
    unsigned rotation_time;
    size_t replant_limit_per_year;
    double rainforest_wood_waste;
    double palm_wood_waste;

    // Read params from the configuration file..
    std::fstream file(params, std::ios_base::in);
    if (! file.is_open()) {
        std::cerr << "couldn't open config-file" << std::endl;
        return 1;
    }

    file >> discrete_area;
    file >> deforest_per_year;
    file >> deforest_limit;
    file >> plantation_size;
    file >> rotation_time;
    file >> replant_limit_per_year;
    file >> rainforest_wood_waste;
    file >> palm_wood_waste;
    file.close();

    try {
        // Initialize simulation.
        Simulation simulation(discrete_area,
                              deforest_per_year,
                              deforest_limit,
                              plantation_size,
                              rotation_time,
                              replant_limit_per_year,
                              rainforest_wood_waste,
                              palm_wood_waste);
        // Set CSV output.
        simulation.set_output(output);

        // Run the simulation.
        simulation.run(duration);

    }
    catch (const std::invalid_argument &e) {
        std::cerr << "config-file: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
