#include <algorithm>
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
                        fuelUsed += fuel;
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
            std::chrono::duration<double> elapsedSeconds = std::chrono::system_clock::now() - startTime;
            std::cout << "Fuel used: " << fuelUsed << "\tElapsed time: " << elapsedSeconds.count() << std::endl;
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
        uint32_t fuelUsed{0};
        std::chrono::time_point<std::chrono::system_clock> startTime{std::chrono::system_clock::now()};
    };
}

int main()
{
    std::vector<std::shared_ptr<cpplab::Engine>> engines{
        std::make_shared<cpplab::Engine>(1, std::chrono::seconds(1)),
        std::make_shared<cpplab::Engine>(5, std::chrono::seconds(2)),
        std::make_shared<cpplab::Engine>(2, std::chrono::seconds(3))
    };

    std::vector<std::shared_ptr<cpplab::FuelTank>> fuelTanks;
    std::generate_n(std::back_inserter(fuelTanks), 3, [] { return std::make_shared<cpplab::FuelTank>(10); });
    std::generate_n(std::back_inserter(fuelTanks), 4, [] { return std::make_shared<cpplab::FuelTank>(15); });
    std::generate_n(std::back_inserter(fuelTanks), 4, [] { return std::make_shared<cpplab::FuelTank>(20); });

    for (auto &engine : engines)
        for (auto &fuelTank : fuelTanks)
            engine->addFuelTank(fuelTank);
}