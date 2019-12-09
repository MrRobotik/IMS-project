#include "PlantationPatch.h"
#include <assert.h>


std::normal_distribution<double>
PlantationPatch::NPP_distr(NPP_mean, NPP_sigma),
PlantationPatch::Rh_distr(Rh_mean, Rh_sigma),
PlantationPatch::NPP_yield_distr(NPP_yield_mean, NPP_yield_sigma),
PlantationPatch::SOC_distr(SOC_mean, SOC_sigma);


std::exponential_distribution<double>
PlantationPatch::wle_distr;


PlantationPatch::PlantationPatch() : Patch()
{
    carbon_stocks.soc = SOC_distr(RandomGenerator::get())*AREA;
}


std::pair<double, double>
PlantationPatch::nextstep(int age)
{
    assert(age > 0 && age <= 25); // No data available.

    auto &rg = RandomGenerator::get(); // Random generator.

    double npp = NPP_distr(rg)*AREA;
    double rh  = Rh_distr(rg)*AREA;

    // Scaling function of age for NPP of palm trees.
    npp *= 1.3412545110882410e+000
         - 1.6244119250121147e-002*age
         - 3.9973678914401005e-004*age*age;

    // Compute Net Ecosystem Product.
    double nep = npp - rh;

    double npp_yield = 0.;
    if (age >= 3)
    {
        // Harvest the fruits.
        npp_yield = NPP_yield_distr(rg)*AREA;

        if (age <= 8) {
            npp_yield *= 0.2*age - 0.6; // Yield increasing.
        }
        else if (age >= 20) {
            npp_yield *= -0.011*age + 1.22; // Yield decreasing.
        }

        // Substract the harvested carbon.
        nep -= npp_yield;
    }

    // Approximate ratios between living AG, living BG and dead biomass.
    carbon_stocks.ag_biomass   += 0.75398634*nep;
    carbon_stocks.bg_biomass   += 0.17539863*nep;
    carbon_stocks.dead_biomass += 0.07061503*nep;

    return {nep, npp_yield};
}
