#include <iostream>
#include <fstream>
#include <string>
#include <getopt.h>

#include "Simulation.h"

#define HELP \
"Simulation of rainforest tranformation to oil palm plantations.\n" \
"Usage: ims-simul -f <config-file> -d <duration-in-years> -o <CSV-output-file>\n\n" \
"Order of params in the config-file:\n" \
"1. deforest-per-year\n" \
"2. deforest-limit\n" \
"3. plantation-size\n" \
"4. rotation-time\n" \
"5. replant-per-year\n" \
"6. rainforest-wood-waste\n" \
"7. palm-wood-waste\n\n" \
"Output CSV format:\n" \
"[deforestation emissions], [woodwaste emissions], [total harvest], [total NEP], [total C stocks]"

#define is_probability(p) (p >= 0. && p <= 1.)


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

    size_t deforest_per_year;
    size_t deforest_limit;
    size_t plantation_size;
    unsigned rotation_time;
    size_t replant_per_year;
    double rainforest_wood_waste;
    double palm_wood_waste;

    // Read params from the configuration file..
    std::fstream file(params, std::ios_base::in);
    file >> deforest_per_year;
    file >> deforest_limit;
    file >> plantation_size;
    file >> rotation_time;
    file >> replant_per_year;
    file >> rainforest_wood_waste;
    file >> palm_wood_waste;
    file.close();

    // Check if params are valid.
    if (! deforest_per_year || ! deforest_limit || ! plantation_size || ! rotation_time || ! replant_per_year ||
        ! is_probability(rainforest_wood_waste) || ! is_probability(palm_wood_waste))
    {
        std::cerr << "Invalid config-file" << std::endl;
        return 1;
    }

    // Initialize simulation.
    Simulation simulation(deforest_per_year,
                          deforest_limit,
                          plantation_size,
                          rotation_time,
                          replant_per_year,
                          rainforest_wood_waste,
                          palm_wood_waste);
    // Set CSV output.
    simulation.set_output(output);

    // Run the simulation.
    simulation.run(duration);
    return 0;
}
