#include "Plantation.h"
#include "WoodStorage.h"


unsigned Plantation::ROTATION_TIME;
unsigned Plantation::REPLANT_TIME;


Plantation::Plantation(size_t size) :
    size(size)
{}


Plantation::Plantation(Plantation &&other)
{ *this = std::move(other); }


Plantation &Plantation::operator=(Plantation &&other)
{
    patches = std::move(other.patches);
    size = other.size;
    age = other.age;
    total_nep = other.total_nep;
    total_harvest = other.total_harvest;
    return *this;
}


void Plantation::nextstep()
{
    age++;
    if (age <= 0) return;

    for (auto &p : patches) {
        auto res = p.nextstep(age);
        total_nep += res.first;
        total_harvest += res.second;
    }

    if (age == ROTATION_TIME)
    {
        // Cut and replant the trees.
        for (auto &patch : patches)
        {
            // Simulate life of processible palm wood after being cut.
            WoodStorage::unit wood;
            wood.biomass = patch.get_wood(PlantationPatch::LITTER_RATIO);
            wood.life_expectancy = std::round(PlantationPatch::wle_distr(RandomGenerator::get()));
            WoodStorage::get().add(wood);

            // Substract the litter.
            total_nep -= patch.get_litter(PlantationPatch::LITTER_RATIO);

            // Clear the patch.
            patch.clear_biomass();
        }
        age = 0 - REPLANT_TIME;
    }
}
