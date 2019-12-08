#ifndef PROCESSABLEWOOD_H
#define PROCESSABLEWOOD_H

#include <vector>


class ProcessableWood
{
public:
    struct unit {
        float biomass;       //< Carbon stocks.
        int life_expectancy; //< Timer.
    };

public:
    /**
     * Decrement timer for each processable wood unit in wood_storage
     * and release those which timer has reached zero.
     */
    double nextstep();

    /**
     * Add wood unit to the storage.
     */
    void add(const ProcessableWood::unit &wood);

private:
    std::vector<ProcessableWood::unit> storage;
};


inline void ProcessableWood::add(const ProcessableWood::unit &wood)
{ storage.push_back(wood); }


#endif // PROCESSABLEWOOD_H
