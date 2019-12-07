#include "Plantation.h"


int Plantation::ROTATION_TIME = 25;


Plantation::Plantation(size_t size) :
    size(size),
    age(0),
    total_harvest(0.)
{}


Plantation::Plantation(Plantation &&other)
{ *this = std::move(other); }


Plantation &Plantation::operator=(Plantation &&other)
{
    patches = std::move(other.patches);
    size = other.size;
    age = other.age;
    total_harvest = other.total_harvest;

    other.size = other.age = other.total_harvest = 0;
    return *this;
}


void Plantation::proceed()
{
    age++;
    for (auto &p : patches) {
        total_harvest += p.proceed(age);
    }

    if (age == ROTATION_TIME) {
        age = 0;
        // TODO: cut down and replant trees
    }
}
