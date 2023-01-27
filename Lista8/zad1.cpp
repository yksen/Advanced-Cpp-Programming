#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

namespace cpplab
{
    class FuelTank
    {
    public:
        FuelTank(uint32_t fuel)
            : fuel(fuel) {}

        uint32_t refuel(uint32_t fuelRequested)
        {
            return fuel < fuelRequested ? 0 : (fuel -= fuelRequested, fuelRequested);
        }

    private:
        uint32_t fuel;
    };

    class Engine
    {
    public:
        Engine(uint32_t fuelConsumption, uint32_t refuelInterval)
            : fuelConsumption(fuelConsumption), refuelInterval(refuelInterval) {}

    private:
        uint32_t fuelConsumption;
        std::chrono::seconds refuelInterval;
        std::vector<std::shared_ptr<FuelTank>> fuelTanks;
    };
}

int main()
{
}