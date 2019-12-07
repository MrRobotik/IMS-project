#include "Simulation.h"
#include <assert.h>


Simulation::Simulation(int rotation_time, double wood_waste)
{
    assert(rotation_time >= 0 && rotation_time <= 25);
    assert(wood_waste >= 0.0 && wood_waste <= 1.0);

    Plantation::ROTATION_TIME = rotation_time;
    WLE = -log(1. - wood_waste)/15.; // Distribution function equals wood_waste at 15 years.

    // FIXME: randomize PLANTATION size from mean and stddev
    next_plantation = Plantation(50);
}


void Simulation::run(size_t duration)
{
    for (size_t t = 0; t < duration; t++)
    {

        // FIXME: randomize DEFORESTED AREA per year
        size_t deforested_area = 10;

        for (size_t i = 0; i < deforested_area; i++)
        {
            RainforestPatch dp; // Generate deforested patch.
            double wood = dp.get_wood(RainforestPatch::LITTER_RATIO);


            // Append patches to the plantation.
            next_plantation.add_patch(PlantationPatch());

            if (next_plantation.is_ready())
            {
                // Begin the rotation cycle.
                plantations.push_back(std::move(next_plantation));
                next_plantation = Plantation(50);
            }
        }

    }
}
