#include "pololu_maestro_driver/pololu_maestro_driver.hpp"

#include <iostream>
#include <thread>
#include <vector>

int main() {
    PololuMaestroDriver driver("/tmp/ttyS0", 115200);

    uint8_t channel=1;
    std::vector<uint32_t> velocities = {
        100, 200, 400, 800, 1000
    };

    driver.SetPosition(channel, 1000);
    for (const auto &v: velocities) {
        std::cout << "Velocity: " << v << std::endl;
        driver.SetVelocity(channel, v);
        driver.SetPosition(channel, 2000);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        driver.SetPosition(channel, 1000);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}