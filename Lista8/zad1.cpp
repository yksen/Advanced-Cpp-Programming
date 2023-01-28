#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
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
            std::lock_guard<std::mutex> lock(mutex);
            return fuel < fuelRequested ? 0 : (fuel -= fuelRequested, fuelRequested);
        }

    private:
        uint32_t fuel;
        std::mutex mutex;
    };

    class Engine
    {
    public:
        Engine(uint32_t fuelConsumption, std::chrono::seconds refuelInterval)
        {
            refuelThread = std::thread([this, fuelConsumption, refuelInterval]
            {
                do
                {
                    std::this_thread::sleep_for(refuelInterval);
                    std::lock_guard<std::mutex> lock(mutex);
                    for (auto fuelTank = fuelTanks.begin(); fuelTank != fuelTanks.end();)
                    {
                        auto fuel = (*fuelTank)->refuel(fuelConsumption);
                        if (fuel == 0)
                            fuelTanks.erase(fuelTank);
                        else
                            fuelTank = fuelTanks.end();
                    }
                } while (!fuelTanks.empty());
            });
        }

        ~Engine()
        {
            refuelThread.join();
        }

        void addFuelTank(std::shared_ptr<FuelTank> fuelTank)
        {
            std::lock_guard<std::mutex> lock(mutex);
            fuelTanks.push_back(fuelTank);
        }

    private:
        std::vector<std::shared_ptr<FuelTank>> fuelTanks;
        std::thread refuelThread;
        std::mutex mutex;
    };
}

int main()
{
}