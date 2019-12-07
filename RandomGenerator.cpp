#include "RandomGenerator.h"

static std::random_device rdev; //< Platform specific random device.

RandomGenerator::RandomGenerator() :
    RG_impl(rdev())
{}

RandomGenerator RandomGenerator::instance;
