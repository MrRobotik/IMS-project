#ifndef PLANTATIONPATCH_H
#define PLANTATIONPATCH_H

#include "Patch.h"
#include "RandomGenerator.h"


class PlantationPatch : public Patch
{
public:
    PlantationPatch();

    /**
     * Proceed to the next time step (year)
     * and simulate primary production and fruit harvest.
     *
     * @param age of the palms after time step
     * @return relation (NEP, NPP yield from the harvest)
     */
    std::pair<double, double> proceed(int age);

private:
    /// Net Primary Product.
    static constexpr double
    NPP_mean = 17.1, NPP_sigma = 0.9;

    /// Soil heterotrophic respiration.
    static constexpr double
    Rh_mean = 4.2, Rh_sigma = 0.3;

    /// Net Primary Product maximum fruit harvest yield.
    static constexpr double
    NPP_yield_mean = 10.0, NPP_yield_sigma = 0.8;

    /// Soil organic carbon.
    static constexpr double
    SOC_mean = 90.1, SOC_sigma = 6.648;

    /// Normal distributions.
    static std::normal_distribution<double>
    NPP_distr, Rh_distr, NPP_yield_distr, SOC_distr;
};

#endif // PLANTATIONPATCH_H
