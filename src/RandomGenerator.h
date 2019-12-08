#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

typedef std::minstd_rand RG_impl;

class RandomGenerator : public RG_impl
{
public:
    /**
     * Get the instance.
     */
    static RandomGenerator &get();

private:
    RandomGenerator();

private:
    static RandomGenerator instance;
};


inline RandomGenerator &RandomGenerator::get()
{ return instance; }


#endif // RANDOMGENERATOR_H
