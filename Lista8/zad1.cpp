#include <iostream>
#include <memory>

namespace cpplab
{
    class FuelTank
    {
    public:
        FuelTank(uint32_t fuel) : fuel(fuel) {}

        uint32_t refuel(uint32_t fuelRequested)
        {
            return fuel < fuelRequested ? 0 : (fuel -= fuelRequested, fuelRequested);
        }

    private:
        uint32_t fuel;
    };
}

int main()
{
}