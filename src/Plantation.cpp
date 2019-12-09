#include "Plantation.h"
#include "WoodStorage.h"


unsigned Plantation::ROTATION_TIME;
unsigned Plantation::replant_area_reservoir;


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
    if (size < patches.size())
        goto keep_replanting;
    // else
    age++;
    for (auto &p : patches) {
        auto res = p.nextstep(age);
        total_nep += res.first;
        total_harvest += res.second;
    }

    if (age == ROTATION_TIME) {
        // Replant the trees.
        size = 0; age = 0; i = 0;
    }
    return;

    keep_replanting:
    {
        // Replant as much as possible this year.
        size_t need = patches.size() - size;
        size_t replanted = (need < replant_area_reservoir) ? need : replant_area_reservoir;
        replant_area_reservoir -= replanted;
        size += replanted;

        for (; i < size; i++)
        {
            // Simulate life of processible palm wood after being cut.
            WoodStorage::unit wood;
            wood.biomass = patches[i].get_wood(PlantationPatch::LITTER_RATIO);
            wood.life_expectancy = std::round(PlantationPatch::wle_distr(RandomGenerator::get()));
            WoodStorage::get().add(wood);

            // Substract the litter.
            total_nep -= patches[i].get_litter(PlantationPatch::LITTER_RATIO);

            // Clear the patch.
            patches[i].clear_biomass();
        }
    }
}
