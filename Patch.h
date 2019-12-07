#ifndef PATCH_H
#define PATCH_H

#include <assert.h>


class Patch
{
public:
    Patch();

    /**
     * Return carbon in processable biomass.
     */
    double get_wood(double litter_ratio);

    /**
     * Return carbon in litter.
     */
    double get_litter(double litter_ratio);

    /**
     * Return carbon in soil.
     */
    double get_soc();

public:
    struct ExtractedWood {
        float biomass;       //< Carbon stocks.
        int life_expectancy; //< After this time, wood will destructed.
    };

public:
    static constexpr double AREA = 100; //< Area of discrete patch in hectars.

protected:
    struct {
        float ag_biomass;   //< Above ground living biomass.
        float bg_biomass;   //< Below ground living biomass.
        float dead_biomass; //< Dead biomass.
        float soc;          //< Soil organic carbon.

    } carbon_stocks; //< Carbon stored by the ecosystem patch.
};


inline Patch::Patch()
{ carbon_stocks = {}; }


inline double Patch::get_wood(double litter_ratio)
{ return double(carbon_stocks.ag_biomass) * litter_ratio; }


inline double Patch::get_litter(double litter_ratio)
{
    return
    double(carbon_stocks.ag_biomass) * (1.0 - litter_ratio)
    + carbon_stocks.bg_biomass
    + carbon_stocks.dead_biomass;
}


inline double Patch::get_soc()
{ return double(carbon_stocks.soc); }


#endif // PATCH_H
