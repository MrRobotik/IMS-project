#include "WoodStorage.h"


WoodStorage WoodStorage::instance;


void WoodStorage::nextstep()
{
    size_t release_cnt = 0;
    for (auto it = storage.begin(); it != storage.end(); it++)
    {
        if (-- it->life_expectancy == 0)
        {
            // Release carbon back to the atmosphere.
            emissions += it->biomass;

            // Just swap with the back so we don't have to copy extra items.
            std::swap(*it, storage.back());
            release_cnt++;
        }
    }
    // Strip the released wood units.
    storage.resize(storage.size() - release_cnt);
}
