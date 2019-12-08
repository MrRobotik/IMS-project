#ifndef PLANTATION_H
#define PLANTATION_H

#include "PlantationPatch.h"
#include <vector>


class Plantation
{
public:
    Plantation() = default;

    Plantation(size_t size);

    Plantation(Plantation &&other);

    Plantation& operator=(Plantation &&other);

    /**
     * Add new patch of transformed rainforest.
     */
    void add_patch(const PlantationPatch &patch);

    /**
     * Tell if plantation is ready to start.
     */
    bool is_ready();

    /**
     * Call nextstep() for each patch and accumulate the harvest.
     */
    void nextstep();

public:
    /**
     * Get total NPP harvest.
     */
    double get_harvest();

    /**
     * Get total NEP.
     */
    double get_nep();

    /**
     * Get patches vector reference.
     */
    const std::vector<PlantationPatch> &get_patches();

public:
    /// Period of the plantation rotation cycle.
    static unsigned ROTATION_TIME;

private:
    size_t size;
    std::vector<PlantationPatch> patches;

    int age;
    double total_nep;
    double total_harvest;
};


inline void Plantation::add_patch(const PlantationPatch &patch)
{ patches.push_back(patch); }


inline bool Plantation::is_ready()
{ return patches.size() == size; }


inline double Plantation::get_harvest()
{ return total_harvest; }


inline double Plantation::get_nep()
{ return total_nep; }


inline const std::vector<PlantationPatch> &Plantation::get_patches()
{ return patches; }


#endif // PLANTATION_H
