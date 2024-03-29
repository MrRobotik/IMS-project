﻿#ifndef PATCH_H
#define PATCH_H

#include <assert.h>


class Patch
{
public:
    Patch();

    /**
     * Clear the biomass, SOC is preserved.
     */
    void clear_biomass();

    /**
     * Return all carbon in biomass.
     */
    double get_biomass();

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
    /// Area of discrete patch in hectars.
    static double AREA;

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


inline void Patch::clear_biomass()
{
    carbon_stocks.ag_biomass   = 0.f;
    carbon_stocks.bg_biomass   = 0.f;
    carbon_stocks.dead_biomass = 0.f;
}


inline double Patch::get_biomass()
{ return carbon_stocks.ag_biomass + carbon_stocks.bg_biomass + carbon_stocks.dead_biomass; }


inline double Patch::get_wood(double litter_ratio)
{ return carbon_stocks.ag_biomass*(1.0 - litter_ratio); }


inline double Patch::get_litter(double litter_ratio)
{ return carbon_stocks.ag_biomass*litter_ratio + carbon_stocks.bg_biomass + carbon_stocks.dead_biomass; }


inline double Patch::get_soc()
{ return carbon_stocks.soc; }


#endif // PATCH_H
