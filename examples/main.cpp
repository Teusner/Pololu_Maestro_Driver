#include "pololu_maestro_driver/pololu_maestro_driver.hpp"

#include <chrono>
#include <thread>


int main() {
    PololuMaestroDriver driver("/dev/POLOLU", 115200);

    // Each actuators test
    for (unsigned int channel=1; channel<=3; ++channel) {
        driver.SetPosition(channel, 1000);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        driver.SetPosition(channel, 2000);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        driver.SetPosition(channel, 1500);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}