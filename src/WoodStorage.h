#ifndef WOODSTORAGE_H
#define WOODSTORAGE_H

#include <vector>
#include <random>


class WoodStorage
{
public:
    struct unit {
        float biomass;       //< Carbon stocks.
        int life_expectancy; //< Timer.
    };

public:
    /**
     * Get the instance.
     */
    static WoodStorage &get();

    /**
     * Decrement timer for each wood unit in the storage
     * and release those which timer has reached zero.
     */
    void nextstep();

    /**
     * Add wood unit to the storage.
     */
    void add(const WoodStorage::unit &wood);

    /**
     * Get produced emissions.
     */
    double get_emissions();

private:
    WoodStorage() = default;

private:
    /// Unit container.
    std::vector<WoodStorage::unit> storage;

    /// Accumulator for processible wood waste emissions.
    double emissions = 0.;

private:
    static WoodStorage instance;
};


inline WoodStorage &WoodStorage::get()
{ return instance; }


inline void WoodStorage::add(const WoodStorage::unit &wood)
{
    if (wood.life_expectancy == 0)
    { emissions += wood.biomass; return; }
    storage.push_back(wood);
}


inline double WoodStorage::get_emissions()
{ return emissions; }


#endif // WOODSTORAGE_H
