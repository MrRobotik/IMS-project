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
    void add_patch(PlantationPatch &&patch);

    /**
     * Tell if plantation is ready to start.
     */
    bool is_ready();

    /**
     * Call proceed for each patch and accumulate the harvest.
     */
    void proceed();

public:
    static int ROTATION_TIME; //< Period of the plantation rotation cycle.

private:
    size_t size;
    std::vector<PlantationPatch> patches;

    int age;
    double total_harvest;
};


inline void Plantation::add_patch(PlantationPatch &&patch)
{ patches.push_back(patch); }


inline bool Plantation::is_ready()
{ return patches.size() == size; }


#endif // PLANTATION_H
