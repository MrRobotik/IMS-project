#ifndef RAINFORESTPATCH_H
#define RAINFORESTPATCH_H

#include "Patch.h"
#include "RandomGenerator.h"


class RainforestPatch : public Patch
{
public:
    RainforestPatch();

public:
    /// Exponential distribution of life expectancy of the processible wood.
    static std::exponential_distribution<double> wle_distr;

public:
    /// Unprocessible biomass.
    static constexpr double LITTER_RATIO = 0.506494;

private:
    /// Above ground living biomass.
    static constexpr double
    AG_mean = 159.7, AG_sigma = 11.2;

    /// Below ground living biomass.
    static constexpr double
    BG_mean = 33.8, BG_sigma = 1.4;

    /// Dead biomass.
    static constexpr double
    D_mean = 13, D_sigma = 1.45;

    /// Soil organic carbon.
    static constexpr double
    SOC_mean = 111.9, SOC_sigma = 5.14781;

    /// Normal distributions.
    static std::normal_distribution<double>
    AG_distr, BG_distr, D_distr, SOC_distr;
};

#endif // RAINFORESTPATCH_H
