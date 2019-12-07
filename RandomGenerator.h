#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

typedef std::minstd_rand RG_impl;

class RandomGenerator : public RG_impl
{
public:
    static RandomGenerator &get()
    { return instance; }

private:
    RandomGenerator();
    ~RandomGenerator() = default;

private:
    static RandomGenerator instance;
};

#endif // RANDOMGENERATOR_H
