#ifndef PLANTATIONPATCH_H
#define PLANTATIONPATCH_H

#include "Patch.h"
#include "RandomGenerator.h"


class PlantationPatch : public Patch
{
public:
    PlantationPatch();

    /**
     * Simulate primary production and fruit harvest in the next year.
     *
     * @param age of the palms after time step
     * @return relation (NEP, NPP yield from the harvest)
     */
    std::pair<double, double> nextstep(int age);

public:
    /// Exponential distribution of life expectancy of the processible wood.
    static std::exponential_distribution<double> wle_distr;

public:
    /// Unprocessible biomass.
    static constexpr double LITTER_RATIO = 0.488095;

private:
    /// Net Primary Product of mature palms.
    static constexpr double
    NPP_mean = 17.1, NPP_sigma = 0.9;

    /// Soil heterotrophic respiration.
    static constexpr double
    Rh_mean = 4.2, Rh_sigma = 0.3;

    /// Net Primary Product maximum yield via fruit harvest.
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
