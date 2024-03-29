﻿#include "RainforestPatch.h"


std::normal_distribution<double>
RainforestPatch::AG_distr(AG_mean, AG_sigma),
RainforestPatch::BG_distr(BG_mean, BG_sigma),
RainforestPatch::D_distr(D_mean, D_mean),
RainforestPatch::SOC_distr(SOC_mean, SOC_sigma);


std::exponential_distribution<double>
RainforestPatch::wle_distr;


RainforestPatch::RainforestPatch() : Patch()
{
    // Generate carbon stocks according to measured distributions.
    auto &rg = RandomGenerator::get();
    carbon_stocks.ag_biomass = AG_distr(rg)*AREA;
    carbon_stocks.bg_biomass = BG_distr(rg)*AREA;
    carbon_stocks.dead_biomass = D_distr(rg)*AREA;
    carbon_stocks.soc = SOC_distr(rg)*AREA;
}
